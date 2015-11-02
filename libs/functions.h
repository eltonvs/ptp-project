void img_info(Pixel img[MAX][MAX]) {
    int i, j;
    printf("Dados da Imagem lida:\n");
    printf("Tipo: %s\n", header);
    printf("Tamanho: %ix%i\n", w, h);
    printf("Cor máxima: %i\n", comp);
    /*
    printf("Cores de cada pixel:\n");
    for (i = 0; i < h; i++)
        for (j = 0; j < w; j++)
            printf("%i %i %i\n", img[i][j].r, img[i][j].g, img[i][j].b);
    */
}

void copy_img(Pixel origin[MAX][MAX], Pixel destiny[MAX][MAX]) {
    int i, j;
    for (i = 0; i < w; i++)
        for (j = 0; j < h; j++)
            destiny[i][j] = origin[i][j];
}

void img_high_relief(Pixel img[MAX][MAX]) {
    int i, j;
    Pixel tmp[MAX][MAX];
    copy_img(img, tmp);
    for (i = 1; i < w - 1; i++)
        for (j = 0; j < h; j++)
            tmp[i][j].r = abs(img[i+1][j].r - img[i-1][j].r) + comp/2,
            tmp[i][j].g = abs(img[i+1][j].g - img[i-1][j].g) + comp/2,
            tmp[i][j].b = abs(img[i+1][j].b - img[i-1][j].b) + comp/2;
    copy_img(tmp, img);
}

void img_blurring(Pixel img[MAX][MAX]) {
    int i, j;
    Pixel tmp[MAX][MAX];
    copy_img(img, tmp);
    for (i = 1; i < w - 1; i++)
        for (j = 1; j < h - 1; j++)
            tmp[i][j].r = (img[i-1][j-1].r + img[i-1][j].r + img[i-1][j+1].r +
                            img[i][j-1].r + img[i][j].r + img[i][j+1].r +
                            img[i+1][j-1].r + img[i+1][j].r + img[i+1][j+1].r)/9,
            tmp[i][j].g = (img[i-1][j-1].g + img[i-1][j].g + img[i-1][j+1].g +
                            img[i][j-1].g + img[i][j].g + img[i][j+1].g +
                            img[i+1][j-1].g + img[i+1][j].g + img[i+1][j+1].g)/9,
            tmp[i][j].b = (img[i-1][j-1].b + img[i-1][j].b + img[i-1][j+1].b +
                            img[i][j-1].b + img[i][j].b + img[i][j+1].b +
                            img[i+1][j-1].b + img[i+1][j].b + img[i+1][j+1].b)/9;
    copy_img(tmp, img);
}

void img_sharpening(Pixel img[MAX][MAX]) {
    int i, j;
    Pixel tmp[MAX][MAX];
    copy_img(img, tmp);
    for (i = 1; i < w - 1; i++)
        for (j = 1; j < h - 1; j++)
            tmp[i][j].r = abs(5*img[i][j].r - img[i-1][j].r - img[i][j-1].r - img[i][j+1].r - img[i+1][j].r),
            tmp[i][j].g = abs(5*img[i][j].g - img[i-1][j].g - img[i][j-1].g - img[i][j+1].g - img[i+1][j].g),
            tmp[i][j].b = abs(5*img[i][j].b - img[i-1][j].b - img[i][j-1].b - img[i][j+1].b - img[i+1][j].b);
    copy_img(tmp, img);
}

void img_posterize(Pixel img[MAX][MAX]) {
    int i, j, pb;
    for (i = 0; i < w; i++)
        for (j = 0; j < h; j++)
            img[i][j].r = (img[i][j].r > comp/2) ? comp: 0,
            img[i][j].g = (img[i][j].g > comp/2) ? comp: 0,
            img[i][j].b = (img[i][j].b > comp/2) ? comp: 0;
}

void img_thresholding(Pixel img[MAX][MAX]) {
    int i, j, bin_color;
    for (i = 0; i < w; i++)
        for (j = 0; j < h; j++)
            bin_color = (img[i][j].r + img[i][j].g + img[i][j].b)/3 > comp/2,
            img[i][j].r = bin_color,
            img[i][j].g = bin_color,
            img[i][j].b = bin_color;
    comp = 1;
}

void img_grayscale(Pixel img[MAX][MAX]) {
    int i, j, pb;
    for (i = 0; i < w; i++)
        for (j = 0; j < h; j++)
            pb = (img[i][j].r + img[i][j].g + img[i][j].b)/3,
            img[i][j].r = pb,
            img[i][j].g = pb,
            img[i][j].b = pb;
}

void img_negative(Pixel img[MAX][MAX]) {
    int i, j;
    for (i = 0; i < w; i++)
        for (j = 0; j < h; j++)
            img[i][j].r = comp-img[i][j].r,
            img[i][j].g = comp-img[i][j].g,
            img[i][j].b = comp-img[i][j].b;
}

