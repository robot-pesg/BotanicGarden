#include"single_chessboard.h"
#include<iostream>
#include<string>
#include<vector>
#include"dirent.h"
#include<cstring>
#include<eigen3/Eigen/Core>
Eigen::Matrix4f rt2T(const cv::Mat& r,const cv::Mat& t){
    Eigen::Matrix4f result=Eigen::Matrix4f::Identity();
    cv::Mat r_rotation_matrix;
    cv::Rodrigues(r,r_rotation_matrix);
    for(int i=0;i<3;i++)
        for(int j=0;j<3;j++)
            result(i,j)=r_rotation_matrix.at<double>(i*3+j);
    result(0,3)=t.at<double>(0)/1000.f;
    result(1,3)=t.at<double>(1)/1000.f;
    result(2,3)=t.at<double>(2)/1000.f;

    return result;
}
bool compare(const std::string &str1,const std::string &str2){
    int length1=str1.length();
    int length2=str2.length();

    std::string num1=str1.substr(0,std::size_t(length1-7));
    std::string num2=str2.substr(0,std::size_t(length2-7));

    if(std::stoi(num1)<std::stoi(num2))
        return true;
    else
        return false;
}
std::vector<std::string> search_folder(const std::string &folder){
    DIR* dir=NULL;
    struct dirent *dir_entry = NULL;
    std::vector<std::string> files;

    const int length = folder.length();
    char* char_array = new char[length + 1];
    strcpy(char_array, folder.c_str());

    if((dir=opendir(char_array))==NULL){
        std::cout<<"load images folder fail"<<std::endl;
    }
    else{
        while((dir_entry=readdir(dir))!=NULL){
            if(dir_entry->d_type==DT_REG){
                // std::cout<<dir_entry->d_name<<std::endl;
                std::string temp_string=dir_entry->d_name;
                files.push_back(temp_string);
            }
        }
        std::sort(files.begin(),files.end(),compare);
        // for(auto it:files)
        //     std::cout<<it<<std::endl;
    }
    closedir(dir);
    return files;
}
void single_chessboard::load_chessboard_params(){
    cv::FileStorage fs("../config/target.yaml",cv::FileStorage::READ);
    if(fs.isOpened()){
        fs["pattern_size"]>>pattern_size;
        fs["grid_size"]>>grid_size;
        // std::cout<<pattern_size<<std::endl;
        fs.release();
    }
    else{
        std::cout<<"fail to load chessboard config!"<<std::endl;
        return;
    }
}
bool single_chessboard::corner_detection(){
    // cv::Mat image_=cv::imread("/home/uu/Documents/c++/3d_reconstruction/images/13_L0.png");
    // load_image(image_);
    if(!image.data){
        std::cout<<"image data is empty!"<<std::endl;
        return -1;
    }
    cv::Mat camera_matrix=cv::Mat(3,3,CV_32FC1,&cam.intrinsic);
    cv::Mat distortion_vector=cv::Mat(4,1,CV_32FC1,&cam.distortion);

    cv::undistort(image,undistorted_image,camera_matrix,distortion_vector);
    
    // cv::Mat show_image;
    // cv::hconcat(image,undistorted_image,show_image);

    // cv::imshow("undistort",show_image);
    // cv::waitKey(0);

    cv::Mat gray_image;
    cv::cvtColor(undistorted_image,gray_image,cv::COLOR_RGB2GRAY);

    bool ret = cv::findChessboardCorners(gray_image,
										 pattern_size,
										 key_points,
										 cv::CALIB_CB_ADAPTIVE_THRESH |
										 cv::CALIB_CB_NORMALIZE_IMAGE);//https://blog.csdn.net/guduruyu/article/details/69573824
    cv::TermCriteria criteria = cv::TermCriteria(cv::TermCriteria::MAX_ITER + cv::TermCriteria::EPS,
                                                40,
                                                0.1);
    cv::cornerSubPix(gray_image, key_points, cv::Size(5, 5), cv::Size(-1, -1), criteria);


    // cv::Mat show;
    // image.copyTo(show);
    // cv::drawChessboardCorners(show,pattern_size,key_points,ret);
    // cv::imshow("show",show);
    // cv::waitKey(0);
    return true;
}
void single_chessboard::load_world_points(){
    load_chessboard_params();
    for(int i=0;i<pattern_size.height;i++)
        for(int j=0;j<pattern_size.width;j++){
            cv::Point3f temp(j*grid_size,i*grid_size,0);
            world_points.push_back(temp);
        }
}

void single_chessboard::reproject_point_(){
    //reprojected_point=K*T*world_point
    for(auto world_point:world_points){
        Eigen::Vector4f world_point_augmented(world_point.x/1000.f,world_point.y/1000.f,world_point.z/1000.f,1.);
        world_point_augmented=T*world_point_augmented;
        Eigen::Vector3f world_point_eigen(world_point_augmented(0),
                                          world_point_augmented(1),
                                          world_point_augmented(2));
        Eigen::Matrix3f K_eigen;
        cv::Mat K_cv=cv::Mat(3,3,CV_32F,&cam.intrinsic);
        cv::cv2eigen(K_cv,K_eigen);

        world_point_eigen=K_eigen*world_point_eigen;

        world_point_eigen=Eigen::Vector3f(world_point_eigen(0)/world_point_eigen(2),
                                            world_point_eigen(1)/world_point_eigen(2),1.);
        cv::Point2f reproject_point;
        reproject_point.x=world_point_eigen(0);
        reproject_point.y=world_point_eigen(1);

        reprojection_points.push_back(reproject_point); 
    }
    // for(int i=0;i<int(reprojection_points.size());i++){
    //     std::cout<<"key point is : "<<key_points.at(i)<<std::endl
    //              <<"reprojection point is : "<<reprojection_points.at(i)<<std::endl;
    // }
    // cal_reprojection_error();
}
cv::Mat single_chessboard::mask_corner(){
    cv::Mat result;
    image.copyTo(result);
    int radius;
    radius=int(sqrt(pow(key_points.at(0).x-key_points.at(1).x,2)+
                    pow(key_points.at(0).y-key_points.at(1).y,2)));
    for(auto corner:key_points){
        cv::circle(result,corner,radius,cv::Scalar(0,0,0),-1);
    }
    return result;
}