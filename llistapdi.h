#ifndef _llistaPDI_H
#define _llistaPDI_H

#include <stdio.h>
#include "tipus.h"

LlistaPDI LLISTAPDI_crea();
void LLISTAPDI_insereix(LlistaPDI *l, Fitxa e);
Fitxa LLISTAPDI_consulta(LlistaPDI l);
void LLISTAPDI_esborra(LlistaPDI *l);
void LLISTAPDI_avanca(LlistaPDI *l);
void LLISTAPDI_vesInici(LlistaPDI *l);
int LLISTAPDI_fi(LlistaPDI l);
int LLISTAPDI_buida(LlistaPDI l);
void LLISTAPDI_destrueix(LlistaPDI *l);

#endif
