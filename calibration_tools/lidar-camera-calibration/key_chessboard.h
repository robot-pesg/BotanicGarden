#ifndef KEY_CHESSBOARD_H
#define KEY_CHESSBOARD_H
#include"single_chessboard.h"
#include<pcl/point_cloud.h>
#include<pcl/point_types.h>
#include<pcl/io/pcd_io.h>
#include<pcl/common/transforms.h>
#include<pcl/visualization/pcl_visualizer.h>
class key_chessboard{
public:
    key_chessboard();
    std::vector<single_chessboard> get_chessboard(){
        std::vector<single_chessboard> result;
        for(int i=0;i<num_chessboard;i++){
            result.push_back(key_chessboards[i]);
        }
        return result;
    }
    int num_chessboard_(){
        return num_chessboard;
    }
    void construct_3D();
    pcl::PointCloud<pcl::PointXYZRGB> generate_chessboard();
    single_chessboard* key_chessboards;
private:
    int num_chessboard;
    cv::Mat target_image;
};
#endif