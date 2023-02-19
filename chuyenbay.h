#include <cstring>
#include <iostream>

#include "Global.h"

// classes
enum ErrorCodes {
    LOI_HE_THONG_DAY_BO_NHO = 1,
};

class Error {
   public:
    int code = 0;
    char message[MAX_LENGTH_ERROR_MESSAGE + 1];
    Error(int code, char message[]) {
        this->code = code;
        strcpy(this->message, message);
    }

    void catchError() {
        switch (this->code) {
            case LOI_HE_THONG_DAY_BO_NHO: {
                cout << ">>> System Warning: Day bo nho!!!";
            }
            default: {
                cout << ">>> Client Warning: " << this->message;
            }
        }
    }
};

class Ve {
   public:
    char so_ve[MAX_LENGTH_SO_VE + 1];
    char so_cmnd[MAX_LENGTH_SO_CMND + 1];
    Ve *next = NULL;
};

class DanhSachVe {
   public:
    int so_luong = 0;
    Ve *head = NULL;
    Ve *tail = NULL;
};

class ThoiGianBay {
   public:
    char minute[MAX_LENGTH_TIME + 1];
    char hour[MAX_LENGTH_TIME + 1];
    char day[MAX_LENGTH_TIME + 1];
    char month[MAX_LENGTH_TIME + 1];
    char year[MAX_LENGTH_TIME + 1];

    ThoiGianBay() {}

    ThoiGianBay(char minute[], char hour[], char day[], char month[], char year[]) {
        strcpy(this->minute, minute);
        strcpy(this->hour, hour);
        strcpy(this->day, day);
        strcpy(this->month, month);
        strcpy(this->year, year);
    }

    void operator=(const ThoiGianBay &thoi_gian_bay) {
        strcpy(this->minute, thoi_gian_bay.minute);
        strcpy(this->hour, thoi_gian_bay.hour);
        strcpy(this->day, thoi_gian_bay.day);
        strcpy(this->month, thoi_gian_bay.month);
        strcpy(this->year, thoi_gian_bay.year);
    }

    string dinhDangChuoiThoiGian() {
        char chuoi_thoi_gian[MAX_LENGTH_TIME_STRING + 1] = "";
        char dau_hai_cham[2] = ":";
        char dau_gach_cheo[2] = "/";
        char dau_cach[2] = " ";

        strcat(chuoi_thoi_gian, this->hour);
        strcat(chuoi_thoi_gian, dau_hai_cham);
        strcat(chuoi_thoi_gian, this->minute);
        strcat(chuoi_thoi_gian, dau_cach);
        strcat(chuoi_thoi_gian, this->day);
        strcat(chuoi_thoi_gian, dau_gach_cheo);
        strcat(chuoi_thoi_gian, this->month);
        strcat(chuoi_thoi_gian, dau_gach_cheo);
        strcat(chuoi_thoi_gian, this->year);

        return string(chuoi_thoi_gian);
    }
};

class ChuyenBay {
   public:
    char ma_so_cb[MAX_LENGTH_MA_CB + 1];
    ThoiGianBay thoi_gian_bay;
    char san_bay_den[MAX_LENGTH_SAN_BAY_DEN + 1];
    int trang_thai_cb;
    char so_hieu_mb[MAX_LENGTH_SO_HIEU_MB + 1];
    DanhSachVe danh_sach_ve;
    ChuyenBay *next = NULL;

    ChuyenBay(char ma_so_cb[], ThoiGianBay thoi_gian_bay, char san_bay_den[],
              char so_hieu_mb[], int trang_thai_cb, DanhSachVe danh_sach_ve) {
        strcpy(this->ma_so_cb, ma_so_cb);
        strcpy(this->san_bay_den, san_bay_den);
        strcpy(this->so_hieu_mb, so_hieu_mb);

        // set status
        this->trang_thai_cb = trang_thai_cb;

        // set time
        strcpy(this->thoi_gian_bay.minute, thoi_gian_bay.minute);
        strcpy(this->thoi_gian_bay.hour, thoi_gian_bay.hour);
        strcpy(this->thoi_gian_bay.day, thoi_gian_bay.day);
        strcpy(this->thoi_gian_bay.month, thoi_gian_bay.month);
        strcpy(this->thoi_gian_bay.year, thoi_gian_bay.year);
    }

    void kiemTraKhoiTaoChuyenBay() {
        if (this == NULL) {
            char mo_ta_loi_error[] = "";
            Error error(1, mo_ta_loi_error);
            error.catchError();
        }
    }

    ~ChuyenBay() {
        delete this;
    }
};

class DanhSachChuyenBay {
   public:
    ChuyenBay *head = NULL;
    ChuyenBay *tail = NULL;

    bool kiemTraChuyenBayTrongDanhSach(char ma_so_cb[]) {
        // check with flight code
        for (ChuyenBay *cb = this->head; cb != NULL; cb = cb->next) {
            if (strcmp(cb->ma_so_cb, ma_so_cb) == 0) {
                return true;
            }
        }
        return false;
    }

    void chenChuyenBayVaoDauDanhSach(ChuyenBay *cb) {
        if (this->head == NULL) {
            this->head = cb;
            this->tail = cb;
            return;
        }
        cb->next = this->head;
        this->head = cb;
    }

    void dayChuyenBayVaoCuoiDanhSach(ChuyenBay *cb) {
        if (this->head == NULL) {
            this->head = cb;
            this->tail = cb;
            return;
        }
        this->tail->next = cb;
        this->tail = cb;
    }

