#ifndef VIEWS_TICKET_H
#define VIEWS_TICKET_H

namespace Flight
{
    enum Position
    {
        HOME,
        MENU,
        EDIT,
        DELETE,
        ADD,
        DATVE,
        XEM_HK
    };

    /**
     * @brief Tạo Scroll cho 1 buffer.
     * @note Phải dùng `set_target` để chỉ định Buffer muốn tạo Scroll.
     * Dùng `handle_event` để bắt sự kiện lăn chuột và kéo thanh Scroll.
     * Dùng `render` để render ra màn hình.
     * Scroll sẽ tự tính vị trí hiển thị và có được hiển thị hay không.
     */
    class Scroll
    {
    private:
        Buffer *buffer = nullptr;
        SDL_Rect *srcrect = nullptr;
        SDL_Rect vi_tri = {0, 0, 0, 0};
        SDL_Rect vt_point_scroll = {0, 0, 0, 0};

        SDL_Rect vi_tri_x = {0, 0, 0, 0};
        SDL_Rect vt_point_scroll_x = {0, 0, 0, 0};

        SDL_Rect temp;

        double tile_x = 0;
        double tile_y = 0;

        int start_x = 0;
        int start_y = 0;

    public:
        void set_target(Buffer &bf, SDL_Rect &srcr)
        {
            this->buffer = &bf;
            this->srcrect = &srcr;
            vi_tri = {buffer->get_rect().x + srcrect->w, buffer->get_rect().y, 20, srcrect->h};
            vt_point_scroll = {vi_tri.x, vi_tri.y, 20, (vi_tri.h * vi_tri.h) / bf.get_rect().h};

            vi_tri_x = {buffer->get_rect().x, buffer->get_rect().y + srcrect->h, srcrect->w, 20};

            vt_point_scroll_x = {vi_tri_x.x, vi_tri_x.y, (vi_tri_x.w * vi_tri_x.w) / bf.get_rect().w, 20};
        }
        void handleEvent(SDL_Event e, int mouse_X, int mouse_Y)
        {
            if (srcrect == nullptr)
                return;
            switch (e.type)
            {
            case SDL_MOUSEWHEEL:
                if (buffer->get_rect().h > srcrect->h)
                {
                    srcrect->y -= e.wheel.y * 5;
                    if (srcrect->y < 0)
                        srcrect->y = 0;
                    if (srcrect->y > (buffer->get_rect().h - srcrect->h))
                        srcrect->y = (buffer->get_rect().h - srcrect->h);
                }
                if (buffer->get_rect().w > srcrect->w)
                {
                    srcrect->x += e.wheel.x * 5;
                    if (srcrect->x < 0)
                        srcrect->x = 0;
                    if (srcrect->x > (buffer->get_rect().w - srcrect->w))
                        srcrect->x = (buffer->get_rect().w - srcrect->w);
                }
                break;
            case SDL_MOUSEBUTTONUP:
                if (e.button.button == SDL_BUTTON_LEFT)
                {
                    tile_x = 0;
                    tile_y = 0;
                    start_x = 0;
                    start_y = 0;
                }
                break;
            case SDL_MOUSEBUTTONDOWN: // sự kiện nhấn vào các box
                if (e.button.button == SDL_BUTTON_LEFT)
                {
                    start_x = mouse_X;
                    start_y = mouse_Y;
                    temp = *(srcrect);
                }

                break;

            case SDL_MOUSEMOTION:

                if (MyFunc::check_click(mouse_X, mouse_Y, vt_point_scroll) && buffer->get_rect().h > srcrect->h)
                {
                    if (e.motion.state & SDL_BUTTON_LMASK)
                    {

                        tile_y = ((mouse_Y - start_y) * 1.0) / vi_tri.h;
                        tile_x = ((mouse_X - start_x) * 1.0) / vi_tri.w;
                        if (vt_point_scroll.y <= vi_tri.y && tile_y < 0)
                        {

                            srcrect->y = 0;
                        }
                        else if (vt_point_scroll.y + 1 >= (vi_tri.y + vi_tri.h - vt_point_scroll.h) && tile_y > 0)
                        {
                            srcrect->y = buffer->get_rect().h - srcrect->h;
                        }
                        else
                        {
                            *srcrect = MyFunc::calc_phan_tram(0, tile_y, temp, this->buffer->get_rect().w, this->buffer->get_rect().h);
                        }
                    }
                }
                if (MyFunc::check_click(mouse_X, mouse_Y, vt_point_scroll_x) && buffer->get_rect().w > srcrect->w)
                {
                    if (e.motion.state & SDL_BUTTON_LMASK)
                    {
                        tile_x = ((mouse_X - start_x) * 1.0) / vi_tri_x.w;

                        if (vt_point_scroll_x.x <= vi_tri_x.x && tile_x < 0)
                        {

                            srcrect->x = 0;
                        }
                        else if (vt_point_scroll_x.x + 1 >= (vi_tri_x.x + vi_tri_x.w - vt_point_scroll_x.w) && tile_x > 0)
                        {
                            srcrect->x = buffer->get_rect().w - srcrect->w;
                        }
                        else
                        {
                            *srcrect = MyFunc::calc_phan_tram(tile_x, 0, temp, this->buffer->get_rect().w, this->buffer->get_rect().h);
                        }
                    }
                }

                break;
            }
        }
        void render(MyScreen &myscreen)
        {
            if (srcrect == nullptr)
                return;
            if (buffer->get_rect().h > srcrect->h)
            {
                myscreen.render_cot(vi_tri, {255, 255, 255}); // render nguyên thanh
                vt_point_scroll.y = buffer->get_rect().y + (srcrect->y * srcrect->h * 1.0) / buffer->get_rect().h;
                myscreen.render_cot(vt_point_scroll, {33, 255, 00});
            }
            if (buffer->get_rect().w > srcrect->w)
            {
                myscreen.render_cot(vi_tri_x, {255, 255, 255}); // render nguyên thanh
                vt_point_scroll_x.x = buffer->get_rect().x + (srcrect->x * srcrect->w * 1.0) / buffer->get_rect().w;
                myscreen.render_cot(vt_point_scroll_x, {33, 255, 00});
            }
        }
    };
    class View_Dat_ve
    {
    private:
        Global_Variable *global = nullptr;
        SDL_Rect khung;
        SDL_Rect vien;
        SDL_Rect info;
        SDL_Rect vien_info;
        SDL_Color nut_x = {255, 255, 255};
        SDL_Rect vt_nut_x = {0, 0, 0, 0};
        SDL_Color nut_ok = {255, 255, 255};
        SDL_Rect vt_nut_ok = {0, 0, 0, 0};
        bool *route = nullptr;

