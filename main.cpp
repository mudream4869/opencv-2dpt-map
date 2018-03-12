#include <opencv2/opencv.hpp>
#include <cstdlib>

#include "Win2dptMap.h"

int main() {
    vector<Point2f> pts;

    int width = 1000, height = 2000;

    for(int lx = 0;lx < 100;lx++) {
        pts.push_back(Point2f(std::rand()%height, std::rand()%width));
    }

    cv::Mat img(cv::Mat::zeros(1000, 2000, CV_64FC3));

    Win2dptMap win2dpt(pts, [](int index){
        printf("%d\n", index);
        return;
    }, img, 2); 

    win2dpt.show();

    return 0;
}
