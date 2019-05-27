#include "utility.h"
#include <iostream>
using namespace std;

Eigen::Matrix3d Utility::g2R(const Eigen::Vector3d &g) {
  std::cout << "debug test, g = " << g.transpose() << std::endl;
  Eigen::Matrix3d R0;
  Eigen::Vector3d ng1 = g.normalized();
  Eigen::Vector3d ng2{0, 0, 1.0};
  R0 = Eigen::Quaterniond::FromTwoVectors(ng1, ng2).toRotationMatrix();
  
  std::cout << "debug test, Before Rot R0 = " << R0 << std::endl;
  double yaw = Utility::R2ypr(R0).x();
  R0 = Utility::ypr2R(Eigen::Vector3d{-yaw, 0, 0}) * R0;
  // R0 = Utility::ypr2R(Eigen::Vector3d{-90, 0, 0}) * R0;
  std::cout << "debug test, After Rot R0 = " << R0 << std::endl;
  return R0;
}
