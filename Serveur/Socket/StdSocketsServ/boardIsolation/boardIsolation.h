#ifndef BOARD_ISOLATION_H
#define BOARD_ISOLATION_H

#include <opencv2/opencv.hpp>
#include <vector>
#include <string>

class BoardIsolation {
private:
	BoardIsolation();

public:
	static int getBoard(std::string src_img_path, std::string output_img_path);
};

#endif