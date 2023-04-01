#ifndef CHUYENBAY_H
#define CHUYENBAY_H

#include "error.h"
#include "maybay.h"

class ThoiGianBay {
   private:
    int minute;
    int hour;
    int day;
    int month;
    int year;

   public:
    std::string to_string() const {  // hh:mm-dd/mm/yyyy
        std::stringstream ss;
        std::tm timeinfo = {};
        timeinfo.tm_year = year - 1900;  // năm bắt đầu từ 1900
        timeinfo.tm_mon = month - 1;     // tháng bắt đầu từ 0
        timeinfo.tm_mday = day;
        timeinfo.tm_hour = hour;
        timeinfo.tm_min = minute;
        // In ra chuỗi theo định dạng hh:mm-dd/mm/yyyy
        ss << std::put_time(&timeinfo, "%H:%M-%d/%m/%Y");
        return ss.str();
    }
    std::string to_time_string() const {
        std::stringstream ss;
        std::tm timeinfo = {};
        timeinfo.tm_hour = hour;
        timeinfo.tm_min = minute;
        // In ra chuỗi theo định dạng hh:mm
        ss << std::put_time(&timeinfo, "%H gio %M phut");
        return ss.str();
    }
    ThoiGianBay() {
    }
    ThoiGianBay(int m, int h, int d, int month, int y) {
        this->set(m, h, d, month, y);
    }
    void set(int minute, int hour, int day, int month, int year) {
        this->minute = minute;
        this->hour = hour;
        this->day = day;
        this->month = month;
        this->year = year;
    }

    bool kiem_tra_ngay_bay(ThoiGianBay ngay_thang_nam) {
        if (this->year != ngay_thang_nam.year || this->month != ngay_thang_nam.month || this->day != ngay_thang_nam.day)
            return false;
        return true;
    }

    friend std::istringstream& operator>>(std::istringstream& is, ThoiGianBay& time);
};
std::istringstream& operator>>(std::istringstream& is, ThoiGianBay& time) {
    char delimiter;
    is >> time.hour >> delimiter >> time.minute >> delimiter >> time.day >> delimiter >> time.month >> delimiter >> time.year;
    return is;
}

class Ve {
   private:
    char so_ve[MAX_LENGTH_SO_VE + 1];
    char so_cmnd[MAX_LENGTH_SO_CMND + 1];
    int count = 0;

   public:
    // getter
    char* getSoVe() {
        return so_ve;
    }
    char* getSoCMND() {
        return so_cmnd;
    }
    int getSoDay() {
        if (strlen(so_ve) == 3) {
            return (int)(so_ve[0] - 'A' + 1);
        }
        return -1;
    }
    int getSoDong() {
        if (strlen(so_ve) == 3) {
            char so_dong[3];
            strcpy(so_dong, so_ve + 1);
            return std::stoi(so_dong);
        }
        return -1;
    }
    // setter
    void setSoVe(char* sv) {
        strncpy(so_ve, sv, MAX_LENGTH_SO_VE);
    }
    void setSoCMND(char* scmnd) {
        strncpy(so_cmnd, scmnd, MAX_LENGTH_SO_CMND);
    }

    Ve() {
    }
    Ve(const Ve& ve) {
        strncpy(so_ve, ve.so_ve, MAX_LENGTH_SO_VE);
        strncpy(so_cmnd, ve.so_cmnd, MAX_LENGTH_SO_CMND);
    }
    Ve(char* sv, char* scmnd) {
        strcpy(so_ve, sv);
        strcpy(so_cmnd, scmnd);
    }
    Ve(int day, int dong, char* scmnd) {
        char d = (char)('A' + day);
        fomatMaVe(day, dong);
        strcpy(so_cmnd, scmnd);
    }
    void fomatMaVe(int so_day, int so_dong) {
        this->so_ve[0] = (char)(so_day + 'A' - 1);
        if (so_dong < 10) {
            this->so_ve[1] = '0';
            this->so_ve[2] = '0' + so_dong;
        } else {
            this->so_ve[2] = '0' + so_dong % 10;
            so_dong /= 10;
            this->so_ve[1] = '0' + so_dong;
        }
        this->so_ve[3] = 0;
    }