        int so_day = -1;
        int so_dong = -1;

        ChuyenBay *target_cb = nullptr;

        Input cmnd;
        Input ho;
        Input ten;
        Choose nam;
        Choose nu;

        bool gioi_tinh = true; // true nam, false nu

        bool flag = false;

        HanhKhach *hanhkhach = nullptr;

        bool render_bien_lai = false;
        SDL_Rect khung_bien_lai;
        SDL_Rect nut_ok_bienlai;
        SDL_Color c_nut_ok_bl = {255, 255, 255};

        bool *flag_re_render = nullptr;
        bool* flag_view_flight = nullptr;

    public:
        void set(Global_Variable *gl, SDL_Rect khung_dat_ve, bool &r, bool &flag_re_render, bool& fl)
        {
            this->global = gl;
            route = &r;
            this->flag_re_render = &flag_re_render;
            this->flag_view_flight = &fl;
            khung = MyFunc::center_Rect(700, 500, khung_dat_ve);
            info = {khung.x, khung.y - 200, khung.w, 400};
            vien_info = {info.x - 2, info.y - 2, info.w + 4, info.h + 4};
            vien = {khung.x - 2, khung.y - 2, khung.w + 4, khung.h + 4};
            vt_nut_x = {info.x + info.w - 50, info.y, 50, 50};
            vt_nut_ok = {khung.x + 300, khung.y + 415, 100, 50};

            khung_bien_lai = MyFunc::center_Rect(800, 800, {0, 0, WIDTH_SCREEN, HEIGHT_SCREEN});
            nut_ok_bienlai = MyFunc::center_Rect(100, 50, {khung_bien_lai.x, khung_bien_lai.y + khung_bien_lai.h - 100, khung_bien_lai.w, 100});

            cmnd.set(&(global->get_myscreen()), MAX_LENGTH_SO_CMND, {khung.x + 50 + 200, khung.y + 100, 400, 50});
            ho.set(&(global->get_myscreen()), MAX_LENGTH_HO, {khung.x + 50 + 200, khung.y + 175, 400, 50});
            ten.set(&(global->get_myscreen()), MAX_LENGTH_TEN, {khung.x + 50 + 200, khung.y + 250, 400, 50});
            nam.connect(&(global->get_myscreen()));
            nam.set_box(&(global->get_c_component().unpick), &(global->get_c_component().pick));
            nam.set_vitri({khung.x + 50 + 200 + 100 + 25, khung.y + 320, 50, 50});

            nu.connect(&(gl->get_myscreen()));
            nu.set_box(&(global->get_c_component().unpick), &(global->get_c_component().pick));
            nu.set_vitri({khung.x + 50 + 200 + 300 + 25, khung.y + 320, 50, 50});
        }
        void set_target(ChuyenBay *cb, int so_day, int so_dong)
        {
            this->target_cb = cb;
            this->so_day = so_day;
            this->so_dong = so_dong;
            this->reset_data();
        }
        void handle_event(SDL_Event e, int mouse_X, int mouse_Y)
        {
            nut_x = {255, 255, 255};
            nut_ok = {255, 255, 255};
            nut_ok_bienlai = {255, 255, 255};
            if (render_bien_lai)
            {
                switch (e.type)
                {
                case SDL_MOUSEMOTION:
                    if (MyFunc::check_click(mouse_X, mouse_Y, nut_ok_bienlai))
                    {
                        c_nut_ok_bl = {255, 219, 26};
                    }
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    if (MyFunc::check_click(mouse_X, mouse_Y, nut_ok_bienlai))
                    {
                        render_bien_lai = false;
                        hanhkhach = nullptr;
                        *route = false;
                        so_day = -1;
                        so_dong = -1;
                        target_cb = nullptr;
                    }
                    break;
                }
            }
            else
            {
                switch (e.type)
                {
                case SDL_MOUSEMOTION:
                    if (MyFunc::check_click(mouse_X, mouse_Y, vt_nut_x))
                    {
                        nut_x = {255, 219, 26};
                    }
                    if (MyFunc::check_click(mouse_X, mouse_Y, vt_nut_ok))
                    {
                        nut_ok = {255, 219, 26};
                    }
                    break;
                case SDL_MOUSEBUTTONDOWN: // sự kiện nhấn vào các box
                    if (MyFunc::check_click(mouse_X, mouse_Y, vt_nut_x))
                    {
                        hanhkhach = nullptr;
                        *route = false;
                        so_day = -1;
                        so_dong = -1;
                        target_cb = nullptr;
                    }
                    if (MyFunc::check_click(mouse_X, mouse_Y, vt_nut_ok))
                    {
                        if (hanhkhach != nullptr)
                        {
                            Status result = global->get_qlcb().dat_ve_khachquen(target_cb, so_day, so_dong, cmnd.get_data().c_str());
                            global->get_thong_bao().set_mess(result.mess);
                            global->get_thong_bao().on();
                        }
                        else
                        {
                            Status result = global->get_qlcb().dat_ve_khachmoi(target_cb, so_day, so_dong, cmnd.get_data().c_str(), ho.get_data().c_str(), ten.get_data().c_str(), gioi_tinh);
                            global->get_thong_bao().set_mess(result.mess);
                            global->get_thong_bao().on();
                        }
                        // render_bien_lai = true;
                        *flag_re_render = true;
                        *flag_view_flight = true;
                        hanhkhach = nullptr;
                        *route = false;
                        so_day = -1;
                        so_dong = -1;
                        target_cb = nullptr;
                    }
                }
                cmnd.handleInput_Num(e, mouse_X, mouse_Y);
                if (cmnd.get_is_click() && (e.type == SDL_KEYDOWN || e.type == SDL_TEXTINPUT))
                    flag = true;
                ho.handleInput_Name(e, mouse_X, mouse_Y);
                ten.handleInput_Name(e, mouse_X, mouse_Y);
                if (nam.handle_choose(e, mouse_X, mouse_Y))
                {
                    gioi_tinh = true;
                }
                else if (nu.handle_choose(e, mouse_X, mouse_Y))
                {
                    gioi_tinh = false;
                }
            }
        }
        void set_data_gioi_tinh()
        {
            nam.set_data(gioi_tinh);
            nu.set_data(!gioi_tinh);
        }
        void set_data_input()
        {
            if (flag)
            {
                hanhkhach = global->get_qlcb().getListHK().search(cmnd.get_data().c_str());
                if (hanhkhach != nullptr)
                {
                    ho.set_data(hanhkhach->getHo());
                    ten.set_data(hanhkhach->getTen());
                    gioi_tinh = hanhkhach->getPhai();
                }
                else
                {
                    ho.set_data("");
                    ten.set_data("");
                }
                flag = false;
            }
        }
        void reset_data()
        {
            cmnd.reset_data();
            ho.reset_data();
            ten.reset_data();
            gioi_tinh = true;
        }
        void render_data(MyScreen &myscreen)
        {
            set_data_input();
            set_data_gioi_tinh();

            myscreen.render_Text("Mã Chuyến Bay:", {info.x, info.y, 200, 50}, {0, 0, 0}, true);
            myscreen.render_Text(target_cb->get_ma_so_cb(), {info.x + 200, info.y, 500, 50}, {0, 0, 0}, true);
            myscreen.render_Text("Sân Bay Đến:", {info.x, info.y + 50, 200, 50}, {0, 0, 0}, true);
            myscreen.render_Text(target_cb->get_san_bay_den(), {info.x + 200, info.y + 50, 500, 50}, {0, 0, 0}, true);
            myscreen.render_Text("Thời Gian Bay:", {info.x, info.y + 100, 200, 50}, {0, 0, 0}, true);
            Time time = target_cb->get_thoi_gian_bay();
            string text_time = std::to_string(time.get_hour()) + " giờ, " + std::to_string(time.get_minute()) + " phút, ngày " + std::to_string(time.get_day()) + " tháng " + std::to_string(time.get_month()) + " năm " + std::to_string(time.get_year());
            myscreen.render_Text(text_time, {info.x + 200, info.y + 100, 500, 50}, {0, 0, 0}, true);
            myscreen.render_Text("Mã Vé:", {info.x, info.y + 150, 200, 50}, {0, 0, 0}, true);
            string text_ma_Ve = (char)(so_day + 'A') + std::to_string(so_dong + 1) + " (Dãy " + std::to_string(so_day + 1) + " - Dòng " + std::to_string(so_dong + 1) + ")";
            myscreen.render_Text(text_ma_Ve, {info.x + 200, info.y + 150, 500, 50}, {0, 0, 0}, true);

            myscreen.render_Text("Nhập Thông Tin Hành Khách", {khung.x, khung.y, khung.w, 100}, {0, 0, 0}, true);
            myscreen.render_Text("Số CMND:", {khung.x + 50, khung.y + 100, 200, 50}, {0, 0, 0}, true);

            cmnd.render();

            myscreen.render_Text("Họ:", {khung.x + 50, khung.y + 175, 200, 50}, {0, 0, 0}, true);
            ho.render();
            myscreen.render_Text("Tên:", {khung.x + 50, khung.y + 250, 200, 50}, {0, 0, 0}, true);
            ten.render();

            myscreen.render_Text("Giới Tính:", {khung.x + 50, khung.y + 320, 200, 50}, {0, 0, 0}, true);
            myscreen.render_Text("Nam", {khung.x + 50 + 200, khung.y + 320, 100, 50}, {0, 0, 0}, true);
            myscreen.render_Text("Nữ", {khung.x + 50 + 200 + 200, khung.y + 320, 100, 50}, {0, 0, 0}, true);
            nam.render();
            nu.render();

            myscreen.render_cot(vt_nut_ok);
            myscreen.render_Text("Đặt Vé", vt_nut_ok, {0, 0, 0}, true);
        }
        void render_bl(MyScreen &myscreen)
        {
            if (render_bien_lai)
            {
                myscreen.blur_background(90);
                myscreen.render_cot(khung_bien_lai, {255, 255, 255});
                int temp = khung_bien_lai.y;
                int a[7] = {temp + 100, temp + 175, temp + 250, temp + 325, temp + 400, temp + 475, temp + 550};
                //
                myscreen.render_Text("_Thông Tin Đặt Vé_", {khung_bien_lai.x, khung_bien_lai.y, khung_bien_lai.w, 50}, {0, 0, 0}, true);
                //
                myscreen.render_Text("Số CMND:", {khung_bien_lai.x, a[0], 300, 50}, {0, 0, 0}, true);
                myscreen.render_Text(cmnd.get_data(), {khung_bien_lai.x + 300, a[0], 500, 50}, {0, 0, 0}, true);
                //
                myscreen.render_Text("Họ Và Tên:", {khung_bien_lai.x, a[1], 300, 50}, {0, 0, 0}, true);
                string ho_ten = ho.get_data() + " " + ten.get_data();
                myscreen.render_Text(ho_ten, {khung_bien_lai.x + 300, a[1], 500, 50}, {0, 0, 0}, true);
                //
                myscreen.render_Text("Giới Tính:", {khung_bien_lai.x, a[2], 300, 50}, {0, 0, 0}, true);
                myscreen.render_Text(gioi_tinh ? "Nam" : "Nữ", {khung_bien_lai.x + 300, a[2], 500, 50}, {0, 0, 0}, true);
                //
                myscreen.render_Text("Mã Chuyến Bay:", {khung_bien_lai.x, a[3], 300, 50}, {0, 0, 0}, true);
                myscreen.render_Text(target_cb->get_ma_so_cb(), {khung_bien_lai.x + 300, a[3], 500, 50}, {0, 0, 0}, true);
                //
                myscreen.render_Text("Số Hiệu Máy Bay:", {khung_bien_lai.x, a[4], 300, 50}, {0, 0, 0}, true);
                myscreen.render_Text(target_cb->get_so_hieu_mb(), {khung_bien_lai.x + 300, a[4], 500, 50}, {0, 0, 0}, true);
                //
                myscreen.render_Text("Thời Gian bay:", {khung_bien_lai.x, a[5], 300, 50}, {0, 0, 0}, true);
                myscreen.render_Text(target_cb->get_thoi_gian_bay().to_string(), {khung_bien_lai.x + 300, a[4], 500, 50}, {0, 0, 0}, true);
                //
                myscreen.render_Text("Sân Bay Đến:", {khung_bien_lai.x, a[6], 300, 50}, {0, 0, 0}, true);
                myscreen.render_Text(target_cb->get_san_bay_den(), {khung_bien_lai.x + 300, a[4], 500, 50}, {0, 0, 0}, true);

                myscreen.render_cot(nut_ok_bienlai, c_nut_ok_bl);
                myscreen.render_Text("OK", nut_ok_bienlai, {0, 0, 0}, true);
            }
        }
        void render(MyScreen &myscreen)
        {
            myscreen.blur_background(50);
            myscreen.render_cot(vien_info, {0, 0, 0});
            myscreen.render_cot(info, {255, 255, 255});
            myscreen.render_cot(vien, {0, 0, 0});
            myscreen.render_cot(khung, {255, 255, 255});
            myscreen.render_cot(vt_nut_x, nut_x);
            myscreen.render_Text("X", vt_nut_x, {0, 0, 0}, true);
            render_data(myscreen);
            render_bl(myscreen);
        }
        ~View_Dat_ve()
        {
        }
    };
    class DatVe
    {
    private:
        Global_Variable *global = nullptr;
        MyScreen *myscreen = nullptr;
        ChuyenBay *target = nullptr;
        SDL_Color nut_x = {255, 255, 255};
        SDL_Rect vt_nut_x = {0, 0, 0, 0};
        Buffer *buffer_ve;
        bool flag = true;

