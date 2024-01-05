#include "tree.h"


Tree::Tree(Seed&& s, int pos) : energy_ (s.energy_), dna_ (std::move(s.dna_)), x_ (pos) {
	add_outgrowths_({x_, 0}, 0);
};


void Tree::give_energy(int energy) {
	energy_ += energy;
}


void Tree::try_to_survive() {
	energy_ -= 16 * mass_ + 4 * age_ + 4 * std::abs(balance_) + dist_b_;
	for (auto og = outgrowths_.begin(); energy_ < 0 && og != outgrowths_.end(); og = outgrowths_.erase(og)) {
		energy_ += og->energy / 2;
		grow_sum_priority_ -= og->priority;
	}
//	print_info();
}


bool Tree::check_alive() const {
	return energy_ >= 0;
}


int Tree::get_age() const {
	return age_;
}


void Tree::proceed_step() {
	int64_t sum_priority = grow_sum_priority_ + dna_.energy_accumulation_priority(age_) * mass_ / 64 + 1;

	++age_;

	for (auto& ps : preseeds_) {
		int energy_add = (int64_t)energy_ * ps.priority / sum_priority;
		ps.energy += energy_add;
		energy_ -= energy_add;
		sum_priority -= ps.priority;
		--ps.steps;
	}
	for (auto& og : outgrowths_) {
		int energy_add = (int64_t)energy_ * og.priority / sum_priority;
		og.energy += energy_add;
		energy_ -= energy_add;
		sum_priority -= og.priority;
	}
}


void Tree::print_info() {
	std::cout << "Energy: " << energy_ << std::endl;
	std::cout << "Age: " << age_ << std::endl;
	std::cout << "Mass " << mass_ << std::endl;
	std::cout << "Outgrowths count: " << outgrowths_.size() << std::endl;
	std::cout << "Preseeds count: " << preseeds_.size() << std::endl;
	std::cout << std::endl;
}


std::vector<Pos> Tree::get_branches(std::function<bool(const Pos&)> check_space) {
	std::vector<Pos> result;
	for (auto og = outgrowths_.begin(); og != outgrowths_.end();) {
		if (og->gene_idx >= dna_.size || og->energy < og->need_energy) {
			++og;
			continue;
		}

		energy_ += og->energy - og->need_energy;
		og->energy = og->need_energy;
		grow_sum_priority_ -= og->priority;

		if (! check_space(og->pos)) {
			og->priority = 0;
			++og;
			continue;
		}

#ifdef HEIGHT
		height_ = std::max(height_, og->pos.y);
#endif // HEIGHT

		balance_ += og->pos.x - x_;
		dist_b_ += og->balance_c * std::abs(og->pos.x - x_);

		add_outgrowths_(og->pos, og->gene_idx);

		result.push_back(og->pos);

		og = outgrowths_.erase(og);
	}
	mass_ += result.size();

	return result;
}


std::vector<std::pair<Seed, Pos>> Tree::get_seeds() {
	std::vector<std::pair<Seed, Pos>> result;
	for (auto ps = preseeds_.begin(); ps != preseeds_.end();) {
		if (ps->steps > 0) {
			++ps;
			continue;
		}
		result.push_back({Seed{dna_, ps->energy / 2}, ps->pos});

		grow_sum_priority_ -= ps->priority;
		ps = preseeds_.erase(ps);
	}

	for (auto og = outgrowths_.begin(); og != outgrowths_.end();) {
		if (og->gene_idx < dna_.size || og->energy < og->need_energy) {
			++og;
			continue;
		}
		energy_ += og->energy - og->need_energy;

		int steps = og->gene_idx + 1 - dna_.size;
		steps = 4 * steps * steps;

		preseeds_.push_front({og->pos, 0, og->priority, steps});

		og = outgrowths_.erase(og);
	}

	return result;
}


std::vector<std::pair<Seed, Pos>> Tree::get_seeds_force() {
	std::vector<std::pair<Seed, Pos>> result;
	result.reserve(preseeds_.size());
	for (const auto& ps : preseeds_) {
		result.push_back({Seed{dna_, ps.energy / 4}, ps.pos});
	}

	return result;
}

uint8_t Tree::get_parent() const {
	return dna_.get_parent();
}


#ifdef SHOW
cv::Vec3b Tree::get_tree_color() const {
	return dna_.get_tree_color();
}


cv::Vec3b Tree::get_seed_color() const {
	return dna_.get_seed_color();
}
#endif // SHOW


#ifdef HEIGHT
int Tree::get_height() const {
	return height_;
}
#endif // HEIGHT

int Tree::branch_energy_by_height_(int y) {
	return 64 + 16 * y;
}


int Tree::seed_energy_by_height_(int y)  {
	return 80 + 8 * y;
}


void Tree::add_outgrowths_(const Pos& pos, const int gene_idx) {
	const auto& gene = dna_.get(gene_idx);
	// left
	if (const auto& og = gene.next(0, age_); og.first < dna_.size + seeds_ && og.second != 0) {
		int need_energy = (og.first < dna_.size)
		                  ? branch_energy_by_height_(pos.y)
		                  : seed_energy_by_height_(pos.y);
		outgrowths_.push_front({{pos.x - 1, pos.y}, need_energy, 0, og.second, og.first, 1});
		grow_sum_priority_ += og.second;
	}
	// top
	if (const auto& og = gene.next(1, age_); og.first < dna_.size + seeds_ && og.second != 0) {
		int need_energy = (og.first < dna_.size)
		                  ? branch_energy_by_height_(pos.y + 1)
		                  : seed_energy_by_height_(pos.y + 1);
		outgrowths_.push_front({{pos.x, pos.y + 1}, need_energy, 0, og.second, og.first, 3});
		grow_sum_priority_ += og.second;
	}
	// right
	if (const auto& og = gene.next(2, age_); og.first < dna_.size + seeds_ && og.second != 0) {
		int need_energy = (og.first < dna_.size)
		                  ? branch_energy_by_height_(pos.y)
		                  : seed_energy_by_height_(pos.y);
		outgrowths_.push_front({{pos.x + 1, pos.y}, need_energy, 0, og.second, og.first, 1});
		grow_sum_priority_ += og.second;
	}
	// bottom
	if (const auto& og = gene.next(3, age_); og.first < dna_.size + seeds_ && og.second != 0 && pos.y > 0) {
		int need_energy = (og.first < dna_.size)
		                  ? branch_energy_by_height_(pos.y - 1)
		                  : seed_energy_by_height_(pos.y - 1);
		outgrowths_.push_front({{pos.x, pos.y - 1}, need_energy, 0, og.second, og.first, 0});
		grow_sum_priority_ += og.second;
	}
}
