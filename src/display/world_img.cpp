#include "world_img.h"

#include <opencv2/imgproc.hpp>


static constexpr int img_w = 1920, img_h = 1080;
static constexpr int resize_step = 2;
static constexpr int graph_h_ = 100 / resize_step, spacer_ = 4 / resize_step;
static constexpr int lines_ = 3;

World_Img::World_Img(const World& w) : w_(w), W(img_w), H(img_h), resize_(resize_step),
		line_h_((H / resize_ - graph_h_ - spacer_ * (lines_ + 1)) / lines_) {

}


cv::Mat World_Img::get_img() {
	if (w_.current_step() == last_step_) {
		return last_img_;
    }

	last_step_ = w_.current_step();
	last_img_ = cv::Mat(H / resize_, W / resize_, CV_8UC3, {0, 0, 0});

	for (int i = 0; i < w_.W; ++i) {
		const auto& col = w_.branches_[i];
		const int x = i % (w_.W / lines_);
		const int h_add = graph_h_ + (1 + i * lines_ / w_.W) * (line_h_ + spacer_) - 1;
		for (int j = 0; j < line_h_ && (size_t)j < col.size(); ++j) {
			int y = h_add - j;
			if (auto b_sh = col[j].lock()) {
				last_img_.at<cv::Vec3b>(y, x) = b_sh->get_tree_color();
			}
		}
	}

	for (const auto& sp : w_.seeds_pos_) {
		if (sp.first.y >= line_h_) {
			continue;
		}
		int x_ = w_.to_word_x_(sp.first.x);
		int x = x_ % (w_.W / lines_);
		int y = graph_h_ + (1 + x_ * lines_ / w_.W) * (line_h_ + spacer_) - 1 - sp.first.y;
		last_img_.at<cv::Vec3b>(y, x) = sp.second;
	}

	auto stats = w_.climat_monitor_.get_stats();
	for (int i = 0; i < (int)stats.size(); ++i) {
		last_img_.at<cv::Vec3b>(graph_h_ * (1 - stats[i]), i) = {(uint8_t)(120 + 60 * stats[i]), 255, 255};
	}

	cv::cvtColor(last_img_, last_img_, cv::COLOR_HSV2BGR);

	for (int i = 0; i <= lines_; ++i) {
		cv::rectangle(last_img_, {0, graph_h_+i*(line_h_ + spacer_)}, {last_img_.cols-1, (graph_h_ + spacer_)+i * (line_h_ + spacer_)}, {128, 128, 128}, -1);
	}

	cv::resize(last_img_, last_img_, cv::Size(), resize_, resize_, cv::INTER_NEAREST);

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