        SDL_Rect srcrect = {0, 0, 0, 0};

        SDL_Rect hover = {0, 0, 50, 50};
        SDL_Color hover_c = {255, 255, 255};

        Scroll scroll;
        SDL_Rect khung_dat_ve;
        SDL_Rect vien_khung_dat_ve;

        View_Dat_ve view_dat_ve;

        bool route = false; // false : không render màn đặt vé, true: render

        int current_hover_so_day = -1;
        int current_hover_so_dong = -1;
        int temp_1;
        int temp_2;

        string so_ve = "";

    public:
        DatVe()
        {
            khung_dat_ve = MyFunc::center_Rect(1300, 750, {X_START_BODY, Y_START_BODY, W_BODY, H_BODY});
            vien_khung_dat_ve = {khung_dat_ve.x - 2, khung_dat_ve.y - 2, khung_dat_ve.w + 4, khung_dat_ve.h + 4};
            vt_nut_x = {khung_dat_ve.x + khung_dat_ve.w - 50, khung_dat_ve.y - 100, 50, 50};
        }
        ~DatVe()
        {
            delete buffer_ve;
        }
        void set(Global_Variable &global, bool& flag_view_flight)
        {
            this->global = &global;
            this->myscreen = &(global.get_myscreen());
            view_dat_ve.set(&global, khung_dat_ve, route, flag, flag_view_flight);
        }
        void handleEvent(SDL_Event e, Position &state, int mouse_X, int mouse_Y)
        {
            nut_x = {255, 255, 255};
            hover_c = {255, 255, 255};
            hover = {0, 0, 0, 0};
            so_ve = "";

            if (route == false)
            {
                scroll.handleEvent(e, mouse_X, mouse_Y);
                switch (e.type)
                {
                case SDL_MOUSEBUTTONDOWN: // sự kiện nhấn vào các box
                    if (MyFunc::check_click(mouse_X, mouse_Y, vt_nut_x))
                    {
                        flag = true;
                        delete buffer_ve;
                        buffer_ve = nullptr;
                        state = Position::HOME;
                    }
                    if (current_hover_so_day != -1 && current_hover_so_dong != -1)
                    {
                        view_dat_ve.set_target(this->target, current_hover_so_day, current_hover_so_dong);
                        route = true; // bật màn đặt vé lên
                    }
                    break;

                case SDL_MOUSEMOTION:
                    if (MyFunc::check_click(mouse_X, mouse_Y, vt_nut_x))
                    {
                        nut_x = {255, 219, 26};
                    }
                    if (MyFunc::check_click(mouse_X, mouse_Y, khung_dat_ve))
                    {
                        temp_1 = mouse_X - khung_dat_ve.x;
                        temp_2 = mouse_Y - khung_dat_ve.y;
                        if ((((temp_1 + srcrect.x) % 100) >= 25) && (((temp_1 + srcrect.x) % 100) <= 75) && (((temp_2 + srcrect.y) % 100) >= 25) && (((temp_2 + srcrect.y) % 100) <= 75))
                        {
                            hover = MyFunc::center_Rect(50, 50, {((temp_1 + srcrect.x) / 100) * 100 - srcrect.x + khung_dat_ve.x, ((temp_2 + srcrect.y) / 100) * 100 - srcrect.y + khung_dat_ve.y, 100, 100});
                            hover.h = std::min(khung_dat_ve.y + srcrect.h - hover.y, 50);
                            hover.w = std::min(khung_dat_ve.x + srcrect.w - hover.x, 50);
                            hover_c = {255, 219, 26};
                            current_hover_so_day = (temp_1 + srcrect.x) / 100;
                            current_hover_so_dong = (temp_2 + srcrect.y) / 100;
                            so_ve = (char)(current_hover_so_day + 'A') + std::to_string(current_hover_so_dong + 1);
                        }
                        else
                        {
                            current_hover_so_day = -1;
                            current_hover_so_dong = -1;
                            so_ve = "";
                        }
                    }
                    break;
                }
            }
            else
            {
                view_dat_ve.handle_event(e, mouse_X, mouse_Y);
            }
        }

