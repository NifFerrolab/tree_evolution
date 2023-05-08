#include "gene.h"


bool DirectionGrow::operator == (const DirectionGrow& another) const {
	return (priority == another.priority) && (priority_add == another.priority_add)
			&& (next_gene[0] == another.next_gene[0]) && (next_gene[1] == another.next_gene[1]);
}


Gene::Gene() {
	for (auto& og : next_outgrowth_) {
		og.next_gene[0] = rand_int(max_v);
		og.next_gene[1] = rand_int(max_v);
		og.priority = rand_int(max_v + 1) - max_v / 2;
		og.priority_add = rand_int(max_v + 1) - max_v / 2;
	}
}


void Gene::mutation() {
	auto& mut_og = next_outgrowth_[rand_int(next_outgrowth_.size())];
	switch (rand_int(4)) {
	case 0:
		mut_og.next_gene[0] = rand_int(max_v);
		break;
	case 1:
		mut_og.next_gene[1] = rand_int(max_v);
		break;
	case 2:
		mut_og.priority = rand_int(max_v + 1) - max_v / 2;
		break;
	case 3:
		mut_og.priority_add = rand_int(max_v + 1) - max_v / 2;
		break;
	default:
		std::cout << "Error\n";
	}
}


std::pair<uint8_t, int> Gene::next(int idx, int age) const {
	const auto& og = next_outgrowth_[idx];
	int priority = age * og.priority_add + og.priority * priority_c;

	return { og.next_gene[priority >= 0], std::abs(priority) + (priority >= 0) };
}


std::pair<int, int> Gene::energy_accumulation_priority () const {
	int priority = 0;
	int priority_add = 0;
	for (const auto& og : next_outgrowth_) {
		priority += og.priority;
		priority_add += og.priority_add;
	}
	priority *= priority_c;
	return {priority, priority_add};
}


int Gene::seed_wait_time() const {
	int t = 0;
	for (const auto& d : next_outgrowth_) {
		t += d.next_gene[1] - d.next_gene[0];
	}

	return t;
}


bool Gene::operator == (const Gene& another) const {
	return next_outgrowth_ == another.next_outgrowth_;
}
