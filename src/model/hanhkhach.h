#ifndef HANHKHACH_H
#define HANHKHACH_H

#include "error.h"


class HanhKhach{
    private:
    char so_cmnd[MAX_LENGTH_SO_CMND+1]={};
    char ho[MAX_LENGTH_HO+1]={};
    char ten[MAX_LENGTH_TEN+1]={}; 
    char phai[MAX_LENGTH_PHAI+1]={};
    HanhKhach *left = nullptr, *right = nullptr;
    void set(char * so_cmnd, char * ho, char * ten, char * phai){
        strcpy(this->so_cmnd,so_cmnd);
        strcpy(this->ho,ho);
        strcpy(this->ten,ten);
        strcpy(this->phai,phai);
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
    const char* getPhai() const {
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
    void setPhai(const char* p) {
        strcpy(phai, p);
    }
    void setLeft(HanhKhach* l) {
        left = l;
    }
    void setRight(HanhKhach* r) {
        right = r;
    }


    HanhKhach(){}
    HanhKhach(char * so_cmnd, char * ho, char * ten, char * phai){
        this->set(so_cmnd,ho,ten,phai);
    }
    int compare_cmnd(char* cmnd){
        return strcmp(this->so_cmnd,cmnd);
    }

    friend std::istringstream& operator>>(std::istringstream& is, HanhKhach& mb);
	friend std::ostream& operator<<(std::ostream& os, const HanhKhach& mb);
};
std::istringstream& operator>>(std::istringstream& is, HanhKhach& mb){ //0123456789|Nguyen Van|A|Nam
    is.getline(mb.so_cmnd,MAX_LENGTH_SO_CMND+1,'|');
    is.getline(mb.ho,MAX_LENGTH_HO+1,'|');
    is.getline(mb.ten,MAX_LENGTH_TEN+1,'|');
    is.getline(mb.phai,MAX_LENGTH_PHAI+1);
    return is;
}
std::ostream& operator<<(std::ostream& os, const HanhKhach& mb) {
    os<<mb.so_cmnd<<'|'<<mb.ho<<'|'<<mb.ten<<'|'<<mb.phai;
    return os;
}


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
        void inorderTraversal(HanhKhach* p) {
            if (p == nullptr) {
                return;
            }

            inorderTraversal(p->getLeft());
            std::cout << *p << "\n"; // In ra thông tin của HanhKhach
            inorderTraversal(p->getRight());
        }
        std::ofstream& in_data(std::ofstream& os, HanhKhach* p) const {
            if (p == nullptr) {
                return os;
            }
            os<<*p<<'\n';
            in_data(os,p->getLeft());
            in_data(os,p->getRight());
            return os;
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
        void insert(HanhKhach* new_node) {
            root = insertNode(root, new_node);
        }
        HanhKhach* search(const char* cmnd) const {
            return searchNode(root, cmnd);
        }
        void printAll() {
                inorderTraversal(root);
        }
        void print_data(std::ofstream& os) const{
                in_data(os,root);
        }
        int so_hanh_khach() {
            return countNodes(this->root);
        }
        friend std::ofstream& operator<<(std::ofstream& os, const TreeHanhKhach& mb);
};
std::ofstream& operator<<(std::ofstream& os, const TreeHanhKhach& mb){
    mb.print_data(os);
    return os;
}

//lưu ý, viết thêm code về lưu và load data sao cho nó tự cân bằng, làm sau ... :3
#endif
