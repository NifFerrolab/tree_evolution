#ifndef WORLD_H_
#define WORLD_H_

#include "tree.h"
#include "seed.h"
#include "sun.h"
#include "climat_monitor.h"

#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/videoio.hpp>

#include <list>
#include <utility>
#include <memory>
#include <array>

#include <fstream>


//#define AGE
//#define HEIGHT
//#define SHOW


class World {
public:
	World(int w_s);

	~World();

	void proceed_step();

	bool check_life_exist();

	bool check_space_method(const Pos& pos);

	int trees_count();

	int current_step();

private:
	static constexpr int img_w = 1920, img_h = 1080;
	static constexpr int resize_step = 2;
	static constexpr int graph_h_ = 100 / resize_step, spacer_ = 4 / resize_step, text_w = 400 / resize_step;
	static constexpr int lines_ = 2;
	static constexpr int W = img_w * lines_ / resize_step, H = (img_h / resize_step - graph_h_ - spacer_ * (lines_ + 1)) / lines_;
	std::list<std::shared_ptr<Tree>> trees_ {};
	Sun sun_;
	std::vector<std::list<Seed>> seeds_;
	std::vector<std::array<std::weak_ptr<Tree>, H>> branches_;
	std::vector<std::pair<Pos, cv::Vec3b>> seeds_pos_;
	int step_ = 0;

#ifdef SHOW
	cv::VideoWriter video_;
	Climat climat_monitor_ {img_w / resize_step, 128 * 1024 / 4, Sun::min_e + Sun::rand_add - 1, Sun::max_e + Sun::rand_add - 1, Sun::start_e};
#endif // SHOW

#ifdef AGE
	std::ofstream age_file {"/tmp/age", std::ios::binary};
#endif // AGE

	void give_energy_();

	void check_trees_();

	void tree_grow_();

	void seeds_grow_();

	void get_seeds_();

	void seed_to_ground_(std::pair<Seed, Pos>&& seed_data);

	static int to_word_x_(int x);

	void create_tree_(int x, Seed&& s);

#ifdef SHOW
	void show_();
#endif // SHOW
};


#endif // WORLD_H_
