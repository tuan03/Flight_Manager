#ifndef FLIGHT_MANAGER_H
#define FLIGHT_MANAGER_H

#include "maybay.h"
#include "hanhkhach.h"
#include "chuyenbay.h"

class Flight_Manager
{
private:
    ListMayBay ds_maybay;
    ListChuyenBay ds_chuyenbay;
    TreeHanhKhach ds_hanhkhach;

public:
    ListMayBay &getListMB()
    {
        return ds_maybay;
    }
    ListChuyenBay &getListCB()
    {
        return ds_chuyenbay;
    }
    TreeHanhKhach &getListHK()
    {
        return ds_hanhkhach;
    }
    Flight_Manager()
    {
        ds_maybay.read_bin(DATA_MAY_BAY);
        ds_chuyenbay.read_bin(DATA_CHUYEN_BAY, ds_maybay);
        ds_hanhkhach.read_bin(DATA_HANH_KHACH);
    }

    ~Flight_Manager()
    {
        ds_maybay.write_bin(DATA_MAY_BAY);
        ds_chuyenbay.write_bin(DATA_CHUYEN_BAY);
        ds_hanhkhach.write_bin(DATA_HANH_KHACH);
        cout<<"Completed Saved\n";
    }

    Status del_mb_by_index(int index)
    {
        if (index == -1)  return Status("Không Tìm Thấy Máy Bay.");
        if (this->ds_chuyenbay.find_by_sh_mb_v2(ds_maybay.get_at(index)->getSoHieuMB()))  return Status("Xóa Thất Bại, Máy Bay Đã Lập Chuyến Bay.");
        this->ds_maybay.del(index);
        return Status("Xóa Thành Công.", Status_Name::SUCCESS);
    }

    Status edit_chuyen_bay(ChuyenBay *cb, int minute, int hour, int day, int month, int year, const char *san_bay_den, const char *so_hieu_mb)
    {
        // check error
        Time thoi_gian_bay(minute, hour, day, month, year);
        if (!thoi_gian_bay.isValidDate())
            return Status("Ngày Giờ Không Hợp Lệ !");
        if (cb->get_trang_thai_cb() == 2 || cb->get_trang_thai_cb() == 3)
            return Status("Không thể sửa thông tin của chuyến bay đang bay hoặc hoàn tất");
        MayBay *mb = this->ds_maybay.find_mamb_ct(so_hieu_mb);
        if (mb == nullptr)
            return Status("Số hiệu máy bay không tồn tại");
        Time current_time;
        current_time.get_current_time();
        double difference = Time::timeDiffInSeconds(current_time, thoi_gian_bay);
        if (difference <= 60 * 60 * 2)
            return Status("Thời gian lập chuyến bay phải lớn hơn thòi gian hiện tại 2 giờ");
        if (difference > 60 * 60 * 24 * 365)
            return Status("Thời gian lập chuyến bay chỉ được phép trong vòng 365 ngày");
        // edit
        cb->set_thoi_gian_bay(thoi_gian_bay);
        cb->set_san_bay_den(san_bay_den);
        cb->set_so_hieu_mb(so_hieu_mb);
        return Status("Sửa thông tin chuyến bay thành công", Status_Name::SUCCESS);
    }

    Status add_cb(const char *ma_so_cb, int minute, int hour, int day, int month, int year, const char *san_bay_den, const char *so_hieu_mb)
    {
        if (ds_chuyenbay.find_by_ma_cb(ma_so_cb))
        {
            return Status("Mã Chuyến Bay Đã Tồn Tại");
        }
        MayBay *temp = ds_maybay.find_mamb_ct(so_hieu_mb);
        if (temp == nullptr)
        {
            return Status("Số Hiệu Máy Bay Không Tồn tại");
        }
        Time time(minute, hour, day, month, year);
        if (!time.isValidDate())
        {
            return Status("Thời Gian Không Hợp Lệ");
        }

        Time current_time;
        current_time.get_current_time();

        if (Time::timeDiffInSeconds(current_time, time) < 3600)
        {
            return Status("Chỉ Được Lập Chuyến Bay Cách Thời Gian Hiện Tại 1 Giờ");
        }
        if (Time::timeDiffInSeconds(current_time, time) > 3600 * 24 * 365)
        {
            return Status("Chỉ Được Lập Chuyến Bay Trong Vòng 365 Ngày");
        }
        // có case : tồn tại nhiều chuyến bay đúng quy định với mã máy bay này, // sữa sau
        // thêm cái check kể từ lúc hoàn thành 12h nữa, còn thiếu
        // ChuyenBay* cb = ds_chuyenbay.find_by_sh_mb_ct(so_hieu_mb);
        // if(cb != nullptr){
        //     if(cb->get_trang_thai_cb() == 3){
        //         return Status("");
        //     }
        // }
        ChuyenBay *new_chuyenbay = new ChuyenBay(ma_so_cb, time, san_bay_den, so_hieu_mb, 1);
        new_chuyenbay->get_listve().init_ve(temp->getSoDay(), temp->getSoDong());

        ds_chuyenbay.insert_order(new_chuyenbay);
        return Status("Thêm Chuyến Bay Thành Công", Status_Name::SUCCESS);
    }

    // void filter_list_cb(int page, const char *ma_cb, int day, int month, int year, const char *noi_den)
    // { // 1 page hiển thị 10 line
    //     ChuyenBay *current = ds_chuyenbay.get_head();
    //     while (current != nullptr)
    //     {
    //         if (Func_Global::check_prefix(current->get_ma_so_cb(), ma_cb) && Func_Global::check_prefix(current->get_san_bay_den(), noi_den))
    //         {
    //             cout << *current << "\n";
    //         }
    //         current = current->get_next();
    //     }
    // }

    Status dat_ve_khachquen(ChuyenBay *chuyenbay, int so_day, int so_dong, const char *cmnd)
    {
        return chuyenbay->get_listve().add_ve(so_day, so_dong, cmnd);
    }
    Status dat_ve_khachmoi(ChuyenBay *chuyenbay, int so_day, int so_dong, const char *cmnd, const char *ho, const char *ten, bool phai)
    {
        HanhKhach *hk = new HanhKhach(cmnd, ho, ten, phai);
        // this->ds_hanhkhach.add_from_file_data(hk);
        return chuyenbay->get_listve().add_ve(so_day, so_dong, cmnd);
    }

    void rank_slthcb(int *mb, int &n)
    {
        n = this->ds_maybay.get_so_luong();
        for (int i = 0; i < n; i++)
        {
            mb[i] = i;
        }
        int vitrimin;
        int min;
        for (int i = 0; i < n - 1; i++)
        {
            vitrimin = i;
            for (int j = i + 1; j < n; j++)
                if (ds_maybay.get_at(mb[j]) < ds_maybay.get_at(mb[vitrimin]))
                    vitrimin = j;
            if (i != vitrimin)
            {
                min = mb[vitrimin];
                mb[vitrimin] = mb[i];
                mb[i] = min;
            }
        }
    }

    
};

#endif
