#ifndef VIEWS_PLANE_H
#define VIEWS_PLANE_H
#include "../header.h"
#include "component.h"
namespace Plane
{
    enum Position
    {
        HOME,
        MENU,
        EDIT,
        DELETE,
        ADD
    };

    class Menu
    {
    private:
        Global_Variable* global = nullptr;

        SDL_Color nut_xoa = {255, 255, 255}; // màu rgb
        SDL_Color nut_sua = {255, 255, 255};
        MayBay* current = nullptr;
        bool* flag_re_render_in_home = nullptr;

        Box* khung_menu = nullptr; 
        Box* edit = nullptr; 
        Box* del = nullptr;
        MyScreen* myscreen = nullptr;
    public:
     void set(Global_Variable& global,bool* flag)
        {
            this->flag_re_render_in_home = flag;
            this->global = &global;


            khung_menu = &(global.get_c_component().khung_menu); //tuannnnn
            edit = &(global.get_c_component().edit); 
            del = &(global.get_c_component().del);
            myscreen = &(global.get_myscreen());


        }


        void handleEvent(SDL_Event e, Position &state, int mouse_X, int mouse_Y)
        {
            nut_xoa = {255, 255, 255};
            nut_sua = {255, 255, 255};
            switch (e.type)
            {
            case SDL_MOUSEMOTION:
                if (edit->is_in_box(mouse_X, mouse_Y))
                {
                    nut_sua = {255, 219, 26};
                }
                else if (del->is_in_box(mouse_X, mouse_Y))
                {
                    nut_xoa = {255, 219, 26};
                }
                break;
            case SDL_MOUSEBUTTONDOWN:                                                // sự kiện nhấn vào các box
                if (!khung_menu->is_in_box(mouse_X, mouse_Y)) // bấm bên ngoài menu sẽ thoát
                {
                    state = Position::HOME;
                }
                else if (edit->is_in_box(mouse_X, mouse_Y)) // nhấn vào Box edit
                {                                                                  //
                    state = Position::EDIT;                                        // chuyển sang trang edit
                }
                else if (del->is_in_box(mouse_X, mouse_Y)) // nhấn vào Box xóa
                {
                    Status result;
                    result = this->global->get_qlcb().del_mb(this->current->getSoHieuMB());
                    global->get_thong_bao().set_mess(result.mess);
                    global->get_thong_bao().on();
                    if (result.get_status() == Status_Name::SUCCESS)
                    {
                        *(this->flag_re_render_in_home) = true;
                        state = Position::HOME;
                    }
                    
                }
                break;
            }
        }
       

        void render_menu(MayBay *mb, int vt)
        {
            


            this->current = mb;
            // render khung menu
            SDL_Rect rect = {700, Y_START_TABLE + vt * 50 - 280, 300, 300};
            khung_menu->set_rect(rect);
            khung_menu->render(myscreen->get_my_renderer());
            // end

            SDL_Rect rect_2 = {rect.x + 75, rect.y + 60, 150, 60};
            edit->set_rect(rect_2); // đặt vị trí theo khung menu
            rect_2.y += 30;
            rect_2.y += 60;
            del->set_rect(rect_2); // đặt vị trí theo khung menu
            this->render_button_xoa_sua_thoat();
        }
        void render_button_xoa_sua_thoat()
        {

            //
            myscreen->render_cot(del->get_rect(), nut_xoa);  // render nền
            myscreen->render_cot(edit->get_rect(), nut_sua); // render nền
            // tại nút edit và xóa có nền trong suốt cho nên màu nên sẽ phụ thuộc lớp ô vuông ở phía dưới nó, cụ thể là 2 ô vuông ở trên

            edit->render(myscreen->get_my_renderer()); // render nút edit
            del->render(myscreen->get_my_renderer());  // render nút delete
        }
    };
    class Edit
    {
    private:
        Global_Variable* global = nullptr;

