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
        void in_ds_kh( const char* ma_so_cb){
   ChuyenBay* p= ds_chuyenbay.timChuyenBayTheoMaSoMB(ma_so_cb);
  cout<<"1";
   if(p!=nullptr){
    MayBay* mb=ds_maybay.find_mamb_ct(p->get_so_hieu_mb());
    for(int i=0; i<mb->getSoDay();i++){
         cout<<"2";
        for(int j=0;j<mb->getSoDong();j++){
             cout<<"3";
            if(p->get_listve()[i][j] != nullptr){
            HanhKhach* hk= ds_hanhkhach.search(p->get_listve()[i][j]->getSoCMND());
             cout<<"4";
            cout<< hk;

            }
        }
    }
     
}
}
};

#endif
