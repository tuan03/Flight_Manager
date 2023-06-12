#ifndef VIEWS_FLIGHT_H
#define VIEWS_FLIGHT_H

#include "../header.h"
#include "component.h"
#include "views_ticket.h"

namespace Flight
{
    class Menu
    {
    private:
        Global_Variable *global = nullptr;

        SDL_Color nut_xoa = {255, 255, 255}; // màu rgb
        SDL_Color nut_sua = {255, 255, 255};
        SDL_Color nut_datve = {255, 255, 255};
        SDL_Color nut_xemhk = {255, 255, 255};
        SDL_Rect vt_nut_datve = {0, 0, 0, 0};
        SDL_Rect vt_nut_xemhk = {0, 0, 0, 0};
        SDL_Rect vt_nut_huy = {0, 0, 0, 0};
        SDL_Rect vt_nut_sua = {0, 0, 0, 0};
        ChuyenBay *current = nullptr;
        bool *flag_re_render_in_home = nullptr;

        Box *khung_menu = nullptr;
        MyScreen *myscreen = nullptr;

    public:
        void set(Global_Variable &global, bool *flag)
        {
            this->flag_re_render_in_home = flag;
            this->global = &global;

            khung_menu = &(global.get_c_component().khung_menu); // tuannnnn
            myscreen = &(global.get_myscreen());
        }

        void handleEvent(SDL_Event e, Position &state, int mouse_X, int mouse_Y)
        {
            nut_xoa = {255, 255, 255};
            nut_sua = {255, 255, 255};
            nut_datve = {255, 255, 255};
            nut_xemhk = {255, 255, 255};
            switch (e.type)
            {
            case SDL_MOUSEMOTION:
                if (MyFunc::check_click(mouse_X, mouse_Y, vt_nut_sua))
                {
                    nut_sua = {255, 219, 26};
                }
                else if (MyFunc::check_click(mouse_X, mouse_Y, vt_nut_huy))
                {
                    nut_xoa = {255, 219, 26};
                }
                else if (MyFunc::check_click(mouse_X, mouse_Y, vt_nut_datve))
                {
                    nut_datve = {255, 219, 26};
                }
                else if (MyFunc::check_click(mouse_X, mouse_Y, vt_nut_xemhk))
                {
                    nut_xemhk = {255, 219, 26};
                }
                break;
            case SDL_MOUSEBUTTONDOWN:                         // sự kiện nhấn vào các box
                if (!khung_menu->is_in_box(mouse_X, mouse_Y)) // bấm bên ngoài menu sẽ thoát
                {
                    state = Position::HOME;
                }
                if (this->current->get_trang_thai_cb() != 0 && this->current->get_trang_thai_cb() != 3)
                {
                    if (MyFunc::check_click(mouse_X, mouse_Y, vt_nut_datve))
                    {
                        state = Position::DATVE;
                    }
                    else if (MyFunc::check_click(mouse_X, mouse_Y, vt_nut_sua)) // nhấn vào Box edit
                    {                                                           //
                        state = Position::EDIT;                                 // chuyển sang trang edit
                    }
                    else if (MyFunc::check_click(mouse_X, mouse_Y, vt_nut_huy)) // nhấn vào Box xóa
                    {
                        // del_function
                        global->get_thong_bao().set_mess("Chỉ Hủy Khi Thật Cần Thiết.");
                        global->get_thong_bao().on(false);
                    }
                }
                if (MyFunc::check_click(mouse_X, mouse_Y, vt_nut_xemhk))
                {
                    state = Position::XEM_HK;
                }
                break;
            }
            if (global->get_thong_bao().get_value())
            {
                Status result;
                result = current->huy_chuyen_bay();
                global->get_thong_bao().set_mess(result.mess);
                global->get_thong_bao().on();
                if (result.get_status() == Status_Name::SUCCESS)
                {
                    *(this->flag_re_render_in_home) = true;
                    state = Position::HOME;
                }
                global->get_thong_bao().reset_value();
            }
        }

        void render_menu(ChuyenBay *cb, int vt)
        {
            this->current = cb;
            // render khung menu
            SDL_Rect rect = {700 - 150, Y_START_TABLE + vt * 50 - 330, 300, 400};
            khung_menu->set_rect(rect);
            khung_menu->render(myscreen->get_my_renderer());
            // end
            int width = 150;
            int height = 50;
            vt_nut_datve = MyFunc::center_Rect(width, height, {rect.x, rect.y + 50, rect.w, 50});
            vt_nut_xemhk = MyFunc::center_Rect(width, height, {rect.x, rect.y + 120, rect.w, 50});
            vt_nut_sua = MyFunc::center_Rect(width, height, {rect.x, rect.y + 190, rect.w, 50});
            vt_nut_huy = MyFunc::center_Rect(width, height, {rect.x, rect.y + 260, rect.w, 50});

            if (this->current->get_trang_thai_cb() != 0 && this->current->get_trang_thai_cb() != 3)
            {
                myscreen->render_cot(vt_nut_datve, nut_datve); // render nền
                myscreen->render_Text("Đặt Vé", vt_nut_datve, {0, 0, 0}, true);
                myscreen->render_cot(vt_nut_sua, nut_sua); // render nền
                myscreen->render_Text("Sửa Thông Tin", vt_nut_sua, {0, 0, 0}, true);
                myscreen->render_cot(vt_nut_huy, nut_xoa); // render nền
                myscreen->render_Text("Hủy Chuyến", vt_nut_huy, {0, 0, 0}, true);
            } else {
                string text = "Chuyến Bay Đã " + string(this->current->get_trang_thai_cb() == 0 ? "Hủy" : "Hoàn Thành");
                myscreen->render_Text(text ,{rect.x, rect.y + 190, rect.w, 50},{0,0,0},true);
            
            }

            myscreen->render_cot(vt_nut_xemhk, nut_xemhk); // render nền
            myscreen->render_Text("DS HK", vt_nut_xemhk, {0, 0, 0}, true);

            

            // tại nút edit và xóa có nền trong suốt cho nên màu nên sẽ phụ thuộc lớp ô vuông ở phía dưới nó, cụ thể là 2 ô vuông ở trên
        }
        ~Menu()
        {
        }
    };
    class Edit
    {
    private:
        Global_Variable *global = nullptr;

