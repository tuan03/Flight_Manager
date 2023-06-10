#ifndef CHUYENBAY_H
#define CHUYENBAY_H

#include <chrono>

#include "error.h"
#include "maybay.h"

class Time
{
private:
    int minute;
    int hour;
    int day;
    int month;
    int year;

public:
    // getter
    int get_minute() { return this->minute; }
    int get_hour() { return this->hour; }
    int get_day() { return this->day; }
    int get_month() { return this->month; }
    int get_year() { return this->year; }

    std::string to_string() const
    { // hh:mm-dd/mm/yyyy
        std::stringstream ss;
        std::tm timeinfo = {};
        timeinfo.tm_year = year - 1900; // năm bắt đầu từ 1900
        timeinfo.tm_mon = month - 1;    // tháng bắt đầu từ 0
        timeinfo.tm_mday = day;
        timeinfo.tm_hour = hour;
        timeinfo.tm_min = minute;
        // In ra chuỗi theo định dạng hh:mm-dd/mm/yyyy
        ss << std::put_time(&timeinfo, "%H:%M-%d/%m/%Y");
        return ss.str();
    }
    std::string to_string_dd_mm_yyyy_hh_mm() const
    { // hh:mm-dd/mm/yyyy
        std::stringstream ss;
        std::tm timeinfo = {};
        timeinfo.tm_year = year - 1900; // năm bắt đầu từ 1900
        timeinfo.tm_mon = month - 1;    // tháng bắt đầu từ 0
        timeinfo.tm_mday = day;
        timeinfo.tm_hour = hour;
        timeinfo.tm_min = minute;
        // In ra chuỗi theo định dạng hh:mm-dd/mm/yyyy
        ss << std::put_time(&timeinfo, "%d/%m/%Y %H:%M");
        return ss.str();
    }
    Time()
    {
    }
    Time(int m, int h, int d, int month, int y)
    {
        this->set(m, h, d, month, y);
    }

    void set(int minute, int hour, int day, int month, int year)
    {
        this->minute = minute;
        this->hour = hour;
        this->day = day;
        this->month = month;
        this->year = year;
    }
    void get_current_time()
    {
        auto now = chrono::system_clock::now();
        time_t now_c = chrono::system_clock::to_time_t(now);
        struct tm *parts = localtime(&now_c);
        this->hour = parts->tm_hour;
        this->minute = parts->tm_min;
        this->year = parts->tm_year + 1900;
        this->month = parts->tm_mon + 1;
        this->day = parts->tm_mday;
    }
    /**
     * @brief Hàm tính khoảng cách giữa 2 mốc thời gian
     *
     * @param t1 thời gian A
     * @param t2 thời gian B
     * @return số giây B - A
     */
    static double timeDiffInSeconds(Time t1, Time t2)
    {
        struct tm time1, time2;
        time1.tm_sec = 0;
        time1.tm_hour = t1.hour;
        time1.tm_min = t1.minute;
        time1.tm_year = t1.year - 1900;
        time1.tm_mon = t1.month - 1;
        time1.tm_mday = t1.day;
        time2.tm_sec = 0;
        time2.tm_hour = t2.hour;
        time2.tm_min = t2.minute;
        time2.tm_year = t2.year - 1900;
        time2.tm_mon = t2.month - 1;
        time2.tm_mday = t2.day;

        time_t t1_time = mktime(&time1);
        time_t t2_time = mktime(&time2);

        double diff = difftime(t2_time, t1_time);
        return diff;
    }
    bool isValidDate()
    {
        if (minute < 0 || minute > 60 || hour < 0 || hour > 24)
        {
            return false;
        }
        if (year < 1 || year > 9999 || month < 1 || month > 12)
        {
            return false;
        }
        int daysInMonth;
        if (month == 2)
        {
            if (Func_Global::is_nam_nhuan(year))
            {
                daysInMonth = 29;
            }
            else
            {
                daysInMonth = 28;
            }
        }
        else if (month == 4 || month == 6 || month == 9 || month == 11)
        {
            daysInMonth = 30;
        }
        else
        {
            daysInMonth = 31;
        }
        if (day < 1 || day > daysInMonth)
        {
            return false;
        }
        return true;
    }
};

