#ifndef TREE_H_
#define TREE_H_

#include "seed.h"
#include "DNA.h"

#include <list>
#include <vector>
#include <functional>

#include <iostream>


struct Pos {
	int x, y;
};


struct Outgrowth {
	Pos pos;
	int need_energy;
	int energy;
	int priority;
	uint8_t gene_idx;
	int8_t balance_c;
};


struct Preseed {
	Pos pos;
	int energy;
	int priority;
	int steps;
};


class Tree {
public:
	Tree(Seed&& s, int pos);

	void give_energy(int energy);

	void try_to_survive();

	bool check_alive() const;

	int get_age() const;

	void proceed_step();

	void print_info();

	std::vector<Pos> get_branches(std::function<bool(const Pos&)> check_space);

	std::vector<std::pair<Seed, Pos>> get_seeds();

	std::vector<std::pair<Seed, Pos>> get_seeds_force();

	cv::Vec3b get_tree_color() const;

	cv::Vec3b get_seed_color() const;
private:
	static constexpr int seeds_ = 8;

	int age_ { 0 };
	int mass_ { 1 };
	int energy_;
	int balance_ { 0 };
	int dist_b_ { 0 };
	int64_t grow_sum_priority_ { 0 };

	DNA dna_;
	int x_;

	std::list<Outgrowth> outgrowths_ {};
	std::list<Preseed> preseeds_ {};

	static int branch_energy_by_height_(int y);

	static int seed_energy_by_height_(int y);

	void add_outgrowths_(const Pos& pos, const int gene_idx);
};


#endif
