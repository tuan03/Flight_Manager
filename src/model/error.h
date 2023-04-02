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
        Status_Name status;
        string mess;
    Status(string mess ="Thành Công",Status_Name status = Status_Name::SUCCESS) {
        this->mess = mess;
        this->status = status;
    }
    Status_Name get_status() {
        return this->status;
    }
};




#endif