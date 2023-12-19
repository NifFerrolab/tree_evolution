#ifndef WORLD_H_
#define WORLD_H_

#include "tree.h"
#include "seed.h"
#include "sun.h"

#ifdef SHOW
#include "climat_monitor.h"

#include <opencv2/core.hpp>
#endif // SHOW

#include <list>
#include <set>
#include <utility>
#include <memory>

#include <fstream>


class World {
	friend class World_Img;
public:
	World(uint w_s);

	void proceed_step();

	bool check_life_exist() const;

	bool check_space_method(const Pos& pos);

	int trees_count() const;

	int current_step() const;

private:
	static constexpr int W = 1920 * 2;
	std::list<std::shared_ptr<Tree>> trees_ {};
	Sun sun_;
	std::vector<std::multiset<Seed>> sleeping_seeds_;
	std::vector<std::list<Seed>> growing_seeds_;
	std::vector<std::vector<std::weak_ptr<Tree>>> branches_;
#ifdef SHOW
	std::vector<std::pair<Pos, cv::Vec3b>> seeds_pos_;
#endif // SHOW
	int step_ = 0;

#ifdef SHOW
	Climat climat_monitor_ {1920 / 2, 128 * 1024 / 4, Sun::min_e + Sun::rand_add - 1, Sun::max_e + Sun::rand_add - 1, Sun::start_e};
#endif // SHOW

#ifdef AGE
	std::ofstream age_file {"/tmp/age", std::ios::binary};
#endif // AGE

#ifdef AGE_SEED
	std::ofstream age_seed_file {"/tmp/age_seed", std::ios::binary};
#endif // AGE_SEED

#ifdef SLEEP_SEED
	std::ofstream sleep_seed_file {"/tmp/sleep_seed", std::ios::binary};
#endif // SLEEP_SEED

#ifdef HEIGHT
	std::ofstream height_file {"/tmp/height", std::ios::binary};
#endif // HEIGHT

	void give_energy_();

	void check_trees_();

	void tree_grow_();

	void seeds_grow_();

	void get_seeds_();

	void seed_to_ground_(std::pair<Seed, Pos>&& seed_data);

	static int to_word_x_(int x);

	void create_tree_(int x, Seed&& s);
};


#endif // WORLD_H_
