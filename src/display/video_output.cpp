#include "video_output.h"


Video_Output::Video_Output(World_Img& img_maker, uint w_s) : Show(img_maker) {
	video_ = cv::VideoWriter{std::to_string(w_s) + ".mkv",
		cv::VideoWriter::fourcc('H', '2', '6', '4'), 30, img_maker_.get_size()};
}


Video_Output::~Video_Output() {
	video_.release();
}


void Video_Output::feed_img() {
	video_ << img_maker_.get_img();
}
