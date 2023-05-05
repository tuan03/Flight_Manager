#ifndef VIEWS_PLANE_H
#define VIEWS_PLANE_H
#include "../header.h"
#include "component.h"

namespace Plane {
enum State {
    HOME,
    MENU,
    EDIT,
    DELETE,
    ADD
};

class Menu {
   private:
    MyScreen* myscreen = nullptr;
    Box* khung_menu = nullptr;
    SDL_Rect vi_tri_nut_x = {1250, 210, 50, 50};  // vị trí nút quit
    SDL_Color nut_xoa = {255, 255, 255};          // màu rgb
    SDL_Color nut_sua = {255, 255, 255};
    SDL_Color nut_x = {255, 255, 255};

    Box* edit = nullptr;
    Box* del = nullptr;

   public:
    void handleEvent(SDL_Event e, State& state, int mouse_X, int mouse_Y, bool& quit) {
        nut_xoa = {255, 255, 255};
        nut_sua = {255, 255, 255};
        nut_x = {255, 255, 255};
        switch (e.type) {
            case SDL_MOUSEMOTION:
                if (MyFunc::check_click(mouse_X, mouse_Y, vi_tri_nut_x)) {
                    nut_x = {255, 219, 26};
                } else if (edit->is_in_box(mouse_X, mouse_Y)) {
                    nut_sua = {255, 219, 26};
                } else if (del->is_in_box(mouse_X, mouse_Y)) {
                    nut_xoa = {255, 219, 26};
                }

                break;
            case SDL_MOUSEBUTTONDOWN:  // sự kiện nhấn vào các box
                if (MyFunc::check_click(mouse_X, mouse_Y, vi_tri_nut_x)) {
                    state = State::HOME;
                } else if (edit->is_in_box(mouse_X, mouse_Y)) {  //
                    state = State::EDIT;                         // chuyển sang trang edit
                } else if (del->is_in_box(mouse_X, mouse_Y)) {
                    cout << "Click xoa\n";  // xử lí sự kiện xóa
                }

                break;
            case SDL_QUIT:  // sự kiện nhất thoát
                quit = true;
                break;
        }
    }
    void set(MyScreen* mc, Box* khung_menu, Box* edit, Box* del) {
        this->myscreen = mc;
        this->khung_menu = khung_menu;
        this->edit = edit;
        this->del = del;
    }

    void render_menu(MayBay* mb, int vt) {
        // render khung menu
        SDL_Rect rect = {700, Y_START_TABLE + vt * 50 - 280, 300, 300};
        khung_menu->set_rect(rect);
        khung_menu->render(myscreen->get_my_renderer());
        // end

        SDL_Rect rect_2 = {rect.x + 75, rect.y + 60, 150, 60};
        edit->set_rect(rect_2);  // đặt vị trí theo khung menu
        rect_2.y += 30;
        this->vi_tri_nut_x = {960, rect_2.y, 50, 50};
        rect_2.y += 60;
        del->set_rect(rect_2);  // đặt vị trí theo khung menu
        this->render_button_xoa_sua_thoat();
    }
    void render_button_xoa_sua_thoat() {
        //
        myscreen->render_cot(del->get_rect(), nut_xoa);   // render nền
        myscreen->render_cot(edit->get_rect(), nut_sua);  // render nền
        // tại nút edit và xóa có nền trong suốt cho nên màu nên sẽ phụ thuộc lớp ô vuông ở phía dưới nó, cụ thể là 2 ô vuông ở trên

        this->edit->render(this->myscreen->get_my_renderer());  // render nút edit
        this->del->render(this->myscreen->get_my_renderer());   // render nút delete
        myscreen->render_cot(vi_tri_nut_x, nut_x);              // render nút thoát x
        myscreen->render_Text("X", vi_tri_nut_x, {0, 0, 0}, true);
    }
};
class Del {
   private:
    MyScreen* myscreen;
    /*
    stt -1
    so luong data -1
    ĐK: máy bay phải đang ko thực hiện chuyến bay
    */
   public:
};
class Edit {
   private:
    MyScreen* myscreen;
    Box* khung;
    Box* edit;
    SDL_Rect vi_tri_nut_x = {1250, 210, 50, 50};
    SDL_Rect vi_tri_nut_sua = {950, 450, 150, 60};
    SDL_Color nut_sua = {255, 255, 255};
    SDL_Color nut_x = {255, 255, 255};

