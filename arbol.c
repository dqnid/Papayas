#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "arbol.h"

Arbol crearArbol(listaPapayas l)
{
	if (l.num == 0)
		return NULL;
	Arbol nuevo = (Arbol)malloc(sizeof(Nodo));
	nuevo->resto = l;
	nuevo->asignadas.lista = NULL;
	nuevo->asignadas.num = 0;
	nuevo->cerrado = 0;
	nuevo->num = 0;
	nuevo->ramas = NULL;
	nuevo->anterior = NULL;
	nuevo->coste = 0;
	nuevo->peso = 0;

	return nuevo;
}

int expandirArbol(Arbol a)
{
	int i,j,k;
	if (a->num != 0)
		return 1;
	if ((obtenerPesoListaPapayas(a->resto) + a->peso) < 2)
		return 1;
	a->ramas = (Nodo**)malloc(sizeof(Nodo*)*(a->resto.num));
	for (i=0; i<a->resto.num; i++)
	{
		a->ramas[i] = (Nodo*)malloc(sizeof(Nodo));
		a->num += 1;
	}

	for (i=0; i<a->num; i++)
	{
		a->ramas[i]->resto.lista = (Papaya*)malloc(sizeof(Papaya)*(a->resto.num - 1));
		k=0;
		for (j=0; j<a->resto.num; j++)
		{
			if (j != i)
			{
				a->ramas[i]->resto.lista[k] = a->resto.lista[j];	
				k++;
			}
		}
		a->ramas[i]->resto.num = k;

		a->ramas[i]->asignadas.lista = (Papaya *)malloc(sizeof(Papaya)*(a->asignadas.num + 1));	
		j = 0;
		while (j<a->asignadas.num){
			a->ramas[i]->asignadas.lista[j]=a->asignadas.lista[j];
			j++;
		}
		a->ramas[i]->asignadas.lista[j] = a->resto.lista[i];
		a->ramas[i]->asignadas.num = j+1;

		a->ramas[i]->cerrado = 0;
		a->ramas[i]->num = 0;

		a->ramas[i]->ramas = NULL;
		a->ramas[i]->anterior = a;

		a->ramas[i]->coste = evaluarListaPapayas(a->ramas[i]->asignadas);
		a->ramas[i]->peso = obtenerPesoListaPapayas(a->ramas[i]->asignadas);
		a->ramas[i]->precio = obtenerPrecioListaPapayas(a->ramas[i]->asignadas);
	}
	a->cerrado = 1;

	return 0;
}

double evaluarListaPapayas(listaPapayas l)
{
	// precioBandeja = 0.3 + 2*peso + 0.05*tiempo + 0.1*nPapayas
	// 2 - 2.1 = 0.1
	double res,temp;
	temp = obtenerPesoListaPapayas(l);
	res = (fabs(PP - temp)) + (PU / l.lista[l.num-1].peso) - (PA / l.lista[l.num-1].tiempo);
	//res = (fabs(PP - temp)) + (PU / l.lista[l.num-1].peso) + (PA * l.lista[l.num-1].tiempo);
	return res;
}

double obtenerPrecioListaPapayas(listaPapayas l)
{
	double res;
	res = PB;
	for (int i=0; i<l.num; i++)
		res += PU + PP*l.lista[i].peso + PA*l.lista[i].tiempo;
	return res;
}

double obtenerPesoListaPapayas(listaPapayas l)
{
	double peso=0;
	for (int i=0; i<l.num; i++)
		peso+=l.lista[i].peso;
	return peso;
}

void mostrarArbol(Arbol a)
{
	int i,j;
	Nodo * pivote;

	if (a!=NULL)
	{
		printf("|Libres:( ");
		for (j=0;j<a->resto.num;j++)
			printf("%d ", a->resto.lista[j].id);
		printf(") ");
		printf(" Usados:( ");
		for (j=0;j<a->asignadas.num;j++)
			printf("%d ", a->asignadas.lista[j].id);
		printf(")|\n");
		printf("|Peso: %lf,Cose: %lf|\n\n", a->peso, a->coste);
	}
	for (i=0; i<a->num; i++)	
		mostrarArbol(a->ramas[i]);
}
