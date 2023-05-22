#include "world.h"
#ifdef SHOW
#include "world_img.h"
#include "video_output.h"
#endif // SHOW

#include <chrono>
#include <cstdlib>

namespace chr = std::chrono;


int main(int argc, char *argv[]) {
	uint w_i = chr::time_point_cast<chr::seconds>(chr::system_clock::now()).time_since_epoch().count();
	if (argc > 1) {
		w_i = std::atoi(argv[1]);
	}
	int steps = 5 * 60 * 60 * 30;
	if (argc > 2) {
		steps = std::atoi(argv[2]);
	}

	std::cout << "w_i " << w_i << std::endl;
	auto begin = chr::steady_clock::now();
	World w(w_i);
#ifdef SHOW
	World_Img img_maker(w);
	Video_Output video(img_maker, w_i);
#endif // SHOW
	while(w.current_step() < steps && w.check_life_exist()) {
		w.proceed_step();
#ifdef SHOW
		video.feed_img();
#endif // SHOW
	}
	if (! w.check_life_exist()) {
		std::cout << "All died\n";
	}
	auto end = chr::steady_clock::now();
	std::cout << chr::duration_cast<chr::seconds>(end - begin).count() << " seconds\n";
	std::cout << "Done\n";

	return 0;
}
