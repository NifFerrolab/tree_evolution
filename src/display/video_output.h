#ifndef SRC_DISPLAY_VIDEO_SHOW_H_
#define SRC_DISPLAY_VIDEO_SHOW_H_

#include "basic_show.h"

#include <opencv2/videoio.hpp>


class Video_Output : public Show {
public:
	Video_Output(World_Img& img_maker, uint w_s);
	~Video_Output() override;
	void feed_img() override;
private:
	cv::VideoWriter video_;
};



#endif /* SRC_DISPLAY_VIDEO_SHOW_H_ */
