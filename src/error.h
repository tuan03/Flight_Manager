#ifndef ERROR_H
#define ERROR_H
#include "Global.h"
// classes
enum Error_Name {
    HE_THONG_DAY_BO_NHO = 1,
};

class Error {
    public:
        Error_Name name;
    Error(Error_Name name) {
        this->name = name;
    }

    std::string getError() {
        switch (this->name) {
            case HE_THONG_DAY_BO_NHO: {
                return "He Thong Day Bo Nho";
            }
            default: {
                return "Khong Xac Dinh";
            }
        }
    }
};

#endif