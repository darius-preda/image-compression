/*Preda Ionut Darius Teodor 313CB*/
# include "define.h"

unsigned char ColorScore(TGrid grid, int x, int y, unsigned int size, char c) { //calculeaza scorul de culoare red, green sau blue(in functie de caracterul primit)
	unsigned long long sum = 0;
	unsigned char result = 0;
	int i, j;
	if (c == 'r') {
		for(i = x; i < x + size; i++)
			for(j = y; j < y + size; j++)
				sum += grid[i][j].red;
	} else if (c == 'g') {
		for(i = x; i < x + size; i++)
			for(j = y; j < y + size; j++)
				sum += grid[i][j].green;
	} else if (c == 'b') {
		for(i = x; i < x + size; i++)
			for(j = y; j < y + size; j++)
				sum += grid[i][j].blue;
	}
	result = sum / (size * size);
	return result;
}

int MeanScore(TGrid grid, int x, int y, unsigned int size, unsigned char red, unsigned char green, unsigned char blue) {
	unsigned long long sum = 0;
	int i, j;
	for(i = x; i < x + size; i++)
		for(j = y; j < y + size; j++) {
			sum += (red - grid[i][j].red) * (red - grid[i][j].red);
			sum += (green - grid[i][j].green) * (green - grid[i][j].green);
			sum += (blue - grid[i][j].blue) * (blue - grid[i][j].blue);
		}
	return sum /= (3 * size * size);
}

int FinalScore(TGrid grid, int x, int y, unsigned int size, int factor_value) {
	unsigned char red = ColorScore(grid, x, y, size, 'r');
	unsigned char green = ColorScore(grid, x, y, size, 'g');
	unsigned char blue = ColorScore(grid, x, y, size, 'b');

	int mean = MeanScore(grid, x, y, size, red, green, blue);

	if (mean <= factor_value)
		return 1;
	else return 0;
}

void ConstructQTree(TArb a, TGrid grid, int x, int y, unsigned int size, int factor_value) {
	if (FinalScore(grid, x, y, size, factor_value) == 1 && size > 0) {
		unsigned char red = ColorScore(grid, x, y, size, 'r');
		unsigned char green = ColorScore(grid, x, y, size, 'g');
		unsigned char blue = ColorScore(grid, x, y, size, 'b');
		a->type = 1;
		a->red = red;
		a->green = green;
		a->blue = blue;
	} else {
		a->q1 = (TArb)calloc(sizeof(TNod), 1);
		a->q2 = (TArb)calloc(sizeof(TNod), 1);
		a->q3 = (TArb)calloc(sizeof(TNod), 1);
		a->q4 = (TArb)calloc(sizeof(TNod), 1);
		size = size / 2;
		ConstructQTree(a->q1, grid, x, y, size, factor_value);
		ConstructQTree(a->q2, grid, x, y + size, size, factor_value);
		ConstructQTree(a->q3, grid, x + size, y + size, size, factor_value);
		ConstructQTree(a->q4, grid, x + size, y, size, factor_value);
	}	
}

