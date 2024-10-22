#ifndef VIEWS_COMPONENT_H
#define VIEWS_COMPONENT_H
#include "../header.h"
/**
 * @brief Method in file component.h
 *
 */
namespace Func_Render
{

}

class Choose
{
private:
    MyScreen *myscreen;
    bool data = false;
    Box *v1 = nullptr;
    Box *v2 = nullptr;
    SDL_Rect vt{0, 0, 0, 0};

public:
    bool get_data()
    {
        return data;
    }
    void set_data(bool dt)
    {
        this->data = dt;
    }
    void connect(MyScreen *mc)
    {
        this->myscreen = mc;
    }
    void set_box(Box *b1, Box *b2)
    {
        v1 = b1;
        v2 = b2;
    }
    void set_vitri(SDL_Rect rect)
    {
        vt = rect;
    }
    bool handle_choose(SDL_Event e, int x, int y)
    {
        if (e.type == SDL_MOUSEBUTTONDOWN)
        {
            if (MyFunc::check_click(x, y, vt))
            {
                data = !data;
                return true;
            }
        }
        return false;
    }
    void render()
    {
        v1->set_rect(vt);
        v2->set_rect(vt);
        if (!data)
        {
            v1->render(myscreen->get_my_renderer());
        }
        else
        {
            v2->render(myscreen->get_my_renderer());
        }
    }
};

class Input
{
private:
    MyScreen *myscreen;
    string data = "";
    string note = "";
    int max_length = 0;
    bool is_clicked = false;
    SDL_Rect vitri;

public:
    string get_data() { return data; }
    bool is_empty()
    {
        return data.length() == 0;
    }
    void handleInput_ID(SDL_Event e, int x, int y)
    { // dùng để nhập ID. có thể nhập chữ cái in hoa, số - không được phép : dấu cách và kí tự đặc biệt
        if (e.type == SDL_MOUSEBUTTONDOWN)
            this->is_clicked = MyFunc::check_click(x, y, this->vitri);
        if (this->is_clicked)
        {
            switch (e.type)
            {
            case SDL_KEYDOWN:
                if (e.key.keysym.sym == SDLK_BACKSPACE && (data).length() > 0)
                {
                    (data).pop_back();
                }
                break;
            case SDL_TEXTINPUT:
                if ((data).length() < max_length)
                {
                    if (e.text.text[0] >= '0' && e.text.text[0] <= '9')
                        data += e.text.text;
                    else if (e.text.text[0] >= 'A' && e.text.text[0] <= 'Z')
                        data += e.text.text;
                    else if (e.text.text[0] >= 'a' && e.text.text[0] <= 'z')
                        data += e.text.text[0] - ('a' - 'A');
                }
                break;
            }
        }
    }
    void handleInput_Name(SDL_Event e, int x, int y)
    { // dùng để nhập Tên, Kiểu, được phép số (chỉ 1 kc giữa 2 từ, viết hoa ở đầu) - không được phép :kí tự đặc biệt
        if (e.type == SDL_MOUSEBUTTONDOWN)
            this->is_clicked = MyFunc::check_click(x, y, this->vitri);
        if (this->is_clicked)
        {
            switch (e.type)
            {
            case SDL_KEYDOWN:
                if (e.key.keysym.sym == SDLK_BACKSPACE && (data).length() > 0)
                {
                    (data).pop_back();
                }
                break;
            case SDL_TEXTINPUT:
                if ((data).length() < max_length)
                {
                    if ((e.text.text[0] >= 'A' && e.text.text[0] <= 'Z') || (e.text.text[0] >= 'a' && e.text.text[0] <= 'z'))
                    {
                        if (data.length() == 0 || (data.length() > 0 && (data)[(data.length() - 1)] == ' '))
                        {
                            data += std::toupper(e.text.text[0]);
                        }
                        else
                        {
                            data += std::tolower(e.text.text[0]);
                        }
                    }
                    else if (e.text.text[0] == ' ' && (data.length() > 0 && (data)[(data.length() - 1)] != ' '))
                        data += e.text.text[0];
                    else if (e.text.text[0] >= '0' && e.text.text[0] <= '9')
                        data += e.text.text;
                }
                break;
            }
        }
    }
    void handleInput_Num(SDL_Event e, int x, int y)
    { // chỉ có thể nhập số
        if (e.type == SDL_MOUSEBUTTONDOWN)
            this->is_clicked = MyFunc::check_click(x, y, this->vitri);
        if (this->is_clicked)
        {
            switch (e.type)
            {
            case SDL_KEYDOWN:
                if (e.key.keysym.sym == SDLK_BACKSPACE && (data).length() > 0)
                {
                    (data).pop_back();
                }
                break;
            case SDL_TEXTINPUT:
                if ((data).length() < max_length)
                {
                    if (e.text.text[0] >= '0' && e.text.text[0] <= '9')
                        data += e.text.text;
                }
                break;
            }
        }
    }

    
    
    const char * chuan_hoa()
    {
        int end = data.length() - 1;
        while (end > 0 && data[end] == ' ')
        {
            end--;
        }

        this->data = data.substr(0, end + 1);
        return this->data.c_str();
    }

