#include "boardBuilder.h"

/* Pos
	0	: Top - left
	1	: Top - Right
	2	: Bottom - Left
	3	: Bottom - Right
*/

/* Objectives
	0	: Red - circle
	1	: Red - triangle
	2	: Red - planet
	3	: Red - star

	4	: Green - circle
	5	: Green - triangle
	6	: Green - planet
	7	: Green - star

	8	: Blue - circle
	9	: Blue - triangle
	10	: Blue - planet
	11	: Blue - star

	12	: Yellow - circle
	13	: Yellow - triangle
	14	: Yellow - planet
	15	: Yellow - star

	16	: Multi
*/

void constructPart1(Board* board, int pos);
void constructPart2(Board* board, int pos);
void constructPart3(Board* board, int pos);
void constructPart4(Board* board, int pos);
void constructPart5(Board* board, int pos);
void constructPart6(Board* board, int pos);
void constructPart7(Board* board, int pos);
void constructPart8(Board* board, int pos);
void constructPart9(Board* board, int pos);
void constructPart10(Board* board, int pos);
void constructPart11(Board* board, int pos);
void constructPart12(Board* board, int pos);
void constructPart13(Board* board, int pos);
void constructPart14(Board* board, int pos);
void constructPart15(Board* board, int pos);
void constructPart16(Board* board, int pos);
void constructWalls(Board* board);

int posToId(int x, int y) {
	return x + y * 16;
}

Board BoardBuilder::constructBoard(std::string input_img, std::string part_path) {
	Board board;

	cv::Mat src_img = cv::imread(input_img);
	cv::Mat part_img[16];
	cv::Rect rect;
	cv::Mat cropped;

	for (int i = 0; i < 16; i++) {
		part_img[i] = cv::imread(part_path + "part" + std::to_string(i+1) + ".jpg");
	}

	cv::Ptr<cv::SIFT> detector = cv::SIFT::create();
	cv::Ptr<cv::BFMatcher> BFMatcher = cv::BFMatcher::create();

	int matches_number[16];
	int maxI;

	// -- Board part Top-Left --

	rect = cv::Rect(cv::Point(0, 0), cv::Point(300, 300));
	cropped = src_img(rect);

	std::vector<cv::KeyPoint> keypoints_1;
	cv::Mat descriptors_1;
	detector->detect(cropped, keypoints_1);
	detector->compute(cropped, keypoints_1, descriptors_1);

	for (int i = 0; i < 16; i++) {
		std::vector<cv::KeyPoint> keypoints_tmp;
		cv::Mat descriptors_tmp;
		detector->detect(part_img[i], keypoints_tmp);
		detector->compute(part_img[i], keypoints_tmp, descriptors_tmp);

		std::vector<std::vector<cv::DMatch>> matches;
		BFMatcher->knnMatch(descriptors_1, descriptors_tmp, matches, 2);

		std::vector<cv::DMatch> good_matches;
		for (int j = 0; j < matches.size(); j++) {
			if (matches[j][0].distance < 0.3f * matches[j][1].distance)
				good_matches.push_back(matches[j][0]);
		}

		matches_number[i] = good_matches.size();
	}

	maxI = 0;
	for (int i = 1; i < 16; i++) {
		if (matches_number[maxI] < matches_number[i])
			maxI = i;
	}

	switch (maxI) {
	case 0:
		constructPart1(&board, 0);
		break;
	case 1:
		constructPart2(&board, 0);
		break;
	case 2:
		constructPart3(&board, 0);
		break;
	case 3:
		constructPart4(&board, 0);
		break;
	case 4:
		constructPart5(&board, 0);
		break;
	case 5:
		constructPart6(&board, 0);
		break;
	case 6:
		constructPart7(&board, 0);
		break;
	case 7:
		constructPart8(&board, 0);
		break;
	case 8:
		constructPart9(&board, 0);
		break;
	case 9:
		constructPart10(&board, 0);
		break;
	case 10:
		constructPart11(&board, 0);
		break;
	case 11:
		constructPart12(&board, 0);
		break;
	case 12:
		constructPart13(&board, 0);
		break;
	case 13:
		constructPart14(&board, 0);
		break;
	case 14:
		constructPart15(&board, 0);
		break;
	case 15:
		constructPart16(&board, 0);
		break;
	default:
		break;
	}

	// -- Board part Top-Right --

	rect = cv::Rect(cv::Point(0, 300), cv::Point(300, 600));
	cv::Mat rotation_mat = cv::getRotationMatrix2D(cv::Point2f(150, 150), -90.0, 1.0);
	cv::warpAffine(src_img(rect), cropped, rotation_mat, rect.size());

	std::vector<cv::KeyPoint> keypoints_2;
	cv::Mat descriptors_2;
	detector->detect(cropped, keypoints_2);
	detector->compute(cropped, keypoints_2, descriptors_2);

	for (int i = 0; i < 16; i++) {
		std::vector<cv::KeyPoint> keypoints_tmp;
		cv::Mat descriptors_tmp;
		detector->detect(part_img[i], keypoints_tmp);
		detector->compute(part_img[i], keypoints_tmp, descriptors_tmp);

		std::vector<std::vector<cv::DMatch>> matches;
		BFMatcher->knnMatch(descriptors_2, descriptors_tmp, matches, 2);

		std::vector<cv::DMatch> good_matches;
		for (int j = 0; j < matches.size(); j++) {
			if (matches[j][0].distance < 0.3f * matches[j][1].distance)
				good_matches.push_back(matches[j][0]);
		}

		matches_number[i] = good_matches.size();
	}

	maxI = 0;
	for (int i = 1; i < 16; i++) {
		if (matches_number[maxI] < matches_number[i])
			maxI = i;
	}

	switch (maxI) {
	case 0:
		constructPart1(&board, 1);
		break;
	case 1:
		constructPart2(&board, 1);
		break;
	case 2:
		constructPart3(&board, 1);
		break;
	case 3:
		constructPart4(&board, 1);
		break;
	case 4:
		constructPart5(&board, 1);
		break;
	case 5:
		constructPart6(&board, 1);
		break;
	case 6:
		constructPart7(&board, 1);
		break;
	case 7:
		constructPart8(&board, 1);
		break;
	case 8:
		constructPart9(&board, 1);
		break;
	case 9:
		constructPart10(&board, 1);
		break;
	case 10:
		constructPart11(&board, 1);
		break;
	case 11:
		constructPart12(&board, 1);
		break;
	case 12:
		constructPart13(&board, 1);
		break;
	case 13:
		constructPart14(&board, 1);
		break;
	case 14:
		constructPart15(&board, 1);
		break;
	case 15:
		constructPart16(&board, 1);
		break;
	default:
		break;
	}

	// -- Board part Bottom-Left --

	rect = cv::Rect(cv::Point(300, 0), cv::Point(600, 300));
	rotation_mat = cv::getRotationMatrix2D(cv::Point2f(150, 150), 90.0, 1.0);
	cv::warpAffine(src_img(rect), cropped, rotation_mat, rect.size());

	std::vector<cv::KeyPoint> keypoints_3;
	cv::Mat descriptors_3;
	detector->detect(cropped, keypoints_3);
	detector->compute(cropped, keypoints_3, descriptors_3);

	for (int i = 0; i < 16; i++) {
		std::vector<cv::KeyPoint> keypoints_tmp;
		cv::Mat descriptors_tmp;
		detector->detect(part_img[i], keypoints_tmp);
		detector->compute(part_img[i], keypoints_tmp, descriptors_tmp);

		std::vector<std::vector<cv::DMatch>> matches;
		BFMatcher->knnMatch(descriptors_3, descriptors_tmp, matches, 2);

		std::vector<cv::DMatch> good_matches;
		for (int j = 0; j < matches.size(); j++) {
			if (matches[j][0].distance < 0.3f * matches[j][1].distance)
				good_matches.push_back(matches[j][0]);
		}

		matches_number[i] = good_matches.size();
	}

	maxI = 0;
	for (int i = 1; i < 16; i++) {
		if (matches_number[maxI] < matches_number[i])
			maxI = i;
	}

	switch (maxI) {
	case 0:
		constructPart1(&board, 2);
		break;
	case 1:
		constructPart2(&board, 2);
		break;
	case 2:
		constructPart3(&board, 2);
		break;
	case 3:
		constructPart4(&board, 2);
		break;
	case 4:
		constructPart5(&board, 2);
		break;
	case 5:
		constructPart6(&board, 2);
		break;
	case 6:
		constructPart7(&board, 2);
		break;
	case 7:
		constructPart8(&board, 2);
		break;
	case 8:
		constructPart9(&board, 2);
		break;
	case 9:
		constructPart10(&board, 2);
		break;
	case 10:
		constructPart11(&board, 2);
		break;
	case 11:
		constructPart12(&board, 2);
		break;
	case 12:
		constructPart13(&board, 2);
		break;
	case 13:
		constructPart14(&board, 2);
		break;
	case 14:
		constructPart15(&board, 2);
		break;
	case 15:
		constructPart16(&board, 2);
		break;
	default:
		break;
	}

	// -- Board part Bottom-Right --

	rect = cv::Rect(cv::Point(300, 300), cv::Point(600, 600));
	rotation_mat = cv::getRotationMatrix2D(cv::Point2f(150, 150), 180.0, 1.0);
	cv::warpAffine(src_img(rect), cropped, rotation_mat, rect.size());

	std::vector<cv::KeyPoint> keypoints_4;
	cv::Mat descriptors_4;
	detector->detect(cropped, keypoints_4);
	detector->compute(cropped, keypoints_4, descriptors_4);

	for (int i = 0; i < 16; i++) {
		std::vector<cv::KeyPoint> keypoints_tmp;
		cv::Mat descriptors_tmp;
		detector->detect(part_img[i], keypoints_tmp);
		detector->compute(part_img[i], keypoints_tmp, descriptors_tmp);

		std::vector<std::vector<cv::DMatch>> matches;
		BFMatcher->knnMatch(descriptors_4, descriptors_tmp, matches, 2);

		std::vector<cv::DMatch> good_matches;
		for (int j = 0; j < matches.size(); j++) {
			if (matches[j][0].distance < 0.3f * matches[j][1].distance)
				good_matches.push_back(matches[j][0]);
		}

		matches_number[i] = good_matches.size();
	}

	maxI = 0;
	for (int i = 1; i < 16; i++) {
		if (matches_number[maxI] < matches_number[i])
			maxI = i;
	}

	switch (maxI) {
	case 0:
		constructPart1(&board, 3);
		break;
	case 1:
		constructPart2(&board, 3);
		break;
	case 2:
		constructPart3(&board, 3);
		break;
	case 3:
		constructPart4(&board, 3);
		break;
	case 4:
		constructPart5(&board, 3);
		break;
	case 5:
		constructPart6(&board, 3);
		break;
	case 6:
		constructPart7(&board, 3);
		break;
	case 7:
		constructPart8(&board, 3);
		break;
	case 8:
		constructPart9(&board, 3);
		break;
	case 9:
		constructPart10(&board, 3);
		break;
	case 10:
		constructPart11(&board, 3);
		break;
	case 11:
		constructPart12(&board, 3);
		break;
	case 12:
		constructPart13(&board, 3);
		break;
	case 13:
		constructPart14(&board, 3);
		break;
	case 14:
		constructPart15(&board, 3);
		break;
	case 15:
		constructPart16(&board, 3);
		break;
	default:
		break;
	}

	constructWalls(&board);

	return board;
}

void constructPart1(Board* board, int pos) {
	if (pos == 0) {
		board->objectives[13] = posToId(6, 1);
		board->objectives[3] = posToId(4, 3);
		board->objectives[8] = posToId(1, 5);
		board->objectives[6] = posToId(5, 6);
		board->objectives[16] = posToId(2, 7);

		ADD_WALL(board->cases[posToId(3, 0)], EAST);
		ADD_WALL(board->cases[posToId(4, 0)], WEST);
		ADD_WALL(board->cases[posToId(5, 1)], EAST);
		ADD_WALL(board->cases[posToId(6, 1)], WEST);
		ADD_WALL(board->cases[posToId(6, 1)], SOUTH);
		ADD_WALL(board->cases[posToId(0, 2)], SOUTH);
		ADD_WALL(board->cases[posToId(6, 2)], NORTH);
		ADD_WALL(board->cases[posToId(0, 3)], NORTH);
		ADD_WALL(board->cases[posToId(4, 3)], EAST);
		ADD_WALL(board->cases[posToId(5, 3)], WEST);
		ADD_WALL(board->cases[posToId(4, 3)], SOUTH);
		ADD_WALL(board->cases[posToId(1, 4)], SOUTH);
		ADD_WALL(board->cases[posToId(4, 4)], NORTH);
		ADD_WALL(board->cases[posToId(1, 5)], NORTH);
		ADD_WALL(board->cases[posToId(1, 5)], EAST);
		ADD_WALL(board->cases[posToId(2, 5)], WEST);
		ADD_WALL(board->cases[posToId(5, 5)], SOUTH);
		ADD_WALL(board->cases[posToId(4, 6)], EAST);
		ADD_WALL(board->cases[posToId(5, 6)], WEST);
		ADD_WALL(board->cases[posToId(5, 6)], NORTH);
		ADD_WALL(board->cases[posToId(7, 6)], SOUTH);
		ADD_WALL(board->cases[posToId(2, 7)], SOUTH);
		ADD_WALL(board->cases[posToId(2, 7)], EAST);
		ADD_WALL(board->cases[posToId(3, 7)], WEST);
		ADD_WALL(board->cases[posToId(6, 7)], EAST);

		return;
	}

	if (pos == 1) {
		board->objectives[13] = posToId(14, 6);
		board->objectives[3] = posToId(12, 4);
		board->objectives[8] = posToId(10, 1);
		board->objectives[6] = posToId(9, 5);
		board->objectives[16] = posToId(8, 2);

		ADD_WALL(board->cases[posToId(12, 0)], EAST);
		ADD_WALL(board->cases[posToId(13, 0)], WEST);
		ADD_WALL(board->cases[posToId(10, 1)], EAST);
		ADD_WALL(board->cases[posToId(10, 1)], SOUTH);
		ADD_WALL(board->cases[posToId(11, 1)], WEST);
		ADD_WALL(board->cases[posToId(8, 2)], WEST);
		ADD_WALL(board->cases[posToId(8, 2)], SOUTH);
		ADD_WALL(board->cases[posToId(10, 2)], NORTH);
		ADD_WALL(board->cases[posToId(8, 3)], NORTH);
		ADD_WALL(board->cases[posToId(15, 3)], SOUTH);
		ADD_WALL(board->cases[posToId(9, 4)], SOUTH);
		ADD_WALL(board->cases[posToId(11, 4)], EAST);
		ADD_WALL(board->cases[posToId(12, 4)], SOUTH);
		ADD_WALL(board->cases[posToId(12, 4)], WEST);
		ADD_WALL(board->cases[posToId(15, 4)], NORTH);
		ADD_WALL(board->cases[posToId(9, 5)], NORTH);
		ADD_WALL(board->cases[posToId(9, 5)], EAST);
		ADD_WALL(board->cases[posToId(10, 5)], WEST);
		ADD_WALL(board->cases[posToId(12, 5)], NORTH);
		ADD_WALL(board->cases[posToId(14, 5)], SOUTH);
		ADD_WALL(board->cases[posToId(8, 6)], SOUTH);
		ADD_WALL(board->cases[posToId(13, 6)], EAST);
		ADD_WALL(board->cases[posToId(14, 6)], WEST);
		ADD_WALL(board->cases[posToId(14, 6)], NORTH);
		ADD_WALL(board->cases[posToId(9, 7)], WEST);

		return;
	}

	if (pos == 2) {
		board->objectives[13] = posToId(2, 9);
		board->objectives[3] = posToId(3, 11);
		board->objectives[8] = posToId(5, 14);
		board->objectives[6] = posToId(6, 10);
		board->objectives[16] = posToId(13, 2);

		ADD_WALL(board->cases[posToId(6, 8)], EAST);
		ADD_WALL(board->cases[posToId(1, 9)], SOUTH);
		ADD_WALL(board->cases[posToId(1, 9)], EAST);
		ADD_WALL(board->cases[posToId(2, 9)], WEST);
		ADD_WALL(board->cases[posToId(7, 9)], NORTH);
		ADD_WALL(board->cases[posToId(1, 10)], NORTH);
		ADD_WALL(board->cases[posToId(3, 10)], SOUTH);
		ADD_WALL(board->cases[posToId(5, 10)], EAST);
		ADD_WALL(board->cases[posToId(6, 10)], WEST);
		ADD_WALL(board->cases[posToId(6, 10)], SOUTH);
		ADD_WALL(board->cases[posToId(0, 11)], SOUTH);
		ADD_WALL(board->cases[posToId(3, 11)], NORTH);
		ADD_WALL(board->cases[posToId(3, 11)], EAST);
		ADD_WALL(board->cases[posToId(4, 11)], WEST);
		ADD_WALL(board->cases[posToId(6, 11)], NORTH);
		ADD_WALL(board->cases[posToId(0, 12)], NORTH);
		ADD_WALL(board->cases[posToId(7, 12)], SOUTH);
		ADD_WALL(board->cases[posToId(5, 13)], SOUTH);
		ADD_WALL(board->cases[posToId(7, 13)], NORTH);
		ADD_WALL(board->cases[posToId(7, 13)], EAST);
		ADD_WALL(board->cases[posToId(4, 14)], EAST);
		ADD_WALL(board->cases[posToId(5, 14)], WEST);
		ADD_WALL(board->cases[posToId(5, 14)], NORTH);
		ADD_WALL(board->cases[posToId(2, 15)], EAST);
		ADD_WALL(board->cases[posToId(3, 15)], WEST);

		return;
	}

	if (pos == 3) {
		board->objectives[13] = posToId(9, 15);
		board->objectives[3] = posToId(11, 12);
		board->objectives[8] = posToId(14, 10);
		board->objectives[6] = posToId(10, 9);
		board->objectives[16] = posToId(13, 8);

		ADD_WALL(board->cases[posToId(9, 8)], WEST);
		ADD_WALL(board->cases[posToId(12, 8)], EAST);
		ADD_WALL(board->cases[posToId(13, 8)], WEST);
		ADD_WALL(board->cases[posToId(13, 8)], NORTH);
		ADD_WALL(board->cases[posToId(8, 9)], SOUTH);
		ADD_WALL(board->cases[posToId(10, 9)], EAST);
		ADD_WALL(board->cases[posToId(10, 9)], SOUTH);
		ADD_WALL(board->cases[posToId(11, 9)], WEST);
		ADD_WALL(board->cases[posToId(10, 10)], NORTH);
		ADD_WALL(board->cases[posToId(13, 10)], EAST);
		ADD_WALL(board->cases[posToId(14, 10)], WEST);
		ADD_WALL(board->cases[posToId(14, 10)], SOUTH);
		ADD_WALL(board->cases[posToId(11, 11)], SOUTH);
		ADD_WALL(board->cases[posToId(14, 11)], NORTH);
		ADD_WALL(board->cases[posToId(10, 12)], EAST);
		ADD_WALL(board->cases[posToId(11, 12)], WEST);
		ADD_WALL(board->cases[posToId(11, 12)], NORTH);
		ADD_WALL(board->cases[posToId(15, 12)], SOUTH);
		ADD_WALL(board->cases[posToId(9, 13)], SOUTH);
		ADD_WALL(board->cases[posToId(15, 13)], NORTH);
		ADD_WALL(board->cases[posToId(9, 14)], NORTH);
		ADD_WALL(board->cases[posToId(9, 14)], EAST);
		ADD_WALL(board->cases[posToId(10, 14)], WEST);
		ADD_WALL(board->cases[posToId(11, 15)], EAST);
		ADD_WALL(board->cases[posToId(12, 15)], WEST);

		return;
	}
}

