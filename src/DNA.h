#ifndef DNA_H_
#define DNA_H_

#include "gene.h"

#include <opencv2/core.hpp>

#include <array>
#include <cmath>
#include <algorithm>


class DNA {
public:
	static constexpr int size = 16;
	DNA(int color_idx, int trees);

	DNA(const DNA& parent_dna);

	DNA(DNA&& parent_dna);

	const Gene& get(int i) const;

	cv::Vec3b get_tree_color() const;

	cv::Vec3b get_seed_color() const;

	int64_t energy_accumulation_priority(int age) const;

	int seed_wait_time() const;
private:
	static constexpr float mutation_p_ = std::pow(1023. / 1024, 256);
	std::array<Gene, size> genes_ {};
	cv::Vec3b color_;
	int64_t priority_{0}, priority_add_{0};

	void fill_priority_();
};


#endif