class ListVe
{
private:
    char ***list = nullptr;

    // chỉ số tạm
    int so_day = 0;
    int so_dong = 0;

public:
    ListVe()
    {
    }
    ~ListVe()
    {
        for (int i = 0; i < this->so_day; ++i)
        {
            for (int j = 0; j < this->so_dong; ++j)
            {
                delete list[i][j];
            }
            delete[] list[i];
        }
        delete[] list;
    }
    void init_ve(int so_day, int so_dong)
    { // khởi tạo vé
        this->so_day = so_day;
        this->so_dong = so_dong;
        if (this->so_day < 0 || this->so_dong < 0)
            throw "Error : Init Ticket\n";

        list = new char **[this->so_day];
        for (int i = 0; i < this->so_day; ++i)
        {
            list[i] = new char *[this->so_dong];
        }
        for (int i = 0; i < this->so_day; i++)
        {
            for (int j = 0; j < this->so_dong; j++)
            {
                list[i][j] = nullptr;
            }
        }
    }
    int get_so_day()
    {
        return so_day;
    }
    int get_so_dong()
    {
        return so_dong;
    }
    int get_ve_da_ban()
    {
        int count = 0;
        for (int i = 0; i < this->so_day; i++)
        {
            for (int j = 0; j < this->so_dong; j++)
            {
                if (this->list[i][j] != nullptr)
                {
                    count++;
                }
            }
        }
        return count;
    }
    int get_total_ve()
    {
        return so_day * so_dong;
    }
    int so_ve_trong()
    {
        return get_total_ve() - get_ve_da_ban();
    }
    const char *get_cmnd(int i, int j)
    {
        if (list[i][j] == nullptr)
            throw "Rong\n";
        return list[i][j];
    }
    bool check_empty(int so_day, int so_dong) // true nếu empty
    { 
        return list[so_day][so_dong] == nullptr;
    }

    Status add_ve(int so_day, int so_dong, const char *cmnd)
    { // hàm này để thêm vé từ file data nên sẽ không cần check đã tồn tại
        if (so_day < 0 || so_dong < 0 || so_day >= this->so_day || so_dong >= this->so_dong)
            return Status("Số Dãy Hoặc Số Dòng Không Hợp Lệ");
        list[so_day][so_dong] = new char[MAX_LENGTH_SO_CMND + 1];
        strcpy(list[so_day][so_dong], cmnd);
        return Status("Đặt Vé Thành Công", Status_Name::SUCCESS);
    }
    Status huy_ve(int so_day, int so_dong){
        delete list[so_day][so_dong];
        list[so_day][so_dong] = nullptr;
        return Status("Hủy Vé Thành Công", Status_Name::SUCCESS);
    }
};

class ChuyenBay
{
private:
    char ma_so_cb[MAX_LENGTH_MA_CB + 1];
    Time thoi_gian_bay;
    char san_bay_den[MAX_LENGTH_SAN_BAY_DEN + 1];
    int trang_thai_cb; // 0: hủy chuyến, 1: còn vé, 2: hết vé,3: hoàn tất
    char so_hieu_mb[MAX_LENGTH_SO_HIEU_MB + 1];
    ListVe list_ve;
    ChuyenBay *next = NULL;

