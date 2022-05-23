#ifndef _fitxers_H
#define _fitxers_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include "tipus.h"

	void llegeixJugadors(FILE *f,Partida *p,int *error);
	void llegeixRanking(FILE *g, Partida *p);
	void mostraRanking(Partida p);
	void updateRanking(Partida *p);
	void escriuRanking(FILE *g, Partida *p);
	void ordenaRankingAlfa(Partida *p);
	void ordenaRankingWin(Partida *p);

	void escriuTest(FILE *g);


#endif
