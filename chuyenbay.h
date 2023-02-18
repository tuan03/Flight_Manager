#ifndef CHUYENBAY_H
#define CHUYENBAY_H


#include"Global.h"

class Ve {
    public:
    char so_ve[MAX_LENGTH_SO_VE+1];
    char so_cmnd[MAX_LENGTH_SO_CMND+1];
};

class ListVe{
    int so_luong = 0;
    Ve first;
    Ve* next = NULL;
};
class ChuyenBay{
    public:
    char ma_cb[MAX_LENGTH_MA_CB+1];
    char thoi_gian_bay[MAX_LENGTH_TIME+1];
    char san_bay_den[MAX_LENGTH_SAN_BAY_DEN+1];
    int trang_thai;
	char so_hieu_mb[MAX_LENGTH_SO_HIEU_MB+1];
	ListVe danh_sach_ve;
};

class ListChuyenBay{ //theo thứ tự mã chuyến bay
    public:
	ChuyenBay first;
	ListChuyenBay *next = NULL;
};


#endif