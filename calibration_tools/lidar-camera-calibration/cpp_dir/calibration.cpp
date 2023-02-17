#include"calibration.h"
extern std::vector<std::string> search_folder(const std::string &folder);
extern Eigen::Matrix4f rt2T(const cv::Mat& r,const cv::Mat& t);
void load_python_script(){
    Py_Initialize();
    if(!Py_IsInitialized()){
        return;
    }
    PyRun_SimpleString("import sys");
    if(PyRun_SimpleString("exec(open('../scripts/test.py').read())")==NULL){
        return;
    }
    Py_Finalize();
}
std::vector<Eigen::Vector3f> T2plane_coeffs(const Eigen::Matrix4f& T,const cv::Size& pattern_size,float grid_size,std::vector<float>& plane_coeffs){
    
    
    Eigen::Vector3f p1(0.,0.,0.);
    float a=pattern_size.width*grid_size/1000.f;
    float b=pattern_size.height*grid_size/1000.f;

    Eigen::Vector3f p2(0.,b,0.);
    Eigen::Vector3f p3(a,b,0.);
    Eigen::Vector3f p4(a,0.,0.);

    Eigen::Vector4f p1_(0.,0.,0.,1.);
    Eigen::Vector4f p2_(0.,b,0.,1.);
    Eigen::Vector4f p3_(a,b,0.,1.);
    Eigen::Vector4f p4_(a,0.,0.,1.);

    Eigen::Vector4f p1__=T*p1_;
    Eigen::Vector4f p2__=T*p2_;
    Eigen::Vector4f p3__=T*p3_;
    Eigen::Vector4f p4__=T*p4_;

    p1=Eigen::Vector3f(p1__(0),p1__(1),p1__(2));
    p2=Eigen::Vector3f(p2__(0),p2__(1),p2__(2));
    p3=Eigen::Vector3f(p3__(0),p3__(1),p3__(2));
    p4=Eigen::Vector3f(p4__(0),p4__(1),p4__(2));

    /*A = (y3 - y1)*(z3 - z1) - (z2 -z1)*(y3 - y1);

    B = (x3 - x1)*(z2 - z1) - (x2 - x1)*(z3 - z1);

    C = (x2 - x1)*(y3 - y1) - (x3 - x1)*(y2 - y1);

    又D = -(A * x1 + B * y1 + C * z1)，所以可以求得D的值。*/

    float A=(p3(1)-p1(1))*(p3(2)-p1(2))-(p3(1)-p1(1))*(p2(2)-p1(2));
    float B=(p3(0)-p1(0))*(p2(2)-p1(2))-(p2(0)-p1(0))*(p3(2)-p1(2));
    float C=(p2(0)-p1(0))*(p3(1)-p1(1))-(p3(0)-p1(0))*(p2(1)-p1(1));
    float D=-(A*p1(0)+B*p1(1)+C*p1(2));

    plane_coeffs.clear();
    plane_coeffs.push_back(A);
    plane_coeffs.push_back(B);
    plane_coeffs.push_back(C);
    plane_coeffs.push_back(D);

    // std::cout<<"A = "<<A<<" B = "<<B<<" C = "<<C<<" D = "<<D<<std::endl;
    // std::vector<float> result;
    // result.push_back(A);
    // result.push_back(B);
    // result.push_back(C);
    // result.push_back(D);

    std::vector<Eigen::Vector3f> result;
    result.push_back(p1);
    result.push_back(p2);
    result.push_back(p3);
    result.push_back(p4);

    return result;
}
calibration::calibration(){
    std::vector<std::string> image_pathes;
    cv::FileStorage fs("../config/target.yaml",cv::FileStorage::READ);
    std::string image_folder;
    if(fs.isOpened()){
        // std::cout<<"load yaml file successfully!"<<std::endl;
        fs["image_folder"]>>image_folder;
        fs.release();
    }
    else{
        return;
    }
    image_pathes=search_folder(image_folder);
    for(auto image_path:image_pathes){
        image_path=image_folder+"/"+image_path;
        // std::cout<<image_path<<std::endl;
        cv::Mat image=cv::imread(image_path);
        single_chessboard temp_chessboard;
        temp_chessboard.load_world_points();
        // std::cout<<temp_chessboard.world_points_()<<std::endl;
        temp_chessboard.load_image(image);
        temp_chessboard.corner_detection();
        chessboards.push_back(temp_chessboard);
    }
}
bool calibration::compute(){
    cv::Size image_size=chessboards.begin()->image_size();
    // std::cout<<image_size<<std::endl;
    cameraParams camera_params=chessboards.begin()->get_camera_params();
    cv::Mat K=cv::Mat(3,3,CV_32F,&camera_params.intrinsic);
    cv::Mat D=cv::Mat(4,1,CV_32F,&camera_params.distortion);

    std::vector<std::vector<cv::Point2f>> corners;
    std::vector<std::vector<cv::Point3f>> world_points;
    for(int i=0;i<keyChessboard.num_chessboard_();i++){
        chessboards.push_back(keyChessboard.key_chessboards[i]);
    }
    for(auto chessboard:chessboards){
        corners.push_back(chessboard.key_points_());
        world_points.push_back(chessboard.world_points_());
    }
    std::vector<cv::Mat> rvecs,tvecs,stdDeviationsIntrinsics,stdDeviationsExtrinsics,perViewErrors;
    int flag=0;
    // std::cout<<"start calibrating!"<<std::endl;
    double ave_error=cv::calibrateCamera(world_points,corners,image_size,K,D,rvecs,tvecs);
    //brings the calibration pattern from the object coordinate space (in which object points are specified) to the camera coordinate space
    std::cout<<"average error is "<<ave_error<<std::endl;

    cameraParams update_cam(K,D);

    for(auto &chessboard:chessboards)
        chessboard.update_camera_params(update_cam);
    std::cout<<update_cam;

    for(int i=0;i<int(rvecs.size());i++){
        Eigen::Matrix4f T=rt2T(rvecs.at(i),tvecs.at(i));
        // std::cout<<rvecs.at(i)<<std::endl<<tvecs.at(i)<<std::endl;
        // std::cout<<T<<std::endl;
        // std::cout<<"T = "<<T<<std::endl;
        chessboards.at(i).update_T(T);
    }
    for(auto chessboard:chessboards){
        chessboard.reproject_point_();
    }
    for(int i=0;i<keyChessboard.num_chessboard_();i++){
        // std::cout<<"totle boards are "<<chessboards.size()<<std::endl;
        // std::cout<<"let chessboards.at("<<int(chessboards.size())+i-keyChessboard.num_chessboard_()<<") => keyBoard"<<std::endl;
        keyChessboard.key_chessboards[i]=chessboards.at(int(chessboards.size())+i-keyChessboard.num_chessboard_());
    }
    keyChessboard.construct_3D();
    return true;
}
void calibration::construct3D(){
    cv::FileStorage fs("../scripts/board_result.xml",cv::FileStorage::WRITE);
    if(fs.isOpened()){
        int cnt=1;
        // fs<<"construct-result";
        for(auto chessboard:chessboards){
            Eigen::Matrix4f T=chessboard.T_();
            float grid_size=chessboard.grid_size_();
            cv::Size pattern_size=chessboard.pattern_size_();
            std::vector<float> plane_coeffs;
            std::vector<Eigen::Vector3f> chessboard_corners=T2plane_coeffs(T,pattern_size,grid_size,plane_coeffs);
            
            std::vector<float> temp;
            for(auto point:chessboard_corners){
                temp.push_back(point(0));
                temp.push_back(point(1));
                temp.push_back(point(2));
            }
            float planes_coeffs_arr[4];
            float key_points_arr[12];

            for(int i=0;i<4;i++)
                planes_coeffs_arr[i]=plane_coeffs.at(i);
            for(int i=0;i<12;i++)
                key_points_arr[i]=temp.at(i);
            std::string board_id="board"+std::to_string(cnt);
            cnt++;

            cv::Mat plane_coeffs_cv=cv::Mat(4,1,CV_32F,&planes_coeffs_arr);
            cv::Mat key_points_cv=cv::Mat(4,3,CV_32F,&key_points_arr);
            
            // std::cout<<plane_coeffs_cv;
            // std::cout<<key_points_cv;
            fs<<board_id;
            fs<<"{"<<"plane-coefficients"<<plane_coeffs_cv;
            fs<<"key-points"<<key_points_cv<<"}";
        }
        fs.release();
    }
    else{
            std::cout<<"can not open xml"<<std::endl;
            return;
        }
    
    
}
// void calibration::construct3D(){
//     pcl::visualization::PCLVisualizer::Ptr viewer(new pcl::visualization::PCLVisualizer("3D Viewer"));
//     viewer->setBackgroundColor(0,0,0);
//     // pcl::visualization::PointCloudColorHandlerCustom<pcl::PointXYZ> single_color(cloud, 0, 255, 0);
//     // viewer->addPointCloud<pcl::PointXYZ> (cloud, single_color, "sample cloud");
//     // viewer->setPointCloudRenderingProperties (pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 3, "sample cloud");
//     int cnt=1;
//     for(auto chessboard:chessboards){
//         cnt++;
//         if(cnt<15){
//             continue;
//         }
//         Eigen::Matrix4f T=chessboard.T_();
//         std::vector<float> coeffs_vec=T2plane_coeffs(T);
//         pcl::ModelCoefficients coeffs;
//         coeffs.values.resize(4);
//         coeffs.values[0]=coeffs_vec.at(0);
//         coeffs.values[1]=coeffs_vec.at(1);
//         coeffs.values[2]=coeffs_vec.at(2);
//         coeffs.values[3]=coeffs_vec.at(3);

//         std::string plane_id="plane"+std::to_string(cnt);

//         viewer->addPlane(coeffs,plane_id);
//     }
//     viewer->addCoordinateSystem(1.0);
//     viewer->initCameraParameters();

//     while (!viewer->wasStopped()){
//         viewer->spin();
//     }
// }
