// sets the terminal to non-canonical mode
//


#ifndef HEADER
#define HEADER
#include "header.h"
#endif

void orig_terminal() {
  tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_term);
}

void set_terminal() {

  if(tcgetattr(STDIN_FILENO, &orig_term)==-1){
      cerr<<"Failed to proceed(11)";
      exit(11);
  }
  atexit(orig_terminal);
  
  struct termios new_term = orig_term;
  
  new_term.c_lflag &= ~(ECHO | ICANON);
  new_term.c_oflag &= ~(OPOST);

  if(tcsetattr(STDIN_FILENO, TCSAFLUSH, &new_term)==-1){
      cerr<<"Failed to Proceed(12)";
      exit(12);
  }
}