        SDL_Rect vi_tri_nut_x = {1250, 210, 50, 50};
        SDL_Rect vi_tri_nut_sua = {825, 530, 120, 60};
        SDL_Color nut_sua = {255, 255, 255};
        SDL_Color nut_x = {255, 255, 255};

        Input input_so_hieu_mb;
        Input input_san_bay_den;
        Input input_tgb_hour;
        Input input_tgb_minute;
        Input input_tgb_day;
        Input input_tgb_month;
        Input input_tgb_year;

        bool now = true; // flag để gán 1 lần cho tất cả

        SDL_Rect rect_input_time[5] = {{770, 400, 50, 50}, {840, 400, 50, 50}, {950, 400, 50, 50}, {1020, 400, 50, 50}, {1090, 400, 180, 50}};
        string name_field_time[4] = {":", "-", "/", "/"};
        SDL_Rect rect_field_time[4] = {{710, 400, 240, 50}, {800, 400, 240, 50}, {890, 400, 240, 50}, {960, 400, 240, 50}};

        string name_field[4] = {"Mã Chuyến Bay:", "Nơi Đến:", "Thời Gian Bay:", "Số Hiệu Máy Bay:"};
        SDL_Rect rect_field[4] = {{530, 280, 240, 50}, {530, 340, 240, 50}, {530, 400, 240, 50}, {530, 460, 240, 50}};
        SDL_Rect rect_input[4] = {{770, 280, 500, 50}, {770, 340, 500, 50}, {770, 400, 500, 50}, {770, 460, 500, 50}};
        int current_click_input = -1;

        bool da_lap_cb = false;

        ChuyenBay *target_chuyenbay = nullptr;

        bool *flag_re_render_in_home = nullptr;

        MyScreen *myscreen = nullptr;
        Box *khung_add_edit = nullptr;

    public:
        void
        set(Global_Variable &global, bool *flag)
        {
            this->global = &global;
            this->myscreen = &(global.get_myscreen());
            khung_add_edit = &(global.get_c_component().khung_add_edit);

            this->flag_re_render_in_home = flag;

            input_so_hieu_mb.set(&(global.get_myscreen()), MAX_LENGTH_SO_HIEU_MB, rect_input[3]);
            string note = "Tối đa " + std::to_string(MAX_LENGTH_SO_HIEU_MB) + " kí tự";
            input_so_hieu_mb.set_note(note);
            input_san_bay_den.set(&(global.get_myscreen()), MAX_LENGTH_SAN_BAY_DEN, rect_input[1]);
            note = "Tối đa " + std::to_string(MAX_LENGTH_SAN_BAY_DEN) + " kí tự";
            input_san_bay_den.set_note(note);
            input_tgb_day.set(&(global.get_myscreen()), 2, rect_input_time[2]);
            note = "dd";
            input_tgb_day.set_note(note);
            input_tgb_hour.set(&(global.get_myscreen()), 2, rect_input_time[0]);
            note = "hh";
            input_tgb_hour.set_note(note);
            input_tgb_minute.set(&(global.get_myscreen()), 2, rect_input_time[1]);
            note = "mm";
            input_tgb_minute.set_note(note);
            input_tgb_month.set(&(global.get_myscreen()), 2, rect_input_time[3]);
            note = "mm";
            input_tgb_month.set_note(note);
            input_tgb_year.set(&(global.get_myscreen()), 4, rect_input_time[4]);
            note = "yyyy";
            input_tgb_year.set_note(note);
        }