    Input input_shmb;
    Input input_loaimb;
    Input input_soday;
    Input input_sodong;

    bool now = true;  // flag để gán 1 lần cho tất cả

    string name_field[4] = {"Số hiệu Máy Bay", "Loại", "Số Dãy", "Số Dòng"};
    SDL_Rect rect_field[4] = {{530, 300, 240, 50}, {530, 350, 240, 50}, {530, 400, 240, 50}, {530, 450, 240, 50}};
    SDL_Rect rect_input[4] = {{770, 300, 500, 50}, {770, 350, 500, 50}, {770, 400, 500, 50}, {770, 450, 500, 50}};
    int current_click_input = -1;

    string so_hieu_mb = "";
    string loai_mb = "";
    string so_day = "";
    string so_dong = "";

    bool da_lap_cb = false;

    ListMayBay* danh_sach_mb = nullptr;
    MayBay* mb_dc_chon = nullptr;

    bool* view_state = nullptr;

    Thong_Bao thong_bao;
    bool toast_result_option = false;

    bool escape_flag = false;

   public:
    void
    set(MyScreen* mc, Box* khung, BoxComponents& cpn_on_route, Box* edit, Flight_Manager* qlcb, bool* view_state) {
        this->view_state = view_state;
        this->danh_sach_mb = &qlcb->getListMB();
        this->thong_bao.set_box(&(cpn_on_route.thong_bao));
        this->myscreen = mc;
        this->khung = khung;
        khung->set_rect(300, 140, 1200, 600);
        this->vi_tri_nut_sua = {825, 515, 120, 60};
        this->edit = edit;

        input_shmb.connect(mc);
        input_loaimb.connect(mc);
        input_soday.connect(mc);
        input_sodong.connect(mc);

        input_shmb.connect_data(&so_hieu_mb, MAX_LENGTH_SO_HIEU_MB);
        input_loaimb.connect_data(&loai_mb, MAX_LENGTH_LOAI_MAY_BAY);
        input_soday.connect_data(&so_day, 3);
        input_sodong.connect_data(&so_dong, 3);

        input_shmb.set_vitri(rect_input[0]);
        input_loaimb.set_vitri(rect_input[1]);
        input_soday.set_vitri(rect_input[2]);
        input_sodong.set_vitri(rect_input[3]);
    }

    void handleEvent(SDL_Event e, State& state, int mouse_X, int mouse_Y, bool& quit) {
        nut_sua = {255, 255, 255};
        nut_x = {255, 255, 255};

        switch (e.type) {
            case SDL_MOUSEMOTION:
                if (MyFunc::check_click(mouse_X, mouse_Y, vi_tri_nut_x)) {
                    nut_x = {255, 219, 26};
                } else if (MyFunc::check_click(mouse_X, mouse_Y, vi_tri_nut_sua)) {
                    nut_sua = {255, 219, 26};
                }
                break;
            case SDL_MOUSEBUTTONDOWN:  // sự kiện nhấn vào các box
                this->current_click_input = -1;
                for (int i = 0; i < 4; i++) {
                    if (MyFunc::check_click(mouse_X, mouse_Y, rect_input[i])) {
                        this->current_click_input = i;
                        break;
                    }
                }
                if (MyFunc::check_click(mouse_X, mouse_Y, vi_tri_nut_x)) {
                    state = State::MENU;
                    this->now = true;
                    nut_sua = {255, 255, 255};
                    nut_x = {255, 255, 255};
                } else if (MyFunc::check_click(mouse_X, mouse_Y, vi_tri_nut_sua)) {  //>>> save change button
                    this->now = true;
                    this->escape_flag = true;
                }
                break;
            case SDL_QUIT:  // sự kiện nhất thoát
                quit = true;
                break;
        }

        input_loaimb.handleInput_IN_HOA_SO_KHONG_CACH(e, mouse_X, mouse_Y);
        input_soday.handleInput_IN_HOA_SO_KHONG_CACH(e, mouse_X, mouse_Y);
        input_sodong.handleInput_IN_HOA_SO_KHONG_CACH(e, mouse_X, mouse_Y);

        if (this->escape_flag) {
            thong_bao.set_mess("Ban co chac muon thay doi khong ?");
            thong_bao.on_warning();

            this->thong_bao.handleEvent(e, mouse_X, mouse_Y, quit, this->escape_flag);

            if (thong_bao.get_check_tb() == false) goto label;
            std::cout << ">>> run this\n";
            // Status is_error;
            // is_error = this->danh_sach_mb->edit(this->mb_dc_chon, this->mb_dc_chon->getLoaiMB(), this->mb_dc_chon->getSoDay(), this->mb_dc_chon->getSoDong());

            std::cout << ">>> input data loai mb >>> " << this->input_loaimb.get_data().c_str() << "\n";
            this->mb_dc_chon->setLoaiMB(this->input_loaimb.get_data().c_str());
            this->mb_dc_chon->setSoDay(stoi(this->input_soday.get_data()));
            this->mb_dc_chon->setSoDong(stoi(this->input_sodong.get_data()));
            *(this->view_state) = true;
            this->escape_flag = false;
        }
    label:;
    }

