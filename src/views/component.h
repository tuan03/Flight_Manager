#ifndef VIEWS_COMPONENT_H
#define VIEWS_COMPONENT_H
#include "../header.h"

class Input {
   private:
    MyScreen* myscreen;
    string* data;
    int max_length = 0;
    bool is_clicked = false;
    bool ok_warning = true;
    SDL_Rect vitri;

   public:
    string get_data() { return *data; }
    int get_data_in_number() { return stoi(*data); }

    void set(bool logic) {
        this->ok_warning = logic;
    }
    void handleInput_IN_HOA_SO_KHONG_CACH(SDL_Event e, int x, int y) {
        if (ok_warning && e.type == SDL_MOUSEBUTTONDOWN) this->is_clicked = MyFunc::check_click(x, y, this->vitri);
        if (this->is_clicked) {
            switch (e.type) {
                case SDL_KEYDOWN:
                    if (e.key.keysym.sym == SDLK_BACKSPACE && (*data).length() > 0) {
                        (*data).pop_back();
                    }
                    break;
                case SDL_TEXTINPUT:
                    if ((*data).length() < max_length) {
                        if (e.text.text[0] >= '0' && e.text.text[0] <= '9')
                            *data += e.text.text;
                        else if (e.text.text[0] >= 'A' && e.text.text[0] <= 'Z')
                            *data += e.text.text;
                        else if (e.text.text[0] >= 'a' && e.text.text[0] <= 'z')
                            *data += e.text.text[0] - ('a' - 'A');
                    }
                    break;
            }
        }
    }

    void connect(MyScreen* mc) {
        this->myscreen = mc;
    }
    void connect_data(string* str, int max_length) {
        this->data = str;
        this->max_length = max_length;
    }
    void set_vitri(SDL_Rect rect) {
        this->vitri = rect;
    }
    void render() {
        SDL_Rect box_input{vitri.x + 3, vitri.y + 3, vitri.w - 6, vitri.h - 6};
        myscreen->render_cot(vitri, {0, 0, 0});
        if (this->is_clicked)
            myscreen->render_cot(box_input);
        else
            myscreen->render_cot(box_input, {255, 255, 255});
        SDL_Rect con_tro;
        myscreen->render_Text(*data, box_input, {0, 0, 0}, true, &con_tro);
        if (this->is_clicked) {
            con_tro.x = con_tro.x + con_tro.w + 2;
            con_tro.w = 2;
            myscreen->render_cot(con_tro);
        }
    }
};

class Thong_Bao {
   private:
    string mess = "";
    Box* man_thong_bao = nullptr;
    SDL_Rect ok_warning{980, 700, 200, 50};  // ok2
    SDL_Rect huy{600, 700, 200, 50};
    SDL_Color c_ok = {255, 255, 255};
    SDL_Color c_huy = {255, 255, 255};
    SDL_Rect ok_error{790, 700, 200, 50};
    bool check_tb = false;

    bool is_turn_on_warning = false;
    bool is_turn_on_error = false;

   public:
    void set_box(Box* box) {
        this->man_thong_bao = box;
    }
    void set_mess(string mess) {
        this->mess = mess;
    }
    void on_warning() {
        this->check_tb = false;
        this->is_turn_on_warning = true;
    }
    void on_error() {
        this->check_tb = false;
        this->is_turn_on_error = true;
    }
    bool get_check_tb() {
        return this->check_tb;
    }
    void handleEvent(SDL_Event e, int mouse_X, int mouse_Y, bool& quit, bool& escape_flag) {
        c_ok = {255, 255, 255};
        c_huy = {255, 255, 255};
        switch (e.type) {
            case SDL_MOUSEMOTION:
                if (MyFunc::check_click(mouse_X, mouse_Y, ok_warning)) {
                    c_ok = {255, 219, 26};
                } else if (MyFunc::check_click(mouse_X, mouse_Y, huy)) {
                    c_huy = {255, 219, 26};
                }
                break;
            case SDL_MOUSEBUTTONDOWN:  // sự kiện nhấn vào các box
                if (MyFunc::check_click(mouse_X, mouse_Y, ok_error)) {
                    this->is_turn_on_error = false;
                } else if (MyFunc::check_click(mouse_X, mouse_Y, ok_warning)) {
                    this->is_turn_on_warning = false;
                    this->check_tb = true;
                } else if (MyFunc::check_click(mouse_X, mouse_Y, huy)) {
                    this->is_turn_on_warning = false;
                    this->is_turn_on_error = false;
                    escape_flag = false;
                }
                break;
            case SDL_QUIT:  // sự kiện nhất thoát
                quit = true;
                break;
        }
    }
    // void render_error(MyScreen& myscreen) {
    //     if (this->is_turn_on_error) {
    //         man_thong_bao->render(myscreen.get_my_renderer());
    //         myscreen.render_cot(ok_error, {255, 255, 255});
    //         myscreen.render_Text("Đồng Ý", ok_error, {0, 0, 0}, true);
    //         myscreen.render_Text(this->mess, man_thong_bao->get_rect(), {0, 0, 0}, true);
    //     }
    // }
    void render_warning(MyScreen& myscreen) {
        if (this->is_turn_on_warning) {
            man_thong_bao->render(myscreen.get_my_renderer());
            myscreen.render_cot(ok_warning, c_ok);
            myscreen.render_Text("Đồng Ý", ok_warning, {0, 0, 0}, true);
            myscreen.render_cot(huy, c_huy);
            myscreen.render_Text("Hủy", huy, {0, 0, 0}, true);
            myscreen.render_Text(this->mess, man_thong_bao->get_rect(), {0, 0, 0}, true);
        }
    }
};

class Render_Data {
   private:
   public:
    Render_Data() {
    }
};

struct BoxComponents {
    Box prev;
    Box next;
    Box plane_at_homepage;
    Box khung_menu;
    Box edit;
    Box add;
    Box del;
    Box khung_add_edit;
    Box thong_bao;
};
#endif