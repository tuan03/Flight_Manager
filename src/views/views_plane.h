#ifndef VIEWS_PLANE_H
#define VIEWS_PLANE_H
#include"../header.h"
bool check_click(int x, int y, SDL_Rect rect){
        if(x>=rect.x && x<= rect.x + rect.w && y>=rect.y && y<=rect.y + rect.h){
            return true;
        }
        return false;
}
namespace Plane{
enum State{
    HOME,
    MENU,
    EDIT,
    DELETE,
    ADD
};

class Menu{
    private:
    MyScreen* myscreen = nullptr;
    Box* khung_menu = nullptr;
    SDL_Rect vi_tri_nut_x = {1250, 210,50,50};
    SDL_Rect vi_tri_nut_xoa = {700, 450,150,60};
    SDL_Rect vi_tri_nut_sua = {950, 450,150,60};
    SDL_Color nut_xoa = {255,255,255};
    SDL_Color nut_sua = {255,255,255};
    SDL_Color nut_x = {255,255,255};

    Box* edit = nullptr;
    Box* del = nullptr;

    public:
    void handleEvent(SDL_Event e, State& state, int mouse_X, int mouse_Y,bool& quit){
        nut_xoa = {255,255,255};
        nut_sua = {255,255,255};
        nut_x = {255,255,255};
        switch (e.type)
        {
        case SDL_MOUSEMOTION:
                if(check_click(mouse_X,mouse_Y, vi_tri_nut_x)){
                    nut_x = {255,219,26};
                } else
                if(check_click(mouse_X,mouse_Y, vi_tri_nut_sua)){
                    nut_sua = {255,219,26};
                } else
                if(check_click(mouse_X,mouse_Y, vi_tri_nut_xoa)){
                    nut_xoa = {255,219,26};
                }

                break;
                case SDL_MOUSEBUTTONDOWN: // sự kiện nhấn vào các box
                        if(check_click(mouse_X,mouse_Y, vi_tri_nut_x)){
                            state = State::HOME;
                        } else
                        if(check_click(mouse_X,mouse_Y, vi_tri_nut_sua)){
                            state = State::EDIT;

                        } else
                        if(check_click(mouse_X,mouse_Y, vi_tri_nut_xoa)){
                            cout<<"Click xoa\n";
                        }
                    break;
                case SDL_QUIT: // sự kiện nhất thoát
                    quit = true;
                    break;
        }
    }
    void set(MyScreen* mc, Box* khung_menu,Box* edit, Box* del){
        this->myscreen = mc;
        this->khung_menu = khung_menu;
        this->edit = edit;
        this->del = del;
        this->edit->set_rect(this->vi_tri_nut_sua);
        this->del->set_rect(this->vi_tri_nut_xoa);
    }
    void render_menu(MayBay* mb, int vt){
        // SDL_Rect rect;
        // myscreen->blur_background(150);
        SDL_Rect rect ={700, Y_START_TABLE + vt*50 -280 ,300,300};
        khung_menu->set_rect(rect);
        khung_menu->render(myscreen->get_my_renderer());

        SDL_Rect rect_2 = edit->get_rect();

        rect_2.x = rect.x + 75;
        rect_2.y = rect.y + 60;
        this->vi_tri_nut_sua = rect_2;
        edit->set_rect(rect_2);

        rect_2.y += 30;
        this->vi_tri_nut_x = {960,rect_2.y,50,50};


        rect_2.y += 60;
        del->set_rect(rect_2);
        this->vi_tri_nut_xoa = rect_2;
        
        this->render_button_xoa_sua();
    }
        void render_confirm_xoa(){
        SDL_Rect rect;
        rect = {700, 310,400,200};
        myscreen->render_cot(rect,COLOR_MENU_CHILD);
        myscreen->render_Text("Xác nhận xóa ?",rect,{0,0,0},true);
    }
    
    void render_button_xoa_sua(){
        myscreen->render_cot(vi_tri_nut_xoa,nut_xoa);
        myscreen->render_cot(vi_tri_nut_sua,nut_sua);

        this->edit->render(this->myscreen->get_my_renderer());
        this->del->render(this->myscreen->get_my_renderer());
        myscreen->render_cot(vi_tri_nut_x,nut_x);
        myscreen->render_Text("X",vi_tri_nut_x,{0,0,0},true);
    }
};
class Del{
    private:


    public:
};
class Edit{
    private:
    MyScreen* myscreen;
    Box* khung;
    Box* edit;
    SDL_Rect vi_tri_nut_x = {1250, 210,50,50};
    SDL_Rect vi_tri_nut_sua = {950, 450,150,60};
    SDL_Color nut_sua = {255,255,255};
    SDL_Color nut_x = {255,255,255};

    bool now = true;

    string name_field[4] = {"Số hiệu Máy Bay", "Loại","Số Dãy","Số Dòng"};
        SDL_Rect rect_field[4]= {{530, 300 ,240,50},{530, 350,240,50},{530, 400,240,50},{530, 450,240,50}};
        SDL_Rect rect_input[4]={{770, 300,500,50},{770, 350,500,50},{770, 400,500,50},{770, 450,500,50}};
    int current_click_input = -1;
    
    string so_hieu_mb = "";
    string loai_mb = "";
    string so_day = "";
    string so_dong = "";

    bool da_lap_cb = false;
    public:
    void set(MyScreen* mc, Box* khung,Box* edit){
        this->myscreen = mc;
        this->khung = khung;
        khung->set_rect(300,140,1200,600);
        this->vi_tri_nut_sua = {825,515,120,60};
        this->edit = edit;
        
    }
    void reset(){
        nut_sua = {255,255,255};
        nut_x = {255,255,255};
    }
    void handleEvent(SDL_Event e, State& state, int mouse_X, int mouse_Y,bool& quit){
        this->reset();
        switch (e.type)
        {
        case SDL_MOUSEMOTION:
                if(check_click(mouse_X,mouse_Y, vi_tri_nut_x)){
                    nut_x = {255,219,26};
                } else
                if(check_click(mouse_X,mouse_Y, vi_tri_nut_sua)){
                    nut_sua = {255,219,26};
                }
                break;
                case SDL_MOUSEBUTTONDOWN: // sự kiện nhấn vào các box
                        this->current_click_input = -1;
                        for(int i=0; i<4; i++){ 
                            if(check_click(mouse_X,mouse_Y, rect_input[i])){
                                this->current_click_input = i;
                                break;
                            }
                        }  
                        if(check_click(mouse_X,mouse_Y, vi_tri_nut_x)){
                            state = State::MENU;
                            this->reset();
                        } else
                        if(check_click(mouse_X,mouse_Y, vi_tri_nut_sua)){
                            cout<<"click sua\n";
                        } 
                        
                    break;
                case SDL_QUIT: // sự kiện nhất thoát
                    quit = true;
                    break;
        }
        this->handleInput_IN_HOA_KHONG_CACH(e,so_hieu_mb,MAX_LENGTH_SO_HIEU_MB);

    }
    void handleInput_IN_HOA_KHONG_CACH(SDL_Event e, string& inputString, int max_length){
        
        switch(e.type){
            case SDL_KEYDOWN:
                    if (e.key.keysym.sym == SDLK_RETURN)
                    {
                        this->current_click_input +=1;
                        if(this->current_click_input == 5) this->current_click_input = -1;
                    }else if (e.key.keysym.sym == SDLK_BACKSPACE && inputString.length() > 0)
                    {
                        inputString.pop_back();
                    }
                    break;
                case SDL_TEXTINPUT:
                    if(e.text.text[0] >= 'A' && e.text.text[0] <= 'Z' && inputString.length() < max_length) 
                    inputString += e.text.text;
                    if(e.text.text[0] >= 'a' && e.text.text[0] <= 'z' && inputString.length() < max_length) 
                    inputString +=  e.text.text[0] - ('a'-'A');
                    break;
        }
    }
     void handleInput_number(SDL_Event e, string& inputString){
        switch(e.type){
            case SDL_KEYDOWN:
                    if (e.key.keysym.sym == SDLK_RETURN)
                    {
                        inputString = "";
                    }else if (e.key.keysym.sym == SDLK_BACKSPACE && inputString.length() > 0)
                    {
                        // Xóa ký tự cuối cùng trong chuỗi nhập vào
                        inputString.pop_back();
                    }
                    break;
                case SDL_TEXTINPUT:
                    // Nếu sự kiện là nhập ký tự
                    inputString += e.text.text;
                    break;
        }
    }

