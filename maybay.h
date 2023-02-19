#include"Global.h"
#include<cstring>
#include<iostream>
#include<cmath>
#include<fstream>

#define MAX_SOCHO 300
#define MIN_SOCHO 20
using namespace std;
class MayBay{
    public:
    char so_hieu_mb[MAX_LENGTH_SO_HIEU_MB+1];
    char loai_mb[MAX_LENGTH_LOAI_MAY_BAY+1];
    int so_day;
	int so_dong;
	int socho;
};
class ListMayBay{
    public:
	MayBay *data[MAX_MAYBAY+1];
	int so_luong = 0;
};
bool isEmpty(ListMayBay &list){
return(list.so_luong==0 ? true: false);
}
bool isFull(ListMayBay &list){
	return(list.so_luong>= MAX_MAYBAY? true : false);
}
MayBay *newMaybay(MayBay & mb){
   MayBay *p= new MayBay;
   *p=mb ;
   return p;
}
void them_May_bay(ListMayBay& list, MayBay& mb, char* sh_temp, char* l_temp, int sc){
    if(isFull(list))
	return;
	list.data[list.so_luong]= newMaybay(mb);
	strcpy(list.data[list.so_luong]->so_hieu_mb,sh_temp);
	strcpy(list.data[list.so_luong]->loai_mb,l_temp) ;
	list.data[list.so_luong]->socho=sc;
	list.so_luong++;
}
int tim_May_bay(ListMayBay& list , char* sh_maybay){
     for(int i=0; i< list. so_luong; i++){
		if(strcmp(list.data[i]->so_hieu_mb,sh_maybay)==0)
		return i;
	 }
	 return -1;
}
void xoa_May_bay(ListMayBay& list , int index){
    delete list.data[index];
		for (int i = index; i < list.so_luong - 1; i++) {
		list.data[i] = list.data[i + 1];
	}
	list.so_luong--;
}
bool xau_trung(char a[],char b[]){
  int i=0;
  while(a[i]!='\0' || b[i]!='\0'){
    if(a[i]!=b[i]){
      return false;
      
     // break;
    }
    i++;
  }
  return true;
}
bool ktrMB(ListMayBay &list, char sh[], bool them, int chiso){
	int so_lan=0;
	for(int i = 0; i<list.so_luong; i++){
		if(xau_trung(list.data[i]->so_hieu_mb,sh)) so_lan++;
		//cout<<"trung : "<<i<<endl;
	}
	//cout<<"so lan :"<<so_lan<<endl;
	if(them) return ((so_lan==0) ? true : false);
	else{
		if(xau_trung(list.data[chiso]->so_hieu_mb,sh)) so_lan--;
	 	return ((so_lan==0) ? true : false);
	}
}
bool ktsocho(int sc) {
	return (sc <= MAX_SOCHO && sc >= MIN_SOCHO);
}
void writeFilePlane(ListMayBay& list) {

	ofstream out("PlaneData.txt", ios::binary);

	if (out.fail()) {
		printf("Cannot open file plane data\n");
		return;
	}

	for (int i = 0; i < list.so_luong; i++) {
		out.write(reinterpret_cast<char*>(list.data[i]), sizeof(MayBay));

	}

	out.close();


}

void readFilePlane(ListMayBay& list) {
	ifstream inp("PlaneData.txt", ios::binary);

	if (inp.fail()) {
		printf("Cannot open file plane data\n");
		return;
	}

       MayBay mb;
	inp.read(reinterpret_cast<char*>(&mb), sizeof(MayBay));
	inp.close();

}
void xoadsMaybay(ListMayBay &list) {
	for (int i = 0; i < list.so_luong; i++)
		delete list.data[i];

}
