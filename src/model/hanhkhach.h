#ifndef HANHKHACH_H
#define HANHKHACH_H

#include "error.h"


class HanhKhach{
    private:
    char so_cmnd[MAX_LENGTH_SO_CMND+1]={};
    char ho[MAX_LENGTH_HO+1]={};
    char ten[MAX_LENGTH_TEN+1]={}; 
    bool phai; // true : nam, false : nữ
    HanhKhach *left = nullptr, *right = nullptr;
    void set(const char * so_cmnd,const char * ho,const char * ten,const bool phai){
        strcpy(this->so_cmnd,so_cmnd);
        strcpy(this->ho,ho);
        strcpy(this->ten,ten);
        this->phai = phai;
    }
    public:
    //getter
    const char* getSoCMND() const {
        return so_cmnd;
    }
    const char* getHo() const {
        return ho;
    }
    const char* getTen() const {
        return ten;
    }
    bool getPhai() const {
        return phai;
    }
    HanhKhach* getLeft() const {
        return left;
    }
    HanhKhach* getRight() const {
        return right;
    }
    // Setters
    void setSoCMND(const char* cmnd) {
        strcpy(so_cmnd, cmnd);
    }
    void setHo(const char* h) {
        strcpy(ho, h);
    }
    void setTen(const char* t) {
        strcpy(ten, t);
    }
    void setPhai(bool p) {
        this->phai = p;
    }
    void setLeft(HanhKhach* l) {
        left = l;
    }
    void setRight(HanhKhach* r) {
        right = r;
    }


    HanhKhach(){}
    HanhKhach(const char * so_cmnd,const char * ho,const char * ten, bool phai){
        this->set(so_cmnd,ho,ten,phai);
    }
    int compare_cmnd(const char* cmnd){
        return strcmp(this->so_cmnd,cmnd);
    }

     void serialize(std::ofstream &os)
    {
        os.write(so_cmnd, sizeof(so_cmnd));
        os.write(ho, sizeof(ho));
        os.write(ten, sizeof(ten));
        os.write(reinterpret_cast<const char *>(&phai), sizeof(phai));
    }

    // chuyển đổi chuỗi byte thành đối tượng
    void deserialize(std::ifstream &is)
    {
        is.read(so_cmnd, sizeof(so_cmnd));
        is.read(ho, sizeof(ho));
        is.read(ten, sizeof(ten));
        is.read(reinterpret_cast<char *>(&phai), sizeof(phai));
    }
};



class TreeHanhKhach {
    private:
        HanhKhach* root;
        HanhKhach* insertNode(HanhKhach* node, HanhKhach* new_node) {
            if (node == nullptr) {
                node = new_node;
            }
            else if (strcmp(node->getSoCMND(), new_node->getSoCMND()) > 0) {
                node->setLeft(insertNode(node->getLeft(), new_node));
            }
            else {
                node->setRight(insertNode(node->getRight(), new_node));
            }
            return node;
        }
        HanhKhach* searchNode(HanhKhach* node, const char* cmnd) const {
            if (node == nullptr) {
                return nullptr;
            }
            if (strcmp(node->getSoCMND(), cmnd) == 0) {
                return node;
            }
            else if (strcmp(node->getSoCMND(), cmnd) > 0) {
                return searchNode(node->getLeft(), cmnd);
            }
            else {
                return searchNode(node->getRight(), cmnd);
            }
        }

        int countNodes(HanhKhach* root) {
            if (root == NULL) {
                return 0;
            }
            return 1 + countNodes(root->getLeft()) + countNodes(root->getRight());
        }
    public:
        HanhKhach* getRoot(){
            return this->root;
        }
        TreeHanhKhach() {
            root = nullptr;
        }
        
        void add_from_file_data(HanhKhach* new_node) {
            root = insertNode(root, new_node);
        }
        
        HanhKhach* search(const char* cmnd) const {
            return searchNode(root, cmnd);
        }
        int so_hanh_khach() {
            return countNodes(this->root);
        }
};

#endif