void constructPart2(Board* board, int pos) {
	if (pos == 0) {
		board->objectives[2] = posToId(2, 1);
		board->objectives[9] = posToId(6, 2);
		board->objectives[7] = posToId(1, 5);
		board->objectives[12] = posToId(4, 6);

		ADD_WALL(board->cases[posToId(2, 0)], SOUTH);
		ADD_WALL(board->cases[posToId(3, 0)], EAST);
		ADD_WALL(board->cases[posToId(4, 0)], WEST);
		ADD_WALL(board->cases[posToId(2, 1)], NORTH);
		ADD_WALL(board->cases[posToId(2, 1)], EAST);
		ADD_WALL(board->cases[posToId(3, 1)], WEST);
		ADD_WALL(board->cases[posToId(5, 2)], EAST);
		ADD_WALL(board->cases[posToId(6, 2)], WEST);
		ADD_WALL(board->cases[posToId(6, 2)], SOUTH);
		ADD_WALL(board->cases[posToId(0, 3)], SOUTH);
		ADD_WALL(board->cases[posToId(0, 4)], NORTH);
		ADD_WALL(board->cases[posToId(1, 5)], SOUTH);
		ADD_WALL(board->cases[posToId(1, 5)], EAST);
		ADD_WALL(board->cases[posToId(2, 5)], WEST);
		ADD_WALL(board->cases[posToId(4, 5)], SOUTH);
		ADD_WALL(board->cases[posToId(1, 6)], NORTH);
		ADD_WALL(board->cases[posToId(3, 6)], EAST);
		ADD_WALL(board->cases[posToId(4, 6)], WEST);
		ADD_WALL(board->cases[posToId(4, 6)], NORTH);
		ADD_WALL(board->cases[posToId(7, 6)], SOUTH);
		ADD_WALL(board->cases[posToId(6, 7)], EAST);

		return;
	}

	if (pos == 1) {
		board->objectives[2] = posToId(14, 2);
		board->objectives[9] = posToId(13, 6);
		board->objectives[7] = posToId(10, 1);
		board->objectives[12] = posToId(9, 4);

		ADD_WALL(board->cases[posToId(11, 0)], WEST);
		ADD_WALL(board->cases[posToId(12, 0)], EAST);
		ADD_WALL(board->cases[posToId(9, 1)], EAST);
		ADD_WALL(board->cases[posToId(10, 1)], WEST);
		ADD_WALL(board->cases[posToId(10, 1)], SOUTH);
		ADD_WALL(board->cases[posToId(10, 2)], NORTH);
		ADD_WALL(board->cases[posToId(14, 2)], SOUTH);
		ADD_WALL(board->cases[posToId(14, 2)], EAST);
		ADD_WALL(board->cases[posToId(15, 2)], WEST);
		ADD_WALL(board->cases[posToId(10, 3)], SOUTH);
		ADD_WALL(board->cases[posToId(15, 3)], SOUTH);
		ADD_WALL(board->cases[posToId(10, 4)], NORTH);
		ADD_WALL(board->cases[posToId(10, 4)], EAST);
		ADD_WALL(board->cases[posToId(11, 4)], WEST);
		ADD_WALL(board->cases[posToId(15, 4)], NORTH);
		ADD_WALL(board->cases[posToId(13, 5)], SOUTH);
		ADD_WALL(board->cases[posToId(8, 6)], SOUTH);
		ADD_WALL(board->cases[posToId(12, 6)], EAST);
		ADD_WALL(board->cases[posToId(13, 6)], WEST);
		ADD_WALL(board->cases[posToId(13, 6)], NORTH);
		ADD_WALL(board->cases[posToId(9, 7)], WEST);

		return;
	}

	if (pos == 2) {
		board->objectives[2] = posToId(1, 13);
		board->objectives[9] = posToId(2, 9);
		board->objectives[7] = posToId(10, 1);
		board->objectives[12] = posToId(5, 14);

		ADD_WALL(board->cases[posToId(6, 8)], EAST);
		ADD_WALL(board->cases[posToId(2, 9)], SOUTH);
		ADD_WALL(board->cases[posToId(2, 9)], EAST);
		ADD_WALL(board->cases[posToId(3, 9)], WEST);
		ADD_WALL(board->cases[posToId(7, 9)], NORTH);
		ADD_WALL(board->cases[posToId(2, 10)], NORTH);
		ADD_WALL(board->cases[posToId(0, 11)], SOUTH);
		ADD_WALL(board->cases[posToId(5, 11)], EAST);
		ADD_WALL(board->cases[posToId(6, 11)], WEST);
		ADD_WALL(board->cases[posToId(6, 11)], SOUTH);
		ADD_WALL(board->cases[posToId(0, 12)], NORTH);
		ADD_WALL(board->cases[posToId(1, 12)], SOUTH);
		ADD_WALL(board->cases[posToId(6, 12)], NORTH);
		ADD_WALL(board->cases[posToId(0, 13)], EAST);
		ADD_WALL(board->cases[posToId(1, 13)], WEST);
		ADD_WALL(board->cases[posToId(1, 13)], NORTH);
		ADD_WALL(board->cases[posToId(5, 13)], SOUTH);
		ADD_WALL(board->cases[posToId(5, 14)], NORTH);
		ADD_WALL(board->cases[posToId(5, 14)], EAST);
		ADD_WALL(board->cases[posToId(6, 14)], WEST);
		ADD_WALL(board->cases[posToId(3, 15)], EAST);
		ADD_WALL(board->cases[posToId(4, 15)], WEST);

		return;
	}

	if (pos == 3) {
		board->objectives[2] = posToId(13, 14);
		board->objectives[9] = posToId(9, 13);
		board->objectives[7] = posToId(14, 10);
		board->objectives[12] = posToId(11, 9);

		ADD_WALL(board->cases[posToId(9, 8)], WEST);
		ADD_WALL(board->cases[posToId(8, 9)], NORTH);
		ADD_WALL(board->cases[posToId(11, 9)], SOUTH);
		ADD_WALL(board->cases[posToId(11, 9)], EAST);
		ADD_WALL(board->cases[posToId(12, 9)], WEST);
		ADD_WALL(board->cases[posToId(14, 9)], SOUTH);
		ADD_WALL(board->cases[posToId(11, 10)], NORTH);
		ADD_WALL(board->cases[posToId(13, 10)], EAST);
		ADD_WALL(board->cases[posToId(14, 10)], WEST);
		ADD_WALL(board->cases[posToId(14, 10)], NORTH);
		ADD_WALL(board->cases[posToId(15, 11)], SOUTH);
		ADD_WALL(board->cases[posToId(9, 12)], SOUTH);
		ADD_WALL(board->cases[posToId(15, 12)], NORTH);
		ADD_WALL(board->cases[posToId(9, 13)], NORTH);
		ADD_WALL(board->cases[posToId(9, 13)], EAST);
		ADD_WALL(board->cases[posToId(10, 13)], WEST);
		ADD_WALL(board->cases[posToId(12, 14)], EAST);
		ADD_WALL(board->cases[posToId(13, 14)], WEST);
		ADD_WALL(board->cases[posToId(13, 14)], SOUTH);
		ADD_WALL(board->cases[posToId(11, 15)], EAST);
		ADD_WALL(board->cases[posToId(12, 15)], WEST);

		return;
	}
}

void constructPart3(Board* board, int pos) {
	if (pos == 0) {
		board->objectives[13] = posToId(3, 1);
		board->objectives[3] = posToId(5, 2);
		board->objectives[6] = posToId(4, 5);
		board->objectives[8] = posToId(1, 6);
		board->objectives[16] = posToId(5, 7);

		ADD_WALL(board->cases[posToId(6, 0)], EAST);
		ADD_WALL(board->cases[posToId(7, 0)], WEST);
		ADD_WALL(board->cases[posToId(2, 1)], EAST);
		ADD_WALL(board->cases[posToId(3, 1)], WEST);
		ADD_WALL(board->cases[posToId(3, 1)], SOUTH);
		ADD_WALL(board->cases[posToId(5, 2)], SOUTH);
		ADD_WALL(board->cases[posToId(5, 2)], EAST);
		ADD_WALL(board->cases[posToId(6, 2)], WEST);
		ADD_WALL(board->cases[posToId(0, 3)], SOUTH);
		ADD_WALL(board->cases[posToId(0, 4)], NORTH);
		ADD_WALL(board->cases[posToId(4, 4)], SOUTH);
		ADD_WALL(board->cases[posToId(1, 5)], SOUTH);
		ADD_WALL(board->cases[posToId(3, 5)], EAST);
		ADD_WALL(board->cases[posToId(4, 5)], WEST);
		ADD_WALL(board->cases[posToId(4, 5)], NORTH);
		ADD_WALL(board->cases[posToId(1, 6)], NORTH);
		ADD_WALL(board->cases[posToId(1, 6)], EAST);
		ADD_WALL(board->cases[posToId(2, 6)], WEST);
		ADD_WALL(board->cases[posToId(7, 6)], SOUTH);
		ADD_WALL(board->cases[posToId(5, 7)], SOUTH);
		ADD_WALL(board->cases[posToId(5, 7)], EAST);
		ADD_WALL(board->cases[posToId(6, 7)], WEST);
		ADD_WALL(board->cases[posToId(6, 7)], EAST);

		return;
	}

	if (pos == 1) {
		board->objectives[13] = posToId(6, 3);
		board->objectives[3] = posToId(14, 13);
		board->objectives[6] = posToId(10, 4);
		board->objectives[8] = posToId(9, 1);
		board->objectives[16] = posToId(8, 13);

		ADD_WALL(board->cases[posToId(11, 0)], EAST);
		ADD_WALL(board->cases[posToId(12, 0)], WEST);
		ADD_WALL(board->cases[posToId(9, 1)], SOUTH);
		ADD_WALL(board->cases[posToId(9, 1)], EAST);
		ADD_WALL(board->cases[posToId(10, 1)], WEST);
		ADD_WALL(board->cases[posToId(9, 2)], NORTH);
		ADD_WALL(board->cases[posToId(14, 2)], SOUTH);
		ADD_WALL(board->cases[posToId(11, 3)], SOUTH);
		ADD_WALL(board->cases[posToId(14, 3)], EAST);
		ADD_WALL(board->cases[posToId(15, 3)], WEST);
		ADD_WALL(board->cases[posToId(15, 3)], NORTH);
		ADD_WALL(board->cases[posToId(10, 4)], NORTH);
		ADD_WALL(board->cases[posToId(10, 4)], EAST);
		ADD_WALL(board->cases[posToId(11, 4)], WEST);
		ADD_WALL(board->cases[posToId(8, 5)], WEST);
		ADD_WALL(board->cases[posToId(8, 5)], SOUTH);
		ADD_WALL(board->cases[posToId(12, 5)], EAST);
		ADD_WALL(board->cases[posToId(13, 5)], WEST);
		ADD_WALL(board->cases[posToId(13, 5)], SOUTH);
		ADD_WALL(board->cases[posToId(8, 6)], NORTH);
		ADD_WALL(board->cases[posToId(8, 6)], SOUTH);
		ADD_WALL(board->cases[posToId(15, 6)], SOUTH);
		ADD_WALL(board->cases[posToId(9, 7)], WEST);
		ADD_WALL(board->cases[posToId(15, 7)], NORTH);

		return;
	}

	if (pos == 2) {
		board->objectives[13] = posToId(1, 12);
		board->objectives[3] = posToId(2, 10);
		board->objectives[6] = posToId(5, 11);
		board->objectives[8] = posToId(6, 14);
		board->objectives[16] = posToId(7, 10);

		ADD_WALL(board->cases[posToId(0, 8)], SOUTH);
		ADD_WALL(board->cases[posToId(6, 8)], EAST);
		ADD_WALL(board->cases[posToId(0, 9)], NORTH);
		ADD_WALL(board->cases[posToId(2, 9)], SOUTH);
		ADD_WALL(board->cases[posToId(7, 9)], NORTH);
		ADD_WALL(board->cases[posToId(7, 9)], SOUTH);
		ADD_WALL(board->cases[posToId(2, 10)], NORTH);
		ADD_WALL(board->cases[posToId(2, 10)], EAST);
		ADD_WALL(board->cases[posToId(3, 10)], WEST);
		ADD_WALL(board->cases[posToId(7, 10)], NORTH);
		ADD_WALL(board->cases[posToId(7, 10)], EAST);
		ADD_WALL(board->cases[posToId(4, 11)], EAST);
		ADD_WALL(board->cases[posToId(5, 11)], WEST);
		ADD_WALL(board->cases[posToId(5, 11)], SOUTH);
		ADD_WALL(board->cases[posToId(1, 12)], SOUTH);
		ADD_WALL(board->cases[posToId(1, 12)], EAST);
		ADD_WALL(board->cases[posToId(2, 12)], WEST);
		ADD_WALL(board->cases[posToId(5, 12)], NORTH);
		ADD_WALL(board->cases[posToId(1, 13)], NORTH);
		ADD_WALL(board->cases[posToId(6, 13)], SOUTH);
		ADD_WALL(board->cases[posToId(5, 14)], EAST);
		ADD_WALL(board->cases[posToId(6, 14)], WEST);
		ADD_WALL(board->cases[posToId(6, 14)], NORTH);
		ADD_WALL(board->cases[posToId(3, 15)], EAST);
		ADD_WALL(board->cases[posToId(4, 15)], WEST);

		return;
	}

	if (pos == 3) {
		board->objectives[13] = posToId(12, 14);
		board->objectives[3] = posToId(10, 13);
		board->objectives[6] = posToId(11, 10);
		board->objectives[8] = posToId(14, 9);
		board->objectives[16] = posToId(10, 8);

		ADD_WALL(board->cases[posToId(9, 8)], WEST);
		ADD_WALL(board->cases[posToId(9, 8)], EAST);
		ADD_WALL(board->cases[posToId(10, 8)], WEST);
		ADD_WALL(board->cases[posToId(10, 8)], NORTH);
		ADD_WALL(board->cases[posToId(8, 9)], NORTH);
		ADD_WALL(board->cases[posToId(13, 9)], EAST);
		ADD_WALL(board->cases[posToId(14, 9)], WEST);
		ADD_WALL(board->cases[posToId(14, 9)], SOUTH);
		ADD_WALL(board->cases[posToId(11, 10)], SOUTH);
		ADD_WALL(board->cases[posToId(11, 10)], EAST);
		ADD_WALL(board->cases[posToId(12, 10)], WEST);
		ADD_WALL(board->cases[posToId(14, 10)], NORTH);
		ADD_WALL(board->cases[posToId(11, 11)], NORTH);
		ADD_WALL(board->cases[posToId(15, 11)], SOUTH);
		ADD_WALL(board->cases[posToId(10, 12)], SOUTH);
		ADD_WALL(board->cases[posToId(15, 12)], NORTH);
		ADD_WALL(board->cases[posToId(9, 13)], EAST);
		ADD_WALL(board->cases[posToId(10, 13)], WEST);
		ADD_WALL(board->cases[posToId(10, 13)], NORTH);
		ADD_WALL(board->cases[posToId(12, 13)], SOUTH);
		ADD_WALL(board->cases[posToId(12, 14)], NORTH);
		ADD_WALL(board->cases[posToId(12, 14)], EAST);
		ADD_WALL(board->cases[posToId(13, 14)], WEST);
		ADD_WALL(board->cases[posToId(8, 15)], EAST);
		ADD_WALL(board->cases[posToId(9, 15)], WEST);

		return;
	}
}