    friend std::ostream& operator<<(std::ostream& os, const Ve& mb);
    friend std::istringstream& operator>>(std::istringstream& is, Ve& ve);
};
std::ostream& operator<<(std::ostream& os, const Ve& mb) {
    os << mb.so_ve << '-' << mb.so_cmnd << ';';
    return os;
}

std::istringstream& operator>>(std::istringstream& is, Ve& ve) {
    is.getline(ve.so_ve, MAX_LENGTH_SO_VE, '-');
    is.getline(ve.so_cmnd, MAX_LENGTH_SO_CMND, ';');
    return is;
}

class ChuyenBay {  // ma_so_cb|so_hieu_mb|hh:mm-dd/mm/yyyy|san_bay_den|trang_thai|ve1-cmnd;ve2-cmnd
   private:
    char ma_so_cb[MAX_LENGTH_MA_CB + 1];
    ThoiGianBay thoi_gian_bay;
    char san_bay_den[MAX_LENGTH_SAN_BAY_DEN + 1];
    int trang_thai_cb;
    char so_hieu_mb[MAX_LENGTH_SO_HIEU_MB + 1];
    Ve*** listve;  // cần fix
    ChuyenBay* next = NULL;

   public:
    // Getter
    char* get_ma_so_cb() { return this->ma_so_cb; }
    ThoiGianBay get_thoi_gian_bay() { return this->thoi_gian_bay; }
    char* get_san_bay_den() { return this->san_bay_den; }
    int get_trang_thai_cb() { return this->trang_thai_cb; }
    char* get_so_hieu_mb() { return this->so_hieu_mb; }
    Ve*** get_listve() { return this->listve; }
    ChuyenBay* get_next() { return this->next; }

    // Setter
    void set_ma_so_cb(char* ma_so_cb) { strcpy(this->ma_so_cb, ma_so_cb); }
    void set_thoi_gian_bay(ThoiGianBay thoi_gian_bay) { this->thoi_gian_bay = thoi_gian_bay; }
    void set_san_bay_den(char* san_bay_den) { strcpy(this->san_bay_den, san_bay_den); }
    void set_trang_thai_cb(int trang_thai_cb) { this->trang_thai_cb = trang_thai_cb; }
    void set_so_hieu_mb(char* so_hieu_mb) { strcpy(this->so_hieu_mb, so_hieu_mb); }
    void set_next(ChuyenBay* next) { this->next = next; }

    void set_macb(char* mcb) {
        strcpy(this->ma_so_cb, mcb);
    }
    // void set_time(char* time){
    //     thoi_gian_bay.set(time);
    // }
    // void add_ve(int day,int dong,char* cmnd){
    //     listve[day-1 ] = new Ve(day,dong,cmnd);
    // }
    // void add_ve(char* mave,char* cmnd){
    //     char* s = &mave[1];
    //     if(listve[mave[0]-'A' + std::stoi(s) - 1 ]  == nullptr)
    //     listve[mave[0]-'A' + std::stoi(s) - 1 ] = new Ve(mave,cmnd);
    // }
    void add_ve(Ve& ve) {  // hàm này để thêm vé từ file data nên sẽ không cần check đã tồn tại
        listve[ve.getSoDay() - 1][ve.getSoDong() - 1] = new Ve(ve);
    }

    void init_ve() {
        int so_day = 25, so_dong = 40;
        listve = new Ve**[so_day];
        for (int i = 0; i < so_day; ++i) {
            listve[i] = new Ve*[so_dong];
        }
        for (int i = 0; i < so_day; i++) {
            for (int j = 0; j < so_dong; j++) {
                listve[i][j] = nullptr;
            }
        }
    }

    int dem_so_ve_con_trong() {
        int so_day = 25, so_dong = 40, count = 0;
        for (int i = 0; i < so_day; i++) {
            for (int j = 0; j < so_dong; j++) {
                if (this->listve[i][j] == NULL) {
                    count++;
                }
            }
        }
        return count;
    }

