#ifndef SUN_H_
#define SUN_H_


#include "rand.h"


class Sun {
public:
	static constexpr int min_e = 143;
	static constexpr int max_e = 343 * 343 / min_e;
	static constexpr int start_e = (max_e * 3 + min_e) / 4;
	static constexpr int rand_add = 16;
	static constexpr int move_num = 6, move_denum = 2;

	Sun() {
		std::cout << "Min e " << min_e << std::endl;
	};

	int get_energy() {
//		return 359;
		return energy_ + step_add + rand_int(rand_add);
	}

	void next_step() {
		step_add = rand_int(rand_add);
		energy_ += (rand_int(2 * move_num + 1) - move_num) / move_denum;
		if (energy_ < min_e) {
			energy_ = min_e;
		} else if (energy_ > max_e) {
			energy_ = max_e;
		}
	}

	int current_sun_energy() {
		return energy_ + rand_add - 1;
	}

	static constexpr int min_energy() {
		return min_e + rand_add - 1;
	}
private:
	int energy_ { start_e };
	int step_add { 0 };
};


#endif