void constructPart4(Board* board, int pos) {
	if (pos == 0) {
		board->objectives[1] = posToId(1, 1);
		board->objectives[11] = posToId(4, 2);
		board->objectives[4] = posToId(2, 6);
		board->objectives[14] = posToId(5, 7);

		ADD_WALL(board->cases[posToId(1, 0)], SOUTH);
		ADD_WALL(board->cases[posToId(5, 0)], EAST);
		ADD_WALL(board->cases[posToId(6, 0)], WEST);
		ADD_WALL(board->cases[posToId(1, 1)], NORTH);
		ADD_WALL(board->cases[posToId(1, 1)], EAST);
		ADD_WALL(board->cases[posToId(6, 1)], WEST);
		ADD_WALL(board->cases[posToId(4, 2)], SOUTH);
		ADD_WALL(board->cases[posToId(4, 2)], EAST);
		ADD_WALL(board->cases[posToId(5, 2)], WEST);
		ADD_WALL(board->cases[posToId(0, 3)], SOUTH);
		ADD_WALL(board->cases[posToId(4, 3)], NORTH);
		ADD_WALL(board->cases[posToId(0, 4)], NORTH);
		ADD_WALL(board->cases[posToId(1, 6)], EAST);
		ADD_WALL(board->cases[posToId(2, 6)], WEST);
		ADD_WALL(board->cases[posToId(2, 6)], SOUTH);
		ADD_WALL(board->cases[posToId(5, 6)], SOUTH);
		ADD_WALL(board->cases[posToId(7, 6)], SOUTH);
		ADD_WALL(board->cases[posToId(2, 7)], NORTH);
		ADD_WALL(board->cases[posToId(4, 7)], EAST);
		ADD_WALL(board->cases[posToId(5, 7)], WEST);
		ADD_WALL(board->cases[posToId(5, 7)], NORTH);
		ADD_WALL(board->cases[posToId(6, 7)], EAST);

		return;
	}

	if (pos == 1) {
		board->objectives[1] = posToId(14, 1);
		board->objectives[11] = posToId(13, 4);
		board->objectives[4] = posToId(9, 2);
		board->objectives[14] = posToId(8, 5);

		ADD_WALL(board->cases[posToId(11, 0)], EAST);
		ADD_WALL(board->cases[posToId(12, 0)], WEST);
		ADD_WALL(board->cases[posToId(9, 1)], SOUTH);
		ADD_WALL(board->cases[posToId(14, 1)], SOUTH);
		ADD_WALL(board->cases[posToId(14, 1)], EAST);
		ADD_WALL(board->cases[posToId(15, 1)], WEST);
		ADD_WALL(board->cases[posToId(8, 2)], EAST);
		ADD_WALL(board->cases[posToId(9, 2)], WEST);
		ADD_WALL(board->cases[posToId(9, 2)], NORTH);
		ADD_WALL(board->cases[posToId(14, 2)], NORTH);
		ADD_WALL(board->cases[posToId(8, 4)], SOUTH);
		ADD_WALL(board->cases[posToId(12, 4)], EAST);
		ADD_WALL(board->cases[posToId(13, 4)], WEST);
		ADD_WALL(board->cases[posToId(13, 4)], SOUTH);
		ADD_WALL(board->cases[posToId(8, 5)], NORTH);
		ADD_WALL(board->cases[posToId(8, 5)], EAST);
		ADD_WALL(board->cases[posToId(9, 5)], WEST);
		ADD_WALL(board->cases[posToId(13, 5)], NORTH);
		ADD_WALL(board->cases[posToId(15, 5)], SOUTH);
		ADD_WALL(board->cases[posToId(8, 6)], SOUTH);
		ADD_WALL(board->cases[posToId(15, 6)], NORTH);
		ADD_WALL(board->cases[posToId(9, 7)], WEST);

		return;
	}

	if (pos == 2) {
		board->objectives[1] = posToId(1, 15);
		board->objectives[11] = posToId(2, 11);
		board->objectives[4] = posToId(6, 13);
		board->objectives[14] = posToId(7, 10);

		ADD_WALL(board->cases[posToId(6, 8)], EAST);
		ADD_WALL(board->cases[posToId(0, 9)], SOUTH);
		ADD_WALL(board->cases[posToId(7, 9)], NORTH);
		ADD_WALL(board->cases[posToId(0, 10)], NORTH);
		ADD_WALL(board->cases[posToId(2, 10)], SOUTH);
		ADD_WALL(board->cases[posToId(6, 10)], EAST);
		ADD_WALL(board->cases[posToId(7, 10)], WEST);
		ADD_WALL(board->cases[posToId(7, 10)], SOUTH);
		ADD_WALL(board->cases[posToId(2, 11)], NORTH);
		ADD_WALL(board->cases[posToId(2, 11)], EAST);
		ADD_WALL(board->cases[posToId(3, 11)], WEST);
		ADD_WALL(board->cases[posToId(7, 11)], NORTH);
		ADD_WALL(board->cases[posToId(2, 13)], SOUTH);
		ADD_WALL(board->cases[posToId(6, 13)], SOUTH);
		ADD_WALL(board->cases[posToId(6, 13)], EAST);
		ADD_WALL(board->cases[posToId(7, 13)], WEST);
		ADD_WALL(board->cases[posToId(0, 14)], EAST);
		ADD_WALL(board->cases[posToId(1, 14)], WEST);
		ADD_WALL(board->cases[posToId(1, 14)], NORTH);
		ADD_WALL(board->cases[posToId(6, 14)], NORTH);
		ADD_WALL(board->cases[posToId(3, 15)], EAST);
		ADD_WALL(board->cases[posToId(4, 15)], WEST);

		return;
	}

	if (pos == 3) {
		board->objectives[1] = posToId(14, 14);
		board->objectives[11] = posToId(11, 13);
		board->objectives[4] = posToId(13, 9);
		board->objectives[14] = posToId(10, 8);

		ADD_WALL(board->cases[posToId(9, 8)], EAST);
		ADD_WALL(board->cases[posToId(10, 8)], EAST);
		ADD_WALL(board->cases[posToId(10, 8)], SOUTH);
		ADD_WALL(board->cases[posToId(11, 8)], WEST);
		ADD_WALL(board->cases[posToId(13, 8)], SOUTH);
		ADD_WALL(board->cases[posToId(8, 9)], NORTH);
		ADD_WALL(board->cases[posToId(10, 9)], NORTH);
		ADD_WALL(board->cases[posToId(13, 9)], NORTH);
		ADD_WALL(board->cases[posToId(13, 9)], EAST);
		ADD_WALL(board->cases[posToId(14, 9)], WEST);
		ADD_WALL(board->cases[posToId(15, 11)], SOUTH);
		ADD_WALL(board->cases[posToId(11, 12)], SOUTH);
		ADD_WALL(board->cases[posToId(15, 12)], NORTH);
		ADD_WALL(board->cases[posToId(10, 13)], EAST);
		ADD_WALL(board->cases[posToId(11, 13)], WEST);
		ADD_WALL(board->cases[posToId(11, 13)], NORTH);
		ADD_WALL(board->cases[posToId(13, 14)], EAST);
		ADD_WALL(board->cases[posToId(14, 14)], WEST);
		ADD_WALL(board->cases[posToId(14, 14)], SOUTH);
		ADD_WALL(board->cases[posToId(9, 15)], EAST);
		ADD_WALL(board->cases[posToId(10, 15)], WEST);

		return;
	}
}

void constructPart5(Board* board, int pos) {
	if (pos == 0) {
		board->objectives[3] = posToId(5, 1);
		board->objectives[8] = posToId(3, 2);
		board->objectives[6] = posToId(3, 3);
		board->objectives[16] = posToId(7, 5);
		board->objectives[13] = posToId(2, 6);

		ADD_WALL(board->cases[posToId(6, 0)], EAST);
		ADD_WALL(board->cases[posToId(7, 0)], WEST);
		ADD_WALL(board->cases[posToId(5, 1)], SOUTH);
		ADD_WALL(board->cases[posToId(5, 1)], EAST);
		ADD_WALL(board->cases[posToId(6, 1)], WEST);
		ADD_WALL(board->cases[posToId(2, 2)], EAST);
		ADD_WALL(board->cases[posToId(3, 2)], WEST);
		ADD_WALL(board->cases[posToId(3, 2)], SOUTH);
		ADD_WALL(board->cases[posToId(5, 2)], NORTH);
		ADD_WALL(board->cases[posToId(3, 3)], NORTH);
		ADD_WALL(board->cases[posToId(3, 3)], EAST);
		ADD_WALL(board->cases[posToId(4, 3)], WEST);
		ADD_WALL(board->cases[posToId(0, 4)], SOUTH);
		ADD_WALL(board->cases[posToId(0, 5)], NORTH);
		ADD_WALL(board->cases[posToId(2, 5)], SOUTH);
		ADD_WALL(board->cases[posToId(7, 5)], SOUTH);
		ADD_WALL(board->cases[posToId(7, 5)], EAST);
		ADD_WALL(board->cases[posToId(1, 6)], EAST);
		ADD_WALL(board->cases[posToId(2, 6)], WEST);
		ADD_WALL(board->cases[posToId(2, 6)], NORTH);
		ADD_WALL(board->cases[posToId(7, 6)], NORTH);
		ADD_WALL(board->cases[posToId(7, 6)], SOUTH);
		ADD_WALL(board->cases[posToId(6, 7)], EAST);

		return;
	}

	if (pos == 1) {
		board->objectives[13] = posToId(9, 2);
		board->objectives[6] = posToId(12, 3);
		board->objectives[8] = posToId(13, 3);
		board->objectives[3] = posToId(14, 5);
		board->objectives[16] = posToId(10, 7);

		ADD_WALL(board->cases[posToId(10, 0)], EAST);
		ADD_WALL(board->cases[posToId(11, 0)], WEST);
		ADD_WALL(board->cases[posToId(9, 1)], SOUTH);
		ADD_WALL(board->cases[posToId(9, 2)], NORTH);
		ADD_WALL(board->cases[posToId(9, 2)], EAST);
		ADD_WALL(board->cases[posToId(10, 2)], WEST);
		ADD_WALL(board->cases[posToId(13, 2)], SOUTH);
		ADD_WALL(board->cases[posToId(12, 3)], SOUTH);
		ADD_WALL(board->cases[posToId(12, 3)], EAST);
		ADD_WALL(board->cases[posToId(13, 3)], WEST);
		ADD_WALL(board->cases[posToId(13, 3)], NORTH);
		ADD_WALL(board->cases[posToId(12, 4)], NORTH);
		ADD_WALL(board->cases[posToId(13, 5)], EAST);
		ADD_WALL(board->cases[posToId(14, 5)], WEST);
		ADD_WALL(board->cases[posToId(14, 5)], SOUTH);
		ADD_WALL(board->cases[posToId(8, 6)], SOUTH);
		ADD_WALL(board->cases[posToId(15, 6)], SOUTH);
		ADD_WALL(board->cases[posToId(9, 7)], WEST);
		ADD_WALL(board->cases[posToId(9, 7)], EAST);
		ADD_WALL(board->cases[posToId(10, 7)], WEST);
		ADD_WALL(board->cases[posToId(10, 7)], SOUTH);
		ADD_WALL(board->cases[posToId(15, 7)], NORTH);

		return;
	}

	if (pos == 2) {
		board->objectives[16] = posToId(5, 8);
		board->objectives[3] = posToId(1, 10);
		board->objectives[8] = posToId(2, 12);
		board->objectives[6] = posToId(3, 12);
		board->objectives[13] = posToId(6, 13);

		ADD_WALL(board->cases[posToId(0, 8)], SOUTH);
		ADD_WALL(board->cases[posToId(5, 8)], NORTH);
		ADD_WALL(board->cases[posToId(5, 8)], EAST);
		ADD_WALL(board->cases[posToId(6, 8)], WEST);
		ADD_WALL(board->cases[posToId(6, 8)], EAST);
		ADD_WALL(board->cases[posToId(0, 9)], NORTH);
		ADD_WALL(board->cases[posToId(1, 9)], SOUTH);
		ADD_WALL(board->cases[posToId(7, 9)], NORTH);
		ADD_WALL(board->cases[posToId(1, 10)], NORTH);
		ADD_WALL(board->cases[posToId(1, 10)], EAST);
		ADD_WALL(board->cases[posToId(2, 10)], WEST);
		ADD_WALL(board->cases[posToId(3, 11)], SOUTH);
		ADD_WALL(board->cases[posToId(2, 12)], SOUTH);
		ADD_WALL(board->cases[posToId(2, 12)], EAST);
		ADD_WALL(board->cases[posToId(3, 12)], WEST);
		ADD_WALL(board->cases[posToId(3, 12)], NORTH);
		ADD_WALL(board->cases[posToId(2, 13)], NORTH);
		ADD_WALL(board->cases[posToId(5, 13)], EAST);
		ADD_WALL(board->cases[posToId(6, 13)], WEST);
		ADD_WALL(board->cases[posToId(6, 13)], SOUTH);
		ADD_WALL(board->cases[posToId(6, 14)], NORTH);
		ADD_WALL(board->cases[posToId(4, 15)], EAST);
		ADD_WALL(board->cases[posToId(5, 15)], WEST);

		return;
	}

	if (pos == 3) {
		board->objectives[13] = posToId(13, 9);
		board->objectives[16] = posToId(8, 10);
		board->objectives[6] = posToId(12, 12);
		board->objectives[8] = posToId(12, 13);
		board->objectives[3] = posToId(10, 14);

		ADD_WALL(board->cases[posToId(9, 8)], WEST);
		ADD_WALL(board->cases[posToId(8, 9)], NORTH);
		ADD_WALL(board->cases[posToId(8, 9)], SOUTH);
		ADD_WALL(board->cases[posToId(13, 9)], SOUTH);
		ADD_WALL(board->cases[posToId(13, 9)], EAST);
		ADD_WALL(board->cases[posToId(14, 9)], WEST);
		ADD_WALL(board->cases[posToId(8, 10)], NORTH);
		ADD_WALL(board->cases[posToId(13, 10)], NORTH);
		ADD_WALL(board->cases[posToId(15, 10)], SOUTH);
		ADD_WALL(board->cases[posToId(15, 11)], NORTH);
		ADD_WALL(board->cases[posToId(11, 12)], EAST);
		ADD_WALL(board->cases[posToId(12, 12)], WEST);
		ADD_WALL(board->cases[posToId(12, 12)], SOUTH);
		ADD_WALL(board->cases[posToId(10, 13)], SOUTH);
		ADD_WALL(board->cases[posToId(12, 13)], NORTH);
		ADD_WALL(board->cases[posToId(12, 13)], EAST);
		ADD_WALL(board->cases[posToId(13, 13)], WEST);
		ADD_WALL(board->cases[posToId(9, 14)], EAST);
		ADD_WALL(board->cases[posToId(10, 14)], WEST);
		ADD_WALL(board->cases[posToId(10, 14)], NORTH);
		ADD_WALL(board->cases[posToId(8, 15)], EAST);
		ADD_WALL(board->cases[posToId(9, 15)], WEST);

		return;
	}
}

