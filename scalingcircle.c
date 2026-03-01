#include <stdio.h>
#include <stdlib.h>
#define W 300
#define H 300
int img[H][W][3];

void plot(int x,int y,int color){
    if(x>=0 && x<W && y>=0 && y<H)
        img[y][x][color] = 255; 
        // color = 2 → blue
        // color = 0 → red
}

void circle(int xc,int yc,int r,int color){
    int x=0,y=r,d=3-2*r;
    while(x<=y){
        plot(xc+x,yc+y,color); plot(xc-x,yc+y,color);
        plot(xc+x,yc-y,color); plot(xc-x,yc-y,color);
        plot(xc+y,yc+x,color); plot(xc-y,yc+x,color);
        plot(xc+y,yc-x,color); plot(xc-y,yc-x,color);
        if(d<0)
            d+=4*x+6;
        else{
            d+=4*(x-y)+10;
            y--;
        }
        x++;
    }
}

int main(){
    int xc=150,yc=150,r=40;
    float sx;

    printf("Enter scaling factor: ");
    scanf("%f",&sx);

    // Original Circle (Blue)
    circle(xc,yc,r,2);

    // Scaled Circle (Red)
    int new_r = r * sx;
    circle(xc,yc,new_r,0);

    FILE *f=fopen("circle_scaling.ppm","w");
    fprintf(f,"P3\n%d %d\n255\n",W,H);

    for(int y=0;y<H;y++){
        for(int x=0;x<W;x++)
            fprintf(f,"%d %d %d ",
                    img[y][x][0],
                    img[y][x][1],
                    img[y][x][2]);
        fprintf(f,"\n");
    }

    fclose(f);
    return 0;
}