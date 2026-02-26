#include <stdio.h>
#include <stdlib.h>
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
    FILE *f = fopen(fname, "w");
    fprintf(f, "P3\n%d %d\n255\n", W, H);
    for(int y=0;y<H;y++){
        for(int x=0;x<W;x++)
            fprintf(f,"%d %d %d ", img[y][x][0], img[y][x][1], img[y][x][2]);
        fprintf(f,"\n");
    }
    fclose(f);
}

int main(){
    int x1,y1,x2,y2;
    printf("Enter x1 y1 x2 y2 : ");
    scanf("%d%d%d%d",&x1,&y1,&x2,&y2);

    int dx=abs(x2-x1), sx=x1<x2?1:-1;
    int dy=-abs(y2-y1), sy=y1<y2?1:-1;
    int err = dx + dy, e2;

    while(1){
        plot(x1,y1,255,255,0);
        if(x1==x2 && y1==y2) break;

        e2 = 2*err;
        if(e2 >= dy){ err += dy; x1 += sx; }
        if(e2 <= dx){ err += dx; y1 += sy; }
    }

    saveImage("bres_line.ppm");
    return 0;
}