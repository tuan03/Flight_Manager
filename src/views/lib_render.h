#pragma once
#include<SDL.h>
#include<SDL_image.h>
#include<SDL_ttf.h>
#include"views_error.h"
#define FPS 60
#define TIME_A_FRAME (1000/FPS)


namespace MyFunc{
    bool check_click(int x, int y, SDL_Rect rect){
        if(x>=rect.x && x<= rect.x + rect.w && y>=rect.y && y<=rect.y + rect.h){
            return true;
        }
        return false;
    }
}
class SDLInit {
public:
    SDLInit() {
        // std::cout<<"Init SDL\n";
        if (SDL_Init(SDL_INIT_VIDEO) != 0) throw Views::Error(Views::Name_Error::CAN_NOT_INIT_SDL);
        if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG) throw Views::Error(Views::Name_Error::CAN_NOT_INIT_IMG);
        if (TTF_Init() != 0) throw Views::Error(Views::Name_Error::CAN_NOT_INIT_TTF);
        
    }
    ~SDLInit() {
        TTF_Quit();
        IMG_Quit();
        SDL_Quit();
        // std::cout<<"Quit SDL\n";
    }
};

class MyWindow{
    private:
    SDL_Window* window = nullptr;
    public:
    MyWindow(const char* nameProgram,int screen_width,int screen_height){
        // std::cout<<"Init Window\n";
        this->window = SDL_CreateWindow(nameProgram, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screen_width, screen_height,SDL_WINDOW_SHOWN);
        if (this->window == nullptr) throw Views::Error(Views::Name_Error::CAN_NOT_CREATE_WINDOW);
        
    }
    SDL_Window* get_window() const {
        return this->window;
    }
    ~MyWindow(){
        SDL_DestroyWindow(window);
        // std::cout<<"Destroy Window\n";
    }
};
class MyRenderer{
    private:
    SDL_Renderer* renderer = nullptr;
    public:
    MyRenderer(SDL_Window* window){
        // std::cout<<"Init Renderer\n";
        this->renderer = SDL_CreateRenderer(window, -1, 0);
        if (this->renderer == nullptr) throw Views::Error(Views::Name_Error::CAN_NOT_CREATE_RENDERER);
    }
    SDL_Renderer* get_renderer() const {
        return this->renderer;
    }

    ~MyRenderer(){
        SDL_DestroyRenderer(renderer);
        // std::cout<<"Destroy Renderer\n";
    }
};
class MyFont{
    private:
    TTF_Font* font ;
    int fontSize;
    std::string fontName;
    public:
    MyFont(const char* nameFileFont, int fontSize){
        // std::cout<<"Load Font\n";
        this->font = TTF_OpenFont(nameFileFont, fontSize);
        if(!this->font) throw Views::Error(Views::Name_Error::CAN_NOT_OPEN_FONT);
        this->fontSize=fontSize;
        this->fontName = nameFileFont;
    }
    TTF_Font* get_font() const{
        return font;
    }
    int get_font_size() const {
        return fontSize;
    }
    std::string get_font_name() const {
        return fontName;
    }
    ~MyFont(){
            TTF_CloseFont(font);
            // std::cout<<"Destroy Font\n";
    }
};
class MyTexture{
    private:
    SDL_Texture* texture = nullptr;
    public:
    MyTexture(const char* file,SDL_Renderer* renderer) {
        // std::cout<<"Create Texture\n";
        SDL_Surface* image = IMG_Load(file);    //load ảnh vào surface
        if (image == nullptr) throw Views::Error(Views::Name_Error::CAN_NOT_GET_IMG);
        this->texture = SDL_CreateTextureFromSurface(renderer, image); 
        SDL_FreeSurface(image); //xóa surface
        if(this->texture == nullptr) throw Views::Error(Views::Name_Error::CAN_NOT_CREATE_TEXTURE);
    }
    SDL_Texture* get_texture() const{
        return this->texture;
    }
    ~MyTexture(){
            SDL_DestroyTexture(this->texture);
            // std::cout<<"Delete a texture\n";
    }

};

