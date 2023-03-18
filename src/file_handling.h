#ifndef FILEHANDLING_H
#define FILEHANDLING_H


#include"chuyenbay.h"
#include"maybay.h"
#include"hanhkhach.h"

using namespace std;
class FileHandler{
    private:
        std::fstream inout;
    public:
    FileHandler(){
        
    }
    void read(string link_file,ListMayBay& l_mb){
        inout.open(link_file,ios::in | ios::out);
        if (inout.is_open()) { // kiểm tra xem file có được mở thành công không
            std::string line;
            MayBay* temp = nullptr;
            while (std::getline(inout, line)) {
                temp = new MayBay();
                std::istringstream iss(line);
                iss>>*temp;
                l_mb.push_data(temp);
                
            }
            inout.close();
        } else {
            throw "Khong the mo file";
        }
    }
    void read(string link_file,ListChuyenBay& l_mb){
        inout.open(link_file,ios::in | ios::out);
        if (inout.is_open()) { // kiểm tra xem file có được mở thành công không
            std::string line;
            ChuyenBay* temp = nullptr;
            while (std::getline(inout, line)) {
                temp = new ChuyenBay();
                std::istringstream iss(line);
                iss>>*temp;
                l_mb.push_data(temp);
                
            }
            inout.close();
        } else {
            throw "Khong the mo file";
        }
    }
    void read(string link_file,TreeHanhKhach& l_mb){
        inout.open(link_file,ios::in | ios::out);
        if (inout.is_open()) { // kiểm tra xem file có được mở thành công không
            std::string line;
            HanhKhach* temp = nullptr;
            while (std::getline(inout, line)) {
                temp = new HanhKhach();
                std::istringstream iss(line);
                iss>>*temp;
                l_mb.insert(temp);
                
            }
            inout.close();
        } else {
            throw "Khong the mo file";
        }
    }


    void write(string link_file,TreeHanhKhach& l_mb){
        std::ifstream inputFile(link_file);
        std::string fileContent((std::istreambuf_iterator<char>(inputFile)), std::istreambuf_iterator<char>());
        inputFile.close();

        std::ofstream backupFile("backup\\HanhKhach_data_backup.txt",ios::trunc);
        backupFile << fileContent;
        backupFile.close();

        std::ofstream outputFile(link_file,ios::trunc);
        outputFile<<l_mb;
        outputFile.close();
        
        remove("backup\\HanhKhach_data_backup.txt");
        
    }
};



/*
- đọc dữ liệu từng file 
- lưu dữ liệu vào từng file


*/


#endif