    int get_num()
    {
        int value;
        try
        {
            value = stoi(this->data);
        }
        catch (exception &e)
        {
            value = 0;
        }
        return value;
    }

    void set(MyScreen *mc, int max_length, SDL_Rect vt)
    {
        this->myscreen = mc;
        this->max_length = max_length;
        this->vitri = vt;
    }
    bool get_is_click()
    {
        return this->is_clicked;
    }
    void connect(MyScreen *mc)
    {
        this->myscreen = mc;
    }
    SDL_Rect get_rect()
    {
        return vitri;
    }
    void reset_data()
    {
        this->data = "";
    }
    void set_max_length(int max_length)
    {
        this->max_length = max_length;
    }
    void set_data(string data)
    {
        this->data = data;
    }
    void set_note(string data)
    {
        this->note = data;
    }
    void set_vitri(SDL_Rect rect)
    {
        this->vitri = rect;
    }
    void render()
    {
        if (this->myscreen == nullptr)
            throw "MyScreen Input is NULL\n";
        SDL_Rect box_input{vitri.x + 3, vitri.y + 3, vitri.w - 6, vitri.h - 6};
        myscreen->render_cot(vitri, {0, 0, 0});
        if (this->is_clicked)
            myscreen->render_cot(box_input);
        else
            myscreen->render_cot(box_input, {255, 255, 255});
        SDL_Rect con_tro;
        if (this->data.length() != 0)
        {
            myscreen->render_Text(data, box_input, {0, 0, 0}, true, &con_tro);
        }
        else
        {
            myscreen->render_Text(data, box_input, {0, 0, 0}, true, &con_tro);
            myscreen->render_Text(note, box_input, {128, 128, 128}, true);
        }
        if (this->is_clicked)
        {
            con_tro.x = con_tro.x + con_tro.w + 2;
            con_tro.w = 2;
            myscreen->render_cot(con_tro);
        }
    }
};

class Thong_Bao
{
private:
    string mess = "";
    Box *man_thong_bao = nullptr;
    SDL_Rect ok{790, 700, 200, 50};
    SDL_Color c_ok = {255, 255, 255};

    SDL_Rect vt_next{790 + 200, 700, 200, 50};
    SDL_Color c_next = {255, 255, 255};
    SDL_Rect vt_huy{790 - 200, 700, 200, 50};
    SDL_Color c_huy = {255, 255, 255};

    MyScreen *myscreen = nullptr;

    bool flag = false;
    bool value = false;

    bool type = true; // true: thông báo status, false : thông báo cảnh báo

public:
    void connect_screen(MyScreen &myscreen)
    {
        this->myscreen = &myscreen;
    }
    void set_box(Box *box)
    {
        this->man_thong_bao = box;
    }
    void set_mess(string mess)
    {
        this->mess = mess;
    }
    void reset_value()
    {
        this->value = false;
    }
    void on(bool type = true) // bật thông báo trạng thái
    {
        this->flag = true;
        this->type = type;
        if (type)
            this->value = false;
    }

    bool get_value()
    { // true : bấm đồng ý, false : bấm hủy
        return value;
    }
    bool is_display()
    {
        return flag;
    }
    void handleEvent(SDL_Event e, int mouse_X, int mouse_Y)
    {
        c_ok = {255, 255, 255};
        c_next = {255, 255, 255};
        c_huy = {255, 255, 255};
        switch (e.type)
        {
        case SDL_MOUSEMOTION:
            if (type)
            {
                if (MyFunc::check_click(mouse_X, mouse_Y, ok))
                {
                    c_ok = {255, 219, 26};
                }
            }
            else
            {
                if (MyFunc::check_click(mouse_X, mouse_Y, vt_next))
                {
                    c_next = {255, 219, 26};
                }
                if (MyFunc::check_click(mouse_X, mouse_Y, vt_huy))
                {
                    c_huy = {255, 219, 26};
                }
            }
            break;
        case SDL_MOUSEBUTTONDOWN: // sự kiện nhấn vào các box
            if (type)
            {
                if (MyFunc::check_click(mouse_X, mouse_Y, ok))
                {
                    flag = false;
                }
            }
            else
            {
                if (MyFunc::check_click(mouse_X, mouse_Y, vt_next))
                {
                    value = true;
                    flag = false;
                }
                if (MyFunc::check_click(mouse_X, mouse_Y, vt_huy))
                {
                    value = false;
                    flag = false;
                }
            }
            break;
        }
    }
    void render()
    {
        if (flag)
        {
            if (myscreen == nullptr)
                throw "MyScreen is NULL\n";
            man_thong_bao->render(myscreen->get_my_renderer());
            if (type)
            {
                myscreen->render_cot(ok, c_ok);
                myscreen->render_Text("Đồng Ý", ok, {0, 0, 0}, true);
            }
            else
            {
                myscreen->render_cot(vt_next, c_next);
                myscreen->render_Text("Tiếp Tục", vt_next, {0, 0, 0}, true);
                myscreen->render_cot(vt_huy, c_huy);
                myscreen->render_Text("Hủy", vt_huy, {0, 0, 0}, true);
            }
            int dem = 0;
            stringstream str(this->mess);
            string t;
            while(getline(str,t)){
                dem++;
            }
            SDL_Rect rect = man_thong_bao->get_rect();
            rect.h = rect.h/dem;
            stringstream str2(this->mess);
            string k;
            while(getline(str2,k)){
                myscreen->render_Text(k, rect, {0, 0, 0}, true);
                rect.y += rect.h;
            }
            
        }
    }
};

