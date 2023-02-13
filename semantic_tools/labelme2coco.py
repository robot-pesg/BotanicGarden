import argparse
import json
import matplotlib.pyplot as plt
import skimage.io as io
import cv2
#from labelme import utils
#
from image import img_b64_to_arr
#
import numpy as np
import glob
import PIL.Image
import PIL.ImageDraw

import os


class labelme2coco(object):
    def __init__(self, labelme_json=[], save_json_path='./new.json'):
        '''
        Args: labelme_json: paths of labelme json files
        : save_json_path: saved path 
        '''
        self.labelme_json = labelme_json
        self.save_json_path = save_json_path
        self.images = []
        self.categories = []
        self.annotations = []
        # self.data_coco = {}
        self.label = []
        self.annID = 1
        self.height = 0
        self.width = 0

        self.save_json()

    def data_transfer(self):
        for num, json_file in enumerate(self.labelme_json):
            with open(json_file, 'r') as fp:
                data = json.load(fp)
                (prefix, res) = os.path.split(json_file)
                (file_name, extension) = os.path.splitext(res)
                self.images.append(self.image(data, num, file_name))
                for shapes in data['shapes']:
                    label = shapes['label']
                    if label not in self.label:
                        self.categories.append(self.categorie(label))
                        self.label.append(label)
                    points = shapes['points']
                    self.annotations.append(
                        self.annotation(points, label, num))
                    self.annID += 1

    def image(self, data, num, file_name):
        image = {}
        #img = img_b64_to_arr(data['imageData'])

        height, width = 1200, 1920
        #img = None
        image['height'] = height
        image['width'] = width
        image['id'] = int(num+1)
        image['file_name'] = file_name + '.tif'

        self.height = height
        self.width = width

        return image

    def categorie(self, label):
        categorie = {}
        categorie['supercategory'] = label
        categorie['id'] = int(len(self.label)+1)
        categorie['name'] = label

        return categorie

    def annotation(self, points, label, num):
        annotation = {}
        annotation['iscrowd'] = 0
        annotation['image_id'] = int(num+1)
        # TODO: check the segementation result:OK
        # annotation['bbox'] = list(map(float, self.getbbox(points)))

        # # coarsely from bbox to segmentation
        # x = annotation['bbox'][0]
        # y = annotation['bbox'][1]
        # w = annotation['bbox'][2]
        # h = annotation['bbox'][3]
        # annotation['segmentation'] = [
        #     [x, y, x+w, y, x+w, y+h, x, y+h]]  # at least 6 points
        annotation['segmentation'] = [list(np.asarray(points).flatten())]
        annotation['category_id'] = self.getcatid(label)
        annotation['id'] = int(self.annID)
        # add area info
        # the area is not used for detection
        annotation['area'] = self.height * self.width
        return annotation

    def getcatid(self, label):
        for categorie in self.categories:
            if label == categorie['name']:
                return categorie['id']
            # if label[1]==categorie['name']:
            #     return categorie['id']
        return -1

    def getbbox(self, points):
        # img = np.zeros([self.height,self.width],np.uint8)
        # cv2.polylines(img, [np.asarray(points)], True, 1, lineType=cv2.LINE_AA)
        # cv2.fillPoly(img, [np.asarray(points)], 1)
        polygons = points
        mask = self.polygons_to_mask([self.height, self.width], polygons)
        return self.mask2box(mask)

    def mask2box(self, mask):
        # np.where(mask==1)
        index = np.argwhere(mask == 1)
        rows = index[:, 0]
        clos = index[:, 1]

        left_top_r = np.min(rows)  # y
        left_top_c = np.min(clos)  # x

        right_bottom_r = np.max(rows)
        right_bottom_c = np.max(clos)

        # [x1,y1,w,h] for coco box format
        return [left_top_c, left_top_r, right_bottom_c-left_top_c, right_bottom_r-left_top_r]

    def polygons_to_mask(self, img_shape, polygons):
        mask = np.zeros(img_shape, dtype=np.uint8)
        mask = PIL.Image.fromarray(mask)
        xy = list(map(tuple, polygons))
        PIL.ImageDraw.Draw(mask).polygon(xy=xy, outline=1, fill=1)
        mask = np.array(mask, dtype=bool)
        return mask

    def data2coco(self):
        data_coco = {}
        data_coco['images'] = self.images
        data_coco['categories'] = self.categories
        data_coco['annotations'] = self.annotations
        return data_coco

    def save_json(self):
        self.data_transfer()
        self.data_coco = self.data2coco()

        json.dump(self.data_coco, open(self.save_json_path, 'w',
                  encoding='utf-8'), indent=4, separators=(',', ': '), cls=MyEncoder)

# type check when save json files


class MyEncoder(json.JSONEncoder):
    def default(self, obj):
        if isinstance(obj, np.integer):
            return int(obj)
        elif isinstance(obj, np.floating):
            return float(obj)
        elif isinstance(obj, np.ndarray):
            return obj.tolist()
        else:
            return super(MyEncoder, self).default(obj)


# you need to modify the path according to your environment
labelme_json = glob.glob('train/*.json')

labelme2coco(labelme_json, 'annotations/train.json')
