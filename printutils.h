// 
//printsutils contains all the methods required for formatting the terminal
//

//-------------print the content of vector

void prntVec(){
    
    x=2;y=1;int i;
    for(i=top_cu;x<=pos_bottom && i<vec.size();i++){
        goto(x,1);
        printf("\033[2K");
        cout<<vec[i].perm<<" ";
        cout<<vec[i].usrown<<" ";
        cout<<vec[i].grpown<<"  ";
        cout<<vec[i].sze<<"K  ";
        cout<<vec[i].m<<" ";
        cout<<vec[i].d<<" ";
        cout<<vec[i].hr<<":";
        cout<<vec[i].min<<"  ";
        cout<<vec[i].nme;
        x++;
    }
    temp_x=x-1;
    bottom_cu=i-1;
    if(x<=pos_bottom){
        while(x<=pos_bottom){
            goto(x++,y);
            printf("\033[2K");
        }
    }
}

//------------------back the color to normal 

void normalText(){
    

    cout<<vec[top_cu+x-2].perm<<" ";
    cout<<vec[top_cu+x-2].usrown<<" ";
    cout<<vec[top_cu+x-2].grpown<<"  ";
    cout<<vec[top_cu+x-2].sze<<"K  ";
    cout<<vec[top_cu+x-2].m<<" ";
    cout<<vec[top_cu+x-2].d<<" ";
    cout<<vec[top_cu+x-2].hr<<":";
    cout<<vec[top_cu+x-2].min<<"  ";
    cout<<vec[top_cu+x-2].nme;

}

//------------------hightlighting the line which cursor points

void coloredText(){

    goto(x,1);
    printf("\033[2K");
    printf("\033[0;44m");
    cout<<vec[top_cu+x-2].perm<<" ";
    cout<<vec[top_cu+x-2].usrown<<" ";
    cout<<vec[top_cu+x-2].grpown<<"  ";
    cout<<vec[top_cu+x-2].sze<<"K  ";
    cout<<vec[top_cu+x-2].m<<" ";
    cout<<vec[top_cu+x-2].d<<" ";
    cout<<vec[top_cu+x-2].hr<<":";
    cout<<vec[top_cu+x-2].min<<"  ";
    cout<<vec[top_cu+x-2].nme;
    printf("\033[49m");
}

//---------clears the screen

void clrscreen(){
    x=2,y=1;
    goto(x,y);
    while(x<=pos_bottom){
        goto(x,y);
        printf("\033[2K");
        x++;
    }
    x=4,y=1;
    goto(x,y);
}

//------------prints the status of command mode

void prntstatus(string sts){

    goto(2,1);
    printf("\033[2K");
    goto(3,1);
    printf("\033[2K");
    goto(2,1);
    cout<<sts;
    goto(4,4);
}