        SDL_Rect vi_tri_nut_x = {1250, 210, 50, 50};
        SDL_Rect vi_tri_nut_sua = {950, 450, 150, 60};
        SDL_Color nut_sua = {255, 255, 255};
        SDL_Color nut_x = {255, 255, 255};

        Input input_shmb;
        Input input_loaimb;
        Input input_soday;
        Input input_sodong;

        bool now = true; // flag để gán 1 lần cho tất cả

        string name_field[4] = {"Số hiệu Máy Bay", "Loại", "Số Dãy", "Số Dòng"};
        SDL_Rect rect_field[4] = {{530, 300, 240, 50}, {530, 350, 240, 50}, {530, 400, 240, 50}, {530, 450, 240, 50}};
        SDL_Rect rect_input[4] = {{770, 300, 500, 50}, {770, 350, 500, 50}, {770, 400, 500, 50}, {770, 450, 500, 50}};
        int current_click_input = -1;

        bool da_lap_cb = false;

        MayBay *target_maybay = nullptr;

        bool *flag_re_render_in_home = nullptr;

        MyScreen* myscreen = nullptr;
        Box* khung_add_edit = nullptr;
    public:
        void
        set(Global_Variable& global, bool *flag)
        {
            this->global = &global;
            this->myscreen = &(global.get_myscreen());
            khung_add_edit = &(global.get_c_component().khung_add_edit);


            this->flag_re_render_in_home = flag;
            this->vi_tri_nut_sua = {825, 515, 120, 60};

            input_shmb.set(&(global.get_myscreen()),MAX_LENGTH_SO_HIEU_MB,rect_input[0]);
            input_loaimb.set(&(global.get_myscreen()),MAX_LENGTH_LOAI_MAY_BAY,rect_input[1]);
            input_soday.set(&(global.get_myscreen()),2,rect_input[2]);
            input_sodong.set(&(global.get_myscreen()),2,rect_input[3]);

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
                    this->target_maybay = nullptr;
                    nut_sua = {255, 255, 255};
                    nut_x = {255, 255, 255};
                }
                else if (MyFunc::check_click(mouse_X, mouse_Y, vi_tri_nut_sua)) // nhấn vào vút sửa
                {
                    Status result = this->target_maybay->edit(this->input_loaimb.get_data().c_str(), std::stoi(this->input_soday.get_data()), std::stoi(this->input_sodong.get_data()));
                    global->get_thong_bao().set_mess(result.mess);
                    global->get_thong_bao().on();
                    if (result.get_status() == Status_Name::SUCCESS)
                    {
                        *(this->flag_re_render_in_home) = true;
                    }
                }
                break;
            }

