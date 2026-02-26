//1.DDA Line – dda.c

#include <stdio.h>
#include <math.h>

#define W 300
#define H 300
static int img[H][W][3] = {0};

void plot(int x, int y, int r, int g, int b) {
    if(x>=0 && x<W && y>=0 && y<H){
        img[y][x][0] = r;
        img[y][x][1] = g;
        img[y][x][2] = b;
    }
}

void saveImage(char *fname) {
    FILE *f = fopen(fname, "w");
    fprintf(f,"P3\n%d %d\n255\n", W, H);
    for(int y=0;y<H;y++){
        for(int x=0;x<W;x++)
            fprintf(f,"%d %d %d ", img[y][x][0], img[y][x][1], img[y][x][2]);
        fprintf(f,"\n");
    }
    fclose(f);
}

int main() {
    float x1, y1, x2, y2;
    printf("Enter x1 y1 x2 y2 : ");
    scanf("%f %f %f %f", &x1, &y1, &x2, &y2);

    float dx = x2 - x1;
    float dy = y2 - y1;
    float steps = fabs(dx) > fabs(dy) ? fabs(dx) : fabs(dy);

    float xi = dx / steps;
    float yi = dy / steps;

    float x = x1, y = y1;

    for(int i=0;i<=steps;i++){
        plot((int)(x+0.5), (int)(y+0.5), 255, 0, 0);
        x += xi;
        y += yi;
    }
       saveImage("dda.ppm");
    return 0;
}