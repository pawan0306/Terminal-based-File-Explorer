//
// cmdutils contain definition of copy, delete, rename, search and create method
//

#ifndef HEADER
#define HEADER

#include "header.h"

#endif

//----------------copy file ---------------------

int cpyfile(char *pth, char* des){

    char buf[1024];
    int r,w;
    if((r=open(pth,O_RDONLY))<0){
        prntstatus("cannot open "+string(pth));
        return 1;
    }
    if((w=open(des, O_WRONLY|O_CREAT, S_IRUSR|S_IWUSR))<0){
        prntstatus("cannot open "+string(des));
        return 1;
    }
    while((r=read(r,buf,sizeof(buf)))>0)
        write(w,buf,r);
    
    struct stat sstat,dstat;
    if(stat(pth,&sstat)<0){prntstatus("cannot get stat"+(string)pth);return 1;}
    if(stat(des,&dstat)<0){prntstatus("cannot get stat"+(string)des);return 1;}
    
    if(chown(des,sstat.st_uid, sstat.st_gid)<0){prntstatus("error setting ownership");return 1;}
    if(chmod(des,sstat.st_mode)<0){prntstatus("error setting permisions");return 1;}
    
    close(r);
    close(w);
    
    return 0;
}

//-------------copy dir----------------

int cpydir(char *pth,char *des){


    if(mkdir(des,S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH)<0){
        prntstatus("error creating dir");
        return 1;
    }
    DIR *d;
    struct dirent *dir;
    d=opendir(pth);
    if(!d){
        prntstatus("no such diretory found");
        return 1;
    }
    while ((dir = readdir(d)) != NULL){  
        
        if((string(dir->d_name) == "..") || (string(dir->d_name) == "."))
            continue; 
        
        else{   

            string fpath=string(pth) + "/" +string(dir->d_name);
            char* npath = new char[fpath.length() + 1];
            strcpy(npath, fpath.c_str());
            
            string fdespath=string(des) + "/" +string(dir->d_name);
            char* ndespath = new char[fdespath.length() + 1];
            strcpy(ndespath, fdespath.c_str());
            
            struct stat tempstat;
            if (stat(npath,&tempstat) == -1) {
                prntstatus("cannot get stat");
                return 1;
            }
            else{
                if((S_ISDIR(tempstat.st_mode)))
                    cpydir(npath,ndespath);
                else
                    cpyfile(npath,ndespath);
            }
                    
        }
    }
}


// delete dir*******************************


int deldir(char *pth){

    if((string)pth=="/"||(string)pth=="."||(string)pth==".."){
        prntstatus("cannot delete::"+(string)pth);
        return 1;
    }
    DIR *d;
    struct dirent *dir;
    if(!(d=opendir(pth))){
        prntstatus("Failed to open::"+(string)pth);
        return 1;
    }
    while((dir=readdir(d))!=NULL){

        string str=(string)pth+"/"+dir->d_name;
        char *npth=new char[str.length()];
        strcpy(npth,str.c_str());

        struct stat tempstat;
        stat(npth,&tempstat);

        if(S_ISDIR(tempstat.st_mode)){
            if(deldir(npth))return 1;
        }
        else {
            if(delfile(npth))return 1;
        }
    }
    closedir(d);
    if(rmdir(pth)<0){
        prntstatus("Failed to delete::"+(string)pth);
        return 1;
    }
    return 0;

}

//***************delete a file************


int delfile(char *pth){

    if(unlink(pth)<0){
        prntstatus("Failed to delete::"+(string)pth);
        return 1;
    }
    return 0;
}


//--------------------rename file----------------


int renamFilDir(char* ol, char* nw){

    if(rename(ol,nw)<0){
        prntstatus("Failed to rename");
        return 1;
    }
    return 0;
}



//-------------create file********************


int createfle(char* des){

    if(open(des,O_RDONLY|O_CREAT,S_IRWXU|S_IRGRP|S_IWGRP|S_IROTH)<0){
        prntstatus("Failed to create file::"+(string)des);
        return 1;
    }
    return 0;
}


//*****************************create dir*******************


int createdir(char* des){

    if(mkdir(des,S_IRWXU|S_IRWXG|S_IROTH|S_IXOTH)<0){
        prntstatus("Failed to create dir::"+(string)des);
        return 1;
    }
    return 0;
}


//*********************searching ********************


bool searchpth(string srch,char* pth){

    DIR *d=opendir(pth);
    if(!d){
        return 0;
    }
    struct dirent *dir;
    while((dir=readdir(d))!=NULL){
       
        if((string)dir->d_name==srch){
            closedir(d);
            return 1;
        }
        string temp=(string)pth+"/"+(string)dir->d_name;
        char* ch=new char[temp.length()+1];
        strcpy(ch,temp.c_str());
        struct stat st;
        stat(ch,&st);
        if(S_ISDIR(st.st_mode)){
            if((string)dir->d_name=="." || (string)dir->d_name=="..")continue;
            if(searchpth(srch,ch)){
                closedir(d);
                return 1;
            }
        }
    }
    closedir(d);
    return 0;
}