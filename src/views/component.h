#ifndef VIEWS_COMPONENT_H
#define VIEWS_COMPONENT_H
#include"../header.h"
class Input{
    private:
        MyScreen* myscreen;
        string* data;
        int max_length = 0;
        bool is_clicked = false;
        bool ok = true;
        SDL_Rect vitri;
    public:
        void set(bool logic){
            this->ok = logic;
        }
        void handleInput_IN_HOA_KHONG_CACH(SDL_Event e , int x, int y){
            if(ok && e.type == SDL_MOUSEBUTTONDOWN) this->is_clicked = MyFunc::check_click(x,y, this->vitri);
            if(this->is_clicked){
                switch(e.type){
                    case SDL_KEYDOWN:
                            if (e.key.keysym.sym == SDLK_BACKSPACE && (*data).length() > 0)
                            {
                                (*data).pop_back();
                            }
                    break;
                    case SDL_TEXTINPUT:
                        if((*data).length() < max_length){
                            if(e.text.text[0] >= 'A' && e.text.text[0] <= 'Z') *data += e.text.text; 
                            else if(e.text.text[0] >= 'a' && e.text.text[0] <= 'z') *data +=  e.text.text[0] - ('a'-'A');
                        }
                    break;
                }
            }
        }
        void connect(MyScreen* mc){
            this->myscreen = mc;
        }
        void connect_data(string* str, int max_length){
            this->data = str;
            this->max_length = max_length;
        }
        void set_vitri(SDL_Rect rect){
            this->vitri = rect;
        }
        void render(){
           
            SDL_Rect box_input{vitri.x+3,vitri.y + 3,vitri.w - 6,vitri.h-6};
            myscreen->render_cot(vitri,{0,0,0});
            if(this->is_clicked)
                myscreen->render_cot(box_input);
            else
                myscreen->render_cot(box_input,{255,255,255});
            SDL_Rect con_tro;
            myscreen->render_Text(*data,box_input,{0,0,0},true,&con_tro);
            if(this->is_clicked){
                con_tro.x = con_tro.x + con_tro.w + 2;
                con_tro.w = 2;
                myscreen->render_cot(con_tro);
            }
        }
};



#endif