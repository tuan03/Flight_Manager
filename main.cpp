#include <iostream>

#include "src/model/chuyenbay.h"
#include "src/model/error.h"
#include "src/model/file_handling.h"
#include "src/model/flight_manager.h"
#include "src/model/maybay.h"

char HAN[MAX_LENGTH_SAN_BAY_DEN + 1] = "HAN";
char SGN[MAX_LENGTH_SAN_BAY_DEN + 1] = "SGN";
char DAD[MAX_LENGTH_SAN_BAY_DEN + 1] = "DAD";
char CXR[MAX_LENGTH_SAN_BAY_DEN + 1] = "CXR";

int main() {
    char ma_so_cb_1[MAX_LENGTH_MA_CB + 1] = "CB001";
    char so_hieu_mb_1[MAX_LENGTH_SO_HIEU_MB + 1] = "MB003";
    ThoiGianBay thoi_gian_bay_1(35, 14, 24, 3, 2023);
    int trang_thai_cb_1 = 1;
    ChuyenBay* cb_1;
    cb_1 = new ChuyenBay(ma_so_cb_1, thoi_gian_bay_1, HAN, so_hieu_mb_1, trang_thai_cb_1);

    char ma_so_cb_2[MAX_LENGTH_MA_CB + 1] = "CB002";
    char so_hieu_mb_2[MAX_LENGTH_SO_HIEU_MB + 1] = "MB009";
    ThoiGianBay thoi_gian_bay_2(20, 8, 25, 3, 2022);
    int trang_thai_cb_2 = 0;
    ChuyenBay* cb_2;
    cb_2 = new ChuyenBay(ma_so_cb_2, thoi_gian_bay_2, SGN, so_hieu_mb_2, trang_thai_cb_2);

    char ma_so_cb_3[MAX_LENGTH_MA_CB + 1] = "CB003";
    char so_hieu_mb_3[MAX_LENGTH_SO_HIEU_MB + 1] = "MB002";
    ThoiGianBay thoi_gian_bay_3(45, 16, 4, 4, 2023);
    int trang_thai_cb_3 = 3;
    ChuyenBay* cb_3;
    cb_3 = new ChuyenBay(ma_so_cb_3, thoi_gian_bay_3, DAD, so_hieu_mb_3, trang_thai_cb_3);

    char ma_so_cb_4[MAX_LENGTH_MA_CB + 1] = "CB004";
    char so_hieu_mb_4[MAX_LENGTH_SO_HIEU_MB + 1] = "MB007";
    ThoiGianBay thoi_gian_bay_4(55, 11, 28, 3, 2022);
    int trang_thai_cb_4 = 1;
    ChuyenBay* cb_4;
    cb_4 = new ChuyenBay(ma_so_cb_4, thoi_gian_bay_4, CXR, so_hieu_mb_4, trang_thai_cb_4);

    char ma_so_cb_5[MAX_LENGTH_MA_CB + 1] = "CB005";
    char so_hieu_mb_5[MAX_LENGTH_SO_HIEU_MB + 1] = "MB004";
    ThoiGianBay thoi_gian_bay_5(10, 19, 29, 3, 2022);
    int trang_thai_cb_5 = 1;
    ChuyenBay* cb_5;
    cb_5 = new ChuyenBay(ma_so_cb_5, thoi_gian_bay_5, HAN, so_hieu_mb_5, trang_thai_cb_5);

    char ma_so_cb_6[MAX_LENGTH_MA_CB + 1] = "CB006";
    char so_hieu_mb_6[MAX_LENGTH_SO_HIEU_MB + 1] = "MB005";
    ThoiGianBay thoi_gian_bay_6(58, 19, 29, 3, 2022);
    int trang_thai_cb_6 = 1;
    ChuyenBay* cb_6;
    cb_6 = new ChuyenBay(ma_so_cb_6, thoi_gian_bay_6, HAN, so_hieu_mb_6, trang_thai_cb_6);

    ListChuyenBay danh_sach_cb;

    danh_sach_cb.insert_last(cb_1);
    danh_sach_cb.insert_last(cb_2);
    danh_sach_cb.insert_last(cb_3);
    danh_sach_cb.insert_last(cb_4);
    danh_sach_cb.insert_last(cb_5);
    danh_sach_cb.insert_last(cb_6);

    danh_sach_cb.print();

    std::cout << "\n";

    ThoiGianBay thoi_gian_bay_de_loc(58, 19, 29, 3, 2022);
    ListChuyenBay danh_sach_cb_sau_khi_loc = danh_sach_cb.tim_cac_cb_con_ve_trong_ngay(HAN, thoi_gian_bay_de_loc);

    std::cout << ">>> Danh sach chuyen bay tra cuu:\n";
    danh_sach_cb_sau_khi_loc.print();
    std::cout << ">>> So luong ve con trong:\n";
    danh_sach_cb_sau_khi_loc.dem_so_luong_ve_con_trong_cua_cac_cb();
    std::cout << ">>> Gio khoi hanh cua cac chuyen bay:\n";
    danh_sach_cb_sau_khi_loc.gio_khoi_hanh_cua_cac_cb();

    std::cout << "\n";
    bool dk = danh_sach_cb.kiem_tra_chuyen_bay_ton_tai_trong_danh_sach(ma_so_cb_6);
    if (dk)
        std::cout << ">>> Yes!";
    else
        std::cout << ">>> No!";

    std::cout << "\n";
    Status status = danh_sach_cb.them_cb_moi_vao_danh_sach_co_bat_loi(cb_3);
    std::cout << ">>> Loi: " << status.get_status();
    std::cout << "\n";
    danh_sach_cb.print();

    return 0;
}