#include"src/flight_manager.h"
#include"src/views/component.h"
#undef main
int main(){
    try{
    MyScreen myscreen(1800,950,"Quản Lí Chuyến Bay","src/views/font/Arial.ttf",24);
    Flight_Manager qlcb;
    
    // qlcb.getListCB().print();
    // qlcb.getListHK().printAll();
    // qlcb.getListMB().print();
    // test từ dưới


    ListBox menu;
    menu.connect_my_renderer(myscreen.get_my_renderer());
    menu.insert("src/views/img/plane1.png",{50,25,300,100},Name_Box::PLANE)->set_hover("src/views/img/plane2.png",myscreen.get_my_renderer())->set_clicked("src/views/img/plane3.png",myscreen.get_my_renderer());
    menu.insert("src/views/img/chuyenbay1.jpg",{400,25,300,100},Name_Box::FLIGHT)->set_hover("src/views/img/chuyenbay2.jpg",myscreen.get_my_renderer())->set_clicked("src/views/img/chuyenbay3.jpg",myscreen.get_my_renderer());
    menu.insert("src/views/img/custom1.jpg",{750,25,300,100},Name_Box::CUSTOMER)->set_hover("src/views/img/custom2.jpg",myscreen.get_my_renderer())->set_clicked("src/views/img/custom3.jpg",myscreen.get_my_renderer());
    menu.insert("src/views/img/ve1.jpg",{1100,25,300,100},Name_Box::TICKET)->set_hover("src/views/img/ve2.jpg",myscreen.get_my_renderer())->set_clicked("src/views/img/ve3.jpg",myscreen.get_my_renderer());
    menu.insert("src/views/img/thongke1.jpg",{1450,25,300,100},Name_Box::THONGKE)->set_hover("src/views/img/thongke2.jpg",myscreen.get_my_renderer())->set_clicked("src/views/img/thongke3.jpg",myscreen.get_my_renderer());

    menu.insert("src/views/img/body.png",{50,150,1700,780});


    //end test
    bool quit = false; // điều kiện thoát chương trình
    SDL_Event e;
    Uint32 timeCurrent = SDL_GetTicks();
    Uint32 timePre = SDL_GetTicks();
    int mouseX,mouseY,x,y;
    Box* get_box_hover = nullptr;
    Name_Box current_hover = Name_Box::NONE;
    Name_Box current_route = Name_Box::NONE;
    while (!quit){
        while (SDL_PollEvent(&e) != 0)  {
            switch (e.type) {
                case SDL_MOUSEMOTION:
                // Lấy vị trí chuột
                SDL_GetMouseState(&x, &y);
                get_box_hover = menu.checkClick(x,y);
                if(get_box_hover != nullptr){
                    current_hover =  get_box_hover->get_name_box();
                } else {
                    current_hover = Name_Box::NONE;
                }
                break;
                case SDL_MOUSEBUTTONDOWN: // sự kiện nhấn vào các box
                    if(current_hover != Name_Box::NONE)
                        current_route = current_hover;
                    break;
                case SDL_KEYDOWN:
                    break;
                case SDL_QUIT: // sự kiện nhất thoát
                    quit = true;
                    break;
            }
            
        }
        
        //render
        SDL_SetRenderDrawColor(myscreen.get_my_renderer()->get_renderer(), 255, 255, 255, 0);
        SDL_RenderClear(myscreen.get_my_renderer()->get_renderer());
        menu.render_list_ver2(current_hover,current_route);
        string text_test;
        SDL_Rect vt {900,500,0,0};
        SDL_Color cl{0,0,0,0};
        switch (current_route)
        {
        case Name_Box::PLANE :
            text_test = "Route Plane";
            myscreen.render_Text(text_test,vt,cl);
            break;
        case Name_Box::FLIGHT :
            text_test = "Route Flight";
            myscreen.render_Text(text_test,vt,cl);
            break;
        case Name_Box::CUSTOMER :
            text_test = "Route Customer";
            myscreen.render_Text(text_test,vt,cl);
            break;
        case Name_Box::TICKET :
            text_test = "Route Ticket";
            myscreen.render_Text(text_test,vt,cl);
            break;
        case Name_Box::THONGKE :
            text_test = "Route Thong Ke";
            myscreen.render_Text(text_test,vt,cl);
            break;
        
        default:
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

    } catch(Views::Error& err){
        std::cerr<<err.getMessage()<<'\n';
    }

    return 0;
}