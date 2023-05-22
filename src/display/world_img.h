#ifndef WORLD_IMG_H_
#define WORLD_IMG_H_

#include "world.h"

#include <opencv2/core.hpp>


class World_Img {
public:
	World_Img(const World& w);
	cv::Mat get_img();
	cv::Size get_size() const;
private:
	const World& w_;
	const int W, H;
	const int resize_;
	const int line_h_;
	cv::Mat last_img_ {};
	int last_step_ { -1 };
};



#endif /* WORLD_IMG_H_ */
