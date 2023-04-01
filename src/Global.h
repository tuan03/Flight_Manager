#ifndef GLOBAL_H
#define GLOBAL_H



#include <iostream>
#include <cstring>
#include<string>
#include<sstream>
#include<iomanip>
#include<fstream>
#include<cmath>
#include <cstdio>
#include<ctime>





using namespace std;

//class máy bay
#define MAX_LENGTH_SO_HIEU_MB 15
#define MAX_LENGTH_LOAI_MAY_BAY 40 
#define MAX_MAYBAY 300

// class chuyến bay
#define MAX_LENGTH_MA_CB 15
#define MAX_LENGTH_SAN_BAY_DEN 100
#define MAX_LENGTH_TIME 5
#define MAX_LENGTH_TIME_STRING 15
#define MAX_LENGTH_SO_CMND 15
#define MAX_LENGTH_HO 50
#define MAX_LENGTH_TEN 15
#define MAX_LENGTH_PHAI 100
#define MAX_LENGTH_SO_VE 4
#define MAX_LENGTH_ERROR_MESSAGE 100
#define MAX_SOCHO 300
#define MIN_SOCHO 20


#define FILE_PATH_DATA_CHUYEN_BAY "data/data_chuyen_bay.txt"
#define FILE_PATH_DATA_HANH_KHACH "data/data_hanh_khach.txt"
#define FILE_PATH_DATA_MAY_BAY "data/data_may_bay.txt"


#define X_START_BODY 50
#define Y_START_BODY 150

#define X_START_TABLE 150
#define Y_START_TABLE 290
#define HEIGHT_TABLE 500
#define WIDTH_TABLE 1500

#define WIDTH_SCREEN 1800
#define HEIGHT_SCREEN 950

#define COLOR_HOVER_LINE {99,130,28, 255}
#define COLOR_MENU_CHILD  {255,115,115}
//{232,186,236,255}

#endif