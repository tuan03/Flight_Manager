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
    public:
    void handleEvent(SDL_Event e, State& state, int mouse_X, int mouse_Y){
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
                            cout<<"click sua\n";
                        } else
                        if(check_click(mouse_X,mouse_Y, vi_tri_nut_xoa)){
                            cout<<"Click xoa\n";
                        }
                    break;
        }
    }
    void set(MyScreen* mc, Box* khung_menu){
        this->myscreen = mc;
        this->khung_menu = khung_menu;
    }
    void render_menu(MayBay* mb){
        SDL_Rect rect;
        myscreen->blur_background(150);
        khung_menu->render(myscreen->get_my_renderer());
        rect = {500, 210,800,400};
        
        rect = {500, rect.y + 10 ,300,50};
        myscreen->render_Text("Số hiệu Máy Bay:",rect,{0,0,0},true);
        
        rect = {800, rect.y,500,50};
        
        myscreen->render_Text(mb->getSoHieuMB(),rect,{0,0,0},true);
        rect = {500, rect.y + 50,300,50};
        
        myscreen->render_Text("Loại:",rect,{0,0,0},true);
        rect = {800, rect.y ,500,50};
        
        myscreen->render_Text(mb->getLoaiMB(),rect,{0,0,0},true);
        rect = {500, rect.y + 50,300,50};
        
        myscreen->render_Text("Số dãy:",rect,{0,0,0},true);
        rect = {800, rect.y ,500,50};
        
        myscreen->render_Text(std::to_string(mb->getSoDay()),rect,{0,0,0},true);
        rect = {500, rect.y + 50,300,50};
        
        myscreen->render_Text("Số dòng:",rect,{0,0,0},true);
        rect = {800, rect.y,500,50};
        
        myscreen->render_Text(std::to_string(mb->getSoDong()),rect,{0,0,0},true);
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
        myscreen->render_Text("Xóa",vi_tri_nut_xoa,{0,0,0},true);
        myscreen->render_cot(vi_tri_nut_sua,nut_sua);
        myscreen->render_Text("Sửa",vi_tri_nut_sua,{0,0,0},true);
        myscreen->render_cot(vi_tri_nut_x,nut_x);
        myscreen->render_Text("X",vi_tri_nut_x,{0,0,0},true);
    }
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
        int vi_tri_hover_on_table = -1;

        MayBay* temp = nullptr;

        int so_luong_data = 0;

        int route_plane_width[5]{150,250,600,250,250};
        string route_plane_name_cot[6]{"STT","Số Hiệu MB","Loại","Số Dãy","Số Dòng"};

        
    public:
    View_Plane(Flight_Manager* qlcb, MyScreen* myscreen, Box* prev, Box* next,Box* khung_menu) {
        this->qlcb = qlcb;
        this->myscreen = myscreen;
        current_page = 1;
        this->prev = prev;
        this->next = next;
        menu_plane.set(myscreen,khung_menu);
        this->so_luong_data = qlcb->getListMB().get_so_luong();
    }
    
    void handleEvent(SDL_Event e,Name_Box& current_route, ListBox& menu, bool& quit) {
        switch (e.type) {
                case SDL_MOUSEMOTION:
                // Lấy vị trí chuột
                SDL_GetMouseState(&mouse_X, &mouse_Y);
                if(this->state == Plane::State::HOME){ // không get vị trí hover nữa khi đã bật menu lên
                this->vi_tri_hover_on_table = this->get_vitri(this->mouse_X,this->mouse_Y,qlcb->getListMB().get_so_luong()); // 0 - 9
                }

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

            if(state == Plane::State::MENU){
                menu_plane.handleEvent(e,this->state,mouse_X,mouse_Y);
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
        this->render_data();
        this->render_next_prev();

        if(state == Plane::State::MENU){
                menu_plane.render_menu(temp);
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
void input(){
        SDL_Rect box_input_vien{300,400,300,50};
        SDL_Rect box_input{303,403,294,44};
        SDL_Rect con_tro;
        myscreen->render_cot(box_input_vien,{0,0,0});
        myscreen->render_cot(box_input);
        myscreen->render_Text(inputString,box_input,{0,0,0},true,&con_tro);
        con_tro.x = con_tro.x + con_tro.w + 2;
        con_tro.w = 2;
        myscreen->render_cot(con_tro);
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