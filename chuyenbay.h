#include <cstring>
#include <iostream>

#include "Global.h"

// classes
class Error {
   public:
    int code = 0;
    char message[MAX_LENGTH_ERROR_MESSAGE + 1];
    Error(int code, char message[]) {
        this->code = code;
        strcpy(this->message, message);
    }
};

class Ticket {
   public:
    char so_ve[MAX_LENGTH_SO_VE + 1];
    char so_cmnd[MAX_LENGTH_SO_CMND + 1];
    Ticket *next = NULL;
};

class TicketList {
   public:
    int so_luong = 0;
    Ticket *head = NULL;
    Ticket *tail = NULL;
};

class FlightTime {
   public:
    char minute[MAX_LENGTH_TIME + 1];
    char hour[MAX_LENGTH_TIME + 1];
    char day[MAX_LENGTH_TIME + 1];
    char month[MAX_LENGTH_TIME + 1];
    char year[MAX_LENGTH_TIME + 1];
};

class Flight {
   public:
    char ma_so_cb[MAX_LENGTH_MA_CB + 1];
    FlightTime thoi_gian_bay;
    char san_bay_den[MAX_LENGTH_SAN_BAY_DEN + 1];
    int trang_thai_cb;
    char so_hieu_mb[MAX_LENGTH_SO_HIEU_MB + 1];
    TicketList danh_sach_ve;
    Flight *next = NULL;
};

class FlightList {
   public:
    Flight *head = NULL;
    Flight *tail = NULL;
};

// prototypes of flight
void printFlightList(FlightList);
bool checkFlightIsExisted(FlightList &, Flight);
void insertFlightToListBegin(FlightList &, Flight *);
void pushFlightToList(FlightList &, Flight *);
void insertTheNextFlight(FlightList &, Flight *);
Flight *initFlight(char[], FlightTime, char[], char[], int, TicketList);
void addFlightToList(FlightList &, Flight *);
void catchError(Error);
void setFlightTime(FlightList &, char[], FlightTime);
void cancelFlight(FlightList &, char[]);

// int main() {
//     FlightList danh_sach_cb;
//     Flight *cb;
//     Flight *cb2;
//     Flight *cb3;
//     Flight *cb4;

//     char ma_so_cb[] = "C15";
//     char ma_so_cb2[] = "C16";
//     char ma_so_cb3[] = "C15";
//     char ma_so_cb4[] = "C18";

//     FlightTime thoi_gian_bay;
//     strcpy(thoi_gian_bay.minute, "22");
//     strcpy(thoi_gian_bay.hour, "05");
//     strcpy(thoi_gian_bay.day, "11");
//     strcpy(thoi_gian_bay.month, "07");
//     strcpy(thoi_gian_bay.year, "2022");

//     char san_bay_den[] = "Tan Son Nhat";

//     int trang_thai_cb = 1;

//     char so_hieu_mb[] = "C15";

//     TicketList danh_sach_ve;

//     cb = initFlight(ma_so_cb, thoi_gian_bay, san_bay_den, so_hieu_mb, trang_thai_cb, danh_sach_ve);
//     addFlightToList(danh_sach_cb, cb);

//     cb2 = initFlight(ma_so_cb2, thoi_gian_bay, san_bay_den, so_hieu_mb, trang_thai_cb, danh_sach_ve);
//     addFlightToList(danh_sach_cb, cb2);

//     cb3 = initFlight(ma_so_cb3, thoi_gian_bay, san_bay_den, so_hieu_mb, trang_thai_cb, danh_sach_ve);
//     addFlightToList(danh_sach_cb, cb3);

//     cb4 = initFlight(ma_so_cb4, thoi_gian_bay, san_bay_den, so_hieu_mb, trang_thai_cb, danh_sach_ve);
//     addFlightToList(danh_sach_cb, cb4);

//     // cout list
//     cout << "\n>>> Print 1";
//     printFlightList(danh_sach_cb);

//     // set time
//     FlightTime thoi_gian_bay2;
//     strcpy(thoi_gian_bay2.minute, "09");
//     strcpy(thoi_gian_bay2.hour, "12");
//     strcpy(thoi_gian_bay2.day, "21");
//     strcpy(thoi_gian_bay2.month, "01");
//     strcpy(thoi_gian_bay2.year, "1999");

//     setFlightTime(danh_sach_cb, cb2->ma_so_cb, thoi_gian_bay2);

//     // cout list
//     cout << "\n>>> Print 2";
//     printFlightList(danh_sach_cb);
// }

void catchError(Error error) {
    switch (error.code) {
        case 1: {
            cout << ">>> System Warning: Day bo nho!!!";
        }
        default: {
            cout << ">>> Client Warning: " << error.message;
        }
    }
}

