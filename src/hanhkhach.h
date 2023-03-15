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

    public:

    HanhKhach(){}
    HanhKhach(char * so_cmnd, char * ho, char * ten, char * phai){
        this->set(so_cmnd,ho,ten,phai);
    }
    void set(char * so_cmnd, char * ho, char * ten, char * phai){
        strcpy(this->so_cmnd,so_cmnd);
        strcpy(this->ho,ho);
        strcpy(this->ten,ten);
        strcpy(this->phai,phai);
    }
    int compare_cmnd(char* cmnd){
        return strcmp(this->so_cmnd,cmnd);
    }
    char* get_cmnd(){
        return so_cmnd;
    }
    HanhKhach**  get_left(){
        return &(this->left);
    }
    void set_left(HanhKhach* next){
        this->left = next;
    }
    HanhKhach**  get_right(){
        return &(this->right);
    }
    void set_right(HanhKhach* next){
        this->right = next;
    }
};




class TreeHanhKhach {
    private:
        HanhKhach* root;
    public:
        TreeHanhKhach() {
            root = nullptr;
        }
        bool add(char * so_cmnd, char * ho, char * ten, char * phai){
            if(search_hanhkhach(so_cmnd) != nullptr) return false;
            HanhKhach* newhk = new HanhKhach(so_cmnd,ho,ten,phai);
            insert(&root,newhk);
        }
        void insert( HanhKhach**  root, HanhKhach* hanhkhach) {
            if(*root == nullptr){
                *root = hanhkhach;
            }
            else{
                if(hanhkhach->compare_cmnd((*root)->get_cmnd()) == -1){
                    insert((*root)->get_left(),hanhkhach);
                } else{
                    insert((*root)->get_right(),hanhkhach);
                }
            }
        }


        HanhKhach * search_hanhkhach(char *CMND){
            HanhKhach* nodeRun = this->root;
	        while(nodeRun != nullptr && nodeRun->compare_cmnd(CMND) != 0){
		    if( nodeRun->compare_cmnd(CMND)  == -1)     
		        nodeRun = *(nodeRun->get_right());
		    else
		        nodeRun = *(nodeRun->get_left());
	        }
	        return nodeRun;
        }


};



#endif