#include <vector>
#include <math.h>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <string>
#include <unordered_map>
#include <set>
#include <map>
#include <unordered_set>
#include <numeric>
using namespace std;


double NormalizeAngle(double angle) {
    double a = fmod(angle + M_PI, 2.0 * M_PI);
    if (a < 0.0) 
    {
        a += (2.0 * M_PI);
    }
    return a - M_PI;
}
// 定义直线参数结构体  
struct LinePara
{
	// double k;
	// double b;
    float k;
	float b;
};

struct Pose {
    float x_rig;
    float y_rig;
    float length;
    float width;
    float yaw;
    };
    

class Point2f{
public:
    double x;
    double y;
    Point2f(){};
    ~Point2f(){};
    Point2f(double x, double y):x(x),y(y){}
    Point2f(const Point2f& other):x(other.x),y(other.y){}
    Point2f(Point2f&& other):x(std::move(other.x)),y(std::move(other.y)){

    } //移动构造函数
    Point2f& operator=(const Point2f& other){
        if(this == &other) return *this;
        this->x = other.x;
        this->y = other.y;
        return *this;
    } // 赋值操作符
    Point2f& operator=(Point2f&& other){
        *this = std::move(other);
        return *this;
    } //移动赋值操作符

    // bool operator<(const Point2f other) {
    //     if (this->x < other.x) return true;
    //     return false;
    // }
    // bool operator<(Point2f other) {
    //     if (this->x < other.x) return true;
    //     return false;
    // }
};

struct classcomp {
  bool operator() (const Point2f& lhs, const Point2f& rhs) const
  {return lhs.x < rhs.x;}
};

struct Line {
    Point2f p1;
    Point2f p2;
    Line(double x1, double y1, double x2, double y2) : p1(x1,y1), p2(x2,y2) {}
};

typedef struct{
    float x;
    float y;
    float w;
    float h;
    float theta;
    // float score;
    // int label;
}detection;


// 第一步找到最左边的点
int find_leftmost_point(vector<Point2f> intersectingRegion)
{
    int index = 0;
    Point2f* tmp = &intersectingRegion[0];
    for(int i=1; i<intersectingRegion.size(); i++)
    {
        if(intersectingRegion[i].x > tmp->x || intersectingRegion[i].x == tmp->x && intersectingRegion[i].y > tmp->y)
        {
            tmp = &intersectingRegion[i];
            index = i;
        }
    }
    return index;
}

void sort_points(vector<Point2f>& intersectingRegion) {
    // Point2f tmp = intersectingRegion[0];
    // std::cout << "leftpoint: " << tmp->x << "," << tmp->y << std::endl;
    Point2f sumP(0,0);
    // for(int i=1; i<intersectingRegion.size(); i++)
    // {
    //     if(intersectingRegion[i].x > tmp.x || intersectingRegion[i].x == tmp.x && intersectingRegion[i].y > tmp.y)
    //     {
    //         tmp = intersectingRegion[i];
    //     }
    // }

    for(int i=0; i<intersectingRegion.size(); i++)
    {
        sumP.x += intersectingRegion[i].x;
        sumP.y += intersectingRegion[i].y;
    }
    sumP.x = sumP.x /intersectingRegion.size();
    sumP.y = sumP.y /intersectingRegion.size();
    std::cout << fixed;
    std::cout << "avg.x: (" << sumP.x << "," << sumP.y<<")"<< std::endl;

    std::map<float,Point2f> map;
    std::cout << "atan" << std::endl;
    for(int i=0; i<intersectingRegion.size(); i++) {
        std::cout << " (" << (float)(intersectingRegion[i].x - sumP.x) << ","<< (float)(intersectingRegion[i].y - sumP.y) << ")" << std::endl;
        map.emplace(atan2(intersectingRegion[i].y - sumP.y, intersectingRegion[i].x - sumP.x), std::move(intersectingRegion[i]));
    }

    intersectingRegion.clear();
    for (auto i : map) {
        std::cout <<" sort_map: " << i.first << "(" << i.second.x <<"," << i.second.y << ")" << std::endl;
        intersectingRegion.emplace_back(std::move(i.second));
    }
    // intersectingRegion.emplace_back(std::move(tmp));
    // std::cout <<" sort_map: 0" <<  "(" << tmp.x <<"," << tmp.y << ")" << std::endl;
    std::cout << "map: " << map.size() << std::endl;
}



