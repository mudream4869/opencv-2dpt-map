#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <string>
#include <functional>
#include <vector>

using std::vector;
using std::string;
using cv::Point2f;

class Win2dptMap {
public:
    
    Win2dptMap(const vector<Point2f>& _pts, std::function<void(int)> callback, const cv::Mat& _bg) :
        pts(_pts), func(callback), win_title("Win 2dpt Mapping"), bg(_bg) {
        for(Point2f& pt : pts) {
            circle(bg, pt, 3, cv::Scalar(0, 255, 0), 3);
        }
        return;
    }

    void show() {
        cv::namedWindow(win_title, 1);
        cv::setMouseCallback(win_title, Win2dptMap::mouseEvent, this);
        imshow(win_title, bg);
        cv::waitKey(0);
        return;
    }

    static void mouseEvent(int event, int x, int y, int flags, void* param) {
        if(event != CV_EVENT_LBUTTONDOWN) {
            return;
        }
        Win2dptMap* _this = (Win2dptMap*) param;
        double dist = 10000000000.;
        int call_index = -1;
        for(int lx = 0;lx < _this->pts.size();lx++) {
            Point2f& pt = _this->pts[lx];
            double cdist = cv::norm(pt - Point2f(x, y));
            if(cdist < dist) {
                dist = cdist;
                call_index = lx;
            }
        }
        if(call_index != -1) {
            _this->func(call_index);
        }
        return;
    }
        
private:
    vector<Point2f> pts;
    std::function<void(int)> func;
    string win_title;
    cv::Mat bg;
};
