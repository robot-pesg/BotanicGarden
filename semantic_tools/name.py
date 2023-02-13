import os,sys

path = "1/"
dirs = os.listdir(path)

for file in dirs:
    if os.path.splitext(file)[1] == ".tif":
        new = file[34:]
        os.rename(file,new)
        print(new)