void constructPart6(Board* board, int pos) {
	if (pos == 0) {
		board->objectives[7] = posToId(6, 1);
		board->objectives[12] = posToId(1, 2);
		board->objectives[2] = posToId(5, 4);
		board->objectives[9] = posToId(3, 6);

		ADD_WALL(board->cases[posToId(4, 0)], EAST);
		ADD_WALL(board->cases[posToId(5, 0)], WEST);
		ADD_WALL(board->cases[posToId(1, 1)], SOUTH);
		ADD_WALL(board->cases[posToId(6, 1)], SOUTH);
		ADD_WALL(board->cases[posToId(6, 1)], EAST);
		ADD_WALL(board->cases[posToId(7, 1)], WEST);
		ADD_WALL(board->cases[posToId(0, 2)], EAST);
		ADD_WALL(board->cases[posToId(1, 2)], WEST);
		ADD_WALL(board->cases[posToId(1, 2)], NORTH);
		ADD_WALL(board->cases[posToId(6, 2)], NORTH);
		ADD_WALL(board->cases[posToId(0, 4)], SOUTH);
		ADD_WALL(board->cases[posToId(4, 4)], EAST);
		ADD_WALL(board->cases[posToId(5, 4)], WEST);
		ADD_WALL(board->cases[posToId(5, 4)], SOUTH);
		ADD_WALL(board->cases[posToId(0, 5)], NORTH);
		ADD_WALL(board->cases[posToId(3, 5)], SOUTH);
		ADD_WALL(board->cases[posToId(5, 5)], NORTH);
		ADD_WALL(board->cases[posToId(3, 6)], NORTH);
		ADD_WALL(board->cases[posToId(3, 6)], EAST);
		ADD_WALL(board->cases[posToId(4, 6)], WEST);
		ADD_WALL(board->cases[posToId(7, 6)], SOUTH);
		ADD_WALL(board->cases[posToId(6, 7)], EAST);

		return;
	}

	if (pos == 1) {
		board->objectives[12] = posToId(13, 1);
		board->objectives[9] = posToId(9, 3);
		board->objectives[2] = posToId(11, 5);
		board->objectives[7] = posToId(14, 6);

		ADD_WALL(board->cases[posToId(10, 0)], EAST);
		ADD_WALL(board->cases[posToId(11, 0)], WEST);
		ADD_WALL(board->cases[posToId(13, 0)], SOUTH);
		ADD_WALL(board->cases[posToId(13, 1)], NORTH);
		ADD_WALL(board->cases[posToId(13, 1)], EAST);
		ADD_WALL(board->cases[posToId(14, 1)], WEST);
		ADD_WALL(board->cases[posToId(9, 3)], SOUTH);
		ADD_WALL(board->cases[posToId(9, 3)], EAST);
		ADD_WALL(board->cases[posToId(10, 3)], WEST);
		ADD_WALL(board->cases[posToId(9, 4)], NORTH);
		ADD_WALL(board->cases[posToId(11, 4)], SOUTH);
		ADD_WALL(board->cases[posToId(15, 4)], SOUTH);
		ADD_WALL(board->cases[posToId(10, 5)], EAST);
		ADD_WALL(board->cases[posToId(11, 5)], WEST);
		ADD_WALL(board->cases[posToId(11, 5)], NORTH);
		ADD_WALL(board->cases[posToId(15, 5)], NORTH);
		ADD_WALL(board->cases[posToId(8, 6)], SOUTH);
		ADD_WALL(board->cases[posToId(13, 6)], EAST);
		ADD_WALL(board->cases[posToId(14, 6)], WEST);
		ADD_WALL(board->cases[posToId(14, 6)], SOUTH);
		ADD_WALL(board->cases[posToId(9, 7)], WEST);

		return;
	}

	if (pos == 2) {
		board->objectives[7] = posToId(1, 9);
		board->objectives[2] = posToId(4, 10);
		board->objectives[9] = posToId(6, 12);
		board->objectives[12] = posToId(2, 14);

		ADD_WALL(board->cases[posToId(1, 8)], SOUTH);
		ADD_WALL(board->cases[posToId(6, 8)], EAST);
		ADD_WALL(board->cases[posToId(1, 9)], NORTH);
		ADD_WALL(board->cases[posToId(1, 9)], EAST);
		ADD_WALL(board->cases[posToId(2, 9)], WEST);
		ADD_WALL(board->cases[posToId(7, 9)], NORTH);
		ADD_WALL(board->cases[posToId(0, 10)], SOUTH);
		ADD_WALL(board->cases[posToId(4, 10)], SOUTH);
		ADD_WALL(board->cases[posToId(4, 10)], EAST);
		ADD_WALL(board->cases[posToId(5, 10)], WEST);
		ADD_WALL(board->cases[posToId(0, 11)], NORTH);
		ADD_WALL(board->cases[posToId(4, 11)], NORTH);
		ADD_WALL(board->cases[posToId(6, 11)], SOUTH);
		ADD_WALL(board->cases[posToId(5, 12)], EAST);
		ADD_WALL(board->cases[posToId(6, 12)], WEST);
		ADD_WALL(board->cases[posToId(6, 12)], NORTH);
		ADD_WALL(board->cases[posToId(1, 14)], EAST);
		ADD_WALL(board->cases[posToId(2, 14)], WEST);
		ADD_WALL(board->cases[posToId(2, 14)], SOUTH);
		ADD_WALL(board->cases[posToId(2, 15)], NORTH);
		ADD_WALL(board->cases[posToId(4, 15)], EAST);
		ADD_WALL(board->cases[posToId(5, 15)], WEST);

		return;
	}

	if (pos == 3) {
		board->objectives[9] = posToId(12, 9);
		board->objectives[2] = posToId(10, 11);
		board->objectives[12] = posToId(14, 13);
		board->objectives[7] = posToId(9, 14);

		ADD_WALL(board->cases[posToId(9, 8)], WEST);
		ADD_WALL(board->cases[posToId(8, 9)], NORTH);
		ADD_WALL(board->cases[posToId(11, 9)], EAST);
		ADD_WALL(board->cases[posToId(12, 9)], WEST);
		ADD_WALL(board->cases[posToId(12, 9)], SOUTH);
		ADD_WALL(board->cases[posToId(10, 10)], SOUTH);
		ADD_WALL(board->cases[posToId(12, 10)], NORTH);
		ADD_WALL(board->cases[posToId(15, 10)], SOUTH);
		ADD_WALL(board->cases[posToId(10, 11)], NORTH);
		ADD_WALL(board->cases[posToId(10, 11)], EAST);
		ADD_WALL(board->cases[posToId(11, 11)], WEST);
		ADD_WALL(board->cases[posToId(15, 11)], NORTH);
		ADD_WALL(board->cases[posToId(9, 13)], SOUTH);
		ADD_WALL(board->cases[posToId(14, 13)], SOUTH);
		ADD_WALL(board->cases[posToId(14, 13)], EAST);
		ADD_WALL(board->cases[posToId(15, 13)], WEST);
		ADD_WALL(board->cases[posToId(8, 14)], EAST);
		ADD_WALL(board->cases[posToId(9, 14)], WEST);
		ADD_WALL(board->cases[posToId(9, 14)], NORTH);
		ADD_WALL(board->cases[posToId(14, 14)], NORTH);
		ADD_WALL(board->cases[posToId(10, 15)], EAST);
		ADD_WALL(board->cases[posToId(11, 15)], WEST);

		return;
	}
}

void constructPart7(Board* board, int pos) {
	if (pos == 0) {
		board->objectives[6] = posToId(3, 1);
		board->objectives[3] = posToId(1, 2);
		board->objectives[16] = posToId(7, 3);
		board->objectives[8] = posToId(6, 5);
		board->objectives[13] = posToId(4, 6);

		ADD_WALL(board->cases[posToId(3, 0)], SOUTH);
		ADD_WALL(board->cases[posToId(4, 0)], EAST);
		ADD_WALL(board->cases[posToId(5, 0)], WEST);
		ADD_WALL(board->cases[posToId(3, 1)], NORTH);
		ADD_WALL(board->cases[posToId(3, 1)], EAST);
		ADD_WALL(board->cases[posToId(4, 1)], WEST);
		ADD_WALL(board->cases[posToId(1, 2)], SOUTH);
		ADD_WALL(board->cases[posToId(1, 2)], EAST);
		ADD_WALL(board->cases[posToId(2, 2)], WEST);
		ADD_WALL(board->cases[posToId(1, 3)], NORTH);
		ADD_WALL(board->cases[posToId(7, 3)], SOUTH);
		ADD_WALL(board->cases[posToId(7, 3)], EAST);
		ADD_WALL(board->cases[posToId(0, 4)], SOUTH);
		ADD_WALL(board->cases[posToId(7, 4)], NORTH);
		ADD_WALL(board->cases[posToId(0, 5)], NORTH);
		ADD_WALL(board->cases[posToId(4, 5)], SOUTH);
		ADD_WALL(board->cases[posToId(5, 5)], EAST);
		ADD_WALL(board->cases[posToId(6, 5)], WEST);
		ADD_WALL(board->cases[posToId(6, 5)], SOUTH);
		ADD_WALL(board->cases[posToId(3, 6)], EAST);
		ADD_WALL(board->cases[posToId(4, 6)], WEST);
		ADD_WALL(board->cases[posToId(4, 6)], NORTH);
		ADD_WALL(board->cases[posToId(6, 6)], NORTH);
		ADD_WALL(board->cases[posToId(7, 6)], SOUTH);
		ADD_WALL(board->cases[posToId(6, 7)], EAST);

		return;
	}

	if (pos == 1) {
		board->objectives[3] = posToId(13, 1);
		board->objectives[6] = posToId(14, 3);
		board->objectives[13] = posToId(9, 4);
		board->objectives[8] = posToId(10, 6);
		board->objectives[16] = posToId(12, 7);

		ADD_WALL(board->cases[posToId(10, 0)], EAST);
		ADD_WALL(board->cases[posToId(11, 0)], WEST);
		ADD_WALL(board->cases[posToId(11, 1)], EAST);
		ADD_WALL(board->cases[posToId(12, 1)], WEST);
		ADD_WALL(board->cases[posToId(12, 1)], SOUTH);
		ADD_WALL(board->cases[posToId(13, 2)], NORTH);
		ADD_WALL(board->cases[posToId(9, 3)], SOUTH);
		ADD_WALL(board->cases[posToId(14, 3)], SOUTH);
		ADD_WALL(board->cases[posToId(14, 3)], EAST);
		ADD_WALL(board->cases[posToId(15, 3)], WEST);
		ADD_WALL(board->cases[posToId(9, 4)], NORTH);
		ADD_WALL(board->cases[posToId(9, 4)], EAST);
		ADD_WALL(board->cases[posToId(10, 4)], WEST);
		ADD_WALL(board->cases[posToId(14, 4)], NORTH);
		ADD_WALL(board->cases[posToId(15, 4)], SOUTH);
		ADD_WALL(board->cases[posToId(10, 5)], SOUTH);
		ADD_WALL(board->cases[posToId(15, 5)], NORTH);
		ADD_WALL(board->cases[posToId(8, 6)], SOUTH);
		ADD_WALL(board->cases[posToId(9, 6)], EAST);
		ADD_WALL(board->cases[posToId(10, 6)], WEST);
		ADD_WALL(board->cases[posToId(10, 6)], NORTH);
		ADD_WALL(board->cases[posToId(9, 7)], WEST);
		ADD_WALL(board->cases[posToId(11, 7)], EAST);
		ADD_WALL(board->cases[posToId(12, 7)], WEST);
		ADD_WALL(board->cases[posToId(12, 7)], SOUTH);

		return;
	}

	if (pos == 2) {
		board->objectives[16] = posToId(3, 8);
		board->objectives[8] = posToId(5, 9);
		board->objectives[13] = posToId(6, 11);
		board->objectives[6] = posToId(1, 12);
		board->objectives[3] = posToId(2, 14);

		ADD_WALL(board->cases[posToId(3, 8)], NORTH);
		ADD_WALL(board->cases[posToId(3, 8)], EAST);
		ADD_WALL(board->cases[posToId(4, 8)], WEST);
		ADD_WALL(board->cases[posToId(6, 8)], EAST);
		ADD_WALL(board->cases[posToId(5, 9)], SOUTH);
		ADD_WALL(board->cases[posToId(5, 9)], EAST);
		ADD_WALL(board->cases[posToId(6, 9)], WEST);
		ADD_WALL(board->cases[posToId(7, 9)], NORTH);
		ADD_WALL(board->cases[posToId(0, 10)], SOUTH);
		ADD_WALL(board->cases[posToId(5, 10)], NORTH);
		ADD_WALL(board->cases[posToId(0, 11)], NORTH);
		ADD_WALL(board->cases[posToId(1, 11)], SOUTH);
		ADD_WALL(board->cases[posToId(5, 11)], EAST);
		ADD_WALL(board->cases[posToId(6, 11)], WEST);
		ADD_WALL(board->cases[posToId(6, 11)], SOUTH);
		ADD_WALL(board->cases[posToId(0, 12)], EAST);
		ADD_WALL(board->cases[posToId(1, 12)], WEST);
		ADD_WALL(board->cases[posToId(1, 12)], NORTH);
		ADD_WALL(board->cases[posToId(6, 12)], NORTH);
		ADD_WALL(board->cases[posToId(2, 13)], SOUTH);
		ADD_WALL(board->cases[posToId(2, 14)], NORTH);
		ADD_WALL(board->cases[posToId(2, 14)], EAST);
		ADD_WALL(board->cases[posToId(3, 14)], WEST);
		ADD_WALL(board->cases[posToId(4, 15)], EAST);
		ADD_WALL(board->cases[posToId(5, 15)], WEST);

		return;
	}

	if (pos == 3) {
		board->objectives[13] = posToId(11, 9);
		board->objectives[8] = posToId(9, 10);
		board->objectives[16] = posToId(8, 12);
		board->objectives[3] = posToId(14, 13);
		board->objectives[6] = posToId(11, 14);

		ADD_WALL(board->cases[posToId(9, 8)], WEST);
		ADD_WALL(board->cases[posToId(8, 9)], NORTH);
		ADD_WALL(board->cases[posToId(9, 9)], SOUTH);
		ADD_WALL(board->cases[posToId(11, 9)], SOUTH);
		ADD_WALL(board->cases[posToId(11, 9)], EAST);
		ADD_WALL(board->cases[posToId(12, 9)], WEST);
		ADD_WALL(board->cases[posToId(9, 10)], NORTH);
		ADD_WALL(board->cases[posToId(9, 10)], EAST);
		ADD_WALL(board->cases[posToId(10, 10)], WEST);
		ADD_WALL(board->cases[posToId(11, 10)], NORTH);
		ADD_WALL(board->cases[posToId(15, 10)], SOUTH);
		ADD_WALL(board->cases[posToId(8, 11)], SOUTH);
		ADD_WALL(board->cases[posToId(15, 11)], NORTH);
		ADD_WALL(board->cases[posToId(8, 12)], WEST);
		ADD_WALL(board->cases[posToId(8, 12)], NORTH);
		ADD_WALL(board->cases[posToId(14, 12)], SOUTH);
		ADD_WALL(board->cases[posToId(13, 13)], EAST);
		ADD_WALL(board->cases[posToId(14, 13)], WEST);
		ADD_WALL(board->cases[posToId(14, 13)], NORTH);
		ADD_WALL(board->cases[posToId(11, 14)], EAST);
		ADD_WALL(board->cases[posToId(12, 14)], WEST);
		ADD_WALL(board->cases[posToId(12, 14)], SOUTH);
		ADD_WALL(board->cases[posToId(10, 15)], EAST);
		ADD_WALL(board->cases[posToId(11, 15)], WEST);
		ADD_WALL(board->cases[posToId(12, 15)], NORTH);

		return;
	}
}

