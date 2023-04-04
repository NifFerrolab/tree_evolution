#ifndef SEED_H_
#define SEED_H_

#include "DNA.h"


class Seed {
	friend class Tree;
public:
	Seed(const DNA& dna, int energy) : dna_ (dna), energy_ (energy) { };

	int get_energy() const {
		return energy_;
	}

	void try_to_survive () {
		energy_ -= 4 + age_;
		++age_;
	}

	bool check_alive() {
		return energy_ >= 0;
	}
private:
	DNA dna_;
	int energy_;
	int age_ { 0 };
};


#endif
