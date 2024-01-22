#ifndef BOARD_BUILDER_H
#define BOARD_BUILDER_H

#include <opencv2/opencv.hpp>
#include <string>

#include "board.h"

class BoardBuilder {
public:
	static Board constructBoard(std::string input_img, std::string part_path);
};

#endif