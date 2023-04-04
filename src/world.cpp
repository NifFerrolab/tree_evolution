#include "world.h"


World::World(int w_s) {
//	std::cout << "Word H: " << H << std::endl;
	seeds_.resize(W);
	branches_.resize(W);
	std::srand(w_s);
	static constexpr int seeds_start = 4;
	for(int i = 0; i < seeds_start; ++i) {
		create_tree_((2 * i + 1) * W / 2 / seeds_start, Seed(DNA(i, seeds_start), Sun::min_e));
	}
#ifdef SHOW
	video_ = cv::VideoWriter{"/Windows/D/Downloads/Videos/digital_trees/" + std::to_string(w_s) + "_" + std::to_string(Sun::min_e) + ".mkv",
		cv::VideoWriter::fourcc('H', '2', '6', '4'), 60, {img_w, img_h}};
#endif // SHOW
}

World::~World() {
#ifdef SHOW
	video_.release();
#endif // SHOW
}



void World::proceed_step() {
	give_energy_();
	check_trees_();
	tree_grow_();
	seeds_grow_();
	get_seeds_();

#ifdef SHOW
	if (step_ % 2 == 0) {
		show_();
	}
//		show_();
#endif // SHOW

	++step_;
	if (step_ % 1000 == 0) {
		std::cout << step_ / 1000 << std::endl;
	}

//	std::cout << step << std::endl;
}

bool World::check_life_exist() {
	if (! trees_.empty()) {
		return true;
	}

	for (const auto& s : seeds_) {
		if (! s.empty()) {
			return true;
		}
	}

	return false;
}

bool World::check_space_method(const Pos& pos) {
	int x = to_word_x_(pos.x);
#ifdef HEIGHT
	static int max_h = 0;
	if (max_h < pos.y) {
		max_h = pos.y;
		std::cout << "New max h" << max_h << std::endl;
	}
#endif // HEIGHT
	return pos.y >= 0 && pos.y < H && branches_[x][pos.y].expired();
}

int World::trees_count() {
	return trees_.size();
}

int World::current_step() {
	return step_;
}

void World::give_energy_() {
	sun_.next_step();

#ifdef SHOW
	climat_monitor_.add_energy(sun_.current_sun_energy());
#endif // SHOW
	for (auto& col : branches_) {
		int energy = sun_.get_energy();
		for (int i = H - 1; i >= 0; --i) {
			if (auto b_sh = col[i].lock()) {
				int before = energy;
				energy = energy * 3 / 4;
				b_sh->give_energy(before - energy);
			}
		}
	}
}

void World::check_trees_() {
	seeds_pos_.clear();
	for (auto t = trees_.begin(); t != trees_.end(); ) {
		(*t)->try_to_survive();
		if (! (*t)->check_alive()) {
#ifdef AGE
			const int age = (*t)->get_age();
#endif //  AGE
			const auto seed_color = (*t)->get_seed_color();
			for (auto& s : (*t)->get_seeds_force()) {
#ifdef AGE
				age_file.write((char*)(&age), sizeof(age));
#endif //  AGE
				seeds_pos_.emplace_back(s.second, seed_color);
				seed_to_ground_(std::move(s));
			}
			t = trees_.erase(t);
		} else {
			++t;
		}
	}
}

void World::tree_grow_() {
	for (auto& t : trees_) {
		t->proceed_step();

		auto branches = t->get_branches([this](const Pos& pos) {return this->check_space_method(pos);});
		for (auto [x, y] : branches) {
			x = to_word_x_(x);
			branches_[x][y] = t;
		}
	}
}

void World::seeds_grow_() {
	for (int i = 0; i < W; ++i) {
		if (branches_[i][0].expired() && ! seeds_[i].empty()) {
			int idx = rand_int(seeds_[i].size());
			auto s = std::next(seeds_[i].begin(), idx);
			if (s->check_alive()) {
				create_tree_(i, std::move(*s));
			}
			seeds_[i].erase(s);
		}
		for (auto& s : seeds_[i]) {
			s.try_to_survive();
		}
	}
}

void World::get_seeds_() {
	for (auto& t : trees_) {
		const auto seed_color = t->get_seed_color();
#ifdef AGE
		const int age = t->get_age();
#endif //  AGE
		for (auto& s : t->get_seeds()) {
#ifdef AGE
			age_file.write((char*)(&age), sizeof(age));
#endif //  AGE
			seeds_pos_.emplace_back(s.second, seed_color);
			seed_to_ground_(std::move(s));
		}
	}
}

void World::seed_to_ground_(std::pair<Seed, Pos>&& seed_data) {
	while (seed_data.second.y >= 0) {
		--seed_data.second.y;
		switch (rand_int(4)) {
		case 0:
			--seed_data.second.x;
			break;
		case 1:
			++seed_data.second.x;
		}
	}
	seeds_[to_word_x_(seed_data.second.x)].push_front(std::move(seed_data.first));
}

int World::to_word_x_(int x) {
	while (x < 0) {
		x += W;
	}
	return x %= W;
}

void World::create_tree_(int x, Seed&& s) {
	auto t = std::make_shared<Tree>(std::move(s), x);
	trees_.push_front(t);
	branches_[x][0] = t;
}

#ifdef SHOW
void World::show_() {
	cv::Mat img(img_h / resize_step, img_w / resize_step, CV_8UC3, {0, 0, 0});
	for (int i = 0; i < W; ++i) {
		const auto& col = branches_[i];
		const int x = i % (W / lines_);
		const int h_add = graph_h_ + (1 + i * lines_ / W) * (H + spacer_) - 1;
		for (int j = 0; j < H; ++j) {
			int y = h_add - j;
			if (auto b_sh = col[j].lock()) {
				img.at<cv::Vec3b>(y, x) = b_sh->get_tree_color();
			}
		}
	}

	for (const auto& sp : seeds_pos_) {
		int x_ = to_word_x_(sp.first.x);
		int x = x_ % (W / lines_);
		int y = graph_h_ + (1 + x_ * lines_ / W) * (H + spacer_) - 1 - sp.first.y;
		img.at<cv::Vec3b>(y, x) = sp.second;
	}

	auto stats = climat_monitor_.get_stats();
	for (int i = 0; i < (int)stats.size(); ++i) {
		img.at<cv::Vec3b>(graph_h_ * (1 - stats[i]), i) = {(uint8_t)(120 + 60 * stats[i]), 255, 255};
	}

	cv::cvtColor(img, img, cv::COLOR_HSV2BGR);

	for (int i = 0; i < lines_ + 1; ++i) {
		cv::rectangle(img, {0, graph_h_+i*(H+spacer_)}, {img.cols-1, (graph_h_+spacer_)+i*(H+spacer_)}, {128, 128, 128}, -1);
	}

	cv::resize(img, img, cv::Size(), resize_step, resize_step, cv::INTER_NEAREST);

	cv::putText(img, "Sun energy: " + std::to_string(sun_.current_sun_energy()),
			cv::Point(0, 32), cv::FONT_HERSHEY_COMPLEX, 1, {255, 255, 255}, 1, cv::LINE_AA);

	cv::putText(img, "Step: " + std::to_string(step_),
			cv::Point(0, 64), cv::FONT_HERSHEY_COMPLEX, 1, {255, 255, 255}, 1, cv::LINE_AA);

	cv::putText(img, "Trees alive: " + std::to_string(trees_.size()),
			cv::Point(0, 96), cv::FONT_HERSHEY_COMPLEX, 1, {255, 255, 255}, 1, cv::LINE_AA);

//	cv::imshow("World", img);
//	cv::waitKey(1);

	video_ << img;
}
#endif // SHOW