class MyScreen {
    private:
    SDLInit sdl;    
    MyWindow* mywindow = nullptr;
    MyRenderer* myrenderer = nullptr;
    MyFont* myfont = nullptr;
    int screen_width;       //kích thước màn hình, để sau này resposive sau
    int screen_height;
    public:
    MyScreen(int width, int height,const char * nameProgram, const char * fileFont, int fontSize){
        // std::cout<<"Create Screen\n";
        mywindow = new MyWindow(nameProgram,width,height);
        screen_width = width;
        screen_height = height;
        myrenderer = new MyRenderer(mywindow->get_window());
        myfont = new MyFont(fileFont,fontSize);
    }
    ~MyScreen(){      
        delete myfont;
        delete myrenderer;
        delete mywindow;
        // std::cout<<"Quit Screen\n";
        TTF_Quit();
        IMG_Quit();
        SDL_Quit();
    }
    MyWindow* get_my_window() const {
        return mywindow;
    }
    SDL_Window* get_window() const {
        return mywindow->get_window();
    }
    MyRenderer* get_my_renderer() const{
        return myrenderer;
    }
    SDL_Renderer* get_renderer() const {
        return myrenderer->get_renderer();
    }
    
    void set_font_size(int font_size){
        std::string fontName = this->myfont->get_font_name();
        delete myfont;
        myfont = new MyFont(fontName.c_str(),font_size);
    }
    void render_cot(SDL_Rect rect, SDL_Color fill = {222, 252, 249, 255}, SDL_Color vien = {0, 0, 0, 255}){ // fill nên xanh nhạt dễ thw :3 :3
                SDL_Rect content = {rect.x+1,rect.y+1,rect.w - 2,rect.h - 2};
                SDL_SetRenderDrawColor(myrenderer->get_renderer(), vien.r,vien.g,vien.b,vien.a); // màu đen
                SDL_RenderFillRect(myrenderer->get_renderer(), &rect);
                SDL_SetRenderDrawColor(myrenderer->get_renderer(), fill.r,fill.g,fill.b,fill.a); 
                SDL_RenderFillRect(myrenderer->get_renderer(), &content);
    }

    void render_table(int n, int* arr,string* name_cot){ //n : số cột, arr: mảng chứa độ rộng từng cột liên tiếp // dùng cho các views
            SDL_Rect rect = {X_START_TABLE,Y_START_TABLE,0,0};
            SDL_Rect rect_text;
            for(int i=0; i<n;i++){
                rect = {rect.x + rect.w , 290,arr[i],HEIGHT_TABLE};
                this->render_cot(rect);
                rect_text = {rect.x,rect.y-50,rect.w,50};
                this->render_Text(name_cot[i],rect_text,{0,0,0},true);
            }
        }


