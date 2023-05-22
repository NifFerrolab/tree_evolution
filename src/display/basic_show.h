#ifndef SRC_DISPLAY_ABSTRACT_SHOW_H_
#define SRC_DISPLAY_ABSTRACT_SHOW_H_

#include "world_img.h"


class Show {
public:
	Show(World_Img& img_maker) : img_maker_(img_maker) {};
	virtual ~Show() {};
	virtual void feed_img() = 0;
protected:
	World_Img& img_maker_;
};

#endif /* SRC_DISPLAY_ABSTRACT_SHOW_H_ */
