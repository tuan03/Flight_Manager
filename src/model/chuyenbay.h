#ifndef CHUYENBAY_H
#define CHUYENBAY_H

#include <chrono>

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

    bool kiem_tra_thoi_gian_lap_cb_gan_nhat_chua_qua_12h() {
        // dinh dang: giay, phut, gio, ngay, thang, nam
        std::tm input_time = {0, this->minute, this->hour, this->day, this->month - 1, this->year - 1900};
        // Chuyển đổi thời gian đầu vào thành std::time_t
        std::time_t input_c = std::mktime(&input_time);
        // Lấy thời gian hiện tại
        std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
        // Chuyển đổi thành cấu trúc thời gian của C
        std::time_t now_c = std::chrono::system_clock::to_time_t(now);
        // Kiểm tra chênh lệch giữa thời gian hiện tại và thời gian đầu vào
        double diff_hours = std::difftime(input_c, now_c) / 3600.0;

        if (diff_hours > 12.0) return false;
        return true;
    }

    bool kiem_tra_gio_hop_le() {
        // định dạng: giay, phut, gio, ngay, thang, nam
        std::tm input_time = {0, this->minute, this->hour, this->day, this->month - 1, this->year - 1900};
        // Chuyển đổi thời gian đầu vào thành std::time_t
        std::time_t input_c = std::mktime(&input_time);
        // Lấy thời gian hiện tại
        std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
        // Chuyển đổi thành cấu trúc thời gian của C
        std::time_t now_c = std::chrono::system_clock::to_time_t(now);
        // Kiểm tra chênh lệch giữa thời gian hiện tại và thời gian đầu vào
        double diff_hours = std::difftime(input_c, now_c) / 3600.0;

        if (diff_hours > 1.0) return true;
        return false;
    }

    bool kiem_tra_nam_hop_le() {
        // dinh dang: giay, phut, gio, ngay, thang, nam
        std::tm input_time = {0, this->minute, this->hour, this->day, this->month - 1, this->year - 1900};
        // Chuyển đổi thời gian đầu vào thành std::time_t
        std::time_t input_c = std::mktime(&input_time);
        // Lấy thời gian hiện tại
        std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
        // Chuyển đổi thành cấu trúc thời gian của C
        std::time_t now_c = std::chrono::system_clock::to_time_t(now);
        std::tm now_tm = *std::localtime(&now_c);
        // Kiểm tra chênh lệch giữa thời gian hiện tại và thời gian đầu vào
        double diff_hours = std::difftime(now_c, input_c) / 3600.0;

        if (diff_hours > 1.0 * 8760.0) return false;

        return true;
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
        strncpy(so_ve, sv, MAX_LENGTH_SO_VE + 1);
    }
    void setSoCMND(char* scmnd) {
        strncpy(so_cmnd, scmnd, MAX_LENGTH_SO_CMND + 1);
    }

    Ve() {
    }
    Ve(const Ve& ve) {
        strncpy(so_ve, ve.so_ve, MAX_LENGTH_SO_VE + 1);
        strncpy(so_cmnd, ve.so_cmnd, MAX_LENGTH_SO_CMND + 1);
    }
    Ve(char* sv, char* scmnd) {
        strcpy(so_ve, sv);
        strcpy(so_cmnd, scmnd);
    }
    Ve(int day, int dong, char* scmnd) {
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
    is.getline(ve.so_ve, MAX_LENGTH_SO_VE + 1, '-');
    is.getline(ve.so_cmnd, MAX_LENGTH_SO_CMND + 1, ';');
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
        char* found = std::strstr(this->san_bay_den, san_bay_den);  // tìm kiếm chuỗi con
        if (found != NULL) return true;
        return false;
    }

    bool kiem_tra_con_ve() {
        return this->trang_thai_cb == 1;
    }

    friend std::istringstream& operator>>(std::istringstream& is, ChuyenBay& mb);
    friend std::ostream& operator<<(std::ostream& os, const ChuyenBay& mb);
};
// ma_so_cb|so_hieu_mb|hh:mm-dd/mm/yyyy|san_bay_den|trang_thai|A01|12321|A02|2344
std::istringstream& operator>>(std::istringstream& is, ChuyenBay& mb) {
    is.getline(mb.ma_so_cb, MAX_LENGTH_MA_CB + 1, '|');
    is.getline(mb.so_hieu_mb, MAX_LENGTH_SO_HIEU_MB + 1, '|');
    is >> mb.thoi_gian_bay;
    is.ignore(1);
    is.getline(mb.san_bay_den, MAX_LENGTH_SAN_BAY_DEN + 1, '|');
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
    int get_so_luong_cb() {
        int count = 0;
        ChuyenBay* current = head;
        while (current != nullptr) {
            count++;
            current = current->get_next();
        }
        return count;
    }
    void print() {
        ChuyenBay* current = head;
        while (current != nullptr) {
            cout << *current << "\n";
            current = current->get_next();
        }
    }

    Status them_cb_moi_vao_danh_sach_co_bat_loi(ChuyenBay* cb_can_them) {
        if (listMayBay.timMayBay(cb_can_them->get_so_hieu_mb()) == -1)
            return Status("Không tồn tại trong danh sách máy bay");
        if (!cb_can_them->get_thoi_gian_bay().kiem_tra_gio_hop_le())
            return Status("Thời gian bay không hợp lệ (giờ khởi hành phải lớn hơn giờ hiện tại 1 giờ)");
        if (!cb_can_them->get_thoi_gian_bay().kiem_tra_nam_hop_le())
            return Status("Thời gian bay không hợp lệ (năm khởi hành phải lớn hơn năm hiện tại không quá 1 giờ)");
        ChuyenBay* kiem_tra_cb = this->kiem_tra_va_tra_ve_chuyen_bay_ton_tai_trong_danh_sach(cb_can_them);
        if (kiem_tra_cb != NULL && kiem_tra_cb->get_trang_thai_cb() != 3)
            return Status("Chuyến bay đang được thực thi");
        if (kiem_tra_cb != NULL && kiem_tra_cb->get_trang_thai_cb() == 3 && kiem_tra_cb->get_thoi_gian_bay().kiem_tra_thoi_gian_lap_cb_gan_nhat_chua_qua_12h())
            return Status("Thời gian lập chuyến bay mới phải hơn 12h kể từ chuyến bay gần nhất");
        this->insert_order(cb_can_them);
        return Status();
    }

    void add(char* ma_so_cb, ThoiGianBay thoi_gian_bay, char* san_bay_den, char* so_hieu_mb) {
        ChuyenBay* new_chuyenbay = new ChuyenBay(ma_so_cb, thoi_gian_bay, san_bay_den, so_hieu_mb, 1);
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

    ChuyenBay* timChuyenBayTheoMaSoMB(const char* ma_so_mb) {
        ChuyenBay* p = head;
        while (p != NULL) {
            if (strcmp(p->get_so_hieu_mb(), ma_so_mb) == 0) {  // sử dụng hàm getter để lấy mã máy bay
                return p;                                      // trả về chuyến bay nếu tìm thấy
            }
            p = p->get_next();
        }
        return nullptr;  // trả về NULL nếu không tìm thấy chuyến bay
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
            cout << ">>> Gio khoi hanh cua chuyen bay " << current->get_ma_so_cb() << ": " << current->get_thoi_gian_bay().to_time_string() << "\n";
            current = current->get_next();
        }
    }

    void dem_so_luong_ve_con_trong_cua_cac_cb() {
        for (ChuyenBay* current = this->head; current != NULL; current = current->get_next()) {
            cout << ">>> So ve con trong cua chuyen bay " << current->get_ma_so_cb() << ": " << current->dem_so_ve_con_trong() << "\n";
        }
    }

    void xoa_cb_theo_san_bay_den(char* san_bay_den) {
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

    void xoa_cb_theo_ngay_thang_nam(ThoiGianBay ngay_thang_nam) {
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

    void xoa_cb_theo_trang_thai_khong_con_ve() {
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

    ListChuyenBay tim_cac_cb_con_ve_trong_ngay(char* san_bay_can_loc, ThoiGianBay thoi_gian_bay_can_loc) {
        ListChuyenBay danh_sach_de_loc;
        if (this->head == NULL) return danh_sach_de_loc;
        ChuyenBay* current = this->head;
        ChuyenBay* them_cb;
        while (current != NULL) {
            if (current->kiem_tra_san_bay_den(san_bay_can_loc) && current->get_thoi_gian_bay().kiem_tra_ngay_bay(thoi_gian_bay_can_loc) && current->kiem_tra_con_ve()) {
                them_cb = new ChuyenBay(current);
                danh_sach_de_loc.insert_last(them_cb);
            }
            current = current->get_next();
        }
        return danh_sach_de_loc;
    }

    void in_du_lieu(std::ofstream& os) const {
        for (ChuyenBay* current = this->head; current != NULL; current = current->get_next()) {
            os << *current << "\n";
        }
    }

    bool kiem_tra_chuyen_bay_ton_tai_trong_danh_sach(char* ma_so_cb) {
        ChuyenBay* current = this->head;
        while (current != NULL) {
            if (current->compare_macb(ma_so_cb) == 0)
                return true;
            current = current->get_next();
        }
        return false;
    }

    ChuyenBay* kiem_tra_va_tra_ve_chuyen_bay_ton_tai_trong_danh_sach(ChuyenBay* cb) {
        ChuyenBay* current = this->head;
        while (current != NULL) {
            if (current->so_sanh_macb_voi_macb_cua_doi_tuong(cb) == 0)
                return current;
            current = current->get_next();
        }
        return NULL;
    }

    friend std::ofstream& operator<<(std::ofstream& os, const ListChuyenBay& list);
    ListChuyenBay& operator=(const ListChuyenBay& list);
};
std::ofstream& operator<<(std::ofstream& os, const ListChuyenBay& list) {
    list.in_du_lieu(os);
    return os;
}

ListChuyenBay& ListChuyenBay::operator=(const ListChuyenBay& list) {
    if (this != &list) {
        head = list.head;
        tail = list.tail;
    }
    return *this;
}

#endif