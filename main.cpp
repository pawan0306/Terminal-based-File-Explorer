#ifndef HEADER
#define HEADER
#include "header.h"
#endif

#include "cmdutils.h"
#include "commandmode.h"
#include "getdir.h"
#include "set_terminal.h"
#include "setWindow.h"
#include "printutils.h"
#include "navigation.h"

int main(){
    set_terminal();   // setting the terminal*********error code (1*) 
    setting_up();
    displayCuDir();
    navigate();
}