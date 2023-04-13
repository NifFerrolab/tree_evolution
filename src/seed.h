#ifndef SEED_H_
#define SEED_H_

#include "DNA.h"


class Seed {
	friend class Tree;
public:
	Seed(const DNA& dna, int energy) : dna_ (dna), energy_ (energy) { };

	void set_target_step(int step) {
		target_step_ = dna_.seed_wait_time() + step;
	}

	int get_target_step() const {
		return target_step_;
	}

	void try_to_survive () {
		energy_ -= 4 + age_;
		++age_;
	}

	bool check_alive() const {
		return energy_ >= 0;
	}

	int get_age() const {
		return age_;
	}

	bool operator < (const Seed& another) const {
		return target_step_ < another.target_step_;
	}
private:
	DNA dna_;
	int energy_;
	int age_ { 0 };
	int target_step_ { 0 };
};


#endif
