///setting up the window and display the current dir

#ifndef HEADER
#define HEADER

#include "header.h"

#endif

// set the window
void setting_up(){

    clr;
    
    if(getWinSize(&winx, &winy)==-1){
        cerr<<"Failed to get windows config(21)";
    }
    pos_top=2;
    pos_bottom=winx-1;
    winsiz=pos_bottom-pos_top+1;

    // for defining terminal working space  
    printf("\x1b[%d;%dr",1,winx);

    x=2;
    y=1;
    goto(winx,1);
    printf("\033[32m");
    printf("for command mode press \":\"");
    printf("\033[39m");
    goto(x,y);
}

//get window size

int getWinSize(int* rows, int* cols){
    
    struct winsize ws;
    if( ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) == -1 || ws.ws_col == 0){
        return -1;
    }
    else {
        *cols = ws.ws_col;
        *rows = ws.ws_row;
    }
    return 0;
}

// display the current directory content 

void displayCuDir(){
    
    getcwd(cwd, sizeof(cwd));
    strcpy(root,cwd);
    getDir();
}