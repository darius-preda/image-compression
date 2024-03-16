#include "define.h"

void Task1(char *file_in, char *file_out, int factor_value) {
    unsigned int type, red, green, blue;
    unsigned int length;
    unsigned char var;

    TArb a = malloc(sizeof(TNod));
    if (!a) {
        printf("Tree could not be created!\n");
        exit(1);
    }
    TArb node = malloc(sizeof(TNod));
    if (!node) {
        printf("Node could not be created!\n");
        exit(1);
    }
    FILE *in = fopen(file_in, "rb");
    if (!in) {
        printf("File could not be opened!\n");
        exit(1);
    }
    FILE *out = fopen(file_out, "w");
    if (!out) {
        printf("File could not be opened!\n");
        exit(1);
    }

    fread(&length, sizeof(unsigned int), 1, in); //citim nr de pixeli
    fread(&var, sizeof(unsigned char), 1, in); //citim radacina ca sa nu o mai ia in calcul
    while (!feof(in)) { //citim datele pixelilor
        if (fread(&var, sizeof(unsigned char), 1, in) == 0) {
            break;
        }
        type = (unsigned int)var; //convertim valoarea in int
        if (type == 1) {
            fread(&var, sizeof(unsigned char), 1, in);
            red = (unsigned int)var;
            fread(&var, sizeof(unsigned char), 1, in);
            green = (unsigned int)var;
            fread(&var, sizeof(unsigned char), 1, in);
            blue = (unsigned int)var;
            node = ConstrFrunza(red, green, blue);
            InsertNode(a, node);
        } else if (type == 0) {
            node = ConstrNode();
            InsertNode(a, node);
        }
    }
    fprintf(out, "%d\n", NrNiv(a)); /*primul rand din fisier*/

    
}

TArb ConstrFrunza(unsigned int red, unsigned int green, unsigned int blue) {
	TArb aux = (TArb)malloc (sizeof(TNod));
	if (!aux)
        return NULL;
	aux->type = 1;
    aux->red = red;
    aux->green = green;
    aux->blue = blue;
    aux->q1 = NULL;
    aux->q2 = NULL;
    aux->q3 = NULL;
    aux->q4 = NULL;

	return aux;
}

TArb ConstrNode() {
	TArb aux = (TArb)malloc (sizeof(TNod));
	if (!aux)
        return NULL;
	aux->type = 0;
    aux->q1 = NULL;
    aux->q2 = NULL;
    aux->q3 = NULL;
    aux->q4 = NULL;

	return aux;
}

void InsertNode(TArb a, TArb node) {
    if (a != NULL) {
        if (a->q1 != NULL || a->type == 1)
            if (a->q2 != NULL || a->type == 1)
                if (a->q3 != NULL || a->type == 1)
                    if (a->q4 != NULL || a->type == 1)
                        InsertNode(a->q1, node);
                    else a->q4 = node;
                else a->q3 = node;
            else a->q2 = node;
        else a->q1 = node;  
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

int max(int a, int b) { //functie auxiliara
    return (a > b) ? a : b;
}

void printeaza(TArb a) {
    if (a == NULL)
        return;
    printf("%u ", a->type);
    printeaza(a->q1);
    printeaza(a->q2);
    printeaza(a->q3);
    printeaza(a->q4);
}
