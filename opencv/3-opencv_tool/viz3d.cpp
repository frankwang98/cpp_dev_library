#include <opencv2/viz.hpp>
#include <opencv2/calib3d.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main()
{
    /// Create a window
    viz::Viz3d myWindow("Coordinate Frame");

    /// Add coordinate axes
    myWindow.showWidget("Coordinate Widget", viz::WCoordinateSystem());

    /// Add line to represent (1,1,1) axis
    viz::WLine axis(Point3f(-1.0f, -1.0f, -1.0f), Point3f(1.0f, 1.0f, 1.0f));
    axis.setRenderingProperty(viz::LINE_WIDTH, 4.0);
    myWindow.showWidget("Line Widget", axis);

    /// Construct a cube widget
    viz::WCube cube_widget(Point3f(0.5, 0.5, 0.0), Point3f(0.0, 0.0, -0.5), true, viz::Color::blue());
    cube_widget.setRenderingProperty(viz::LINE_WIDTH, 4.0);

    /// Display widget (update if already displayed)
    myWindow.showWidget("Cube Widget", cube_widget);

    /// Rodrigues vector
    Mat rot_vec = Mat::zeros(1, 3, CV_32F);
    float translation_phase = 0.0, translation = 0.0;
    while (!myWindow.wasStopped())
    {
        /* Rotation using rodrigues */
        /// Rotate around (1,1,1)
        rot_vec.at<float>(0, 0) += CV_PI * 0.01f;
        rot_vec.at<float>(0, 1) += CV_PI * 0.01f;
        rot_vec.at<float>(0, 2) += CV_PI * 0.01f;

        /// Shift on (1,1,1)
        translation_phase += CV_PI * 0.01f;
        translation = sin(translation_phase);

        Mat rot_mat;
        Rodrigues(rot_vec, rot_mat);

        /// Construct pose
        Affine3f pose(rot_mat, Vec3f(translation, translation, translation));

        myWindow.setWidgetPose("Cube Widget", pose);

        myWindow.spinOnce(1, true);
    }

    return 0;
}