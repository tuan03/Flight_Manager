#ifndef FILEHANDLING_H
#define FILEHANDLING_H

#include "chuyenbay.h"
#include "hanhkhach.h"
#include "maybay.h"
#include <string>
#include <cstdio>

using namespace std;

void load_flight_data_into_file(string path, string backup, ChuyenBay * flight) {
    std::ifstream fileToLoad;
    std::fstream fileToBackup;
    fileToLoad.open(path, ios::in);
    fileToBackup.open(backup, ios::out | ios::in);
    if (fileToLoad.is_open() && fileToBackup.is_open()) {
        std::string data;
        while (std::getline(fileToLoad, data)) {
            fileToBackup << data << "\n";
        }
    } else{
        throw "Can not open file!";
        return;
    }
    fileToLoad.close();

    std::ofstream chuyenBayFile;
    chuyenBayFile.open(path, ios::trunc);
    if (chuyenBayFile.is_open()) {
        chuyenBayFile << flight -> dinh_danh_chuyen_bay_theo_string();
        chuyenBayFile << "\n";
    } else {
        std::string data;
        while (std::getline(fileToBackup, data)) {
            chuyenBayFile << data << "\n";
        }
    }
    fileToBackup.close();
    chuyenBayFile.close();
}

void read(string link_file, ListMayBay& l_mb) {
    if (!l_mb.isEmpty()) {
        l_mb.~ListMayBay();
    }
    std::fstream inout;
    inout.open(link_file, ios::in | ios::out);
    if (inout.is_open()) {  // kiểm tra xem file có được mở thành công không
        std::string line;
        MayBay* temp = nullptr;
        while (std::getline(inout, line)) {
            temp = l_mb.push_empty();  // tạo 1 Máy Bay rỗng thông tin
            std::istringstream iss(line);
            iss >> *temp;
        }
        inout.close();
    } else {
        throw "Khong the mo file";
    }
}
void read(string link_file, ListChuyenBay& l_mb) {
    l_mb.~ListChuyenBay();
    std::fstream inout;
    inout.open(link_file, ios::in | ios::out);
    if (inout.is_open()) {  // kiểm tra xem file có được mở thành công không
        std::string line;
        ChuyenBay* temp = nullptr;
        while (std::getline(inout, line)) {
            temp = new ChuyenBay();
            std::istringstream iss(line);
            iss >> *temp;
            l_mb.push_data(temp);
        }
        inout.close();
    } else {
        throw "Khong the mo file";
    }
}
//     void read(string link_file, ListChuyenBay& l_mb) {
//     l_mb.clear();
//     std::fstream inout(link_file, std::ios::in);

//     if (!inout) {
//         throw std::runtime_error("Khong the mo file " + link_file);
//     }

//     try {
//         std::string line;
//         ChuyenBay* temp = nullptr;

//         while (std::getline(inout, line)) {
//             temp = new ChuyenBay();
//             std::istringstream iss(line);
//             iss >> *temp;
//             l_mb.push_data(temp);
//         }
//     } catch (const std::exception& e) {
//         throw std::runtime_error("Khong the doc file " + link_file + ": " + e.what());
//     }
// }

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

void write(string link_file, TreeHanhKhach& l_mb) {
    std::ifstream inputFile(link_file);
    std::string fileContent((std::istreambuf_iterator<char>(inputFile)), std::istreambuf_iterator<char>());
    inputFile.close();

    std::ofstream backupFile("backup\\HanhKhach_data_backup.txt", ios::trunc);
    backupFile << fileContent;
    backupFile.close();

    std::ofstream outputFile(link_file, ios::trunc);
    outputFile << l_mb;
    outputFile.close();

    remove("backup\\HanhKhach_data_backup.txt");
}

/*
- đọc dữ liệu từng file
- lưu dữ liệu vào từng file


*/

#endif
