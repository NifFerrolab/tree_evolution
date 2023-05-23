#ifndef SRC_DISPLAY_WINDOW_OUTPUT_H_
#define SRC_DISPLAY_WINDOW_OUTPUT_H_

#include "basic_output.h"


class Window_Output : public Show {
public:
	Window_Output(World_Img& img_maker, uint w_s);
	void feed_img() override;
private:
	std::string w_name_;
};

#endif /* SRC_DISPLAY_WINDOW_OUTPUT_H_ */
