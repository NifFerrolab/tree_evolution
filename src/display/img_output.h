#ifndef SRC_DISPLAY_IMG_OUTPUT_H_
#define SRC_DISPLAY_IMG_OUTPUT_H_

#include "basic_output.h"


class Img_Output : public Show {
public:
	Img_Output(World_Img& img_maker, uint w_s);
	void feed_img() override;
private:
	std::string w_name_;
	uint i_ { 0 };
};

#endif /* SRC_DISPLAY_IMG_OUTPUT_H_ */
