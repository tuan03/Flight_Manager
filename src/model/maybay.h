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
	void set(char* sh, char* loai, int day, int dong){
        strcpy(this->so_hieu_mb, sh);
        strcpy(this->loai_mb, loai);
        this->so_day = day;
        this->so_dong = dong;
    }
	public:
	//getter
		const char* getSoHieuMB() const {
            return so_hieu_mb;
        }
        const char* getLoaiMB() const {
            return loai_mb;
        }
 		int getSoDay() const {
            return so_day;
        }
		int getSoDong() const {
            return so_dong;
        }
	//setter
        void setSoHieuMB(const char* so_hieu) {
            strncpy(so_hieu_mb, so_hieu, MAX_LENGTH_SO_HIEU_MB);
            so_hieu_mb[MAX_LENGTH_SO_HIEU_MB] = '\0';
        }
        void setLoaiMB(const char* loai) {
            strncpy(loai_mb, loai, MAX_LENGTH_LOAI_MAY_BAY);
            loai_mb[MAX_LENGTH_LOAI_MAY_BAY] = '\0';
        }
        void setSoDay(int day) {
            so_day = day;
        }
        void setSoDong(int dong) {
            so_dong = dong;
        }

	//
	MayBay(){

	}
    MayBay(const MayBay& mb) { // Khởi tạo sao chép nông
            strcpy(so_hieu_mb, mb.so_hieu_mb);
            strcpy(loai_mb, mb.loai_mb);
            so_day = mb.so_day;
            so_dong = mb.so_dong;
    }
    MayBay(const std::string& so_hieu_mb, const std::string& loai_mb, int so_day, int so_dong) {
        strncpy(this->so_hieu_mb, so_hieu_mb.c_str(), MAX_LENGTH_SO_HIEU_MB);
        strncpy(this->loai_mb, loai_mb.c_str(), MAX_LENGTH_LOAI_MAY_BAY);
        this->so_day = so_day;
        this->so_dong = so_dong;
    }
	MayBay(char* sh, char* loai, int day, int dong){
		this->set(sh,loai,day,dong);
	}
		friend std::istringstream& operator>>(std::istringstream& is, MayBay& mb);
		friend std::ostream& operator<<(std::ostream& os, const MayBay& mb) ;
};
std::istringstream& operator>>(std::istringstream& is, MayBay& mb) {
    is.getline(mb.so_hieu_mb,MAX_LENGTH_SO_HIEU_MB+1,'|');
    is.getline(mb.loai_mb,MAX_LENGTH_LOAI_MAY_BAY+1,'|');
    is>>mb.so_day;
    is.ignore(1);
    is>>mb.so_dong;
    return is;
}
std::ostream& operator<<(std::ostream& os, const MayBay& mb) {
    os << mb.so_hieu_mb << "|" << mb.loai_mb << "|" << mb.so_day << "|" << mb.so_dong;
    return os;
}
class ListMayBay{	
    private:
		MayBay* data[MAX_MAYBAY];
		int so_luong = 0;
	public:
		~ListMayBay(){
			for (int i = 0; i < so_luong; i++) {
				delete data[i];
			}
			so_luong = 0;
		}
		MayBay* get_at(int index) const {
			return this->data[index];
		}
		int get_so_luong(){
			return this->so_luong;
		}
		bool isEmpty(){	
			return this->so_luong==0;
		}
		bool isFull(){
			return this->so_luong >= MAX_MAYBAY;
		}
		MayBay* push_empty(){
			MayBay* mb = new MayBay();
			data[so_luong] = mb;
			so_luong++;
			return mb;
		}
		bool push(char* sh, char* loai, int day, int dong){ // cần return đầy + đã tồn tại
			if(isFull() && this->timMayBay(sh) != -1){
				return false;
			}
			else{
				data[so_luong] = new MayBay(sh,loai,day,dong);
				so_luong++;
				return true;
			}
		}
		void print(){
            for(int i = 0; i < so_luong; i++){
				cout<<*data[i]<<'\n';
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
				if(strcmp(data[i]->getSoHieuMB(), so_hieu_mb) == 0){
					return i;
				}
			}
			return -1; // Trả về -1 nếu không tìm thấy
		}
		MayBay* find(char* so_hieu_mb){
			for(int i = 0; i < so_luong; i++){
				if(strcmp(data[i]->getSoHieuMB(), so_hieu_mb) == 0){
					return data[i];
				}
			}
			return nullptr; // Trả về -1 nếu không tìm thấy
		}
		// bool hieuChinhMayBay(char* sh_maybay, char* sh, char* loai, int day, int dong){
		// 	int index = timMayBay(sh_maybay);
		// 	if(index != -1){
		// 		data[index]->set(sh, loai, day, dong);
		// 		return true;
		// 	}
		// 	return false;
		// }

};

#endif