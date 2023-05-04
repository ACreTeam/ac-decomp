#include "libu64/pad.h"


int pad_physical_stick_x(pad_t* pad){
    return pad->now.stick_x;
}

int pad_physical_stick_y(pad_t* pad){
    return pad->now.stick_y;
}

void pad_set_logical_stick(pad_t* pad, int x, int y){
    pad->off.stick_x = x;
    pad->off.stick_y = y;
}

void pad_correct_stick(pad_t* pad){

    int x = pad_physical_stick_x(pad);
    int y = pad_physical_stick_y(pad);

    pad_set_logical_stick(pad,((x * 60) / 72), ((y * 60) / 72));
}