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
        cout << "Completed Saved\n";
    }
    Status edit_may_bay(MayBay *maybay, int new_day, int new_dong, const char *loai)
    {
        bool da_lap_chuyen_bay = this->ds_chuyenbay.find_by_sh_mb(maybay->getSoHieuMB());
        Status result;
        if (!da_lap_chuyen_bay)
        {
            result = maybay->edit(loai, new_day, new_dong, false);
        }
        else
        { // sửa dòng hoặc sửa loại
            result = maybay->edit(loai, new_day, new_dong);
            if (result.get_status() == Status_Name::SUCCESS)
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

    Status edit_chuyen_bay(ChuyenBay *cb, int minute, int hour, int day, int month, int year, const char *san_bay_den)
    {
        return ds_chuyenbay.edit_chuyen_bay(cb, minute, hour, day, month, year, san_bay_den);
    }

    Status add_cb(const char *ma_so_cb, int minute, int hour, int day, int month, int year, const char *san_bay_den, const char *so_hieu_mb)
    {
        return ds_chuyenbay.add_cb(this->ds_maybay, ma_so_cb, minute, hour, day, month, year, san_bay_den, so_hieu_mb);
    }

    Status dat_ve(ChuyenBay *chuyenbay, int so_day, int so_dong, const char *cmnd, bool type = true)
    {
        return ds_chuyenbay.dat_ve(so_day, so_dong, chuyenbay, cmnd, type);
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
            {
                if (ds_maybay.get_at(mb[j])->get_so_lan_bay() > ds_maybay.get_at(mb[vitrimin])->get_so_lan_bay())
                    vitrimin = j;
            }
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
