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

    Box homepage;
    homepage.create("src/views/img/plane_img.png",myscreen.get_my_renderer());
    homepage.set_rect(500,190,800,700);
    Box prev;
    prev.create("src/views/img/prev.png",myscreen.get_my_renderer());
    prev.set_rect(760,815,80,80);
    Box next;
    next.create("src/views/img/next.png",myscreen.get_my_renderer());
    next.set_rect(960,815,80,80);



    ListBox menu;
    menu.connect_my_renderer(myscreen.get_my_renderer());
    menu.insert("src/views/img/plane1.png",{50,25,300,100},Name_Box::PLANE)->set_hover("src/views/img/plane2.png",myscreen.get_my_renderer())->set_clicked("src/views/img/plane3.png",myscreen.get_my_renderer());
    menu.insert("src/views/img/chuyenbay1.jpg",{400,25,300,100},Name_Box::FLIGHT)->set_hover("src/views/img/chuyenbay2.jpg",myscreen.get_my_renderer())->set_clicked("src/views/img/chuyenbay3.jpg",myscreen.get_my_renderer());
    menu.insert("src/views/img/custom1.jpg",{750,25,300,100},Name_Box::CUSTOMER)->set_hover("src/views/img/custom2.jpg",myscreen.get_my_renderer())->set_clicked("src/views/img/custom3.jpg",myscreen.get_my_renderer());
    menu.insert("src/views/img/ve1.jpg",{1100,25,300,100},Name_Box::TICKET)->set_hover("src/views/img/ve2.jpg",myscreen.get_my_renderer())->set_clicked("src/views/img/ve3.jpg",myscreen.get_my_renderer());
    menu.insert("src/views/img/thongke1.jpg",{1450,25,300,100},Name_Box::THONGKE)->set_hover("src/views/img/thongke2.jpg",myscreen.get_my_renderer())->set_clicked("src/views/img/thongke3.jpg",myscreen.get_my_renderer());



    int x_start_body = 50;
    int y_statrt_body = 150;
    menu.insert("src/views/img/body.png",{x_start_body,y_statrt_body,1700,780});

    SDL_SetRenderDrawBlendMode(myscreen.get_my_renderer()->get_renderer(), SDL_BLENDMODE_BLEND);

    //end test
    bool quit = false; // điều kiện thoát chương trình
    SDL_Event e;
    Uint32 timeCurrent = SDL_GetTicks();
    Uint32 timePre = SDL_GetTicks();
    int mouseX,mouseY,x,y;
    Box* get_box_hover = nullptr;
    Name_Box current_hover = Name_Box::NONE;
    Name_Box current_route = Name_Box::NONE;
    int pos_current = 0;
    int page = 1;
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

                pos_current =( y - 290 ) / 50;





                break;
                case SDL_MOUSEBUTTONDOWN: // sự kiện nhấn vào các box
                    if(current_hover != Name_Box::NONE)
                        current_route = current_hover;
                    if(page > 1){
                    if(prev.is_in_box(x,y)){
                        page-=1;
                    }
                    } 
                    if(page <10){
                    if(next.is_in_box(x,y)){
                        page+=1;
                    }
                    }
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



        SDL_Rect rect;
        SDL_Rect content;
        SDL_Rect rect__text;
        string textt;
        int route_plane_width[6]{150,200,500,250,250,150};
        string name_cot[6]{"STT","Mã Số CB","Loại","Số Dãy","Số Dòng","Trạng Thái"};
        switch (current_route)
        {
        case Name_Box::PLANE :

                // vẽ cột dọc
                rect = {150,290,route_plane_width[0],500};
                for(int i=0; i<6;i++){
                    if(i>=1) rect = {rect.x + route_plane_width[i-1],290,route_plane_width[i],500};
                    myscreen.render_cot(rect);
                    rect__text = {rect.x,rect.y-50,rect.w,50};
                    myscreen.render_Text(name_cot[i],rect__text,{0,0,0},true);
                }
                
                // for(int i=0; i<10; i++){
                if(pos_current>=0 && pos_current <10 && x >=150 && x<=1650){
                rect = {150,290 + 50*pos_current ,1500,50};
                myscreen.render_cot_2(rect);}
                // }
                //render data
                for(int i=0; i< 10; i++){
                    if(i + 10*(page-1) >= qlcb.getListMB().get_so_luong()) break;
                    MayBay* mb = qlcb.getListMB().get_at(i+10*(page-1));
                    rect = {150,290 + i*50,150,50};
                    myscreen.render_Text(std::to_string(i+1), rect,{0,0,0,255},true);
                    rect = {300,290 + i*50,200,50};
                    myscreen.render_Text(mb->getSoHieuMB(), rect,{0,0,0,255},true);
                    rect = {500,290 + i*50,500,50};
                    myscreen.render_Text(mb->getLoaiMB(), rect,{0,0,0,255},true);
                    rect = {1000,290 + i*50,250,50};
                    myscreen.render_Text(std::to_string(mb->getSoDay()), rect,{0,0,0,255},true);
                    rect = {1250,290 + i*50,250,50};
                    myscreen.render_Text(std::to_string(mb->getSoDong()), rect,{0,0,0,255},true);
                    rect = {1500,290 + i*50,150,50};
                    myscreen.render_Text("Mặc Định :v", rect,{0,0,0,255},true);
                }
                //end
                //@
                //render next and prev
                next.render(myscreen.get_my_renderer());
                prev.render(myscreen.get_my_renderer());
                rect = {840,825,120,50};
                myscreen.render_Text(std::to_string(page)+"/"+std::to_string(10), rect,{0,0,0,255},true);
                //end
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

    } catch(Views::Error& err){
        std::cerr<<err.getMessage()<<'\n';
    } catch(const char* err){
        std::cerr<<err<<'\n';
    }

    return 0;
}