// 计算 |p1 p2| X |p1 p|
float GetCross1(Point2f& p1, Point2f& p2,Point2f& p)
{
    // std::cout << "GetCross1: (" << p1.x << "," << p1.y << "),("<< p2.x << "," << p2.y << ") ans:" << (p2.x - p1.x) * (p.y - p1.y) -(p.x - p1.x) * (p2.y - p1.y)<<  std::endl;
	return (p2.x - p1.x) * (p.y - p1.y) -(p.x - p1.x) * (p2.y - p1.y);
}
// 判断点是否在5X5 以原点为左下角的正方形内（便于测试）
bool IsPointInMatrix(Point2f& p1, Point2f& p2,Point2f& p4, Point2f& p3,Point2f& p)
{
	return GetCross1(p1,p2,p) * GetCross1(p3,p4,p) >= 0 && GetCross1(p2,p3,p) * GetCross1(p4,p1,p) >= 0;
}
// 计算 |p1 p2| X |p1 p|
bool IsPointInMatrix(Line& l1, Line& l2, Point2f& p)
{
    // std::cout<< "l1: " << ((l1.p2.x - l1.p1.x) * (p.y - l1.p1.y) - (p.x - l1.p1.x) * (l1.p2.y - l1.p1.y)) << std::endl;
    // std::cout << " l2: "<< ((l2.p2.x - l2.p1.x) * (p.y - l2.p1.y) - (p.x - l2.p1.x) * (l2.p2.y - l2.p1.y)) << std::endl;
	return ((l1.p2.x - l1.p1.x) * (p.y - l1.p1.y) - (p.x - l1.p1.x) * (l1.p2.y - l1.p1.y)) * ((l2.p2.x - l2.p1.x) * (p.y - l2.p1.y) - (p.x - l2.p1.x) * (l2.p2.y - l2.p1.y)) >= 0;
}


// 获取直线参数  
void getLinePara(const Line& line, LinePara& LP) {
	double m = 0;
 
	// 计算分子  
	m = line.p2.x - line.p1.x;
 
	if (0 == m)
	{
		LP.k = 10000.0;
		LP.b = line.p1.y - LP.k * line.p1.x;
	}
	else
	{
		LP.k = (line.p2.y - line.p1.y) / (line.p2.x - line.p1.x);
		LP.b = line.p1.y - LP.k * line.p1.x;
	}
}

// 获取交点  
bool getCross(const Line& line1, const Line& line2,  Point2f& pt){
	LinePara para1, para2;
	getLinePara(line1, para1);
	getLinePara(line2, para2);
    std::cout << "line1: "<< line1.p1.x <<"," << line1.p1.y << "," << line1.p2.x << "," << line1.p2.y << std::endl;
    std::cout << "line2: "<< line2.p1.x <<"," << line2.p1.y << "," << line2.p2.x << "," << line2.p2.y << std::endl;
    std::cout << "para1(" << para1.k << "," << para1.b << ")" << "para2(" << para2.k << "," << para2.b<< ")" << std::endl;
	// 判断是否平行  
	if (abs(para1.k - para2.k) > 0.5)
	{
		pt.x = (para2.b - para1.b) / (para1.k - para2.k);
		pt.y = para1.k * pt.x + para1.b;
        std::cout << "get jiaodian: " << pt.x << "," << pt.y << std::endl;
		return true;
	}
	else
	{
        std::cout <<"line pingxing..." << std::endl;
		return false;
	}
}

