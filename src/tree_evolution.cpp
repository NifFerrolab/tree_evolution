#include "world.h"

int main() {
	int w_i = 666;
	std::cout << "w_i " << w_i << std::endl;
	while (true) {
		World w(w_i);
		++w_i;
		while(w.current_step() < 40*60*60*2) {
//		while(w.current_step() < 2'000'000) {
			w.proceed_step();
			if (! w.check_life_exist()) {
				std::cout << "All died\n";
				break;
			}
		}
		std::cout << "Done\n";
//		break;
	}

	return 0;
}
