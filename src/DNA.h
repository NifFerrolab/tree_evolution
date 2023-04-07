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
	DNA(int color_idx, int trees) {
		color_ = {(uint8_t)((color_idx % 2 * 90 + color_idx / 2 * 45) % 180), 255, 160};
		fill_priority_();

//		// min energy
//		genes_[0].next_outgrowth_[0] = {{31, 31}, 0, 0};
//		genes_[0].next_outgrowth_[1] = {{16, 0}, 1, -9};
//		genes_[0].next_outgrowth_[2] = {{31, 31}, -1, 9};
//		genes_[0].next_outgrowth_[3] = {{31, 31}, 0, 0};

//		// max height
//		genes_[0].next_outgrowth_[0] = {{31, 14}, 16, 0};
//		genes_[0].next_outgrowth_[1] = {{1, 0}, 1, -9};
//		genes_[0].next_outgrowth_[2] = {{15, 31}, -16, 0};
//		genes_[0].next_outgrowth_[3] = {{31, 31}, -1, 9};
//
//		genes_[1].next_outgrowth_[0] = {{31, 31}, 0, 0};
//		genes_[1].next_outgrowth_[1] = {{31, 1}, 16, 0};
//		genes_[1].next_outgrowth_[2] = {{31, 31}, 0, 0};
//		genes_[1].next_outgrowth_[3] = {{31, 31}, -16, 0};
//
//		genes_[2].next_outgrowth_[0] = {{31, 31}, 0, 0};
//		genes_[2].next_outgrowth_[1] = {{3, 3}, 0, 0};
//		genes_[2].next_outgrowth_[2] = {{31, 31}, 0, 0};
//		genes_[2].next_outgrowth_[3] = {{31, 31}, 0, 0};
//
//		genes_[3].next_outgrowth_[0] = {{31, 31}, 0, 0};
//		genes_[3].next_outgrowth_[1] = {{4, 4}, 0, 0};
//		genes_[3].next_outgrowth_[2] = {{31, 31}, 0, 0};
//		genes_[3].next_outgrowth_[3] = {{31, 31}, 0, 0};
//
//		genes_[4].next_outgrowth_[0] = {{31, 31}, 0, 0};
//		genes_[4].next_outgrowth_[1] = {{5, 5}, 0, 0};
//		genes_[4].next_outgrowth_[2] = {{31, 31}, 0, 0};
//		genes_[4].next_outgrowth_[3] = {{31, 31}, 0, 0};
//
//		genes_[5].next_outgrowth_[0] = {{31, 31}, 0, 0};
//		genes_[5].next_outgrowth_[1] = {{6, 6}, 0, 0};
//		genes_[5].next_outgrowth_[2] = {{31, 31}, 0, 0};
//		genes_[5].next_outgrowth_[3] = {{31, 31}, 0, 0};
//
//		genes_[6].next_outgrowth_[0] = {{31, 31}, 0, 0};
//		genes_[6].next_outgrowth_[1] = {{7, 7}, 0, 0};
//		genes_[6].next_outgrowth_[2] = {{31, 31}, 0, 0};
//		genes_[6].next_outgrowth_[3] = {{31, 31}, 0, 0};
//
//		genes_[7].next_outgrowth_[0] = {{31, 31}, 0, 0};
//		genes_[7].next_outgrowth_[1] = {{8, 8}, 0, 0};
//		genes_[7].next_outgrowth_[2] = {{31, 31}, 0, 0};
//		genes_[7].next_outgrowth_[3] = {{31, 31}, 0, 0};
//
//		genes_[8].next_outgrowth_[0] = {{31, 31}, 0, 0};
//		genes_[8].next_outgrowth_[1] = {{9, 9}, 0, 0};
//		genes_[8].next_outgrowth_[2] = {{31, 31}, 0, 0};
//		genes_[8].next_outgrowth_[3] = {{31, 31}, 0, 0};
//
//		genes_[9].next_outgrowth_[0] = {{31, 31}, 0, 0};
//		genes_[9].next_outgrowth_[1] = {{10, 10}, 0, 0};
//		genes_[9].next_outgrowth_[2] = {{31, 31}, 0, 0};
//		genes_[9].next_outgrowth_[3] = {{31, 31}, 0, 0};
//
//		genes_[10].next_outgrowth_[0] = {{31, 31}, 0, 0};
//		genes_[10].next_outgrowth_[1] = {{11, 11}, 0, 0};
//		genes_[10].next_outgrowth_[2] = {{31, 31}, 0, 0};
//		genes_[10].next_outgrowth_[3] = {{31, 31}, 0, 0};
//
//		genes_[11].next_outgrowth_[0] = {{31, 31}, 0, 0};
//		genes_[11].next_outgrowth_[1] = {{12, 12}, 0, 0};
//		genes_[11].next_outgrowth_[2] = {{31, 31}, 0, 0};
//		genes_[11].next_outgrowth_[3] = {{31, 31}, 0, 0};
//
//		genes_[12].next_outgrowth_[0] = {{31, 31}, 0, 0};
//		genes_[12].next_outgrowth_[1] = {{13, 13}, 0, 0};
//		genes_[12].next_outgrowth_[2] = {{31, 31}, 0, 0};
//		genes_[12].next_outgrowth_[3] = {{31, 31}, 0, 0};
//
//		genes_[13].next_outgrowth_[0] = {{31, 14}, 0, 0};
//		genes_[13].next_outgrowth_[1] = {{0, 0}, 0, 0};
//		genes_[13].next_outgrowth_[2] = {{15, 31}, 0, 0};
//		genes_[13].next_outgrowth_[3] = {{31, 31}, 0, 0};
//
//		genes_[14].next_outgrowth_[0] = {{31, 14}, 10, -11};
//		genes_[14].next_outgrowth_[1] = {{31, 31}, 0, 0};
//		genes_[14].next_outgrowth_[2] = {{31, 31}, 0, 0};
//		genes_[14].next_outgrowth_[3] = {{31, 31}, 0, 0};
//
//		genes_[15].next_outgrowth_[0] = {{31, 31}, 0, 0};
//		genes_[15].next_outgrowth_[1] = {{31, 31}, 0, 0};
//		genes_[15].next_outgrowth_[2] = {{15, 31}, -10, 11};
//		genes_[15].next_outgrowth_[3] = {{31, 31}, 0, 0};
	}

	DNA(const DNA& parent_dna) {
		float mut = rand_float();
		genes_ = parent_dna.genes_;
		if (mut < mutation_p_) {
			color_ = parent_dna.color_;
		} else {
			int mut_c = 1;
			mut -= mutation_p_;
			float p = mutation_p_ * 256 / 1023;
			while (mut > p) {
				mut -= p;
				++mut_c;
				p *= (float)(257 - mut_c) / mut_c / 1023;
			}
			for (int i = 0; i < mut_c; ++i) {
				genes_[rand_int(size)].mutation();
			}
			color_[0] = (parent_dna.color_[0] + rand_int(5) + 178) % 180;
			color_[1] = parent_dna.color_[1];
			color_[2] = std::max(std::min((parent_dna.color_[2] + rand_int(5) - 2), 255), 64);
		}
		fill_priority_();
	}

	DNA(DNA&& parent_dna) {
		genes_ = std::move(parent_dna.genes_);
		color_ = std::move(parent_dna.color_);
		fill_priority_();
	}
	const Gene& get(int i) const {
		return genes_[i];
	}

	cv::Vec3b get_tree_color() const {
		return color_;
	}

	cv::Vec3b get_seed_color() const {
		return {color_[0], 128, (uint8_t)((255 + color_[2]) / 2)};
	}

	int64_t energy_accumulation_priority(int age) const {
		int64_t priority = std::max(priority_ + priority_add_ * age, 0l);
		return priority;
	}
private:
	static constexpr float mutation_p_ = std::pow(1023. / 1024, 256);
	std::array<Gene, size> genes_ {};
	cv::Vec3b color_;
	int64_t priority_{0}, priority_add_{0};

	void fill_priority_() {
		priority_ = 0;
		priority_add_ = 0;
		for (const auto& g : genes_) {
			auto p = g.energy_accumulation_priority();
			priority_ += p.first;
			priority_add_ += p.second;
		}
	}
};


#endif
