#ifndef CHUYENBAY_H
#define CHUYENBAY_H

#include"maybay.h"

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
        std::string to_string() const { //hh:mm-dd/mm/yyyy
            std::stringstream ss;
            std::tm timeinfo = {};
            timeinfo.tm_year = year - 1900; // năm bắt đầu từ 1900
            timeinfo.tm_mon = month - 1;    // tháng bắt đầu từ 0
            timeinfo.tm_mday = day;
            timeinfo.tm_hour = hour;
            timeinfo.tm_min = minute;
            // In ra chuỗi theo định dạng hh:mm-dd/mm/yyyy
            ss<<std::put_time(&timeinfo, "%H:%M-%d/%m/%Y");
            return ss.str();

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
        friend std::istringstream& operator>>(std::istringstream& is, ThoiGianBay& time);
};
std::istringstream& operator>>(std::istringstream& is, ThoiGianBay& time){
    char delimiter;
    is >> time.hour >> delimiter >> time.minute >> delimiter >> time.day >> delimiter >> time.month >> delimiter >> time.year;
    return is;
}

class Ve {
    private:
    char so_ve[MAX_LENGTH_SO_VE + 1];
    char so_cmnd[MAX_LENGTH_SO_CMND + 1];
    public:
    //getter
    char* getSoVe() { 
        return so_ve;
    }
    char* getSoCMND() {
        return so_cmnd;
    }
    int getSoDay(){
        if(strlen(so_ve) == 3){
            return (int)(so_ve[0] - 'A' + 1);
        } 
        return -1;
    }
    int getSoDong(){
        if(strlen(so_ve) == 3){
            char so_dong[3];
            strcpy(so_dong,so_ve+1);
            return std::stoi(so_dong);
        }
        return -1;
    }
    //setter
    void setSoVe(char* sv) {
        strncpy(so_ve, sv, MAX_LENGTH_SO_VE+1);
    }
    void setSoCMND(char* scmnd) {
        strncpy(so_cmnd, scmnd, MAX_LENGTH_SO_CMND+1);
    }

    Ve(){

    }
    Ve(const Ve& ve){
        strncpy(so_ve, ve.so_ve, MAX_LENGTH_SO_VE+1);
        strncpy(so_cmnd, ve.so_cmnd, MAX_LENGTH_SO_CMND+1);
    }
    Ve(char* sv, char* scmnd) {
        strcpy(so_ve, sv);
        strcpy(so_cmnd, scmnd); 
    }
    Ve(int day, int dong, char* scmnd) {
        char d = (char)('A'+day);
        fomatMaVe(day,dong);
        strcpy(so_cmnd, scmnd); 
    }
    void fomatMaVe(int so_day, int so_dong) {
        this->so_ve[0] = (char)(so_day + 'A' - 1);
        if(so_dong < 10){
            this->so_ve[1] = '0';
            this->so_ve[2] = '0'+so_dong;
        } else {
            this->so_ve[2] = '0' +so_dong%10;
            so_dong/=10;
            this->so_ve[1] = '0'+so_dong;
        }
        this->so_ve[3] = 0;
    }
    
    friend std::ostream& operator<<(std::ostream& os, const Ve& mb) ;
    friend std::istringstream& operator>>(std::istringstream& is, Ve& ve);
};
std::ostream& operator<<(std::ostream& os, const Ve& mb){
    os<<mb.so_ve<<'-'<<mb.so_cmnd<<';';
    return os;
}
 
std::istringstream& operator>>(std::istringstream& is, Ve& ve){
    is.getline(ve.so_ve,MAX_LENGTH_SO_VE+1,'-');
    is.getline(ve.so_cmnd,MAX_LENGTH_SO_CMND+1,';');
    return is;
}

class ChuyenBay { //ma_so_cb|so_hieu_mb|hh:mm-dd/mm/yyyy|san_bay_den|trang_thai|ve1-cmnd;ve2-cmnd
   private:
    char ma_so_cb[MAX_LENGTH_MA_CB + 1];
    ThoiGianBay thoi_gian_bay;
    char san_bay_den[MAX_LENGTH_SAN_BAY_DEN + 1];
    int trang_thai_cb;
    char so_hieu_mb[MAX_LENGTH_SO_HIEU_MB + 1];
    Ve*** listve; // cần fix
    ChuyenBay *next = NULL;
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