int NrNiv(TArb a) {
	if (!a)
        return 0;
    int n1 = 0, n2 = 0, n3 = 0, n4 = 0;
	n1 = NrNiv(a->q1);
    n2 = NrNiv(a->q2);
    n3 = NrNiv(a->q3);
    n4 = NrNiv(a->q2);

    return 1 + max(max(n1, n2), max(n3, n4));
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

int min(int a, int b) {
    return (a < b) ? a : b;
}

int NrFrunze(TArb a) {
	int c = 0;
	if (a == NULL) {
		return 0;
	}
	c += NrFrunze(a->q1);
	c += NrFrunze(a->q2);
	c += NrFrunze(a->q3);
	c += NrFrunze(a->q4);

	if (a->type == 1)
		c++;

	return c;
}

int PrimaFrunza(TArb a, int niv, unsigned int size) {
	if (a == NULL)
		return -1;
	int c1 = 0, c2 = 0, c3 = 0, c4 = 0;
	if (a->type == 1)
		return niv;
	niv++;
	c1 = PrimaFrunza(a->q1, niv, size);
	c2 = PrimaFrunza(a->q2, niv, size);
	c3 = PrimaFrunza(a->q3, niv, size);
	c4 = PrimaFrunza(a->q4, niv, size);

	return min(min(c1, c2), min(c3, c4));
}

void freeArb(TArb a) {
	if (a == NULL)
		return;
	freeArb(a->q1);
	freeArb(a->q2);
	freeArb(a->q3);
	freeArb(a->q4);
	free(a);
}

void freeGrid(TGrid grid, unsigned int size) {
	int i;
	for (i = 0; i < size; i++)
		free(grid[i]);
	free(grid);
}

void printeaza(FILE *out, TArb a, int curr_niv, int niv) {
	if(a == NULL)
		return;
	if (curr_niv == niv) {
    	if (a->type == 0) {
			fwrite(&a->type, 1, sizeof(char), out);
		} else {
			fwrite(&a->type, 1, sizeof(char), out);
			fwrite(&a->red, 1, sizeof(char), out);
			fwrite(&a->green, 1, sizeof(char), out);
			fwrite(&a->blue, 1, sizeof(char), out);
		}
	}
	printeaza(out, a->q1, curr_niv + 1, niv);
	printeaza(out, a->q2, curr_niv + 1, niv);
	printeaza(out, a->q3, curr_niv + 1, niv);
	printeaza(out, a->q4, curr_niv + 1, niv);
}

void afiseaza(TArb a) {
    if (a == NULL)
        return;
    printf("%u (", a->type);
    afiseaza(a->q1);
    afiseaza(a->q2);
    afiseaza(a->q3);
    afiseaza(a->q4);
	printf(")");
}

void ConstructMatrix(TArb a, int x, int y, unsigned int size, TGrid grid) {
	int i, j;
	if(a->type == 0) {
		size = size / 2;
		ConstructMatrix(a->q1, x, y, size, grid);
		ConstructMatrix(a->q2, x, y + size, size, grid);
		ConstructMatrix(a->q3, x + size, y + size, size, grid);
		ConstructMatrix(a->q4, x + size, y, size, grid);
	} else if(a->type == 1) {
		for (i = x; i < x + size; i++) {
			for (j = y; j < y + size; j++) {
				grid[i][j].red = a->red;
				grid[i][j].green = a->green;
				grid[i][j].blue = a->blue;
			}
		}
	}
}

void ReconstructTree(TArb a, FILE *in) {
	unsigned char type, red, green, blue, niv = 0;
	
	while (!feof(in)) {
        if (fread(&type, sizeof(unsigned char), 1, in) == 0) {
            break;
        }
        if (type == 1) {
			TArb node = (TArb)malloc(sizeof(TNod));
            fread(&red, sizeof(unsigned char), 1, in);
            fread(&green, sizeof(unsigned char), 1, in);
            fread(&blue, sizeof(unsigned char), 1, in);
            node->type = 1;
            node->red = red;
            node->green = green;
            node->blue = blue;
            InsertNode(a, node, &niv);
        } else if (type == 0) {
            a->q1 = (TArb)malloc(sizeof(TNod));
		    a->q2 = (TArb)malloc(sizeof(TNod));
		    a->q3 = (TArb)malloc(sizeof(TNod));
		    a->q4 = (TArb)malloc(sizeof(TNod));
			TArb node = (TArb)malloc(sizeof(TNod));
            node->type = 0;
			InsertNode(a, node, &niv);
        }
    }
}

void InsertNode(TArb a, TArb node, unsigned char *niv) {
	if ((*niv) == 0) {
		a->type = node->type;
		a->red = node->red;
		a->green = node->green;
		a->blue = node->blue;
		(*niv)++;
		return;
	}
	(*niv)++;
    if (a != NULL && node != NULL) {
        if (a->type == 1) {
            return;
        }
        if (a->q1 == NULL) {
            a->q1 = node;
        } else if (a->q2 == NULL) {
            a->q2 = node;
        } else if (a->q3 == NULL) {
            a->q3 = node;
        } else if (a->q4 == NULL) {
            a->q4 = node;
        } else {
            InsertNode(a->q1, node, niv);
            InsertNode(a->q2, node, niv);
            InsertNode(a->q3, node, niv);
            InsertNode(a->q4, node, niv);
        }
    }
} 

void InsCoada(TCoada *coada, TArb nod) {
	TNodCoada *aux = (TNodCoada*)calloc(sizeof(TNodCoada), 1);
	aux->arb = nod;
	aux->urm = NULL;
	if(coada->inc == NULL && coada->sf == NULL) {
		coada->inc = aux;
		coada->sf = aux;
	} else {
		coada->sf->urm = aux;
		coada->sf = aux;
	}
}

void ExtrCoada(TCoada *coada) {
	if (coada->inc == NULL && coada->sf == NULL) {
		return;
	} else if (coada->inc == coada->sf) {
		coada->inc = NULL;
		coada->sf = NULL;
	} else {
		TNodCoada *aux = coada->inc;
		coada->inc = coada->inc->urm;
		free(aux);
	}

}

/*void ReconstructTree(TArb *a, TCoada *coada, unsigned char *nr_tati) {
    if ((*nr_tati) == 0)
        return;
	if (coada->inc == NULL || coada->sf == NULL)
		return;
	int n1 = 0, n2 = 0, n3 = 0, n4 = 0;
	(*a)->q1 = coada->inc->arb;
	ExtrCoada(coada);
	if ((*a)->q1->type == 0) {
		(*nr_tati)--;
		n1 = 1;
	}
	(*a)->q2 = coada->inc->arb;
	ExtrCoada(coada);
	if ((*a)->q2->type == 0) {
		(*nr_tati)--;
		n2 = 1;
	}
	(*a)->q3 = coada->inc->arb;
	ExtrCoada(coada);
	if ((*a)->q3->type == 0) {
		(*nr_tati)--;
		n3 = 1;
	}
	(*a)->q4 = coada->inc->arb;
	ExtrCoada(coada);
	if ((*a)->q4->type == 0) {
		(*nr_tati)--;
		n4 = 1;
	}

	if (n1 == 1)
    	ReconstructTree(&((*a)->q1), coada, nr_tati);
	else if (n2 == 1)
		ReconstructTree(&((*a)->q2), coada, nr_tati);
	else if (n3 == 1)
		ReconstructTree(&((*a)->q3), coada, nr_tati);
	else if (n4 == 1)
		ReconstructTree(&((*a)->q4), coada, nr_tati);
    }*/