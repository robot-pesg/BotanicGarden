#include"key_chessboard.h"
key_chessboard::key_chessboard(){
    cv::FileStorage fs("../config/target.yaml",cv::FileStorage::READ);
    fs["key_board_num"]>>num_chessboard;

    key_chessboards = new single_chessboard[num_chessboard];

    std::string target_image_path;
    fs["target_image"]>>target_image_path;
    target_image=cv::imread(target_image_path);

    std::vector<cv::Mat> images;
    for(int i=0;i<num_chessboard;i++){
        single_chessboard temp;
        temp.load_image(target_image);
        temp.load_world_points();
        temp.corner_detection();
        key_chessboards[i]=temp;
        target_image=temp.mask_corner();
        
        // cv::imshow("image_masked",target_image);
        // cv::waitKey(0);
    }
    fs.release();
}
pcl::PointCloud<pcl::PointXYZRGB> key_chessboard::generate_chessboard(){
    pcl::PointCloud<pcl::PointXYZRGB> src;
    single_chessboard temp;
    temp.load_chessboard_params();
    cv::Size pattern_size = temp.pattern_size_();
    float grid_size = temp.grid_size_()/1000.f;
    cv::Mat white,black;
    cv::FileStorage fs("../config/target.yaml",cv::FileStorage::READ);
    if(fs.isOpened()){
        fs["white"]>>white;
        fs["black"]>>black;
        fs.release();
    }
    std::uint32_t rgb;
    std::uint8_t r(0), g(0), b(0);
    float resolution=50;
    int cnt=0;
    for(float i=0;i<float(pattern_size.width-std::size_t(1));i=i+1)
        for(float j=0;j<float(pattern_size.height-std::size_t(1));j=j+1){
            for(float i_=0;i_<resolution;i_=i_+1)
                for(float j_=0;j_<resolution;j_=j_+1){
                    pcl::PointXYZRGB point;
                    point.x=i*grid_size+(i_/resolution)*grid_size;
                    point.y=j*grid_size+(j_/resolution)*grid_size;
                    point.z=0.;
                    // std::cout<<" x = "<<point.x
                    //          <<" y = "<<point.y
                    //          <<" z = "<<point.z<<std::endl;
                    if((int(i+j))%2==0){
                        r=std::uint8_t(static_cast<int>(255*white.at<double>(0)));
                        g=std::uint8_t(static_cast<int>(255*white.at<double>(1)));
                        b=std::uint8_t(static_cast<int>(255*white.at<double>(2)));
                        rgb = (static_cast<std::uint32_t>(r) << 16 |
                        static_cast<std::uint32_t>(g) << 8 | static_cast<std::uint32_t>(b));
                    }
                    else{
                        r=std::uint8_t(static_cast<int>(255*black.at<double>(0)));
                        g=std::uint8_t(static_cast<int>(255*black.at<double>(1)));
                        b=std::uint8_t(static_cast<int>(255*black.at<double>(2)));
                        rgb = (static_cast<std::uint32_t>(r) << 16 |
                        static_cast<std::uint32_t>(g) << 8 | static_cast<std::uint32_t>(b));
                    }
                    // std::cout<<r<<std::endl;
                    point.rgb=*reinterpret_cast<float*>(&rgb);
                    
                    src.points.push_back(point);
                    cnt++;
                    // std::cout<<"-------------------"<<std::endl;
                }
        }
        // std::cout<<"cnt = "<<cnt<<std::endl;
    src.height=1;
    src.width=cnt;
    src.resize(1*cnt);

    return src;
}
void key_chessboard::construct_3D(){
    pcl::PointCloud<pcl::PointXYZRGB> cloud_src;
    for(int i=0;i<num_chessboard;i++){
        key_chessboards[i].cal_reprojection_error();
        pcl::PointCloud<pcl::PointXYZRGB> cloud=generate_chessboard();
        pcl::PointCloud<pcl::PointXYZRGB> cloud_;
        // std::cout<<"T = "<<key_chessboards[i].T_()<<std::endl;
        pcl::transformPointCloud(cloud,cloud_,key_chessboards[i].T_());
        cloud_src=cloud_src+cloud_;
    }
    pcl::visualization::PCLVisualizer::Ptr viewer(new pcl::visualization::PCLVisualizer("3D Viewer"));
    viewer->setBackgroundColor(0,0,0);
    viewer->addPointCloud<pcl::PointXYZRGB> (cloud_src.makeShared(), "sample cloud");

    viewer->spin();
    pcl::io::savePCDFile("result.pcd",cloud_src);
}