    void blur_background(int alpha){
        SDL_Surface* surface = IMG_Load("src/views/img/blur.png");
        SDL_Texture* texture = SDL_CreateTextureFromSurface(this->get_my_renderer()->get_renderer(), surface);
        SDL_FreeSurface(surface);
        SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
        SDL_SetTextureAlphaMod(texture, alpha); 
        SDL_Rect destRect = {0, 0, WIDTH_SCREEN, HEIGHT_SCREEN};
        SDL_RenderCopy(this->get_my_renderer()->get_renderer(), texture, NULL, &destRect);
    }

    
    void render_Text(const std::string& text,SDL_Rect vitri,SDL_Color text_color,bool type_center_box = false, SDL_Rect* rect_return = nullptr){ // true: in text giữa box vitri, false: in text tại vitri
        SDL_Color textColor = text_color;
        SDL_Surface* textSurface = TTF_RenderUTF8_Blended(myfont->get_font(), text.c_str(), textColor); // thay thành TTF_RenderText_Solid để tối ưu nhưng text sẽ xấu :v // tiếng viêt : TTF_RenderUTF8_Solid
        SDL_Texture* textTexture = SDL_CreateTextureFromSurface(myrenderer->get_renderer(), textSurface);

        if(type_center_box == false){
            vitri.w =  (textSurface != NULL ? textSurface->w : vitri.w = 0);
            vitri.h = myfont->get_font_size();
            SDL_RenderCopy(myrenderer->get_renderer(), textTexture, NULL, &vitri);

        } else {
            SDL_Rect vt_render;
            vt_render.w =  (textSurface != NULL ? textSurface->w : vt_render.w = 0);
            vt_render.h = myfont->get_font_size();
            SDL_Rect vt_box = vitri ; //box->get_rect()
            vt_render.x = vt_box.x + (vt_box.w/2) - (vt_render.w/2);
            vt_render.y = vt_box.y + (vt_box.h/2) - (vt_render.h/2);
            SDL_RenderCopy(myrenderer->get_renderer(), textTexture, NULL, &vt_render);
            if(rect_return != nullptr) *rect_return = vt_render;
        }
            SDL_FreeSurface(textSurface);
            SDL_DestroyTexture(textTexture);
    }
    void render_Text(const char* text,SDL_Rect vitri,SDL_Color text_color,bool type_center_box = false, SDL_Rect* rect_return = nullptr){ // true: in text giữa box vitri, false: in text tại vitri
        SDL_Color textColor = text_color;
        SDL_Surface* textSurface = TTF_RenderUTF8_Blended(myfont->get_font(), text, textColor); // thay thành TTF_RenderText_Solid để tối ưu nhưng text sẽ xấu :v // tiếng viêt : TTF_RenderUTF8_Solid
        SDL_Texture* textTexture = SDL_CreateTextureFromSurface(myrenderer->get_renderer(), textSurface);

        if(type_center_box == false){
            vitri.w =  (textSurface != NULL ? textSurface->w : vitri.w = 0);
            vitri.h = myfont->get_font_size();
            SDL_RenderCopy(myrenderer->get_renderer(), textTexture, NULL, &vitri);

        } else {
            SDL_Rect vt_render;
            vt_render.w =  (textSurface != NULL ? textSurface->w : vt_render.w = 0);
            vt_render.h = myfont->get_font_size();
            SDL_Rect vt_box = vitri ; //box->get_rect()
            vt_render.x = vt_box.x + (vt_box.w/2) - (vt_render.w/2);
            vt_render.y = vt_box.y + (vt_box.h/2) - (vt_render.h/2);
            SDL_RenderCopy(myrenderer->get_renderer(), textTexture, NULL, &vt_render);
            if(rect_return != nullptr) *rect_return = vt_render;
        }
            SDL_FreeSurface(textSurface);
            SDL_DestroyTexture(textTexture);
    }
};
enum Name_Box{
    NONE,
    PLANE,
    FLIGHT,
    CUSTOMER,
    TICKET,
    THONGKE,
    PREV,
    NEXT
};
class Box{
    private:
    MyTexture* mytexture = nullptr; //chứa texture
    SDL_Rect rect;                  // chứa vị trí, kích thước render
    bool is_clone = false;          //check xem phải là Box clone không, để không cần xóa texture của Box này, vì box được clone xóa rồi
    Name_Box namebox;               //đặt tên cho Box, đễ truy vấn
    Box* next;                      //danh sách liên kết đơn
    MyTexture* hover = nullptr;   
    MyTexture* clicked = nullptr; 
     public:
    Box(){
        next = nullptr; 
    }
    ~Box(){
        if(!is_clone) delete mytexture;
        delete hover;
        delete clicked;
        // std::cout<<"Delete a box\n";
        delete next;
    }
    MyTexture* get_my_texture(){
        return mytexture;
    }
    SDL_Rect& get_rect(){
        return this->rect;
    }
    Name_Box get_name_box(){
        return this->namebox;
    }
    Box* set_name_box(Name_Box n){
        this->namebox = n;
        return this;
    }
    Box* get_next(){
        return next;
    }
    Box* set_hover(const char* file, MyRenderer* renderer){
        this->hover = new MyTexture(file,renderer->get_renderer());
        return this;
    }
    Box* set_clicked(const char* file, MyRenderer* renderer){
        this->clicked = new MyTexture(file,renderer->get_renderer());
        return this;
    }
    void set_next(Box*& box){
        next = box;
    }
    void create(const char * file, MyRenderer* renderer){
        mytexture = new MyTexture(file,renderer->get_renderer());
    }
    void create_from(Box* box){ //clone box
        mytexture = box->get_my_texture();
        this->is_clone = true;
    }

