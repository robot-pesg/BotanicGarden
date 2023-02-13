# 全景分割数据集转换脚本

## 简介

仓库中的脚本用于将Labelme标注的数据转换为PASCAL VOC格式或MS COCO格式的标准数据集，便于直接利用现有的训练框架进行训练。

**使用须知:** 脚本只提供segmentation的转换。

## 标注工具和常见的两种数据集格式

原始标注格式对应Labelme版本为3.5.0。Labelme工具的GitHub地址如下：

[labelme: Image Polygonal Annotation with Python](https://github.com/wkentaro/labelme)

PASCAL-VOC和MS-COCO是两个大型的开源数据集，其数据集的标注形式成为了通用的标注方式，常见的视觉模型的训练框架都支持这两种格式的读取，将自己的数据集转换为这两种标注方式，可以避免修改读取数据的代码。

两种数据集和标注格式的介绍：

[数据集PASCAL VOC简介](https://arleyzhang.github.io/articles/1dc20586/)

[数据集MSCOCO简介](https://arleyzhang.github.io/articles/e5b86f16/)

## 仓库中的代码文件

- `COCO_Image_Viewer.ipynb`：COCO格式标注可视化
- `labelme2coco.py`：批量处理labelme标注的json文件，转换成COCO格式的数据集,需要自行划分训练集和验证集.路径,图片格式以及输出文件名称可以自行修改。
- `segmentation_labelme2voc.py`：将labelme标注的json文件转换为VOC文件下下的语义分割标注文件。三种类型，`.npy`，`.png`和可视化图像。
- `image.py`: 内置一些简单的转换函数。

## 安装

[labelme](https://github.com/wkentaro/labelme):

```bash
# python3
conda create --name=labelme python=3.6
conda activate labelme
pip3 install labelme==3.5.0
```

其他工具：

```bash
pip3 install progressbar2    # 进度条
pip3 install scikit-learn  # 用于分割数据集 
pip3 install xmltodict
pip3 install lxml
pip3 install opencv-python==3.4.9.31
pip3 install PyQt5-sip
pip3 install PyQt5
```

## 使用流程

### 转换为VOC风格的语义分割数据集和可视化图片

**用法：**

`python segmentation_labelme2voc.py seg_labels_file jsons_dir voc_dir`

- `seg_labels_file`：与标注对应的标签文件
- `jsons_dir`：包含标注文件的文件夹
- `voc_dir`：目标文件夹

**举例：**

`python segmentation_labelme2voc.py test/label_names.txt test/test_jsons test/test_voc`

### 转换为COCO数据集

**用法：**

`python labelme2coco.py`

- `voc_dir `：VOC数据集根目录
- `voc_split`：训练集或测试集文件名称，例如train或test
- `coco_dir`：COCO数据集根目录，脚本创建
- `anno_file`：与训练集或测试集对应的COCO数据集Json标注文件，保存在 `coco_dir/annotations`文件夹下。

**举例：**

`python voc_xml2coco_json.py test/test_voc train test/test_coco train.json`

## Acknowledgments


[labelme2Datasets](https://github.com/veraposeidon/labelme2Datasets)

[Labelme2Coco](https://github.com/XCRobert/Labelme2Coco)

