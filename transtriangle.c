#include <stdio.h>
#include <math.h>
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

/* DDA Line Drawing */
void drawLine(int x1, int y1, int x2, int y2){
    int dx = x2 - x1;
    int dy = y2 - y1;

    int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);

    float xinc = dx / (float)steps;
    float yinc = dy / (float)steps;

    float x = x1;
    float y = y1;

    for(int i=0; i<=steps; i++){
        plot((int)(x+0.5), (int)(y+0.5), 255,255,255);
        x += xinc;
        y += yinc;
    }
}

void saveImage(char *fname){
    FILE *f = fopen(fname,"w");
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
}
int main(){
    int x1=50,y1=50, x2=150,y2=50, x3=100,y3=150;
    int tx, ty;

    /* Original triangle */
    drawLine(x1,y1, x2,y2);
    drawLine(x2,y2, x3,y3);
    drawLine(x3,y3, x1,y1);

    printf("Enter translation tx ty : ");
    scanf("%d %d",&tx,&ty);

    /* Translated triangle */
    drawLine(x1+tx, y1+ty, x2+tx, y2+ty);
    drawLine(x2+tx, y2+ty, x3+tx, y3+ty);
    drawLine(x3+tx, y3+ty, x1+tx, y1+ty);

    saveImage("tri.ppm");
    return 0;
}
