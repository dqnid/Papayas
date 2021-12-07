#include <stdio.h>
#include <stdlib.h>
#include "arbol.h"

Nodo * generarBandeja(Arbol a, int proceso);
int generarConjunto(Arbol a);

int main(void)
{
	double eval;
	int i,j;
	listaPapayas l;
	listaPapayas ** conjunto;

	l.lista = (Papaya*)malloc(sizeof(Papaya)*20);
	l.num = 20;

	l.lista[0].peso = 0.273;
	l.lista[0].tiempo = 1.1;
	l.lista[0].id = 1400001;

	l.lista[1].peso = 0.405;
	l.lista[1].tiempo = 1;
	l.lista[1].id = 1400002;

	l.lista[2].peso = 0.517;
	l.lista[2].tiempo = 1.1;
	l.lista[2].id = 1400003;

	l.lista[3].peso = 0.533;
	l.lista[3].tiempo = 1.7;
	l.lista[3].id = 1400004;

	l.lista[4].peso = 0.358;
	l.lista[4].tiempo = 1.5;
	l.lista[4].id = 1400005;

	l.lista[5].peso = 0.562;
	l.lista[5].tiempo = 1.9;
	l.lista[5].id = 1400006;

	l.lista[6].peso = 0.322;
	l.lista[6].tiempo = 2.4;
	l.lista[6].id = 1400007;

	l.lista[19].peso = 0.494;
	l.lista[19].tiempo = 1.8;
	l.lista[19].id = 1400008;

	l.lista[7].peso = 0.39;
	l.lista[7].tiempo = 1.6;
	l.lista[7].id = 1400009;

	l.lista[8].peso = 0.281;
	l.lista[8].tiempo = 2.2;
	l.lista[8].id = 1400010;

	l.lista[9].peso = 0.395;
	l.lista[9].tiempo = 2;
	l.lista[9].id = 1400011;

	l.lista[10].peso = 0.407;
	l.lista[10].tiempo = 2;
	l.lista[10].id = 1400012;

	l.lista[11].peso = 0.329;
	l.lista[11].tiempo = 3;
	l.lista[11].id = 1400013;

	l.lista[12].peso = 0.629;
	l.lista[12].tiempo = 2.7;
	l.lista[12].id = 1400014;

	l.lista[13].peso = 0.417;
	l.lista[13].tiempo = 1.2;
	l.lista[13].id = 1400015;

	l.lista[14].peso = 0.278;
	l.lista[14].tiempo = 1.4;
	l.lista[14].id = 1400016;

	l.lista[15].peso = 0.583;
	l.lista[15].tiempo = 2.2;
	l.lista[15].id = 1400017;

	l.lista[16].peso = 0.598;
	l.lista[16].tiempo = 1.9;
	l.lista[16].id = 1400018;

	l.lista[17].peso = 0.271;
	l.lista[17].tiempo = 1.6;
	l.lista[17].id = 1400019;

	l.lista[18].peso = 0.265;
	l.lista[18].tiempo = 2.1;
	l.lista[18].id = 1400020;

	Arbol a = crearArbol(l);
	
	generarConjunto(a);

	puts("\n");

	return 0;
}

Nodo * generarBandeja(Arbol a, int proceso)
{
	double eval;
	int i,j;
	Arbol pivote = a;
	if (a==NULL)
		return NULL;
	if (pivote->peso >= 2)
		return pivote;

	while (pivote->peso < 2)
	{	
		if (expandirArbol(pivote)==1)
			return NULL;
		if (proceso != 0)
			mostrarArbol(pivote);
		eval = pivote->ramas[0]->coste;
		j=0;
		for (i=0;i<pivote->num;i++)
		{
			//Elección
			if (pivote->ramas[i]->coste < eval && pivote->ramas[i]->cerrado == 0)
			{
				j=i;
				eval = pivote->ramas[i]->coste;
			}
		}
		pivote = pivote->ramas[j];
	}	
	if (pivote->peso < 2)
		return NULL;
	pivote->cerrado = 1;
	return pivote;
}

int generarConjunto(Arbol a)
{
	Arbol resultado;
	int i,j;	

	resultado = generarBandeja(a, 0);
	j=1;
	while (resultado!=NULL)
	{
		printf("\nBandeja (%d): Peso=%lf, Precio=%lf\n| ",j, resultado->peso, resultado->precio);
		for (i=0; i<resultado->asignadas.num; i++)
			printf("%d(%lf) ", resultado->asignadas.lista[i].id,resultado->asignadas.lista[i].peso);
		printf("|");
		resultado = crearArbol(resultado->resto);
		resultado = generarBandeja(resultado, 0);
		j++;
	}
	return 0;	
}