        void create_buffer(ChuyenBay *cb)
        {
            if (flag)
            {
                ListVe &listve = cb->get_listve();
                int so_day = listve.get_so_day();
                int so_dong = listve.get_so_dong();

                buffer_ve = new Buffer();
                buffer_ve->set(this->myscreen, so_day * 100, so_dong * 100);
                buffer_ve->set_none_alpha();
                SDL_Rect rect;
                string so_ve;
                buffer_ve->connect_render_clear_white();
                for (int i = 0; i < so_day; i++)
                {
                    for (int j = 0; j < so_dong; j++)
                    {
                        rect = MyFunc::center_Rect(50, 50, {i * 100, j * 100, 100, 100});
                        SDL_Color color;
                        if (listve.check_empty(i, j))
                            color = {255, 255, 255};
                        else
                            color = {205, 92, 92};
                        myscreen->render_cot(rect, color);
                        so_ve = (char)(i + 'A') + std::to_string(j + 1);
                        myscreen->render_Text(so_ve, rect, {0, 0, 0}, true);
                    }
                }
                buffer_ve->disconnect_render();
                buffer_ve->set_vitri(khung_dat_ve.x, khung_dat_ve.y);
                srcrect = {0, 0, khung_dat_ve.w, khung_dat_ve.h};
                scroll.set_target(*buffer_ve, srcrect);
                flag = false;
            }
        }
        void render_list_ve(ChuyenBay *cb)
        {
            if (buffer_ve == nullptr)
            {
                cout << "Buffer Ve is NULL\n";
                return;
            }
            buffer_ve->render(true, srcrect);
        }
        void render_menu(ChuyenBay *cb)
        {
            this->target = cb;
            create_buffer(cb); // tạo buffer danh sách vé
            // render title
            SDL_Rect vt_text = {khung_dat_ve.x, khung_dat_ve.y - 100, khung_dat_ve.w, 100};
            myscreen->render_cot(vt_text, {255, 255, 255});
            string text = "Đặt vé Chuyến Bay " + string(cb->get_ma_so_cb());
            myscreen->render_Text(text.c_str(), vt_text, {0, 0, 0}, true);
            // end
            myscreen->render_cot(vien_khung_dat_ve, {0, 0, 0}, {0, 0, 0}); // render viền
            myscreen->render_cot(khung_dat_ve, {255, 255, 255});           // render khung đặt vé
            myscreen->render_cot(vt_nut_x, nut_x);                         // render nút back
            myscreen->render_Text("X", vt_nut_x, {0, 0, 0}, true);         // nút back
            this->render_list_ve(cb);                                      // render list vé
            myscreen->render_cot(hover, hover_c);                          // render vé đang hover
            myscreen->render_Text(so_ve, hover, {0, 0, 0}, true);
            scroll.render(*myscreen); // render scroll bar

            if (route == true)
                view_dat_ve.render(*myscreen);
        }
    };

