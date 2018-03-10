#include <opencv2/opencv.hpp>
#include "Win2dptMap.h"

int main() {
    

    vector<Point2f> pts;
    pts.push_back(Point2f(100, 100));
    pts.push_back(Point2f(100, 200));
    pts.push_back(Point2f(200, 100));
    pts.push_back(Point2f(200, 200));

    cv::Mat img(cv::Mat::zeros(512, 512, CV_64FC3));

    Win2dptMap win2dpt(pts, [](int index){
        printf("%d\n", index);
        return;
    }, img); 

    win2dpt.show();

    return 0;
}
