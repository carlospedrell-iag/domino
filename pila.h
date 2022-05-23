#ifndef _pila_H
#define _pila_H

#include <stdio.h>
#include "tipus.h"


Pila PILA_crea();
void PILA_push(Pila *p, Fitxa fitxa);
Fitxa PILA_top(Pila p);
void PILA_pop(Pila *p);
int PILA_buida(Pila p);
int PILA_plena(Pila p);
void PILA_destrueix(Pila *p);

#endif