    void set_macb(char* mcb){
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
    void add_ve(Ve& ve){ // hàm này để thêm vé từ file data nên sẽ không cần check đã tồn tại
        listve[ve.getSoDay()-1][ve.getSoDong() - 1] = new Ve(ve);
    }

    void init_ve(){
        int so_day = 25, so_dong = 40;
        listve = new Ve**[so_day];
        for (int i = 0; i < so_day; ++i) {
            listve[i] = new Ve*[so_dong];
        }
        for(int i=0; i<so_day; i++){
            for(int j=0; j<so_dong; j++){
                listve[i][j] = nullptr;
            }
        }
    }
    ChuyenBay(){
        init_ve();
    }
    ChuyenBay(char* ma_so_cb, ThoiGianBay thoi_gian_bay, char* san_bay_den, char* so_hieu_mb, int trang_thai_cb) {
        init_ve();
        this->set(ma_so_cb,thoi_gian_bay,san_bay_den,so_hieu_mb,trang_thai_cb);
    }
    ~ChuyenBay(){
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
    int compare_macb_with(ChuyenBay* cb){// return -1: cb này < cb2, 0: cb này == cb2, 1: cb này > cb2
        return strcmp(this->ma_so_cb,cb->get_ma_so_cb());
    }
    int compare_macb(char* macb){// return -1: cb này < cb2, 0: cb này == cb2, 1: cb này > cb2
        return strcmp(this->ma_so_cb,macb);
    }

    friend std::istringstream& operator>>(std::istringstream& is, ChuyenBay& mb);
	friend std::ostream& operator<<(std::ostream& os, const ChuyenBay& mb) ;
};
//ma_so_cb|so_hieu_mb|hh:mm-dd/mm/yyyy|san_bay_den|trang_thai|A01|12321|A02|2344
std::istringstream& operator>>(std::istringstream& is, ChuyenBay& mb) {
    is.getline(mb.ma_so_cb,MAX_LENGTH_MA_CB+1,'|');
    is.getline(mb.so_hieu_mb,MAX_LENGTH_SO_HIEU_MB+1,'|');
    is>>mb.thoi_gian_bay;
    is.ignore(1);
    is.getline(mb.san_bay_den,MAX_LENGTH_SAN_BAY_DEN+1,'|');
    is>>mb.trang_thai_cb;
    is.ignore(1);
    // nhập vé
    Ve ve;
    while (is>>ve)
    {
        mb.add_ve(ve);
    }
    // std::cout<<mb<<'\n';
    
    return is;
}
std::ostream& operator<<(std::ostream& os, const ChuyenBay& mb) {
    os << mb.ma_so_cb << "|" << mb.so_hieu_mb << "|" << mb.thoi_gian_bay.to_string() << "|" << mb.san_bay_den<<'|'<<mb.trang_thai_cb<<'|'; // in cả vé
    int so_day = 25, so_dong = 40;
    for(int i=0; i<so_day; i++){
        for(int j=0; j<so_dong; j++){
            if(mb.listve[i][j] != nullptr){
            os<<*(mb.listve[i][j]);
        }
        }
    }
    return os;
}
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
        head = nullptr;
        
    }
    int get_so_luong_cb(){
        int count = 0;
        ChuyenBay* current = head;
        while (current != nullptr)
        {   
            count++;
            current = current->get_next();
        }
        return count;
        
    }
    void print(){
        ChuyenBay* current = head;
        while (current != nullptr)
        {   
            cout<<*current<<"\n";
            current = current->get_next();
        }
    }
    void add(char* ma_so_cb, ThoiGianBay thoi_gian_bay, char* san_bay_den, char* so_hieu_mb, int trang_thai_cb){
        ChuyenBay* new_chuyenbay = new ChuyenBay(ma_so_cb,thoi_gian_bay,san_bay_den,so_hieu_mb,trang_thai_cb);
        insert_order(new_chuyenbay);
    }
    void insert_last(ChuyenBay *new_chuyenbay){
        if(head == nullptr){
            head = new_chuyenbay;
            tail = new_chuyenbay;
        } else {
            tail->set_next(new_chuyenbay);
            tail = tail->get_next();
        }
    }
    void push_data(ChuyenBay* chuyenbay){
        this->insert_last(chuyenbay);
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