        void handleEvent(SDL_Event e, Position &state, int mouse_X, int mouse_Y)
        {
            nut_sua = {255, 255, 255};
            nut_x = {255, 255, 255};
            switch (e.type)
            {
            case SDL_MOUSEMOTION:
                if (MyFunc::check_click(mouse_X, mouse_Y, vi_tri_nut_x))
                {
                    nut_x = {255, 219, 26};
                }
                else if (MyFunc::check_click(mouse_X, mouse_Y, vi_tri_nut_sua))
                {
                    nut_sua = {255, 219, 26};
                }
                break;
            case SDL_MOUSEBUTTONDOWN: // sự kiện nhấn vào các box
                this->current_click_input = -1;
                for (int i = 0; i < 4; i++)
                {
                    if (MyFunc::check_click(mouse_X, mouse_Y, rect_input[i]))
                    {
                        this->current_click_input = i;
                        break;
                    }
                }
                if (MyFunc::check_click(mouse_X, mouse_Y, vi_tri_nut_x))
                {
                    state = Position::MENU;
                    this->now = true;
                    this->target_chuyenbay = nullptr;
                    nut_sua = {255, 255, 255};
                    nut_x = {255, 255, 255};
                }
                else if (MyFunc::check_click(mouse_X, mouse_Y, vi_tri_nut_sua)) // nhấn vào vút sửa
                {
                    // edit_function
                    Status result;
                    if (input_san_bay_den.is_empty() || input_so_hieu_mb.is_empty() || input_tgb_day.is_empty() || input_tgb_hour.is_empty() || input_tgb_minute.is_empty() || input_tgb_month.is_empty() || input_tgb_year.is_empty())
                    {
                        result = Status("Bạn Chưa Nhập Đủ Thông Tin");
                    }
                    else
                    {
                        result = this->global->get_qlcb().edit_chuyen_bay(target_chuyenbay, input_tgb_minute.get_num(), input_tgb_hour.get_num(), input_tgb_day.get_num(), input_tgb_month.get_num(), input_tgb_year.get_num(), input_san_bay_den.get_data().c_str(), input_so_hieu_mb.get_data().c_str());
                    }
                    global->get_thong_bao().set_mess(result.mess);
                    global->get_thong_bao().on();
                    if (result.get_status() == Status_Name::SUCCESS)
                    {
                        *(this->flag_re_render_in_home) = true;
                    }
                }
                break;
            }

            input_san_bay_den.handleInput_ID(e, mouse_X, mouse_Y);
            input_so_hieu_mb.handleInput_ID(e, mouse_X, mouse_Y);
            input_tgb_day.handleInput_Num(e, mouse_X, mouse_Y);
            input_tgb_hour.handleInput_Num(e, mouse_X, mouse_Y);
            input_tgb_minute.handleInput_Num(e, mouse_X, mouse_Y);
            input_tgb_month.handleInput_Num(e, mouse_X, mouse_Y);
            input_tgb_year.handleInput_Num(e, mouse_X, mouse_Y);
        }
        void set_target(ChuyenBay *cb)
        {
            if (this->now == true)
            {
                this->target_chuyenbay = cb;
                input_san_bay_den.set_data(cb->get_san_bay_den());
                input_so_hieu_mb.set_data(cb->get_so_hieu_mb());
                input_tgb_day.set_data(std::to_string(cb->get_thoi_gian_bay().get_day()));
                input_tgb_month.set_data(std::to_string(cb->get_thoi_gian_bay().get_month()));
                input_tgb_year.set_data(std::to_string(cb->get_thoi_gian_bay().get_year()));
                input_tgb_hour.set_data(std::to_string(cb->get_thoi_gian_bay().get_hour()));
                input_tgb_minute.set_data(std::to_string(cb->get_thoi_gian_bay().get_minute()));
                this->now = false;
            }
        }
        void render_menu(ChuyenBay *cb)
        {
            set_target(cb);
            myscreen->blur_background(150);
            khung_add_edit->render(myscreen->get_my_renderer());

            for (int i = 0; i < 4; i++)
            { // tg
                this->myscreen->render_Text(name_field_time[i], rect_field_time[i], {0, 0, 0}, true);
            }

            for (int i = 0; i < 4; i++)
            {
                myscreen->render_Text(name_field[i], rect_field[i], {0, 0, 0}, true);
            }
            myscreen->render_Text(cb->get_ma_so_cb(), rect_input[0], {0, 0, 0}, true);
            if (cb->get_listve().get_ve_da_ban() > 0)
            {
                myscreen->render_Text(cb->get_san_bay_den(), rect_input[1], {0, 0, 0}, true);
            }
            else
            {
                input_san_bay_den.render();
            }
            input_so_hieu_mb.render();
            input_tgb_day.render();
            input_tgb_month.render();
            input_tgb_year.render();
            input_tgb_hour.render();
            input_tgb_minute.render();

            myscreen->render_cot(vi_tri_nut_sua, nut_sua);
            myscreen->render_Text("OK", vi_tri_nut_sua, {0, 0, 0}, true);
            myscreen->render_cot(vi_tri_nut_x, nut_x);
            myscreen->render_Text("X", vi_tri_nut_x, {0, 0, 0}, true);
        }
    };

    class Add
    {
    private:
        Global_Variable *global = nullptr;

        SDL_Rect vi_tri_nut_x = {1250, 210, 50, 50};
        SDL_Rect vi_tri_nut_sua = {825, 530, 120, 60};
        SDL_Color nut_sua = {255, 255, 255};
        SDL_Color nut_x = {255, 255, 255};
        SDL_Rect vt_nut_auto{1090 + 130, 400, 50, 50};
        SDL_Color nut_auto = {255, 255, 255};

        int line_hover = -1;

        Input input_ma_cb;
        Input input_so_hieu_mb;
        Input input_san_bay_den;
        Input input_tgb_hour;
        Input input_tgb_minute;
        Input input_tgb_day;
        Input input_tgb_month;
        Input input_tgb_year;

        bool now = true; // flag để gán 1 lần cho tất cả

        SDL_Rect rect_input_time[5] = {{770, 400, 50, 50}, {840, 400, 50, 50}, {950, 400, 50, 50}, {1020, 400, 50, 50}, {1090, 400, 100, 50}};
        string name_field_time[4] = {":", "-", "/", "/"};
        SDL_Rect rect_field_time[4] = {{710, 400, 240, 50}, {800, 400, 240, 50}, {890, 400, 240, 50}, {960, 400, 240, 50}};

        string name_field[4] = {"Mã Chuyến Bay:", "Nơi Đến:", "Thời Gian Bay:", "Số Hiệu Máy Bay:"};
        SDL_Rect rect_field[4] = {{530, 280, 240, 50}, {530, 340, 240, 50}, {530, 400, 240, 50}, {530, 460, 240, 50}};
        SDL_Rect rect_input[4] = {{770, 280, 500, 50}, {770, 340, 500, 50}, {770, 400, 500, 50}, {770, 460, 500, 50}};
        int current_click_input = -1;

