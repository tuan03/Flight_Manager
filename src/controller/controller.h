#pragma once
#include"../header.h"

#include"../views/views_plane.h"
#include"../views/views_customer.h"
#include"../views/views_flight.h"
#include"../views/views_thongke.h"
#include"../views/views_ticket.h"

#include"../views/component.h"


class Controller{
    private:
    MyScreen myscreen;
    Flight_Manager qlcb;
    ListBox menu;
    Box homepage;
    Box prev;
    Box next;


    Box khung_menu;

    int route_plane_width[5]{150,250,600,250,250,};
    string route_plane_name_cot[6]{"STT","Số Hiệu MB","Loại","Số Dãy","Số Dòng"};
    
    int route_flight_width[7]{100,200,200,450,200,200,150};
    string route_flight_name_cot[7]{"STT","Mã Số CB","Sân Bay Đến","Thời Gian Bay","Trạng Thái","Số Hiệu MB","Trạng Thái Vé"};
    
    int route_customer_width[6]{100,280,280,280,280,280};
    string route_customer_name_cot[6]{"STT","Vé","Họ","Tên","Số CMND","Giới Tính"};
    
    int route_thongke_width[3]{200,600,700};
    string route_thongke_name_cot[3]{"STT","Mã Số CB","Số Lượt Bay"};


    public:
    Controller(): myscreen{WIDTH_SCREEN,HEIGHT_SCREEN,"Quản Lí Chuyến Bay","src/views/font/Arial.ttf",24}{
        menu.connect_my_renderer(myscreen.get_my_renderer());
        menu.insert("src/views/img/plane1.png",{50,25,300,100},Name_Box::PLANE)->set_hover("src/views/img/plane2.png",myscreen.get_my_renderer())->set_clicked("src/views/img/plane3.png",myscreen.get_my_renderer());
        menu.insert("src/views/img/chuyenbay1.jpg",{400,25,300,100},Name_Box::FLIGHT)->set_hover("src/views/img/chuyenbay2.jpg",myscreen.get_my_renderer())->set_clicked("src/views/img/chuyenbay3.jpg",myscreen.get_my_renderer());
        menu.insert("src/views/img/custom1.jpg",{750,25,300,100},Name_Box::CUSTOMER)->set_hover("src/views/img/custom2.jpg",myscreen.get_my_renderer())->set_clicked("src/views/img/custom3.jpg",myscreen.get_my_renderer());
        menu.insert("src/views/img/ve1.jpg",{1100,25,300,100},Name_Box::TICKET)->set_hover("src/views/img/ve2.jpg",myscreen.get_my_renderer())->set_clicked("src/views/img/ve3.jpg",myscreen.get_my_renderer());
        menu.insert("src/views/img/thongke1.jpg",{1450,25,300,100},Name_Box::THONGKE)->set_hover("src/views/img/thongke2.jpg",myscreen.get_my_renderer())->set_clicked("src/views/img/thongke3.jpg",myscreen.get_my_renderer());
 
        menu.insert("src/views/img/body.png",{X_START_BODY,Y_START_BODY,1700,780});

        homepage.create("src/views/img/plane_img.png",myscreen.get_my_renderer());
        homepage.set_rect(500,190,800,700);

        prev.create("src/views/img/prev.png",myscreen.get_my_renderer());
        prev.set_rect(760,815,80,80);
        prev.set_hover("src/views/img/prev1.png",myscreen.get_my_renderer());

        next.create("src/views/img/next.png",myscreen.get_my_renderer());
        next.set_rect(960,815,80,80);
        next.set_hover("src/views/img/next1.png",myscreen.get_my_renderer());

        khung_menu.create("src/views/img/khung_menu.png",myscreen.get_my_renderer());
        khung_menu.set_rect(300, -10,1200,700);
    }
    

    void running(){

        View_Plane view_plane(&(this->qlcb),&(this->myscreen),&(this->prev),&(this->next),&(this->khung_menu)); // khởi tạo view Plane


        bool quit = false; // điều kiện thoát chương trình
        SDL_Event e;    
        Uint32 timeCurrent = SDL_GetTicks(); //tại fps
        Uint32 timePre = SDL_GetTicks(); // tạo fps

        Box* get_box_hover = nullptr;   // để lấy lấy box đang hover, null nếu khoogn trên box nào
        Name_Box current_hover = Name_Box::NONE; // route đnag hover
        Name_Box current_route = Name_Box::NONE; // route hiện tại đang ở
        int mouse_X, mouse_Y;
        while (!quit){
        while (SDL_PollEvent(&e) != 0)  {
            if(e.type == SDL_MOUSEMOTION){
                SDL_GetMouseState(&mouse_X, &mouse_Y);
                get_box_hover = menu.checkClick(mouse_X,mouse_Y);
                if(get_box_hover != nullptr){
                    current_hover =  get_box_hover->get_name_box();
                } else {
                    current_hover = Name_Box::NONE;
                }
            }
            if(e.type == SDL_MOUSEBUTTONDOWN){// sự kiện nhấn vào các box
                if(current_hover != Name_Box::NONE) current_route = current_hover;
            } 


            view_plane.handleEvent(e,current_route,menu,quit);
        
        }
        
        //render
        SDL_SetRenderDrawColor(myscreen.get_my_renderer()->get_renderer(), 255, 255, 255, 0);
        SDL_RenderClear(myscreen.get_my_renderer()->get_renderer());

        menu.render_list_ver2(current_hover,current_route); // render thanh menu
        switch (current_route)
        {
        case Name_Box::PLANE :
            view_plane.render();
            break;
        case Name_Box::FLIGHT :
               

            break;
        case Name_Box::CUSTOMER :
                
            break;
        case Name_Box::TICKET :
            break;
        case Name_Box::THONGKE :
                
            break;
        
        default:
            homepage.render(myscreen.get_my_renderer());
            break;
        }

        timeCurrent = SDL_GetTicks();
        SDL_RenderPresent(myscreen.get_my_renderer()->get_renderer());
        //render

        if(timeCurrent-timePre < TIME_A_FRAME){
            SDL_Delay(TIME_A_FRAME - (timeCurrent-timePre));
        }
        timePre = SDL_GetTicks();
        
    }


}
    ~Controller(){

    }
    
};