    void render_menu(MayBay* mb, Flight_Manager* qlcb) {
        this->mb_dc_chon = mb;
        myscreen->blur_background(150);
        khung->render(myscreen->get_my_renderer());
        this->edit->set_rect(this->vi_tri_nut_sua);

        if (this->now == true) {
            so_hieu_mb = mb->getSoHieuMB();
            loai_mb = mb->getLoaiMB();
            so_day = std::to_string(mb->getSoDay());
            so_dong = std::to_string(mb->getSoDong());

            this->da_lap_cb = qlcb->getListCB().find_by_sh_mb_v2(mb->getSoHieuMB());

            this->now = false;
        }

        for (int i = 0; i < 4; i++) {
            this->myscreen->render_Text(name_field[i], rect_field[i], {0, 0, 0}, true);
        }

        if (this->da_lap_cb) {
            this->myscreen->render_Text(loai_mb, rect_input[1], {0, 0, 0}, true);
        } else {
            input_loaimb.render();
        }

        this->myscreen->render_Text(so_hieu_mb, rect_input[0], {0, 0, 0}, true);
        input_soday.render();
        input_sodong.render();

        this->render_button_xoa_sua();

        this->thong_bao.render_warning(*(this->myscreen));  // render thong bao
    }
    void render_confirm_xoa() {
        SDL_Rect rect;
        rect = {700, 310, 400, 200};
        myscreen->render_cot(rect, COLOR_MENU_CHILD);
        myscreen->render_Text("Xác nhận xóa ?", rect, {0, 0, 0}, true);
    }

    void render_button_xoa_sua() {
        myscreen->render_cot(vi_tri_nut_sua, nut_sua);

        this->edit->render(this->myscreen->get_my_renderer());
        myscreen->render_cot(vi_tri_nut_x, nut_x);
        myscreen->render_Text("X", vi_tri_nut_x, {0, 0, 0}, true);
    }
};
class Add {
   private:
   public:
};
}  // namespace Plane

class View_Plane {
   private:
    int current_page;      // phân trang hiện tại
    Flight_Manager* qlcb;  //
    MyScreen* myscreen;    //
    Box* prev;             // nút prev
    Box* next;             // nút next
    Box* add = nullptr;    // nút add

    int mouse_X, mouse_Y;                     // vị trí chuột
    Plane::State state = Plane::State::HOME;  // mặc định ở Child_Route Home
    Plane::Menu menu_plane;                   // route menu
    Plane::Edit edit_plane;                   // route edit

    string so_hieu_mb = "";
    Input input_so_hieu_mb;

    MayBay* list_mb_dc_render[10];

    Buffer table;
    Buffer data;

    int vi_tri_hover_on_table = -1;  // vị trí hover trên table

    MayBay* temp = nullptr;  // lấy con trỏ máy bay ở vị trí đang hover rồi click

