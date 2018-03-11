#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <string>
#include <functional>
#include <vector>
#include <algorithm>

using std::vector;
using std::string;
using cv::Point2f;

class Win2dptMap {
public:
    
    Win2dptMap(const vector<Point2f>& _pts, std::function<void(int)> callback, const cv::Mat& _bg) :
        pts(_pts), func(callback), win_title("Win 2dpt Mapping"), bg(_bg), select_index(-1) {
        // Scale < Len Limit
        const float width_len_limit = 1024,
                    height_len_limit = 768;
        cv::Size sz = bg.size();
        if(sz.width > width_len_limit or sz.height > height_len_limit) {
            float ratio = std::max(sz.width/width_len_limit, sz.height/height_len_limit);
            int new_w = sz.width/ratio, new_h = sz.height/ratio;
            cv::resize(bg, bg, cv::Size(new_w, new_h));

            for(Point2f& pt : pts) {
                pt /= ratio;
            }
        }
        // Draw pts
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
        Win2dptMap* _this = (Win2dptMap*) param;
        double dist = 6.1;
        int pt_index = -1;
        for(int lx = 0;lx < _this->pts.size();lx++) {
            Point2f& pt = _this->pts[lx];
            double cdist = cv::norm(pt - Point2f(x, y));
            if(cdist < dist) {
                dist = cdist;
                pt_index = lx;
            }
        }

        if(_this->select_index != -1) {
            circle(_this->bg, _this->pts[_this->select_index], 3, cv::Scalar(0, 255, 0), 3);
            imshow(_this->win_title, _this->bg);
        }

        if(pt_index != -1) {
            circle(_this->bg, _this->pts[pt_index], 4, cv::Scalar(0, 0, 255), 2);
            _this->select_index = pt_index;
            imshow(_this->win_title, _this->bg);
            if(event == CV_EVENT_LBUTTONDOWN) {
                _this->func(pt_index);
            }
        }
        return;
    }
        
private:
    vector<Point2f> pts;
    std::function<void(int)> func;
    string win_title;
    cv::Mat bg;
    
    // GUI
    int select_index;
};
