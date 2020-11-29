//
//retrives the content of the dir and stores it in the info vector
//

#ifndef HEADER
#define HEADER

#include "header.h"

#endif


void getDir(){

    struct stat sb;
    struct dirent *dir;
    DIR *d=opendir(cwd);
    
    if (d==NULL) {
        clrscreen();
        goto(2,1);
        cout<<"no path exists";
        x++;
        return;
    }
    struct tm *t;

    vec.clear();

    while((dir=readdir(d)) != NULL){

        string str=(string)cwd+"/"+dir->d_name;
        char *ch=new char[str.length()+1];
        strcpy(ch,str.c_str());

        if(stat(ch, &sb) == -1){
               perror("lstat");
               exit(EXIT_FAILURE);
        }

        string prm=getPermStr(sb,"");

        struct passwd *pw = getpwuid(sb.st_uid);
        struct group *gr = getgrgid(sb.st_gid);
        string gown="";
        string uown="";
        string tim="";
        if (pw != 0)
            uown=(string)pw->pw_name;
        if (gr != 0)
            gown=(string)gr->gr_name;
    
        t=gmtime(&sb.st_mtime);
        long fsiz=sb.st_size;
        if(fsiz>1024)fsiz=ceil(fsiz/1024);
    
        vec.push_back({dir->d_name,fsiz,prm,gown,uown,getMon(t->tm_mon),t->tm_mday,t->tm_hour,t->tm_min});
    
    }
    top_cu=bottom_cu=0;
    prntVec();
    x=2;y=1;
    coloredText();
    closedir(d);    
}

//----------returns file permissions string



string getPermStr(struct stat sb,string str){

    S_ISDIR(sb.st_mode) ? str+="d" : str+="-";
    sb.st_mode & S_IRUSR ? str+="r" : str+="-";
    sb.st_mode & S_IWUSR ? str+="w" : str+="-";
    sb.st_mode & S_IXUSR ? str+="x" : str+="-";
    sb.st_mode & S_IRGRP ? str+="r" : str+="-";
    sb.st_mode & S_IWGRP ? str+="w" : str+="-";
    sb.st_mode & S_IXGRP ? str+="x" : str+="-";
    sb.st_mode & S_IROTH ? str+="r" : str+="-";
    sb.st_mode & S_IWOTH ? str+="w" : str+="-";
    sb.st_mode & S_IXOTH ? str+="x" : str+="-";
    return str;
}


//get month name


string getMon(int i){
    if(i==0)return "JAN";
    else if(i==1) return "FEB";
    else if(i==2) return "MAR";
    else if(i==3) return "APR"; 
    else if(i==4) return "MAY";
    else if(i==5) return "JUN";
    else if(i==6) return "JUL";
    else if(i==7) return "AUG";
    else if(i==8) return "SEP";
    else if(i==9) return "OCT";
    else if(i==10) return "NOV";
    else return "DEC";
    
}