        bool da_lap_cb = false;

        ChuyenBay *target_chuyenbay = nullptr;

        bool *flag_re_render_in_home = nullptr;

        MyScreen *myscreen = nullptr;
        Box *khung_add_edit = nullptr;

        Buffer *buffer_list_mb = nullptr;
        Scroll scroll;
        SDL_Rect srcrect = {0, 0, 0, 0};
        SDL_Rect khung_list_mb = {0, 0, 0, 0};

        bool flag_list_mb = true;

    public:
        ~Add()
        {
            delete buffer_list_mb;
        }
        void set(Global_Variable &global, bool *flag)
        {
            this->global = &global;
            this->myscreen = &(global.get_myscreen());
            khung_add_edit = &(global.get_c_component().khung_add_edit);

            this->flag_re_render_in_home = flag;

            input_ma_cb.set(&(global.get_myscreen()), MAX_LENGTH_MA_CB, rect_input[0]);
            string note = "Tối đa " + std::to_string(MAX_LENGTH_MA_CB) + " kí tự";
            input_ma_cb.set_note(note);
            input_so_hieu_mb.set(&(global.get_myscreen()), MAX_LENGTH_SO_HIEU_MB, rect_input[3]);
            note = "Tối đa " + std::to_string(MAX_LENGTH_SO_HIEU_MB) + " kí tự";
            input_so_hieu_mb.set_note(note);
            input_san_bay_den.set(&(global.get_myscreen()), MAX_LENGTH_SAN_BAY_DEN, rect_input[1]);
            note = "Tối đa " + std::to_string(MAX_LENGTH_SAN_BAY_DEN) + " kí tự";
            input_san_bay_den.set_note(note);
            input_tgb_day.set(&(global.get_myscreen()), 2, rect_input_time[2]);
            note = "dd";
            input_tgb_day.set_note(note);
            input_tgb_hour.set(&(global.get_myscreen()), 2, rect_input_time[0]);
            note = "hh";
            input_tgb_hour.set_note(note);
            input_tgb_minute.set(&(global.get_myscreen()), 2, rect_input_time[1]);
            note = "mm";
            input_tgb_minute.set_note(note);
            input_tgb_month.set(&(global.get_myscreen()), 2, rect_input_time[3]);
            note = "mm";
            input_tgb_month.set_note(note);
            input_tgb_year.set(&(global.get_myscreen()), 4, rect_input_time[4]);
            note = "yyyy";
            input_tgb_year.set_note(note);

            khung_list_mb = {input_so_hieu_mb.get_rect().x + input_so_hieu_mb.get_rect().w + 10, input_so_hieu_mb.get_rect().y - 100, 500, 500};
        }
        void get_hover_mb(int x, int y)
        {
            line_hover = -1;
            if (MyFunc::check_click(x, y, khung_list_mb) && input_so_hieu_mb.get_is_click())
            {
                int vt_y = y - khung_list_mb.y + srcrect.y;
                if (vt_y < buffer_list_mb->get_rect().h)
                    line_hover = vt_y / 50;
            }
        }
        void set_click_mb()
        {
            if (line_hover != -1)
            {
                int stt = -1;
                int total = global->get_list_plane().get_so_luong();
                for (int i = 0; i < total; i++)
                {
                    if (Func_Global::check_prefix(global->get_list_plane().get_at(i)->getSoHieuMB(), input_so_hieu_mb.get_data().c_str()))
                    {
                        stt++;
                    }
                    if (stt == line_hover)
                    {
                        cout << global->get_list_plane().get_at(i)->getSoHieuMB() << '\n';
                        input_so_hieu_mb.set_data(global->get_list_plane().get_at(i)->getSoHieuMB());
                        flag_list_mb = true;
                        break;
                    }
                }
            }
        }
        void handleEvent(SDL_Event e, Position &state, int mouse_X, int mouse_Y)
        {
            nut_sua = {255, 255, 255};
            nut_x = {255, 255, 255};
            nut_auto = {255, 255, 255};
            switch (e.type)
            {
            case SDL_MOUSEMOTION:
                get_hover_mb(mouse_X, mouse_Y);
                if (MyFunc::check_click(mouse_X, mouse_Y, vi_tri_nut_x))
                {
                    nut_x = {255, 219, 26};
                }
                else if (MyFunc::check_click(mouse_X, mouse_Y, vi_tri_nut_sua))
                {
                    nut_sua = {255, 219, 26};
                }
                else if (MyFunc::check_click(mouse_X, mouse_Y, vt_nut_auto))
                {
                    nut_auto = {255, 219, 26};
                }
                break;
            case SDL_MOUSEBUTTONDOWN: // sự kiện nhấn vào các box
                this->set_click_mb();
                this->current_click_input = -1;
                for (int i = 0; i < 4; i++)
                {
                    if (MyFunc::check_click(mouse_X, mouse_Y, rect_input[i]))
                    {
                        this->current_click_input = i;
                        break;
                    }
                }
                if (MyFunc::check_click(mouse_X, mouse_Y, vi_tri_nut_x))
                {
                    state = Position::HOME;
                    this->now = true;
                    flag_list_mb = true;
                    nut_sua = {255, 255, 255};
                    nut_x = {255, 255, 255};
                }
                else if (MyFunc::check_click(mouse_X, mouse_Y, vt_nut_auto))
                {
                    Time tm;
                    tm.get_next_time_some_hours(4); // 4 giờ kể từ bây giờ
                    input_tgb_minute.set_data(std::to_string(tm.get_minute()));
                    input_tgb_hour.set_data(std::to_string(tm.get_hour()));
                    input_tgb_day.set_data(std::to_string(tm.get_day()));
                    input_tgb_month.set_data(std::to_string(tm.get_month()));
                    input_tgb_year.set_data(std::to_string(tm.get_year()));
                }
                else if (MyFunc::check_click(mouse_X, mouse_Y, vi_tri_nut_sua)) // nhấn vào vút sửa
                {
                    // add_function
                    Status result;
                    if (input_san_bay_den.is_empty() || input_so_hieu_mb.is_empty() || input_tgb_day.is_empty() || input_tgb_hour.is_empty() || input_tgb_minute.is_empty() || input_tgb_month.is_empty() || input_tgb_year.is_empty() || input_ma_cb.is_empty())
                    {
                        result = Status("Bạn Chưa Nhập Đủ Thông Tin");
                    }
                    else
                    {
                        result = this->global->get_qlcb().add_cb(input_ma_cb.get_data().c_str(), input_tgb_minute.get_num(), input_tgb_hour.get_num(), input_tgb_day.get_num(), input_tgb_month.get_num(), input_tgb_year.get_num(), input_san_bay_den.get_data().c_str(), input_so_hieu_mb.get_data().c_str());
                    }
                    global->get_thong_bao().set_mess(result.mess);
                    global->get_thong_bao().on();
                    if (result.get_status() == Status_Name::SUCCESS)
                    {
                        *(this->flag_re_render_in_home) = true;
                        flag_list_mb = true;
                        this->now = true;
                        state = Position::HOME;
                    }
                }
                break;
            }
            input_ma_cb.handleInput_ID(e, mouse_X, mouse_Y);
            input_san_bay_den.handleInput_ID(e, mouse_X, mouse_Y);
            input_so_hieu_mb.handleInput_ID(e, mouse_X, mouse_Y);
            input_tgb_day.handleInput_Num(e, mouse_X, mouse_Y);
            input_tgb_hour.handleInput_Num(e, mouse_X, mouse_Y);
            input_tgb_minute.handleInput_Num(e, mouse_X, mouse_Y);
            input_tgb_month.handleInput_Num(e, mouse_X, mouse_Y);
            input_tgb_year.handleInput_Num(e, mouse_X, mouse_Y);
            if (input_so_hieu_mb.get_is_click() && (e.type == SDL_KEYDOWN || e.type == SDL_TEXTINPUT))
                flag_list_mb = true;
            if (input_so_hieu_mb.get_is_click())
            {
                scroll.handleEvent(e, mouse_X, mouse_Y);
            }
        }
        void reset_data()
        {
            if (this->now == true)
            {
                input_ma_cb.reset_data();
                input_san_bay_den.reset_data();
                input_so_hieu_mb.reset_data();
                input_tgb_day.reset_data();
                input_tgb_month.reset_data();
                input_tgb_year.reset_data();
                input_tgb_hour.reset_data();
                input_tgb_minute.reset_data();
                this->now = false;
            }
        }
        void reset_buffer()
        {
            delete buffer_list_mb;
            buffer_list_mb = nullptr;
        }
        void render_line_data(MayBay *mb, int stt)
        {
            myscreen->render_Text(mb->getSoHieuMB(), {0, (stt - 1) * 50, 150, 50}, {0, 0, 0}, true);
            if (strlen(mb->getLoaiMB()) < 15)
            {
                myscreen->render_Text(mb->getLoaiMB(), {150, (stt - 1) * 50, 250, 50}, {0, 0, 0}, true);
            }
            else
            {
                string sub_str = string(mb->getLoaiMB()).substr(0, 15) + "...";
                myscreen->render_Text(sub_str, {150, (stt - 1) * 50, 250, 50}, {0, 0, 0}, true);
            }
            myscreen->render_Text(std::to_string(mb->getSoDay()), {400, (stt - 1) * 50, 50, 50}, {0, 0, 0}, true);
            myscreen->render_Text(std::to_string(mb->getSoDong()), {450, (stt - 1) * 50, 50, 50}, {0, 0, 0}, true);
        }

