#include "window_output.h"

#include <opencv2/highgui.hpp>


Window_Output::Window_Output(World_Img& img_maker, uint w_s) : Show(img_maker), w_name_(std::to_string(w_s)) { }

void Window_Output::feed_img() {
	cv::imshow(w_name_, img_maker_.get_img());
	cv::waitKey(1);
}
