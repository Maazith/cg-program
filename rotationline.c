#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define W 300
#define H 300
int img[H][W][3];

void plot(int x,int y,int color){
    if(x>=0 && x<W && y>=0 && y<H)
        img[y][x][color] = 255;
}

void line(int x1,int y1,int x2,int y2,int color){
    float dx=x2-x1, dy=y2-y1;
    float steps = fabs(dx)>fabs(dy)?fabs(dx):fabs(dy);
    float xinc=dx/steps, yinc=dy/steps;
    float x=x1, y=y1;

    for(int i=0;i<=steps;i++){
        plot((int)x,(int)y,color);
        x+=xinc;
        y+=yinc;
    }
}

int main(){
    int x1=50,y1=50,x2=150,y2=50;
    float angle;

    printf("Enter rotation angle in degrees: ");
    scanf("%f",&angle);

    float rad = angle * 3.14159 / 180;

    // Original line (Blue)
    line(x1,y1,x2,y2,2);

    // Rotate about origin
    int rx1 = x1*cos(rad) - y1*sin(rad);
    int ry1 = x1*sin(rad) + y1*cos(rad);
    int rx2 = x2*cos(rad) - y2*sin(rad);
    int ry2 = x2*sin(rad) + y2*cos(rad);

    // Rotated line (Red)
    line(rx1,ry1,rx2,ry2,0);

    FILE *f=fopen("line_rotation.ppm","w");
    fprintf(f,"P3\n%d %d\n255\n",W,H);

    for(int y=0;y<H;y++){
        for(int x=0;x<W;x++)
            fprintf(f,"%d %d %d ",img[y][x][0],img[y][x][1],img[y][x][2]);
        fprintf(f,"\n");
    }

    fclose(f);
    return 0;
}