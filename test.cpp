
#include<iostream>
#define MAX_LENGTH_SO_HIEU_MB 15
#define MAX_LENGTH_MA_CB 15
#define MAX_LENGTH_LOAI_MAY_BAY 40
#define MAX_MAYBAY 300
#define MAX_LENGTH_SAN_BAY_DEN 100
#define MAX_LENGTH_TIME 20
#define MAX_LENGTH_SO_CMND 15
#define MAX_LENGTH_HO 50
#define MAX_LENGTH_TEN 15
#define MAX_LENGTH_PHAI 100
#define MAX_LENGTH_SO_VE 4
#define MAX_LENGTH_ERROR_MESSAGE 100
#define MAX_SOCHO 300
#define MIN_SOCHO 20
enum ErrorCodes {
    LOI_HE_THONG_DAY_BO_NHO = 1,
};

class Error {
   public:
    int code = 0;
    char message[MAX_LENGTH_ERROR_MESSAGE + 1];
};

class MayBay{
    public:
    char so_hieu_mb[MAX_LENGTH_SO_HIEU_MB+1];
    char loai_mb[MAX_LENGTH_LOAI_MAY_BAY+1];
    int so_day;
	int so_dong;
};
class ListMayBay{
    public:
	MayBay *data[MAX_MAYBAY+1];
	int so_luong = 0;
};
class Ve {
   public:
    char so_ve[MAX_LENGTH_SO_VE + 1];
    char so_cmnd[MAX_LENGTH_SO_CMND + 1];
};


class ThoiGianBay {
   public:
    int minute;
    int hour;
    int day;
    int month;
    int year;
};

class ChuyenBay {
   public:
    char ma_so_cb[MAX_LENGTH_MA_CB + 1];
    ThoiGianBay thoi_gian_bay;
    char san_bay_den[MAX_LENGTH_SAN_BAY_DEN + 1];
    int trang_thai_cb;
    char so_hieu_mb[MAX_LENGTH_SO_HIEU_MB + 1];
    Ve *danh_sach_ve;
    ChuyenBay *next = NULL;
};

class DanhSachChuyenBay {
   public:
    ChuyenBay *head = NULL;
    ChuyenBay *tail = NULL;
};

class HanhKhach{
    public:
    char so_cmnd[MAX_LENGTH_SO_CMND+1]={};
    char ho[MAX_LENGTH_HO+1]={};
    char ten[MAX_LENGTH_TEN+1]={}; 
    char phai[MAX_LENGTH_PHAI+1]={};
};
class TreeHanhKhach{
    public:
	HanhKhach* data;
    TreeHanhKhach *left, *right;
};