    void set_rect(int x, int y, int w, int h){
        this->rect = {x,y,w,h};
    }
    void set_rect(SDL_Rect& rect){
        this->rect = rect;
    }
    void render(MyRenderer* renderer, int choose = 0){ //true: render texture chính, false: render convert
        if(choose == 0){
            if(mytexture!=nullptr)
            SDL_RenderCopy(renderer->get_renderer(),mytexture->get_texture(),nullptr,&this->rect);
            return;
        }
        if(choose == 1){
            if(hover!=nullptr)
            SDL_RenderCopy(renderer->get_renderer(),hover->get_texture(),nullptr,&this->rect);
            return;
        }
        if(choose == 2){
            if(clicked!=nullptr)
            SDL_RenderCopy(renderer->get_renderer(),clicked->get_texture(),nullptr,&this->rect);
            return;
        }


    }
    
    bool is_in_box(int x, int y){
        return (x>=this->rect.x) && (x<=this->rect.x+this->rect.w) && (y>=this->rect.y) && (y<=this->rect.y+this->rect.h);
    }
};


class ListBox{
    private:
    Box* head;
    MyRenderer* renderer;
    public:
    ListBox(){
        head = nullptr;
        renderer = nullptr;
    }
    void connect_my_renderer(MyRenderer* renderer){
        this->renderer = renderer;
    }
  
    Box* insert(const char * file, SDL_Rect rect, Name_Box name_box = Name_Box::NONE){ // thêm box no name
        //create box
        Box* newBox = new Box;
        if(!renderer) throw Views::Error(Views::Name_Error::UNKNOWN_RENDERER);
        newBox->create(file,this->renderer);
        newBox->set_rect(rect);
        newBox->set_name_box(name_box);
        //add
        if(this->head == nullptr){
            this->head = newBox;
            return newBox;
        }
        Box* current = head;
        while (current->get_next() != nullptr)
        {
            current = current->get_next();
        }
        current->set_next(newBox);
        return newBox;
    }
    
    Box* insert_clone(Box* box, SDL_Rect rect){ // clone box, noname
        //create box
        Box* newBox = new Box;
        if(!renderer) throw Views::Error(Views::Name_Error::UNKNOWN_RENDERER);
        newBox->create_from(box);
        newBox->set_rect(rect);
        //add
        if(this->head == nullptr){
            this->head = newBox;
            return newBox;
        }
        Box* current = head;
        while (current->get_next() != nullptr)
        {
            current = current->get_next();
        }
        current->set_next(newBox);
        return newBox;
    }

    void render_list(){ //render list lên cửa sổ
        Box* current = head;
        while (current != NULL) {
            current->render(renderer);
            current = current->get_next();
        }
    }
    void render_list_ver2(Name_Box& namebox, Name_Box& current_route){ //render list lên cửa sổ
        Box* current = head;
        while (current != NULL) {
            if(current_route != Name_Box::NONE && current->get_name_box() == current_route){
                current->render(renderer,2);
                current = current->get_next();
                continue;
            }
            if(namebox != Name_Box::NONE && current->get_name_box() == namebox){
                current->render(renderer,1);
            } else {
                current->render(renderer);
            }
            current = current->get_next();
        }
    }
    Box* checkClick(int x, int y){ //kiểm tra click cái nào ?
        Box* current = this->head;
        while (current != nullptr)
        {
            if(current->is_in_box(x,y))  return current;
            current = current->get_next();
        }
        return nullptr;
        
    }
    ~ListBox(){
        delete head;
        // std::cout<<"Delete Listbox\n"; 
    }
    Box* operator[] (int index){
        Box* current = head;
        int i=0;
        while (current != NULL) {
            if(index == i){
                return current;
            }
            current = current->get_next();
            i++;
        }
        return nullptr;
    }
    Box* operator[] (Name_Box name){
        Box* current = head;
        while (current != NULL) {
            if(current->get_name_box() == name){
                return current;
            }
            current = current->get_next();
        }
        return nullptr;
    }
};

