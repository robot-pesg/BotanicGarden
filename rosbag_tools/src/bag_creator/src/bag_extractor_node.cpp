#include <rosbag/bag.h>
#include <rosbag/view.h>

#include <sensor_msgs/Image.h>
#include <boost/foreach.hpp>
#include <cv_bridge/cv_bridge.h>
#include <opencv2/imgcodecs.hpp>

#include <yaml-cpp/yaml.h>


int main(int argc, char **argv)
{
    rosbag::Bag bag;
    std::string config_file_path = std::string(argv[1]);
    YAML::Node config_node = YAML::LoadFile(config_file_path);
    std::string input_bag_path = config_node["input_bag_path"].as<std::string>();
    std::string bag_name = config_node["bag_name"].as<std::string>();
    std::string bag_path = input_bag_path + bag_name;

    std::string output_folder_path = config_node["output_folder_path"].as<std::string>();
    std::string output_image_prefix = config_node["output_image_prefix"].as<std::string>();
    std::string output_image_format = config_node["output_image_format"].as<std::string>();

    bag.open(bag_path, rosbag::bagmode::Read);

    std::string l_cam = config_node["cam_topic"].as<std::string>();

    int down_sample_ratio = config_node["down_sample_ratio"].as<int>();

    // Image topics to load
    std::vector<std::string> topics;
    topics.push_back(l_cam);

    rosbag::View view(bag, rosbag::TopicQuery(topics));

    // ros::Time bag_begin_time = view.getBeginTime();
    // ros::Time bag_end_time = view.getEndTime();

    // std::cout << "ROS bag time: " << (bag_end_time-bag_begin_time).toSec() << "(s)" << std::endl;
    int value = 0;
    BOOST_FOREACH(rosbag::MessageInstance const m, view){
        if (m.getTopic() == l_cam || ("/" + m.getTopic() == l_cam))
        {
            value++;
            if (value % down_sample_ratio != 0){
                continue;
            }
            const ros::Time time = m.getTime();
            std::cout << time << std::endl;
            sensor_msgs::Image::ConstPtr l_img = m.instantiate<sensor_msgs::Image>();
            if (l_img != NULL){
                cv_bridge::CvImagePtr cv_ptr;
                cv_ptr = cv_bridge::toCvCopy(l_img, l_img->encoding);
                std::string s = std::to_string(value);
                std::string file_name = output_folder_path + output_image_prefix + s + output_image_format;                
                cv::imwrite(file_name, cv_ptr->image);
            }
        }
    }
    
    bag.close();

    return 0;
}