void img_invert_h(Pixel img[MAX][MAX]) {
    int i, j;
    Pixel tmp[MAX][MAX];
    copy_img(img, tmp);
    for (i = 0; i < h; i++)
        for (j = 0; j < w; j++)
            img[h-i-1][j].r = tmp[i][j].r,
            img[h-i-1][j].g = tmp[i][j].g,
            img[h-i-1][j].b = tmp[i][j].b;
}

void img_invert_v(Pixel img[MAX][MAX]) {
    int i, j;
    Pixel tmp[MAX][MAX];
    copy_img(img, tmp);
    for (i = 0; i < h; i++)
        for (j = 0; j < w; j++)
            img[i][w-j-1].r = tmp[i][j].r,
            img[i][w-j-1].g = tmp[i][j].g,
            img[i][w-j-1].b = tmp[i][j].b;
}

void img_rot_left(Pixel img[MAX][MAX]) {
    int i, j, aux;
    Pixel tmp[MAX][MAX];
    copy_img(img, tmp);
    for (i = 0; i < h; i++)
        for (j = 0; j < w; j++)
            img[w-j-1][i].r = tmp[i][j].r,
            img[w-j-1][i].g = tmp[i][j].g,
            img[w-j-1][i].b = tmp[i][j].b;
    aux = h, h = w, w = aux;
}

void img_rot_right(Pixel img[MAX][MAX]) {
    int i;
    for (i = 0; i < 3; i++)
        img_rot_left(img);
}

void img_rot_180(Pixel img[MAX][MAX]) {
    img_invert_v(img);
    img_invert_h(img);
}

void img_amp(char file[], int zoom, Pixel img[MAX][MAX]) {
    int i, j, k, l;

    strcat(file, "-amp.ppm");

    FILE *img_f;
    img_f = fopen(file, "w");

    fprintf(img_f, "%s\n", header);
    fprintf(img_f, "%i %i\n", w*zoom, h*zoom);
    fprintf(img_f, "%i\n", comp);
    for (i = 0; i < h; i++)
        for (k = 0; k < zoom; k++)
            for (j = 0; j < w; j++)
                for (l = 0; l < zoom; l++)
                    fprintf(img_f, "%i %i %i\n",
                    (img[i][j].r > comp) ? comp : img[i][j].r,
                    (img[i][j].g > comp) ? comp : img[i][j].g,
                    (img[i][j].b > comp) ? comp : img[i][j].b);

    fclose(img_f);

    printf("\nA imagem foi salva como %s\n", file);
}

void img_red(char file[], int zoom, Pixel img[MAX][MAX]) {
    int i, j, k, l, area = zoom*zoom;
    Pixel sum = {0, 0, 0};

    strcat(file, "-red.ppm");

    FILE *img_f;
    img_f = fopen(file, "w");

    fprintf(img_f, "%s\n", header);
    fprintf(img_f, "%i %i\n", w/zoom, h/zoom);
    fprintf(img_f, "%i\n", comp);
    for (i = 0; i <= h-zoom; i += zoom)
        for (j = 0; j <= w-zoom; j += zoom, sum.r = 0, sum.g = 0, sum.b = 0) {
            for (k = 0; k < zoom; k++)
                for (l = 0; l < zoom; l++)
                    sum.r += img[i+k][j+l].r,
                    sum.g += img[i+k][j+l].g,
                    sum.b += img[i+k][j+l].b;
            fprintf(img_f, "%i %i %i\n",
            (sum.r/area > comp) ? comp : sum.r/area,
            (sum.g/area > comp) ? comp : sum.g/area,
            (sum.b/area > comp) ? comp : sum.b/area);
        }

    fclose(img_f);

    printf("\nA imagem foi salva como %s\n", file);
}

void build_img(char file[], Pixel img[MAX][MAX]){
    int i, j;

    strcat(strcat(strcat(file, "-"), op), ".ppm");

    FILE *img_f;
    img_f = fopen(file, "w");

    fprintf(img_f, "%s\n", header);
    fprintf(img_f, "%i %i\n", w, h);
    fprintf(img_f, "%i\n", comp);
    for (i = 0; i < h; i++)
        for (j = 0; j < w; j++)
            fprintf(img_f, "%i %i %i\n",
            (img[i][j].r > comp) ? comp : (img[i][j].r < 0) ? 0 : img[i][j].r,
            (img[i][j].g > comp) ? comp : (img[i][j].g < 0) ? 0 : img[i][j].g,
            (img[i][j].b > comp) ? comp : (img[i][j].b < 0) ? 0 : img[i][j].b);

    fclose(img_f);

    printf("\nA imagem foi salva como %s\n", file);
}
