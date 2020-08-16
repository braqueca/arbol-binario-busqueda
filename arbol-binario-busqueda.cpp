/*Programacion III Seccion C
Billy Oswaldo Raquec Arias			Carnet:5990-14-5609
Programa ArbolBinarioBusqueda
programa hecho en Dev-C++ 5.11
Declaracion de librerias*/
#include<iostream>
//#include<windows.h>
#include<stdlib.h>
//#include<conio.h>
#include<math.h>

#define CIFRAS 3   //Cantidad de espacios minimos para graficar
using namespace std;

struct Nodo{
	int dato;
	Nodo *padre;
	Nodo *hijoIzquierdo;
	Nodo *hijoDerecho;
}*aux=NULL, *raiz=NULL;

Nodo* crearNodo();
void insertar(Nodo *nuevo, Nodo *raizSubArbol);
Nodo* buscar();
void eliminarHoja(Nodo *nodo, Nodo *padre);
void eliminarUnHijo(Nodo *padre, Nodo *nodo, Nodo *hijo, bool unHijo);
void eliminar();
bool tieneUnHijo(Nodo *nodo);
bool esHoja(Nodo *nodo);
void preOrden(Nodo *nodo);
void inOrden(Nodo *nodo);
void postOrden(Nodo *nodo);
int evaluarAltura(Nodo *nodo);
void graficar(Nodo *nodo, int espaciosX, int espaciosY, int nivel);
int obtenerEspaciosNivel(int nivel);

int main(){
	int opcion,altura;
	do{
		cout<<"\t\t\tMENU\n\n";
		cout<<"1.Insertar un nodo\n";
		cout<<"2.Buscar un nodo\n";
		cout<<"3.Eliminar\n";
		cout<<"4.Recorrido Pre Orden\n";
		cout<<"5.Recorrido In Orden\n";
		cout<<"6.Recorrido Post Orden\n";
		cout<<"7.Graficar\n";
		cout<<"8.Evaluar Altura\n";
		cout<<"9.Salir\n\n";
		cout<<"Ingrese su opcion\n";
		cin>>opcion;
		switch(opcion){
			case 1:
				{
					Nodo *nuevo = crearNodo();
					cout<<"Ingrese el dato a insertar: ";
					cin>>nuevo->dato;
					insertar(nuevo, raiz);
					nuevo = NULL;
					break;
				}
			case 2:			//caso 2
				buscar();   //Llamada a procedimiento buscar
				break;
			case 3:			//caso 3
				eliminar(); //Llamada a procedimiento eliminar
				break;
			case 4:			//caso 4
				preOrden(raiz);   //Llamada a procedimiento preOrden
				//getch();
				break;
			case 5:				//caso 5
				inOrden(raiz);  //Llamada a procedimiento inOrden
				//getch();
				break;
			case 6:				//caso 6
				postOrden(raiz);//Llamada a procedimiento postOrden
				//getch();
				break;
			case 7:				//caso 7
				system("cls");  //limpia pantalla
				graficar(raiz,80,3,1);   //Llamada a procedimiento graficar, enviandole como parametro la raiz, 80 que sera la coordenada en X, 3 que sera la coordenada en Y
				break;
			case 8:						//caso 8
				altura=evaluarAltura(raiz);   //le asigna a la variable altura lo que le devuelva la funcion evaluarAltura
				cout<<altura;					//Imprime la altura
				break;
			case 9:								//caso 9
				cout<<"Gracias por utilizar el programa";  //agradecimiento por usar el programa
				break;
			default:										//cualquier otro caso
				cout<<"Opcion invalida";					//indicando al usuario que no existe tal opcion
				break;
		}													//fin switch
	}while(opcion!=9);											//mientras opcion sea diferente a 9 o salir
}

Nodo* crearNodo(){
	Nodo *nuevo = new Nodo;
	nuevo->padre=NULL;
	nuevo->hijoIzquierdo=NULL;
	nuevo->hijoDerecho=NULL;

	return nuevo;
}

bool estaVacio(Nodo *raizSubArbol){
	return raizSubArbol == NULL;
}

void insertar(Nodo *nuevo, Nodo *raizSubArbol){
	if(estaVacio(raizSubArbol)){
		raiz = nuevo;
	}
	else{
		if(nuevo->dato <= raizSubArbol->dato){
			if(estaVacio(raizSubArbol->hijoIzquierdo)){
				raizSubArbol->hijoIzquierdo = nuevo;
			} else {
				insertar(nuevo, raizSubArbol->hijoIzquierdo);
			}
		}									//fin if
		else{								//si el dato del nuevo nodo es mayor al actual
			if(estaVacio(raizSubArbol->hijoDerecho)){
				raizSubArbol->hijoDerecho = nuevo;
			} else{
				insertar(nuevo, raizSubArbol->hijoDerecho);
			}
		}   								//fin else
	} 											//fin else
	cout<<"Agregado\n";
}												//fin procedimiento insertar

