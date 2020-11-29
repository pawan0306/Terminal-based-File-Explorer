#include <bits/stdc++.h>
#include <iostream>
#include <iomanip>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <termios.h>
#include <sys/ioctl.h>
#include <pwd.h>
#include <grp.h>
using namespace std;

//defining macros
#define clr printf("\x1b[2J")
#define goto(x,y) printf("\x1b[%d;%dH",x,y)
#define UP 65
#define DOWN 66
#define RIGHT 67
#define LEFT 68

//function declarations
void normalText();    
void coloredText();
void getDir();
void cmdMode();
int cpyfile(char*,char*);
void prntstatus(string);
int cpydir(char*,char*);
int delfile(char*);
int deldir(char*);
int createfle(char*);
int createdir(char*);
int renamFilDir(char*,char*);
bool searchpth(string,char*);
void clrscreen();
void prntVec();
string getPermStr(struct stat,string);
string getMon(int);
int getWinSize(int*, int*);
void displayCuDir();
void setting_up();
void orig_terminal();
void set_terminal();
void navigate();

//defining "info" struct for storing dir information  
struct info{
    string nme; 
    long sze;
    string perm;
    string grpown;
    string usrown;
    string m;
    int d;
    int hr;
    int min;
};

//declaring global variables
struct termios orig_term;

int pos_top, pos_bottom;
int x,y,temp_x;
int winx,winy;
int winsiz;

stack<string> back_stk;
stack<string> fwd_stk;

char cwd[PATH_MAX];
vector<info> vec;
char root[PATH_MAX];
int top_cu;
int bottom_cu;