    void set(const char *ma_so_cb, Time thoi_gian_bay, const char *san_bay_den, const char *so_hieu_mb, int trang_thai_cb)
    {
        strcpy(this->ma_so_cb, ma_so_cb);
        strcpy(this->san_bay_den, san_bay_den);
        strcpy(this->so_hieu_mb, so_hieu_mb);

        this->trang_thai_cb = trang_thai_cb;
        this->thoi_gian_bay = thoi_gian_bay;
    }

public:
    // Getter
    const char *get_ma_so_cb() { return this->ma_so_cb; }
    Time get_thoi_gian_bay() { return this->thoi_gian_bay; }
    const char *get_san_bay_den() { return this->san_bay_den; }
    int get_trang_thai_cb() { return this->trang_thai_cb; }
    const char *get_so_hieu_mb() { return this->so_hieu_mb; }
    ListVe &get_listve() { return this->list_ve; }
    ChuyenBay *get_next() { return this->next; }

    // Setter
    void set_ma_so_cb(const char *ma_so_cb) { strcpy(this->ma_so_cb, ma_so_cb); }
    void set_thoi_gian_bay(Time thoi_gian_bay) { this->thoi_gian_bay = thoi_gian_bay; }
    void set_san_bay_den(const char *san_bay_den) { strcpy(this->san_bay_den, san_bay_den); }
    void set_trang_thai_cb(int trang_thai_cb) { this->trang_thai_cb = trang_thai_cb; }
    void set_so_hieu_mb(const char *so_hieu_mb) { strcpy(this->so_hieu_mb, so_hieu_mb); }
    void set_next(ChuyenBay *next) { this->next = next; }

    ChuyenBay()
    {
    }
    ChuyenBay(const char *ma_so_cb, Time thoi_gian_bay, const char *san_bay_den, const char *so_hieu_mb, int trang_thai_cb)
    {
        // init_ve();
        this->set(ma_so_cb, thoi_gian_bay, san_bay_den, so_hieu_mb, trang_thai_cb);
    }
    ~ChuyenBay()
    {
    }
    int compare_macb(const char *macb)
    { // return -1: cb này < cb2, 0: cb này == cb2, 1: cb này > cb2
        return strcmp(this->ma_so_cb, macb);
    }
    Status huy_chuyen_bay(){
        if(this->trang_thai_cb == 0) return Status("Chuyến Bay Đã Được Hủy Trước Đó.");
        if(this->trang_thai_cb == 3) return Status("Chuyến Bay Đã Thực Hiện Thành Công.");
        this->trang_thai_cb = 0;
        return Status("Hủy Chuyến Bay Thành Công.",Status_Name::SUCCESS);

    }
    void serialize(std::ofstream &os)
    {
        os.write(ma_so_cb, sizeof(ma_so_cb));
        os.write(san_bay_den, sizeof(san_bay_den));
        os.write(so_hieu_mb, sizeof(so_hieu_mb));
        os.write(reinterpret_cast<const char *>(&trang_thai_cb), sizeof(trang_thai_cb));
        os.write(reinterpret_cast<const char *>(&thoi_gian_bay), sizeof(thoi_gian_bay));
        int so_luong_ve = list_ve.get_ve_da_ban();
        os.write(reinterpret_cast<char *>(&so_luong_ve), sizeof(so_luong_ve));
        // in vé
        for (int i = 0; i < list_ve.get_so_day(); i++)
        {
            for (int j = 0; j < list_ve.get_so_dong(); j++)
            {
                if (!(list_ve.check_empty(i, j)))
                {
                    os.write(reinterpret_cast<const char *>(&i), sizeof(i));
                    os.write(reinterpret_cast<const char *>(&j), sizeof(j));
                    os.write(reinterpret_cast<const char *>(list_ve.get_cmnd(i, j)), MAX_LENGTH_SO_CMND + 1);
                }
            }
        }
    }

