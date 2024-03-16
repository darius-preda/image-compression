/*Preda Ionut Darius Teodor 313CB*/
# include "define.h"

void Task1(char *file_in, char *file_out, int factor_value) {
    char buff[4];
    unsigned int n_pixels;
    unsigned char caracter;
    int var, i, j;

    FILE *in = fopen(file_in, "rb");
    if (!in) {
        printf("File could not be read!\n");
        exit(1);
    }
    FILE *out = fopen(file_out, "w");
    if (!out) {
        printf("File could not be written!\n");
        exit(1);
    }

    fscanf(in, "%s\n%u %u\n%s", buff, &n_pixels, &n_pixels, buff); //conteaza n_pixels
	fseek(in, 1, SEEK_CUR);

    TGrid grid = calloc(sizeof(TPixl), n_pixels);
    if (!grid) {
        printf("Matrix could not be allocated!\n");
        exit(1);
    }
    for (i = 0; i < n_pixels; i++) {
        grid[i] = calloc(sizeof(TPixel), n_pixels);
        if (!grid[i]) {
            printf("Matrix could not be allocated!\n");
            exit(1);
        }
    }

    for (i = 0; i < n_pixels; i++) {
        for(j = 0; j < n_pixels; j++) {
            fread(&grid[i][j].red, sizeof(unsigned char), 1, in);
            fread(&grid[i][j].green, sizeof(unsigned char), 1, in);
            fread(&grid[i][j].blue, sizeof(unsigned char), 1, in);
        }
	}
	
	TArb a = (TArb)calloc(sizeof(TNod), 1);
	i = 0; j = 0;
	ConstructQTree(a, grid, i, j, n_pixels, factor_value);
	i = NrNiv(a);
	fprintf(out, "%d\n", i); // prima linie din quadtree.out
	i = NrFrunze(a);
	fprintf(out, "%d\n", i); // a doua linie din quadtree.out
	j = 0;
	i = PrimaFrunza(a, j, n_pixels);
	unsigned int auxiliar = n_pixels;
	for(j = 0; j < i; j++)
		auxiliar = auxiliar / 2;
	fprintf(out, "%d\n", auxiliar); // a treia linie din quadtree.out

	freeArb(a);
	freeGrid(grid, n_pixels);
	fclose(in);
	fclose(out);
}

void Task2(char *file_in, char *file_out, int factor_value) {
    char buff[4];
    unsigned int n_pixels;
    unsigned char caracter;
    int var, i, j, curr_niv, niv;

    FILE *in = fopen(file_in, "rb");
    if (!in) {
        printf("File could not be read!\n");
        exit(1);
    }
    FILE *out = fopen(file_out, "w");
    if (!out) {
        printf("File could not be written!\n");
        exit(1);
    }

    fscanf(in, "%s\n%u %u\n%s", buff, &n_pixels, &n_pixels, buff); //conteaza n_pixels
	fseek(in, 1, SEEK_CUR);

    TGrid grid = calloc(sizeof(TPixl), n_pixels);
    if (!grid) {
        printf("Matrix could not be allocated!\n");
        exit(1);
    }
    for (i = 0; i < n_pixels; i++) {
        grid[i] = calloc(sizeof(TPixel), n_pixels);
        if (!grid[i]) {
            printf("Matrix could not be allocated!\n");
            exit(1);
        }
    }

    for (i = 0; i < n_pixels; i++) {
        for(j = 0; j < n_pixels; j++) {
            fread(&grid[i][j].red, sizeof(unsigned char), 1, in);
            fread(&grid[i][j].green, sizeof(unsigned char), 1, in);
            fread(&grid[i][j].blue, sizeof(unsigned char), 1, in);
        }
	}
	
	TArb a = (TArb)calloc(sizeof(TNod), 1);
	i = 0; j = 0;
	ConstructQTree(a, grid, i, j, n_pixels, factor_value);
	
    fwrite(&n_pixels, 1, sizeof(unsigned int), out);
    niv = NrNiv(a);
    for(i = 0; i < niv; i++) {
        curr_niv = 0;
        printeaza(out, a, curr_niv, i);
    }

	freeArb(a);
	freeGrid(grid, n_pixels);
	fclose(in);
	fclose(out);
}

