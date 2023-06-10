#ifndef MAYBAY_H
#define MAYBAY_H
#include "error.h"

class ListMayBay;
class MayBay
{
private:
	char so_hieu_mb[MAX_LENGTH_SO_HIEU_MB + 1];
	char loai_mb[MAX_LENGTH_LOAI_MAY_BAY + 1];
	int so_day;
	int so_dong;
	int so_lan_bay = 0;

	void set(const char *sh, const char *loai, int day, int dong)
	{
		strcpy(this->so_hieu_mb, sh);
		strcpy(this->loai_mb, loai);
		this->so_day = day;
		this->so_dong = dong;
	}
	void setSoHieuMB(const char *so_hieu)
	{
		strncpy(so_hieu_mb, so_hieu, MAX_LENGTH_SO_HIEU_MB);
		so_hieu_mb[MAX_LENGTH_SO_HIEU_MB] = '\0';
	}
	void setLoaiMB(const char *loai)
	{
		strncpy(loai_mb, loai, MAX_LENGTH_LOAI_MAY_BAY);
		loai_mb[MAX_LENGTH_LOAI_MAY_BAY] = '\0';
	}
	void setSoDay(int day)
	{
		so_day = day;
	}
	void setSoDong(int dong)
	{
		so_dong = dong;
	}

public:
	void tang_so_lan_bay()
	{
		this->so_lan_bay++;
	}
	// getter
	const char *getSoHieuMB() const { return so_hieu_mb; }
	const char *getLoaiMB() const { return loai_mb; }
	int getSoDay() const { return so_day; }
	int getSoDong() const { return so_dong; }
	int getSoCho() { return so_day * so_dong; }
	int get_so_lan_bay(){ return this->so_lan_bay; }

	// edit

	Status edit(const char *loai_mb, int day, int dong)
	{
		if (day * dong < 20)
			return Status("Số Chỗ Ngồi Phải Lớn Hơn Hoặc Bằng 20");
		if (day < 1 || day > 26)
			return Status("Số Dãy Không Hợp Lệ (1-26)");
		if (dong < 1 || dong > 99)
			return Status("Số Dòng Không Hợp Lệ (1-99)");
		this->setLoaiMB(loai_mb);
		this->setSoDay(day);
		this->setSoDong(dong);
		return Status("Sửa Máy Bay Thành Công !", Status_Name::SUCCESS);
	}

	MayBay(){}
	MayBay(const char *sh, const char *loai, int day, int dong)
	{
		this->set(sh, loai, day, dong);
	}
};

class ListMayBay
{
private:
	MayBay *data[MAX_MAYBAY];
	int so_luong = 0;

	void add(MayBay *mb)
	{
		data[so_luong] = mb;
		so_luong++;
	}

public:
	~ListMayBay()
	{
		for (int i = 0; i < so_luong; i++)
		{
			delete data[i];
		}
	}
	MayBay *get_at(int index) const
	{
		if (index == -1 || index > this->so_luong)
			return nullptr;
		return this->data[index];
	}
	int get_so_luong() { return this->so_luong; }
	bool isEmpty() { return this->so_luong == 0; }
	bool isFull() { return this->so_luong >= MAX_MAYBAY; }
	Status add(const char *so_hieu_mb, const char *loai, int day, int dong)
	{
		if (this->isFull())
			return Status("Danh Sách Máy Bay Đã Đầy");
		if (this->find_mamb(so_hieu_mb) != -1)
			return Status("Số Hiệu Máy Bay Đã Tồn Tại");
		if (day * dong < 20)
			return Status("Số Chỗ Ngồi Phải Lớn Hơn Hoặc Bằng 20");
		if (day < 1 || day > 26)
			return Status("Số Dãy Không Hợp Lệ (1-26)");
		if (dong < 1 || dong > 99)
			return Status("Số Dòng Không Hợp Lệ (1-99)");

		data[so_luong++] = new MayBay(so_hieu_mb, loai, day, dong);
		return Status("Thêm Máy Bay Thành Công !", Status_Name::SUCCESS);
	}

	void del(int index)
	{
		if (index >= 0 && index < so_luong)
		{
			delete data[index];
			for (int i = index; i < so_luong - 1; i++)
			{
				data[i] = data[i + 1];
			}
			so_luong--;
		}
	}
	// find chuyen bay
	int find_mamb(const char *so_hieu_mb)
	{
		for (int i = 0; i < so_luong; i++)
		{
			if (strcmp(data[i]->getSoHieuMB(), so_hieu_mb) == 0)
			{
				return i;
			}
		}
		return -1; // Trả về false nếu không tìm thấy
	}
	MayBay *find_mamb_ct(const char *so_hieu_mb)
	{
		return get_at(find_mamb(so_hieu_mb));
	}

	void read_bin(string fileName)
	{
		std::ifstream file(fileName, std::ios::binary);
		if (file.is_open())
		{
			MayBay *temp = nullptr;
			while (!file.eof())
			{
				temp = new MayBay(); // cấp phát bộ nhớ động cho node
				file.read(reinterpret_cast<char *>(temp), sizeof(*temp));
				if (file.gcount() != sizeof(*temp))
				{
					delete temp;
					break;
				}
				this->add(temp);
			}
			file.close();
		}
		else
		{
			std::cout << "Khong the mo file " + fileName + ".\n";
		}
	}
	void write_bin(string fileName)
	{
		std::ofstream file(fileName, std::ios::binary);
		if (file.is_open())
		{
			for (int i = 0; i < this->so_luong; i++)
			{
				MayBay *maybay = this->get_at(i);
				file.write(reinterpret_cast<const char *>(maybay), sizeof(*maybay));
			}
			file.close();
		}
		else
		{
			std::cout << "Khong the mo file " + fileName + ".\n";
		}
	}
};
#endif