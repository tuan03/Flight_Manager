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


		// 
		int so_lan_bay = 0;


		void set(const char* sh, const char* loai, int day, int dong){
			strcpy(this->so_hieu_mb, sh);
			strcpy(this->loai_mb, loai);
			this->so_day = day;
			this->so_dong = dong;
		}
	public:
	//getter
		const char* getSoHieuMB() const { return so_hieu_mb; }
        const char* getLoaiMB() const { return loai_mb; }
 		int getSoDay() const { return so_day; }
		int getSoDong() const { return so_dong; }
		int getSoCho() { return so_day*so_dong;}
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

	//edit

		Status edit(const char* loai_mb,int day,int dong){
			if(day*dong < 20 ) return Status("Số Chỗ Ngồi Phải Lớn Hơn Hoặc Bằng 20");
			if(day < 1 || day > 26 ) return Status("Số Dãy Không Hợp Lệ (1-26)");
			if(dong < 1 || dong > 99 ) return Status("Số Dòng Không Hợp Lệ (1-99)");
            this->setLoaiMB(loai_mb);
			this->setSoDay(day);
			this->setSoDong(dong);
			return Status("Sửa Máy Bay Thành Công !",Status_Name::SUCCESS);
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
	MayBay(const char* sh, const char* loai, int day, int dong){
		this->set(sh,loai,day,dong);
	}
		friend std::istringstream& operator>>(std::istringstream& is, MayBay& mb);
		friend std::ostream& operator<<(std::ostream& os, const MayBay& mb) ;
		friend std::ofstream& operator<<(std::ofstream& os, const MayBay& mb) ;
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
	std::ofstream& operator<<(std::ofstream& os, const MayBay& mb) {
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
		MayBay* get_at(int index) const { return this->data[index]; }
		int get_so_luong(){ return this->so_luong; }
		bool isEmpty(){	 return this->so_luong==0; }
		bool isFull(){ return this->so_luong >= MAX_MAYBAY; }
		void add_from_file_data(MayBay* mb){
			data[so_luong] = mb;
			so_luong++;
		}
		Status add(const char* so_hieu_mb,const char* loai, int day, int dong){
			if(this->isFull()) return Status("Danh Sách Máy Bay Đã Đầy");
			if(this->find_mamb(so_hieu_mb) != -1) return Status("Số Hiệu Máy Bay Đã Tồn Tại");
			if(day*dong < 20 ) return Status("Số Chỗ Ngồi Phải Lớn Hơn Hoặc Bằng 20");
			if(day < 1 || day > 26 ) return Status("Số Dãy Không Hợp Lệ (1-26)");
			if(dong < 1 || dong > 99 ) return Status("Số Dòng Không Hợp Lệ (1-99)");

			data[so_luong++] = new MayBay(so_hieu_mb,loai,day,dong);
			return Status("Thêm Máy Bay Thành Công !",Status_Name::SUCCESS);
		}


		


		void del(int index){
    		if (index >=0 && index < so_luong) {
			    delete data[index];
			    for (int i = index; i < so_luong - 1; i++) {
				data[i] = data[i + 1];
			       }
			    so_luong--;
			}
		}

		void print(){
            for(int i = 0; i < so_luong; i++){
				cout<<*data[i]<<'\n';
			}
        }
	
		
		//find chuyen bay
		int find_mamb(const char* so_hieu_mb){
			for(int i = 0; i < so_luong; i++){
				if(strcmp(data[i]->getSoHieuMB(), so_hieu_mb) == 0){
					return i;
				}
			}
			return -1; // Trả về false nếu không tìm thấy
		}
		MayBay* find_mamb_ct(const char* so_hieu_mb){
			for(int i = 0; i < so_luong; i++){
				if(strcmp(data[i]->getSoHieuMB(), so_hieu_mb) == 0){
					return data[i];
				}
			}
			return nullptr; // Trả về -1 nếu không tìm thấy
		}
		//end
		// bool hieuChinhMayBay(char* sh_maybay, char* sh, char* loai, int day, int dong){
		// 	int index = timMayBay(sh_maybay);
		// 	if(index != -1){
		// 		data[index]->set(sh, loai, day, dong);
		// 		return true;
		// 	}
		// 	return false;
		// }


   friend std::ofstream& operator<<(std::ofstream& os, const ListMayBay& list);
   friend std::ostream& operator<<(std::ostream& os, const ListMayBay& list);
};

std::ostream& operator<<(std::ostream& os, const ListMayBay& list) {
   for (int i = 0; i < list.so_luong; i++) {
        os << *(list.get_at(i)) << "\n";
   }
   return os;
}

std::ofstream& operator<<(std::ofstream& os, const ListMayBay& list) {
    for (int i=0 ; i < list.so_luong; i++) {
        os << *(list.get_at(i)) << "\n";
    }
    return os;
}
#endif