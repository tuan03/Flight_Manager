#include"src/controller/controller.h"
#undef main
int main(){
    try{
    Controller ui;
    ui.running();
    return 0;
    } catch(Views::Error& error){
        std::cerr<<error.getMessage()<<'\n';
    }
    catch(const char * error){
        std::cerr<<error<<'\n';
    }
}