#include "world.h"

#include <chrono>

namespace chr = std::chrono;


int main() {
	int w_i = 765;
	while (true) {
		std::cout << "w_i " << w_i << std::endl;
		auto begin = chr::steady_clock::now();
		World w(w_i);
		++w_i;
		while(w.current_step() < 5*60*60*30) {
//		while(w.current_step() < 2'000'000) {
//		while(w.current_step() < 30'000) {
			w.proceed_step();
			if (! w.check_life_exist()) {
				std::cout << "All died\n";
				break;
			}
		}
		auto end = chr::steady_clock::now();
		std::cout << chr::duration_cast<chr::seconds>(end - begin).count() << " seconds\n";
		std::cout << "Done\n";
		break;
	}

	return 0;
}
