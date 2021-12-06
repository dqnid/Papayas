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

	l.lista = (Papaya*)malloc(sizeof(Papaya)*4);
	l.num = 4;

	l.lista[1].peso = 1.5;
	l.lista[1].tiempo = 2.1;
	l.lista[1].id = 1;
	l.lista[2].peso = 0.9;
	l.lista[2].tiempo = 3.1;
	l.lista[2].id = 2;
	l.lista[0].peso = 4.3;
	l.lista[0].tiempo = 1.1;
	l.lista[0].id = 0;
	l.lista[3].peso = 0.3;
	l.lista[3].tiempo = 1.1;
	l.lista[3].id = 0;

	Arbol a = crearArbol(l);
	
	generarConjunto(a);
	//for (i=0;i<4;i++)
	//	mostrarArbol(conjunto[i]);

	return 0;
}

Nodo * generarBandeja(Arbol a, int proceso)
{
	double eval;
	int i,j;
	Arbol pivote = a;
	if (a==NULL)
		return NULL;
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
			if (pivote->ramas[i]->coste < eval) //¿Falta ponderar en función de la cercanía a 2kg?
			{
				j=i;
				eval = pivote->ramas[i]->coste;
			}
		}
		pivote = pivote->ramas[j];
	}	
	return pivote;
}

int generarConjunto(Arbol a)
{
	Arbol resultado;
	int i,j;	
	//Debería generar un nuevo árbol	
	resultado = generarBandeja(a, 0);
	j=1;
	while (resultado!=NULL)
	{
		printf("\nBandeja (%d)\n| ",j);
		for (i=0; i<resultado->asignadas.num; i++)
			printf("%d(%lf) ", resultado->asignadas.lista[i].id,resultado->asignadas.lista[i].peso);
		printf("|");
		resultado = crearArbol(resultado->resto);
		resultado = generarBandeja(resultado, 0);
		j++;
	}
	return 0;	
}