void constructPart8(Board* board, int pos) {
	if (pos == 0) {
		board->objectives[14] = posToId(6, 1);
		board->objectives[4] = posToId(4, 2);
		board->objectives[11] = posToId(2, 5);
		board->objectives[1] = posToId(5, 7);

		ADD_WALL(board->cases[posToId(4, 0)], EAST);
		ADD_WALL(board->cases[posToId(5, 0)], WEST);
		ADD_WALL(board->cases[posToId(6, 0)], SOUTH);
		ADD_WALL(board->cases[posToId(5, 1)], EAST);
		ADD_WALL(board->cases[posToId(6, 1)], WEST);
		ADD_WALL(board->cases[posToId(6, 1)], NORTH);
		ADD_WALL(board->cases[posToId(3, 2)], EAST);
		ADD_WALL(board->cases[posToId(4, 2)], WEST);
		ADD_WALL(board->cases[posToId(4, 2)], SOUTH);
		ADD_WALL(board->cases[posToId(0, 3)], SOUTH);
		ADD_WALL(board->cases[posToId(4, 3)], NORTH);
		ADD_WALL(board->cases[posToId(0, 4)], NORTH);
		ADD_WALL(board->cases[posToId(2, 5)], SOUTH);
		ADD_WALL(board->cases[posToId(2, 5)], EAST);
		ADD_WALL(board->cases[posToId(3, 5)], WEST);
		ADD_WALL(board->cases[posToId(2, 6)], NORTH);
		ADD_WALL(board->cases[posToId(5, 6)], SOUTH);
		ADD_WALL(board->cases[posToId(7, 6)], SOUTH);
		ADD_WALL(board->cases[posToId(5, 7)], NORTH);
		ADD_WALL(board->cases[posToId(5, 7)], EAST);
		ADD_WALL(board->cases[posToId(6, 7)], WEST);
		ADD_WALL(board->cases[posToId(6, 7)], EAST);

		return;
	}

	if (pos == 1) {
		board->objectives[11] = posToId(10, 2);
		board->objectives[4] = posToId(13, 4);
		board->objectives[1] = posToId(8, 5);
		board->objectives[14] = posToId(14, 6);

		ADD_WALL(board->cases[posToId(11, 0)], EAST);
		ADD_WALL(board->cases[posToId(12, 0)], WEST);
		ADD_WALL(board->cases[posToId(9, 2)], EAST);
		ADD_WALL(board->cases[posToId(10, 2)], WEST);
		ADD_WALL(board->cases[posToId(10, 2)], SOUTH);
		ADD_WALL(board->cases[posToId(10, 3)], NORTH);
		ADD_WALL(board->cases[posToId(13, 3)], SOUTH);
		ADD_WALL(board->cases[posToId(12, 4)], EAST);
		ADD_WALL(board->cases[posToId(13, 4)], WEST);
		ADD_WALL(board->cases[posToId(13, 4)], NORTH);
		ADD_WALL(board->cases[posToId(15, 4)], SOUTH);
		ADD_WALL(board->cases[posToId(8, 5)], SOUTH);
		ADD_WALL(board->cases[posToId(8, 5)], EAST);
		ADD_WALL(board->cases[posToId(9, 5)], WEST);
		ADD_WALL(board->cases[posToId(14, 5)], SOUTH);
		ADD_WALL(board->cases[posToId(15, 5)], NORTH);
		ADD_WALL(board->cases[posToId(8, 6)], NORTH);
		ADD_WALL(board->cases[posToId(8, 6)], SOUTH);
		ADD_WALL(board->cases[posToId(14, 6)], NORTH);
		ADD_WALL(board->cases[posToId(14, 6)], EAST);
		ADD_WALL(board->cases[posToId(15, 6)], WEST);
		ADD_WALL(board->cases[posToId(9, 7)], WEST);

		return;
	}

	if (pos == 2) {
		board->objectives[14] = posToId(1, 9);
		board->objectives[1] = posToId(7, 10);
		board->objectives[4] = posToId(2, 11);
		board->objectives[11] = posToId(5, 13);

		ADD_WALL(board->cases[posToId(6, 8)], EAST);
		ADD_WALL(board->cases[posToId(0, 9)], EAST);
		ADD_WALL(board->cases[posToId(1, 9)], WEST);
		ADD_WALL(board->cases[posToId(1, 9)], SOUTH);
		ADD_WALL(board->cases[posToId(7, 9)], NORTH);
		ADD_WALL(board->cases[posToId(7, 9)], SOUTH);
		ADD_WALL(board->cases[posToId(0, 10)], SOUTH);
		ADD_WALL(board->cases[posToId(1, 10)], NORTH);
		ADD_WALL(board->cases[posToId(6, 10)], EAST);
		ADD_WALL(board->cases[posToId(7, 10)], WEST);
		ADD_WALL(board->cases[posToId(7, 10)], NORTH);
		ADD_WALL(board->cases[posToId(0, 11)], NORTH);
		ADD_WALL(board->cases[posToId(2, 11)], SOUTH);
		ADD_WALL(board->cases[posToId(2, 11)], EAST);
		ADD_WALL(board->cases[posToId(3, 11)], WEST);
		ADD_WALL(board->cases[posToId(2, 12)], NORTH);
		ADD_WALL(board->cases[posToId(5, 12)], SOUTH);
		ADD_WALL(board->cases[posToId(5, 13)], NORTH);
		ADD_WALL(board->cases[posToId(5, 13)], EAST);
		ADD_WALL(board->cases[posToId(6, 13)], WEST);
		ADD_WALL(board->cases[posToId(3, 15)], EAST);
		ADD_WALL(board->cases[posToId(4, 15)], WEST);

		return;
	}

	if (pos == 3) {
		board->objectives[1] = posToId(10, 8);
		board->objectives[11] = posToId(13, 10);
		board->objectives[4] = posToId(11, 13);
		board->objectives[14] = posToId(9, 14);

		ADD_WALL(board->cases[posToId(9, 8)], WEST);
		ADD_WALL(board->cases[posToId(9, 8)], EAST);
		ADD_WALL(board->cases[posToId(10, 8)], WEST);
		ADD_WALL(board->cases[posToId(10, 8)], SOUTH);
		ADD_WALL(board->cases[posToId(8, 9)], NORTH);
		ADD_WALL(board->cases[posToId(10, 9)], NORTH);
		ADD_WALL(board->cases[posToId(13, 9)], SOUTH);
		ADD_WALL(board->cases[posToId(12, 10)], EAST);
		ADD_WALL(board->cases[posToId(13, 10)], WEST);
		ADD_WALL(board->cases[posToId(13, 10)], NORTH);
		ADD_WALL(board->cases[posToId(15, 11)], SOUTH);
		ADD_WALL(board->cases[posToId(11, 12)], SOUTH);
		ADD_WALL(board->cases[posToId(15, 12)], NORTH);
		ADD_WALL(board->cases[posToId(11, 13)], NORTH);
		ADD_WALL(board->cases[posToId(11, 13)], EAST);
		ADD_WALL(board->cases[posToId(12, 13)], WEST);
		ADD_WALL(board->cases[posToId(9, 14)], SOUTH);
		ADD_WALL(board->cases[posToId(9, 14)], EAST);
		ADD_WALL(board->cases[posToId(10, 14)], WEST);
		ADD_WALL(board->cases[posToId(9, 15)], NORTH);
		ADD_WALL(board->cases[posToId(10, 15)], EAST);
		ADD_WALL(board->cases[posToId(11, 15)], WEST);

		return;
	}
}

void constructPart9(Board* board, int pos) {
	if (pos == 0) {
		board->objectives[5] = posToId(2, 1);
		board->objectives[10] = posToId(6, 3);
		board->objectives[0] = posToId(1, 4);
		board->objectives[15] = posToId(3, 6);

		ADD_WALL(board->cases[posToId(5, 0)], EAST);
		ADD_WALL(board->cases[posToId(6, 0)], WEST);
		ADD_WALL(board->cases[posToId(0, 1)], SOUTH);
		ADD_WALL(board->cases[posToId(1, 1)], EAST);
		ADD_WALL(board->cases[posToId(2, 1)], WEST);
		ADD_WALL(board->cases[posToId(2, 1)], SOUTH);
		ADD_WALL(board->cases[posToId(0, 2)], NORTH);
		ADD_WALL(board->cases[posToId(2, 2)], NORTH);
		ADD_WALL(board->cases[posToId(6, 2)], SOUTH);
		ADD_WALL(board->cases[posToId(1, 3)], SOUTH);
		ADD_WALL(board->cases[posToId(6, 3)], NORTH);
		ADD_WALL(board->cases[posToId(6, 3)], EAST);
		ADD_WALL(board->cases[posToId(7, 3)], WEST);
		ADD_WALL(board->cases[posToId(0, 4)], EAST);
		ADD_WALL(board->cases[posToId(1, 4)], WEST);
		ADD_WALL(board->cases[posToId(1, 4)], NORTH);
		ADD_WALL(board->cases[posToId(3, 6)], SOUTH);
		ADD_WALL(board->cases[posToId(3, 6)], EAST);
		ADD_WALL(board->cases[posToId(4, 6)], WEST);
		ADD_WALL(board->cases[posToId(7, 6)], SOUTH);
		ADD_WALL(board->cases[posToId(3, 7)], NORTH);
		ADD_WALL(board->cases[posToId(6, 7)], EAST);

		return;
	}

	if (pos == 1) {
		board->objectives[0] = posToId(11, 1);
		board->objectives[5] = posToId(14, 2);
		board->objectives[15] = posToId(9, 3);
		board->objectives[10] = posToId(12, 6);

		ADD_WALL(board->cases[posToId(11, 0)], SOUTH);
		ADD_WALL(board->cases[posToId(13, 0)], EAST);
		ADD_WALL(board->cases[posToId(14, 0)], WEST);
		ADD_WALL(board->cases[posToId(11, 1)], NORTH);
		ADD_WALL(board->cases[posToId(11, 1)], EAST);
		ADD_WALL(board->cases[posToId(12, 1)], WEST);
		ADD_WALL(board->cases[posToId(14, 1)], SOUTH);
		ADD_WALL(board->cases[posToId(13, 2)], EAST);
		ADD_WALL(board->cases[posToId(14, 2)], WEST);
		ADD_WALL(board->cases[posToId(14, 2)], NORTH);
		ADD_WALL(board->cases[posToId(8, 3)], EAST);
		ADD_WALL(board->cases[posToId(9, 3)], WEST);
		ADD_WALL(board->cases[posToId(9, 3)], SOUTH);
		ADD_WALL(board->cases[posToId(9, 4)], NORTH);
		ADD_WALL(board->cases[posToId(15, 5)], SOUTH);
		ADD_WALL(board->cases[posToId(8, 6)], SOUTH);
		ADD_WALL(board->cases[posToId(12, 6)], SOUTH);
		ADD_WALL(board->cases[posToId(12, 6)], EAST);
		ADD_WALL(board->cases[posToId(13, 6)], WEST);
		ADD_WALL(board->cases[posToId(15, 6)], NORTH);
		ADD_WALL(board->cases[posToId(9, 7)], WEST);
		ADD_WALL(board->cases[posToId(12, 7)], NORTH);

		return;
	}

	if (pos == 2) {
		board->objectives[10] = posToId(3, 9);
		board->objectives[15] = posToId(6, 12);
		board->objectives[5] = posToId(1, 13);
		board->objectives[0] = posToId(4, 14);

		ADD_WALL(board->cases[posToId(3, 8)], SOUTH);
		ADD_WALL(board->cases[posToId(6, 8)], EAST);
		ADD_WALL(board->cases[posToId(0, 9)], SOUTH);
		ADD_WALL(board->cases[posToId(2, 9)], EAST);
		ADD_WALL(board->cases[posToId(3, 9)], WEST);
		ADD_WALL(board->cases[posToId(3, 9)], NORTH);
		ADD_WALL(board->cases[posToId(7, 9)], NORTH);
		ADD_WALL(board->cases[posToId(0, 10)], NORTH);
		ADD_WALL(board->cases[posToId(6, 11)], SOUTH);
		ADD_WALL(board->cases[posToId(6, 12)], NORTH);
		ADD_WALL(board->cases[posToId(6, 12)], EAST);
		ADD_WALL(board->cases[posToId(7, 12)], WEST);
		ADD_WALL(board->cases[posToId(1, 13)], SOUTH);
		ADD_WALL(board->cases[posToId(1, 13)], EAST);
		ADD_WALL(board->cases[posToId(2, 13)], WEST);
		ADD_WALL(board->cases[posToId(1, 14)], NORTH);
		ADD_WALL(board->cases[posToId(3, 14)], EAST);
		ADD_WALL(board->cases[posToId(4, 14)], WEST);
		ADD_WALL(board->cases[posToId(4, 14)], SOUTH);
		ADD_WALL(board->cases[posToId(1, 15)], EAST);
		ADD_WALL(board->cases[posToId(2, 15)], WEST);
		ADD_WALL(board->cases[posToId(4, 15)], NORTH);

		return;
	}

	if (pos == 3) {
		board->objectives[15] = posToId(12, 9);
		board->objectives[0] = posToId(14, 11);
		board->objectives[10] = posToId(9, 12);
		board->objectives[5] = posToId(13, 14);

		ADD_WALL(board->cases[posToId(9, 8)], WEST);
		ADD_WALL(board->cases[posToId(12, 8)], SOUTH);
		ADD_WALL(board->cases[posToId(8, 9)], NORTH);
		ADD_WALL(board->cases[posToId(11, 9)], EAST);
		ADD_WALL(board->cases[posToId(12, 9)], WEST);
		ADD_WALL(board->cases[posToId(12, 9)], NORTH);
		ADD_WALL(board->cases[posToId(14, 11)], SOUTH);
		ADD_WALL(board->cases[posToId(14, 11)], EAST);
		ADD_WALL(board->cases[posToId(15, 11)], WEST);
		ADD_WALL(board->cases[posToId(8, 12)], EAST);
		ADD_WALL(board->cases[posToId(9, 12)], WEST);
		ADD_WALL(board->cases[posToId(9, 12)], SOUTH);
		ADD_WALL(board->cases[posToId(14, 12)], NORTH);
		ADD_WALL(board->cases[posToId(9, 13)], NORTH);
		ADD_WALL(board->cases[posToId(13, 13)], SOUTH);
		ADD_WALL(board->cases[posToId(15, 13)], SOUTH);
		ADD_WALL(board->cases[posToId(13, 14)], NORTH);
		ADD_WALL(board->cases[posToId(13, 14)], EAST);
		ADD_WALL(board->cases[posToId(14, 14)], WEST);
		ADD_WALL(board->cases[posToId(15, 14)], NORTH);
		ADD_WALL(board->cases[posToId(9, 15)], EAST);
		ADD_WALL(board->cases[posToId(10, 15)], WEST);

		return;
	}
}

