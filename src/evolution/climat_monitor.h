#ifndef CLIMAT_MONITOR_H_
#define CLIMAT_MONITOR_H_


#include <deque>


class Climat {
public:
	Climat(int graph_points, int total_steps, int min_e, int max_e);

	void add_energy(int last_energy);

	const std::deque<float>& get_stats() const;
private:
	const int step_per_point_;
	const int min_e_;
	const int range_;
	std::deque<int> energy_ {};
	std::deque<float> graph_;
};


#endif
