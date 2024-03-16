/*Preda Ionut Darius Teodor 313CB*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>

typedef struct pixel {
    unsigned char red, green, blue;
}TPixel, *TPixl, **TGrid;

typedef struct nod {
    unsigned char type;
    unsigned char red, green, blue;
    struct nod *q1, *q2, *q3, *q4;
}TNod, *TArb;

typedef struct nod_coada {
    TArb arb;
    struct nod_coada *urm;
}TNodCoada;

typedef struct coada {
    struct nod_coada *inc, *sf;
}TCoada;

void Task1(char *file_in, char *file_out, int factor_value);
void Task2(char *file_in, char *file_out, int factor_value);
void Task3(char *file_in, char *file_out);
unsigned char ColorScore(TGrid grid, int x, int y, unsigned int size, char c);
int MeanScore(TGrid grid, int x, int y, unsigned int size, unsigned char red, unsigned char blue, unsigned char green);
int FinalScore(TGrid grid, int x, int y, unsigned int size, int factor_value);
void ConstructQTree(TArb a, TGrid grid, int x, int y, unsigned int size, int factor_value);
int PrimaFrunza(TArb a, int niv, unsigned int size);
void freeArb(TArb a);
void freeGrid(TGrid grid, unsigned int size);
int NrNiv(TArb a);
int max(int a, int b);
int NrFrunze(TArb a);
int min(int a, int b);
void printeaza(FILE *out, TArb a, int curr_niv, int niv);
void ConstructMatrix(TArb a, int x, int y, unsigned int size, TGrid grid);
void InsCoada(TCoada *coada, TArb nod);
void ExtrCoada(TCoada *coada);
//void ReconstructTree(TArb *a, TCoada *coada, unsigned char *nr_tati);
void InsertNode(TArb a, TArb node, unsigned char *niv);
void ReconstructTree(TArb a, FILE *in);

void afiseaza(TArb a);