        void get_data()
        {
            if (flag_list_mb)
            {
                reset_buffer();
                int total = global->get_list_plane().get_so_luong();
                int so_luong = 0;
                for (int i = 0; i < total; i++)
                {
                    if (Func_Global::check_prefix(global->get_list_plane().get_at(i)->getSoHieuMB(), input_so_hieu_mb.get_data().c_str()))
                    {
                        so_luong++;
                    }
                }

                buffer_list_mb = new Buffer();
                if (so_luong > 0)
                {
                    buffer_list_mb->set(this->myscreen, 500, so_luong * 50);
                    buffer_list_mb->connect_render_clear();
                    myscreen->render_cot({0, 0, 150, so_luong * 50}, {255, 255, 255});
                    myscreen->render_cot({150, 0, 250, so_luong * 50}, {255, 255, 255});
                    myscreen->render_cot({400, 0, 50, so_luong * 50}, {255, 255, 255});
                    myscreen->render_cot({450, 0, 50, so_luong * 50}, {255, 255, 255});
                    int stt = 0;
                    for (int i = 0; i < total; i++)
                    {
                        if (Func_Global::check_prefix(global->get_list_plane().get_at(i)->getSoHieuMB(), input_so_hieu_mb.get_data().c_str()))
                        {
                            stt++;
                            render_line_data(global->get_list_plane().get_at(i), stt);
                        }
                    }
                    buffer_list_mb->disconnect_render();
                }
                else
                {
                    buffer_list_mb->set(this->myscreen, 500, 50);
                    buffer_list_mb->connect_render_clear();
                    myscreen->render_Text("Không Tồn Tại Số Hiệu Máy Bay Phù Hợp", buffer_list_mb->get_rect(), {0, 0, 0}, true);
                    buffer_list_mb->disconnect_render();
                }
                buffer_list_mb->set_vitri(khung_list_mb.x, khung_list_mb.y);
                srcrect = {0, 0, khung_list_mb.w, khung_list_mb.h};
                scroll.set_target(*buffer_list_mb, srcrect);
                flag_list_mb = false;
            }
        }
        void render_menu()
        {
            reset_data();
            get_data();
            myscreen->blur_background(150);
            khung_add_edit->render(myscreen->get_my_renderer());

            for (int i = 0; i < 4; i++)
            { // tg
                this->myscreen->render_Text(name_field_time[i], rect_field_time[i], {0, 0, 0}, true);
            }

            for (int i = 0; i < 4; i++)
            {
                myscreen->render_Text(name_field[i], rect_field[i], {0, 0, 0}, true);
            }

            input_ma_cb.render();
            input_san_bay_den.render();
            input_so_hieu_mb.render();
            input_tgb_day.render();
            input_tgb_month.render();
            input_tgb_year.render();
            input_tgb_hour.render();
            input_tgb_minute.render();

            myscreen->render_cot(vt_nut_auto, nut_auto);
            myscreen->render_Text("auto", vt_nut_auto, {0, 0, 0}, true);
            this->render_button_xoa_sua();
            if (input_so_hieu_mb.get_is_click())
            {
                myscreen->render_cot(khung_list_mb, {255, 255, 255});
                if (line_hover != -1)
                    myscreen->render_cot({khung_list_mb.x, khung_list_mb.y - srcrect.y + line_hover * 50, khung_list_mb.w, 50}, {159, 212, 171});

                buffer_list_mb->render(true, srcrect);
                scroll.render(*myscreen);
                myscreen->render_cot({khung_list_mb.x, khung_list_mb.y - 50, khung_list_mb.w, 50});
                myscreen->render_Text("Số Hiệu MB", {khung_list_mb.x, khung_list_mb.y - 50, 150, 50}, {0, 0, 0}, true);
                myscreen->render_Text("Loại", {khung_list_mb.x + 150, khung_list_mb.y - 50, 250, 50}, {0, 0, 0}, true);
                myscreen->render_Text("Dãy", {khung_list_mb.x + 400, khung_list_mb.y - 50, 50, 50}, {0, 0, 0}, true);
                myscreen->render_Text("Dòng", {khung_list_mb.x + 450, khung_list_mb.y - 50, 50, 50}, {0, 0, 0}, true);
            }
        }
        void render_button_xoa_sua()
        {
            myscreen->render_cot(vi_tri_nut_sua, nut_sua);
            myscreen->render_Text("OK", vi_tri_nut_sua, {0, 0, 0}, true);
            myscreen->render_cot(vi_tri_nut_x, nut_x);
            myscreen->render_Text("X", vi_tri_nut_x, {0, 0, 0}, true);
        }
    };

} // namespace Flight

