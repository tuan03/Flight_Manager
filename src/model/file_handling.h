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
    void read_bin(string fileName, ListChuyenBay &list)
    {
        std::ifstream file(fileName, std::ios::binary);
        if (file.is_open())
        {
            ChuyenBay *temp = nullptr;
            while (!file.eof())
            {
                temp = new ChuyenBay();               // cấp phát bộ nhớ động cho node
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
     void read_bin(string fileName, TreeHanhKhach &list)
    {
        std::ifstream file(fileName, std::ios::binary);
        if (file.is_open())
        {
            HanhKhach *temp = nullptr;
            while (!file.eof())
            {
                temp = new HanhKhach();               // cấp phát bộ nhớ động cho node
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

            for (ChuyenBay* current = list.head; current != nullptr; current = current->get_next()) {
                file.write(reinterpret_cast<char*>(current), sizeof(*current));
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
            file.write(reinterpret_cast<char*>(node), sizeof(*node));
            write_tree(file,node->getLeft());
            write_tree(file,node->getRight());
    }
    void write_bin(const string& fileName, TreeHanhKhach &list)
    {
        std::ofstream file(fileName, std::ios::binary);
        if (file.is_open())
        {
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
