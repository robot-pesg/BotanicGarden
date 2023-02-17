#include"cameraParams.h"
cameraParams::cameraParams(){
    std::string xml_file_path="../config/camera.xml";
    cv::FileStorage fs(xml_file_path,cv::FileStorage::READ);

    if(fs.isOpened()){
        cv::Mat intrinsic_;
        cv::Mat distortion_;
        fs["camera-matrix"]>>intrinsic_;
        fs["distortion"]>>distortion_;
        // std::cout<<intrinsic_<<std::endl<<distortion_<<std::endl;
        radial_distortion[0]=distortion_.at<double>(0);
        radial_distortion[1]=distortion_.at<double>(1);
        tangential_distortion[0]=distortion_.at<double>(2);
        tangential_distortion[1]=distortion_.at<double>(3);
        for(int i=0;i<4;i++){
            *(distortion+i)=distortion_.at<double>(i);
        }
        for(int i=0;i<9;i++){
            *(intrinsic+i)=intrinsic_.at<double>(i);
        }
        fs.release();
    }
    else{
        std::cout<<"error loading xml file"<<std::endl;
        return;
    }
}
cameraParams::cameraParams(const cv::Mat& K,const cv::Mat& D){
    radial_distortion[0]=D.at<double>(0);
    radial_distortion[1]=D.at<double>(1);
    tangential_distortion[0]=D.at<double>(2);
    tangential_distortion[1]=D.at<double>(3);
    for(int i=0;i<4;i++){
        *(distortion+i)=D.at<double>(i);
    }
    for(int i=0;i<9;i++){
        *(intrinsic+i)=K.at<double>(i);
    }
}