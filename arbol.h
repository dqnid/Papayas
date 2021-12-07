#define PP 2 	//Precio por peso
#define PA 0.05 //Precio por almacén
#define PU 0.1	//Precio por procesado de unidad
#define PB 0.3	//Precio bandeja

typedef struct papaya{
	double peso;
	int id;
	float tiempo;
}Papaya;

typedef struct listaPapayas{
	Papaya * lista;
	int num;
}listaPapayas;

typedef struct nodo{
	listaPapayas resto;
	listaPapayas asignadas;
	int cerrado;
	int num;
	struct nodo ** ramas;
	struct nodo * anterior;

	double coste;
	double precio;
	double peso;
}Nodo;

typedef Nodo * Arbol;

Arbol crearArbol(listaPapayas l);

/*
Siempre expando en todas las ramas posibles
Puedo hacer la evaluación del nodo aquí mismo
 @param nodo del árbol que queremos expandir
 @return puntero a la rama con mejor evaluación
nota: igual es mejor separarlo todo en funciones, por un lado el despliegue del árbol y, por otro, las evaluaciones y toma de deciciones.
*/
int expandirArbol(Arbol a);

double evaluarListaPapayas(listaPapayas l);
double obtenerPrecioListaPapayas(listaPapayas l);
double obtenerPesoListaPapayas(listaPapayas l);

void mostrarArbol(Arbol a);

void liberarMemoria(Arbol a);