bool getvalidCross(const Line& line1, const Line& line2,  Point2f& pt) {

float epsilon = 1e-3;
    std::cout << "epsilon: " << epsilon << ";" << -0.000064 * 0.776110<< std::endl;
    std::cout << "(pt.x-line1.p1.x): " << (pt.x-line1.p1.x) << " (pt.x-line1.p2.x): " << (pt.x-line1.p2.x) 
                << " (pt.y-line1.p1.y): " << (pt.y-line1.p1.y) << " (pt.x-line1.p2.y): " << (pt.y-line1.p2.y)  << std::endl;
    std::cout << "(pt.x-line2.p1.x): " << (pt.x-line2.p1.x) << " (pt.x-line2.p2.x): " << (pt.x-line2.p2.x)
                << " (pt.y-line2.p1.y): " << (pt.y-line2.p1.y)  << " (pt.x-line2.p2.y): " << (pt.x-line2.p2.y)<< std::endl;
        std::cout << "getvalidCross failed:" << ((pt.x-line1.p1.x)*(pt.x-line1.p2.x) ) <<"," <<((pt.y-line1.p1.y)*(pt.y-line1.p2.y) )<< "; "
                 << (pt.x-line2.p1.x)*(pt.x-line2.p2.x) << "," << (pt.y-line2.p1.y)*(pt.y-line2.p2.y) << std::endl;
    if (((pt.x-line1.p1.x)*(pt.x-line1.p2.x) <= epsilon)
        && (pt.y-line1.p1.y)*(pt.y-line1.p2.y) <= epsilon 
        && (pt.x-line2.p1.x)*(pt.x-line2.p2.x) <= epsilon 
        && (pt.y-line2.p1.y)*(pt.y-line2.p2.y) <= epsilon) {
        std::cout << "getvalidCross"<< std::endl;
        return true;
    } else {
        float a = (pt.y-line1.p1.y);
        float b = pt.y-line1.p2.y;
        std::cout << "a: " << a << " b: " << b << " a*b " << a*b << std::endl;

        std::cout << "(pt.x-line1.p1.x): " << (pt.x-line1.p1.x) << " (pt.x-line1.p2.x): " << (pt.x-line1.p2.x) 
                    << " (pt.y-line1.p1.y): " << (pt.y-line1.p1.y) << " (pt.x-line1.p2.y): " << (pt.y-line1.p2.y)  << std::endl;
        std::cout << "(pt.x-line2.p1.x): " << (pt.x-line2.p1.x) << " (pt.x-line2.p2.x): " << (pt.x-line2.p2.x)
                   << " (pt.y-line2.p1.y): " << (pt.y-line2.p1.y)  << " (pt.x-line2.p2.y): " << (pt.x-line2.p2.y)<< std::endl;
        std::cout << "getvalidCross failed:" << ((pt.x-line1.p1.x)*(pt.x-line1.p2.x) ) <<"," <<((pt.y-line1.p1.y)*(pt.y-line1.p2.y) )<< "; "
                 << (pt.x-line2.p1.x)*(pt.x-line2.p2.x) << "," << (pt.y-line2.p1.y)*(pt.y-line2.p2.y) << std::endl;
    }



    return false;
}

bool intersection(const Line &l1, const Line &l2, std::vector<Point2f>& vecs)
{
    // std::cout << "l1.p1.x: " << l1.p1.x << "," << l1.p1.y << ", p2.x: " << l1.p2.x << "," << l1.p2.y <<std::endl;
    // std::cout << "l1.p1.x: " << l2.p1.x << "," << l2.p1.y << ", p2.x: " << l2.p2.x << "," << l2.p2.y <<std::endl;
    //快速排斥实验
    if ((l1.p1.x > l1.p2.x ? l1.p1.x : l1.p2.x) < (l2.p1.x < l2.p2.x ? l2.p1.x : l2.p2.x) ||
        (l1.p1.y > l1.p2.y ? l1.p1.y : l1.p2.y) < (l2.p1.y < l2.p2.y ? l2.p1.y : l2.p2.y) ||
        (l2.p1.x > l2.p2.x ? l2.p1.x : l2.p2.x) < (l1.p1.x < l1.p2.x ? l1.p1.x : l1.p2.x) ||
        (l2.p1.y > l2.p2.y ? l2.p1.y : l2.p2.y) < (l1.p1.y < l1.p2.y ? l1.p1.y : l1.p2.y))
    {
        // std::cout << "kuaisupaicha" << std::endl;
        return false;
    }
    //跨立实验
    if ((((l1.p1.x - l2.p1.x)*(l2.p2.y - l2.p1.y) - (l1.p1.y - l2.p1.y)*(l2.p2.x - l2.p1.x))*
        ((l1.p2.x - l2.p1.x)*(l2.p2.y - l2.p1.y) - (l1.p2.y - l2.p1.y)*(l2.p2.x - l2.p1.x))) > 0 ||
        (((l2.p1.x - l1.p1.x)*(l1.p2.y - l1.p1.y) - (l2.p1.y - l1.p1.y)*(l1.p2.x - l1.p1.x))*
        ((l2.p2.x - l1.p1.x)*(l1.p2.y - l1.p1.y) - (l2.p2.y - l1.p1.y)*(l1.p2.x - l1.p1.x))) > 0)
    {
        // std::cout << "kuali" << std::endl;
        return false;
    }
    
    Point2f pt;
    if (getCross(l1, l2, pt)) {
        vecs.emplace_back(pt);
    }

    return true;
}

