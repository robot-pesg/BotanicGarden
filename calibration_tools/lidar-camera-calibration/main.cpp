#include<iostream>
#include"single_chessboard.h"
#include"calibration.h"
extern void load_python_script();
int main(int argc,char** argv){

    calibration object;
    object.compute();

    return 0;
}