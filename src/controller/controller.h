#pragma once
#include "../header.h"
#include "../views/component.h"
#include "../views/views_customer.h"
#include "../views/views_flight.h"
#include "../views/views_plane.h"
#include "../views/views_thongke.h"
#include "../views/views_ticket.h"
// BoxComponents components_on_route

#include "../model/thread_update_status_cb.h"

class Controller
{
private:
    Global_Variable global;
    ListBox menu;

    int route_plane_width[5]{
        150,
        250,
        600,
        250,
        250,
    };
    string route_plane_name_cot[6]{"STT", "Số Hiệu MB", "Loại", "Số Dãy", "Số Dòng"};

    int route_flight_width[7]{100, 200, 200, 450, 200, 200, 150};
    string route_flight_name_cot[7]{"STT", "Mã Số CB", "Sân Bay Đến", "Thời Gian Bay", "Trạng Thái", "Số Hiệu MB", "Trạng Thái Vé"};

    int route_customer_width[6]{100, 280, 280, 280, 280, 280};
    string route_customer_name_cot[6]{"STT", "Vé", "Họ", "Tên", "Số CMND", "Giới Tính"};

    int route_thongke_width[3]{200, 600, 700};
    string route_thongke_name_cot[3]{"STT", "Mã Số CB", "Số Lượt Bay"};

    bool is_home = true;

public:
    Controller()
    {
        menu.connect_my_renderer(global.get_myscreen().get_my_renderer()); //
        menu.insert("src/views/img/ve1.jpg", {50, 25, 300, 100}, Name_Box::HOME)->set_hover("src/views/img/ve2.jpg", global.get_myscreen().get_my_renderer())->set_clicked("src/views/img/ve3.jpg", global.get_myscreen().get_my_renderer());
        menu.insert("src/views/img/plane1.png", {400, 25, 300, 100}, Name_Box::PLANE)->set_hover("src/views/img/plane2.png", global.get_myscreen().get_my_renderer())->set_clicked("src/views/img/plane3.png", global.get_myscreen().get_my_renderer());
        menu.insert("src/views/img/chuyenbay1.jpg", {750, 25, 300, 100}, Name_Box::FLIGHT)->set_hover("src/views/img/chuyenbay2.jpg", global.get_myscreen().get_my_renderer())->set_clicked("src/views/img/chuyenbay3.jpg", global.get_myscreen().get_my_renderer());
        menu.insert("src/views/img/custom1.jpg", {1100, 25, 300, 100}, Name_Box::CUSTOMER)->set_hover("src/views/img/custom2.jpg", global.get_myscreen().get_my_renderer())->set_clicked("src/views/img/custom3.jpg", global.get_myscreen().get_my_renderer());
        menu.insert("src/views/img/thongke1.jpg", {1450, 25, 300, 100}, Name_Box::THONGKE)->set_hover("src/views/img/thongke2.jpg", global.get_myscreen().get_my_renderer())->set_clicked("src/views/img/thongke3.jpg", global.get_myscreen().get_my_renderer());
        menu.insert("src/views/img/body.png", {X_START_BODY, Y_START_BODY, W_BODY, H_BODY});
    }