class View_Flight
{
private:
    Global_Variable &global;

    Input input_ma_so_cb;
    Input input_noi_den;
    Input input_day;
    Input input_month;
    Input input_year;

    Choose input_con_ve;

    Buffer table;
    Buffer data;

    bool flag = false;
    bool flag3 = false; // theo dõi sự thay đổi còn vé
    bool &flag2;

    Flight::Position state = Flight::Position::HOME; // mặc định ở Child_Route Home

    Flight::DatVe dat_ve;
    Flight::XemHK xem_hk;
    Flight::Menu menu_flight; // route menu
    Flight::Edit edit_flight; // route edit
    Flight::Add add_flight;   // route edit

    ChuyenBay *list_cb_dc_render[10];
    ChuyenBay *temp = nullptr; // lấy con trỏ máy bay ở vị trí đang hover rồi click

    int vi_tri_hover_on_table = -1; // vị trí hover trên table data Máy Bay tính từ 0 - 9
    int so_luong_data = 0;          // số lượng máy bay
    int current_page;               // phân trang hiện tại
    int mouse_X, mouse_Y;           // vị trí chuột

    int route_flight_width[7]{100, 200, 200, 450, 200, 200, 150};
    string route_flight_name_cot[7]{"STT", "Mã Số CB", "Sân Bay Đến", "Thời Gian Bay", "Trạng Thái", "Số Hiệu MB", "Vé Còn Trống"};

    SDL_Color nut_add{255, 255, 255};

public:
    View_Flight(Global_Variable &gb, bool &flag_re_render_from_thread);

