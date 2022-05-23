#include "llistapdi.h"
#include "tipus.h"

LlistaPDI LLISTAPDI_crea(){
  LlistaPDI l;
  l.cap = (NodeLlista *)malloc(sizeof(NodeLlista));
  if(l.cap == NULL){
    printf("Error_crea");
  }else{
    l.ant = l.cap;
    l.cap->seg = NULL;
  }

  return l;
}

void LLISTAPDI_insereix(LlistaPDI *l, Fitxa e){
  NodeLlista *aux;
  aux = (NodeLlista *)malloc(sizeof(NodeLlista));
  if( aux == NULL) {
    printf("Error_insereix");
  }else{
    aux->f = e;
    aux->seg = l->ant->seg;
    l->ant->seg = aux;
    l->ant = aux;
  }
}

Fitxa LLISTAPDI_consulta(LlistaPDI l){
  Fitxa e;

  e.valors[0] = -1;
  e.valors[1] = -1;

  if( l.ant->seg != NULL){
    e = l.ant->seg->f;
  }
  return e;
}

void LLISTAPDI_esborra(LlistaPDI *l){
  NodeLlista *aux;
  if(l->ant->seg == NULL) {
    printf("Error_esborra");
  }else{
    aux = l->ant->seg;
    l->ant->seg = aux->seg;
    free(aux);
  }
}

void LLISTAPDI_avanca(LlistaPDI *l){
  if(l->ant->seg == NULL){
    printf("Error_avanca\n");
  }else{
    l->ant = l->ant->seg;
  }
}

int LLISTAPDI_fi(LlistaPDI l){
  return l.ant->seg == NULL;
}

void LLISTAPDI_vesInici(LlistaPDI *l){
  l->ant = l->cap;
}

int LLISTAPDI_buida(LlistaPDI l){
  return l.cap->seg == NULL;
}

void LLISTAPDI_destrueix(LlistaPDI *l){
  NodeLlista *aux;
  while(l->cap != NULL){
    aux = l->cap;
    l->cap = l->cap->seg;
    free(aux);
  }
  l->ant = NULL;
}
