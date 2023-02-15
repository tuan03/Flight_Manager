#include"Global.h"

class HanhKhach{
    public:
    char so_cmnd[MAX_LENGTH_SO_CMND+1];
    char ho[MAX_LENGTH_HO+1];
    char ten[MAX_LENGTH_TEN+1]; 
    char phai[MAX_LENGTH_PHAI+1];
};

struct NodeHanhKhach{
    public:
	HanhKhach data;
	NodeHanhKhach *left = NULL;
	NodeHanhKhach *right= NULL;
};