    class XemHK
    {
    private:
        Global_Variable *global = nullptr;
        MyScreen *myscreen = nullptr;
        ChuyenBay *target = nullptr;

        SDL_Color nut_x = {255, 255, 255};
        SDL_Rect vt_nut_x = {0, 0, 0, 0};

        Buffer *buffer;

        bool flag = true; // re-render

        Scroll scroll;
        SDL_Rect srcrect = {0, 0, 0, 0}; // tạo scroll

        SDL_Rect hover = {0, 0, 50, 50};
        SDL_Color hover_c = {255, 255, 255};

        SDL_Rect khung;
        SDL_Rect vien;

    public:
        XemHK()
        {
            khung = MyFunc::center_Rect(1300, 500, {X_START_BODY, Y_START_BODY, W_BODY, H_BODY});
            vien = {khung.x - 2, khung.y - 2, khung.w + 4, khung.h + 4};
            vt_nut_x = {khung.x + khung.w - 50, khung.y - 200, 50, 50};
        }
        ~XemHK()
        {
            delete buffer;
        }
        void set(Global_Variable &global)
        {
            this->global = &global;
            this->myscreen = &(global.get_myscreen());
        }
        void handleEvent(SDL_Event e, Position &state, int mouse_X, int mouse_Y)
        {
            nut_x = {255, 255, 255};
            hover_c = {255, 255, 255};
            hover = {0, 0, 0, 0};

            scroll.handleEvent(e, mouse_X, mouse_Y);
            switch (e.type)
            {
            case SDL_MOUSEBUTTONDOWN: // sự kiện nhấn vào các box
                if (MyFunc::check_click(mouse_X, mouse_Y, vt_nut_x))
                {
                    flag = true;
                    delete buffer;
                    buffer = nullptr;
                    state = Position::HOME;
                }
                break;

            case SDL_MOUSEMOTION:
                if (MyFunc::check_click(mouse_X, mouse_Y, vt_nut_x))
                {
                    nut_x = {255, 219, 26};
                }
                break;
            }
        }
        void render_line(HanhKhach* hk, int stt, const char* sove){
            this->myscreen->render_Text(std::to_string(stt),{0,(stt-1)*50,150,50},{0,0,0},true);
            this->myscreen->render_Text(sove,{150,(stt-1)*50,150,50},{0,0,0},true);
            this->myscreen->render_Text(hk->getSoCMND(),{300,(stt-1)*50,300,50},{0,0,0},true);
            this->myscreen->render_Text(hk->getHo(),{600,(stt-1)*50,400,50},{0,0,0},true);
            this->myscreen->render_Text(hk->getTen(),{1000,(stt-1)*50,200,50},{0,0,0},true);
            this->myscreen->render_Text(hk->getPhai() ? "Nam":"Nữ",{1200,(stt-1)*50,100,50},{0,0,0},true);
        }