    void chenChuyenBayVaoGiuaDanhSach(ChuyenBay *cb_can_them) {
        if (this->head == NULL) {
            return this->chenChuyenBayVaoDauDanhSach(cb_can_them);
        }
        for (ChuyenBay *cb = this->head; cb != NULL; cb = cb->next) {
            if (strcmp(cb->ma_so_cb, cb_can_them->ma_so_cb) == 0) {
                ChuyenBay *temp = cb->next;
                cb_can_them->next = temp;
                cb->next = cb_can_them;
                return;
            }
        }
        this->dayChuyenBayVaoCuoiDanhSach(cb_can_them);
    }

    void themChuyenBay(ChuyenBay *cb_can_them) {
        try {
            bool cb_da_ton_tai = kiemTraChuyenBayTrongDanhSach(cb_can_them->ma_so_cb);
            if (cb_da_ton_tai) {
                char mo_ta_loi_error[] = "Chuyen bay da ton tai!!!";
                Error error(5, mo_ta_loi_error);
                throw error;
            }

            if (this->head == NULL) {
                return this->chenChuyenBayVaoDauDanhSach(cb_can_them);
            }

            for (ChuyenBay *cb = this->head; cb != NULL; cb = cb->next) {
                if (strcmp(cb->ma_so_cb, cb_can_them->ma_so_cb) == 0) {
                    ChuyenBay *temp = cb->next;
                    cb_can_them->next = temp;
                    cb->next = cb_can_them;
                    return;
                }
            }

            this->dayChuyenBayVaoCuoiDanhSach(cb_can_them);
        } catch (Error error) {
            error.catchError();
        }
    }

    void chinhSuaThoiGianChuyenBay(char ma_so_cb[], ThoiGianBay thoi_gian_bay) {
        for (ChuyenBay *cb = this->head; cb != NULL; cb = cb->next) {
            if (strcmp(cb->ma_so_cb, ma_so_cb) == 0) {
                cb->thoi_gian_bay = thoi_gian_bay;
                return;
            }
        }
    }

    void huyChuyenBay(char ma_so_cb[]) {
        for (ChuyenBay *cb = this->head; cb != NULL; cb = cb->next) {
            if (strcmp(cb->ma_so_cb, ma_so_cb) == 0) {
                cb->trang_thai_cb = 0;
                return;
            }
        }
    }
};

// prototypes of flights
void inDanhSachChuyenBay(DanhSachChuyenBay);

int main() {
    DanhSachChuyenBay danh_sach_cb;

    char ma_so_cb[] = "C15";
    char ma_so_cb2[] = "C16";
    char ma_so_cb3[] = "C15";
    char ma_so_cb4[] = "C18";

    char minute[] = "22";
    char hour[] = "05";
    char day[] = "11";
    char month[] = "07";
    char year[] = "2022";
    ThoiGianBay thoi_gian_bay(minute, hour, day, month, year);

    char san_bay_den[] = "Tan Son Nhat";

    int trang_thai_cb = 1;

    char so_hieu_mb[] = "C15";

    DanhSachVe danh_sach_ve;

    ChuyenBay *cb = new ChuyenBay(ma_so_cb, thoi_gian_bay, san_bay_den, so_hieu_mb,
                                  trang_thai_cb, danh_sach_ve);
    cb->kiemTraKhoiTaoChuyenBay();

    ChuyenBay *cb2 = new ChuyenBay(ma_so_cb2, thoi_gian_bay, san_bay_den, so_hieu_mb,
                                   trang_thai_cb, danh_sach_ve);
    cb->kiemTraKhoiTaoChuyenBay();

    ChuyenBay *cb3 = new ChuyenBay(ma_so_cb3, thoi_gian_bay, san_bay_den, so_hieu_mb,
                                   trang_thai_cb, danh_sach_ve);
    cb->kiemTraKhoiTaoChuyenBay();

    ChuyenBay *cb4 = new ChuyenBay(ma_so_cb4, thoi_gian_bay, san_bay_den, so_hieu_mb,
                                   trang_thai_cb, danh_sach_ve);
    cb->kiemTraKhoiTaoChuyenBay();

    danh_sach_cb.themChuyenBay(cb);
    danh_sach_cb.themChuyenBay(cb2);
    danh_sach_cb.themChuyenBay(cb3);
    danh_sach_cb.themChuyenBay(cb4);

    // cout list 1
    cout << "\n\n>>> Print 1";
    inDanhSachChuyenBay(danh_sach_cb);

    // set time
    char minute2[] = "09";
    char hour2[] = "12";
    char day2[] = "21";
    char month2[] = "01";
    char year2[] = "1999";
    ThoiGianBay thoi_gian_bay2(minute2, hour2, day2, month2, year2);

    danh_sach_cb.chinhSuaThoiGianChuyenBay(cb2->ma_so_cb, thoi_gian_bay2);

    // cout list 2
    cout << "\n\n>>> Print 2";
    inDanhSachChuyenBay(danh_sach_cb);
}

void inDanhSachChuyenBay(DanhSachChuyenBay danh_sach_cb) {
    for (ChuyenBay *cb = danh_sach_cb.head; cb != NULL; cb = cb->next) {
        cout << "\n\n>>> Ma so cb: " << cb->ma_so_cb;
        cout << "\n>>> Thoi gian bay: " << cb->thoi_gian_bay.dinhDangChuoiThoiGian();
        cout << "\n>>> San bay den: " << cb->san_bay_den;
        cout << "\n>>> Trang thai cb: " << cb->trang_thai_cb;
        cout << "\n>>> So hieu mb: " << cb->so_hieu_mb;
    }
}