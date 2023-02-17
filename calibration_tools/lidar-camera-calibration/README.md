# 3D_reconstruct_base_on_2D_image
This reposity constructs 3D point cloud based on 2D images containing chessboard.
# dependency library
[opencv](https://opencv.org/), [PCL](https://pointclouds.org/)
# usage
## put images containing chessboards in certain folders
In this step, you should get more than 10 images containing single chessboard and 1 image which you want to reconstruct 3D based on.
The above 10 images should be put in folder named [images](https://github.com/xbx1/3D_reconstruct_base_on_2D_image/tree/main/images), and notice that the naming regulation should be like the example. The target image which you want to reconstruct should be put in [taget_image folder](https://github.com/xbx1/3D_reconstruct_base_on_2D_image/tree/main/target_image).
## rewrite config files
There are two config files in folder [config](https://github.com/xbx1/3D_reconstruct_base_on_2D_image/tree/main/config).
### camera.xml
Containing camera intrinsic.
### target.yaml
```
image_folder : "/home/uu/Documents/L515_ros_ws/src/github_tutorial/rqt_mypkg/rqt_example_cpp/data/image_shoots"# single chessboard images folder
target_image : "/home/uu/Documents/L515_ros_ws/L515.jpg"# target image 
pattern_size : [6,7]# chessboard pattern
grid_size : 50 #mm # chessboard grid size
key_board_num : 3 # number of chessboard contained in target image

white: !!opencv-matrix # color of white grid of chessboard point cloud, in range[0,1]
   rows: 1
   cols: 3
   dt: d
   data: [ 0.60784314, 0.70588235, 0.68627451 ]
black: !!opencv-matrix # color of black grid of chessboard point cloud, in range[0,1]
   rows: 1
   cols: 3
   dt: d
   data: [ 0.80784314, 0.9372549 , 0.95294118 ]
```
# result
## point cloud from lidar
<img src="https://github.com/xbx1/github_display_files/blob/main/3dconstruct/original%20cloud.png"/>

## reconstruct result
<img src="https://github.com/xbx1/github_display_files/blob/main/3dconstruct/reconstruct_result.png"/>

## ICP result
<img src="https://github.com/xbx1/github_display_files/blob/main/3dconstruct/ICP_result.png"/>