    void input(SDL_Rect vitri,string& inputString, int stt){




        SDL_Rect box_input{vitri.x+3,vitri.y + 3,vitri.w - 6,vitri.h-6};
        myscreen->render_cot(vitri,{0,0,0});
        if(stt == current_click_input)
        myscreen->render_cot(box_input);
        else
        myscreen->render_cot(box_input,{255,255,255});
        SDL_Rect con_tro;
        myscreen->render_Text(inputString,box_input,{0,0,0},true,&con_tro);
        if(stt == current_click_input){
        con_tro.x = con_tro.x + con_tro.w + 2;
        con_tro.w = 2;
        myscreen->render_cot(con_tro);
        }
}
    void render_menu(MayBay* mb, Flight_Manager* qlcb){
        myscreen->blur_background(150);
        khung->render(myscreen->get_my_renderer());
        this->edit->set_rect(this->vi_tri_nut_sua);
        
        
        if(this->now == true){
            so_hieu_mb = mb->getSoHieuMB();
            loai_mb = mb->getLoaiMB();
            so_day = std::to_string(mb->getSoDay());
            so_dong = std::to_string(mb->getSoDong());

            
            this->da_lap_cb = qlcb->getListCB().timChuyenBayTheoMaSoMB(mb->getSoHieuMB()) != nullptr;

            this->now = false;
        }



        for(int i=0; i<4; i++){
            this->myscreen->render_Text(name_field[i],rect_field[i],{0,0,0},true);
        }
        this->myscreen->render_Text(so_hieu_mb,rect_input[0],{0,0,0},true);
        if(this->da_lap_cb == false){
            this->myscreen->render_Text(loai_mb,rect_input[1],{0,0,0},true);
        } else {
        this->input(rect_input[1],loai_mb,1);
        }

        
        this->input(rect_input[2],so_day,2);
        this->input(rect_input[3],so_dong,3);

        this->render_button_xoa_sua();
    }
        void render_confirm_xoa(){
        SDL_Rect rect;
        rect = {700, 310,400,200};
        myscreen->render_cot(rect,COLOR_MENU_CHILD);
        myscreen->render_Text("Xác nhận xóa ?",rect,{0,0,0},true);
    }
    
    void render_button_xoa_sua(){

        myscreen->render_cot(vi_tri_nut_sua,nut_sua);

        this->edit->render(this->myscreen->get_my_renderer());
        myscreen->render_cot(vi_tri_nut_x,nut_x);
        myscreen->render_Text("X",vi_tri_nut_x,{0,0,0},true);
    }


};
class Add{
    private:
    public:
};
}


class View_Plane{
    private:
        int current_page;
        Flight_Manager* qlcb;
        MyScreen* myscreen;
        Box* prev;
        Box* next;

        int mouse_X , mouse_Y;

        string inputString ="";

        Plane::State state = Plane::State::HOME;
        Plane::Menu menu_plane;
        Plane::Edit edit_plane;


        int vi_tri_hover_on_table = -1;

        MayBay* temp = nullptr;

        int so_luong_data = 0;

        int route_plane_width[5]{150,250,600,250,250};
        string route_plane_name_cot[6]{"STT","Số Hiệu MB","Loại","Số Dãy","Số Dòng"};

        Box* add = nullptr;

        
    public:
    View_Plane(Flight_Manager* qlcb, MyScreen* myscreen, Box* prev, Box* next,Box* khung_menu, Box* add, Box* edit, Box* del,Box* khung) {
        this->qlcb = qlcb;
        this->myscreen = myscreen;
        current_page = 1;
        this->prev = prev;
        this->next = next;

        menu_plane.set(myscreen,khung_menu,edit,del);
        edit_plane.set(myscreen,khung,edit);




        this->add = add;
        this->add->set_rect(X_START_BODY + 1700 - 150, Y_START_BODY, 150,60);
        this->so_luong_data = qlcb->getListMB().get_so_luong();
    }
    
