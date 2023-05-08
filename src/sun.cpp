#include "sun.h"

#include <iostream>


Sun::Sun() {
	std::cout << "Min e " << min_e << std::endl;
};


int Sun::get_energy() {
//	return 359;
	return energy_ + step_add + rand_int(rand_add);
}


void Sun::next_step() {
	step_add = rand_int(rand_add);
	energy_ += (rand_int(2 * move_num + 1) - move_num) / move_denum;
	if (energy_ < min_e) {
		energy_ = min_e;
	} else if (energy_ > max_e) {
		energy_ = max_e;
	}
}


int Sun::current_sun_energy() {
	return energy_ + rand_add - 1;
}


constexpr int Sun::min_energy() {
	return min_e + rand_add - 1;
}