void constructPart10(Board* board, int pos) {
	if (pos == 0) {
		board->objectives[1] = posToId(3, 1);
		board->objectives[11] = posToId(6, 3);
		board->objectives[4] = posToId(1, 4);
		board->objectives[14] = posToId(5, 5);

		ADD_WALL(board->cases[posToId(3, 0)], SOUTH);
		ADD_WALL(board->cases[posToId(5, 0)], EAST);
		ADD_WALL(board->cases[posToId(6, 0)], WEST);
		ADD_WALL(board->cases[posToId(0, 1)], SOUTH);
		ADD_WALL(board->cases[posToId(3, 1)], NORTH);
		ADD_WALL(board->cases[posToId(3, 1)], EAST);
		ADD_WALL(board->cases[posToId(4, 1)], WEST);
		ADD_WALL(board->cases[posToId(0, 2)], NORTH);
		ADD_WALL(board->cases[posToId(6, 3)], SOUTH);
		ADD_WALL(board->cases[posToId(6, 3)], EAST);
		ADD_WALL(board->cases[posToId(7, 3)], WEST);
		ADD_WALL(board->cases[posToId(0, 4)], EAST);
		ADD_WALL(board->cases[posToId(1, 4)], WEST);
		ADD_WALL(board->cases[posToId(1, 4)], SOUTH);
		ADD_WALL(board->cases[posToId(5, 4)], SOUTH);
		ADD_WALL(board->cases[posToId(6, 4)], NORTH);
		ADD_WALL(board->cases[posToId(1, 5)], NORTH);
		ADD_WALL(board->cases[posToId(4, 5)], EAST);
		ADD_WALL(board->cases[posToId(5, 5)], WEST);
		ADD_WALL(board->cases[posToId(5, 5)], NORTH);
		ADD_WALL(board->cases[posToId(7, 6)], SOUTH);
		ADD_WALL(board->cases[posToId(6, 7)], EAST);

		return;
	}

	if (pos == 1) {
		board->objectives[4] = posToId(11, 1);
		board->objectives[1] = posToId(14, 3);
		board->objectives[14] = posToId(10, 5);
		board->objectives[11] = posToId(12, 6);

		ADD_WALL(board->cases[posToId(11, 0)], SOUTH);
		ADD_WALL(board->cases[posToId(13, 0)], EAST);
		ADD_WALL(board->cases[posToId(14, 0)], WEST);
		ADD_WALL(board->cases[posToId(10, 1)], EAST);
		ADD_WALL(board->cases[posToId(11, 1)], WEST);
		ADD_WALL(board->cases[posToId(11, 1)], NORTH);
		ADD_WALL(board->cases[posToId(14, 3)], SOUTH);
		ADD_WALL(board->cases[posToId(14, 3)], EAST);
		ADD_WALL(board->cases[posToId(15, 3)], WEST);
		ADD_WALL(board->cases[posToId(10, 4)], SOUTH);
		ADD_WALL(board->cases[posToId(14, 4)], NORTH);
		ADD_WALL(board->cases[posToId(10, 5)], NORTH);
		ADD_WALL(board->cases[posToId(10, 5)], EAST);
		ADD_WALL(board->cases[posToId(11, 5)], WEST);
		ADD_WALL(board->cases[posToId(15, 5)], SOUTH);
		ADD_WALL(board->cases[posToId(8, 6)], SOUTH);
		ADD_WALL(board->cases[posToId(11, 6)], EAST);
		ADD_WALL(board->cases[posToId(12, 6)], WEST);
		ADD_WALL(board->cases[posToId(12, 6)], SOUTH);
		ADD_WALL(board->cases[posToId(15, 6)], NORTH);
		ADD_WALL(board->cases[posToId(9, 7)], WEST);
		ADD_WALL(board->cases[posToId(12, 7)], NORTH);

		return;
	}

	if (pos == 2) {
		board->objectives[11] = posToId(3, 9);
		board->objectives[14] = posToId(5, 10);
		board->objectives[1] = posToId(1, 12);
		board->objectives[4] = posToId(4, 14);

		ADD_WALL(board->cases[posToId(3, 8)], SOUTH);
		ADD_WALL(board->cases[posToId(6, 8)], EAST);
		ADD_WALL(board->cases[posToId(0, 9)], SOUTH);
		ADD_WALL(board->cases[posToId(3, 9)], NORTH);
		ADD_WALL(board->cases[posToId(3, 9)], EAST);
		ADD_WALL(board->cases[posToId(4, 9)], WEST);
		ADD_WALL(board->cases[posToId(7, 9)], NORTH);
		ADD_WALL(board->cases[posToId(0, 10)], NORTH);
		ADD_WALL(board->cases[posToId(4, 10)], EAST);
		ADD_WALL(board->cases[posToId(5, 10)], WEST);
		ADD_WALL(board->cases[posToId(5, 10)], SOUTH);
		ADD_WALL(board->cases[posToId(1, 11)], SOUTH);
		ADD_WALL(board->cases[posToId(5, 11)], NORTH);
		ADD_WALL(board->cases[posToId(0, 12)], EAST);
		ADD_WALL(board->cases[posToId(1, 12)], WEST);
		ADD_WALL(board->cases[posToId(1, 12)], NORTH);
		ADD_WALL(board->cases[posToId(4, 14)], SOUTH);
		ADD_WALL(board->cases[posToId(4, 14)], EAST);
		ADD_WALL(board->cases[posToId(5, 14)], WEST);
		ADD_WALL(board->cases[posToId(1, 15)], EAST);
		ADD_WALL(board->cases[posToId(2, 15)], WEST);
		ADD_WALL(board->cases[posToId(4, 15)], NORTH);

		return;
	}

	if (pos == 3) {
		board->objectives[14] = posToId(10, 10);
		board->objectives[4] = posToId(14, 11);
		board->objectives[11] = posToId(9, 12);
		board->objectives[1] = posToId(12, 14);

		ADD_WALL(board->cases[posToId(9, 8)], WEST);
		ADD_WALL(board->cases[posToId(8, 9)], NORTH);
		ADD_WALL(board->cases[posToId(10, 10)], SOUTH);
		ADD_WALL(board->cases[posToId(10, 10)], EAST);
		ADD_WALL(board->cases[posToId(11, 10)], WEST);
		ADD_WALL(board->cases[posToId(14, 10)], SOUTH);
		ADD_WALL(board->cases[posToId(9, 11)], SOUTH);
		ADD_WALL(board->cases[posToId(10, 11)], NORTH);
		ADD_WALL(board->cases[posToId(14, 11)], NORTH);
		ADD_WALL(board->cases[posToId(14, 11)], EAST);
		ADD_WALL(board->cases[posToId(15, 11)], WEST);
		ADD_WALL(board->cases[posToId(8, 12)], EAST);
		ADD_WALL(board->cases[posToId(9, 12)], WEST);
		ADD_WALL(board->cases[posToId(9, 12)], NORTH);
		ADD_WALL(board->cases[posToId(15, 13)], SOUTH);
		ADD_WALL(board->cases[posToId(11, 14)], EAST);
		ADD_WALL(board->cases[posToId(12, 14)], WEST);
		ADD_WALL(board->cases[posToId(12, 14)], SOUTH);
		ADD_WALL(board->cases[posToId(15, 14)], NORTH);
		ADD_WALL(board->cases[posToId(9, 15)], EAST);
		ADD_WALL(board->cases[posToId(10, 15)], WEST);
		ADD_WALL(board->cases[posToId(12, 15)], NORTH);

		return;
	}
}

void constructPart11(Board* board, int pos) {
	if (pos == 0) {
		board->objectives[0] = posToId(4, 1);
		board->objectives[5] = posToId(1, 3);
		board->objectives[10] = posToId(6, 4);
		board->objectives[15] = posToId(3, 6);

		ADD_WALL(board->cases[posToId(4, 0)], SOUTH);
		ADD_WALL(board->cases[posToId(6, 0)], EAST);
		ADD_WALL(board->cases[posToId(7, 0)], WEST);
		ADD_WALL(board->cases[posToId(0, 1)], SOUTH);
		ADD_WALL(board->cases[posToId(4, 1)], NORTH);
		ADD_WALL(board->cases[posToId(4, 1)], EAST);
		ADD_WALL(board->cases[posToId(5, 1)], WEST);
		ADD_WALL(board->cases[posToId(0, 2)], NORTH);
		ADD_WALL(board->cases[posToId(1, 2)], SOUTH);
		ADD_WALL(board->cases[posToId(0, 3)], EAST);
		ADD_WALL(board->cases[posToId(1, 3)], WEST);
		ADD_WALL(board->cases[posToId(1, 3)], NORTH);
		ADD_WALL(board->cases[posToId(5, 4)], EAST);
		ADD_WALL(board->cases[posToId(6, 4)], WEST);
		ADD_WALL(board->cases[posToId(6, 4)], SOUTH);
		ADD_WALL(board->cases[posToId(3, 6)], SOUTH);
		ADD_WALL(board->cases[posToId(3, 6)], EAST);
		ADD_WALL(board->cases[posToId(4, 6)], WEST);
		ADD_WALL(board->cases[posToId(7, 6)], SOUTH);
		ADD_WALL(board->cases[posToId(3, 7)], NORTH);
		ADD_WALL(board->cases[posToId(6, 7)], SOUTH);

		return;
	}

	if (pos == 1) {
		board->objectives[5] = posToId(12, 1);
		board->objectives[15] = posToId(9, 3);
		board->objectives[0] = posToId(14, 4);
		board->objectives[10] = posToId(11, 6);

		ADD_WALL(board->cases[posToId(12, 0)], SOUTH);
		ADD_WALL(board->cases[posToId(13, 0)], EAST);
		ADD_WALL(board->cases[posToId(14, 0)], WEST);
		ADD_WALL(board->cases[posToId(12, 1)], NORTH);
		ADD_WALL(board->cases[posToId(12, 1)], EAST);
		ADD_WALL(board->cases[posToId(13, 1)], WEST);
		ADD_WALL(board->cases[posToId(8, 3)], EAST);
		ADD_WALL(board->cases[posToId(9, 3)], WEST);
		ADD_WALL(board->cases[posToId(9, 3)], SOUTH);
		ADD_WALL(board->cases[posToId(9, 4)], NORTH);
		ADD_WALL(board->cases[posToId(14, 4)], SOUTH);
		ADD_WALL(board->cases[posToId(14, 4)], EAST);
		ADD_WALL(board->cases[posToId(15, 4)], WEST);
		ADD_WALL(board->cases[posToId(10, 5)], SOUTH);
		ADD_WALL(board->cases[posToId(14, 5)], NORTH);
		ADD_WALL(board->cases[posToId(8, 6)], SOUTH);
		ADD_WALL(board->cases[posToId(10, 6)], EAST);
		ADD_WALL(board->cases[posToId(11, 6)], WEST);
		ADD_WALL(board->cases[posToId(11, 6)], NORTH);
		ADD_WALL(board->cases[posToId(15, 6)], SOUTH);
		ADD_WALL(board->cases[posToId(9, 7)], WEST);
		ADD_WALL(board->cases[posToId(15, 7)], NORTH);

		return;
	}

	if (pos == 2) {
		board->objectives[10] = posToId(4, 9);
		board->objectives[0] = posToId(1, 11);
		board->objectives[15] = posToId(6, 12);
		board->objectives[5] = posToId(3, 14);

		ADD_WALL(board->cases[posToId(0, 8)], SOUTH);
		ADD_WALL(board->cases[posToId(6, 8)], EAST);
		ADD_WALL(board->cases[posToId(0, 9)], NORTH);
		ADD_WALL(board->cases[posToId(4, 9)], SOUTH);
		ADD_WALL(board->cases[posToId(4, 9)], EAST);
		ADD_WALL(board->cases[posToId(5, 9)], WEST);
		ADD_WALL(board->cases[posToId(7, 9)], NORTH);
		ADD_WALL(board->cases[posToId(1, 10)], SOUTH);
		ADD_WALL(board->cases[posToId(4, 10)], NORTH);
		ADD_WALL(board->cases[posToId(0, 11)], EAST);
		ADD_WALL(board->cases[posToId(1, 11)], WEST);
		ADD_WALL(board->cases[posToId(1, 11)], NORTH);
		ADD_WALL(board->cases[posToId(6, 11)], SOUTH);
		ADD_WALL(board->cases[posToId(6, 12)], NORTH);
		ADD_WALL(board->cases[posToId(6, 12)], EAST);
		ADD_WALL(board->cases[posToId(7, 12)], WEST);
		ADD_WALL(board->cases[posToId(2, 14)], EAST);
		ADD_WALL(board->cases[posToId(3, 14)], WEST);
		ADD_WALL(board->cases[posToId(3, 14)], SOUTH);
		ADD_WALL(board->cases[posToId(1, 15)], EAST);
		ADD_WALL(board->cases[posToId(2, 15)], WEST);
		ADD_WALL(board->cases[posToId(3, 15)], NORTH);

		return;
	}

	if (pos == 3) {
		board->objectives[15] = posToId(12, 9);
		board->objectives[10] = posToId(9, 11);
		board->objectives[5] = posToId(14, 12);
		board->objectives[0] = posToId(11, 14);

		ADD_WALL(board->cases[posToId(9, 8)], WEST);
		ADD_WALL(board->cases[posToId(12, 8)], SOUTH);
		ADD_WALL(board->cases[posToId(8, 9)], NORTH);
		ADD_WALL(board->cases[posToId(11, 9)], EAST);
		ADD_WALL(board->cases[posToId(12, 9)], WEST);
		ADD_WALL(board->cases[posToId(12, 9)], NORTH);
		ADD_WALL(board->cases[posToId(9, 10)], SOUTH);
		ADD_WALL(board->cases[posToId(9, 11)], NORTH);
		ADD_WALL(board->cases[posToId(9, 11)], EAST);
		ADD_WALL(board->cases[posToId(10, 11)], WEST);
		ADD_WALL(board->cases[posToId(14, 12)], SOUTH);
		ADD_WALL(board->cases[posToId(14, 12)], EAST);
		ADD_WALL(board->cases[posToId(15, 12)], WEST);
		ADD_WALL(board->cases[posToId(14, 13)], NORTH);
		ADD_WALL(board->cases[posToId(15, 13)], SOUTH);
		ADD_WALL(board->cases[posToId(10, 14)], EAST);
		ADD_WALL(board->cases[posToId(11, 14)], WEST);
		ADD_WALL(board->cases[posToId(11, 14)], SOUTH);
		ADD_WALL(board->cases[posToId(15, 14)], NORTH);
		ADD_WALL(board->cases[posToId(8, 15)], EAST);
		ADD_WALL(board->cases[posToId(9, 15)], WEST);
		ADD_WALL(board->cases[posToId(11, 15)], NORTH);

		return;
	}
}