float contourArea(std::set<Point2f,classcomp>& vecs) {
    if (vecs.empty()) return 0.;
    double a00 = 0;
    Point2f prev =*(vecs.rbegin()); // vecs[vecs.size()-1];
    for (auto& i : vecs) {
        a00 += (double)prev.x*i.y - (double)prev.y*i.x;
        std::cout << " value:" <<(double)prev.x*i.y - (double)prev.y*i.x << std::endl;
        prev = i;
    }
    a00 *= 0.5;
    return std::fabs(a00);
}

bool IsCross(const Pose& pre, const Pose& cur, const float& ego_yaw, std::vector<Point2f>& vecs) {        
    float yaw_pre = NormalizeAngle(pre.yaw - ego_yaw);
    float yaw_cur = NormalizeAngle(cur.yaw - ego_yaw);

    std::cout << "pre jiaodu: " << (yaw_pre)/M_PI*180 <<  " cur jiaod: " << (yaw_cur)/M_PI*180 << std::endl;
    std::cout << "yaw_pre: " << yaw_pre << " yaw_cur: " << yaw_cur << " M_PI " << M_PI << std::endl;
    
        std::vector<Line> pre_vec = {
          {pre.x_rig + pre.length/2*std::cos(yaw_pre) - pre.width/2*std::sin(yaw_pre), pre.y_rig + pre.length/2*std::sin(yaw_pre) + pre.width/2*std::cos(yaw_pre),//A1
          pre.x_rig + pre.length/2*std::cos(yaw_pre) + pre.width/2*std::sin(yaw_pre), pre.y_rig + pre.length/2*std::sin(yaw_pre) - pre.width/2*std::cos(yaw_pre)},//B1
          {pre.x_rig + pre.length/2*std::cos(yaw_pre) - pre.width/2*std::sin(yaw_pre), pre.y_rig + pre.length/2*std::sin(yaw_pre) + pre.width/2*std::cos(yaw_pre),//A1
          pre.x_rig - pre.length/2*std::cos(yaw_pre) - pre.width/2*std::sin(yaw_pre), pre.y_rig - pre.length/2*std::sin(yaw_pre) + pre.width/2*std::cos(yaw_pre)},//D1
          {pre.x_rig - pre.length/2*std::cos(yaw_pre) - pre.width/2*std::sin(yaw_pre), pre.y_rig - pre.length/2*std::sin(yaw_pre) + pre.width/2*std::cos(yaw_pre),//D1
          pre.x_rig - pre.length/2*std::cos(yaw_pre) + pre.width/2*std::sin(yaw_pre), pre.y_rig - pre.length/2*std::sin(yaw_pre) - pre.width/2*std::cos(yaw_pre)},//C1
          {pre.x_rig + pre.length/2*std::cos(yaw_pre) + pre.width/2*std::sin(yaw_pre), pre.y_rig + pre.length/2*std::sin(yaw_pre) - pre.width/2*std::cos(yaw_pre),//B1
          pre.x_rig - pre.length/2*std::cos(yaw_pre) + pre.width/2*std::sin(yaw_pre), pre.y_rig - pre.length/2*std::sin(yaw_pre) - pre.width/2*std::cos(yaw_pre)}//C1
          };
          
        std::vector<Line> cur_vec = {
          {cur.x_rig + cur.length/2*std::cos(yaw_cur) - cur.width/2*std::sin(yaw_cur), cur.y_rig + cur.length/2*std::sin(yaw_cur) + cur.width/2*std::cos(yaw_cur),//A1
          cur.x_rig + cur.length/2*std::cos(yaw_cur) + cur.width/2*std::sin(yaw_cur), cur.y_rig + cur.length/2*std::sin(yaw_cur) - cur.width/2*std::cos(yaw_cur)},//B1
          {cur.x_rig + cur.length/2*std::cos(yaw_cur) - cur.width/2*std::sin(yaw_cur), cur.y_rig + cur.length/2*std::sin(yaw_cur) + cur.width/2*std::cos(yaw_cur),//A1
          cur.x_rig - cur.length/2*std::cos(yaw_cur) - cur.width/2*std::sin(yaw_cur), cur.y_rig - cur.length/2*std::sin(yaw_cur) + cur.width/2*std::cos(yaw_cur)},//D1
          {cur.x_rig - cur.length/2*std::cos(yaw_cur) - cur.width/2*std::sin(yaw_cur), cur.y_rig - cur.length/2*std::sin(yaw_cur) + cur.width/2*std::cos(yaw_cur),//D1
          cur.x_rig - cur.length/2*std::cos(yaw_cur) + cur.width/2*std::sin(yaw_cur), cur.y_rig - cur.length/2*std::sin(yaw_cur) - cur.width/2*std::cos(yaw_cur)},//C1
          {cur.x_rig + cur.length/2*std::cos(yaw_cur) + cur.width/2*std::sin(yaw_cur), cur.y_rig + cur.length/2*std::sin(yaw_cur) - cur.width/2*std::cos(yaw_cur),//B1
          cur.x_rig - cur.length/2*std::cos(yaw_cur) + cur.width/2*std::sin(yaw_cur), cur.y_rig - cur.length/2*std::sin(yaw_cur) - cur.width/2*std::cos(yaw_cur)}//C1
          };     
        

    std::string prestr("point_pre");
    prestr += "(" + std::to_string(pre.x_rig + pre.length/2*std::cos(yaw_pre) - pre.width/2*std::sin(yaw_pre)) 
            +"," + std::to_string(pre.y_rig + pre.length/2*std::sin(yaw_pre) + pre.width/2*std::cos(yaw_pre)) + "),"//A
            
            +"(" + std::to_string(pre.x_rig + pre.length/2*std::cos(yaw_pre) + pre.width/2*std::sin(yaw_pre)) 
            +"," + std::to_string(pre.y_rig + pre.length/2*std::sin(yaw_pre) - pre.width/2*std::cos(yaw_pre)) + "),"//B
            
            + "(" + std::to_string(pre.x_rig - pre.length/2*std::cos(yaw_pre) + pre.width/2*std::sin(yaw_pre)) 
            +"," + std::to_string(pre.y_rig - pre.length/2*std::sin(yaw_pre) - pre.width/2*std::cos(yaw_pre)) + "),"//C
            
            +"(" + std::to_string(pre.x_rig - pre.length/2*std::cos(yaw_pre) - pre.width/2*std::sin(yaw_pre)) 
            +"," + std::to_string(pre.y_rig - pre.length/2*std::sin(yaw_pre) + pre.width/2*std::cos(yaw_pre)) + ")";//D
    std::string curstr("point_cur");
  curstr += "(" + std::to_string(cur.x_rig + cur.length/2*std::cos(yaw_cur) - cur.width/2*std::sin(yaw_cur)) 
            +"," + std::to_string(cur.y_rig + cur.length/2*std::sin(yaw_cur) + cur.width/2*std::cos(yaw_cur)) + "),"//A
            
            +"(" + std::to_string(cur.x_rig + cur.length/2*std::cos(yaw_cur) + cur.width/2*std::sin(yaw_cur)) 
            +"," + std::to_string(cur.y_rig + cur.length/2*std::sin(yaw_cur) - cur.width/2*std::cos(yaw_cur)) + "),"//B
            
            + "(" + std::to_string(cur.x_rig - cur.length/2*std::cos(yaw_cur) + cur.width/2*std::sin(yaw_cur)) 
            +"," + std::to_string(cur.y_rig - cur.length/2*std::sin(yaw_cur) - cur.width/2*std::cos(yaw_cur)) + "),"//C
            
            +"(" + std::to_string(cur.x_rig - cur.length/2*std::cos(yaw_cur) - cur.width/2*std::sin(yaw_cur)) 
            +"," + std::to_string(cur.y_rig - cur.length/2*std::sin(yaw_cur) + cur.width/2*std::cos(yaw_cur)) + ")";//D
    std::cout << "IsCross:preid " << " pose: "<< prestr << "\n" << " pose: " << curstr << std::endl;

// std::vector<Line> pre_vec = {{7.097693,4.513980},{7.090459,6.321583},{11.562720,6.339480},{11.569955,4.531877}};//(9.330207,5.426730),(7.097693,4.513980),(7.090459,6.321583),(11.562720,6.339480),(11.569955,4.531877)
// std::vector<Line> cur_vec = {{6.820826,4.512929},{6.813592,6.320532},{11.285853,6.338428},11.293088,4.530826};//(9.053340,5.425679),(6.820826,4.512929),(6.813592,6.320532),(11.285853,6.338428),(11.293088,4.530826)

    std::cout << "prevec[0,2](" <<pre_vec[0].p1.x << "," << pre_vec[0].p1.y <<"),(" <<pre_vec[0].p2.x << "," << pre_vec[0].p2.y <<"),(" <<pre_vec[2].p1.x << "," << pre_vec[2].p1.y <<"),(" <<pre_vec[2].p2.x << "," << pre_vec[2].p2.y <<")" << "]" << std::endl;
    std::cout << "curvec[0,2](" <<cur_vec[0].p1.x << "," << cur_vec[0].p1.y <<"),(" <<cur_vec[0].p2.x << "," << cur_vec[0].p2.y <<"),(" <<cur_vec[2].p1.x << "," << cur_vec[2].p1.y <<"),(" <<cur_vec[2].p2.x << "," << cur_vec[2].p2.y <<")" << "]" << std::endl;
    std::set<Point2f,classcomp> sets;
    for (auto& pre : pre_vec) {
      for (auto& cur : cur_vec) {
        if (intersection(pre,cur,vecs)) {
            std::cout << "xiangjiao: [(" <<cur.p1.x << "," << cur.p1.y <<"),(" <<cur.p2.x << "," << cur.p2.y <<"),(" <<pre.p1.x << "," << pre.p1.y <<"),(" <<pre.p2.x << "," << pre.p2.y <<")" << "]" << std::endl;
            Point2f p;
            if (IsPointInMatrix(pre_vec[0].p1,pre_vec[0].p2, pre_vec[2].p1,pre_vec[2].p2, cur.p1)) {
                vecs.emplace_back(cur.p1);
                sets.insert(cur.p1);
                
                std::cout << "input cur.p1:( " << cur.p1.x << "," << cur.p1.y << ")" << std::endl;
            }
            if (IsPointInMatrix(pre_vec[0].p1,pre_vec[0].p2, pre_vec[2].p1,pre_vec[2].p2, cur.p2)) {
                vecs.emplace_back(cur.p2);
                sets.emplace(cur.p2);
                std::cout << "input cur.p2:( " << cur.p2.x << "," << cur.p2.y << ")" << std::endl;
            }
            if (IsPointInMatrix(cur_vec[0].p1,cur_vec[0].p2, cur_vec[2].p1,cur_vec[2].p2, pre.p1)) {
                vecs.emplace_back(pre.p1);
                sets.emplace(pre.p1);
                std::cout << "input pre.p1:( " << pre.p1.x << "," << pre.p1.y << ")" << std::endl;
            }
            if (IsPointInMatrix(cur_vec[0].p1,cur_vec[0].p2, cur_vec[2].p1,cur_vec[2].p2, pre.p2)) {
                vecs.emplace_back(pre.p2);
                sets.emplace(pre.p2);
                std::cout << "input pre.p2:( " << pre.p2.x << "," << pre.p2.y << ")" << std::endl;
            }
        }
      }
    }
    // std::cout << "sets:>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> " << std::endl;
    // for (auto i :sets) {
    //     std:cout << "(" << i.x << ","<< i.y << ")" << std::endl;
    // }
    // std::cout << "set_area: " << contourArea(sets) << std::endl;
    // std::cout << "sets:>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> " << std::endl;
    if (vecs.empty()) return false;
    return true;
}