            input_loaimb.handleInput_Name(e, mouse_X, mouse_Y);
            input_soday.handleInput_Num(e, mouse_X, mouse_Y);
            input_sodong.handleInput_Num(e, mouse_X, mouse_Y);
        }
        void set_target(MayBay *mb)
        {
            if (this->now == true)
            {
                this->target_maybay = mb;
                this->input_shmb.set_data(mb->getSoHieuMB());
                this->input_loaimb.set_data(mb->getLoaiMB());
                this->input_soday.set_data(std::to_string(mb->getSoDay()));
                this->input_sodong.set_data(std::to_string(mb->getSoDong()));

                this->da_lap_cb = global->get_qlcb().getListCB().find_by_sh_mb_v2(mb->getSoHieuMB());
                this->now = false;
            }
        }
        void render_menu(MayBay *mb)
        {
            

            set_target(mb);
            myscreen->blur_background(150);
            khung_add_edit->render(myscreen->get_my_renderer());

            for (int i = 0; i < 4; i++)
            {
                myscreen->render_Text(name_field[i], rect_field[i], {0, 0, 0}, true);
            }

            if (this->da_lap_cb)
            {
                myscreen->render_Text(input_loaimb.get_data(), rect_input[1], {0, 0, 0}, true);
            }
            else
            {
                input_loaimb.render();
            }

            myscreen->render_Text(input_shmb.get_data(), rect_input[0], {0, 0, 0}, true);
            input_soday.render();
            input_sodong.render();

            this->render_button_xoa_sua();
        }
        void render_button_xoa_sua()
        {
            myscreen->render_cot(vi_tri_nut_sua, nut_sua);
            myscreen->render_Text("OK",vi_tri_nut_sua,{0,0,0}, true);
            myscreen->render_cot(vi_tri_nut_x, nut_x);
            myscreen->render_Text("X", vi_tri_nut_x, {0, 0, 0}, true);
        }
    };
    class Add
    {
    private:
        Global_Variable* global = nullptr;
        SDL_Rect vi_tri_nut_x = {1250, 210, 50, 50};
        SDL_Rect vi_tri_nut_sua = {950, 450, 150, 60};
        SDL_Color nut_sua = {255, 255, 255};
        SDL_Color nut_x = {255, 255, 255};

        Input input_shmb;
        Input input_loaimb;
        Input input_soday;
        Input input_sodong;

        bool now = true; // flag để gán 1 lần cho tất cả

        string name_field[4] = {"Số hiệu Máy Bay", "Loại", "Số Dãy", "Số Dòng"};
        SDL_Rect rect_field[4] = {{530, 300, 240, 50}, {530, 350, 240, 50}, {530, 400, 240, 50}, {530, 450, 240, 50}};
        SDL_Rect rect_input[4] = {{770, 300, 500, 50}, {770, 350, 500, 50}, {770, 400, 500, 50}, {770, 450, 500, 50}};
        int current_click_input = -1;

        bool da_lap_cb = false;

        bool *flag_re_render_in_home = nullptr;
        MyScreen* myscreen = nullptr;
        Box* khung_add_edit = nullptr;
        Box* edit = nullptr;

    public:
        void
        set(Global_Variable& global, bool *flag)
        {
            this->global = &global;
            khung_add_edit = &(global.get_c_component().khung_add_edit);
            edit = &(global.get_c_component().edit);
            myscreen = &(global.get_myscreen());

            this->flag_re_render_in_home = flag;
            this->vi_tri_nut_sua = {825, 515, 120, 60};


            input_shmb.set(&(global.get_myscreen()),MAX_LENGTH_SO_HIEU_MB,rect_input[0]);
            input_loaimb.set(&(global.get_myscreen()),MAX_LENGTH_LOAI_MAY_BAY,rect_input[1]);
            input_soday.set(&(global.get_myscreen()),2,rect_input[2]);
            input_sodong.set(&(global.get_myscreen()),2,rect_input[3]);

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
                    state = Position::HOME;
                    this->now = true;
                    nut_sua = {255, 255, 255};
                    nut_x = {255, 255, 255};
                }
                else if (MyFunc::check_click(mouse_X, mouse_Y, vi_tri_nut_sua)) // nhấn vào vút sửa
                {
                    Status result;
                    result = global->get_qlcb().getListMB().add(input_shmb.get_data().c_str(),input_loaimb.get_data().c_str(), std::stoi(input_soday.get_data()), std::stoi(input_sodong.get_data()));
                    global->get_thong_bao().set_mess(result.mess);
                    global->get_thong_bao().on();
                    if (result.get_status() == Status_Name::SUCCESS)
                    {
                        now = true;
                        *(this->flag_re_render_in_home) = true;
                    }
                }
                break;
            }
            input_shmb.handleInput_ID(e,mouse_X,mouse_Y);
            input_loaimb.handleInput_Name(e, mouse_X, mouse_Y);
            input_soday.handleInput_Num(e, mouse_X, mouse_Y);
            input_sodong.handleInput_Num(e, mouse_X, mouse_Y);
        }
        void reset_data(){
            input_loaimb.reset_data();
            input_shmb.reset_data();
            input_soday.reset_data();
            input_sodong.reset_data();
        }
        void render_menu()
        {
            if(this->now){
            this->reset_data();
            now = false;
            }

            

            myscreen->blur_background(150);
            khung_add_edit->render(myscreen->get_my_renderer());
            edit->set_rect(this->vi_tri_nut_sua);

            for (int i = 0; i < 4; i++)
            {
                myscreen->render_Text(name_field[i], rect_field[i], {0, 0, 0}, true);
            }

            input_shmb.render();
            input_loaimb.render();
            input_soday.render();
            input_sodong.render();

            this->render_button_xoa_sua();
        }
        void render_button_xoa_sua()
        {
            myscreen->render_cot(vi_tri_nut_sua, nut_sua);

            edit->render(myscreen->get_my_renderer());
            myscreen->render_cot(vi_tri_nut_x, nut_x);
            myscreen->render_Text("X", vi_tri_nut_x, {0, 0, 0}, true);
        }
    };
} // namespace Plane

