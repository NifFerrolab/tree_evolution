#ifndef GENE_H_
#define GENE_H_

#include "rand.h"

#include <cstdint>
#include <array>
#include <utility>
#include <cmath>

struct DirectionGrow {
	int8_t next_gene[2];
	int8_t priority;
	int8_t priority_add;

	bool operator == (const DirectionGrow& another) const {
		return (priority == another.priority) && (priority_add == another.priority_add)
				&& (next_gene[0] == another.next_gene[0]) && (next_gene[1] == another.next_gene[1]);
	}
};

class Gene {
public:
	static constexpr uint8_t max_v = 32;
	static constexpr int mutation = 1024;
	static constexpr int priority_c = 64;

	Gene() {
		for (auto& og : next_outgrowth_) {
			og.next_gene[0] = rand_int(max_v);
			og.next_gene[1] = rand_int(max_v);
			og.priority = rand_int(max_v + 1) - max_v / 2;
			og.priority_add = rand_int(max_v + 1) - max_v / 2;
		}
	}
	Gene(const Gene& parent_gene) {
		for (std::size_t i = 0; i < next_outgrowth_.size(); ++i) {
			auto& og = next_outgrowth_[i];
			auto& pg = parent_gene.next_outgrowth_[i];
			og.next_gene[0] = rand_int(mutation) ? pg.next_gene[0] : rand_int(max_v);
			og.next_gene[1] = rand_int(mutation) ? pg.next_gene[1] : rand_int(max_v);
			og.priority = rand_int(mutation) ? pg.priority : rand_int(max_v + 1) - max_v / 2;
			og.priority_add = rand_int(mutation) ? pg.priority_add : rand_int(max_v + 1) - max_v / 2;
		}
	}
	Gene(Gene&& parent_gene) {
		next_outgrowth_ = std::move(parent_gene.next_outgrowth_);
	}
	Gene& operator=(const Gene& parent_gene) {
		for (std::size_t i = 0; i < next_outgrowth_.size(); ++i) {
			auto& og = next_outgrowth_[i];
			const auto& pg = parent_gene.next_outgrowth_[i];
			og.next_gene[0] = rand_int(mutation) ? pg.next_gene[0] : rand_int(max_v);
			og.next_gene[1] = rand_int(mutation) ? pg.next_gene[1] : rand_int(max_v);
			og.priority = rand_int(mutation) ? pg.priority : rand_int(max_v + 1) - max_v / 2;
			og.priority_add = rand_int(mutation) ? pg.priority_add : rand_int(max_v + 1) - max_v / 2;
		}
		return *this;
	}
	Gene& operator=(Gene&& parent_gene) {
		next_outgrowth_ = std::move(parent_gene.next_outgrowth_);
		return *this;
	}

	std::pair<uint8_t, int> next(int idx, int age) const {
		const auto& og = next_outgrowth_[idx];
		int priority = age * og.priority_add + og.priority * priority_c;

		return { og.next_gene[priority >= 0], std::abs(priority) + (priority >= 0) };
	}

	int energy_accumulation_priority (int age) const {
		int priority = 0;
		for (const auto& og : next_outgrowth_) {
			priority += age * og.priority_add + og.priority * priority_c;
		}
		return priority;
	}

	bool operator == (const Gene& another) const {
		return next_outgrowth_ == another.next_outgrowth_;
	}

//private:
	std::array<DirectionGrow, 4> next_outgrowth_;
};

#endif
