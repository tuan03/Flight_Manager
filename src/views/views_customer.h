#ifndef VIEWS_CUSTOMER_H
#define VIEWS_CUSTOMER_H
#include"../header.h"
#include"component.h"
class View_Customer
{
private:
    Global_Variable& global;

    Buffer table;

    Buffer data;

    int so_luong_data = 0; 
    int current_page;              // phân trang hiện tại
    int mouse_X, mouse_Y;          // vị trí chuột


    int route_plane_width[5]{100, 300, 250, 500, 350};
    string route_plane_name_cot[5]{"STT", "Họ", "Tên", "CMND", "Giới Tính"};

public:
    View_Customer(Global_Variable& gb); 

    void handleEvent(SDL_Event e, bool &is_home, int mouse_X, int mouse_Y)
    {
        this->mouse_X = mouse_X;
        this->mouse_Y = mouse_Y;
            is_home = true;
            switch (e.type)
            {
            case SDL_MOUSEBUTTONDOWN: // sự kiện nhấn vào các box
                                      // bắt sự kiện nhấn next và prev
                if (current_page > 1 && global.get_c_component().prev.is_in_box(mouse_X, mouse_Y))
                {
                    this->current_page -= 1;
                    this->re_render_data();
                }
                if (current_page < ((this->so_luong_data - 1) / 10) + 1 && global.get_c_component().next.is_in_box(mouse_X, mouse_Y))
                {
                    current_page += 1;
                    this->re_render_data();
                }
                break;
            }
        }
    void render()
    {

        table.render(); // render table
        data.render(); // render data

        this->global.get_c_component().render_next_prev(mouse_X,mouse_Y,current_page,so_luong_data,&(this->global.get_myscreen()));
    }

    ////////////////////////////////////////////////////////////
    void duyet(HanhKhach* p, int start, int end, int& stt, int& so_line_render) {
            if (p == nullptr) {
                return;
            }

            duyet(p->getLeft(),start,end,stt,so_line_render);

            if (stt >= start && stt <= end)
                {
                    this->render_line_data(stt, start, p);
                    so_line_render++;
                }
            stt++;

            duyet(p->getRight(),start,end,stt,so_line_render);
        }
    void getData() // đưa data vào bộ đệm
    {
        data.connect_render_clear();
        TreeHanhKhach* list_hk = &(this->global.get_qlcb().getListHK());
        int start = (this->current_page - 1) * 10;
        int end = start + 9; // 0 - 9 là 10
        int stt = 0;
        int so_line_render = 0;
        
        duyet(list_hk->getRoot(),start,end,stt,so_line_render);

        this->so_luong_data = stt;
        if (so_line_render == 0)
        {
            this->global.get_myscreen().render_Text("Trống !!!", {X_START_TABLE, Y_START_TABLE, WIDTH_TABLE, HEIGHT_TABLE}, {255, 0, 0}, true);
        }
        data.disconnect_render();
    }
    void re_render_data(){
        this->getData();
    }
    void follow_flag();
    void createTable(); // vẽ ra viền bảng
    void render_line_data(int stt, int start, HanhKhach *hk); // render 1 linedata Máy Bay
};
View_Customer::View_Customer(Global_Variable& gb) : global{gb}
    {
        current_page = 1;

        table.set(&(global.get_myscreen()), WIDTH_TABLE, HEIGHT_TABLE + 50);
        table.set_vitri(X_START_TABLE, Y_START_TABLE - 50);
        this->createTable();

        data.set(&(global.get_myscreen()), WIDTH_TABLE, HEIGHT_TABLE);
        data.set_vitri(X_START_TABLE, Y_START_TABLE);
        this->getData();
    }

void View_Customer::createTable() // vẽ ra viền bảng
{
    table.connect_render_clear();
    this->global.get_myscreen().render_table(5, route_plane_width, route_plane_name_cot);
    table.disconnect_render();
}

void View_Customer::render_line_data(int stt, int start, HanhKhach *hk) // render 1 linedata Máy Bay
{
    SDL_Rect rect;
    rect = {0, 0 + (stt - start) * 50, route_plane_width[0], 50};
    this->global.get_myscreen().render_Text(std::to_string((stt) + 1), rect, {0, 0, 0, 255}, true);

    rect.x += rect.w;
    rect.w = route_plane_width[1];
    this->global.get_myscreen().render_Text(hk->getHo(), rect, {0, 0, 0, 255}, true);

    rect.x += rect.w;
    rect.w = route_plane_width[2];
    this->global.get_myscreen().render_Text(hk->getTen(), rect, {0, 0, 0, 255}, true);

    rect.x += rect.w;
    rect.w = route_plane_width[3];
    this->global.get_myscreen().render_Text(hk->getSoCMND(), rect, {0, 0, 0, 255}, true);

    rect.x += rect.w;
    rect.w = route_plane_width[4];
    this->global.get_myscreen().render_Text(std::to_string(hk->getPhai()), rect, {0, 0, 0, 255}, true);
}


#endif