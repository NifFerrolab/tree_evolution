#include "world_img.h"

#include <opencv2/imgproc.hpp>


static constexpr int img_w = 1920, img_h = 1080;
static constexpr int graph_h_ = 100, spacer_ = 4;
static constexpr int lines_ = 4;

World_Img::World_Img(const World& w) : w_(w), W(img_w), H(img_h),
		line_h_((H - graph_h_ - spacer_ * (lines_ + 1)) / lines_) {

}

template <class T>
bool compare_weak_ptr(std::weak_ptr<T> p1, std::weak_ptr<T> p2) {
	return !p1.owner_before(p2) && !p2.owner_before(p1);
}

cv::Mat World_Img::get_img() {
	if (w_.current_step() == last_step_) {
		return last_img_;
	}

	last_step_ = w_.current_step();
	last_img_ = cv::Mat(H, W, CV_8UC3, {0, 0, 0});

	for (int i = 0; i < w_.W; ++i) {
		const auto& col = w_.branches_[i];
		const auto& col_next = w_.branches_[(i + 1) % w_.W];
		const int x = 4 * (i % (w_.W / lines_));
		const int h_add = graph_h_ + (1 + i * lines_ / w_.W) * (line_h_ + spacer_) - 1;
		for (int j = 0; j < line_h_ / 4 && (size_t)j < col.size(); ++j) {
			int y = h_add - 4 * j;
			if (auto b_sh = col[j].lock()) {
				cv::rectangle(last_img_, cv::Rect(x, y - 2, 3, 3), b_sh->get_tree_color(), cv::FILLED);
				uint8_t neighbors = 1;
				if (j < col_next.size() && compare_weak_ptr(col_next[j], col[j])) {
					cv::rectangle(last_img_, cv::Rect(x + 3, y - 2, 1, 3), b_sh->get_tree_color(), cv::FILLED);
					++neighbors;
				}
				if (j + 1 < col.size() && compare_weak_ptr(col[j + 1], col[j])) {
					cv::rectangle(last_img_, cv::Rect(x, y - 3, 3, 1), b_sh->get_tree_color(), cv::FILLED);
					++neighbors;
				}
				if (neighbors == 3 && j + 1 < col_next.size() && compare_weak_ptr(col_next[j + 1], col[j])) {
					last_img_.at<cv::Vec3b>(y - 3, x + 3) = b_sh->get_tree_color();
				}
			}
		}
	}

	for (const auto& sp : w_.seeds_pos_) {
		if (sp.first.y >= line_h_ / 4) {
			continue;
		}
		int x_ = w_.to_word_x_(sp.first.x);
		int x = 4 * (x_ % (w_.W / lines_));
		int y = graph_h_ + (1 + x_ * lines_ / w_.W) * (line_h_ + spacer_) - 1 - 4 *sp.first.y;
		cv::rectangle(last_img_, cv::Rect(x, y - 2, 3, 3), sp.second, cv::FILLED);
	}

	auto stats = w_.climat_monitor_.get_stats();
	for (int i = 0; i < (int)stats.size() - 1; ++i) {
		if (stats[i] < 0) {
			continue;
		}
		cv::line(last_img_,
				 cv::Point(2 * i, graph_h_ * (1 - stats[i])),
				 cv::Point(2 * (i + 1), graph_h_ * (1 - stats[i + 1])),
				 cv::Scalar((uint8_t)(120 + 60 * stats[i]), 255, 255),
				 2,
				 cv::LINE_AA);
	}

	cv::cvtColor(last_img_, last_img_, cv::COLOR_HSV2BGR);

	for (int i = 0; i <= lines_; ++i) {
		cv::rectangle(last_img_, {0, graph_h_+i*(line_h_ + spacer_)}, {last_img_.cols-1, (graph_h_ + spacer_)+i * (line_h_ + spacer_)}, {128, 128, 128}, -1);
	}

	cv::putText(last_img_, "Sun energy: " + std::to_string(w_.sun_.current_sun_energy()),
			cv::Point(0, 32), cv::FONT_HERSHEY_COMPLEX, 1, {255, 255, 255}, 1, cv::LINE_AA);

	cv::putText(last_img_, "Step: " + std::to_string(w_.step_),
			cv::Point(0, 64), cv::FONT_HERSHEY_COMPLEX, 1, {255, 255, 255}, 1, cv::LINE_AA);

	cv::putText(last_img_, "Trees alive: " + std::to_string(w_.trees_.size()),
			cv::Point(0, 96), cv::FONT_HERSHEY_COMPLEX, 1, {255, 255, 255}, 1, cv::LINE_AA);

	return last_img_;
}

cv::Size World_Img::get_size() const {
	return cv::Size(W, H);
}
