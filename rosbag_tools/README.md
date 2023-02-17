# Rosbag Tools Scripts

## Introduction

Our dataset is captured in rosbag and raw formats. For the convenience of usage, we have provided a toolbox to convert between different structures.

## Build Rosbag Tools on ROS

```bash
cd /{YOUR_PATH}/rosbag_tools
catkin_make
source /devel/setup.bash
```

## Usage
**Append your images into a bag file：**

You can use this tool to add images to an existing bag file using the following command:

`rosrun bag_creator bag_append_node config_file_path`

The yaml file format and interpretation is as follows:

- `image_folder_path`：the path of images that needs to be added to the bag
For example, in the sequence 1005_01, there are two grayscale cameras and two RGB cameras. Two grayscale cameras are named c4a3a4 and c4a3a8, and two color cameras are named c54d7a and c54d79. The folder structure should be /{YOUR_PATH}/1005_01/c4a3a4/{c4a3a4 images}, /{YOUR_PATH}/1005_01/c4a3a8/{c4a3a8 images} and so on, Only enter /{YOUR_PATH}/1005_01/ here.
- `timestamp_file_path`：the path of timestamp file
- `bag_names`：the original bag to be added
- `down_sample_ratio`: image downsampling frequency.
For example, if the original picture is collected at 40Hz, and the corresponding timestamp file records 40Hz information, when down_sample_ratio is set to 4, the picture will be added to the bag at a frequency of 10Hz
- `left_cam_topic`：topic of left gray camera
- `right_cam_topic`：topic of right gray camera
- `left_cam_topic_rgb`：topic of left rgb camera
- `right_cam_topic_rgb`：topic of right rgb camera

see the yaml sample file [settings_for_append.yaml](./src/bag_creator/config/settings_for_append.yaml)

**Create a new bag with your images:**

You can create a new bag file from an existing image file using the following command:

`rosrun bag_creator bag_creator_node config_file_path`

The yaml file meaning of this tool is exactly the same as the append tool, please see the append section.

see the yaml sample file [settings_for_creator.yaml](./src/bag_creator/config/settings_for_creator.yaml)

**Extract images from existing bag file:**

You can extract topic-specific images from the bag using the following command:

`rosrun bag_creator bag_extractor_node config_file_path`

The yaml file format and interpretation is as follows:

- `down_sample_ratio`：how many frames to output a picture every
- `input_bag_path`：the path of input bag
- `bag_name`：bag name
- `output_folder_path`：the path of images output
- `output_image_prefix`：the prefix of the image output
- `output_image_format`：the format of the image output
- `cam_topic`：the image topic to output

see the yaml sample file [settings_for_extractor.yaml](./src/bag_creator/config/settings_for_extractor.yaml)



