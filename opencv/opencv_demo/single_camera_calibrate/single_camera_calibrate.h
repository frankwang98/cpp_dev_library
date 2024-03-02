#ifndef CAMERA_CALIBRATED
#define CAMERA_CALIBRATED

#include <io.h>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>

class CameraCalibrated 
{
public:
	CameraCalibrated() {};
	~CameraCalibrated() {};

	/**
	* @brief get_image_list
	* 获取标定文件夹内部的图片路径
	* @param	image_dir_path	输入图片文件夹的路径
	* @param	format			输入图片的文件格式，默认为 .bmp 的格式
	*/
	std::vector<std::string> get_image_list(const char* image_dir_path,
										  const std::string format = ".jpg");
	/**
	* @brief single_camera_calibrated
	* 单相机标定算法(仅用于debug模式)
	* @param	camera_grab_image	输入标定图片数据
	*/
	void single_camera_calibrated(const std::vector<cv::Mat> camera_grab_image);

	/**
	* @brief set_camera_paramter
	* 设置棋盘格的参数
	* @param	pattern_width			输入棋盘格宽度的角点数量
	* @param	pattern_height			输入棋盘格高度的角点数量
	* @param	chessboard_size_mm		输入棋盘格中的小格物理尺寸(mm单位)
	*/
	void set_camera_paramter(const int pattern_width = 9, 
							 const int pattern_height = 8,
							 const double chessboard_size_mm = 30) {
		pattern_size.width = pattern_width;
		pattern_size.height = pattern_height;
		chessboard_size.width = chessboard_size_mm;
		chessboard_size.height = chessboard_size_mm;
		return;
	}

private:
	/**
	* @brief image_corner_detection
	* 单相机标定的图片角点检测函数
	* @param	input_image			输入标定图片数据
	* @param	corners_seq			输出对应的角点
	* @param	object_points		输出角点对应的世界坐标点
	* @return	是否成功检测角点
	*/
	bool image_corner_detection(const cv::Mat  input_image,
		std::vector<std::vector<cv::Point2f>> &corners_seq,
		std::vector<std::vector<cv::Point3f>> &object_points);


	cv::Size pattern_size = cv::Size(9, 8);		///< 棋盘格行列数
	cv::Size chessboard_size = cv::Size(30, 30);	///< 棋盘格物理尺寸
};

#endif //end CAMERA_CALIBRATED