class View_Plane
{
private:
    Global_Variable& global;

    Input input_so_hieu_mb;
    Buffer table;
    Buffer data;

    bool flag = false;

    Plane::Position state = Plane::Position::HOME; // mặc định ở Child_Route Home

    Plane::Menu menu_plane; // route menu
    Plane::Edit edit_plane; // route edit
    Plane::Add add_plane; // route edit

    MayBay *list_mb_dc_render[10];
    MayBay *temp = nullptr; // lấy con trỏ máy bay ở vị trí đang hover rồi click


    int vi_tri_hover_on_table = -1; // vị trí hover trên table data Máy Bay tính từ 0 - 9
    int so_luong_data = 0; // số lượng máy bay
    int current_page;              // phân trang hiện tại
    int mouse_X, mouse_Y;          // vị trí chuột


    int route_plane_width[5]{150, 250, 600, 250, 250};
    string route_plane_name_cot[6]{"STT", "Số Hiệu MB", "Loại", "Số Dãy", "Số Dòng"};

    SDL_Color nut_add {255,255,255};
public:
    View_Plane(Global_Variable& gb); 

    void handleEvent(SDL_Event e, bool &is_home, int mouse_X, int mouse_Y)
    {
        this->mouse_X = mouse_X;
        this->mouse_Y = mouse_Y;
        nut_add = {255,255,255};
        if (this->state == Plane::Position::HOME)
        {
            is_home = true;
            switch (e.type)
            {
            case SDL_MOUSEMOTION:
                if(global.get_c_component().add.is_in_box(mouse_X,mouse_Y)){
                    nut_add = {255, 219, 26};
                }
                this->vi_tri_hover_on_table = Func_Global::get_line(this->mouse_X, this->mouse_Y, this->so_luong_data,this->current_page); // 0 - 9
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
                    this->temp = this->list_mb_dc_render[vi_tri_hover_on_table];
                    this->state = Plane::Position::MENU;
                }
                if(global.get_c_component().add.is_in_box(mouse_X,mouse_Y)){
                    state = Plane::Position::ADD;
                }
                break;
            }

            input_so_hieu_mb.handleInput_ID(e, mouse_X, mouse_Y);
            if (e.type == SDL_KEYDOWN || e.type == SDL_TEXTINPUT)
                this->re_render_data();
        }
        else
        {
            is_home = false;
            if (state == Plane::Position::MENU)
            {
                menu_plane.handleEvent(e, this->state, mouse_X, mouse_Y);
            }
            else if (state == Plane::Position::EDIT)
            {
                edit_plane.handleEvent(e, this->state, mouse_X, mouse_Y);
            }
            else if (state == Plane::Position::ADD)
            {
                add_plane.handleEvent(e, this->state, mouse_X, mouse_Y);
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

        this->global.get_myscreen().render_cot(this->global.get_c_component().add.get_rect(),nut_add);
        this->global.get_c_component().add.render(this->global.get_myscreen().get_my_renderer()); // render nút add

        this->global.get_c_component().render_next_prev(mouse_X,mouse_Y,current_page,so_luong_data,&(this->global.get_myscreen()));

        SDL_Rect rect_temp{150, 175, 150, 50}; // ô input : 300,175,300,50
        this->global.get_myscreen().render_Text("Số Hiệu MB:", rect_temp, {0, 0, 0}, true);
        input_so_hieu_mb.render(); // render ô input nhập số hiệu máy bay

        if (state == Plane::Position::MENU)
        {
            menu_plane.render_menu(temp, vi_tri_hover_on_table);
        }
        else if (state == Plane::Position::EDIT)
        {
            edit_plane.render_menu(temp);
        }
        else if (state == Plane::Position::ADD)
        {
            add_plane.render_menu();
        }
    }

    ////////////////////////////////////////////////////////////
    void getData() // đưa data vào bộ đệm
    {
        data.connect_render_clear();
        ListMayBay* list_mb = &(this->global.get_qlcb().getListMB());
        int so_may_bay = list_mb->get_so_luong();
        int start = (this->current_page - 1) * 10;
        int end = start + 9; // 0 - 9 là 10
        int stt = 0;
        int so_line_render = 0;
        MayBay *mb = nullptr;
        int index = 0;
        for (int i = 0; i < so_may_bay; i++)
        {
            mb = list_mb->get_at(i);
            if (Func_Global::check_prefix(mb->getSoHieuMB(), this->input_so_hieu_mb.get_data().c_str()))
            {
                if (stt >= start && stt <= end)
                {
                    this->list_mb_dc_render[index] = mb;
                    index++;
                    this->render_line_data(stt, start, mb);
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
    void createTable(); // vẽ ra viền bảng
    void render_line_data(int stt, int start, MayBay *mb); // render 1 linedata Máy Bay
};
View_Plane::View_Plane(Global_Variable& gb) : global{gb}
    {

        current_page = 1;

        menu_plane.set(global,&flag);
        edit_plane.set(global, &flag);
        add_plane.set(global, &flag);
        
        table.set(&(global.get_myscreen()), WIDTH_TABLE, HEIGHT_TABLE + 50);
        table.set_vitri(X_START_TABLE, Y_START_TABLE - 50);
        this->createTable();

        data.set(&(global.get_myscreen()), WIDTH_TABLE, HEIGHT_TABLE);
        data.set_vitri(X_START_TABLE, Y_START_TABLE);

        this->getData();

        input_so_hieu_mb.set(&(global.get_myscreen()),MAX_LENGTH_SO_HIEU_MB,{300, 175, 300, 50});
        string note = "Tối đa " + std::to_string(MAX_LENGTH_SO_HIEU_MB) +" kí tự";
        input_so_hieu_mb.set_note(note);
    }
void View_Plane::re_render_data()
{
    this->flag = true;
}
void View_Plane::follow_flag()
{
    if (this->flag == true)
    {
        this->getData();
        this->flag = false;
    }
}

void View_Plane::createTable() // vẽ ra viền bảng
{
    table.connect_render_clear();
    this->global.get_myscreen().render_table(5, route_plane_width, route_plane_name_cot);
    table.disconnect_render();
}

void View_Plane::render_line_data(int stt, int start, MayBay *mb) // render 1 linedata Máy Bay
{
    SDL_Rect rect;
    rect = {0, 0 + (stt - start) * 50, route_plane_width[0], 50};
    this->global.get_myscreen().render_Text(std::to_string((stt) + 1), rect, {0, 0, 0, 255}, true);

    rect.x += rect.w;
    rect.w = route_plane_width[1];
    this->global.get_myscreen().render_Text(mb->getSoHieuMB(), rect, {0, 0, 0, 255}, true);

    rect.x += rect.w;
    rect.w = route_plane_width[2];
    this->global.get_myscreen().render_Text(mb->getLoaiMB(), rect, {0, 0, 0, 255}, true);

    rect.x += rect.w;
    rect.w = route_plane_width[3];
    this->global.get_myscreen().render_Text(std::to_string(mb->getSoDay()), rect, {0, 0, 0, 255}, true);

    rect.x += rect.w;
    rect.w = route_plane_width[4];
    this->global.get_myscreen().render_Text(std::to_string(mb->getSoDong()), rect, {0, 0, 0, 255}, true);
}
#endif