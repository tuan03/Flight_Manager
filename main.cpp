// biến const : in hoa + snake_case
// class : PascalCase
// biến :  chữ thường + snake_case hoặc cameCase
// biến trong class: chữ thường + cameCase
//tên hàm: cameCase

#include"Global.h"

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


class HanhKhach{
    public:
    char so_cmnd[MAX_LENGTH_SO_CMND+1];
    char ho[MAX_LENGTH_HO+1];
    char ten[MAX_LENGTH_TEN+1]; 
    char phai[MAX_LENGTH_PHAI+1];
};

struct NodeHanhKhach{
    public:
	HanhKhach data;
	NodeHanhKhach *left = NULL;
	NodeHanhKhach *right= NULL;
};
int main(){
    ListMayBay ds_maybay;
    ListChuyenBay ds_chuyenbay;
    NodeHanhKhach ds_hanhkhach;
}