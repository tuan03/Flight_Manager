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