void printFlightList(FlightList danh_sach_cb) {
    for (Flight *cb = danh_sach_cb.head; cb != NULL; cb = cb->next) {
        cout << "\n\n>>> ma so cb: " << cb->ma_so_cb;
        cout << "\n>>> thoi gian bay: ";
        cout << cb->thoi_gian_bay.hour << ":" << cb->thoi_gian_bay.minute
             << " " << cb->thoi_gian_bay.day << "/" << cb->thoi_gian_bay.month
             << "/" << cb->thoi_gian_bay.year;
        cout << "\n>>> san bay den: " << cb->san_bay_den;
        cout << "\n>>> trang thai cb: " << cb->trang_thai_cb;
        cout << "\n>>> so hieu mb: " << cb->so_hieu_mb;
    }
}

bool checkFlightIsExisted(FlightList &danh_sach_cb, char ma_so_cb[]) {
    // check with flight code
    for (Flight *cb = danh_sach_cb.head; cb != NULL; cb = cb->next) {
        if (strcmp(cb->ma_so_cb, ma_so_cb) == 0) {
            return true;
        }
    }
    return false;
}

void insertFlightToListBegin(FlightList &danh_sach_cb, Flight *cb) {
    if (danh_sach_cb.head == NULL) {
        danh_sach_cb.head = cb;
        danh_sach_cb.tail = cb;
        return;
    }
    cb->next = danh_sach_cb.head;
    danh_sach_cb.head = cb;
}

void pushFlightToList(FlightList &danh_sach_cb, Flight *cb) {
    if (danh_sach_cb.head == NULL) {
        danh_sach_cb.head = cb;
        danh_sach_cb.tail = cb;
        return;
    }
    danh_sach_cb.tail->next = cb;
    danh_sach_cb.tail = cb;
}

void insertTheNextFlight(FlightList &danh_sach_cb, Flight *cb_can_them) {
    if (danh_sach_cb.head == NULL) {
        return insertFlightToListBegin(danh_sach_cb, cb_can_them);
    }
    for (Flight *cb = danh_sach_cb.head; cb != NULL; cb = cb->next) {
        if (strcmp(cb->ma_so_cb, cb_can_them->ma_so_cb) == 0) {
            Flight *temp = cb->next;
            cb_can_them->next = temp;
            cb->next = cb_can_them;
            return;
        }
    }
    pushFlightToList(danh_sach_cb, cb_can_them);
}

Flight *initFlight(char ma_so_cb[], FlightTime thoi_gian_bay, char san_bay_den[],
                   char so_hieu_mb[], int trang_thai_cb, TicketList danh_sach_ve) {
    try {
        Flight *them_cb = new Flight;
        if (them_cb == NULL) {
            int code_error = 1;
            char message_error[] = "";
            Error error(code_error, message_error);
            throw error;
        }

        strcpy(them_cb->ma_so_cb, ma_so_cb);
        strcpy(them_cb->san_bay_den, san_bay_den);
        strcpy(them_cb->so_hieu_mb, so_hieu_mb);

        // set status
        them_cb->trang_thai_cb = trang_thai_cb;

        // set time
        strcpy(them_cb->thoi_gian_bay.minute, thoi_gian_bay.minute);
        strcpy(them_cb->thoi_gian_bay.hour, thoi_gian_bay.hour);
        strcpy(them_cb->thoi_gian_bay.day, thoi_gian_bay.day);
        strcpy(them_cb->thoi_gian_bay.month, thoi_gian_bay.month);
        strcpy(them_cb->thoi_gian_bay.year, thoi_gian_bay.year);

        return them_cb;
    } catch (Error error) {
        catchError(error);
        return NULL;
    }
}

void addFlightToList(FlightList &danh_sach_cb, Flight *cb) {
    try {
        bool cb_da_ton_tai = checkFlightIsExisted(danh_sach_cb, cb->ma_so_cb);
        if (cb_da_ton_tai) {
            int code_error = 5;
            char message_error[] = "Chuyen bay da ton tai!!!";
            Error error(code_error, message_error);
            throw error;
        }

        insertTheNextFlight(danh_sach_cb, cb);
    } catch (Error error) {
        catchError(error);
    }
}

void setFlightTime(FlightList &danh_sach_cb, char ma_so_cb[], FlightTime thoi_gian_bay) {
    for (Flight *cb = danh_sach_cb.head; cb != NULL; cb = cb->next) {
        if (strcmp(cb->ma_so_cb, ma_so_cb) == 0) {
            strcpy(cb->thoi_gian_bay.minute, thoi_gian_bay.minute);
            strcpy(cb->thoi_gian_bay.hour, thoi_gian_bay.hour);
            strcpy(cb->thoi_gian_bay.day, thoi_gian_bay.day);
            strcpy(cb->thoi_gian_bay.month, thoi_gian_bay.month);
            strcpy(cb->thoi_gian_bay.year, thoi_gian_bay.year);
            return;
        }
    }
}

void cancelFlight(FlightList &danh_sach_cb, char ma_so_cb[]) {
    for (Flight *cb = danh_sach_cb.head; cb != NULL; cb = cb->next) {
        if (strcmp(cb->ma_so_cb, ma_so_cb) == 0) {
            cb->trang_thai_cb = 0;
            return;
        }
    }
}