    void handleEvent(SDL_Event e, bool &is_home, int mouse_X, int mouse_Y)
    {
        this->mouse_X = mouse_X;
        this->mouse_Y = mouse_Y;
        nut_add = {255, 255, 255};
        if (this->state == Flight::Position::HOME)
        {
            is_home = true;
            switch (e.type)
            {
            case SDL_MOUSEMOTION:
                if (global.get_c_component().add.is_in_box(mouse_X, mouse_Y))
                {
                    nut_add = {255, 219, 26};
                }
                this->vi_tri_hover_on_table = Func_Global::get_line(this->mouse_X, this->mouse_Y, this->so_luong_data, this->current_page); // 0 - 9
                break;
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
                // end handle

                if (this->vi_tri_hover_on_table != -1)
                { // nếu nhấn vào, mà đnag hover vào line trong table thì bật menu.
                    this->temp = this->list_cb_dc_render[vi_tri_hover_on_table];
                    this->state = Flight::Position::MENU;
                }
                if (global.get_c_component().add.is_in_box(mouse_X, mouse_Y))
                {
                    state = Flight::Position::ADD;
                }
                break;
            }

            input_ma_so_cb.handleInput_ID(e, mouse_X, mouse_Y);
            input_noi_den.handleInput_ID(e, mouse_X, mouse_Y);
            input_day.handleInput_Num(e, mouse_X, mouse_Y);
            input_year.handleInput_Num(e, mouse_X, mouse_Y);
            input_month.handleInput_Num(e, mouse_X, mouse_Y);
            input_con_ve.handle_choose(e, mouse_X, mouse_Y);
            if (e.type == SDL_KEYDOWN || e.type == SDL_TEXTINPUT)
                this->re_render_data();
            if (flag3 != input_con_ve.get_data())
            {
                this->re_render_data();
                flag3 = input_con_ve.get_data();
            }
        }
        else
        {
            is_home = false;
            if (state == Flight::Position::MENU)
            {
                menu_flight.handleEvent(e, this->state, mouse_X, mouse_Y);
            }
            else if (state == Flight::Position::EDIT)
            {
                edit_flight.handleEvent(e, this->state, mouse_X, mouse_Y);
            }
            else if (state == Flight::Position::ADD)
            {
                add_flight.handleEvent(e, this->state, mouse_X, mouse_Y);
            }
            else if (state == Flight::Position::DATVE)
            {
                dat_ve.handleEvent(e, this->state, mouse_X, mouse_Y);
            }
            else if (state == Flight::Position::XEM_HK)
            {
                xem_hk.handleEvent(e, this->state, mouse_X, mouse_Y);
            }
        }
    }
    void render()
    {

        this->follow_flag();

        table.render(); // render table
        if (vi_tri_hover_on_table != -1)
        {
            this->global.get_myscreen().render_cot({X_START_TABLE, Y_START_TABLE + (vi_tri_hover_on_table)*50, WIDTH_TABLE, 50}, {159, 212, 171});
        }

        data.render(); // render data

        this->global.get_myscreen().render_cot(this->global.get_c_component().add.get_rect(), nut_add);
        this->global.get_c_component().add.render(this->global.get_myscreen().get_my_renderer()); // render nút add

        this->global.get_c_component().render_next_prev(mouse_X, mouse_Y, current_page, so_luong_data, &(this->global.get_myscreen()));

        SDL_Rect rect_temp{100, 175, 150, 50}; // ô input : 300,175,300,50
        this->global.get_myscreen().render_Text("Mã CB:", rect_temp, {0, 0, 0}, true);
        input_ma_so_cb.render(); // render ô input nhập số hiệu máy bay
        SDL_Rect rect_sbd{1050 - 150, 175, 150, 50};
        this->global.get_myscreen().render_Text("Nơi Đến:", rect_sbd, {0, 0, 0}, true);
        input_noi_den.render();
        SDL_Rect rect_time{500, 175, 100, 50};
        this->global.get_myscreen().render_Text("Time:", rect_time, {0, 0, 0}, true);
        input_day.render();
        rect_time = {650, 175, 50, 50};
        this->global.get_myscreen().render_Text("/", rect_time, {0, 0, 0}, true);
        input_month.render();
        rect_time = {750, 175, 50, 50};
        this->global.get_myscreen().render_Text("/", rect_time, {0, 0, 0}, true);
        input_year.render();

        SDL_Rect rect_conve{1300, 175, 100, 50};
        this->global.get_myscreen().render_Text("Còn Vé:", rect_conve, {0, 0, 0}, true);
        input_con_ve.render();

        if (state == Flight::Position::MENU)
        {
            menu_flight.render_menu(temp, vi_tri_hover_on_table);
        }
        else if (state == Flight::Position::EDIT)
        {
            edit_flight.render_menu(temp);
        }
        else if (state == Flight::Position::ADD)
        {
            add_flight.render_menu();
        }
        else if (state == Flight::Position::DATVE)
        {
            dat_ve.render_menu(temp);
        }
        else if (state == Flight::Position::XEM_HK)
        {
            xem_hk.render_menu(temp);
        }
    }

