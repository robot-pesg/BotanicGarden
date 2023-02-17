#ifndef CAMERAPARAMS_H
#define CAMERAPARAMS_H
#include<vector>
#include<string>
#include<iostream>
#include<opencv2/core.hpp>
class cameraParams{
friend std::ostream &operator<<(std::ostream &out,const cameraParams& obj){
    out<<"intrainsic : "<<std::endl<<"["<<obj.intrinsic[0]<<", "
                         <<obj.intrinsic[1]<<", "
                         <<obj.intrinsic[2]<<"]"<<std::endl
                         <<"["<<obj.intrinsic[3]<<", "
                         <<obj.intrinsic[4]<<", "
                         <<obj.intrinsic[5]<<"]"<<std::endl
                         <<"["<<obj.intrinsic[6]<<", "
                         <<obj.intrinsic[7]<<", "
                         <<obj.intrinsic[8]<<"]"<<std::endl;
    out<<"disortion : "<<std::endl<<"["<<obj.distortion[0]<<", "
                                  <<obj.distortion[1]<<", "
                                  <<obj.distortion[2]<<", "
                                  <<obj.distortion[3]<<"]"<<std::endl;
    return out;
}
public:
    cameraParams();
    cameraParams& operator=(const cameraParams& obj){
        if(this!=&obj){
            radial_distortion[0]=obj.radial_distortion[0];
            radial_distortion[1]=obj.radial_distortion[1];
            tangential_distortion[1]=obj.tangential_distortion[1];
            tangential_distortion[1]=obj.tangential_distortion[1];
            for(int i=0;i<4;i++)
                distortion[i]=obj.distortion[i];
            for(int i=0;i<9;i++)
                intrinsic[i]=obj.intrinsic[i];
        }
        return *this;
    }
    cameraParams(const cv::Mat& K,const cv::Mat& D);
    float radial_distortion[2];
    float tangential_distortion[2];
    float distortion[4];
    float intrinsic[9];//fx,0,0,s,fy,0,cx,cy,1
};
#endif