Nodo* buscar(){   //funcion insertar que devuelve la direccion de un nodo si este es encontrado y NULL si no lo es
	bool salir=false, encontrado=false;   //salir servira para salir de un ciclo y encontrado para indicar que encontro el nodo
	int dato;							//dato servira para almacenar el dato a buscar

	system("cls");						//Limpia pantalla

	cout<<"Ingrese el dato a buscar: "; //Solicitando dato
	cin>>dato;

	aux=raiz;							//referenciando aux a raiz
	cout<<"Recorriendo arbol"<<endl;
	while(!salir && aux!=NULL){			//mientras no sea indicada la salida y no llegue al final del arbol
		cout<<aux->dato<<endl;
		if(dato<aux->dato){				//si el dato buscado es menor al dato del nodo actual
			aux=aux->hijoIzquierdo;		//moverse un nodo a la izquierda
		}								//fin if
		else if(dato>aux->dato){		//sino si el dato buscado es mayor al dato del nodo actual
			aux=aux->hijoDerecho;		//moverse un nodo a la derecha
		}								//fin else if
		else if(dato==aux->dato){		//sino si dato buscado es igual al dato del nodo actual
			cout<<"Dato encontrado!!\n\n";   //el dato fue encontrado
			salir=true;						//indicando la salida del ciclo
			encontrado=true;				//indicando que el nodo fue encontrado
			return aux;						//regresa la direccion del nodo encontrado
		}									//fin else if
	}										//fin while
	if(!encontrado){						//si el nodo no fue encontrado
		cout<<"No se encontro el dato"<<endl;
		return NULL;   						//regresa NULL
	}										//fin if
	return NULL;
}											//fin funcion buscar

void eliminarUnHijo(Nodo *padre, Nodo *nodo, Nodo *hijo, bool unHijo){   //procedimiento eliminarUnHijo que resive como parametro 3 nodos que seran un padre su hijo y el hijo de su hijo
																		//y una variable booleana que indica nodo tiene un hijo ya que la funcion se utilizara para otro tipo de eliminacion
	if(padre->hijoIzquierdo==nodo){										//si el hijo izquierdo del padre es el nodo
		padre->hijoIzquierdo=hijo;										//el hijo izquierdo del padre va a ser ahora el hijo recibido en la funcion
		if(!unHijo){													//si no es la eliminacion de un nodo que tiene un solo hijo
			hijo->hijoDerecho=nodo->hijoDerecho;						//el hijo derecho del hijo del eliminado es ahora el hijo derecho del nodo eliminado
			hijo->hijoDerecho->padre=hijo;								//asignando el nuevo padre
		}																//fin if
	}																	//fin if
	else if(padre->hijoDerecho==nodo){									//sino si el hijo derecho del padre es el nodo eliminado
		padre->hijoDerecho=hijo;										//el hijo derecho del padre del eliminado es el hijo ahora
		if(!unHijo){													//si el nodo eliminado no tiene un solo hijo
			hijo->hijoDerecho=nodo->hijoDerecho;						//el hijo derecho del hijo del eliminado es ahora el hijo derecho del nodo eliminado
			hijo->hijoDerecho->padre=hijo;								//asignando el nuevo padre
		}																//fin if
	}																	//fin if
	hijo->padre=padre;													//el padre del hijo del eliminado es ahora el padre del eliminado
	delete nodo;														//eliminando el nodo
}																		//Fin procedimiento eliminarUnHijo

void eliminarHoja(Nodo *nodo, Nodo *padre){   //Procedimiento eliminar hoja recibe como parametros el nodo a eliminar y su padre
	if(padre->hijoDerecho == nodo){									//si el hijo derecho del padre del nodo a eliminar es el nodo a eliminar
        padre->hijoDerecho = NULL;										//El hijo derecho del padre del nodo a eliminar es NULL ahora
	} 																	//fin if
    else if(padre->hijoIzquierdo == nodo) {								//sino si el hijo izquierdo del padre del nodo a eliminar es el nodo a eliminar
    	padre->hijoIzquierdo = NULL;									//el hijo izquierdo del padre del nodo a eliminar es igual a NULL
	}																	//fin else
    delete nodo; // Borrar el nodo
    nodo = NULL; //nodo es igual a NULL
    return;		//regresa al proceso que lo llamo
}				//fin funcion eliminarHoja

