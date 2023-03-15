#ifndef CHUYENBAY_H
#define CHUYENBAY_H



#include "error.h"
class ThoiGianBay {
    private:
        int minute;
        int hour;
        int day;
        int month;
        int year;
    public:
        ThoiGianBay(){

        }
        ThoiGianBay(int m, int h, int d, int month, int y){
            this->set(m,h,d,month,y);
        }
        void set(int m, int h, int d, int month, int y){
            this->minute = m;
            this->hour = h;
            this->day = d;
            this->month = month;
            this->year = y;
        }

};


class Ve {
   public:
    char so_ve[MAX_LENGTH_SO_VE + 1];
    char so_cmnd[MAX_LENGTH_SO_CMND + 1];
};


class ChuyenBay {
   private:
    char ma_so_cb[MAX_LENGTH_MA_CB + 1];
    ThoiGianBay thoi_gian_bay;
    char san_bay_den[MAX_LENGTH_SAN_BAY_DEN + 1];
    int trang_thai_cb;
    char so_hieu_mb[MAX_LENGTH_SO_HIEU_MB + 1];
    Ve *listve; // cần fix
    ChuyenBay *next = NULL;
    public:
    ChuyenBay(){

    }
    ChuyenBay(char* ma_so_cb, ThoiGianBay thoi_gian_bay, char* san_bay_den, char* so_hieu_mb, int trang_thai_cb, Ve* danh_sach_ve) {
        this->set(ma_so_cb,thoi_gian_bay,san_bay_den,so_hieu_mb,trang_thai_cb,danh_sach_ve);
    }
    void copy_from(ChuyenBay& chuyenbay){
        this->set(chuyenbay.ma_so_cb,chuyenbay.thoi_gian_bay,chuyenbay.san_bay_den,chuyenbay.so_hieu_mb,chuyenbay.trang_thai_cb,chuyenbay.listve);
    }
    void set(char* ma_so_cb, ThoiGianBay thoi_gian_bay, char* san_bay_den, char* so_hieu_mb, int trang_thai_cb, Ve* danh_sach_ve) {
        strcpy(this->ma_so_cb, ma_so_cb);
        strcpy(this->san_bay_den, san_bay_den);
        strcpy(this->so_hieu_mb, so_hieu_mb);
        
        this->trang_thai_cb = trang_thai_cb;
        this->thoi_gian_bay = thoi_gian_bay;
        this->listve = danh_sach_ve; // cần fix
    }
    int compare_macb_with(ChuyenBay* cb){// return -1: cb này < cb2, 0: cb này == cb2, 1: cb này > cb2
        return strcmp(this->ma_so_cb,cb->get_macb());
    }
    int compare_macb(char* macb){// return -1: cb này < cb2, 0: cb này == cb2, 1: cb này > cb2
        return strcmp(this->ma_so_cb,macb);
    }
    char* get_macb(){
        return ma_so_cb;
    }
    ChuyenBay* get_next(){
        return this->next;
    }
    void set_next(ChuyenBay* next){
        this->next = next;
    }
};

class ListChuyenBay {
    private:
    ChuyenBay *head = NULL;
    ChuyenBay *tail = NULL;
    public:
    ~ListChuyenBay(){
        ChuyenBay* current = head;
        ChuyenBay* next = nullptr;
        while (current != nullptr)
        {   
            next = current->get_next();
            delete current;
            current = next;
        }
        
    }
    void add(char* ma_so_cb, ThoiGianBay thoi_gian_bay, char* san_bay_den, char* so_hieu_mb, int trang_thai_cb, Ve* danh_sach_ve){
        ChuyenBay* new_chuyenbay = new ChuyenBay(ma_so_cb,thoi_gian_bay,san_bay_den,so_hieu_mb,trang_thai_cb,danh_sach_ve);
        insert_order(new_chuyenbay);
    }
    
    void insert_order(ChuyenBay *new_chuyenbay) {
        //nếu danh sách rỗng hoặc chuyên bay mới có mã nhỏ hơn head
    if (head == NULL || new_chuyenbay->compare_macb_with(head) == -1 ) {
        new_chuyenbay->set_next(head);
        head = new_chuyenbay;
    }
    else {
        ChuyenBay *current = head;
        // Tìm vị trí để chèn vào
        while (current->get_next() != NULL && new_chuyenbay->get_next()->compare_macb_with(current) == -1) {
            current = current->get_next();
        }
        
        new_chuyenbay->set_next(current->get_next());
        current->set_next(new_chuyenbay);
    }
    // Nếu danh sách rỗng hoặc chuyenbay được thêm sau tail thì cập nhật tail
    if (tail == NULL || tail->get_next() == new_chuyenbay) {
        tail = new_chuyenbay;
    }
    }

    bool xoa_chuyen_bay(char* ma_so_cb){
        ChuyenBay* chuyenbay = head;
        ChuyenBay* chuyenbay_truoc = NULL;
        while(chuyenbay != NULL){
            if(chuyenbay->compare_macb(ma_so_cb) == 0){
                if(chuyenbay == head){ // chuyến bay cần xóa ở đầu danh sách
                    head = chuyenbay->get_next();
                } else { // chuyến bay cần xóa ở vị trí khác
                    chuyenbay_truoc->set_next(chuyenbay->get_next());
                }
                if(chuyenbay == tail){ // chuyến bay cần xóa ở cuối danh sách
                    tail = chuyenbay_truoc;
                }
                delete chuyenbay;
                return true;
            }
            chuyenbay_truoc = chuyenbay;
            chuyenbay = chuyenbay->get_next();
        }
        return false;
    }


};



#endif