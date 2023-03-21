#include"src/flight_manager.h"
int main(){
    Flight_Manager qlcb;
    qlcb.getListCB().print();
    qlcb.getListHK().printAll();
    qlcb.getListMB().print();
    return 0;
}