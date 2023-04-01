#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct {
  char codigo[6];
  char nome[50];
  char professor[100];
  char creditos[5];
  struct disciplina* prox;
} disciplina;

int main(){
    disciplina* d;
    printf("%s, %s", d->codigo, (d->prox));
}