void constructPart12(Board* board, int pos) {
	if (pos == 0) {
		board->objectives[2] = posToId(4, 2);
		board->objectives[12] = posToId(2, 3);
		board->objectives[7] = posToId(5, 4);
		board->objectives[9] = posToId(3, 5);

		ADD_WALL(board->cases[posToId(3, 0)], EAST);
		ADD_WALL(board->cases[posToId(4, 0)], WEST);
		ADD_WALL(board->cases[posToId(2, 2)], SOUTH);
		ADD_WALL(board->cases[posToId(3, 2)], EAST);
		ADD_WALL(board->cases[posToId(4, 2)], WEST);
		ADD_WALL(board->cases[posToId(4, 2)], SOUTH);
		ADD_WALL(board->cases[posToId(1, 3)], EAST);
		ADD_WALL(board->cases[posToId(2, 3)], WEST);
		ADD_WALL(board->cases[posToId(2, 3)], NORTH);
		ADD_WALL(board->cases[posToId(4, 3)], NORTH);
		ADD_WALL(board->cases[posToId(3, 4)], SOUTH);
		ADD_WALL(board->cases[posToId(5, 4)], SOUTH);
		ADD_WALL(board->cases[posToId(5, 4)], EAST);
		ADD_WALL(board->cases[posToId(6, 4)], WEST);
		ADD_WALL(board->cases[posToId(0, 5)], SOUTH);
		ADD_WALL(board->cases[posToId(3, 5)], NORTH);
		ADD_WALL(board->cases[posToId(3, 5)], EAST);
		ADD_WALL(board->cases[posToId(4, 5)], WEST);
		ADD_WALL(board->cases[posToId(5, 5)], NORTH);
		ADD_WALL(board->cases[posToId(0, 6)], NORTH);
		ADD_WALL(board->cases[posToId(7, 6)], SOUTH);
		ADD_WALL(board->cases[posToId(6, 7)], EAST);

		return;
	}

	if (pos == 1) {
		board->objectives[12] = posToId(12, 10);
		board->objectives[9] = posToId(10, 11);
		board->objectives[2] = posToId(12, 12);
		board->objectives[7] = posToId(11, 13);

		ADD_WALL(board->cases[posToId(9, 0)], EAST);
		ADD_WALL(board->cases[posToId(10, 0)], WEST);
		ADD_WALL(board->cases[posToId(12, 1)], SOUTH);
		ADD_WALL(board->cases[posToId(12, 2)], NORTH);
		ADD_WALL(board->cases[posToId(12, 2)], EAST);
		ADD_WALL(board->cases[posToId(13, 2)], WEST);
		ADD_WALL(board->cases[posToId(10, 3)], SOUTH);
		ADD_WALL(board->cases[posToId(10, 3)], EAST);
		ADD_WALL(board->cases[posToId(11, 3)], WEST);
		ADD_WALL(board->cases[posToId(13, 3)], SOUTH);
		ADD_WALL(board->cases[posToId(15, 3)], SOUTH);
		ADD_WALL(board->cases[posToId(10, 4)], NORTH);
		ADD_WALL(board->cases[posToId(12, 4)], EAST);
		ADD_WALL(board->cases[posToId(13, 4)], WEST);
		ADD_WALL(board->cases[posToId(13, 4)], NORTH);
		ADD_WALL(board->cases[posToId(15, 4)], NORTH);
		ADD_WALL(board->cases[posToId(10, 5)], WEST);
		ADD_WALL(board->cases[posToId(11, 5)], EAST);
		ADD_WALL(board->cases[posToId(11, 5)], SOUTH);
		ADD_WALL(board->cases[posToId(8, 6)], SOUTH);
		ADD_WALL(board->cases[posToId(11, 6)], NORTH);
		ADD_WALL(board->cases[posToId(9, 7)], WEST);

		return;
	}

	if (pos == 2) {
		board->objectives[7] = posToId(4, 10);
		board->objectives[2] = posToId(2, 11);
		board->objectives[9] = posToId(5, 12);
		board->objectives[12] = posToId(3, 13);

		ADD_WALL(board->cases[posToId(6, 8)], EAST);
		ADD_WALL(board->cases[posToId(4, 9)], SOUTH);
		ADD_WALL(board->cases[posToId(7, 9)], NORTH);
		ADD_WALL(board->cases[posToId(4, 10)], NORTH);
		ADD_WALL(board->cases[posToId(4, 10)], EAST);
		ADD_WALL(board->cases[posToId(5, 10)], WEST);
		ADD_WALL(board->cases[posToId(0, 11)], SOUTH);
		ADD_WALL(board->cases[posToId(2, 11)], SOUTH);
		ADD_WALL(board->cases[posToId(2, 11)], EAST);
		ADD_WALL(board->cases[posToId(5, 11)], WEST);
		ADD_WALL(board->cases[posToId(5, 11)], SOUTH);
		ADD_WALL(board->cases[posToId(0, 12)], NORTH);
		ADD_WALL(board->cases[posToId(2, 12)], NORTH);
		ADD_WALL(board->cases[posToId(4, 12)], EAST);
		ADD_WALL(board->cases[posToId(5, 12)], WEST);
		ADD_WALL(board->cases[posToId(5, 12)], NORTH);
		ADD_WALL(board->cases[posToId(2, 13)], EAST);
		ADD_WALL(board->cases[posToId(3, 13)], WEST);
		ADD_WALL(board->cases[posToId(3, 13)], SOUTH);
		ADD_WALL(board->cases[posToId(3, 14)], NORTH);
		ADD_WALL(board->cases[posToId(5, 15)], EAST);
		ADD_WALL(board->cases[posToId(6, 15)], WEST);

		return;
	}

	if (pos == 3) {
		board->objectives[9] = posToId(12, 10);
		board->objectives[7] = posToId(10, 11);
		board->objectives[12] = posToId(13, 12);
		board->objectives[2] = posToId(11, 13);

		ADD_WALL(board->cases[posToId(9, 8)], WEST);
		ADD_WALL(board->cases[posToId(15, 9)], SOUTH);
		ADD_WALL(board->cases[posToId(10, 10)], SOUTH);
		ADD_WALL(board->cases[posToId(11, 10)], EAST);
		ADD_WALL(board->cases[posToId(12, 10)], WEST);
		ADD_WALL(board->cases[posToId(12, 10)], SOUTH);
		ADD_WALL(board->cases[posToId(15, 10)], NORTH);
		ADD_WALL(board->cases[posToId(9, 11)], WEST);
		ADD_WALL(board->cases[posToId(10, 11)], EAST);
		ADD_WALL(board->cases[posToId(10, 11)], NORTH);
		ADD_WALL(board->cases[posToId(12, 11)], NORTH);
		ADD_WALL(board->cases[posToId(11, 12)], SOUTH);
		ADD_WALL(board->cases[posToId(13, 12)], SOUTH);
		ADD_WALL(board->cases[posToId(13, 12)], EAST);
		ADD_WALL(board->cases[posToId(14, 12)], WEST);
		ADD_WALL(board->cases[posToId(11, 13)], NORTH);
		ADD_WALL(board->cases[posToId(11, 13)], EAST);
		ADD_WALL(board->cases[posToId(12, 13)], WEST);
		ADD_WALL(board->cases[posToId(13, 13)], NORTH);
		ADD_WALL(board->cases[posToId(11, 15)], EAST);
		ADD_WALL(board->cases[posToId(12, 15)], WEST);

		return;
	}
}

void constructPart13(Board* board, int pos) {
	if (pos == 0) {
		board->objectives[4] = posToId(4, 2);
		board->objectives[1] = posToId(4, 3);
		board->objectives[14] = posToId(6, 5);
		board->objectives[11] = posToId(2, 6);

		ADD_WALL(board->cases[posToId(1, 0)], EAST);
		ADD_WALL(board->cases[posToId(2, 0)], WEST);
		ADD_WALL(board->cases[posToId(3, 2)], EAST);
		ADD_WALL(board->cases[posToId(4, 2)], WEST);
		ADD_WALL(board->cases[posToId(4, 2)], SOUTH);
		ADD_WALL(board->cases[posToId(4, 3)], NORTH);
		ADD_WALL(board->cases[posToId(4, 3)], EAST);
		ADD_WALL(board->cases[posToId(5, 3)], WEST);
		ADD_WALL(board->cases[posToId(0, 4)], SOUTH);
		ADD_WALL(board->cases[posToId(6, 4)], SOUTH);
		ADD_WALL(board->cases[posToId(0, 5)], NORTH);
		ADD_WALL(board->cases[posToId(5, 5)], EAST);
		ADD_WALL(board->cases[posToId(6, 5)], WEST);
		ADD_WALL(board->cases[posToId(6, 5)], NORTH);
		ADD_WALL(board->cases[posToId(2, 6)], SOUTH);
		ADD_WALL(board->cases[posToId(2, 6)], EAST);
		ADD_WALL(board->cases[posToId(3, 6)], WEST);
		ADD_WALL(board->cases[posToId(7, 6)], SOUTH);
		ADD_WALL(board->cases[posToId(2, 7)], NORTH);
		ADD_WALL(board->cases[posToId(6, 7)], EAST);

		return;
	}

	if (pos == 1) {
		board->objectives[11] = posToId(9, 2);
		board->objectives[1] = posToId(12, 12);
		board->objectives[4] = posToId(13, 12);
		board->objectives[14] = posToId(10, 14);

		ADD_WALL(board->cases[posToId(10, 0)], EAST);
		ADD_WALL(board->cases[posToId(11, 0)], WEST);
		ADD_WALL(board->cases[posToId(8, 2)], EAST);
		ADD_WALL(board->cases[posToId(9, 2)], WEST);
		ADD_WALL(board->cases[posToId(9, 2)], SOUTH);
		ADD_WALL(board->cases[posToId(15, 2)], SOUTH);
		ADD_WALL(board->cases[posToId(9, 3)], NORTH);
		ADD_WALL(board->cases[posToId(13, 3)], SOUTH);
		ADD_WALL(board->cases[posToId(15, 3)], NORTH);
		ADD_WALL(board->cases[posToId(12, 4)], SOUTH);
		ADD_WALL(board->cases[posToId(12, 4)], EAST);
		ADD_WALL(board->cases[posToId(13, 4)], WEST);
		ADD_WALL(board->cases[posToId(13, 4)], NORTH);
		ADD_WALL(board->cases[posToId(10, 5)], SOUTH);
		ADD_WALL(board->cases[posToId(12, 5)], NORTH);
		ADD_WALL(board->cases[posToId(8, 6)], SOUTH);
		ADD_WALL(board->cases[posToId(10, 6)], NORTH);
		ADD_WALL(board->cases[posToId(10, 6)], EAST);
		ADD_WALL(board->cases[posToId(11, 6)], WEST);
		ADD_WALL(board->cases[posToId(9, 7)], WEST);

		return;
	}

	if (pos == 2) {
		board->objectives[14] = posToId(5, 9);
		board->objectives[4] = posToId(2, 11);
		board->objectives[1] = posToId(3, 11);
		board->objectives[11] = posToId(6, 13);

		ADD_WALL(board->cases[posToId(6, 8)], EAST);
		ADD_WALL(board->cases[posToId(4, 9)], EAST);
		ADD_WALL(board->cases[posToId(5, 9)], WEST);
		ADD_WALL(board->cases[posToId(5, 9)], SOUTH);
		ADD_WALL(board->cases[posToId(7, 9)], NORTH);
		ADD_WALL(board->cases[posToId(3, 10)], SOUTH);
		ADD_WALL(board->cases[posToId(5, 10)], NORTH);
		ADD_WALL(board->cases[posToId(2, 11)], SOUTH);
		ADD_WALL(board->cases[posToId(2, 11)], EAST);
		ADD_WALL(board->cases[posToId(3, 11)], WEST);
		ADD_WALL(board->cases[posToId(3, 11)], NORTH);
		ADD_WALL(board->cases[posToId(0, 12)], SOUTH);
		ADD_WALL(board->cases[posToId(2, 12)], NORTH);
		ADD_WALL(board->cases[posToId(6, 12)], SOUTH);
		ADD_WALL(board->cases[posToId(0, 13)], NORTH);
		ADD_WALL(board->cases[posToId(6, 13)], NORTH);
		ADD_WALL(board->cases[posToId(6, 13)], EAST);
		ADD_WALL(board->cases[posToId(7, 13)], WEST);
		ADD_WALL(board->cases[posToId(4, 15)], EAST);
		ADD_WALL(board->cases[posToId(5, 15)], WEST);

		return;
	}

	if (pos == 3) {
		board->objectives[11] = posToId(13, 9);
		board->objectives[14] = posToId(9, 10);
		board->objectives[1] = posToId(11, 12);
		board->objectives[4] = posToId(11, 13);

		ADD_WALL(board->cases[posToId(9, 8)], WEST);
		ADD_WALL(board->cases[posToId(13, 8)], SOUTH);
		ADD_WALL(board->cases[posToId(8, 9)], NORTH);
		ADD_WALL(board->cases[posToId(12, 9)], EAST);
		ADD_WALL(board->cases[posToId(13, 9)], WEST);
		ADD_WALL(board->cases[posToId(13, 9)], NORTH);
		ADD_WALL(board->cases[posToId(9, 10)], SOUTH);
		ADD_WALL(board->cases[posToId(9, 10)], EAST);
		ADD_WALL(board->cases[posToId(10, 10)], WEST);
		ADD_WALL(board->cases[posToId(15, 10)], SOUTH);
		ADD_WALL(board->cases[posToId(9, 11)], NORTH);
		ADD_WALL(board->cases[posToId(15, 11)], NORTH);
		ADD_WALL(board->cases[posToId(10, 12)], EAST);
		ADD_WALL(board->cases[posToId(11, 12)], WEST);
		ADD_WALL(board->cases[posToId(11, 12)], SOUTH);
		ADD_WALL(board->cases[posToId(11, 13)], NORTH);
		ADD_WALL(board->cases[posToId(11, 13)], EAST);
		ADD_WALL(board->cases[posToId(12, 13)], WEST);
		ADD_WALL(board->cases[posToId(12, 15)], EAST);
		ADD_WALL(board->cases[posToId(13, 15)], WEST);

		return;
	}
}

void constructPart14(Board* board, int pos) {
	if (pos == 0) {
		board->objectives[2] = posToId(5, 1);
		board->objectives[9] = posToId(7, 4);
		board->objectives[7] = posToId(2, 5);
		board->objectives[12] = posToId(2, 6);

		ADD_WALL(board->cases[posToId(5, 0)], SOUTH);
		ADD_WALL(board->cases[posToId(6, 0)], EAST);
		ADD_WALL(board->cases[posToId(7, 0)], WEST);
		ADD_WALL(board->cases[posToId(5, 1)], NORTH);
		ADD_WALL(board->cases[posToId(5, 1)], EAST);
		ADD_WALL(board->cases[posToId(6, 1)], WEST);
		ADD_WALL(board->cases[posToId(0, 2)], SOUTH);
		ADD_WALL(board->cases[posToId(0, 3)], NORTH);
		ADD_WALL(board->cases[posToId(6, 4)], EAST);
		ADD_WALL(board->cases[posToId(7, 4)], WEST);
		ADD_WALL(board->cases[posToId(7, 4)], SOUTH);
		ADD_WALL(board->cases[posToId(2, 5)], SOUTH);
		ADD_WALL(board->cases[posToId(3, 5)], EAST);
		ADD_WALL(board->cases[posToId(3, 5)], WEST);
		ADD_WALL(board->cases[posToId(7, 5)], NORTH);
		ADD_WALL(board->cases[posToId(1, 6)], EAST);
		ADD_WALL(board->cases[posToId(2, 6)], WEST);
		ADD_WALL(board->cases[posToId(2, 6)], NORTH);
		ADD_WALL(board->cases[posToId(7, 6)], SOUTH);
		ADD_WALL(board->cases[posToId(6, 7)], EAST);

		return;
	}

	if (pos == 1) {
		board->objectives[12] = posToId(9, 2);
		board->objectives[7] = posToId(10, 2);
		board->objectives[2] = posToId(14, 5);
		board->objectives[9] = posToId(11, 7);

		ADD_WALL(board->cases[posToId(12, 0)], EAST);
		ADD_WALL(board->cases[posToId(13, 0)], WEST);
		ADD_WALL(board->cases[posToId(9, 1)], SOUTH);
		ADD_WALL(board->cases[posToId(9, 2)], NORTH);
		ADD_WALL(board->cases[posToId(9, 2)], EAST);
		ADD_WALL(board->cases[posToId(10, 2)], WEST);
		ADD_WALL(board->cases[posToId(10, 2)], SOUTH);
		ADD_WALL(board->cases[posToId(10, 3)], NORTH);
		ADD_WALL(board->cases[posToId(14, 5)], SOUTH);
		ADD_WALL(board->cases[posToId(14, 5)], EAST);
		ADD_WALL(board->cases[posToId(15, 5)], WEST);
		ADD_WALL(board->cases[posToId(8, 6)], SOUTH);
		ADD_WALL(board->cases[posToId(11, 6)], SOUTH);
		ADD_WALL(board->cases[posToId(14, 6)], NORTH);
		ADD_WALL(board->cases[posToId(15, 6)], SOUTH);
		ADD_WALL(board->cases[posToId(9, 7)], WEST);
		ADD_WALL(board->cases[posToId(10, 7)], EAST);
		ADD_WALL(board->cases[posToId(11, 7)], WEST);
		ADD_WALL(board->cases[posToId(11, 7)], NORTH);
		ADD_WALL(board->cases[posToId(15, 7)], NORTH);

		return;
	}

	if (pos == 2) {
		board->objectives[9] = posToId(4, 8);
		board->objectives[2] = posToId(1, 10);
		board->objectives[7] = posToId(5, 13);
		board->objectives[12] = posToId(6, 13);

		ADD_WALL(board->cases[posToId(0, 8)], SOUTH);
		ADD_WALL(board->cases[posToId(4, 8)], SOUTH);
		ADD_WALL(board->cases[posToId(4, 8)], EAST);
		ADD_WALL(board->cases[posToId(5, 8)], WEST);
		ADD_WALL(board->cases[posToId(6, 8)], EAST);
		ADD_WALL(board->cases[posToId(0, 9)], NORTH);
		ADD_WALL(board->cases[posToId(1, 9)], SOUTH);
		ADD_WALL(board->cases[posToId(4, 9)], NORTH);
		ADD_WALL(board->cases[posToId(7, 9)], NORTH);
		ADD_WALL(board->cases[posToId(0, 10)], EAST);
		ADD_WALL(board->cases[posToId(1, 10)], WEST);
		ADD_WALL(board->cases[posToId(1, 10)], NORTH);
		ADD_WALL(board->cases[posToId(5, 13)], NORTH);
		ADD_WALL(board->cases[posToId(5, 13)], EAST);
		ADD_WALL(board->cases[posToId(6, 13)], WEST);
		ADD_WALL(board->cases[posToId(6, 13)], SOUTH);
		ADD_WALL(board->cases[posToId(6, 14)], NORTH);
		ADD_WALL(board->cases[posToId(2, 15)], EAST);
		ADD_WALL(board->cases[posToId(3, 15)], WEST);

		return;
	}

	if (pos == 3) {
		board->objectives[12] = posToId(13, 9);
		board->objectives[7] = posToId(13, 10);
		board->objectives[9] = posToId(8, 11);
		board->objectives[2] = posToId(10, 14);

		ADD_WALL(board->cases[posToId(9, 8)], WEST);
		ADD_WALL(board->cases[posToId(8, 9)], NORTH);
		ADD_WALL(board->cases[posToId(13, 9)], SOUTH);
		ADD_WALL(board->cases[posToId(13, 9)], EAST);
		ADD_WALL(board->cases[posToId(14, 9)], WEST);
		ADD_WALL(board->cases[posToId(8, 10)], SOUTH);
		ADD_WALL(board->cases[posToId(12, 10)], EAST);
		ADD_WALL(board->cases[posToId(13, 10)], WEST);
		ADD_WALL(board->cases[posToId(13, 10)], NORTH);
		ADD_WALL(board->cases[posToId(8, 11)], NORTH);
		ADD_WALL(board->cases[posToId(8, 11)], EAST);
		ADD_WALL(board->cases[posToId(9, 11)], WEST);
		ADD_WALL(board->cases[posToId(15, 12)], SOUTH);
		ADD_WALL(board->cases[posToId(15, 12)], NORTH);
		ADD_WALL(board->cases[posToId(9, 13)], EAST);
		ADD_WALL(board->cases[posToId(10, 13)], WEST);
		ADD_WALL(board->cases[posToId(10, 13)], SOUTH);
		ADD_WALL(board->cases[posToId(8, 14)], EAST);
		ADD_WALL(board->cases[posToId(9, 14)], WEST);
		ADD_WALL(board->cases[posToId(10, 14)], NORTH);

		return;
	}
}

