#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

struct Tarea{
	int tareaID; //numerado en ciclo iterativo
	char *descripcion;
	int duracion; //entre 10 y 100
};

struct Nodo{
	struct Tarea T;
	Nodo* siguiente;
};

typedef struct Nodo* Lista;

//--------------------------------------------------------------------//
//----------------------DEFINICION DE FUNCIONES-----------------------//
//--------------------------------------------------------------------//

Lista cargarTareasPendientes(Lista TP, int n);
Lista insertar(Lista L, Tarea x);
bool esListaVacia(Lista L);
void realizarTareas(Lista *TP, Lista *TR);
void mostrarTareasRealizadas(Lista TR);
void mostrarTareasPendientes(Lista TP);
void mostrarTarea(Tarea T);
Tarea busquedaPorPalabra(Lista *TP, Lista *TR, char clave[]);
Tarea busquedaPorID(Lista *TP, Lista *TR, int id);

//--------------------------------------------------------------------//
//--------------------------------MAIN--------------------------------//
//--------------------------------------------------------------------//

int main(){
	srand(time(NULL));
	int n, aux;
	Tarea busqueda;
	
	printf("Ingrese la cantidad de tareas que desea cargar: "); scanf("%d",&n);
	
	Lista TareasPendientes = NULL;
	Lista TareasRealizadas = NULL;
	
	printf("\n");
	printf("--------------------------------------------------------------------\n");
	printf("--------------------------CARGA DE TAREAS---------------------------\n");
	printf("--------------------------------------------------------------------\n");
	TareasPendientes = cargarTareasPendientes(TareasPendientes, n);
	
	printf("\n");
	printf("--------------------------------------------------------------------\n");
	printf("-------------------------REVISION DE TAREAS-------------------------\n");
	printf("--------------------------------------------------------------------\n");
	realizarTareas(&TareasPendientes, &TareasRealizadas);
	
	printf("\n");
	printf("--------------------------------------------------------------------\n");
	printf("-------------------------TAREAS REALIZADAS--------------------------\n");
	printf("--------------------------------------------------------------------\n");
	mostrarTareasRealizadas(TareasRealizadas);
	
	printf("\n");
	printf("--------------------------------------------------------------------\n");
	printf("-------------------------TAREAS PENDIENTES--------------------------\n");
	printf("--------------------------------------------------------------------\n");
	mostrarTareasPendientes(TareasPendientes);
	
	printf("\n");
	printf("--------------------------------------------------------------------\n");
	printf("-------------------------BUSQUEDA DE TAREAS-------------------------\n");
	printf("-----------------------------por clave------------------------------\n");
	char clave[15];
	printf("\nIngrese una palabra clave: "); fflush(stdin); gets(clave);
	busqueda = busquedaPorPalabra(&TareasPendientes, &TareasRealizadas, clave);
	if(busqueda.tareaID == -1){
		printf("\nNo se encontraron tareas con esa palabra clave");
	}else{
		mostrarTarea(busqueda);
	}
	
	printf("\n");
	printf("--------------------------------------------------------------------\n");
	printf("-------------------------BUSQUEDA DE TAREAS-------------------------\n");
	printf("-------------------------------por ID-------------------------------\n");
	printf("\n");
	aux = 0;
	while(aux<1 || aux>n){
		printf("Ingrese el ID de la tarea que busca: "); fflush(stdin); scanf("%d",&aux);
	}
	busqueda = busquedaPorID(&TareasPendientes, &TareasRealizadas, aux);
	if(busqueda.tareaID == -1){
		printf("\nNo se encontraron tareas con ese ID");
	}else{
		mostrarTarea(busqueda);
	}
	
	free(TareasPendientes);
	free(TareasRealizadas);
	
	return 0;
}

//--------------------------------------------------------------------//
//-----------------------------FUNCIONES------------------------------//
//--------------------------------------------------------------------//

