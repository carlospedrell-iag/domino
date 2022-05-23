#include "fitxers.h"


	void llegeixJugadors(FILE *f,Partida *p,int *error){

		int i=0,ordre,before=0;
		char aux[50];
		//llegim del fitxer de text el numero de jugadors
		fscanf(f,"%d",&p->num_jugadors);
		//ho controlem
		if(p->num_jugadors < 2 || p->num_jugadors > 4){
			*error = 1;
	  		printf("\nError! el numero de jugadors ha d'estar entre 2 i 4\n\n");
		}else{
			//fem alocacio de memoria en funcio del numero de jugadors trobat
			p->jugador =  (Jugador *) malloc( (p->num_jugadors + 1) * sizeof(Jugador));
			//saltem newline
			fgets(aux,10,f);
			fgets(aux,50,f);
			//fem aquest bucle per el nombre de jugadors
	  		for(i=1;i<=p->num_jugadors;i++){
				//si la cadena del jugador es mes petita de 20, error
				if(strlen(aux)-4>20){
		  			*error = 1;
					if(!before){
						printf("\nError! Maxim 20 caracters per nom!\n\n");
						before = 1;
					}
				}else{
					ordre = atoi(&aux[strlen(aux)-3]);

					aux[strlen(aux)-4]= '\0';
					p->jugador[ordre].nom_jugador = (char *) malloc( strlen(aux) * sizeof(char));
					strcpy(p->jugador[ordre].nom_jugador,aux);
					fgets(aux,50,f);
					//tornem a llegir per el seguent jugador
				}
			}
		}
		fclose(f);
	}

	void llegeixRanking(FILE *g, Partida *p){
		int i=0;

		Ranking raux;
		//posem el cursor al inici del fitxer
		fseek(g,0,SEEK_SET);
		fread(&p->num_jr, sizeof(int),1,g);
		//fem alocacio de memoria segons el numero de jugadors llegit del fitxer
		p->jr =  (Jugador *) malloc((p->num_jr ) * sizeof(Jugador));

		for(i=0;i<p->num_jr;i++){
			//pasem els valors del tipus auxiliar a cada jugador
			fread(&raux, sizeof(Ranking),1,g);
			p->jr[i].nom_jugador = (char *) malloc(  strlen(raux.nom) * sizeof(char));
			strcpy(p->jr[i].nom_jugador,raux.nom);
			p->jr[i].partides_guanyades = raux.pg;
			p->jr[i].partides_perdudes = raux.pp;
			p->jr[i].guanyador = 0;
		}

	}

	void mostraRanking(Partida p){
		int i=0;
		float winrate;

		printf("\nNom-------Guanyades----Perdudes---Totals----WinRate\n");
		//en cas de no haver jugadors
		if(p.num_jr  == 0){
			printf("----\t");
			printf("  --\t");
			printf("       --\t");
			printf("  --\t");
			printf("    --%%\n");
		}

		for(i=0;i<p.num_jr;i++){
			//controlem que la divisio del winrate no doni indeterminacio
			winrate = ((float)p.jr[i].partides_guanyades / (float)(p.jr[i].partides_guanyades + p.jr[i].partides_perdudes)) * 100;
			//imprimim per pantalla els valors de cada jugador
			printf("%s\t",p.jr[i].nom_jugador);
			printf("   %d\t",p.jr[i].partides_guanyades);
			printf("      %d\t", p.jr[i].partides_perdudes);
			printf("           %d\t", p.jr[i].partides_perdudes + p.jr[i].partides_guanyades);
			printf("    %.2f%%\n",winrate);

		}
	}

	void updateRanking(Partida *p){
		int i,j,counter =0,flag=0;

		for(i=0;i<p->num_jr;i++){
			flag = 0;
			for(j=1;j<=p->num_jugadors;j++){
				//fem un scan dels noms dels jugadors del ranking i el comparem amb cada nom de jugador
				if(strcmp(p->jr[i].nom_jugador,p->jugador[j].nom_jugador) == 0){
					//si els noms coincideixen
					if(p->jugador[j].guanyador){
						p->jr[i].partides_guanyades ++;
						//afegim 1, al comptador de partides guanyades de i jugador del ranking
					}else{
						p->jr[i].partides_perdudes ++;
						//si no coincideixen afegim 1 al comptador de partides perdudes
					}
				} else {
				}
			}
		}

		for(j=1;j<=p->num_jugadors;j++){
			flag = 0;
			for(i=0;i<p->num_jr;i++){
				//ara fem un scan per posar els jugadors que no es troben en el ranking
				if(strcmp(p->jr[i].nom_jugador,p->jugador[j].nom_jugador) == 0){
					//si coincideixnen els noms llavors no caldra afegir un jugador
					flag=1;
				}
			}
			if(!flag){
				//en el cas de no trobar el jugador en el ranking l'afegim
				if(p->jugador[j].guanyador){
					//si aquest jugador es guanyador, creem un nou jugador en l'array dinamica amb valor 1 en guanyador
					counter++;
					p->jr = (Jugador *)realloc(p->jr, (p->num_jr + counter) * sizeof(Jugador));
					p->jr[p->num_jr + counter - 1].nom_jugador = (char *) malloc(strlen(p->jugador[j].nom_jugador) * sizeof(char));
					strcpy(p->jr[p->num_jr + counter - 1].nom_jugador,p->jugador[j].nom_jugador);
					p->jr[p->num_jr + counter - 1].partides_guanyades = 1;
					p->jr[p->num_jr + counter - 1].partides_perdudes = 0;

				}else{
					//si aquest jugador es perdedor, creem un nou jugador en l'array dinamica amb valor 1 en perdedor
					counter++;
					p->jr = (Jugador *)realloc(p->jr, (p->num_jr + counter) * sizeof(Jugador));
					p->jr[p->num_jr + counter - 1].nom_jugador = (char *) malloc(strlen(p->jugador[j].nom_jugador) * sizeof(char));
					strcpy(p->jr[p->num_jr + counter - 1].nom_jugador,p->jugador[j].nom_jugador);
					p->jr[p->num_jr + counter - 1].partides_guanyades = 0;
					p->jr[p->num_jr + counter - 1].partides_perdudes = 1;

				}
			}
		}
		//segons el comptador de jugadors nous afegim el numero a la variable que controla la quantitat general de jugadors en el ranking
		p->num_jr = p->num_jr + counter;

	}

	void escriuRanking(FILE *g, Partida *p){
		int i;
		Ranking raux;
		//coloquem el cursor al inici del fitxer
		fseek(g,0,SEEK_SET);
		//escribim el numero de jugadors en la primera casella del fitxer
		fwrite(&p->num_jr, sizeof(int),1,g);

		for(i=0;i<p->num_jr;i++){
			//per cada jugador posem els nous valors en el tipus auxiliar estatic Ranking
			strcpy(raux.nom,p->jr[i].nom_jugador);
			raux.pg = p->jr[i].partides_guanyades;
			raux.pp = p->jr[i].partides_perdudes;
			//escribim de cop com a tipus ranking els valors del jugador
			fwrite(&raux, sizeof(Ranking),1,g);
		}
	}

	void ordenaRankingAlfa(Partida *p){
		int casmin=0,i,j,comp = 0;
		Jugador jmin;

		for (i = 0; i < p->num_jr - 1; i++)	{

			jmin = p->jr[i];
			casmin = i;

			for (j = i ; j < p->num_jr ; j++){
				comp = strcmp(p->jr[j].nom_jugador,jmin.nom_jugador);
				if(comp<0)	{
					jmin = p->jr[j];
					casmin = j;
				}
			}

			p->jr[casmin] = p->jr[i];
			p->jr[i] = jmin;
		}
	}

	void ordenaRankingWin(Partida *p){
		int i,j,intercanvi = 1;
		float winrate,winrate1;

		Jugador aux;

		for(i=1; i < p->num_jr && intercanvi; i++)	{

			intercanvi = 0;

			for(j = p->num_jr - 1; j >= i; j --)	{

					winrate = (float)p->jr[j].partides_guanyades / (float)(p->jr[j].partides_guanyades + p->jr[j].partides_perdudes);

					winrate1 = (float)p->jr[j-1].partides_guanyades / (float)(p->jr[j-1].partides_guanyades + p->jr[j-1].partides_perdudes);

				if( winrate1 < winrate)	{

					aux = p->jr[j-1];
					p->jr[j-1] = p->jr[j];
					p->jr[j] = aux;
					intercanvi = 1;

				}
			}
		}
	}

	void escriuTest(FILE *g){
		int i=0,num;

		Ranking raux[10];

		fseek(g,0,SEEK_SET);

		printf("num jugadors:");
		scanf("%d",&num);
		fwrite(&num, sizeof(int),1,g);

		for(i=0;i<num;i++){
			printf("Digues nom: ");
			scanf("%s",raux[i].nom);

			raux[i].pg = 3 + i;

			raux[i].pp = 0 + i;

			fwrite(&raux[i], sizeof(Ranking),1,g);

			}
	}
