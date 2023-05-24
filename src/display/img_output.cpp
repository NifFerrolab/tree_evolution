#include "img_output.h"

#include <opencv2/imgcodecs.hpp>


Img_Output::Img_Output(World_Img& img_maker, uint w_s) : Show(img_maker), w_name_(std::to_string(w_s) + '_') { }

void Img_Output::feed_img() {
	if (i_ % 100 == 0) {
		cv::imwrite(w_name_ + std::to_string(i_) + ".png", img_maker_.get_img());
	}
	++i_;
}