bool esHoja(Nodo *nodo){   //Funcion que devuelve verdadero si el nodo es hoja y falso si no lo es
	if(nodo->hijoIzquierdo==NULL && nodo->hijoDerecho==NULL){   //si el nodo no tiene hijos
		return true;											//devuelve verdadero
	}															//fin if
	else return false;											//sino regresa falso
}																//fin funcion esHoja

bool tieneUnHijo(Nodo *nodo){   //funcion que devuelve verdadero si el nodo solo tiene un hijo y falso si el nodo tiene mas de un hijo
	if(nodo->hijoIzquierdo!=NULL && nodo->hijoDerecho==NULL){   //si el nodo solo teiene hijo izquierdo
		eliminarUnHijo(nodo->padre,nodo,nodo->hijoIzquierdo,true);   //Llamar a la funcion eliminarUnHijo mandandole como parametros el padre del nodo, el nodo, su hijo izquierdo y true indicandole que se esta eliminando un nodo que solo tiene un hijo
		return true;												//devuelve verdadero
	}																//fin if
	else if(nodo->hijoIzquierdo==NULL && nodo->hijoDerecho!=NULL){  //sino si el nodo solo tiene hijo derecho
		eliminarUnHijo(nodo->padre,nodo,nodo->hijoDerecho,true);	//Llamar a la funcion eliminarUnHijo mandandole como parametros el padre del nodo, el nodo, su hijo derecho y true indicandole que se esta eliminando un nodo que solo tiene un hijo
		return true;												//devuelve verdadero
	}																//fin else if
	else{															//en cualquier otro caso
		return false;												//regresar falso
	}																//fin else
}																	//fin funcion tieneUnHijo

void eliminar(){   //funcion que elimina un nodo
	Nodo *temp;   //puntero que nos ayudara a encontrar el nodo que sustituira el nodo eliminado
	int contadorRecorrido=0;    //variable que cuenta cuantos nodos va recorriendo hacia la derecha para buscar el nodo mas a la derecha del subarbol izquierdo
	aux=buscar();   			//aux tomara la referencia que devuelve la funcion buscar

	if(aux==NULL || aux==raiz){   //si aux es null quiere decir que no se encontro el nodo o si aux es raiz
		cout<<"No se puede eliminar, no se encontro o es raiz";
	}															//fin if
	else{														//sino
		Nodo *padreAux=aux->padre;								//se crea un puntero que apuntara al padre del nodo encontrado
		if(esHoja(aux)) { // Y si es un nodo hoja: lo borramos
            eliminarHoja(aux,padreAux);   //Llamada a la funcion eliminarHoja enviandole como parametros el nodo a borrar y su padre
            cout<<"Eliminado";
        }								//fin if
		else if(tieneUnHijo(aux)){		//sino si tiene un solo hijo
			cout<<"Eliminado";			//indicando que se elimino ya que en la funcion tieneUnHijo hay una llamada a la funcion eliminarUnHijo
		}								//fin else if
		else{							//sino
			temp=aux->hijoIzquierdo;	//direccionar temp al hijo izquierdo de auxiliar debido a que se tomara el criterio de eliminacion que dice que el nodo mas a la derecha del subarbol derecho tomara el lugar del nodo eliminado
			while(temp->hijoDerecho!=NULL){   //mientras el hijo derecho de temp no sea null
				temp=temp->hijoDerecho;		//recorre al hijo derecho
				contadorRecorrido++;		//suma cada iteracion
			}								//fin while
			if(contadorRecorrido==0){		//si el contador de recorrido se quedo en cero quiere decir que el hijo izquierdo de aux no tiene hijo derecho
				eliminarUnHijo(aux->padre,aux,aux->hijoIzquierdo,false);   //Llama al procedimiento eliminarUnHijo enviandole como parametro el padre del nodo a eliminar
																			//el nodo a eliminar, su hijo izquierdo y false indicandole que no es un nodo que solo tiene un hijo
			}																//fin if
			else{															//si el hijo izquierdo de aux tiene hijos derechos
				aux->dato=temp->dato;										//el dato de aux va a ser igual al dato del nodo mas a la derecha del subarbol izquierdo
				temp->padre->hijoDerecho=temp->hijoIzquierdo;				//el hijo derecho del padre de temporal ahora va a ser el hijo izquierdo de temporal
				delete temp;												//se elimina temporal
				temp=NULL;													//temp es igual a null
			}																//fin else
		}																	//fin else
		cout<<"Eliminado";
	}																		//fin else
}																			//fin funcion eliminar

