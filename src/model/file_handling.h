#ifndef FILEHANDLING_H
#define FILEHANDLING_H

#include "chuyenbay.h"
#include "hanhkhach.h"
#include "maybay.h"
#include <string>
#include <cstdio>

namespace File_Handling{
using namespace std;

template <class List, class Child>
void read_from_file(string link_file, List& list){
    std::fstream inout;
    inout.open(link_file, ios::in | ios::out);
    if (inout.is_open()) {  // kiểm tra xem file có được mở thành công không
        std::string line;
        Child* obj_temp = nullptr;
        while (std::getline(inout, line)) {
            obj_temp = new Child();  // tạo 1 Máy Bay rỗng thông tin
            std::istringstream iss(line);
            iss >> *obj_temp;
            list.add_from_file_data(obj_temp);
        }
        inout.close();
    } else {
        throw "Khong the mo file";
    }
}

template<class List>
void write(string link_file,string link_file_backup, List& list) {
    std::ifstream inputFile(link_file);
    if (!inputFile.is_open()) {
        std::cerr << "Khong mo duoc file " << link_file << std::endl;
        return;
    }
    std::string fileContent((std::istreambuf_iterator<char>(inputFile)), std::istreambuf_iterator<char>());
    inputFile.close();
    std::ofstream backupFile(link_file_backup, ios::trunc);
    if (!backupFile.is_open()) {
        std::cerr << "Khong tao duoc file backup" << std::endl;
        return;
    }
    backupFile << fileContent;
    backupFile.close();

    std::ofstream outputFile(link_file, ios::trunc);
    if (!outputFile.is_open()) {
        std::cerr << "Khong tao duoc file " << link_file << std::endl;
        return;
    }
    outputFile << list;
    outputFile.close();

    if (remove(link_file_backup.c_str()) != 0) {
        std::cerr << "Khong xoa duoc file backup: " << link_file << std::endl;
    }
}
}

/*
- đọc dữ liệu từng file
- lưu dữ liệu vào từng file
*/

#endif
