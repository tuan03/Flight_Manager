#ifndef FILEHANDLING_H
#define FILEHANDLING_H

#include "chuyenbay.h"
#include "hanhkhach.h"
#include "maybay.h"
#include <string>
#include <cstdio>

namespace File_Handling
{
    using namespace std;

// template <class List, class Child>
    void read_bin(string fileName, ListMayBay &list)
    {
        std::ifstream file(fileName, std::ios::binary);
        if (file.is_open())
        {
            MayBay *temp = nullptr;
            while (!file.eof())
            {
                temp = new MayBay();               // cấp phát bộ nhớ động cho node
                file.read(reinterpret_cast<char *>(temp), sizeof(*temp));
                if (file.gcount() != sizeof(*temp))
                {
                    delete temp;
                    break;
                }
                list.add_from_file_data(temp);
                
            }
            file.close();
        }
        else
        {
            std::cout << "Khong the mo file.\n";
        }
    }
    void read_bin(string fileName, ListChuyenBay &list, ListMayBay& list_mb)
    {
        std::ifstream file(fileName, std::ios::binary);
        if (file.is_open())
        {
            ChuyenBay *temp = nullptr;
            int so_luong = 0;
            if(!(file.read(reinterpret_cast<char*>(&so_luong), sizeof(so_luong)))){
                so_luong = 0;
            }
            for(int i=0; i<so_luong; i++){
                temp = new ChuyenBay();        // cấp phát bộ nhớ động cho node
                temp->deserialize(file,list_mb);
                list.add_from_file_data(temp);
            }
            file.close();
        }
        else
        {
            std::cout << "Khong the mo file.\n";
        }
    }
     void read_bin(string fileName, TreeHanhKhach &list)
    {
        std::ifstream file(fileName, std::ios::binary);
        if (file.is_open())
        {
            HanhKhach *temp = nullptr;
            int so_luong = 0;
            if(!(file.read(reinterpret_cast<char*>(&so_luong), sizeof(so_luong)))){
                so_luong = 0;
            }
            for(int i=0; i<so_luong; i++){
                temp = new HanhKhach();        // cấp phát bộ nhớ động cho node
                temp->deserialize(file);
                list.add_from_file_data(temp);   
            }
            file.close();
        }
        else
        {
            std::cout << "Khong the mo file.\n";
        }
    }
    void write_bin(const string& fileName, ListMayBay &list)
    {
        std::ofstream file(fileName, std::ios::binary);
        if (file.is_open())
        {
            for (int i = 0; i < list.get_so_luong(); i++)
            {
                MayBay* maybay = list.get_at(i);
                file.write(reinterpret_cast<char*>(maybay), sizeof(*maybay));
            }
            file.close();
        }
        else
        {
            std::cout << "Khong the mo file.\n";
        }
    }
    void write_bin(const string& fileName, ListChuyenBay &list)
    {
        std::ofstream file(fileName, std::ios::binary);
        if (file.is_open())
        {   
            int so_luong = list.get_so_luong_cb();
            file.write(reinterpret_cast<const char *>(&so_luong), sizeof(so_luong));
            for (ChuyenBay* current = list.get_head(); current != nullptr; current = current->get_next()) {
                current->serialize(file);
            }
            file.close();
        }
        else
        {
            std::cout << "Khong the mo file.\n";
        }
    }

    void write_tree(std::ofstream& file, HanhKhach* node){
         if (node == nullptr) {
                return;
            }
            node->serialize(file);
            write_tree(file,node->getLeft());
            write_tree(file,node->getRight());
    }
    void write_bin(const string& fileName, TreeHanhKhach &list)
    {
        std::ofstream file(fileName, std::ios::binary);
        if (file.is_open())
        {
            int so_luong = list.so_hanh_khach();
            file.write(reinterpret_cast<const char *>(&so_luong), sizeof(so_luong));
            write_tree(file,list.getRoot());
            file.close();
        }
        else
        {
            std::cout << "Khong the mo file.\n";
        }
    }
}

/*
- đọc dữ liệu từng file
- lưu dữ liệu vào từng file
*/

#endif