    // std::string dinh_dang_chuyen_bay_theo_string(){
    //     std::stringstream ss;
    //     ss << this->get_ma_so_cb();
    //     ss << "|";
    //     ss << this->get_so_hieu_mb();
    //     ss << "|";
    //     ss << this->get_thoi_gian_bay().to_string();
    //     ss << "|";
    //     ss << this->get_san_bay_den();
    //     ss << "|";
    //     ss << this->get_trang_thai_cb();
    //     return ss.str();
    // }

    ChuyenBay() {
        init_ve();
    }
    ChuyenBay(ChuyenBay* cb) {
        init_ve();
        this->set(cb->ma_so_cb, cb->thoi_gian_bay, cb->san_bay_den, cb->so_hieu_mb, cb->trang_thai_cb);
    }
    ChuyenBay(char* ma_so_cb, ThoiGianBay thoi_gian_bay, char* san_bay_den, char* so_hieu_mb, int trang_thai_cb) {
        init_ve();
        this->set(ma_so_cb, thoi_gian_bay, san_bay_den, so_hieu_mb, trang_thai_cb);
    }
    ~ChuyenBay() {
        // cout<<"\ngiai phong bo nho ve\n";
        int so_day = 25, so_dong = 40;
        for (int i = 0; i < so_day; ++i) {
            for (int j = 0; j < so_dong; ++j) {
                delete[] listve[i][j];
            }
            delete[] listve[i];
        }
        delete[] listve;
    }
    void set(char* ma_so_cb, ThoiGianBay thoi_gian_bay, char* san_bay_den, char* so_hieu_mb, int trang_thai_cb) {
        strcpy(this->ma_so_cb, ma_so_cb);
        strcpy(this->san_bay_den, san_bay_den);
        strcpy(this->so_hieu_mb, so_hieu_mb);

        this->trang_thai_cb = trang_thai_cb;
        this->thoi_gian_bay = thoi_gian_bay;
    }
    int so_sanh_macb_voi_macb_cua_doi_tuong(ChuyenBay* cb) {  // return -1: cb này < cb2, 0: cb này == cb2, 1: cb này > cb2
        return strcmp(this->ma_so_cb, cb->get_ma_so_cb());
    }
    int compare_macb(char* macb) {  // return -1: cb này < cb2, 0: cb này == cb2, 1: cb này > cb2
        return strcmp(this->ma_so_cb, macb);
    }

    bool kiem_tra_san_bay_den(char* san_bay_den) {
        return strcmp(this->san_bay_den, san_bay_den) == 0;
    }

    bool kiem_tra_con_ve() {
        return this->trang_thai_cb == 1;
    }

    friend std::istringstream& operator>>(std::istringstream& is, ChuyenBay& mb);
    friend std::ostream& operator<<(std::ostream& os, const ChuyenBay& mb);
};
// ma_so_cb|so_hieu_mb|hh:mm-dd/mm/yyyy|san_bay_den|trang_thai|A01|12321|A02|2344
std::istringstream& operator>>(std::istringstream& is, ChuyenBay& mb) {
    is.getline(mb.ma_so_cb, MAX_LENGTH_MA_CB, '|');
    is.getline(mb.so_hieu_mb, MAX_LENGTH_SO_HIEU_MB, '|');
    is >> mb.thoi_gian_bay;
    is.ignore(1);
    is.getline(mb.san_bay_den, MAX_LENGTH_SAN_BAY_DEN, '|');
    is >> mb.trang_thai_cb;
    is.ignore(1);
    // nhập vé
    Ve ve;
    while (is >> ve) {
        mb.add_ve(ve);
    }
    // std::cout<<mb<<'\n';

    return is;
}
std::ostream& operator<<(std::ostream& os, const ChuyenBay& cb) {
    os << cb.ma_so_cb << "|" << cb.so_hieu_mb << "|" << cb.thoi_gian_bay.to_string() << "|" << cb.san_bay_den << '|' << cb.trang_thai_cb << '|';  // in cả vé
    int so_day = 25, so_dong = 40;
    for (int i = 0; i < so_day; i++) {
        for (int j = 0; j < so_dong; j++) {
            if (cb.listve[i][j] != nullptr) {
                os << *(cb.listve[i][j]);
            }
        }
    }
    return os;
}
class ListChuyenBay {
   private:
    ChuyenBay* head = NULL;
    ChuyenBay* tail = NULL;

