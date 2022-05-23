
#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <stdlib.h>
#include "tipus.h"
#include "fitxers.h"
#include "domino.h"


int main (int argc, char** argv) {

	int OK=0, opcio=0, metode=0,error=0,end=0,i,indexJ=1,counter=0,jugcount=0,millor=30,el=0;
	FILE *f, *g;
	Partida pt;

	// Comprovem que el num de arguments sigui correcte
	if (argc != 3) {
 	printf("Error, falten parametres per la linia de comandes!\n");

	}else{
		//obrim fitxer
		f = fopen(argv[2],"r");

		if(f == NULL){
			printf("Error al obrir el fitxer jugadors.txt\n\n");
		}else{
			//fem una lectura
			llegeixJugadors(f,&pt,&error);

			if(!error){
				//si no hi ha hagut cap error obrim el fitxer de ranking
				g = fopen(argv[1],"rb");
				//controlem error
				if(g == NULL){
					pt.num_jr = 0;
					pt.jr = (Jugador *) malloc(1 * sizeof(Jugador));
					el=1;
				} else {
					llegeixRanking(g,&pt);
					fclose(g);
				}

				do{
					//llegim el ranking del fitxer i el posem en el ranking del joc
					end = 0;
					initzialitzarFitxes(&pt);
					clrscr();
					//menu
					printf("\nBenvingut al Domino La Salle !\n\n");
					printf("\t1. Nova partida\n");
					printf("\t2. Mostrar ranking\n");
					printf("\t3. Sortir");
					printf("\n");

					do{
						//preguntem la opcio
						OK=0;
						printf("Opcio: ");
						opcio = 0;
						scanf("%d",&opcio);
						fflushnou();
						//controlem error de opcio
						if(opcio<1 || opcio>3){
							printf("Error, opcio incorrecta! \n");
							OK=1;
						}

					} while(OK!=0);

					switch(opcio){

						case 1:
							//en la opcio 1 comença la partida, repartim les 5 fitxes a cada jugador
							pt = repartirFitxes(pt);
							while(!end){
								//la funcio game s'encarrega de les funcions principals de cada jugada
								pt = game(pt,indexJ,&counter);
								//despres de la jugada mirem si el jugador ja no te fitxes, es a dir, ha guanyat
								if (LLISTAPDI_buida(pt.jugador[indexJ].stock)){
									//si indexJ jugador no te fitxes, posem a 1 el valor guanyador
									pt.jugador[indexJ].guanyador = 1;
									printf("\n\t%s ha guanyat !\n\n",pt.jugador[indexJ].nom_jugador);
									printf("--- Prem Enter per continuar ---");
									while ( getchar() != '\n');
									//donem missatge de victoria i finalitzem la partida igualant end a 1
									end = 1;
								}
								//controlem el cas que tots els jugadors no poden robar mes fitxes
								if(counter >= pt.num_jugadors){
									printf("\n\tEmpat!\n");
									millor = 28;

									for(i=1;i<=pt.num_jugadors;i++){
										jugcount = 0;
										//contem les fitxes de cada jugador
										LLISTAPDI_vesInici(&pt.jugador[i].stock);
										while(!_fi(pt.jugador[i].stock)){
											LLISTAPDI_avanca(&pt.jugador[i].stock);
											jugcount++;
										}
										//ens guardem el valor de fitxes mes gran que trobem entre tots els jugadors
										if(jugcount < millor){
											millor = jugcount;
										}
									}

									for(i=1;i<=pt.num_jugadors;i++){
										jugcount = 0;
										//tornem a comptar les fitxes de cada jugador
										LLISTAPDI_vesInici(&pt.jugador[i].stock);
										while(!LLISTAPDI_fi(pt.jugador[i].stock)){
											LLISTAPDI_avanca(&pt.jugador[i].stock);
											jugcount++;
										}
										//si i jugador te la quantitat de fitxes que hem guardat abans, significa que es un guanyador
										//ho fem per el cas en que hi hagi un empat i mes d'un jugador tingui el nombre mes alt de fitxes
										if(jugcount == millor){
											millor = jugcount;
											pt.jugador[i].guanyador = 1;
										}
									}
									//imprimim per pantalla els jugadors que han guanyat
									for(i=1;i<=pt.num_jugadors;i++){
										if(pt.jugador[i].guanyador){
											printf("\n\t%s ha guanyat\n",pt.jugador[i].nom_jugador);
											printf("\n--- Prem Enter per continuar ---");
											while ( getchar() != '\n');
										}
									}
									end = 1;
								}

								if(end){
									//si s'acabat el joc, actualitzem el ranking i l'escrbim al fitxer
									updateRanking(&pt);
									g = fopen(argv[1],"wb");
									escriuRanking(g,&pt);
									fclose(g);

									g = fopen(argv[1],"rb");
									llegeixRanking(g,&pt);
									fclose(g);

									for(i=1;i<=pt.num_jugadors;i++){
										pt.jugador[i].guanyador = 0;
									}

									el = 0;

								}

								if(indexJ<pt.num_jugadors){
									//en cas de no haver acabat el joc sumem 1 al index del jugador al qui li toca jugar
									indexJ++;
								}else{
									//si indexJ es == a num_jugadors significa que ha arribat al limit i el resetejem
									indexJ=1;
								}
							}
							break;

						case 2:
							//cas on mostrem el ranking
							printf("\t1. Ordenar el ranking per ordre alfabetic.\n");
							printf("\t2. Ordenar el ranking per win rate (ordre descendent)\n");
							do{								//preguntem per la opcio								printf("\nMetode?: ");
								metode = 0;
								scanf("%d",&metode);
								fflushnou();								//controlem que la opcio sigui correcta								if(metode>2 || metode<1){
									printf("\nOpcio incorrecta\n");
								}
							}while(metode>2 || metode<1);

							switch(metode){
								case 1:
									//cas on ens demana ordernar per ordre alfabetic
									if(el){
										printf("\nNom-------Guanyades----Perdudes---Totals----WinRate\n");
										//en cas de no haver jugadors
										printf("----\t");
										printf("  --\t");
										printf("       --\t");
										printf("  --\t");
										printf("    --%%\n");
									} else {
										g = fopen(argv[1],"rb+");
										llegeixRanking(g,&pt);
										ordenaRankingAlfa(&pt);
										mostraRanking(pt);
										fclose(g);
									}
									printf("\n--- Prem Enter per continuar ---");
									while ( getchar() != '\n')
								break;
								break;

								case 2:
								//cas on ens demana ordernar per win rate
									if(el){
										printf("\nNom-------Guanyades----Perdudes---Totals----WinRate\n");
										//en cas de no haver jugadors
										printf("----\t");
										printf("  --\t");
										printf("       --\t");
										printf("  --\t");
										printf("    --%%\n");
									} else {
										g = fopen(argv[1],"rb+");
										llegeixRanking(g,&pt);
										ordenaRankingWin(&pt);
										mostraRanking(pt);
										fclose(g);
									}
									printf("\n--- Prem Enter per continuar ---");
									while ( getchar() != '\n')
								break;
							}
						break;
					}
				}while (opcio != 3);

			}
		}
	}
	return 0;
}