void Task3(char *file_in, char *file_out) {
    unsigned int n_pixels, aux;
    unsigned char type, red, green, blue, nr_tati = 0;
    int x, y;

    FILE *in = fopen(file_in, "rb");
    if (!in) {
        printf("File could not be read!\n");
        exit(1);
    }
    FILE *out = fopen(file_out, "wb");
    if (!out) {
        printf("File could not be written!\n");
        exit(1);
    }

    fread(&n_pixels, sizeof(unsigned int), 1, in); //citim nr de pixeli

    TArb a = (TArb)calloc(sizeof(TNod), 1); // initialzare arbore

    TGrid grid = calloc(sizeof(TPixl), n_pixels);
    if (!grid) {
        printf("Matrix could not be allocated!\n");
        exit(1);
    }
    for (x = 0; x < n_pixels; x++) {
        grid[x] = calloc(sizeof(TPixel), n_pixels);
        if (!grid[x]) {
            printf("Matrix could not be allocated!\n");
            exit(1);
        }
    }

    ReconstructTree(a, in);
    x = 0;
    y = 0;
    void ConstructMatrix(TArb a, int x, int y, unsigned int size, TGrid grid);
    fprintf(out, "%s\n%u %u\n%u\n", "P6", n_pixels, n_pixels, 255);
        for (x = 0; x < n_pixels; x++) {
            for (y = 0; y < n_pixels; y++) {
                fwrite(&grid[x][y].red, sizeof(unsigned char), 1, out);
                fwrite(&grid[x][y].green, sizeof(unsigned char), 1, out);
                fwrite(&grid[x][y].blue, sizeof(unsigned char), 1, out);
            }
        }

    /*TCoada *coada = (TCoada*)calloc(sizeof(TCoada), 1);
	coada->inc = NULL;
    coada->sf = NULL;
	
	while (!feof(in)) { //aloca nodurile in coada
        if (fread(&type, sizeof(unsigned char), 1, in) == 0) {
            break;
        }
        if (type == 1) {
			TArb node = (TArb)calloc(sizeof(TNod), 1);
            fread(&red, sizeof(unsigned char), 1, in);
            fread(&green, sizeof(unsigned char), 1, in);
            fread(&blue, sizeof(unsigned char), 1, in);
            node->type = 1;
            node->red = red;
            node->green = green;
            node->blue = blue;
            InsCoada(coada, node);
        } else if (type == 0) {
			TArb node = (TArb)calloc(sizeof(TNod), 1);
            node->type = 0;
            node->red = 0;
            node->green = 0;
            node->blue = 0;
			InsCoada(coada, node);
            nr_tati++;
        }
    }
    x = 0;
    y = 0;
    a = coada->inc->arb;
    ExtrCoada(coada);
    nr_tati--;
    if(a->type == 1) {
        ConstructMatrix(a, x, y, n_pixels, grid);

        fprintf(out, "%s\n%u %u\n%u\n", "P6", n_pixels, n_pixels, 255);
        for (x = 0; x < n_pixels; x++) {
            for (y = 0; y < n_pixels; y++) {
                fwrite(&grid[x][y].red, sizeof(unsigned char), 1, out);
                fwrite(&grid[x][y].green, sizeof(unsigned char), 1, out);
                fwrite(&grid[x][y].blue, sizeof(unsigned char), 1, out);
            }
        }
    } else { 
        ReconstructTree(&a, coada, &nr_tati);
        afiseaza(a);
        ConstructMatrix(a, x, y, n_pixels, grid);

        fprintf(out, "%s\n%u %u\n%u\n", "P6", n_pixels, n_pixels, 255);
        for (x = 0; x < n_pixels; x++) {
            for (y = 0; y < n_pixels; y++) {
                fwrite(&grid[x][y].red, sizeof(unsigned char), 1, out);
                fwrite(&grid[x][y].green, sizeof(unsigned char), 1, out);
                fwrite(&grid[x][y].blue, sizeof(unsigned char), 1, out);
            }
        }
    }*/
}