float AngleOfLines(const Pose& pre, const Pose& cur, const float& ego_yaw) {
  float deltax = pre.x_rig - cur.x_rig;
  float deltay = pre.y_rig - cur.y_rig;
  float deltax1 = -pre.width*std::sin(NormalizeAngle(pre.yaw - ego_yaw));
  float deltay1 = pre.width*std::cos(NormalizeAngle(pre.yaw - ego_yaw));
  
  float t =  (deltax * deltax1 + deltay * deltay1) / std::hypot(deltax, deltay) / std::hypot(deltax1, deltay1);
  std::cout << "("<< deltax << "," << deltay << ");(" << deltax1 <<"," << deltay1 << ") t: " <<t << " acos: " <<std::acos(t)<< std::endl;
  float angle = std::acos(t) * (180 / M_PI);
  return angle;
}


// 第一步找到最左边的点
int find_leftmost_point(vector<cv::Point2f> intersectingRegion)
{
    int index = 0;
    float tmp = intersectingRegion[0].x;
    for(int i=1; i<intersectingRegion.size(); i++)
    {
        if(intersectingRegion[i].x < tmp)
        {
            tmp = intersectingRegion[i].x;
            index = i;
        }
    }
    return index;
}
 
//第二步对所有点进行排序
vector<cv::Point2f> sort_points(vector<cv::Point2f> intersectingRegion)
{
    vector<cv::Point2f> sort_intersectingRegion;
    int leftmost_index = find_leftmost_point(intersectingRegion);
 
    vector<float> arctan;
    for(int i=0; i<intersectingRegion.size(); i++)
    {
        arctan.push_back(atan2(intersectingRegion[i].y - intersectingRegion[leftmost_index].y, intersectingRegion[i].x - intersectingRegion[leftmost_index].x));
    }
 
    vector<int> index;
    for(int i=0; i<arctan.size(); i++)
    {
        index.push_back(i);
    }
    
    sort(index.begin(), index.end(), [&](const int& a, const int& b) {return (arctan[a] < arctan[b]);});
    
    for(int i=0; i<index.size(); i++)
    {
        sort_intersectingRegion.push_back(intersectingRegion[index[i]]);
    }
    return sort_intersectingRegion;
}

