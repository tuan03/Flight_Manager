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
            File_Handling::read_from_file<TreeHanhKhach,HanhKhach>("src\\data\\data_hanh_khach.txt",ds_hanhkhach);
            File_Handling::read_from_file<ListMayBay,MayBay>("src\\data\\data_may_bay.txt",ds_maybay);
            File_Handling::read_from_file<ListChuyenBay,ChuyenBay>("src\\data\\data_chuyen_bay.txt",ds_chuyenbay);
        }

        ~Flight_Manager(){
            File_Handling::write<TreeHanhKhach>(FILE_PATH_DATA_HANH_KHACH,FILE_PATH_DATA_HANH_KHACH_BACKUP,ds_hanhkhach);
            File_Handling::write<ListMayBay>(FILE_PATH_DATA_MAY_BAY,FILE_PATH_DATA_MAY_BAY_BACKUP,ds_maybay);
            File_Handling::write<ListChuyenBay>(FILE_PATH_DATA_CHUYEN_BAY,FILE_PATH_DATA_CHUYEN_BAY_BACKUP,ds_chuyenbay);
        }


    Status del_mb(const char* soHieuMB){
    		int index = this->ds_maybay.find_mamb(soHieuMB);
    		if (index == -1) {
                return Status("Không Tìm Thấy Máy Bay.");
            }
				if(this->ds_chuyenbay.find_by_sh_mb_v2(soHieuMB) == true) return Status("Xóa Thất Bại, Máy Bay Đã Lập Chuyến Bay.");
			    this->ds_maybay.del(index);
                return Status("Xóa Thành Công.", Status_Name::SUCCESS);
		}

     Status edit_chuyen_bay(ChuyenBay* cb, int minute, int hour, int day, int month, int year, const char* san_bay_den, const char* so_hieu_mb) {
        //check error
         Time thoi_gian_bay(minute,hour,day,month,year);
        if(!thoi_gian_bay.isValidDate()) return Status("Ngày Giờ Không Hợp Lệ !");
        if (cb->get_trang_thai_cb() == 2 || cb->get_trang_thai_cb() == 3) return Status("Không thể sửa thông tin của chuyến bay đang bay hoặc hoàn tất");
        MayBay* mb = this->ds_maybay.find_mamb_ct(so_hieu_mb);
        if (mb == nullptr) return Status("Số hiệu máy bay không tồn tại");
        Time current_time;
        current_time.get_current_time();
        double difference = Time::timeDiffInSeconds(current_time, thoi_gian_bay);
        if (difference <= 60*60*2) return Status("Thời gian lập chuyến bay phải lớn hơn thòi gian hiện tại 2 giờ");
        if (difference > 60*60 * 24 * 365) return Status("Thời gian lập chuyến bay chỉ được phép trong vòng 365 ngày");
        //edit
        cb->set_thoi_gian_bay(thoi_gian_bay);
        cb->set_san_bay_den(san_bay_den);
        cb->set_so_hieu_mb(so_hieu_mb);
        return Status("Sửa thông tin chuyến bay thành công", Status_Name::SUCCESS);
    }

    Status add_cb(const char* ma_so_cb, int minute, int hour, int day, int month, int year, const char* san_bay_den,const char* so_hieu_mb) {

            if(ds_chuyenbay.find_by_ma_cb(ma_so_cb)){
                return Status("Mã Chuyến Bay Đã Tồn Tại");
            }
            if(ds_maybay.find_mamb(so_hieu_mb) == -1){
                return Status("Số Hiệu Máy Bay Không Tồn tại");
            }
            Time time(minute,hour,day,month,year);
            if(!time.isValidDate()){
                return Status("Thời Gian Không Hợp Lệ");
            }

            Time current_time;
            current_time.get_current_time();

            if(Time::timeDiffInSeconds(current_time,time) < 3600 ){
                return Status("Chỉ Được Lập Chuyến Bay Cách Thời Gian Hiện Tại 1 Giờ");
            }
            if(Time::timeDiffInSeconds(current_time,time) > 3600 * 24 * 365 ){ 
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
            ChuyenBay* new_chuyenbay = new ChuyenBay(ma_so_cb, time, san_bay_den, so_hieu_mb, 1);
            ds_chuyenbay.insert_order(new_chuyenbay);
            return Status("Thêm Chuyến Bay Thành Công",Status_Name::SUCCESS);
        }


        void filter_list_cb(int page, const char * ma_cb, int day, int month, int year, const char* noi_den){ //1 page hiển thị 10 line
            ChuyenBay* current = ds_chuyenbay.get_head();
            while (current != nullptr) {
                if(Func_Global::check_prefix(current->get_ma_so_cb(),ma_cb) && Func_Global::check_prefix(current->get_san_bay_den(),noi_den)){
                    cout << *current << "\n";
                }
                current = current->get_next();
            }
        }

        void rank_slthcb(int mb[], int &n){
            // sau này khắc phục thêm, bây giờ cứ từ từ
            n = this->ds_maybay.get_so_luong();
            int vitrimin;
            int min;
            for (int i = 0; i < n-1; i++){
                vitrimin = i;
                for (int j = i+1; j < n; j++)
                    if (mb[j] < mb[vitrimin]) vitrimin=j;
                min = mb[vitrimin];
                mb[vitrimin] = mb[i];  
                mb[i] = min;
            }
        }


        void in_ds_kh( const char* ma_so_cb){
   ChuyenBay* p= ds_chuyenbay.find_by_ma_cb_ct(ma_so_cb);
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
