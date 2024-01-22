#include "jpegBuilder.h"

void JPEGBuilder::build(char* data, int width, int height, std::string output) {
	cv::Mat img = cv::Mat(width, height, CV_8UC3, (unsigned*)data);
	cv::imwrite(output, img);
}
