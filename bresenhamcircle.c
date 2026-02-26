#include <stdio.h>
#define W 500
#define H 500
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
    fprintf(f,"P3\n%d %d\n255\n",W,H);
    for(int y=0;y<H;y++){
        for(int x=0;x<W;x++)
            fprintf(f,"%d %d %d ",img[y][x][0],img[y][x][1],img[y][x][2]);
        fprintf(f,"\n");
    }
    fclose(f);
}

int main(){
    int xc,yc,r;
    printf("Enter xc yc r : ");
    scanf("%d%d%d",&xc,&yc,&r);

    int x=0,y=r;
    int d = 3 - 2*r;

    while(x <= y){
        plot(xc+x,yc+y,255,255,255);
        plot(xc-x,yc+y,255,255,255);
        plot(xc+x,yc-y,255,255,255);
        plot(xc-x,yc-y,255,255,255);
        plot(xc+y,yc+x,255,255,255);
        plot(xc-y,yc+x,255,255,255);
        plot(xc+y,yc-x,255,255,255);
        plot(xc-y,yc-x,255,255,255);

        if(d < 0)
            d += 4*x + 6;
        else{
            d += 4*(x - y) + 10;
            y--;
        }
        x++;
    }

    saveImage("bres_circle.ppm");
    return 0;
}
