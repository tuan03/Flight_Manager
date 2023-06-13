#pragma once
#include "../header.h"

void run_list(ListChuyenBay& list_cb,ListMayBay& list_mb, bool& flag, bool& quit, std::mutex& myMutex){
    int status;
    bool is_change = false;
    Time current_time;
    current_time.get_current_time();
    while (!quit)
    {
        is_change = false;
        for(ChuyenBay* node = list_cb.get_head(); node != nullptr; node = node->get_next()){
            status = node->get_trang_thai_cb();
            if(status != 0 && status != 3){ // không cần check cb đã hủy hoặc hoàn thành
                current_time.get_current_time();
                if(Time::timeDiffInSeconds(node->get_thoi_gian_bay(), current_time) >= (60*60*3)){ // đã cách 3 giwof kể từ thời gian bay
                    myMutex.lock();
                    node->set_trang_thai_cb(3); // set hoàn thành
                    MayBay* temp = list_mb.find_mamb_ct(node->get_so_hieu_mb());
                    temp->tang_so_lan_bay(); // tăng số lần bay của chuyến bay
                    is_change = true;
                    myMutex.unlock();
                }   
            }
        }
        if(is_change) {
            myMutex.lock();
            flag = true;
            myMutex.unlock();
        }
    }
    

}
