#include <stdio.h>

#define W 750
#define H 750

int main() {
    static int img[H][W][3] = {0};
    int xc, yc, r;

    printf("Enter center (xc yc) and radius r: ");
    scanf("%d %d %d", &xc, &yc, &r);

    int x = 0;
    int y = r;
    int d = 1 - r;

    while (x <= y) {
        // 8-way symmetry
        int pts[8][2] = {
            {xc + x, yc + y},
            {xc - x, yc + y},
            {xc + x, yc - y},
            {xc - x, yc - y},
            {xc + y, yc + x},
            {xc - y, yc + x},
            {xc + y, yc - x},
            {xc - y, yc - x}
        };

        for (int i = 0; i < 8; i++) {
            int px = pts[i][0];
            int py = pts[i][1];

            if (px >= 0 && px < W && py >= 0 && py < H) {
                img[py][px][0] = 255; // Red
                img[py][px][1] = 0; // Green
                img[py][px][2] = 0; // Blue
            }
        }

        if (d < 0) {
            d += (2 * x + 3);
        } else {
            d += (2 * (x - y) + 5);
            y--;
        }
        x++;
    }

    FILE *f = fopen("circle.ppm", "w");
    if (!f) {
        printf("Error creating file\n");
        return 1;
    }

    fprintf(f, "P3\n%d %d\n255\n", W, H);

    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
            fprintf(f, "%d %d %d ",
                img[i][j][0],
                img[i][j][1],
                img[i][j][2]);
        }
        fprintf(f, "\n");
    }

    fclose(f);

    printf("Circle saved to circle.ppm\n");
    return 0;
}