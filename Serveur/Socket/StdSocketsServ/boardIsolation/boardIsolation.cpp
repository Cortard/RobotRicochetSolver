#include "boardIsolation.h"

int BoardIsolation::getBoard(std::string src_img_path, std::string output_img_path) {
	// -- Scale image --
	cv::Mat src_img = cv::imread(src_img_path);
	cv::Mat scaled_img;
	float scale_factor = 600.0 / src_img.cols;
	cv::resize(src_img, scaled_img, cv::Size(), scale_factor, scale_factor, cv::INTER_LINEAR);

	// -- Adptative threshold --
	cv::Mat gray;
	cv::cvtColor(scaled_img, gray, cv::COLOR_BGR2GRAY);
	cv::Mat denoise;
	cv::fastNlMeansDenoising(gray, denoise, 20);

	cv::Mat thresh;
	cv::adaptiveThreshold(denoise, thresh, 255, cv::ADAPTIVE_THRESH_MEAN_C, cv::THRESH_BINARY_INV, 25, 20);

	// -- Canny --
	cv::Mat canny;
	cv::Canny(thresh, canny, 1, 4);

	// -- Contours finding --
	std::vector<std::vector<cv::Point>> contours;
	std::vector<cv::Vec4i> hierarchy;
	cv::findContours(canny, contours, hierarchy, cv::RETR_TREE, cv::CHAIN_APPROX_SIMPLE);
    cv::drawContours(scaled_img, contours, -1, cv::Scalar(0, 0, 255), 2,8);
    cv::imshow("contours",scaled_img);

	// -- Find biggest shape --
	int maxI = 0;
	for (int i = 1; i < contours.size(); i++) {
		if (hierarchy[i][3] < 0) {
			if (cv::contourArea(contours[i]) > cv::contourArea(contours[maxI])) {
				maxI = i;
			}
		}
	}
	std::vector<cv::Point> maxContour = contours[maxI];
    std::cout<<maxContour.size()<<std::endl;

	// -- Simplify biggest contour to square --
	std::vector<cv::Point> squareContour;
    cv::approxPolyDP(maxContour, squareContour, cv::arcLength(maxContour, true) * 0.1, true);
    std::cout<<squareContour.size() << std::endl;

	if (squareContour.size() == 4) { // Check if finded shape is a square
		// -- Get board from finded shape
		cv::Point2f squarePoint[4];
		for (int i = 0; i < 4; i++) {
			squarePoint[i] = cv::Point2f(squareContour[i].x, squareContour[i].y);
		}

		cv::Point2f finalSizePoints[4];
		finalSizePoints[0] = cv::Point(0.0, 0.0);
		finalSizePoints[1] = cv::Point(600.0, 0.0);
		finalSizePoints[2] = cv::Point(600.0, 600.0);
		finalSizePoints[3] = cv::Point(0.0, 600.0);
		cv::Mat perspectiveMat = cv::getPerspectiveTransform(squarePoint, finalSizePoints);

		cv::Mat warped_img;
		cv::warpPerspective(scaled_img, warped_img, perspectiveMat, cv::Size(600, 600));

		cv::imwrite(output_img_path, warped_img);

		return 0;
	}

	return -1;
}