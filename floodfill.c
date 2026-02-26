#include <stdio.h>

#define W 300
#define H 300
static int img[H][W][3] = {0};

void plot(int x, int y, int r, int g, int b){
    if(x>=0 && x<W && y>=0 && y<H){
        img[y][x][0]=r;
        img[y][x][1]=g;
        img[y][x][2]=b;
    }
}

void saveImage(char *fname){
    FILE *f = fopen(fname,"w");
    fprintf(f,"P3\n%d %d\n255\n",W,H);
    for(int y=0;y<H;y++){
        for(int x=0;x<W;x++)
            fprintf(f,"%d %d %d ",img[y][x][0],img[y][x][1],img[y][x][2]);
        fprintf(f,"\n");
    }
    fclose(f);
}

void floodFill(int x,int y,int tr,int tg,int tb,int fr,int fg,int fb){
    int *p = img[y][x];
    if(p[0]!=tr || p[1]!=tg || p[2]!=tb) return;

    plot(x,y,fr,fg,fb);

    floodFill(x+1,y,tr,tg,tb,fr,fg,fb);
    floodFill(x-1,y,tr,tg,tb,fr,fg,fb);
    floodFill(x,y+1,tr,tg,tb,fr,fg,fb);
    floodFill(x,y-1,tr,tg,tb,fr,fg,fb);
}

int main(){
    for(int i=80;i<220;i++)
        for(int j=80;j<220;j++)
            plot(i,j,255,255,255);

    floodFill(100,100,255,255,255,0,0,255);
    saveImage("flood.ppm");
    return 0;
}