    // chuyển đổi chuỗi byte thành đối tượng
    void deserialize(std::ifstream &is, ListMayBay &listmb)
    {
        is.read(ma_so_cb, sizeof(ma_so_cb));
        is.read(san_bay_den, sizeof(san_bay_den));
        is.read(so_hieu_mb, sizeof(so_hieu_mb));
        is.read(reinterpret_cast<char *>(&trang_thai_cb), sizeof(trang_thai_cb));
        is.read(reinterpret_cast<char *>(&thoi_gian_bay), sizeof(thoi_gian_bay));
        int so_luong_ve = 0;
        is.read(reinterpret_cast<char *>(&so_luong_ve), sizeof(so_luong_ve));
        int so_day = 0, so_dong = 0;
        char cmnd[MAX_LENGTH_SO_CMND + 1];
        MayBay *temp = listmb.find_mamb_ct(so_hieu_mb);
        list_ve.init_ve(temp->getSoDay(), temp->getSoDong());
        for (int i = 0; i < so_luong_ve; i++)
        {
            is.read(reinterpret_cast<char *>(&so_day), sizeof(so_day));
            is.read(reinterpret_cast<char *>(&so_dong), sizeof(so_dong));
            is.read(reinterpret_cast<char *>(cmnd), sizeof(cmnd));
            list_ve.add_ve(so_day, so_dong, cmnd);
        }
    }

    friend int compare_ma_cb(const ChuyenBay *mb1, const ChuyenBay *mb2);
};
int compare_ma_cb(const ChuyenBay *mb1, const ChuyenBay *mb2)
{
    return strcmp(mb1->ma_so_cb, mb2->ma_so_cb);
}
class ListChuyenBay
{
private:
    ChuyenBay *head = NULL;
    ChuyenBay *tail = NULL;

    void insert_last(ChuyenBay *new_chuyenbay)
    {
        if (head == nullptr)
        {
            head = new_chuyenbay;
            tail = new_chuyenbay;
        }
        else
        {
            tail->set_next(new_chuyenbay);
            tail = tail->get_next();
        }
    }

public:
    // func insert order
    void insert_order(ChuyenBay *new_chuyenbay)
    {
        // nếu danh sách rỗng hoặc chuyên bay mới có mã nhỏ hơn head
        if (head == NULL || compare_ma_cb(new_chuyenbay, head) == -1)
        {
            new_chuyenbay->set_next(head);
            head = new_chuyenbay;
        }
        else
        {
            ChuyenBay *current = head;
            // Tìm vị trí để chèn vào
            while (current->get_next() != NULL && compare_ma_cb(new_chuyenbay, current) == -1)
            {
                current = current->get_next();
            }

            new_chuyenbay->set_next(current->get_next());
            current->set_next(new_chuyenbay);
        }
        // Nếu danh sách rỗng hoặc chuyenbay được thêm sau tail thì cập nhật tail
        if (tail == NULL || tail->get_next() == new_chuyenbay)
        {
            tail = new_chuyenbay;
        }
    }
    // end
    void add(const char *ma_so_cb, Time thoi_gian_bay, const char *san_bay_den, const char *so_hieu_mb)
    {
        ChuyenBay *new_chuyenbay = new ChuyenBay(ma_so_cb, thoi_gian_bay, san_bay_den, so_hieu_mb, 1);
        insert_order(new_chuyenbay);
    }

    // func find
    ChuyenBay *find_by_sh_mb_ct(const char *ma_so_mb)
    { // find cb theo mã máy bay @ return point
        ChuyenBay *p = head;
        while (p != NULL)
        {
            if (strcmp(p->get_so_hieu_mb(), ma_so_mb) == 0)
            {             // sử dụng hàm getter để lấy mã máy bay
                return p; // trả về chuyến bay nếu tìm thấy
            }
            p = p->get_next();
        }
        return nullptr; // trả về NULL nếu không tìm thấy chuyến bay
    }

