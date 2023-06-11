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
        cout<<"Start saving.\n";
        ds_maybay.write_bin(DATA_MAY_BAY);
        ds_chuyenbay.write_bin(DATA_CHUYEN_BAY);
        ds_hanhkhach.write_bin(DATA_HANH_KHACH);
        cout << "Completed Saved\n";
    }
    Status edit_may_bay(MayBay *maybay, int new_day, int new_dong, const char *loai)
    {
        int pre_day = maybay->getSoDay();
        int pre_dong = maybay->getSoDong();
        Status result = maybay->edit(loai, new_day, new_dong);
        if (result.get_status() == Status_Name::SUCCESS)
        {
            if (pre_day != new_day || pre_dong != new_dong)
            {
                ds_chuyenbay.update_cho_ngoi(maybay->getSoHieuMB(), new_day, new_dong);
            }
        }
        return result;
    }
    Status del_mb_by_index(int index)
    {
        if (index == -1)
            return Status("Không Tìm Thấy Máy Bay.");
        if (this->ds_chuyenbay.find_by_sh_mb(ds_maybay.get_at(index)->getSoHieuMB()))
            return Status("Xóa Thất Bại, Máy Bay Đã Lập Chuyến Bay.");
        this->ds_maybay.del(index);
        return Status("Xóa Thành Công.", Status_Name::SUCCESS);
    }

    Status edit_chuyen_bay(ChuyenBay *cb, int minute, int hour, int day, int month, int year, const char *san_bay_den, const char *so_hieu_mb)
    {
        if (cb->get_trang_thai_cb() == 2 || cb->get_trang_thai_cb() == 3)
            return Status("Không thể sửa thông tin của chuyến bay đang bay hoặc hoàn tất");
        Time thoi_gian_bay(minute, hour, day, month, year);
        if (Time::timeDiffInSeconds(cb->get_thoi_gian_bay(), thoi_gian_bay) == 0 && strcmp(san_bay_den, cb->get_san_bay_den()) == 0 && strcmp(so_hieu_mb, cb->get_so_hieu_mb()) == 0)
        {
            return Status("Không Có Sự Thay Đổi.");
        }
        if (!thoi_gian_bay.isValidDate())
            return Status("Thời Gian Không Hợp Lệ !");
        Time current_time;
        current_time.get_current_time();
        double difference = Time::timeDiffInSeconds(current_time, thoi_gian_bay);
        if (difference <= 60 * 60 * 2)
            return Status("Thời gian lập chuyến bay phải lớn hơn thòi gian hiện tại 2 giờ");
        if (difference > 60 * 60 * 24 * 365)
            return Status("Thời gian lập chuyến bay chỉ được phép trong vòng 365 ngày");

        if (strcmp(so_hieu_mb, cb->get_so_hieu_mb()) != 0)
        {
            MayBay *mb = this->ds_maybay.find_mamb_ct(so_hieu_mb);
            if (mb == nullptr)
                return Status("Số hiệu máy bay không tồn tại");
        }
        if (strcmp(san_bay_den, cb->get_san_bay_den()) != 0)
        {
            if (cb->get_listve().get_ve_da_ban() > 0)
                return Status("Không Được Phép Thay Đổi Nơi Đến Khi Đã Có Khách Đặt Vé.");
        }
        cb->set_thoi_gian_bay(thoi_gian_bay);
        cb->set_so_hieu_mb(so_hieu_mb);
        cb->set_san_bay_den(san_bay_den);
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

        double khoang_cach_time = Time::timeDiffInSeconds(current_time, time);
        if (khoang_cach_time < 0)
        {
            return Status("Lỗi: Thời Gian Ở Quá Khứ");
        }
        if (khoang_cach_time < 3600)
        {
            return Status("Chỉ Được Lập Chuyến Bay Cách Thời Gian Hiện Tại 1 Giờ");
        }
        if (khoang_cach_time > 3600 * 24 * 365)
        {
            return Status("Chỉ Được Lập Chuyến Bay Trong Vòng 365 Ngày");
        }
        Status check_mb = ds_chuyenbay.find_by_sh_mb_ct_ver2(so_hieu_mb, time); // kiểm tra thời gian đăng kí chuyến bay có cách 3 giờ so với chuyến bay khác hay không
        if (check_mb.get_status() != Status_Name::SUCCESS)
        {
            return check_mb;
        }
        ds_chuyenbay.add(ma_so_cb, time, san_bay_den, temp);
        return Status("Thêm Chuyến Bay Thành Công", Status_Name::SUCCESS);
    }

    Status dat_ve(ChuyenBay *chuyenbay, int so_day, int so_dong, const char *cmnd, bool type = true)
    {
        return ds_chuyenbay.dat_ve(so_day,so_dong,chuyenbay,cmnd,type);
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
