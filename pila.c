#include "pila.h"

Pila PILA_crea(){
	Pila p;
	p.q=0;
	return p;
}

void PILA_push(Pila *p, Fitxa e){
	if(p->q>28){
		printf("Pila plena!\n");
	}
	else{
		p->fitxa[p->q]=e;
		(p->q)++;
	}
}

void PILA_pop(Pila *p){
	if(p->q==0){
		printf("Pila buida\n");
	}
	else{
		(p->q)--;
	}
}

Fitxa PILA_top(Pila p){
	Fitxa aux;
	aux.valors[0] = -1;
	aux.valors[1] = -1;

	if(p.q>0){
		aux = p.fitxa[p.q-1];
	}
	return aux;
}

int PILA_buida(Pila p){
	return p.q==0;
}
int PILA_plena(Pila p){
	return p.q==MAX;
}

void PILA_destrueix(Pila *p){
	p->q=0;
}
