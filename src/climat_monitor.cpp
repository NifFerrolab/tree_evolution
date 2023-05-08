#include "climat_monitor.h"


Climat::Climat(int graph_points, int total_steps, int min_e, int max_e, int start_v)
	: step_per_point_ ((total_steps + graph_points / 2) / graph_points),
	  min_e_(min_e),
	  range_(max_e - min_e)
{
	graph_ = std::deque<float>(graph_points, (start_v - min_e) / range_);
}


void Climat::add_energy(int last_energy) {
	energy_.push_back(last_energy - min_e_);

	while ((int)energy_.size() >= step_per_point_) {
		float new_p = 0;
		for (int i = 0; i < step_per_point_; ++i) {
			new_p += energy_[0];
			energy_.pop_front();
		}
		new_p /= step_per_point_ * range_;
		graph_.pop_front();
		graph_.push_back(new_p);
	}
}


const std::deque<float>& Climat::get_stats() const {

	return graph_;
}
