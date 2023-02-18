#ifndef HANHKHACH_H
#define HANHKHACH_H

#include"Global.h"

class HanhKhach{
    public:
    char so_cmnd[MAX_LENGTH_SO_CMND+1]={};
    char ho[MAX_LENGTH_HO+1]={};
    char ten[MAX_LENGTH_TEN+1]={}; 
    char phai[MAX_LENGTH_PHAI+1]={};
    HanhKhach(){}
    HanhKhach(char * so_cmnd, char * ho, char * ten, char * phai){
        strcpy(this->so_cmnd,so_cmnd);
        strcpy(this->ho,ho);
        strcpy(this->ten,ten);
        strcpy(this->phai,phai);
    }
    friend ostream& operator<<(ostream& out,HanhKhach& hk);
    friend istream& operator>>(istream& in,HanhKhach& hk);
};
ostream& operator<<(ostream& out,HanhKhach& hk){
    out<<"Ho va ten: "<<hk.ho<<' '<<hk.ten<<endl;
    out<<"cmnd : "<<hk.so_cmnd<<endl;
    out<<"phai: "<<hk.phai<<endl;
    out<<"--------------"<<endl;
    return out;
}
istream& operator>>(istream& in,HanhKhach& hk){
    in.getline(hk.ho,MAX_LENGTH_HO); 
    in.getline(hk.ten,MAX_LENGTH_TEN); 
    in.getline(hk.so_cmnd,MAX_LENGTH_SO_CMND); 
    in.getline(hk.phai,MAX_LENGTH_PHAI);
    return in;
}
class NodeHanhKhach{
    public:
	HanhKhach* data;
	NodeHanhKhach *left, *right;

    NodeHanhKhach(HanhKhach * hanhkhach) {
    this->data = hanhkhach;
    this->left = this->right = NULL;
    }

    ~NodeHanhKhach() {
    delete data;
    data = NULL;
    delete left;
    left = NULL;
    delete right;
    right = NULL;
}
};




class BinaryTree {
    public:
        NodeHanhKhach* root;
        BinaryTree() {
            root = NULL;
        }
        ~BinaryTree() {
            delete root;
            root = NULL;
        }
        void insert(NodeHanhKhach ** point ,HanhKhach* hanhkhach) {
            if(*point == NULL){
                *point = new NodeHanhKhach(hanhkhach);
            }
            else{
                if(strcmp(hanhkhach->so_cmnd,(*point)->data->so_cmnd) <0){
                    insert(&(*point)->left,hanhkhach);
                } else{
                    insert(&(*point)->right,hanhkhach);
                }
            }
        }


        NodeHanhKhach * search_hanhkhach(NodeHanhKhach *root,char *CMND){
            NodeHanhKhach* nodeRun = root;
	        while(nodeRun != NULL && strcmp(CMND,nodeRun->data->so_cmnd) != 0){
		    if( strcmp(CMND,nodeRun->data->so_cmnd)  > 0)     
		        nodeRun = nodeRun->right;
		    else
		        nodeRun = nodeRun->left;
	        }
	        return nodeRun;
        }


};





class Ve {
    public:
    char so_ve[MAX_LENGTH_SO_VE+1];
    char so_cmnd[MAX_LENGTH_SO_CMND+1];
};

class ListVe{
    int so_luong = 0;
    Ve first;
    Ve* next = NULL;
};






void load_data () {
    HanhKhach temp;
	std::string filename = "data_hanh_khach.txt";
    std::ifstream istrm(filename, std::ios::in);
    if (!istrm.is_open())
        std::cout << "failed to open " << filename << '\n';
    else
    {   
        int k;
        istrm>>k;
        cout<<"So HK: "<<k<<endl;
        istrm.ignore();
        while (!istrm.eof())
        {
            istrm>>temp;
            cout<<temp;
        }
        
        
    }
}
int main(){
    load_data();
}








#endif