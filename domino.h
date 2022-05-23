#ifndef _domino_H
#define _domino_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include "tipus.h"
#include "pila.h"
#include "llistapdi.h"

	void initzialitzarFitxes(Partida *p);
	void barrejar(Fitxa *array, int n);
	Partida repartirFitxes(Partida _p);
	Partida game(Partida _p,int ij,int *counter);
	int coincideix(int a,int b,LlistaPDI l,int mode);

#endif
