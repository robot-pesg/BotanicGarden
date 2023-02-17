#ifndef CALIBRATION_H
#define CALIBRATION_H
#include<iostream>
#include<vector>
#include<string>
#include"single_chessboard.h"
#include<opencv4/opencv2/calib3d.hpp>
#include<pcl/visualization/pcl_visualizer.h>
#include<pcl/ModelCoefficients.h>
#include"python3.8/Python.h"
#include<thread>
#include"key_chessboard.h"
class calibration{
public:
    calibration();
    bool compute();
    void construct3D();
private:
    std::vector<single_chessboard> chessboards;
    key_chessboard keyChessboard;
};
#endif