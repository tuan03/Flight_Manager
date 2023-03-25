#pragma once
#include"lib_render.h"
class Component{
    private:
        int z_index = 1;
        ListBox listbox;
    public:
    Component(){
    }
    void set_z_index(int value){
        this->z_index = value;
    }
    int get_z_index(){
        return z_index;
    }
    ~Component(){

    }
};
enum Name_Component{
    MENU,
    BODY
};


