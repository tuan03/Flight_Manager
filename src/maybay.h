#ifndef MAYBAY_H
#define MAYBAY_H
#include "error.h"

class ListMayBay;
class MayBay{
    private:
		char so_hieu_mb[MAX_LENGTH_SO_HIEU_MB+1];
		char loai_mb[MAX_LENGTH_LOAI_MAY_BAY+1];
		int so_day;
		int so_dong;

	public:
	MayBay(){

	}
	MayBay(char* sh, char* loai, int day, int dong){	this->set(sh,loai,day,dong);	}

	void set(char* sh, char* loai, int day, int dong){
        strcpy(this->so_hieu_mb, sh);
        strcpy(this->loai_mb, loai);
        this->so_day = day;
        this->so_dong = dong;
    }
	char* get_sohieu(){ return so_hieu_mb;	}
	char* get_loai(){ return loai_mb;	}
	int get_socho(){ return so_day*so_dong;	}

};
class ListMayBay{	
    private:
		MayBay* data[MAX_MAYBAY];
		int so_luong = 0;
	public:
		~ListMayBay(){
			for (int i = 0; i < so_luong; i++) {
				delete data[i];
			}
		}
		bool isEmpty(){	
			return this->so_luong==0;
		}
		bool isFull(){
			return this->so_luong >= MAX_MAYBAY;
		}
		bool push(char* sh, char* loai, int day, int dong){
			if(isFull() && this->timMayBay(sh) != -1){
				return false;
			}
			else{
				data[so_luong] = new MayBay(sh,loai,day,dong);
				so_luong++;
				return true;
			}
		}
		void xoaMayBay(char* soHieuMB){
    		int index = timMayBay(soHieuMB);
    		if (index != -1) {
			delete data[index];
			for (int i = index; i < so_luong - 1; i++) {
				data[i] = data[i + 1];
			}
			so_luong--;
    		}
		}
		int timMayBay(char* so_hieu_mb){
			for(int i = 0; i < so_luong; i++){
				if(strcmp(data[i]->get_sohieu(), so_hieu_mb) == 0){
					return i;
				}
			}
			return -1; // Trả về -1 nếu không tìm thấy
		}
		bool hieuChinhMayBay(char* sh_maybay, char* sh, char* loai, int day, int dong){
			int index = timMayBay(sh_maybay);
			if(index != -1){
				data[index]->set(sh, loai, day, dong);
				return true;
			}
			return false;
		}

};


#endif