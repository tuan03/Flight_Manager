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

    FileHandler tuan;
    tuan.read("src\\data\\data_hanh_khach.txt",ds_hanhkhach);
    ds_hanhkhach.printAll();

    return 0;
}