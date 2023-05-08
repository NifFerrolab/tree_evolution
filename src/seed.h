#ifndef SEED_H_
#define SEED_H_

#include "DNA.h"


class Seed {
	friend class Tree;
public:
	Seed(const DNA& dna, int energy);

	void set_target_step(int step);

	int get_target_step() const;

	void try_to_survive ();

	bool check_alive() const;

	int get_age() const;

	bool operator < (const Seed& another) const;
private:
	DNA dna_;
	int energy_;
	int age_ { 0 };
	int target_step_ { 0 };
};


#endif
