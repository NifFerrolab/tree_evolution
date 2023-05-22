#include "seed.h"


Seed::Seed(const DNA& dna, int energy) : dna_ (dna), energy_ (energy) { };


void Seed::set_target_step(int step) {
	target_step_ = dna_.seed_wait_time() + step;
}


int Seed::get_target_step() const {
	return target_step_;
}


void Seed::try_to_survive () {
	energy_ -= 4 + age_;
	++age_;
}


bool Seed::check_alive() const {
	return energy_ >= 0;
}


int Seed::get_age() const {
	return age_;
}


bool Seed::operator < (const Seed& another) const {
	return target_step_ < another.target_step_;
}
