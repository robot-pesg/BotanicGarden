#include <iostream>
#include <fstream>

#include <rosbag/bag.h>
#include <rosbag/view.h>

#include <sensor_msgs/Image.h>
#include <boost/foreach.hpp>
#include <cv_bridge/cv_bridge.h>
#include <opencv2/imgcodecs.hpp>

#include <yaml-cpp/yaml.h>

using namespace std;

bool getFilesFromFolder(const std::string &folder,
                        const std::string &suffix,
                        std::vector<std::string> &files)
{
  boost::filesystem::path path(folder);
 
  if (!boost::filesystem::exists(path) || !boost::filesystem::is_directory(path))
  {
      std::cout << "the folder is not exists or is not directory. the folder: " << folder << std::endl;
      return false;
  }
 
  boost::filesystem::recursive_directory_iterator end_iter;
 
  for(boost::filesystem::recursive_directory_iterator iter(path); iter != end_iter; ++iter)
  {
      //check file
      if(boost::filesystem::is_regular_file(*iter) && iter->path().string().size() > suffix.size())
      {
          std::string curSuffix = iter->path().string().substr(iter->path().string().size() - suffix.size());
 
          if (suffix == curSuffix)
          {
              files.push_back(iter->path().string());
          }
      }
      else if(boost::filesystem::is_directory(iter->status()))
      {
          std::string dirNext(iter->path().string());
 
          getFilesFromFolder(dirNext, suffix, files);
      }
    }
 
    return true;
}

