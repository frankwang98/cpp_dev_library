#include "single_camera_calibrate.h"


std::vector<std::string> CameraCalibrated::get_image_list(const char* image_dir_path,
														  const std::string format) {
	std::vector<std::string> image_list;
	std::string image_dir_pathStr = (std::string)image_dir_path;
	std::string buffer = image_dir_pathStr + "/*" + format;
	_finddata_t c_file;												// 存放文件名的结构体
	intptr_t hFile;
	hFile = _findfirst(buffer.c_str(), &c_file);					// 找第一个文件命
	if (hFile == -1L)												// 检查文件夹目录下存在需要查找的文件
		printf("No %s files in current directory!\n", format);
	else {
		std::string full_file_path;
		do {
			full_file_path.clear();
			full_file_path = image_dir_pathStr + "/" + c_file.name;
			image_list.push_back(full_file_path);
		} while (_findnext(hFile, &c_file) == 0);
		_findclose(hFile);
	}
	return image_list;
}

void CameraCalibrated::single_camera_calibrated(const std::vector<cv::Mat> camera_grab_image) {

	if (camera_grab_image.size() == 0) {
		printf("No picture found, please re-enter the calibration picture \n");
		return;
	}
	cv::Size image_size;
	if (camera_grab_image[0].data) {
		image_size = camera_grab_image[0].size();
	}
	else { printf("No picture found, please re-enter the calibration picture \n"); return; };
	cv::Mat camera_matrix = cv::Mat(3, 3, CV_32FC1, cv::Scalar::all(0));
	cv::Mat distCoeffs_matrix = cv::Mat(1, 5, CV_32FC1, cv::Scalar::all(0));
	std::vector<cv::Mat> rvec;
	std::vector<cv::Mat> tvec;
	std::vector<std::vector<cv::Point3f>> object_points;
	std::vector<std::vector<cv::Point2f>> corners_seq;
	for (size_t i = 0; i < camera_grab_image.size(); i++) {
		cv::Mat grab_image = camera_grab_image[i].clone();
		image_corner_detection(grab_image, corners_seq, object_points);
		cv::namedWindow("cornersframe", 2);
		cv::imshow("cornersframe", grab_image);
		cv::waitKey(1);
	}
	cv::destroyWindow("cornersframe");
	if (object_points.size() == 0) {
		printf("No corner points on the image were found. Please detect the image again. \n");
		return;
	}
	printf("Start calculating the camera_matrix of a single camera. \n");
	cv::TermCriteria criteria = cv::TermCriteria(cv::TermCriteria::COUNT + cv::TermCriteria::EPS, 50, DBL_EPSILON);
	calibrateCamera(object_points, corners_seq, image_size,
					camera_matrix, distCoeffs_matrix,
					rvec, tvec, 0, criteria);
	printf("The camera internal parameter matrix is: \n");
	std::cout << camera_matrix << std::endl;
	printf("The camera distortion matrix is: \n");
	std::cout << distCoeffs_matrix << std::endl;
	cv::FileStorage resultStore("./data/getCameraParams.txt", cv::FileStorage::APPEND);
	resultStore << "camera_matrix" << camera_matrix;
	resultStore << "camera_distCoeffs_matrix" << distCoeffs_matrix;
	resultStore.release();
	return;
}

bool CameraCalibrated::image_corner_detection(const cv::Mat input_image,
											  std::vector<std::vector<cv::Point2f>> &corners_seq,
											  std::vector<std::vector<cv::Point3f>> &object_points) {

	bool is_detection = false;
	std::vector<cv::Point2f> corners; 
	cv::Mat input_image_gray;
	cv::cvtColor(input_image, input_image_gray, cv::COLOR_BGR2GRAY);
	//cv::equalizeHist(input_image_gray, input_image);
	//cv::GaussianBlur(input_image, input_image, Size(7, 7), 1);
	if (cv::findChessboardCorners(input_image_gray, pattern_size, corners, 0)) {
		cv::TermCriteria criteria = cv::TermCriteria(cv::TermCriteria::EPS + cv::TermCriteria::MAX_ITER, 30, 0.001);
		cv::cornerSubPix(input_image_gray, corners, cv::Size(23, 23), cv::Size(-1, -1), criteria);
		corners_seq.push_back(corners);	// 存入角点序列
		cv::drawChessboardCorners(input_image, pattern_size, corners, true);
		is_detection = true;
		std::vector<cv::Point3f> real_point_set;
		for (int i = 0; i < pattern_size.height; i++) {
			for (int j = 0; j < pattern_size.width; j++) {
				cv::Point3d realPoint;
				realPoint.x = j * chessboard_size.width;
				realPoint.y = i * chessboard_size.height;
				realPoint.z = 0;
				real_point_set.push_back(realPoint);
			}
		}
		object_points.push_back(real_point_set);
		return is_detection;
	}
	printf("Corner detection failed.\n");
	return is_detection;
};