        void create_buffer(ChuyenBay *cb)
        {
            if (flag)
            {
                ListVe &listve = cb->get_listve();
                int so_day = listve.get_so_day();
                int so_dong = listve.get_so_dong();
                int total = listve.get_ve_da_ban();

                buffer = new Buffer();
                buffer->set(this->myscreen, khung.w, total * 50);
                SDL_Rect rect;
                string so_ve;
                HanhKhach* temp = nullptr;
                buffer->connect_render_clear();
                this->myscreen->render_cot({0,0,150,total * 50});
                this->myscreen->render_cot({150,0,150,total * 50});
                this->myscreen->render_cot({300,0,300,total * 50});
                this->myscreen->render_cot({600,0,400,total * 50});
                this->myscreen->render_cot({1000,0,200,total * 50});
                this->myscreen->render_cot({1200,0,100,total * 50});
                int stt = 0;
                for (int i = 0; i < so_day; i++)
                {
                    for (int j = 0; j < so_dong; j++)
                    {
                        rect = MyFunc::center_Rect(50, 50, {i * 100, j * 100, 100, 100});
                        if (!(listve.check_empty(i, j))){
                            stt++;
                            so_ve = (char)(i + 'A') + std::to_string(j + 1);
                            temp = global->get_list_hanhkhach().search(listve.get_cmnd(i,j));
                            this->render_line(temp,stt,so_ve.c_str());
                    }
                    }
                }
                buffer->disconnect_render();
                buffer->set_vitri(khung.x, khung.y);
                srcrect = {0, 0, khung.w, khung.h};
                scroll.set_target(*buffer, srcrect);
                flag = false;
            }
        }
        void render_list_hk(ChuyenBay *cb)
        {
            if (buffer == nullptr)
            {
                cout << "Buffer Ve is NULL\n";
                return;
            }
            buffer->render(true, srcrect);
        }
  
