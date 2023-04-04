#include "rand.h"

#include <cstdlib>
#include <ctime>


int rand_int(int rand_max) {
	return rand() % rand_max;
}

float rand_float() {
	return (float) rand() / RAND_MAX;
}