    // tìm theo số hiệu máy bay sẽ trả về cái mà đang còn vé hoặc hết vé mà không hủy hoặc hoàn thành
    bool find_by_sh_mb(const char *so_hieu_mb)
    { // find cb theo mã máy bay @ return bool
        ChuyenBay *p = head;
        while (p != NULL)
        {
            if (strcmp(p->get_so_hieu_mb(), so_hieu_mb) == 0 && p->get_trang_thai_cb() != 0 && p->get_trang_thai_cb() != 3)
            {                // sử dụng hàm getter để lấy mã máy bay
                return true; // trả về chuyến bay nếu tìm thấy
            }
            p = p->get_next();
        }
        return false; // trả về NULL nếu không tìm thấy chuyến bay
    }
    bool find_by_sh_mb_v2(const char *so_hieu_mb)
    { // find cb theo mã máy bay @ return bool
        ChuyenBay *p = head;
        while (p != NULL)
        {
            if (strcmp(p->get_so_hieu_mb(), so_hieu_mb) == 0)
            {                // sử dụng hàm getter để lấy mã máy bay
                return true; // trả về chuyến bay nếu tìm thấy
            }
            p = p->get_next();
        }
        return false; // trả về NULL nếu không tìm thấy chuyến bay
    }
    ChuyenBay *find_by_ma_cb_ct(const char *ma_so_cb)
    {
        ChuyenBay *p = head;
        while (p != NULL)
        {
            if (strcmp(p->get_ma_so_cb(), ma_so_cb) == 0 && p->get_trang_thai_cb() != 0 && p->get_trang_thai_cb() != 3)
            {             // sử dụng hàm getter để lấy mã máy bay
                return p; // trả về chuyến bay nếu tìm thấy
            }
            p = p->get_next();
        }
        return nullptr; // trả về NULL nếu không tìm thấy chuyến bay
    }

    bool find_by_ma_cb(const char *ma_so_cb)
    {
        ChuyenBay *p = head;
        while (p != NULL)
        {
            if (strcmp(p->get_ma_so_cb(), ma_so_cb) == 0)
            {                // sử dụng hàm getter để lấy mã máy bay
                return true; // trả về chuyến bay nếu tìm thấy
            }
            p = p->get_next();
        }
        return false; // trả về NULL nếu không tìm thấy chuyến bay
    }

    // func find

    // getter
    int get_so_luong_cb()
    {
        int count = 0;
        ChuyenBay *current = head;
        while (current != nullptr)
        {
            count++;
            current = current->get_next();
        }
        return count;
    }
    ChuyenBay *get_head()
    {
        return this->head;
    }
    // void print() {
    //     ChuyenBay* current = head;
    //     while (current != nullptr) {
    //         cout << *current << "\n";
    //         current = current->get_next();
    //     }
    // }
    ~ListChuyenBay()
    {
        ChuyenBay *current = head;
        ChuyenBay *next = nullptr;
        while (current != nullptr)
        {
            next = current->get_next();
            delete current;
            current = next;
        }
        head = nullptr;
    }
     void read_bin(string fileName, ListMayBay& list_mb)
    {
        std::ifstream file(fileName, std::ios::binary);
        if (file.is_open())
        {
            ChuyenBay *temp = nullptr;
            int so_luong = 0;
            if(!(file.read(reinterpret_cast<char*>(&so_luong), sizeof(so_luong)))){
                so_luong = 0;
            }
            for(int i=0; i<so_luong; i++){
                temp = new ChuyenBay();        // cấp phát bộ nhớ động cho node
                temp->deserialize(file,list_mb);
                this->insert_last(temp);
            }
            file.close();
        }
        else
        {
            std::cout << "Khong the mo file.\n";
        }
    }
    void write_bin(string fileName)
    {
        std::ofstream file(fileName, std::ios::binary);
        if (file.is_open())
        {   
            int so_luong = this->get_so_luong_cb();
            file.write(reinterpret_cast<const char *>(&so_luong), sizeof(so_luong));
            for (ChuyenBay* current = this->head; current != nullptr; current = current->get_next()) {
                current->serialize(file);
            }
            file.close();
        }
        else
        {
            std::cout << "Khong the mo file.\n";
        }
    }
};

#endif