class Render_Data
{
private:
public:
    Render_Data()
    {
    }
};

/**
 * @note Buộc phải gọi hàm Load_img trước
 *
 */
struct Child_Component
{
    Box pick;
    Box unpick;
    Box logo_ptit; // máy bay ở homepage
    Box logo_maybay;
    Box prev;              // nút Prev
    Box next;              // nút Next
    Box edit;              // nút edit
    Box add;               // nút add
    Box del;               // nút xóa
    Box khung_menu;        // khung menu
    Box khung_add_edit;    // khung để add hoặc edit
    Box thong_bao;         // khung thông báo
    void load_img(MyScreen &myscreen)
    {
        logo_ptit.create("src/views/img/Logo_PTIT.png", myscreen.get_my_renderer()); // rename
        logo_ptit.set_rect(10 + X_START_BODY, 10 + Y_START_BODY, 240, 240);

        logo_maybay.create("src/views/img/maybay.png", myscreen.get_my_renderer()); // rename
        logo_maybay.set_rect(1200 + X_START_BODY, 150 + Y_START_BODY, 355, 355);

        // prev
        prev.create("src/views/img/prev.png", myscreen.get_my_renderer()); // renanme
        prev.set_rect(760, 815, 80, 80);
        prev.set_hover("src/views/img/prev1.png", myscreen.get_my_renderer());
        // end prev

        // start next
        next.create("src/views/img/next.png", myscreen.get_my_renderer());
        next.set_rect(960, 815, 80, 80);
        next.set_hover("src/views/img/next1.png", myscreen.get_my_renderer());
        // end next

        edit.create("src/views/img/edit.png", myscreen.get_my_renderer());
        add.create("src/views/img/add.png", myscreen.get_my_renderer());
        add.set_rect(X_START_BODY + 1700 - 150, Y_START_BODY, 150, 60);
        del.create("src/views/img/del.png", myscreen.get_my_renderer());

        pick.create("src/views/img/chon.png", myscreen.get_my_renderer());
        unpick.create("src/views/img/bt.png", myscreen.get_my_renderer());

        khung_menu.create("src/views/img/khung_menu.png", myscreen.get_my_renderer());
        khung_add_edit.create("src/views/img/khung.png", myscreen.get_my_renderer());
        SDL_Rect vt_khung_add_edit = MyFunc::center_Rect(850, 450, {X_START_BODY, Y_START_BODY, 1700, 580});
        khung_add_edit.set_rect(vt_khung_add_edit);
        thong_bao.create("src/views/img/thong_bao.png", myscreen.get_my_renderer());
        thong_bao.set_rect(vt_khung_add_edit);
    }

    void render_next_prev(int mouse_X, int mouse_Y, int current_page, int so_luong_data, MyScreen *myscreen) // render ra 2 nút next và prev và số phân trang ở phân trang
    {
        SDL_Rect rect;
        this->next.render(myscreen->get_my_renderer(), this->next.is_in_box(mouse_X, mouse_Y) ? 1 : 0);
        this->prev.render(myscreen->get_my_renderer(), this->prev.is_in_box(mouse_X, mouse_Y) ? 1 : 0);
        rect = {840, 825, 120, 50};
        myscreen->render_Text(std::to_string(current_page) + "/" + std::to_string(((so_luong_data - 1) / 10) + 1), rect, {0, 0, 0, 255}, true);
    }
};

class Global_Variable
{
private:
    Child_Component c_components;
    MyScreen myscreen;
    Flight_Manager qlcb;
    Thong_Bao thong_bao;

public:
    Global_Variable() : myscreen{WIDTH_SCREEN, HEIGHT_SCREEN, "Quản Lí Chuyến Bay", "src/views/font/Arial.ttf", 24}
    {
        c_components.load_img(myscreen);
        // end
        thong_bao.connect_screen(myscreen);
        thong_bao.set_box(&(c_components.thong_bao));
    }
    ListChuyenBay &get_list_flight()
    {
        return this->qlcb.getListCB();
    }
    ListMayBay &get_list_plane()
    {
        return this->qlcb.getListMB();
    }
    TreeHanhKhach &get_list_hanhkhach()
    {
        return this->qlcb.getListHK();
    }
    MyScreen &get_myscreen()
    {
        return myscreen;
    }
    Flight_Manager &get_qlcb()
    {
        return qlcb;
    }
    Thong_Bao &get_thong_bao()
    {
        return thong_bao;
    }
    Child_Component &get_c_component()
    {
        return c_components;
    }
};

#endif