float contourArea(std::vector<Point2f>& vecs) {
    if (vecs.empty()) return 0.;
    double a00 = 0;
    Point2f prev = vecs[vecs.size()-1];
    for (int i = 0; i < vecs.size(); ++i) {
        a00 += (double)prev.x*vecs[i].y - (double)prev.y*vecs[i].x;
        std::cout << "i: " << i << " value:" <<(double)prev.x*vecs[i].y - (double)prev.y*vecs[i].x << std::endl;
        prev = vecs[i];
    }
    a00 *= 0.5;
    return std::fabs(a00);
}

 
// 计算两个旋转框的IOU
float rbox_iou(detection d1, detection d2)
{
    float inter_area;
    float area_r1 = d1.w * d1.h;
    float area_r2 = d2.w * d2.h;
    cv::RotatedRect rect1;
    rect1.center = cv::Point2f(d1.x, d1.y);
    rect1.size = cv::Size(d1.w, d1.h);
    rect1.angle = d1.theta;
    cv::RotatedRect rect2;
    rect2.center = cv::Point2f(d2.x, d2.y);
    rect2.size = cv::Size(d2.w, d2.h);
    rect2.angle = d2.theta;

    // auto intersectingRegion1 = {cv::Point2f(13.6286,8.3205),cv::Point2f(12.8935,8.63082),cv::Point2f(14.5738,12.6115),cv::Point2f(15.309,12.3012)};
    // cv::_InputArray array(intersectingRegion1);
    std::vector<cv::Point2f> intersectingRegion;
    cv::rotatedRectangleIntersection(rect1, rect2, intersectingRegion);
    if (intersectingRegion.empty())
    {
        inter_area = 0;
    }
    else
    {
        // vector<cv::Point2f> sort_intersectingRegion = sort_points(intersectingRegion);
        // inter_area = cv::contourArea(sort_intersectingRegion);
        for (int i = 0; i < intersectingRegion.size(); ++i) {
            std::cout << "("<< intersectingRegion[i].x << "," << intersectingRegion[i].y << ")" << std::endl;
        }
        // std::cout << std::endl;
        inter_area = cv::contourArea(intersectingRegion);
    }
    std::cout << "ori area1: " << area_r1 << " area_r2: " << area_r2 << " inter: " << inter_area<< std::endl;

    // std::vector<Point2f> vecs = {{13.6286,8.3205},{12.8935,8.63082},{14.5738,12.6115},{15.309,12.3012}};
    // std::cout <<"self-area: " << contourArea(vecs) << std::endl;

    return inter_area / (area_r1+ 0.00000001);
}





