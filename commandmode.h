//
//cmdMode controls and checks the validity of the commands and tranforms paths of the files into absolute 
// and call the appropriate functions by passing this paths as an args
//

#ifndef HEADER
#define HEADER

#include "header.h"

#endif

void cmdMode()
{
    printf(">> ");
    goto(winx,1);
    printf("\033[0K");
    goto(winx-1,1);
    printf("\033[31m");

    //setting status bar with supportable commands 
    printf("commands(#args)::copy(.) move(.) rename(2) create_file(2) create_dir(2) delete_file(1) delete_dir(1) goto(1) search(1) esc");
    printf("\033[39m");
    goto(4,4);
    vector<string> cmd;
    char ch;
    while(1){
        int i=0;
        cmd.clear();
        cmd.push_back("");
        while((ch=getchar())!='\n'){   /// reads character and stores it in string vector till enter doesnt hit
            if(ch==27)return;          // if escape hits then come out of the command mode
            if(ch==127){
                cmd.clear();
                i=0;
                cmd.push_back("");
                goto(4,4);
                printf("\033[0K");
                goto(4,4);
                continue;
            }
            printf("%c",ch);
            if(ch==' '){
                ++i;
                cmd.push_back("");
                continue;
            }
            cmd[i]+=ch;
        }
        if(cmd[0]=="copy"||cmd[0]=="move"){ ///// if copy or move command
            if(cmd.size()<3){               ///// number of arguments should be greater than 3
                prntstatus("lesser arguments");
            }
            else{ 
            char *pth=NULL;
            char *des=NULL;
            int i=1;
            string temp;
            if(cmd[cmd.size()-1][0]=='~'&&cmd[cmd.size()-1][1]=='/'){
                temp="/home/"+(string)getenv("USER")+"/"+cmd[cmd.size()-1].substr(2,cmd[cmd.size()-1].length()-2);
            }
            else{
                temp=cmd[cmd.size()-1];
            }
            while(i<=cmd.size()-2){

                if(pth)free(pth);
                
                if(cmd[i][0]=='/'){
                    
                    string extract=""; 
                    for(int j=cmd[i].length()-1;j>=0;j--){
                        if(cmd[i][j]=='/')break;
                        extract=cmd[i][j]+extract;
                    }

                    string fdes=temp+"/"+extract;
                    des= new char[fdes.length()+1];
                    strcpy(des,fdes.c_str());

                    pth=new char[cmd[i].length()+1];
                    strcpy(pth,cmd[i].c_str());
                }
                else{

                    string fdes=temp+"/"+cmd[i];
                    des= new char[fdes.length()+1];
                    strcpy(des,fdes.c_str());

                    string temp2=(string)cwd+"/"+cmd[i];
                    pth=new char[temp2.length()+1];
                    strcpy(pth,temp2.c_str());
                }
        
                struct stat pthstat;
                stat(pth,&pthstat);
                if(S_ISDIR(pthstat.st_mode)){
                    if(cmd[0]=="copy"){
                        if(!cpydir(pth,des)){
                            prntstatus("successful");
                        }
                    }
                    else {
                        bool flag=cpydir(pth,des);
                        if(!flag)
                            if(!deldir(pth)){
                                prntstatus("successful");
                            }
                        
                    }
                }
                else{
                    if(cmd[0]=="copy"){
                        if(!cpyfile(pth,des)){
                            prntstatus("successfull");
                        }
                    }
                    else{
                        bool flag=cpyfile(pth,des);
                        if(!flag)
                            if(!delfile(pth)){
                                prntstatus("successful");
                            }
                    }
                }
                i++;
            }

            }
        }
        else if(cmd[0]=="rename"){     // if rename command

            if(cmd.size()!=3){
                prntstatus("Invalid number of argumets");
            }            
            else{
                char *ol=NULL;
                char *nw=NULL;
                if(cmd[1][0]=='/'){
                    ol=new char[cmd[1].length()+1];
                    strcpy(ol,cmd[1].c_str());
                    if(cmd[2][0]!='/'){
                        prntstatus("please pass the paths either absolute or relative");
                        continue;
                    }
                    nw=new char[cmd[2].length()+1];
                    strcpy(nw,cmd[2].c_str());
                    if(!renamFilDir(ol,nw)){
                        prntstatus("successful");
                    }
                }
                else{
                    string temp=(string)cwd+"/"+cwd[1];
                    ol=new char[temp.length()+1];
                    strcpy(ol,temp.c_str());
                    if(cmd[2][0]=='/'){
                        prntstatus("please pass the paths either absolute or relative");
                        continue;
                    }
                    temp=(string)cwd+"/"+cwd[2];
                    nw=new char[temp.length()+1];
                    strcpy(nw,temp.c_str());
                    if(!renamFilDir(ol,nw)){
                        prntstatus("successful");
                    }
                }
                free(nw);
                free(ol);
            }
        }

        else if(cmd[0]=="delete_file" || cmd[0]=="delete_dir"){  /// if delete_file or delete_dir command

            if(cmd.size()!=2){
                prntstatus("Invalid number of argumets");
            }
            else{
                char *pth;
                string temp=string(cwd)+"/"+cmd[1];
                pth=new char[temp.length()+1];
                strcpy(pth,temp.c_str());
                if(cmd[0]=="delete_file"){
                    if(!delfile(pth)){
                        prntstatus("successful");
                    }
                }
                else{
                    if(!deldir(pth)){
                        prntstatus("successful");
                    }
                }
                free(pth);
            }
        }

        else if(cmd[0]=="create_file" || cmd[0]=="create_dir"){   //// if create_file or create_dir command
            if(cmd.size()!=3){
                prntstatus("Invalid number of argumets");
            }
            else{
                char *des;
                string desstr;
                if(cmd[cmd.size()-1][0]=='~'&&cmd[cmd.size()-1][1]=='/'){
                    desstr="/home/"+(string)getenv("USER")+"/"+cmd[cmd.size()-1].substr(2,cmd[cmd.size()-1].length()-2)+"/"+cmd[1];
                }
                else{
                    desstr=cmd[cmd.size()-1]+"/"+cmd[1];
                }
                des=new char[desstr.length()+1];
                strcpy(des,desstr.c_str());
                if(cmd[0]=="create_file"){
                    if(!createfle(des)){
                        prntstatus("successful");
                    }
                }
                else{
                    if(!createdir(des)){
                        prntstatus("successful");
                    }
                }
                free(des);
            }
        }

        else if(cmd[0]=="goto"){    //// if goto command

            if(cmd.size()!=2){
                prntstatus("Invalid number of arguments");
            }
            else{
                char *pth=new char[cmd[1].length()+1];
                strcpy(pth,cmd[1].c_str());
                DIR *d=opendir(pth);
                if(d){
                    closedir(d);
                    strcpy(cwd,cmd[1].c_str());
                    prntstatus("Successful, current working directory::"+(string)cwd);
                }
                else{
                    prntstatus("Invalid path::"+cmd[1]);
                }
                free(pth);
            }
        }

        else if(cmd[0]=="search"){    /// if search command

            if(searchpth(cmd[1],cwd)){
                prntstatus("True");
            }
            else prntstatus("False");
        }
        else prntstatus("command not found");    /// prints error for invalid command

    
        goto(4,4);
        printf("\033[0K");
        goto(4,4);
    }
}