void constructPart15(Board* board, int pos) {
	if (pos == 0) {
		board->objectives[5] = posToId(2, 1);
		board->objectives[0] = posToId(6, 3);
		board->objectives[15] = posToId(1, 6);
		board->objectives[10] = posToId(5, 6);

		ADD_WALL(board->cases[posToId(2, 0)], SOUTH);
		ADD_WALL(board->cases[posToId(5, 0)], EAST);
		ADD_WALL(board->cases[posToId(6, 0)], WEST);
		ADD_WALL(board->cases[posToId(1, 1)], EAST);
		ADD_WALL(board->cases[posToId(2, 1)], WEST);
		ADD_WALL(board->cases[posToId(2, 1)], NORTH);
		ADD_WALL(board->cases[posToId(6, 2)], SOUTH);
		ADD_WALL(board->cases[posToId(6, 3)], NORTH);
		ADD_WALL(board->cases[posToId(6, 3)], EAST);
		ADD_WALL(board->cases[posToId(7, 3)], WEST);
		ADD_WALL(board->cases[posToId(0, 4)], SOUTH);
		ADD_WALL(board->cases[posToId(0, 5)], NORTH);
		ADD_WALL(board->cases[posToId(1, 6)], SOUTH);
		ADD_WALL(board->cases[posToId(1, 6)], EAST);
		ADD_WALL(board->cases[posToId(2, 6)], WEST);
		ADD_WALL(board->cases[posToId(4, 6)], EAST);
		ADD_WALL(board->cases[posToId(5, 6)], WEST);
		ADD_WALL(board->cases[posToId(5, 6)], SOUTH);
		ADD_WALL(board->cases[posToId(7, 6)], SOUTH);
		ADD_WALL(board->cases[posToId(1, 7)], NORTH);
		ADD_WALL(board->cases[posToId(5, 7)], NORTH);
		ADD_WALL(board->cases[posToId(6, 7)], EAST);

		return;
	}

	if (pos == 1) {
		board->objectives[15] = posToId(9, 1);
		board->objectives[5] = posToId(14, 2);
		board->objectives[10] = posToId(9, 5);
		board->objectives[0] = posToId(12, 6);

		ADD_WALL(board->cases[posToId(10, 0)], EAST);
		ADD_WALL(board->cases[posToId(11, 0)], WEST);
		ADD_WALL(board->cases[posToId(8, 1)], EAST);
		ADD_WALL(board->cases[posToId(9, 1)], WEST);
		ADD_WALL(board->cases[posToId(9, 1)], SOUTH);
		ADD_WALL(board->cases[posToId(14, 1)], SOUTH);
		ADD_WALL(board->cases[posToId(9, 2)], NORTH);
		ADD_WALL(board->cases[posToId(14, 2)], NORTH);
		ADD_WALL(board->cases[posToId(14, 2)], EAST);
		ADD_WALL(board->cases[posToId(15, 2)], WEST);
		ADD_WALL(board->cases[posToId(9, 4)], SOUTH);
		ADD_WALL(board->cases[posToId(8, 5)], EAST);
		ADD_WALL(board->cases[posToId(9, 5)], WEST);
		ADD_WALL(board->cases[posToId(9, 5)], NORTH);
		ADD_WALL(board->cases[posToId(15, 5)], SOUTH);
		ADD_WALL(board->cases[posToId(8, 6)], SOUTH);
		ADD_WALL(board->cases[posToId(12, 6)], SOUTH);
		ADD_WALL(board->cases[posToId(12, 6)], EAST);
		ADD_WALL(board->cases[posToId(13, 6)], WEST);
		ADD_WALL(board->cases[posToId(15, 6)], NORTH);
		ADD_WALL(board->cases[posToId(9, 7)], WEST);
		ADD_WALL(board->cases[posToId(12, 7)], NORTH);

		return;
	}

	if (pos == 2) {
		board->objectives[0] = posToId(3, 9);
		board->objectives[10] = posToId(6, 10);
		board->objectives[5] = posToId(1, 13);
		board->objectives[15] = posToId(6, 14);

		ADD_WALL(board->cases[posToId(3, 8)], SOUTH);
		ADD_WALL(board->cases[posToId(6, 8)], EAST);
		ADD_WALL(board->cases[posToId(0, 9)], SOUTH);
		ADD_WALL(board->cases[posToId(2, 9)], EAST);
		ADD_WALL(board->cases[posToId(3, 9)], WEST);
		ADD_WALL(board->cases[posToId(3, 9)], NORTH);
		ADD_WALL(board->cases[posToId(7, 9)], NORTH);
		ADD_WALL(board->cases[posToId(0, 10)], NORTH);
		ADD_WALL(board->cases[posToId(6, 10)], SOUTH);
		ADD_WALL(board->cases[posToId(6, 10)], EAST);
		ADD_WALL(board->cases[posToId(7, 10)], WEST);
		ADD_WALL(board->cases[posToId(6, 11)], NORTH);
		ADD_WALL(board->cases[posToId(1, 13)], EAST);
		ADD_WALL(board->cases[posToId(2, 13)], WEST);
		ADD_WALL(board->cases[posToId(2, 13)], SOUTH);
		ADD_WALL(board->cases[posToId(6, 13)], SOUTH);
		ADD_WALL(board->cases[posToId(1, 14)], NORTH);
		ADD_WALL(board->cases[posToId(6, 14)], NORTH);
		ADD_WALL(board->cases[posToId(6, 14)], EAST);
		ADD_WALL(board->cases[posToId(7, 14)], WEST);
		ADD_WALL(board->cases[posToId(4, 15)], EAST);
		ADD_WALL(board->cases[posToId(5, 15)], WEST);

		return;
	}

	if (pos == 3) {
		board->objectives[10] = posToId(10, 9);
		board->objectives[15] = posToId(14, 9);
		board->objectives[0] = posToId(9, 12);
		board->objectives[5] = posToId(13, 14);

		ADD_WALL(board->cases[posToId(9, 8)], WEST);
		ADD_WALL(board->cases[posToId(10, 8)], SOUTH);
		ADD_WALL(board->cases[posToId(14, 8)], SOUTH);
		ADD_WALL(board->cases[posToId(8, 9)], NORTH);
		ADD_WALL(board->cases[posToId(10, 9)], NORTH);
		ADD_WALL(board->cases[posToId(10, 9)], EAST);
		ADD_WALL(board->cases[posToId(11, 9)], WEST);
		ADD_WALL(board->cases[posToId(13, 9)], EAST);
		ADD_WALL(board->cases[posToId(14, 9)], WEST);
		ADD_WALL(board->cases[posToId(14, 9)], NORTH);
		ADD_WALL(board->cases[posToId(15, 10)], SOUTH);
		ADD_WALL(board->cases[posToId(15, 11)], NORTH);
		ADD_WALL(board->cases[posToId(8, 12)], EAST);
		ADD_WALL(board->cases[posToId(9, 12)], WEST);
		ADD_WALL(board->cases[posToId(9, 12)], SOUTH);
		ADD_WALL(board->cases[posToId(9, 13)], NORTH);
		ADD_WALL(board->cases[posToId(13, 14)], SOUTH);
		ADD_WALL(board->cases[posToId(13, 14)], EAST);
		ADD_WALL(board->cases[posToId(14, 14)], WEST);
		ADD_WALL(board->cases[posToId(9, 15)], EAST);
		ADD_WALL(board->cases[posToId(10, 15)], WEST);
		ADD_WALL(board->cases[posToId(13, 15)], NORTH);

		return;
	}
}

void constructPart16(Board* board, int pos) {
	if (pos == 0) {
		board->objectives[0] = posToId(3, 1);
		board->objectives[5] = posToId(6, 2);
		board->objectives[10] = posToId(6, 3);
		board->objectives[15] = posToId(4, 6);

		ADD_WALL(board->cases[posToId(3, 0)], SOUTH);
		ADD_WALL(board->cases[posToId(5, 0)], EAST);
		ADD_WALL(board->cases[posToId(6, 0)], WEST);
		ADD_WALL(board->cases[posToId(2, 1)], EAST);
		ADD_WALL(board->cases[posToId(3, 1)], WEST);
		ADD_WALL(board->cases[posToId(3, 1)], NORTH);
		ADD_WALL(board->cases[posToId(5, 2)], EAST);
		ADD_WALL(board->cases[posToId(6, 2)], WEST);
		ADD_WALL(board->cases[posToId(6, 2)], SOUTH);
		ADD_WALL(board->cases[posToId(6, 3)], NORTH);
		ADD_WALL(board->cases[posToId(6, 3)], EAST);
		ADD_WALL(board->cases[posToId(7, 3)], WEST);
		ADD_WALL(board->cases[posToId(0, 5)], SOUTH);
		ADD_WALL(board->cases[posToId(0, 6)], NORTH);
		ADD_WALL(board->cases[posToId(4, 6)], SOUTH);
		ADD_WALL(board->cases[posToId(4, 6)], EAST);
		ADD_WALL(board->cases[posToId(5, 6)], WEST);
		ADD_WALL(board->cases[posToId(7, 6)], SOUTH);
		ADD_WALL(board->cases[posToId(4, 7)], NORTH);
		ADD_WALL(board->cases[posToId(6, 7)], EAST);

		return;
	}

	if (pos == 1) {
		board->objectives[0] = posToId(14, 3);
		board->objectives[5] = posToId(13, 14);
		board->objectives[10] = posToId(12, 14);
		board->objectives[15] = posToId(9, 4);

		ADD_WALL(board->cases[posToId(9, 0)], EAST);
		ADD_WALL(board->cases[posToId(10, 0)], WEST);
		ADD_WALL(board->cases[posToId(14, 2)], SOUTH);
		ADD_WALL(board->cases[posToId(14, 3)], NORTH);
		ADD_WALL(board->cases[posToId(14, 3)], EAST);
		ADD_WALL(board->cases[posToId(15, 3)], WEST);
		ADD_WALL(board->cases[posToId(8, 4)], EAST);
		ADD_WALL(board->cases[posToId(9, 4)], WEST);
		ADD_WALL(board->cases[posToId(9, 4)], SOUTH);
		ADD_WALL(board->cases[posToId(9, 5)], NORTH);
		ADD_WALL(board->cases[posToId(13, 5)], SOUTH);
		ADD_WALL(board->cases[posToId(15, 5)], SOUTH);
		ADD_WALL(board->cases[posToId(8, 6)], SOUTH);
		ADD_WALL(board->cases[posToId(12, 6)], SOUTH);
		ADD_WALL(board->cases[posToId(12, 6)], EAST);
		ADD_WALL(board->cases[posToId(13, 6)], WEST);
		ADD_WALL(board->cases[posToId(13, 6)], NORTH);
		ADD_WALL(board->cases[posToId(15, 6)], NORTH);
		ADD_WALL(board->cases[posToId(9, 7)], WEST);
		ADD_WALL(board->cases[posToId(12, 7)], NORTH);

		return;
	}

	if (pos == 2) {
		board->objectives[0] = posToId(1, 12);
		board->objectives[5] = posToId(2, 9);
		board->objectives[10] = posToId(3, 9);
		board->objectives[15] = posToId(6, 11);

		ADD_WALL(board->cases[posToId(3, 8)], SOUTH);
		ADD_WALL(board->cases[posToId(6, 8)], EAST);
		ADD_WALL(board->cases[posToId(0, 9)], SOUTH);
		ADD_WALL(board->cases[posToId(2, 9)], SOUTH);
		ADD_WALL(board->cases[posToId(2, 9)], EAST);
		ADD_WALL(board->cases[posToId(3, 9)], WEST);
		ADD_WALL(board->cases[posToId(3, 9)], NORTH);
		ADD_WALL(board->cases[posToId(7, 9)], NORTH);
		ADD_WALL(board->cases[posToId(0, 10)], NORTH);
		ADD_WALL(board->cases[posToId(2, 10)], NORTH);
		ADD_WALL(board->cases[posToId(6, 10)], SOUTH);
		ADD_WALL(board->cases[posToId(6, 11)], NORTH);
		ADD_WALL(board->cases[posToId(6, 11)], EAST);
		ADD_WALL(board->cases[posToId(7, 11)], WEST);
		ADD_WALL(board->cases[posToId(0, 12)], EAST);
		ADD_WALL(board->cases[posToId(1, 12)], WEST);
		ADD_WALL(board->cases[posToId(1, 12)], SOUTH);
		ADD_WALL(board->cases[posToId(1, 13)], NORTH);
		ADD_WALL(board->cases[posToId(5, 15)], EAST);
		ADD_WALL(board->cases[posToId(6, 15)], WEST);

		return;
	}

	if (pos == 3) {
		board->objectives[0] = posToId(12, 14);
		board->objectives[5] = posToId(9, 13);
		board->objectives[10] = posToId(9, 12);
		board->objectives[15] = posToId(11, 9);

		ADD_WALL(board->cases[posToId(9, 8)], WEST);
		ADD_WALL(board->cases[posToId(11, 8)], SOUTH);
		ADD_WALL(board->cases[posToId(8, 9)], NORTH);
		ADD_WALL(board->cases[posToId(10, 9)], EAST);
		ADD_WALL(board->cases[posToId(11, 9)], WEST);
		ADD_WALL(board->cases[posToId(11, 9)], NORTH);
		ADD_WALL(board->cases[posToId(15, 9)], SOUTH);
		ADD_WALL(board->cases[posToId(15, 10)], NORTH);
		ADD_WALL(board->cases[posToId(8, 12)], EAST);
		ADD_WALL(board->cases[posToId(9, 12)], WEST);
		ADD_WALL(board->cases[posToId(9, 12)], SOUTH);
		ADD_WALL(board->cases[posToId(9, 13)], NORTH);
		ADD_WALL(board->cases[posToId(9, 13)], EAST);
		ADD_WALL(board->cases[posToId(10, 13)], WEST);
		ADD_WALL(board->cases[posToId(12, 14)], SOUTH);
		ADD_WALL(board->cases[posToId(12, 14)], EAST);
		ADD_WALL(board->cases[posToId(13, 14)], WEST);
		ADD_WALL(board->cases[posToId(9, 14)], EAST);
		ADD_WALL(board->cases[posToId(10, 14)], WEST);
		ADD_WALL(board->cases[posToId(13, 14)], NORTH);

		return;
	}
}

void constructWalls(Board* board) {
	for (int i = 0; i < 16; i++) {
		ADD_WALL(board->cases[posToId(i, 0)], NORTH);
		ADD_WALL(board->cases[posToId(i, 15)], SOUTH);

		ADD_WALL(board->cases[posToId(0, i)], WEST);
		ADD_WALL(board->cases[posToId(15, i)], EAST);
	}
}