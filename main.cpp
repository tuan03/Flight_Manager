#include"src/flight_manager.h"
#include"src/views/component.h"
#undef main
int main(){
    MyScreen myscreen(1800,800,"Quản Lí Chuyến Bay","src/views/font/Arial.ttf",26);

    Flight_Manager qlcb;
    
    qlcb.getListCB().print();
    qlcb.getListHK().printAll();
    qlcb.getListMB().print();
    return 0;
}