void preOrden(Nodo *nodo){   //procedimiento recursivo que muestra el recorrido pre-orden del arbol, recibe la raiz en la primera llamada, luego los demas nodos recursivamente
	if(nodo!=NULL){			//si el nodo no es NULL
		cout<<nodo->dato<<" ";   //imprime raiz
		preOrden(nodo->hijoIzquierdo);   //Llamada recursiva a este procedimiento enviandole como parametro el hijo izquierdo del nodo
		preOrden(nodo->hijoDerecho);	//Llamada recusiva a este procedimiento enviandole como parametro el hijo derecho del nodo
	}									//fin if
}										//fin procedimiento preOrden

void inOrden(Nodo *nodo){   //procedimiento recursivo que muestra el recorrido in-orden del arbol, recibe la raiz en la primera llamada, luego los demas nodos
	if(nodo!=NULL){			//si el nodo no es NULL
		inOrden(nodo->hijoIzquierdo);   //llamada recursiva al procedimiento inOrden enviandole como parametro el hijo izquierdo del nodo
		cout<<nodo->dato<<" ";			//imprime raiz
		inOrden(nodo->hijoDerecho);		//Llamada recursiva al procedimiento inOrden enviandole como parametro el hijo derecho del nodo
	}									//fin if
}										//fin procedimiento inOrden

void postOrden(Nodo *nodo){   //Procedimiento recursivo que muestra el recorrido post-orden del arbol
	if(nodo!=NULL){				//si el nodo no es null
		postOrden(nodo->hijoIzquierdo);   //Llamada recursiva al procedimiento postOrden enviandole como parametro el hijo izquierdo del nodo
		postOrden(nodo->hijoDerecho);	//Llamada recursiva al procedimiento postOrden enviandole como parametro el hijo derecho del nodo
		cout<<nodo->dato<<" ";			//imprimiendo raiz
	}									//fin if
}										//fin funcion postOrden

int evaluarAltura(Nodo *nodo){   //funcion recursiva que evalua la altura del arbol
	int altura=0;				//variable que almacenara la altura del arbol con valor inicial 0

	if(nodo!=NULL){				//si el nodo no es null
		altura++;				//suma una unidad a la variable altura

		int alturaIzquierda=evaluarAltura(nodo->hijoIzquierdo);   //variable que tomara el valor que le regrese la llamada recursiva a esta funcion enviandole como parametro el hijo izquierdo el nodo
		int alturaDerecha=evaluarAltura(nodo->hijoDerecho);		//variable que tomara el valor que le regrese la llamada recursiva a esta funcion enviandole como parametro el hijo derecho del nodo

		if(alturaIzquierda>alturaDerecha) altura=altura+alturaIzquierda;   //si la altura izquierda es mayor a la altura derecha la altura total de lo evaluado es altura actual mas la altura izquierda
		else altura=altura+alturaIzquierda;									//sino la altura es igua a la altura mas la altura derecha
	}																		//fin if

	return altura;   //regresa la altura a cada una de las llamadas
}					//fin funcion evaluarAltura

int obtenerEspaciosNivel(int nivel){   //funcion que devuelve el espaciado entre nodos pintados
	return (160/pow(2,nivel));
}										//fin funcion

void graficar(Nodo *nodo, int espaciosX, int espaciosY, int nivel){   //procedimiento que grafica el arbol (Prueba) recibe como parametros el nodo a pintar
																		//las coordenadas en x e y, y el nivel donde esta situado ahora
	int espaciosNivelSiguiente=0;									//variable que guardara el espaciado del siguiente nivel
	if(nodo!=NULL){													//si el nodo es diferente de null

		cout<<nodo->dato;											//pinta el nodo
		espaciosNivelSiguiente=obtenerEspaciosNivel(nivel+1);		//espaciosNivelSiguiente toma el valor que le devuelve la funcion obtenerEspaciosNivelSiguiente
		graficar(nodo->hijoIzquierdo, espaciosX-espaciosNivelSiguiente,espaciosY+3,nivel++);   //Llamada recursiva a este procedimiento enviandole como parametros el hijo izquierdo del nodo
																								//las coordenadas en x e y, y el nivel aumentado en 1
		graficar(nodo->hijoDerecho, espaciosX+espaciosNivelSiguiente,espaciosY+3,nivel++);		//Llamada recursiva a este procedimiento enviandole como parameetro el hijo derecho del nodo
																								//las coordenadas en x e y, y el nivel aumentado en 1
	}																							//fin if
}																								//fin procedimiento graficar
