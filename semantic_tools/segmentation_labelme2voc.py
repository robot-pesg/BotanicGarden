# coding=utf-8

from __future__ import print_function

import argparse
import glob
import json
import os
import os.path as osp

import numpy as np
import PIL.Image

import labelme
import progressbar
import sys
from labelme import utils


# reference: https://github.com/wkentaro/labelme/tree/master/examples/semantic_segmentation
def main():
    parser = argparse.ArgumentParser(
        formatter_class=argparse.ArgumentDefaultsHelpFormatter)
    parser.add_argument('labels_file', help='INPUT: dir with annotated files')
    parser.add_argument('jsons_dir', help='INPUT: dir with annotated files')
    parser.add_argument('voc_dir', help='OUTPUT: voc dataset directory')
    args = parser.parse_args()

    if not osp.exists(args.jsons_dir):
        print("directory not exists, ", args.jsons_dir)
        sys.exit(1)

    if not osp.exists(args.voc_dir):
        os.makedirs(args.voc_dir)
    if not osp.exists(osp.join(args.voc_dir, 'JPEGImages')):
        os.makedirs(osp.join(args.voc_dir, 'JPEGImages'))
    if not osp.exists(osp.join(args.voc_dir, 'SegmentationClass')):
        os.makedirs(osp.join(args.voc_dir, 'SegmentationClass'))
    if not osp.exists(osp.join(args.voc_dir, 'SegmentationClassPNG')):
        os.makedirs(osp.join(args.voc_dir, 'SegmentationClassPNG'))
    if not osp.exists(osp.join(args.voc_dir, 'SegmentationClassVisualization')):
        os.makedirs(osp.join(args.voc_dir, 'SegmentationClassVisualization'))
    print('Creating dataset:', args.voc_dir)

    class_names = []
    class_name_to_id = {}
    for i, line in enumerate(open(args.labels_file, "r", encoding='UTF-8').readlines()):
        class_id = i - 1  # starts with -1
        class_name = line.strip()
        class_name_to_id[class_name] = class_id
        if class_id == -1:
            assert class_name == '__ignore__'
            continue
        elif class_id == 0:
            assert class_name == '_background_'
        class_names.append(class_name)
    class_names = []
    class_names = tuple(class_names)
    print('class_names:', class_names)
    out_class_names_file = osp.join(args.voc_dir, 'seg_class_names.txt')
    with open(out_class_names_file, 'w') as f:
        f.writelines('\n'.join(class_names))
    print('Saved class_names:', out_class_names_file)

    colormap = labelme.utils.label_colormap(255)

    # 3. Process Every Json File
    label_file_list = glob.glob(osp.join(args.jsons_dir, '*.json'))
    for i in progressbar.progressbar(range(len(label_file_list))):
        label_file = label_file_list[i]
        # print('Generating dataset from:', label_file)
        with open(label_file, "r", encoding='UTF-8') as f:
            base = osp.splitext(osp.basename(label_file))[0]
            out_img_file = osp.join(
                args.voc_dir, 'JPEGImages', base + '.jpg')
            out_lbl_file = osp.join(
                args.voc_dir, 'SegmentationClass', base + '.npy')
            out_png_file = osp.join(
                args.voc_dir, 'SegmentationClassPNG', base + '.png')
            out_viz_file = osp.join(
                args.voc_dir, 'SegmentationClassVisualization', base + '.jpg')

            data = json.load(f)

            # labelme annotated file contains source image data(serialized)
            imageData = data.get('imageData')
            if imageData:
                img = utils.img_b64_to_arr(imageData)
            else:
                img_file = osp.join(osp.dirname(label_file), data['imagePath'])
                img = np.asarray(PIL.Image.open(img_file))
            PIL.Image.fromarray(img).save(out_img_file)

            lbl = labelme.utils.shapes_to_label(
                img_shape=img.shape,
                shapes=data['shapes'],
                label_name_to_value=class_name_to_id,
            )
            labelme.utils.lblsave(out_png_file, lbl)

            np.save(out_lbl_file, lbl)

            viz = labelme.utils.draw_label(
                lbl, img, class_names, colormap=colormap)
            PIL.Image.fromarray(viz).save(out_viz_file)


if __name__ == '__main__':
    main()