   public:
    ~ListChuyenBay() {
        ChuyenBay* current = head;
        ChuyenBay* next = nullptr;
        while (current != nullptr) {
            next = current->get_next();
            delete current;
            current = next;
        }
        head = nullptr;
    }
    void print() {
        ChuyenBay* current = head;
        while (current != nullptr) {
            cout << *current << "\n";
            current = current->get_next();
        }
    }
    void add(char* ma_so_cb, ThoiGianBay thoi_gian_bay, char* san_bay_den, char* so_hieu_mb, int trang_thai_cb) {
        ChuyenBay* new_chuyenbay = new ChuyenBay(ma_so_cb, thoi_gian_bay, san_bay_den, so_hieu_mb, trang_thai_cb);
        insert_order(new_chuyenbay);
    }
    void insert_last(ChuyenBay* new_chuyenbay) {
        if (head == nullptr) {
            head = new_chuyenbay;
            tail = new_chuyenbay;
        } else {
            tail->set_next(new_chuyenbay);
            tail = tail->get_next();
        }
    }
    void push_data(ChuyenBay* chuyenbay) {
        this->insert_last(chuyenbay);
    }
    void insert_order(ChuyenBay* new_chuyenbay) {
        // nếu danh sách rỗng hoặc chuyên bay mới có mã nhỏ hơn head
        if (head == NULL || new_chuyenbay->so_sanh_macb_voi_macb_cua_doi_tuong(head) == -1) {
            new_chuyenbay->set_next(head);
            head = new_chuyenbay;
        } else {
            ChuyenBay* current = head;
            // Tìm vị trí để chèn vào
            while (current->get_next() != NULL && new_chuyenbay->get_next()->so_sanh_macb_voi_macb_cua_doi_tuong(current) == -1) {
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

    bool xoa_chuyen_bay_theo_ma_so_cb(char* ma_so_cb) {
        ChuyenBay* chuyenbay = head;
        ChuyenBay* chuyenbay_truoc = NULL;
        while (chuyenbay != NULL) {
            if (chuyenbay->compare_macb(ma_so_cb) == 0) {
                if (chuyenbay == head) {  // chuyến bay cần xóa ở đầu danh sách
                    head = chuyenbay->get_next();
                } else {  // chuyến bay cần xóa ở vị trí khác
                    chuyenbay_truoc->set_next(chuyenbay->get_next());
                }
                if (chuyenbay == tail) {  // chuyến bay cần xóa ở cuối danh sách
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

    void gio_khoi_hanh_cua_cac_cb() {
        ChuyenBay* current = head;
        while (current != NULL) {
            cout << "\n>>> Gio khoi hanh cua chuyen bay " << current->get_ma_so_cb() << ": " << current->get_thoi_gian_bay().to_time_string();
            current = current->get_next();
        }
    }

    void dem_so_luong_ve_con_trong_cua_cac_cb() {
        for (ChuyenBay* current = this->head; current != NULL; current = current->get_next()) {
            cout << "\n>>> So ve con trong cua chuyen bay " << current->get_ma_so_cb() << ": " << current->dem_so_ve_con_trong();
        }
    }

    void sao_chep_danh_sach(ChuyenBay* head_list_for_copy) {
        for (ChuyenBay* current = head_list_for_copy; current != NULL; current = current->get_next()) {
            ChuyenBay* new_cb = new ChuyenBay(current);
            this->insert_last(new_cb);
        }
    }

    void loc_san_bay_den(char* san_bay_den) {
        if (this->head == NULL) return;
        ChuyenBay* current = this->head->get_next();
        ChuyenBay* previous = this->head;
        ChuyenBay* cb_can_xoa;
        while (current != NULL) {
            if (!current->kiem_tra_san_bay_den(san_bay_den)) {
                cb_can_xoa = current;
                previous->set_next(current->get_next());
                current = current->get_next();
                delete cb_can_xoa;
                continue;
            }
            previous = current;
            current = current->get_next();
        }
        if (!this->head->kiem_tra_san_bay_den(san_bay_den)) {
            cb_can_xoa = this->head;
            this->head = this->head->get_next();
            delete cb_can_xoa;
        }
    }

    void loc_ngay_bay(ThoiGianBay ngay_thang_nam) {
        if (this->head == NULL) return;
        ChuyenBay* current = this->head->get_next();
        ChuyenBay* previous = this->head;
        ChuyenBay* cb_can_xoa;
        while (current != NULL) {
            if (!current->get_thoi_gian_bay().kiem_tra_ngay_bay(ngay_thang_nam)) {
                cb_can_xoa = current;
                previous->set_next(current->get_next());
                current = current->get_next();
                delete cb_can_xoa;
                continue;
            }
            previous = current;
            current = current->get_next();
        }
        if (!this->head->get_thoi_gian_bay().kiem_tra_ngay_bay(ngay_thang_nam)) {
            cb_can_xoa = this->head;
            this->head = this->head->get_next();
            delete cb_can_xoa;
        }
    }

    void loc_trang_thai_con_ve() {
        if (this->head == NULL) return;
        ChuyenBay* current = this->head->get_next();
        ChuyenBay* previous = this->head;
        ChuyenBay* cb_can_xoa;
        while (current != NULL) {
            if (!current->kiem_tra_con_ve()) {
                cb_can_xoa = current;
                previous->set_next(current->get_next());
                current = current->get_next();
                delete cb_can_xoa;
                continue;
            }
            previous = current;
            current = current->get_next();
        }
        if (!this->head->kiem_tra_con_ve()) {
            cb_can_xoa = this->head;
            this->head = this->head->get_next();
            delete cb_can_xoa;
        }
    }

    // hoặc hàm 1
    void tim_cac_cb_con_ve_trong_ngay_1(char* san_bay_can_loc, ThoiGianBay thoi_gian_bay_can_loc) {
        ListChuyenBay copy_list;
        copy_list.sao_chep_danh_sach(this->head);

        copy_list.loc_san_bay_den(san_bay_can_loc);
        copy_list.loc_ngay_bay(thoi_gian_bay_can_loc);
        copy_list.loc_trang_thai_con_ve();

        copy_list.gio_khoi_hanh_cua_cac_cb();
        copy_list.dem_so_luong_ve_con_trong_cua_cac_cb();
    }

    // hoặc hàm 2
    void tim_cac_cb_con_ve_trong_ngay_2(char* san_bay_can_loc, ThoiGianBay thoi_gian_bay_can_loc) {
        if (this->head == NULL) return;

        ListChuyenBay copy_list;

        ChuyenBay* current = this->head->get_next();
        ChuyenBay* them_cb;
        while (current != NULL) {
            if (current->kiem_tra_san_bay_den(san_bay_can_loc) && current->get_thoi_gian_bay().kiem_tra_ngay_bay(thoi_gian_bay_can_loc) && current->kiem_tra_con_ve()) {
                ChuyenBay* them_cb = new ChuyenBay(current);
                copy_list.insert_last(them_cb);
            }
            current = current->get_next();
        }

        copy_list.print();
        copy_list.gio_khoi_hanh_cua_cac_cb();
        copy_list.dem_so_luong_ve_con_trong_cua_cac_cb();
    }

    void in_du_lieu(std::ofstream& os) const{
        for (ChuyenBay* current = this->head; current != NULL; current = current->get_next()) {
            os << *current << "\n";
        }
    }

    friend std::ofstream& operator<<(std::ofstream& os, const ListChuyenBay& list);
};
std::ofstream& operator<<(std::ofstream& os, const ListChuyenBay& list){
    list.in_du_lieu(os);
    return os;
}

#endif