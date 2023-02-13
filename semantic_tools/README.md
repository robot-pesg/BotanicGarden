# Panoptic Segmentation Scripts

## Introduction

Scripts in this repository are used to convert labelme-annotated jsons into standard datasets in PASCAL VOC format or MS COCO format.


**Attention:** These scripts are only for the conversion of segmentation data.



## About the scripts

- `COCO_Image_Viewer.ipynb`：COCO-format visualization
- `labelme2coco.py`：Convert a folder of jsons into coco-format segmentation dataset:
- `segmentation_labelme2voc.py`：Convert a folder of jsons into voc-format segmentation dataset and visualization pictures
- `image.py`: Some simple functions。

## Getting Started

[labelme](https://github.com/wkentaro/labelme):

```bash
# python3
conda create --name=labelme python=3.6
conda activate labelme
pip3 install labelme==3.5.0
```

Other tools：

```bash
pip3 install progressbar2    # 进度条
pip3 install scikit-learn  # 用于分割数据集 
pip3 install xmltodict
pip3 install lxml
pip3 install opencv-python==3.4.9.31
pip3 install PyQt5-sip
pip3 install PyQt5
```

## Usage


**convert a folder of jsons into voc-format segmentation dataset and visualization pictures：**

`python segmentation_labelme2voc.py seg_labels_file jsons_dir voc_dir`

- `seg_labels_file`：labels json file
- `jsons_dir`：json dictionary
- `voc_dir`：output dictionary

**Example：**

`python segmentation_labelme2voc.py test/label_names.txt test/test_jsons test/test_voc`

**convert a folder of jsons into coco-format segmentation dataset:**

`python labelme2coco.py`

## Acknowledgments

[labelme2Datasets](https://github.com/veraposeidon/labelme2Datasets)

[Labelme2Coco](https://github.com/XCRobert/Labelme2Coco)
