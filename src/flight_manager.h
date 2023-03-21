#ifndef FLIGHT_MANAGER_H
#define FLIGHT_MANAGER_H

#include"maybay.h"
#include"hanhkhach.h"
#include"chuyenbay.h"
#include"file_handling.h"

class Flight_Manager{
    private:
        ListMayBay ds_maybay;
        ListChuyenBay ds_chuyenbay;
        TreeHanhKhach ds_hanhkhach;
    public:
        ListMayBay& getListMB(){
            return ds_maybay;
        }
        ListChuyenBay& getListCB(){
            return ds_chuyenbay;
        }
        TreeHanhKhach& getListHK(){
            return ds_hanhkhach;
        }
        Flight_Manager(){
            read("src\\data\\data_hanh_khach.txt",ds_hanhkhach);
            read("src\\data\\data_chuyen_bay.txt",ds_chuyenbay);
            read("src\\data\\data_may_bay.txt",ds_maybay);
        }

        ~Flight_Manager(){
            
        }
};


#endif