    void running()
    {
        try
        {
            // Khởi tạo các route
            bool flag_re_render_list_cb = false;
            View_Plane view_plane(global, flag_re_render_list_cb);
            View_Flight view_flight(global, flag_re_render_list_cb); // khởi tạo view Plane
            View_Customer view_customer(global);
            View_Thongke view_thongke(global);
            // end
            std::mutex myMutex;
            bool quit = false; // điều kiện thoát chương trình

            std::thread thread_update_status_cb(run_list, std::ref(this->global.get_qlcb().getListCB()), std::ref(this->global.get_qlcb().getListMB()), std::ref(flag_re_render_list_cb), std::ref(quit), std::ref(myMutex));

            /*
                - sau khi máy bay hoàn thành, thì phải đợi 1 tiếng sau mới tiếp tục thực hiện chuyến bay ( thời gian chuẩn bị).
            */

            SDL_Event e;
            Uint32 timeCurrent = SDL_GetTicks(); // tại fps
            Uint32 timePre = SDL_GetTicks();     // tạo fps
            int frames = 0;
            Box *get_box_hover = nullptr;            // để lấy lấy box đang hover, null nếu khoogn trên box nào
            Name_Box current_hover = Name_Box::NONE; // route đnag hover trên thanh menu
            Name_Box current_route = Name_Box::HOME; // route hiện tại đang ở
            int mouse_X, mouse_Y;
            while (!quit)
            {
                while (SDL_PollEvent(&e) != 0)
                {
                    if (e.type == SDL_QUIT)
                    { // sự kiện nhất thoát
                        myMutex.lock();
                        quit = true;
                        myMutex.unlock();
                        break;
                    }
                    if (e.type == SDL_MOUSEMOTION)
                    {
                        SDL_GetMouseState(&mouse_X, &mouse_Y);
                        get_box_hover = menu.checkClick(mouse_X, mouse_Y);
                        if (get_box_hover != nullptr)
                        {
                            current_hover = get_box_hover->get_name_box();
                        }
                        else
                        {
                            current_hover = Name_Box::NONE;
                        }
                    }
                    if (global.get_thong_bao().is_display())
                    {
                        global.get_thong_bao().handleEvent(e, mouse_X, mouse_Y);
                    }
                    else
                    {
                        if (is_home && e.type == SDL_MOUSEBUTTONDOWN)
                        { // sự kiện nhấn vào các box
                            if ((current_hover != Name_Box::NONE) && (current_route != current_hover))
                            {
                                current_route = current_hover; // chuyển route
                                if (current_route == Name_Box::CUSTOMER)
                                {
                                    view_customer.re_render_data();
                                }
                            }
                        }
                        // bắt sự kiện route Plane
                        if (current_route == Name_Box::PLANE)
                        {
                            view_plane.handleEvent(e, is_home, mouse_X, mouse_Y);
                        }
                        else if (current_route == Name_Box::FLIGHT)
                        {
                            view_flight.handleEvent(e, is_home, mouse_X, mouse_Y);
                        }
                        else if (current_route == Name_Box::CUSTOMER)
                        {
                            view_customer.handleEvent(e, is_home, mouse_X, mouse_Y);
                        }
                        else if (current_route == Name_Box::THONGKE)
                        {
                            view_thongke.handleEvent(e, is_home, mouse_X, mouse_Y);
                        }
                    }
                }

                // render
                SDL_SetRenderDrawColor(global.get_myscreen().get_my_renderer()->get_renderer(), 255, 255, 255, 0);
                SDL_RenderClear(global.get_myscreen().get_my_renderer()->get_renderer());
                menu.render_list_ver2(current_hover, current_route); // render thanh menu
                switch (current_route)
                {
                case Name_Box::PLANE:
                    view_plane.render();
                    break;
                case Name_Box::FLIGHT:
                    view_flight.render();
                    break;
                case Name_Box::CUSTOMER:
                    view_customer.render();
                    break;
                case Name_Box::HOME:
                    global.get_c_component().logo_maybay.render(global.get_myscreen().get_my_renderer()); // rename
                    global.get_myscreen().render_Text("HỌC VIỆN CÔNG NGHỆ BƯU CHÍNH VIỄN THÔNG CƠ SỞ TP.HỒ CHÍ MINH", {350 + X_START_BODY, 105 + Y_START_BODY, 1000, 50}, {0, 0, 0}, true);
                    global.get_myscreen().render_Text("PHẦN MỀM QUẢN LÍ CHUYẾN BAY", {500 + X_START_BODY, 390 + Y_START_BODY, 700, 50}, {0, 0, 0}, true);
                    global.get_c_component().logo_ptit.render(global.get_myscreen().get_my_renderer()); // rename
                    break;
                case Name_Box::THONGKE:
                    view_thongke.render();

                    break;

                default:
                    // global.get_c_component().plane_at_homepage.render(global.get_myscreen().get_my_renderer());  // rename
                    break;
                }
                global.get_thong_bao().render();

                SDL_RenderPresent(global.get_myscreen().get_my_renderer()->get_renderer());
                // render
                //  // tạo fps
                //  timeCurrent = SDL_GetTicks();
                //  if(timeCurrent-timePre < TIME_A_FRAME){
                //      SDL_Delay(TIME_A_FRAME - (timeCurrent-timePre));
                //  }
                //  timePre = SDL_GetTicks();

                // //end
                frames++;
                int elapsedTime = SDL_GetTicks() - timeCurrent;
                if (elapsedTime >= 1000)
                {
                    // std::cout << "FPS: " << frames << std::endl;
                    timeCurrent = SDL_GetTicks();
                    frames = 0;
                }
            }
            thread_update_status_cb.join();
        }
        catch (const char *error)
        {
            std::cerr << error << '\n';
        }
        catch (Views::Error &error)
        {
            std::cerr << error.getMessage() << '\n';
        }
        catch (const std::runtime_error &e)
        {
            // Xử lý khi lỗi std::runtime_error xảy ra
            std::cout << "Đã xảy ra lỗi std::runtime_error: " << e.what() << std::endl;
        }
        catch (const std::exception &e)
        {
            std::cerr << e.what() << '\n';
        }
        cout << "Den Day";
    }
    ~Controller()
    {
    }
};