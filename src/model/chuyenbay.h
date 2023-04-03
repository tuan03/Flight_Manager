#ifndef CHUYENBAY_H
#define CHUYENBAY_H

#include <chrono>

#include "error.h"
#include "maybay.h"

class Time {
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
    Time() {
    }
    Time(int m, int h, int d, int month, int y) {
        this->set(m, h, d, month, y);
    }

    void set(int minute, int hour, int day, int month, int year) {
        this->minute = minute;
        this->hour = hour;
        this->day = day;
        this->month = month;
        this->year = year;
    }
    void get_current_time(){
        auto now = chrono::system_clock::now();
        time_t now_c = chrono::system_clock::to_time_t(now);
        struct tm* parts = localtime(&now_c);
        this->hour = parts->tm_hour;
        this->minute = parts->tm_min;
        this->year = parts->tm_year + 1900;
        this->month = parts->tm_mon + 1;
        this->day = parts->tm_mday;
    }
    // Hàm tính khoảng cách thời gian giữa 2 mốc thời gian (trong đơn vị giây)
    static double timeDiffInSeconds(Time t1, Time t2) { // trả về time : t2 - t1 
        struct tm time1, time2;
        time1.tm_sec = 0;
        time1.tm_hour = t1.hour;
        time1.tm_min = t1.minute ;
        time1.tm_year = t1.year - 1900;
        time1.tm_mon = t1.month - 1;
        time1.tm_mday = t1.day;
        time2.tm_sec = 0;
        time2.tm_hour = t2.hour;
        time2.tm_min = t2.minute ;
        time2.tm_year = t2.year - 1900;
        time2.tm_mon = t2.month - 1;
        time2.tm_mday = t2.day;

        time_t t1_time = mktime(&time1);
        time_t t2_time = mktime(&time2);

        double diff = difftime(t2_time, t1_time);
        return diff;
    }
    bool isValidDate() {
        if(minute < 0 || minute >60 || hour < 0 || hour > 24){
            return false;
        }
        if (year < 1 || year > 9999 || month < 1 || month > 12) {
            return false;
        }
        int daysInMonth;
        if (month == 2) {
            if (Func_Global::is_nam_nhuan(year)) {
                daysInMonth = 29;
            } else {
                daysInMonth = 28;
            }
        } else if (month == 4 || month == 6 || month == 9 || month == 11) {
            daysInMonth = 30;
        } else {
            daysInMonth = 31;
        }
        if (day < 1 || day > daysInMonth) {
            return false;
        }
        return true;
    }
    friend std::istringstream& operator>>(std::istringstream& is, Time& time);
};
std::istringstream& operator>>(std::istringstream& is, Time& time) {
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
    Time thoi_gian_bay;
    char san_bay_den[MAX_LENGTH_SAN_BAY_DEN + 1];
    int trang_thai_cb; //0: hủy chuyến, 1: còn vé, 2: hết vé,3: hoàn tất 
    char so_hieu_mb[MAX_LENGTH_SO_HIEU_MB + 1];
    Ve*** listve;  // cần fix
    ChuyenBay* next = NULL;

    //chỉ số tạm
    int so_day = 0;
    int so_dong = 0;


    void set(char* ma_so_cb, Time thoi_gian_bay, char* san_bay_den, char* so_hieu_mb, int trang_thai_cb) {
        strcpy(this->ma_so_cb, ma_so_cb);
        strcpy(this->san_bay_den, san_bay_den);
        strcpy(this->so_hieu_mb, so_hieu_mb);

        this->trang_thai_cb = trang_thai_cb;
        this->thoi_gian_bay = thoi_gian_bay;
    }
   public:
    // Getter
    char* get_ma_so_cb() { return this->ma_so_cb; }
    Time get_thoi_gian_bay() { return this->thoi_gian_bay; }
    char* get_san_bay_den() { return this->san_bay_den; }
    int get_trang_thai_cb() { return this->trang_thai_cb; }
    char* get_so_hieu_mb() { return this->so_hieu_mb; }
    Ve*** get_listve() { return this->listve; }
    ChuyenBay* get_next() { return this->next; }
    

    // Setter
    void set_ma_so_cb(char* ma_so_cb) { strcpy(this->ma_so_cb, ma_so_cb); }
    void set_thoi_gian_bay(Time thoi_gian_bay) { this->thoi_gian_bay = thoi_gian_bay; }
    void set_san_bay_den(char* san_bay_den) { strcpy(this->san_bay_den, san_bay_den); }
    void set_trang_thai_cb(int trang_thai_cb) { this->trang_thai_cb = trang_thai_cb; }
    void set_so_hieu_mb(char* so_hieu_mb) { strcpy(this->so_hieu_mb, so_hieu_mb); }
    void set_next(ChuyenBay* next) { this->next = next; }


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
    ChuyenBay() {
        init_ve();
    }
    ChuyenBay(char* ma_so_cb, Time thoi_gian_bay, char* san_bay_den, char* so_hieu_mb, int trang_thai_cb) {
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
    int compare_macb(char* macb) {  // return -1: cb này < cb2, 0: cb này == cb2, 1: cb này > cb2
        return strcmp(this->ma_so_cb, macb);
    }
    friend std::istringstream& operator>>(std::istringstream& is, ChuyenBay& mb);
    friend std::ostream& operator<<(std::ostream& os, const ChuyenBay& mb);
    friend int compare_ma_cb(const ChuyenBay* mb1, const ChuyenBay* mb2);
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
int compare_ma_cb(const ChuyenBay* mb1,const ChuyenBay* mb2){
    return strcmp(mb1->ma_so_cb, mb2->ma_so_cb);
}
class ListChuyenBay {
   private:
    ChuyenBay* head = NULL;
    ChuyenBay* tail = NULL;



    void insert_last(ChuyenBay* new_chuyenbay) {
        if (head == nullptr) {
            head = new_chuyenbay;
            tail = new_chuyenbay;
        } else {
            tail->set_next(new_chuyenbay);
            tail = tail->get_next();
        }
    }
   public:
    //func insert order
    void insert_order(ChuyenBay *new_chuyenbay) {
        //nếu danh sách rỗng hoặc chuyên bay mới có mã nhỏ hơn head
        if (head == NULL || compare_ma_cb(new_chuyenbay,head) == -1 ) {
            new_chuyenbay->set_next(head);
            head = new_chuyenbay;
        }
        else {
            ChuyenBay *current = head;
            // Tìm vị trí để chèn vào
            while (current->get_next() != NULL && compare_ma_cb(new_chuyenbay,current) == -1) {
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
    //end
    void add(char* ma_so_cb, Time thoi_gian_bay, char* san_bay_den, char* so_hieu_mb) {
            ChuyenBay* new_chuyenbay = new ChuyenBay(ma_so_cb, thoi_gian_bay, san_bay_den, so_hieu_mb, 1);
            insert_order(new_chuyenbay);
        }

    void add_from_file_data(ChuyenBay* chuyenbay) { // add data từ file, file theo thứ tự sẵn, nên khoogn cần insert_order
        this->insert_last(chuyenbay);
    }
    //func find
    ChuyenBay* find_by_sh_mb_ct(const char* ma_so_mb) { //find cb theo mã máy bay @ return point
        ChuyenBay* p = head;
        while (p != NULL) {
            if (strcmp(p->get_so_hieu_mb(), ma_so_mb) == 0) {  // sử dụng hàm getter để lấy mã máy bay
                return p;                                      // trả về chuyến bay nếu tìm thấy
            }
            p = p->get_next();
        }
        return nullptr;  // trả về NULL nếu không tìm thấy chuyến bay
    } 
    bool find_by_sh_mb(const char* ma_so_mb) { //find cb theo mã máy bay @ return bool
        ChuyenBay* p = head;
        while (p != NULL) {
            if (strcmp(p->get_so_hieu_mb(), ma_so_mb) == 0) {  // sử dụng hàm getter để lấy mã máy bay
                return true;                                      // trả về chuyến bay nếu tìm thấy
            }
            p = p->get_next();
        }
        return false;  // trả về NULL nếu không tìm thấy chuyến bay
    }
    ChuyenBay* find_by_ma_cb_ct(const char* ma_so_cb) {
        ChuyenBay* p = head;
        while (p != NULL) {
            if (strcmp(p->get_ma_so_cb(), ma_so_cb) == 0) {  // sử dụng hàm getter để lấy mã máy bay
                return p;                                      // trả về chuyến bay nếu tìm thấy
            }
            p = p->get_next();
        }
        return nullptr;  // trả về NULL nếu không tìm thấy chuyến bay
    }
    bool find_by_ma_cb(const char* ma_so_cb) {
        ChuyenBay* p = head;
        while (p != NULL) {
            if (strcmp(p->get_ma_so_cb(), ma_so_cb) == 0) {  // sử dụng hàm getter để lấy mã máy bay
                return true;                                      // trả về chuyến bay nếu tìm thấy
            }
            p = p->get_next();
        }
        return false;  // trả về NULL nếu không tìm thấy chuyến bay
    }

    // func find

    

    //getter
    int get_so_luong_cb() {
        int count = 0;
        ChuyenBay* current = head;
        while (current != nullptr) {
            count++;
            current = current->get_next();
        }
        return count;
    }
    ChuyenBay* get_head(){
        return this->head;
    }
    void print() {
        ChuyenBay* current = head;
        while (current != nullptr) {
            cout << *current << "\n";
            current = current->get_next();
        }
    }
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

    friend std::ofstream& operator<<(std::ofstream& os, const ListChuyenBay& list);
};
std::ofstream& operator<<(std::ofstream& os, const ListChuyenBay& list) {
    for (ChuyenBay* current = list.head; current != nullptr; current = current->get_next()) {
        os << *current << "\n";
    }
    return os;
}

#endif