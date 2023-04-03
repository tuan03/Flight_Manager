#ifndef FILEHANDLING_H
#define FILEHANDLING_H

#include "chuyenbay.h"
#include "hanhkhach.h"
#include "maybay.h"
#include <string>
#include <cstdio>

using namespace std;

void read(string link_file, ListMayBay& l_mb) {
    std::fstream inout;
    inout.open(link_file, ios::in | ios::out);
    if (inout.is_open()) {  // kiểm tra xem file có được mở thành công không
        std::string line;
        MayBay* temp = nullptr;
        while (std::getline(inout, line)) {
            temp = new MayBay();  // tạo 1 Máy Bay rỗng thông tin
            std::istringstream iss(line);
            iss >> *temp;
            l_mb.add_from_file_data(temp);
        }
        inout.close();
    } else {
        throw "Khong the mo file";
    }
}
void read(string link_file, ListChuyenBay& l_mb) {
    std::fstream inout;
    inout.open(link_file, ios::in | ios::out);
    if (inout.is_open()) {  // kiểm tra xem file có được mở thành công không
        std::string line;
        ChuyenBay* temp = nullptr;
        while (std::getline(inout, line)) {
            temp = new ChuyenBay();
            std::istringstream iss(line);
            iss >> *temp;
            l_mb.add_from_file_data(temp);
        }
        inout.close();
    } else {
        throw "Khong the mo file";
    }
}

void read(string link_file, TreeHanhKhach& l_mb) {
    std::fstream inout;
    inout.open(link_file, ios::in | ios::out);
    if (inout.is_open()) {  // kiểm tra xem file có được mở thành công không
        std::string line;
        HanhKhach* temp = nullptr;
        while (std::getline(inout, line)) {
            temp = new HanhKhach();
            std::istringstream iss(line);
            iss >> *temp;
            l_mb.insert(temp);
        }
        inout.close();
    } else {
        throw "Khong the mo file";
    }
}

void write(string link_file, TreeHanhKhach& list_hanhkhach) {
    std::ifstream inputFile(link_file);
    if (!inputFile.is_open()) {
        std::cerr << "Khong mo duoc file " << link_file << std::endl;
        return;
    }
    std::string fileContent((std::istreambuf_iterator<char>(inputFile)), std::istreambuf_iterator<char>());
    inputFile.close();

    std::ofstream backupFile("src/backup/HanhKhach_data_backup.txt", ios::trunc);
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
    outputFile << list_hanhkhach;
    outputFile.close();

    if (remove("src/backup/HanhKhach_data_backup.txt") != 0) {
        std::cerr << "Khong xoa duoc file backup" << std::endl;
    }
}

void write(string file_path_to_load_data, ListChuyenBay& list) {
    std::ifstream fileToLoadData(file_path_to_load_data);
    if (!fileToLoadData.is_open()) {
        std::cerr << "Khong mo duoc file " << file_path_to_load_data << std::endl;
        return;
    }
    std::string fileContent((std::istreambuf_iterator<char>(fileToLoadData)), std::istreambuf_iterator<char>());
    fileToLoadData.close();

    std::ofstream backupFile("src/backup/ChuyenBay_data_backup.txt", ios::trunc);
    if (!backupFile.is_open()) {
        std::cerr << "Khong tao duoc file backup" << std::endl;
        return;
    }
    backupFile << fileContent;
    backupFile.close();

    std::ofstream outputFile(file_path_to_load_data, ios::trunc);
    if (!outputFile.is_open()) {
        std::cerr << "Khong tao duoc file " << file_path_to_load_data << std::endl;
        return;
    }
    outputFile << list;
    outputFile.close();

    if (remove("src/backup/ChuyenBay_data_backup.txt") != 0) {
        std::cerr << "Khong xoa duoc file backup" << std::endl;
    }
}

void write(string file_path_to_load_data, ListMayBay& list) {
    std::ifstream fileToLoadData(file_path_to_load_data);
    if (!fileToLoadData.is_open()) {
        std::cerr << "Khong mo duoc file " << file_path_to_load_data << std::endl;
        return;
    }
    std::string fileContent((std::istreambuf_iterator<char>(fileToLoadData)), std::istreambuf_iterator<char>());
    fileToLoadData.close();

    std::ofstream backupFile("src/backup/MayBay_data_backup.txt", ios::trunc);
    if (!backupFile.is_open()) {
        std::cerr << "Khong tao duoc file backup" << std::endl;
        return;
    }
    backupFile << fileContent;
    backupFile.close();

    std::ofstream outputFile(file_path_to_load_data, ios::trunc);
    if (!outputFile.is_open()) {
        std::cerr << "Khong tao duoc file " << file_path_to_load_data << std::endl;
        return;
    }
    outputFile << list;
    outputFile.close();

    if (remove("src/backup/MayBay_data_backup.txt") != 0) {
        std::cerr << "Khong xoa duoc file backup" << std::endl;
    }
}

/*
- đọc dữ liệu từng file
- lưu dữ liệu vào từng file


*/

#endif
