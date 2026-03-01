#include <stdio.h>
#include <stdlib.h>
#define W 300
#define H 300
int img[H][W][3];

void plot(int x,int y){
    if(x>=0 && x<W && y>=0 && y<H)
        img[y][x][2] = 255; // blue color
}

void circle(int xc,int yc,int r){
    int x=0,y=r,d=3-2*r;
    while(x<=y){
        plot(xc+x,yc+y); plot(xc-x,yc+y);
        plot(xc+x,yc-y); plot(xc-x,yc-y);
        plot(xc+y,yc+x); plot(xc-y,yc+x);
        plot(xc+y,yc-x); plot(xc-y,yc-x);
        d<0 ? (d+=4*x+6) : (d+=4*(x-y)+10, y--);
        x++;
    }
}

int main(){
    int xc=100,yc=100,r=40,tx,ty;
    printf("Enter tx ty: ");
    scanf("%d %d",&tx,&ty);

    circle(xc,yc,r); // original
    circle(xc+tx,yc+ty,r); // translated

    FILE *f=fopen("circle_translate.ppm","w");
    fprintf(f,"P3\n%d %d\n255\n",W,H);
    for(int y=0;y<H;y++){
        for(int x=0;x<W;x++)
            fprintf(f,"%d %d %d ",img[y][x][0],img[y][x][1],img[y][x][2]);
        fprintf(f,"\n");
    }
    fclose(f);
    return 0;
}