void points(float x, float y, float width, float height, float angle) {
    double _angle = angle*M_PI/180.;
    float b = (float)cos(_angle)*0.5f;
    float a = (float)sin(_angle)*0.5f;
    Point2f pts;
    std::vector<Point2f> pt = {4,pts};

    pt[0].x = x - a*height - b*width;
    pt[0].y = y + b*height - a*width;
    pt[1].x = x + a*height - b*width;
    pt[1].y = y - b*height - a*width;
    pt[2].x = 2*x - pt[0].x;
    pt[2].y = 2*y - pt[0].y;
    pt[3].x = 2*x - pt[1].x;
    pt[3].y = 2*y - pt[1].y;
    // std::cout << " (" << pt[0].x << "," << pt[0].y << ")" << std::endl;
    // std::cout << " (" << pt[1].x << "," << pt[1].y << ")" << std::endl;
    // std::cout << " (" << pt[2].x << "," << pt[2].y << ")" << std::endl;
    // std::cout << " (" << pt[3].x << "," << pt[3].y << ")" << std::endl;
}



int main() {

    detection d1;//(7.097693,4.513980),(7.090459,6.321583),(11.562720,6.339480),(11.569955,4.531877)
    float theta1 = 0.498563;
    float theta2 = 0.498563;
    float jiaodu1 = theta1*180/M_PI;
    float jiaodu2 = theta2*180/M_PI;
    
    float ego_yaw = 0;
    d1.x = -7743.308594;
    d1.y = 14447.674805;
    d1.w = 4.146301;//1.790039,4.5661910.505195
    d1.h = 1.777344;
    d1.theta = jiaodu1;//NormalizeAngle(theta1-ego_yaw)/M_PI*180;

    detection d2;
    
    d2.x = -7743.312988;
    d2.y = 14447.682617;
    d2.w = 4.146301;//4.360133;//
    d2.h = 1.777344;//1.845703;//
    d2.theta = jiaodu2;// NormalizeAngle(theta2-ego_yaw)/M_PI*180;

    Pose p1 = { d1.x, d1.y, d1.w, d1.h, theta1};
    Pose p2 = { d2.x, d2.y, d2.w, d2.h, theta2};
    std::vector<Point2f> vecs;
    std::cout << fixed;
    if (IsCross(p1, p2, ego_yaw,vecs)) {
        std::cout << " p1 p2 Cross..........." << std::endl;
        for (auto i : vecs) {
            std:cout << "(" << i.x << ","<< i.y << ")" << std::endl;
        }
    }
    // std::cout << " d1.............. " << std::endl;
    // points(d1.x,d1.y,d1.w,d1.h,d1.theta);
    // std::cout << " d2.............. " << std::endl;
    // points(d2.x,d2.y,d2.w,d2.h,d2.theta);
    // std::cout << rbox_iou(d1,d2) << " jiaodu1: " << d1.theta << " jiaodu2: " << d2.theta << " theta1: " << theta1 << " theta2: " << theta2 << std::endl;
    std::cout << "vecs:...................... " << std::endl;
    for (auto i : vecs) {
        std::cout << i.x << "," << i.y << std::endl;
    }
    std::cout << "vecs:...................... " << std::endl;
    sort_points(vecs);
    std::cout <<"self-area: " << contourArea(vecs) << std::endl;


    Line l1(0,1,1,0);
    Line l2(-1,0,0,1);
    std::vector<Point2f> vecs1;
    std::cout << "xiangjiao: " << intersection(l1, l2, vecs1) << std::endl;


    // LinePara para1, para2;
    // Line line1(-7741.873047,14449.481445,-7741.023438,14447.920898);
	// getLinePara(line1, para1);
    // std::cout << "test para: " << para1.k << ", " << para1.b << std::endl;




    return 0;
}