        void render_menu(ChuyenBay *cb)
        {
            this->target = cb;
            create_buffer(cb); // tạo buffer danh sách vé
            // render title
            SDL_Rect vt_text = {khung.x, khung.y - 200, khung.w, 200};
            myscreen->render_cot(vt_text, {255, 255, 255});
            string text_title = "DANH SÁCH HÀNH KHÁCH THUỘC CHUYẾN BAY " + string(cb->get_ma_so_cb());
            string text_time = "Ngày Giờ Khởi Hành: " + cb->get_thoi_gian_bay().to_string_dd_mm_yyyy_hh_mm();
            string text_noi_den = "Nơi Đến: " + string(cb->get_san_bay_den());
            myscreen->render_cot({vt_text.x,vt_text.y,vt_text.w,100},{255,255,255});
            myscreen->render_Text(text_title, {vt_text.x,vt_text.y,vt_text.w,50}, {0, 0, 0}, true);
            myscreen->render_Text(text_time, {vt_text.x,vt_text.y + 50,vt_text.w / 2,50}, {0, 0, 0}, true);
            myscreen->render_Text(text_noi_den, {vt_text.x + vt_text.w / 2,vt_text.y + 50,vt_text.w / 2,50}, {0, 0, 0}, true);
            
            


            myscreen->render_Text("STT",{khung.x,khung.y-50,150,50},{0,0,0},true);
            myscreen->render_Text("Số Vé",{khung.x + 150,khung.y-50,150,50},{0,0,0},true);
            myscreen->render_Text("Số CMND",{khung.x + 300,khung.y-50,300,50},{0,0,0},true);
            myscreen->render_Text("Họ",{khung.x + 600,khung.y-50,400,50},{0,0,0},true);
            myscreen->render_Text("Tên",{khung.x+1000,khung.y-50,200,50},{0,0,0},true);
            myscreen->render_Text("Giới Tính",{khung.x+ 1200,khung.y-50,100,50},{0,0,0},true);

            // end
            myscreen->render_cot(vien, {0, 0, 0}, {0, 0, 0}); // render viền
            myscreen->render_cot(khung, {255, 255, 255});           // render khung đặt vé
            myscreen->render_cot(vt_nut_x, nut_x);                         // render nút back
            myscreen->render_Text("X", vt_nut_x, {0, 0, 0}, true);         // nút back

            this->render_list_hk(cb);                                      // render list vé
            // myscreen->render_cot(hover, hover_c);                          // render vé đang hover

            scroll.render(*myscreen); // render scroll bar
        }
    };

}

#endif