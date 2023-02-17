#ifndef SINGLE_CHESSBOARD_H
#define SINGLE_CHESSBOARD_H
#include<iostream>
#include<vector>
#include<eigen3/Eigen/Core>
#include"cameraParams.h"
#include<opencv2/core.hpp>
#include<opencv2/highgui.hpp>
#include<opencv4/opencv2/imgproc.hpp>
#include<opencv4/opencv2/opencv.hpp>
#include<opencv4/opencv2/core/eigen.hpp>
class single_chessboard{
public:
    single_chessboard(){
        //corner_detection();
        //load_world_points();
        // std::cout<<"construct function!"<<std::endl;
    };
    bool corner_detection();
    void load_world_points();
    void load_image(cv::Mat &image_){
        image_.copyTo(image);
    }
    void load_chessboard_params();
    std::vector<cv::Point2f> key_points_(){
        return key_points;
    }
    std::vector<cv::Point3f> world_points_(){
        return world_points;
    }
    void write_rotation_matrix(const Eigen::Matrix3f &rotation_matrix_){
        rotation_matrix=rotation_matrix_;
    }
    void write_translation_vector(const Eigen::Vector3f &translation_vector_){
        translation_vector=translation_vector_;
    }
    void write_reprojection_points(const std::vector<cv::Point2f> &reprojection_points_){
        for(auto reprojected_point:reprojection_points_){
            reprojection_points.push_back(reprojected_point);
        }
    }
    void cal_reprojection_error(){
        float x_error{0};
        float y_error{0};
        for(int i=0;i<int(reprojection_points.size());i++){
            x_error+=reprojection_points.at(i).x-key_points.at(i).x;
            y_error+=reprojection_points.at(i).y-key_points.at(i).y;
            cv::Point2f error(reprojection_points.at(i).x-key_points.at(i).x,reprojection_points.at(i).y-key_points.at(i).y);
            reprojection_error.push_back(error);
            // std::cout<<"x_error = "<<x_error<<" y_error = "<<y_error<<std::endl;
        }
        // std::cout<<"average error is : ("<<x_error/float(reprojection_points.size())<<", "
        //          <<y_error/float(reprojection_points.size())<<")"<<std::endl;
    }
    cv::Size image_size(){
        // std::cout<<"image size => "<<image.size()<<std::endl;
        return image.size();
    }
    cameraParams get_camera_params(){
        return cam;
    }
    void update_camera_params(const cameraParams& cam_){
        std::copy(std::begin(cam_.distortion),std::end(cam_.distortion),std::begin(cam.distortion));
        std::copy(std::begin(cam_.intrinsic),std::end(cam_.intrinsic),std::begin(cam.intrinsic));
        std::copy(std::begin(cam_.radial_distortion),std::end(cam_.radial_distortion),std::begin(cam.radial_distortion));
        std::copy(std::begin(cam_.tangential_distortion),std::end(cam_.tangential_distortion),std::begin(cam.tangential_distortion));
    }
    void update_T(const Eigen::Matrix4f& T_){
        T=T_;
    }
    Eigen::Matrix4f T_(){
        return T;
    }
    float grid_size_(){
        return static_cast<float>(grid_size);
    }
    cv::Size pattern_size_(){
        return pattern_size;
    }
    void reproject_point_();
    cv::Mat mask_corner();
    single_chessboard& operator =(const single_chessboard& obj){
        // std::cout << "operator =" << std::endl;
        if (this != &obj){
            cam=obj.cam;
            pattern_size=obj.pattern_size;
            grid_size=obj.grid_size;
            obj.image.copyTo(image);
            obj.undistorted_image.copyTo(undistorted_image);
            world_points.clear();
            for(auto world_point:obj.world_points)
                world_points.push_back(world_point);
            key_points.clear();
            for(auto key_point:obj.key_points)
                key_points.push_back(key_point);
            reprojection_points.clear();
            for(auto reprojection_point:obj.reprojection_points)
                reprojection_points.push_back(reprojection_point);
            reprojection_error.clear();
            for(auto reprojection_error_:obj.reprojection_error)
                reprojection_error.push_back(reprojection_error_);
            rotation_matrix=obj.rotation_matrix;
            translation_vector=obj.translation_vector;
            T=obj.T;
        }
        return *this;
    }
private:
    cameraParams cam;
    cv::Size pattern_size;
    int grid_size;
    cv::Mat image;
    cv::Mat undistorted_image;
    std::vector<cv::Point3f> world_points;
    std::vector<cv::Point2f> key_points;
    std::vector<cv::Point2f> reprojection_points;
    Eigen::Matrix3f rotation_matrix;
    Eigen::Vector3f translation_vector;
    Eigen::Matrix4f T;
    std::vector<cv::Point2f> reprojection_error;
};
#endif