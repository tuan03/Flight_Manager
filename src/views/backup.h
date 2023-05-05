class Thong_Bao {
   private:
    string mess = "";
    Box* man_thong_bao = nullptr;
    SDL_Rect ok{980, 700, 200, 50};
    SDL_Rect huy{600, 700, 200, 50};
    SDL_Color c_ok = {255, 255, 255};
    SDL_Color c_huy = {255, 255, 255};
    SDL_Rect ok_error{790, 700, 200, 50};
    bool check_tb = true;

   public:
    void set_box(Box* box) {
        this->man_thong_bao = box;
    }
    void set_mess(string mess) {
        this->mess = mess;
    }
    void handleEvent(SDL_Event e, int mouse_X, int mouse_Y, bool& quit) {
        c_ok = {255, 255, 255};
        c_huy = {255, 255, 255};
        switch (e.type) {
            case SDL_MOUSEMOTION:
                if (MyFunc::check_click(mouse_X, mouse_Y, ok)) {
                    c_ok = {255, 219, 26};
                } else if (MyFunc::check_click(mouse_X, mouse_Y, huy)) {
                    c_huy = {255, 219, 26};
                }
                break;
            case SDL_MOUSEBUTTONDOWN:  // sự kiện nhấn vào các box

                if (MyFunc::check_click(mouse_X, mouse_Y, ok_error)) {
                }
                //    xử lí xác nhận sửa hay lỗi

                if (MyFunc::check_click(mouse_X, mouse_Y, ok)) {
                    // xử lí bấm oke

                } else if (MyFunc::check_click(mouse_X, mouse_Y, huy)) {
                    // xử lý bấm hủy
                }
                break;
            case SDL_QUIT:  // sự kiện nhất thoát
                quit = true;
                break;
        }
    }
    void error(MyScreen& myscreen) {
        man_thong_bao->render(myscreen.get_my_renderer());
        myscreen.render_cot(ok_error, {255, 255, 255});
        myscreen.render_Text("Đồng Ý", ok_error, {0, 0, 0}, true);
        myscreen.render_Text(this->mess, man_thong_bao->get_rect(), {0, 0, 0}, true);
    }
    void warning(MyScreen& myscreen) {
        man_thong_bao->render(myscreen.get_my_renderer());
        myscreen.render_cot(ok, {255, 255, 255});
        myscreen.render_Text("Đồng Ý", ok, {0, 0, 0}, true);
        myscreen.render_cot(huy, {255, 255, 255});
        myscreen.render_Text("Hủy", huy, {0, 0, 0}, true);
    }
};