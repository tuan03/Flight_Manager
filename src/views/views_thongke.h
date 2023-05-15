#ifndef VIEWS_THONGKE_H
#define VIEWS_THONGKE_H
#include "../header.h"
#include "component.h"
class View_Thongke
{
private:
    Global_Variable &global;
    Buffer table;
    int so_luong_data = 0;
    int current_page; // phân trang hiện tại
    int route_plane_width[3]{500, 500, 500};
    string route_plane_name_cot[3]{"STT", "Số Hiệu Máy Bay", "Số Lần Thực Hiện Chuyến Bay"};

    int mouse_X = 0, mouse_Y = 0;

public:
    View_Thongke(Global_Variable &gb) : global{gb}
    {
        current_page = 1;

        table.set(&(global.get_myscreen()), WIDTH_TABLE, HEIGHT_TABLE + 50);
        table.set_vitri(X_START_TABLE, Y_START_TABLE - 50);
        this->createTable();
    }

    void handleEvent(SDL_Event e, bool &is_home, int mouse_X, int mouse_Y)
    {
        is_home = true;
        this->mouse_X = mouse_X;
        this->mouse_Y = mouse_Y;
        switch (e.type)
        {
        case SDL_MOUSEBUTTONDOWN:
            if (current_page > 1 && global.get_c_component().prev.is_in_box(mouse_X, mouse_Y))
            {
                this->current_page -= 1;
            }
            if (current_page < ((this->so_luong_data - 1) / 10) + 1 && global.get_c_component().next.is_in_box(mouse_X, mouse_Y))
            {
                current_page += 1;
            }
            break;
        }
    }
    void render()
    {
        SDL_Rect rt;
        this->global.get_myscreen().render_Text("Thống Kê Số Lượt Thực Hiện Chuyến Bay", {X_START_BODY, Y_START_BODY, W_BODY, 100}, {0, 0, 0}, true, &rt);
        this->global.get_myscreen().render_cot({rt.x, rt.y + rt.h, rt.w, 2});
        table.render(); // render table
        render_Data();
        this->global.get_c_component().render_next_prev(mouse_X, mouse_Y, current_page, so_luong_data, &(this->global.get_myscreen()));
    }

    ////////////////////////////////////////////////////////////
    void render_Data() // đưa data vào bộ đệm
    {
        ListMayBay *list_mb = &(this->global.get_qlcb().getListMB());
        int so_may_bay = 0;
        int sorted[MAX_MAYBAY]{0};
        this->global.get_qlcb().rank_slthcb(sorted, so_may_bay);
        MayBay *mb = nullptr;
        int start = (current_page - 1) * 10;
        int end = start + 9 ; // 0 - 9
        for (int i = start ; i < so_may_bay; i++)
        {
            mb = list_mb->get_at(sorted[i]);
            if (i <= end)
            {
                this->render_line_data(X_START_TABLE, Y_START_TABLE, i, start, mb);
            } else {
                break;
            }
        }
        this->so_luong_data = so_may_bay;
    }
    void createTable() // vẽ ra viền bảng
    {
        table.connect_render_clear();
        this->global.get_myscreen().render_table(3, route_plane_width, route_plane_name_cot);
        table.disconnect_render();
    }

    void render_line_data(int x, int y, int stt, int start, MayBay *mb) // render 1 linedata Máy Bay
    {
        SDL_Rect rect;
        rect = {x, y + (stt - start) * 50, route_plane_width[0], 50};
        this->global.get_myscreen().render_Text(std::to_string((stt) + 1), rect, {0, 0, 0, 255}, true);

        rect.x += rect.w;
        rect.w = route_plane_width[1];
        this->global.get_myscreen().render_Text(mb->getSoHieuMB(), rect, {0, 0, 0, 255}, true);

        rect.x += rect.w;
        rect.w = route_plane_width[2];
        this->global.get_myscreen().render_Text(std::to_string(mb->get_so_lan_bay()), rect, {0, 0, 0, 255}, true);
    }
};
#endif