    int so_luong_data = 0;  // số lượng máy bay

    int route_plane_width[5]{150, 250, 600, 250, 250};
    string route_plane_name_cot[6]{"STT", "Số Hiệu MB", "Loại", "Số Dãy", "Số Dòng"};

    bool view_state = false;

   public:
    View_Plane(Flight_Manager* qlcb, MyScreen* myscreen, BoxComponents* bc) {
        this->qlcb = qlcb;
        this->myscreen = myscreen;
        current_page = 1;
        this->prev = &(bc->prev);
        this->next = &(bc->next);

        menu_plane.set(myscreen, &(bc->khung_menu), &(bc->edit), &(bc->del));
        edit_plane.set(myscreen, &(bc->khung_add_edit), *bc, &(bc->edit), this->qlcb, &(this->view_state));

        table.set(myscreen, WIDTH_TABLE, HEIGHT_TABLE + 50);
        table.set_vitri(X_START_TABLE, Y_START_TABLE - 50);
        this->createTable();

        data.set(myscreen, WIDTH_TABLE, HEIGHT_TABLE);
        data.set_vitri(X_START_TABLE, Y_START_TABLE);
        this->getData();

        input_so_hieu_mb.connect(this->myscreen);
        input_so_hieu_mb.connect_data(&(this->so_hieu_mb), MAX_LENGTH_SO_HIEU_MB);
        input_so_hieu_mb.set_vitri({300, 175, 300, 50});

        this->add = &(bc->add);
        this->add->set_rect(X_START_BODY + 1700 - 150, Y_START_BODY, 150, 60);
    }

    void handleEvent(SDL_Event e, Name_Box& current_route, ListBox& menu, bool& is_home, bool& quit) {
        if (e.type == SDL_MOUSEMOTION) SDL_GetMouseState(&mouse_X, &mouse_Y);
        if (this->state == Plane::State::HOME) {
            is_home = true;
            switch (e.type) {
                case SDL_MOUSEMOTION:
                    this->vi_tri_hover_on_table = this->get_vitri(this->mouse_X, this->mouse_Y, qlcb->getListMB().get_so_luong());  // 0 - 9
                    break;
                case SDL_MOUSEBUTTONDOWN:  // sự kiện nhấn vào các box
                                           // bắt sự kiện nhấn next và prev
                    if (current_page > 1 && prev->is_in_box(mouse_X, mouse_Y)) {
                        this->current_page -= 1;
                        getData();
                    }
                    if (current_page < ((this->so_luong_data - 1) / 10) + 1 && next->is_in_box(mouse_X, mouse_Y)) {
                        current_page += 1;
                        getData();
                    }
                    // end handle

                    if (this->vi_tri_hover_on_table != -1) {  // nếu nhấn vào, mà đnag hover vào line trong table thì bật menu.
                        this->temp = this->list_mb_dc_render[vi_tri_hover_on_table];
                        this->state = Plane::State::MENU;
                    }
                    break;

                case SDL_QUIT:  // sự kiện nhất thoát
                    quit = true;
                    break;
            }

            input_so_hieu_mb.handleInput_IN_HOA_SO_KHONG_CACH(e, mouse_X, mouse_Y);
            if (e.type == SDL_KEYDOWN || e.type == SDL_TEXTINPUT) getData();

        } else {
            is_home = false;
            if (state == Plane::State::MENU) {
                menu_plane.handleEvent(e, this->state, mouse_X, mouse_Y, quit);
            } else if (state == Plane::State::EDIT) {
                edit_plane.handleEvent(e, this->state, mouse_X, mouse_Y, quit);
            }
        }
    }
    void createTable() {
        table.connect_render_clear();
        myscreen->render_table(5, route_plane_width, route_plane_name_cot);
        table.disconnect_render();
    }
    void getData() {
        data.connect_render_clear();
        int so_may_bay = this->qlcb->getListMB().get_so_luong();
        int start = (this->current_page - 1) * 10;
        int end = start + 9;  // 0 - 9 là 10
        int stt = 0;
        int so_line_render = 0;
        MayBay* mb = nullptr;
        int index = 0;
        for (int i = 0; i < so_may_bay; i++) {
            mb = this->qlcb->getListMB().get_at(i);
            if (Func_Global::check_prefix(mb->getSoHieuMB(), this->so_hieu_mb.c_str())) {
                if (stt >= start && stt <= end) {
                    this->list_mb_dc_render[index] = mb;
                    index++;
                    this->render_line_data(stt, start, mb);
                    so_line_render++;
                }
                stt++;
                // if(stt == end+1){
                //     break;
                // }
            }
        }
        this->so_luong_data = stt;
        if (so_line_render == 0) {
            this->myscreen->render_Text("Trống !!!", {X_START_TABLE, Y_START_TABLE, WIDTH_TABLE, HEIGHT_TABLE}, {255, 0, 0}, true);
        }
        data.disconnect_render();

        this->view_state = false;
    }
    void render() {
        if (view_state) this->getData();  // theo dõi sự thay đổi máy bay trong danh sách máy bay

        table.render();  // render table
        if (vi_tri_hover_on_table != -1) {
            myscreen->render_cot({X_START_TABLE, Y_START_TABLE + (vi_tri_hover_on_table)*50, WIDTH_TABLE, 50}, {159, 212, 171});
            // this->temp = mb;
        }

        data.render();  // render data

        this->add->render(this->myscreen->get_my_renderer());  // render nút add

        // this->render_data(); // render bảng dữ liệu

        this->render_next_prev();               // render nút next và prev
        SDL_Rect rect_temp{150, 175, 150, 50};  // ô input : 300,175,300,50
        this->myscreen->render_Text("Số Hiệu MB:", rect_temp, {0, 0, 0}, true);
        input_so_hieu_mb.render();  // render ô input nhập số hiệu máy bay

        if (state == Plane::State::MENU) {
            menu_plane.render_menu(temp, vi_tri_hover_on_table);
        } else if (state == Plane::State::EDIT) {
            edit_plane.render_menu(temp, this->qlcb);
        }
    }
    int get_vitri(int x, int y, int so_luong) {  // vị trí con trỏ chuột trỏ đến / trả về dòng trong bảng dữ liệu
        if (x >= X_START_TABLE && x <= X_START_TABLE + WIDTH_TABLE && y >= Y_START_TABLE && y <= Y_START_TABLE + HEIGHT_TABLE) {
            int vitri = (y - Y_START_TABLE) / 50;
            if (current_page == (so_luong / 10) + 1) {
                if (vitri < so_luong % 10) {
                    return vitri;
                }
            } else {
                return vitri;
            }
        }
        return -1;
    }

