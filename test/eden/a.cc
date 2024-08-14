#include <iostream>
#include <vector>
#include <Eigen/Dense>    // Eigen头文件，<Eigen/Dense>包含Eigen库里面所有的函数和类
#include "matplotlibcpp.h"
const int num_point = 10;
//g++ a.cc -o a -I/usr/include/python3.8 -lpython3.8
namespace plt = matplotlibcpp;
int main()
{
  std::vector<Eigen::Vector3d> fitted_points;
  Eigen::MatrixXd a{Eigen::MatrixXd::Zero(num_point, 5)};
  Eigen::VectorXd b{Eigen::VectorXd::Zero(num_point)};
  std::vector<Eigen::Vector3d> points;
  Eigen::Vector3d point0,point1,point2,point3,point4,point5,point6,point7,point8,point9,point01,point02,point03,point04,point05,point06;
  // point01 = {-10,10,0};
  // point02 = {-10,10,0};
  // point03 = {-10,10,0};
  // point04 = {-10,10,0};
  // point05 = {-10,10,0};
  // point06 = {-10,10,0};
  point0 = {0,10,0};
  point1 = {-8,2,0};
  point2 = {-6,2,0};
  point3 = {-4,2,0};
  point4 = {-2,2,0};
  point5 = {2,2,0};
  point6 = {4,2,0};
  point7 = {6,2,0};
  point8 = {8,2,0};
  point9 = {0,10,0};
  points = {point0,point1,point2,point3,point4,point5,point6,point7,point8,point9};
std::vector<double> x,y,orin_x,orin_y;
  for (size_t i = 0; i < num_point; ++i) {
    const Eigen::Vector3d p = points.at(i);
    a.row(i) << std::pow(p.x(), 4),std::pow(p.x(), 3), std::pow(p.x(), 2), p.x(), 1.0;
    b(i) = p.y();
    orin_x.emplace_back(p.x());
    orin_y.emplace_back(p.y());
  }
  

  Eigen::VectorXd coeffs;// = Eigen::Vector5d::Zero();
  coeffs = a.colPivHouseholderQr().solve(b);
  int error_count = 0;
  for (const Eigen::Vector3d &p : points) {
    const double fit_y = coeffs(0) * std::pow(p.x(), 4) + coeffs(1) * std::pow(p.x(), 3) +
                         coeffs(2) * std::pow(p.x(), 2) + coeffs(3) * p.x() +
                         coeffs(4);
    if (std::abs(fit_y - p.y()) > 0.5) {
      ++error_count;
    }
    fitted_points.emplace_back(p.x(), fit_y, 0.0);
    x.emplace_back(p.x());
    y.emplace_back(fit_y);
  }

	/*原始数据*/
	plt::figure();
	//plt::subplot(2,2,1);
	plt::title("originaldata");
	plt::plot(orin_x,orin_y);
	plt::figure();
	/*最小二乘拟合后的数据*/
	//plt::subplot(2,2,2);
	plt::title("polyfitdata");
	plt::plot(x,y);
	plt::show();
}

