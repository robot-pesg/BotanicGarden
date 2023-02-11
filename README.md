# BotanicGarden Dataset
## A high-quality and large-scale robot navigation dataset in challenging natural environments

## Authors: 
[Yuanzhi Liu](https://github.com/lyzrose), Yujia Fu, [Minghui Qin](https://github.com/SJTU-qin), [Yufeng Xu](https://github.com/feng15423), [Baoxin Xu](https://github.com/xbx1), et al.

<!-- <div align="center">
<img src="./pics/bev_map/bev_whole.png" alt="photo" width="60%" />
</div> -->
<div align="left">
<img src="./pics/robot_pics/fig1-2.jpg" alt="photo" height="200" hspace="5"/>
<img src="./pics/robot_pics/fig1-3.png" alt="photo" height="200" />
</div>

## Abstract: 
The rapid developments of mobile robotics and autonomous navigation over the years are largely empowered by public datasets for testing and upgradation, such as SLAM and localization tasks. Impressive demos and benchmark results have arisen, indicating the establishment of a mature technical framework. However, from the real-world deployments point of view, there are still critical defects of robustness in challenging environments, especially in large-scale, GNSS-denied, textural-monotonous, and unstructured scenarios. To meet the urgent validation demands in such scope, we build a novel challenging robot navigation dataset in a large botanic garden of more than 48000m2. Comprehensive sensors are employed, including high-res/rate stereo Gray&RGB cameras, rotational and forward 3D LiDARs, and low-cost and industrial-grade IMUs, all of which are well calibrated and hardware-synchronized to nanoseconds accuracy. An all-terrain wheeled robot is configured to mount the sensor suite and providing odometry data. A total of 32 long and short sequences of 2.3 million images are collected, covering scenes of thick woods, riversides, narrow paths, bridges, and grasslands that rarely appeared in previous resources. Excitedly, both highly-accurate ego-motions and 3D map ground truth are provided, along with fine-annotated vision semantics. Our goal is to contribute a high-quality dataset to advance robot navigation and sensor fusion research to a higher level.

<div align="left">
<img src="./pics/photo_pairs/cam/c_01.jpg" alt="photo" width="18%" />
<img src="./pics/photo_pairs/cam/c_02.jpg" alt="photo" width="18%" />
<img src="./pics/photo_pairs/cam/c_03.jpg" alt="photo" width="18%" />
<img src="./pics/photo_pairs/cam/c_04.jpg" alt="photo" width="18%" />
<img src="./pics/photo_pairs/cam/c_05.jpg" alt="photo" width="18%" />
<img src="./pics/photo_pairs/map/m_01.jpg" alt="photo" width="18%" />
<img src="./pics/photo_pairs/map/m_02.jpg" alt="photo" width="18%" />
<img src="./pics/photo_pairs/map/m_03.jpg" alt="photo" width="18%" />
<img src="./pics/photo_pairs/map/m_04.jpg" alt="photo" width="18%" />
<img src="./pics/photo_pairs/map/m_05.jpg" alt="photo" width="18%" />
<img src="./pics/photo_pairs/sem/s_01.png" alt="photo" width="18%" />
<img src="./pics/photo_pairs/sem/s_02.png" alt="photo" width="18%" />
<img src="./pics/photo_pairs/sem/s_03.png" alt="photo" width="18%" />
<img src="./pics/photo_pairs/sem/s_04.png" alt="photo" width="18%" />
<img src="./pics/photo_pairs/sem/s_05.png" alt="photo" width="18%" />
</div>

## Main Contributions: 
- We build a novel multi-sensory dataset in a large botanic garden, with a total of 32 long &short sequences and ~2.3 million images which contain diverse challenging natural factors that rarely seen in previous resources.
- We employed comprehensive sensors, including high-res and high-rate stereo Gray&RGB cameras, rotational and forward-facing 3D LiDARs, and low-cost and industrial-grade IMUs, supporting a wide range of applications. By elaborate development of the integrated system, we have achieved synchronization of nanoseconds accuracy. Both the sensors and sync-quality are at top-level of this field.
- We provide both highly-accurate 3D map and trajectories ground truth by dedicated surveying works and advanced map-based localization algorithm. We also provide dense vision semantics labeled by experienced annotators. This is the first robot navigation dataset that provides such all-rounded and high-quality reference data.

<div align="left">
<img src="./gifs/sequences/1005_00.gif" alt="video" width="80%" />
</div>

## Sensor Setup

Sensor/Device|Model|Specification
:--:|:--:|:--:
Gray Stereo | DALSA M1930 | 1920*1200, 2/3", 71°×56°FoV, 40Hz
RGB Stereo | DALSA C1930 | 1920*1200, 2/3", 71°×56°FoV, 40Hz
LiDAR | Velodyne VLP16 | 16C, 360°×30°FoV, ±3cm@100m, 10Hz
MEMS LiDAR | Livox AVIA | 70°×77°FoV, ±2cm@200m, 10Hz
D-GNSS/INS | Xsens Mti-680G | 9-axis, 400Hz, GNSS not in use
Consumer IMU | BMI088 | 6-axis, 200Hz, Livox built-in
Wheel Encoder | Scout V1.0 | 4WD, 3-axis, 200Hz
GT 3D Scanner | Leica RTC360 | 130m range, 1mm+10ppm accuracy

## Time Synchronization

<div align="left">
<img src="./pics/pulse_sync.png" alt="photo" width="60%" />
</div>

## Ground Truth Map
<div align="left">
<img src="./pics/bev_map/bev_whole.png" alt="photo" width="48%" />
</div>

<div align="left">
<img src="./pics/scan/scan_workphoto.jpg" alt="photo" height="200" hspace="5"/>
<img src="./pics/scan/fig6-2.png" alt="photo" height="200" />
</div>

<!-- <div align="center">
<img src="./pics/leica_workphoto.png" alt="photo" width="80%" />
</div> -->

## Sample Sequences
Stat/Sequence|1005-00|1005-01|1005-07|1006-01|1008-03|1018-00|1018-13
:--:|:--:|:--:|:--:|:--:|:--:|:--:|:--:
Duration/s|583.78|458.91|541.52|738.70|620.29|131.12|194.36
Distance/m|598.46|477.92|587.52|761.41|747.26|114.12|199.93
Size/GB|66.8|49.0|59.8|83.1|71.0|13.0|20.9

## Ground Truth Trajectories
<div align="left">
<img src="./pics/gt_poses/fig7-1.png" alt="photo" height="200" hspace="5"/>
<img src="./pics/gt_poses/fig7-2.png" alt="photo" height="200" />
</div>

## Semantic Dense Annotations
All data are provided in LabelMe format and support future reproducing. It is expected that these data can strengthen the abilities of robust motion estimation and semantic map paintings.
<div align="left">
<img src="./gifs/semantics/new/JPEG_480×300.gif" alt="video" width="40%" />
<img src="./gifs/semantics/new/SegmentationVisualization_480×300.gif" alt="video" width="40%" />
<!-- <img src="./gifs/semantics/raw/2_JPEG_960×600.gif" alt="video" width="48%" />
<img src="./gifs/semantics/raw/2_SegmentationVisualization_960×600.gif" alt="video" width="48%" />
<img src="./gifs/semantics/raw/3_JPEG_960×600.gif" alt="video" width="48%" />
<img src="./gifs/semantics/raw/3_SegmentationVisualization_960×600.gif" alt="video" width="48%" />
<img src="./gifs/semantics/raw/4_JPEG_960×600.gif" alt="video" width="48%" />
<img src="./gifs/semantics/raw/4_SegmentationVisualization_960×600.gif" alt="video" width="48%" />
<img src="./gifs/semantics/raw/5_JPEG_960×600.gif" alt="video" width="48%" />
<img src="./gifs/semantics/raw/5_SegmentationVisualization_960×600.gif" alt="video" width="48%" /> -->
</div>

## Toolbox
Our dataset is captured in rosbag and raw formats. For the convenience of usage, we have provided a toolbox to convert between different structures, check the [rosbag_tools](./rosbag_tools/) folder for usage.

## Acknowledgement
The authors would like to thank the colleagues from Tongji University and Sun Yat-sen University for their assistances in the rigorous survey works and post-processings, especially Xiaohang Shao, Chen Chen, and Kunhua Liu. We also thank A/Prof. Hangbin Wu for his guidance in data collection. Besides, we acknowledge Grace Xu from Livox for the support on AVIA LiDAR, and we appreciate the colleagues of Appen for their professional work in visual semantic annotations. Yuanzhi Liu would like to thank Jingxin Dong for her job-loggings and photographs during our data collection.

## Funding
This work was supported by National Key R&D Program of China under Grant 2018YFB1305005.

## Contact
Yuanzhi Liu: lyzrose@sjtu.edu.cn