    void render_next_prev() {
        SDL_Rect rect;
        next->render(myscreen->get_my_renderer(), next->is_in_box(mouse_X, mouse_Y) ? 1 : 0);
        prev->render(myscreen->get_my_renderer(), prev->is_in_box(mouse_X, mouse_Y) ? 1 : 0);
        rect = {840, 825, 120, 50};
        myscreen->render_Text(std::to_string(current_page) + "/" + std::to_string(((this->so_luong_data - 1) / 10) + 1), rect, {0, 0, 0, 255}, true);
    }

    void render_line_data(int stt, int start, MayBay* mb) {
        SDL_Rect rect;
        rect = {0, 0 + (stt - start) * 50, route_plane_width[0], 50};
        this->myscreen->render_Text(std::to_string((stt) + 1), rect, {0, 0, 0, 255}, true);

        rect.x += rect.w;
        rect.w = route_plane_width[1];
        this->myscreen->render_Text(mb->getSoHieuMB(), rect, {0, 0, 0, 255}, true);

        rect.x += rect.w;
        rect.w = route_plane_width[2];
        this->myscreen->render_Text(mb->getLoaiMB(), rect, {0, 0, 0, 255}, true);

        rect.x += rect.w;
        rect.w = route_plane_width[3];
        this->myscreen->render_Text(std::to_string(mb->getSoDay()), rect, {0, 0, 0, 255}, true);

        rect.x += rect.w;
        rect.w = route_plane_width[4];
        this->myscreen->render_Text(std::to_string(mb->getSoDong()), rect, {0, 0, 0, 255}, true);
    }
};

#endif