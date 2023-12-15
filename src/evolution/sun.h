#ifndef SUN_H_
#define SUN_H_


#include "rand.h"


class Sun {
public:
	static constexpr int min_e = 137;
	static constexpr int max_e = 343 * 343 / min_e;
	static constexpr int start_e = (max_e * 3 + min_e) / 4;
	static constexpr int rand_add = 16;
	static constexpr int move_num = 10, move_denum = 3;

	Sun();

	int get_energy();

	void next_step();

	int current_sun_energy() const;

	static constexpr int min_energy();
private:
	int energy_ { start_e };
	int step_add { 0 };
};


#endif
