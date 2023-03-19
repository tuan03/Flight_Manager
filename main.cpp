// biến const : in hoa + snake_case
// class : PascalCase
// biến :  chữ thường + snake_case hoặc cameCase
// biến trong class: chữ thường + cameCase
//tên hàm: cameCase

#include"src/maybay.h"
#include"src/hanhkhach.h"
#include"src/chuyenbay.h"
#include"src/file_handling.h"



int main(){
    ListMayBay ds_maybay;
    ListChuyenBay ds_chuyenbay;
    TreeHanhKhach ds_hanhkhach;

    
    // read("src\\data\\data_hanh_khach.txt",ds_hanhkhach);
    // ds_hanhkhach.printAll();

    read("src\\data\\data_chuyen_bay.txt",ds_chuyenbay);
    ds_chuyenbay.print();

    // read("src\\data\\data_may_bay.txt",ds_maybay);
    // ds_maybay.print();
    return 0;
}