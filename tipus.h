//estructura de la fitxa [a|b]
#ifndef _TIPUS_H_
#define _TIPUS_H_
#define MAX 28
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>

	typedef struct{
		int valors[2]; //[4|3]
	}Fitxa;

	typedef struct {
		Fitxa fitxa[MAX];
		int q;
	}Pila;

	typedef struct n{
		Fitxa f;
		struct n *seg;
	}NodeLlista;

	typedef struct{
		NodeLlista *cap;
		NodeLlista *ant;
	}LlistaPDI;

	typedef struct{
		char *nom_jugador;
		LlistaPDI stock;
		int partides_guanyades;
		int partides_perdudes;
		int guanyador;
	}Jugador;

	typedef struct{
		char nom[20];
		int pg;
		int pp;
	}Ranking;

//
// 	tipus final
	typedef struct{
		int num_jugadors_ranking;
		Jugador *jugador;
		Jugador *jr;
		int num_jugadors;
		int num_jr;
		Pila stack;
		LlistaPDI taulell;
	}Partida;

	#endif