    ////////////////////////////////////////////////////////////
    void getData() // đưa data vào bộ đệm
    {
        data.connect_render_clear();

        ListChuyenBay *list_cb = &(this->global.get_qlcb().getListCB());

        int start = (this->current_page - 1) * 10;
        int end = start + 9; // 0 - 9 là 10
        int stt = 0;
        int so_line_render = 0;
        int index = 0;
        // filter_function
        for (ChuyenBay *current = list_cb->get_head(); current != nullptr; current = current->get_next())
        {
            if (Func_Global::check_prefix(current->get_ma_so_cb(), this->input_ma_so_cb.get_data().c_str()) && Func_Global::check_prefix(current->get_san_bay_den(), this->input_noi_den.get_data().c_str()) && (input_day.is_empty() || current->get_thoi_gian_bay().get_day() == input_day.get_num()) && (input_month.is_empty() || current->get_thoi_gian_bay().get_month() == input_month.get_num()) && (input_year.is_empty() || current->get_thoi_gian_bay().get_year() == input_year.get_num()) && (!input_con_ve.get_data() || current->get_trang_thai_cb() == 1))
            {
                if (stt >= start && stt <= end)
                {
                    this->list_cb_dc_render[index++] = current;
                    this->render_line_data(stt, start, current);
                    so_line_render++;
                }
                stt++;
            }
        }
        this->so_luong_data = stt;
        if (so_line_render == 0)
        {
            this->global.get_myscreen().render_Text("Trống !!!", {X_START_TABLE, Y_START_TABLE, WIDTH_TABLE, HEIGHT_TABLE}, {255, 0, 0}, true);
        }
        data.disconnect_render();
    }
    void re_render_data();
    void follow_flag();
    void createTable();                                       // vẽ ra viền bảng
    void render_line_data(int stt, int start, ChuyenBay *cb); // render 1 linedata Máy Bay
};
View_Flight::View_Flight(Global_Variable &gb, bool &flag_re_render_from_thread) : global{gb}, flag2{flag_re_render_from_thread}
{
    current_page = 1;

    menu_flight.set(global, &flag);
    edit_flight.set(global, &flag);
    add_flight.set(global, &flag);
    dat_ve.set(global, flag);
    xem_hk.set(global);

    table.set(&(global.get_myscreen()), WIDTH_TABLE, HEIGHT_TABLE + 50);
    table.set_vitri(X_START_TABLE, Y_START_TABLE - 50);
    this->createTable();

    data.set(&(global.get_myscreen()), WIDTH_TABLE, HEIGHT_TABLE);
    data.set_vitri(X_START_TABLE, Y_START_TABLE);
    this->getData();

    input_ma_so_cb.set(&(global.get_myscreen()), MAX_LENGTH_MA_CB, {250, 175, 200, 50});
    string note = "Tối đa " + std::to_string(MAX_LENGTH_MA_CB) + " kí tự";
    input_ma_so_cb.set_note(note);
    input_noi_den.set(&(global.get_myscreen()), MAX_LENGTH_SAN_BAY_DEN, {1050, 175, 200, 50});
    note = "Tối đa " + std::to_string(MAX_LENGTH_SAN_BAY_DEN) + " kí tự";
    input_noi_den.set_note(note);
    input_day.set(&(global.get_myscreen()), 2, {600, 175, 50, 50});
    note = "dd";
    input_day.set_note(note);
    input_month.set(&(global.get_myscreen()), 2, {700, 175, 50, 50});
    note = "mm";
    input_month.set_note(note);
    input_year.set(&(global.get_myscreen()), 4, {800, 175, 100, 50});
    note = "yyyy";
    input_year.set_note(note);

    input_con_ve.connect(&(global.get_myscreen()));
    input_con_ve.set_box(&(global.get_c_component().unpick), &(global.get_c_component().pick));
    input_con_ve.set_vitri({1400, 175, 50, 50});
}
void View_Flight::re_render_data()
{
    this->flag = true;
}
void View_Flight::follow_flag()
{
    if (this->flag || this->flag2)
    {
        this->getData();
        this->flag = false;
        this->flag2 = false;
    }
}

void View_Flight::createTable() // vẽ ra viền bảng
{
    table.connect_render_clear();
    this->global.get_myscreen().render_table(7, route_flight_width, route_flight_name_cot);
    table.disconnect_render();
}

void View_Flight::render_line_data(int stt, int start, ChuyenBay *cb) // render 1 linedata Máy Bay
{
    SDL_Rect rect;
    rect = {0, 0 + (stt - start) * 50, route_flight_width[0], 50};
    this->global.get_myscreen().render_Text(std::to_string((stt) + 1), rect, {0, 0, 0, 255}, true);

    rect.x += rect.w;
    rect.w = route_flight_width[1];
    this->global.get_myscreen().render_Text(cb->get_ma_so_cb(), rect, {0, 0, 0, 255}, true);

    rect.x += rect.w;
    rect.w = route_flight_width[2];
    this->global.get_myscreen().render_Text(cb->get_san_bay_den(), rect, {0, 0, 0, 255}, true);

    rect.x += rect.w;
    rect.w = route_flight_width[3];
    this->global.get_myscreen().render_Text(cb->get_thoi_gian_bay().to_string(), rect, {0, 0, 0, 255}, true);

    rect.x += rect.w;
    rect.w = route_flight_width[4];
    string status;
    int tt = cb->get_trang_thai_cb();
    if (tt == 0)
        this->global.get_myscreen().render_Text("Đã Hủy", rect, {0, 0, 0, 255}, true);
    else if (tt == 1)
        this->global.get_myscreen().render_Text("Còn Vé", rect, {0, 0, 0, 255}, true);
    else if (tt == 2)
        this->global.get_myscreen().render_Text("Hết Vé", rect, {0, 0, 0, 255}, true);
    else if (tt == 3)
        this->global.get_myscreen().render_Text("Hoàn Thành", rect, {0, 0, 0, 255}, true);

    rect.x += rect.w;
    rect.w = route_flight_width[5];
    this->global.get_myscreen().render_Text(cb->get_so_hieu_mb(), rect, {0, 0, 0, 255}, true);

    rect.x += rect.w;
    rect.w = route_flight_width[6];
    int total_ve = cb->get_listve().get_total_ve();
    int ve_trong = cb->get_listve().so_ve_trong();
    string so_ve = std::to_string(ve_trong) + " / " + std::to_string(total_ve);
    this->global.get_myscreen().render_Text(so_ve, rect, {0, 0, 0, 255}, true);
}

#endif