int main(int argc, char **argv)
{
    if(argc != 2)
    {
        std::cerr << std::endl << "Usage: ./bag_creator config_file_path" << std::endl;

        return 1;
    }
    std::string config_file_path = std::string(argv[1]);
    YAML::Node config_node = YAML::LoadFile(config_file_path);

    std::string output_folder_path = config_node["output_folder_path"].as<std::string>();
    vector<string>bag_names  = config_node["bag_names"].as<vector<string>>();

    for (string bag_name:bag_names){

        cout << "processing" << bag_name << endl;
        std::string output_bag_name = bag_name;
        std::string output_bag_path = output_folder_path + output_bag_name + ".bag";

        rosbag::Bag bag;
        bag.open(output_bag_path, rosbag::bagmode::Write);
        // bag.open("/home/xuyufeng/my_files/MH_01_easy.bag", rosbag::bagmode::Read);

        std::string l_cam_topic = config_node["left_cam_topic"].as<std::string>();
        std::string r_cam_topic = config_node["right_cam_topic"].as<std::string>();

        std::string l_cam_topic_rgb = config_node["left_cam_topic_rgb"].as<std::string>();
        std::string r_cam_topic_rgb = config_node["right_cam_topic_rgb"].as<std::string>();

        std::vector<double> vTimeStamps;
        std::vector<double> vTimeStamps_rgb;
        std::ifstream fTimes;
        std::string strPathTimes_whole = config_node["timestamp_file_path"].as<std::string>();
        std::string strPathTimes = strPathTimes_whole + bag_name + ".txt";
        fTimes.open(strPathTimes.c_str());
        vTimeStamps.reserve(40000);
        vTimeStamps_rgb.reserve(40000);

        int down_sample_ratio = config_node["down_sample_ratio"].as<int>();

        int flag = 0;
        while(!fTimes.eof())
        {
            std::string s;
            getline(fTimes,s);
            if(!s.empty())
            {
                std::stringstream ss;
                ss << s;
                double t;
                ss >> t;
                // vTimeStamps.push_back(t);
                if (flag % down_sample_ratio == 0){
                    vTimeStamps.push_back(t);
                    vTimeStamps_rgb.push_back(t);
                }
                flag++;  
            }   
        }

        const int nTimes = vTimeStamps.size();
        // std::string image_format = config_node["image_format"].as<std::string>();
        // int cvflag = cv::IMREAD_GRAYSCALE;
        // if (image_format == "bgr8"){
        //     cvflag = cv::IMREAD_COLOR;
        // }

        std::string l_path_whole = config_node["image_folder_path"].as<std::string>();
        std::string r_path_whole = l_path_whole;

        std::string l_path = l_path_whole + bag_name + "/c4a3a4/";
        std::string r_path = r_path_whole + bag_name + "/c4a3a8/";
        std::string l_path_rgb = l_path_whole + bag_name + "/c54d7a/";
        std::string r_path_rgb = r_path_whole + bag_name + "/c54d79/";
        // get prefix
        std::vector<string> file_name_vector_l_gray;
        getFilesFromFolder(l_path, "tif", file_name_vector_l_gray);
        
        std::vector<string> file_name_vector_r_gray;
        getFilesFromFolder(r_path, "tif", file_name_vector_r_gray);
       
        std::vector<string> file_name_vector_l_rgb;
        getFilesFromFolder(l_path_rgb, "tif", file_name_vector_l_rgb);

        std::vector<string> file_name_vector_r_rgb;
        getFilesFromFolder(r_path_rgb, "tif", file_name_vector_r_rgb);

        // for (size_t i = 0; i < nTimes; i++)
        for (size_t i = 0; i < nTimes; i++)
        {
            // 1:left  2:right
            int n = file_name_vector_l_gray[0].size();
            std::string file_name = file_name_vector_l_gray[0].substr(n - 44, 27);
            std::string file_name2 = file_name_vector_r_gray[0].substr(n - 44, 27); 
            std::string file_name3 = file_name_vector_l_rgb[0].substr(n - 44, 27);
            std::string file_name4 = file_name_vector_r_rgb[0].substr(n - 44, 27); 
            // std::string file_name = config_node["left_cam_prefix"].as<std::string>();
            // std::string file_name2 = config_node["right_cam_prefix"].as<std::string>();
            int batch = i*down_sample_ratio/3000;
            std::stringstream ss;
            ss << std::setfill('0') << std::setw(6) << i*down_sample_ratio+1;
            std::stringstream sss;
            sss << std::setfill('0') << std::setw(6) << batch;
            file_name = file_name + sss.str() + "_" + ss.str() + ".tif";
            file_name2 = file_name2 + sss.str() + "_" + ss.str() + ".tif";
            file_name3 = file_name3 + sss.str() + "_" + ss.str() + ".tif";
            file_name4 = file_name4 + sss.str() + "_" + ss.str() + ".tif";

            cv::Mat img = cv::imread(l_path + file_name, cv::IMREAD_GRAYSCALE);
            if (img.empty()){
                std::cout << "failed to read: " << l_path << file_name << std::endl;
                std::cout << "SHUT DOWN!" << std::endl;
                return 0;
            }
            cv::Mat img2 = cv::imread(r_path + file_name2, cv::IMREAD_GRAYSCALE);
            if (img2.empty()){
                std::cout << "failed to read: " << r_path <<file_name2 << std::endl;
                std::cout << "SHUT DOWN!" << std::endl;
                return 0;
            }
            cv::Mat img3 = cv::imread(l_path_rgb + file_name3, cv::IMREAD_COLOR);
            if (img3.empty()){
                std::cout << "failed to read: " << l_path_rgb << file_name3 << std::endl;
                std::cout << "SHUT DOWN!" << std::endl;
                return 0;
            }
            cv::Mat img4 = cv::imread(r_path_rgb + file_name4, cv::IMREAD_COLOR);
            if (img4.empty()){
                std::cout << "failed to read: " << r_path_rgb <<file_name4 << std::endl;
                std::cout << "SHUT DOWN!" << std::endl;
                return 0;
            }

            sensor_msgs::ImagePtr ros_image_msg = cv_bridge::CvImage(std_msgs::Header(), "mono8", img).toImageMsg();
            sensor_msgs::ImagePtr ros_image_msg2 = cv_bridge::CvImage(std_msgs::Header(), "mono8", img2).toImageMsg();

            sensor_msgs::ImagePtr ros_image_msg3 = cv_bridge::CvImage(std_msgs::Header(), "bgr8", img3).toImageMsg();
            sensor_msgs::ImagePtr ros_image_msg4 = cv_bridge::CvImage(std_msgs::Header(), "bgr8", img4).toImageMsg();

            ros_image_msg->header.stamp = ros::Time().fromSec(vTimeStamps[i]);
            ros_image_msg->header.frame_id = l_cam_topic;
            bag.write(l_cam_topic, ros::Time().fromSec(vTimeStamps[i]), ros_image_msg);

            ros_image_msg2->header.stamp = ros::Time().fromSec(vTimeStamps[i]);
            ros_image_msg2->header.frame_id = r_cam_topic;
            bag.write(r_cam_topic, ros::Time().fromSec(vTimeStamps[i]), ros_image_msg2);

            ros_image_msg3->header.stamp = ros::Time().fromSec(vTimeStamps_rgb[i]);
            ros_image_msg3->header.frame_id = l_cam_topic_rgb;
            bag.write(l_cam_topic_rgb, ros::Time().fromSec(vTimeStamps_rgb[i]), ros_image_msg3);

            ros_image_msg4->header.stamp = ros::Time().fromSec(vTimeStamps_rgb[i]);
            ros_image_msg4->header.frame_id = r_cam_topic_rgb;
            bag.write(r_cam_topic_rgb, ros::Time().fromSec(vTimeStamps_rgb[i]), ros_image_msg4);

            std::cout << "wrote frame: " << i+1 << std::endl;
        }

        std::cout << "---------end---------" << std::endl;
        
        bag.close();
    }

    return 0;
}