    void handleEvent(SDL_Event e,Name_Box& current_route, ListBox& menu, bool& quit) {
        if(e.type == SDL_MOUSEMOTION) SDL_GetMouseState(&mouse_X, &mouse_Y);
        if(this->state == Plane::State::HOME){
        switch (e.type) {
                case SDL_MOUSEMOTION:
                this->vi_tri_hover_on_table = this->get_vitri(this->mouse_X,this->mouse_Y,qlcb->getListMB().get_so_luong()); // 0 - 9
                break;

                case SDL_MOUSEBUTTONDOWN: // sự kiện nhấn vào các box
                    if(current_page > 1){
                    if(prev->is_in_box(mouse_X,mouse_Y)){
                        this->current_page-=1;
                    }
                    } 
                    if(current_page <((this->so_luong_data -1 )/10) + 1){
                    if(next->is_in_box(mouse_X,mouse_Y)){
                        current_page+=1;
                    }
                    }
                    if(this->vi_tri_hover_on_table != -1){
                            this->state = Plane::State::MENU;
                            this->temp = qlcb->getListMB().get_at(vi_tri_hover_on_table + (current_page-1) *10);
                    }
                    break;
                case SDL_KEYDOWN:
                    if (e.key.keysym.sym == SDLK_RETURN)
                    {
                        // Thực hiện xử lý với chuỗi nhập vào
                        std::cout << inputString << std::endl;
                        inputString = "";
                    }else if (e.key.keysym.sym == SDLK_BACKSPACE && inputString.length() > 0)
                    {
                        // Xóa ký tự cuối cùng trong chuỗi nhập vào
                        inputString.pop_back();
                    }
                    break;
                case SDL_TEXTINPUT:
                    // Nếu sự kiện là nhập ký tự
                    inputString += e.text.text;
                    break;
                case SDL_QUIT: // sự kiện nhất thoát
                    quit = true;
                    break;
            }
            } else
            if(state == Plane::State::MENU){
                menu_plane.handleEvent(e,this->state,mouse_X,mouse_Y,quit);
            } else
            if(state == Plane::State::EDIT){
                edit_plane.handleEvent(e,this->state,mouse_X,mouse_Y,quit);
            }
    }
    
    void update() {
        this->so_luong_data = qlcb->getListMB().get_so_luong();
    }
    
    void render() {
        this->update();

        myscreen->render_table(5,route_plane_width,route_plane_name_cot);
        if(this->vi_tri_hover_on_table != -1){
            myscreen->render_cot({X_START_TABLE,Y_START_TABLE + vi_tri_hover_on_table*50,WIDTH_TABLE,50},{159,212,171});
        }
        this->add->render(this->myscreen->get_my_renderer());
        this->render_data();
        this->render_next_prev();

        if(state == Plane::State::MENU){
                menu_plane.render_menu(temp,vi_tri_hover_on_table);
        } else 
        if(state == Plane::State::EDIT){
                edit_plane.render_menu(temp,this->qlcb);
        }

    }
    int get_vitri(int x, int y, int so_luong){ // vị trí con trỏ chuột trỏ đến / trả về dòng trong bảng dữ liệu
        if(x>=X_START_TABLE && x<=X_START_TABLE+WIDTH_TABLE && y>=Y_START_TABLE && y<= Y_START_TABLE+HEIGHT_TABLE){
            int vitri = (y-Y_START_TABLE)/50;
            if(current_page == (so_luong/10)+1){
                if(vitri < so_luong%10){
                    return vitri;
                }
            } else {
                    return vitri;
            }
        }
        return -1;
    }



   void render_next_prev(){
        SDL_Rect rect;
        next->render(myscreen->get_my_renderer(),next->is_in_box(mouse_X,mouse_Y) ? 1 :0  );
        prev->render(myscreen->get_my_renderer(),prev->is_in_box(mouse_X,mouse_Y) ? 1 :0 );
        rect = {840,825,120,50};
        myscreen->render_Text(std::to_string(current_page)+"/"+std::to_string(((this->so_luong_data -1 )/10) + 1), rect,{0,0,0,255},true);
    }
    void render_data(){
        SDL_Rect rect;
        for(int i=0; i< 10; i++){ // 10 dòng
            if(i + 10*(this->current_page-1) >= this->qlcb->getListMB().get_so_luong()) break;
            MayBay* mb = this->qlcb->getListMB().get_at(i+10*(this->current_page-1)); // công thức lấy thông tin máy bay tại dòng

            rect = {X_START_TABLE, Y_START_TABLE + i*50 ,route_plane_width[0],50};
            this->myscreen->render_Text(std::to_string(i+1), rect,{0,0,0,255},true);

            rect.x += rect.w; 
            rect.w = route_plane_width[1];
            this->myscreen->render_Text(mb->getSoHieuMB(), rect,{0,0,0,255},true);

            rect.x += rect.w; 
            rect.w = route_plane_width[2];
            this->myscreen->render_Text(mb->getLoaiMB(), rect,{0,0,0,255},true);

            rect.x += rect.w; 
            rect.w = route_plane_width[3];
            this->myscreen->render_Text(std::to_string(mb->getSoDay()), rect,{0,0,0,255},true);
                    
            rect.x += rect.w; 
            rect.w = route_plane_width[4];
            this->myscreen->render_Text(std::to_string(mb->getSoDong()), rect,{0,0,0,255},true);
        }
    }
};


#endif