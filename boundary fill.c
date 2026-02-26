#include <stdio.h>
#define W 300
#define H 300
static int img[H][W][3] = {0};

void plot(int x, int y, int r, int g, int b){
    if(x>=0 && x<W && y>=0 && y<H){
        img[y][x][0] = r;
        img[y][x][1] = g;
        img[y][x][2] = b;
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

void boundaryFill(int x,int y,int fr,int fg,int fb,int br,int bg,int bb){
    int *p = img[y][x];
    if(p[0]==br && p[1]==bg && p[2]==bb) return;
    if(p[0]==fr && p[1]==fg && p[2]==fb) return;

    plot(x,y,fr,fg,fb);

    boundaryFill(x+1,y,fr,fg,fb,br,bg,bb);
    boundaryFill(x-1,y,fr,fg,fb,br,bg,bb);
    boundaryFill(x,y+1,fr,fg,fb,br,bg,bb);
    boundaryFill(x,y-1,fr,fg,fb,br,bg,bb);
}

int main(){
    for(int i=50;i<=250;i++){
        plot(i,50,255,0,0);
        plot(i,250,255,0,0);
        plot(50,i,255,0,0);
        plot(250,i,255,0,0);
    }

    boundaryFill(100,100,0,255,0,255,0,0);
    saveImage("boundary.ppm");
    return 0;
}