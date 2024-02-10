#ifndef JPEGBUILDER_H
#define JPEGBUILDER_H

#include <opencv2/opencv.hpp>
#include <string>

class JPEGBuilder {
public:
	static void build(char *data, int widht, int height, std::string output);
};

#endif