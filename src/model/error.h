#ifndef ERROR_H
#define ERROR_H
#include "../Global.h"
// classes
enum Status_Name {
    SUCCESS,
    ALREADY_EXIST
};
class Status {
    public:
        Status status;
        string mess;
    Status(string mess ="Thành Công",Status_Name status = Status_Name::SUCCESS) {
        this->mess = mess;
    }
    string get_status() {
        return this->mess;
    }
};




#endif