Lista cargarTareasPendientes(Lista TP, int n){
	int i, aux;
	Tarea nuevo;
	for(i = 0; i < n; i++){
		printf("\nTarea #%d", i+1);
		nuevo.tareaID = i+1;
		
		char *desc = (char *) malloc(50 * sizeof(char));
		printf("\nIngrese una descripcion: "); fflush(stdin); gets(desc);
		nuevo.descripcion = desc;
		
		aux = 0;
		while(aux<10 || aux>100){
			printf("Duracion: "); fflush(stdin); scanf("%d", &aux);
		}
		nuevo.duracion = aux;
		
		TP = insertar(TP, nuevo);
	}
	
	return TP;
}

Lista insertar(Lista L, Tarea x){
	struct Nodo *nuevo;
	nuevo = new struct Nodo;
	nuevo->T.tareaID = x.tareaID;
	nuevo->T.descripcion = x.descripcion;
	nuevo->T.duracion = x.duracion;
	nuevo->siguiente = L;
	L = nuevo;
	return L;
}

bool esListaVacia(Lista L){
	if(L == NULL){
		return true;
	}else{
		return false;
	}
}

void realizarTareas(Lista *TP, Lista *TR){
	int aux;
	Lista TPnueva = NULL;
	
	while(!esListaVacia(*TP)){
		printf("\nTarea %d: ", (*TP)->T.tareaID);
		printf("\nDescripcion: %s", (*TP)->T.descripcion);
		printf("\nDuracion: %d dias", (*TP)->T.duracion);
		printf("\nSe realizo esta tarea?\n");
		do{
			printf("(Ingrese un numero: 1 = si, 0 = no): "); scanf("%d",&aux);
		}while(aux<0 || aux>1);
		
		if(aux==1){
			*TR = insertar(*TR, (*TP)->T);
		}else{                    
			TPnueva = insertar(TPnueva, (*TP)->T);
		}
		
		*TP = (*TP)->siguiente;
	}
	
	*TP = TPnueva;
}

void mostrarTareasRealizadas(Lista TR){
	while(!esListaVacia(TR)){
		mostrarTarea(TR->T);
		TR = TR->siguiente;
	}
}

void mostrarTareasPendientes(Lista TP){
	while(!esListaVacia(TP)){
		mostrarTarea(TP->T);
		TP = TP->siguiente;
	}
}

void mostrarTarea(Tarea T){
	printf("\nTarea %d: ", T.tareaID);
	printf("\nDescripcion: %s", T.descripcion);
	printf("\nDuracion: %d dias", T.duracion);
	printf("\n");
}

Tarea busquedaPorPalabra(Lista *TP, Lista *TR, char clave[]){
	Lista auxTP = *TP;
	Lista auxTR = *TR;
	
	while(!esListaVacia(*TP)){
		while(*((*TP)->T.descripcion) != '\0'){
			if(strstr((*TP)->T.descripcion, clave)){
	            return (*TP)->T;
	    	}
	    	((*TP)->T.descripcion)++;
		}
		*TP = (*TP)->siguiente;
	}
	
	while(!esListaVacia(*TR)){
		while(*((*TR)->T.descripcion) != '\0'){
			if(strstr((*TR)->T.descripcion, clave)){
	            return (*TR)->T;
	    	}
	    	((*TR)->T.descripcion)++;
		}
		*TR = (*TR)->siguiente;
	}
	
	*TP = auxTP;
	*TR = auxTR;
	
	Tarea noEnc;
	noEnc.tareaID = -1;
	return noEnc;
}

Tarea busquedaPorID(Lista *TP, Lista *TR, int id){

	while(!esListaVacia(*TP)){
		if(id == (*TP)->T.tareaID) return (*TP)->T;
		*TP = (*TP)->siguiente;
	}
	
	while(!esListaVacia(*TR)){
		if(id == (*TR)->T.tareaID) return (*TR)->T;
		*TR = (*TR)->siguiente;
	}
	
	Tarea noEnc;
	noEnc.tareaID = -1;
	return noEnc;
}
