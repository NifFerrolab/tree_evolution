#ifndef GENE_H_
#define GENE_H_

#include "rand.h"

#include <cstdint>
#include <array>
#include <utility>
#include <cmath>

#include <iostream>

struct DirectionGrow {
	int8_t next_gene[2];
	int8_t priority;
	int8_t priority_add;

	bool operator == (const DirectionGrow& another) const;
};

class Gene {
public:
	Gene();

	void mutation();

	std::pair<uint8_t, int> next(int idx, int age) const;

	std::pair<int, int> energy_accumulation_priority () const;

	int seed_wait_time() const;

	bool operator == (const Gene& another) const;

private:
	static constexpr uint8_t max_v = 32;
	static constexpr int priority_c = 64;
	std::array<DirectionGrow, 4> next_outgrowth_;
};

#endif
