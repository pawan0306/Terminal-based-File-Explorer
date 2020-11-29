//navigation into the file explorer through keys

#ifndef HEADER
#define HEADER

#include "header.h"

#endif

void navigate(){

    while(true){

        char ch=getchar();

        switch((int)ch){

            case 27:{                     //if escape detects

                char ch2=getchar();

                if(ch2==91){              //checks for [
                    
                    char ch3=getchar();
                    switch((int)ch3){

                        case UP:{           //if up key then cursor moves to previous line
                            
                            if(x==pos_top){       
                                if(top_cu>0){

                                    top_cu--;
                                    prntVec();
                                    x=2;y=1;
                                    goto(x,y);
                                    coloredText(); // for coloring the line 
                                }
                            }
                            else if(x>pos_top){
                                goto(x,1);
                                normalText();     
                                goto(--x,1);
                                coloredText();
                            }
                            break;
                        }
                        case DOWN:{  // moves cursor one line down

                            if(x==pos_bottom){
                                if(bottom_cu<(vec.size()-1)){

                                    top_cu++;
                                    prntVec();
                                    x=pos_bottom;y=1;
                                    goto(x,y);
                                    coloredText();
                                }
                            }
                            else if(x<pos_bottom&&x<temp_x){
                                goto(x,1);
                                normalText();
                                goto(++x,1);
                                coloredText();
                            }
                            else ;
                            break;
                        }
                        case RIGHT:{                 // takes the user to next dir
                            if(!fwd_stk.empty()){
                                back_stk.push((string)cwd);
                                strcpy(cwd,fwd_stk.top().c_str());
                                getDir();
                                fwd_stk.pop();
                            }
                            break;
                        }
                        case LEFT:{            // takes to previously visited dir
                            if(!back_stk.empty()){
                                fwd_stk.push((string)cwd);
                                strcpy(cwd,back_stk.top().c_str());
                                getDir();
                                back_stk.pop();
                            }
                            break;
                        }
                    }

                }
                break;
            }
            case 104:{                /* h keys takes user to its home dir that is 
                                      *  from where the execution starts    */
                back_stk.push((string)cwd);
                strcpy(cwd,root);
                getDir();
                prntVec();
                x=2,y=1;
                coloredText();
                break;
            }
            case 107:{     // k key scrolls 10 lines down 

                if(top_cu+10<=(vec.size()-1)){
                    top_cu+=10;
                    prntVec();
                    x=2;y=1;
                    goto(x,y);
                    coloredText();
                }
                break;
            }
            case 105:{     // i key scrolls 10 lines up

                if(top_cu-10>=0){
                    top_cu-=10;
                }
                else{
                    top_cu=0;
                }
                    prntVec();
                    x=2;y=1;
                    goto(x,y);
                    coloredText();
                break;
            }
            case 58:{          // : takes to the command mode
                clrscreen();
                cmdMode();
                goto(winx,1);
                printf("\033[31m");
                printf("For command mode press \":\"");
                printf("\033[39m");
                getDir();
                prntVec();
                x=2;y=1;
                goto(x,y);
                coloredText();
                break;
            }
            case 10:{                    
                // enter takes inside the directory which cursor points
                if(vec[top_cu+x-2].perm[0]=='d'){
                    
                    
                    if(vec[top_cu+x-2].nme==".."){

                        string str=(string)cwd;
                        int i;
                        for(i=str.length()-1;str[i]!='/';i--);
                        str=str.substr(0,i);
                        back_stk.push((string)cwd); 
                        strcpy(cwd,str.c_str());
                        getDir();
                    }

                    // if its file then it opens up in vim editor inside the new terminal

                    else{
                        string str=(string)cwd+'/'+vec[top_cu+x-2].nme;
                        back_stk.push((string)cwd);
                        strcpy(cwd,str.c_str());
                        getDir();
                    }
                }
                else{
                    int i;
                    if((i=fork())==0){
                        string s="vi ";
                        s+=(string)cwd+"/"+vec[top_cu+x-2].nme;
                        char* ch;
                        strcpy(ch,s.c_str());
                        char *cmd[] = {"gnome-terminal","--","/bin/bash","-c",ch,NULL};
                        if(execvp("gnome-terminal",cmd)<0)
                        printf("error occured");
                    }
                }
                break;
            }

            case 127:{          // backspace takes one level up of the present dir
                string prnt=(string)cwd;
                int i;
                if((string)cwd=="/home")break;
                for(i=prnt.length()-1;prnt[i]!='/' && i>=0;i--);
                prnt=prnt.substr(0,i);
                back_stk.push((string)cwd);
                strcpy(cwd,prnt.c_str());
                getDir();
                prntVec();
                x=2,y=1;
                coloredText();
                break;
            }
        }
    }
}
