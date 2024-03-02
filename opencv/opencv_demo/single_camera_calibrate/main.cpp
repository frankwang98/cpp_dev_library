#include "single_camera_calibrate.h"

int main(int argc, char ** argv) {
	CameraCalibrated cc;
	std::string camera_image_dir_path = "./data";
	cc.set_camera_paramter(10,7,30);
	std::vector<std::string> image_list_path;
	image_list_path = cc.get_image_list(camera_image_dir_path.c_str(),".bmp");
	std::vector<cv::Mat> image_calibrated;
	for (size_t i = 0; i < image_list_path.size(); i++){
		cv::Mat image = cv::imread(image_list_path[i]);
		if (!image.data){
			printf("no picture imread ( %s ). \n", image_list_path[i].c_str());
			continue;
		}
		image_calibrated.push_back(image);
	}
	cc.single_camera_calibrated(image_calibrated);
	return 0;
}
