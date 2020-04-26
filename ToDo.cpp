#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

typedef struct Tarea{
	int tareaID; //numerado en ciclo iterativo
	char *descripcion;
	int duracion; //entre 10 y 100
}Tarea;

//--------------------------------------------------------------------//
//----------------------DEFINICION DE FUNCIONES-----------------------//
//--------------------------------------------------------------------//

void cargarTareasPendientes(Tarea *TP, int n);
void realizarTareas(Tarea *TP, Tarea *TR, int n);
void mostrarTareasRealizadas(Tarea *TR, int n);
void mostrarTareasPendientes(Tarea *TP, int n);
void mostrarTarea(Tarea T);
Tarea buscarTarea(Tarea *TP, Tarea *TR, int n, char clave[]);

//--------------------------------------------------------------------//
//--------------------------------MAIN--------------------------------//
//--------------------------------------------------------------------//

int main(){
	srand(time(NULL));
	int n, i;
	
	printf("Ingrese la cantidad de tareas que desea cargar: "); scanf("%d",&n);
	
	Tarea *TareasPendientes = (Tarea *) malloc(n * sizeof(Tarea));
	Tarea *TareasRealizadas = (Tarea *) malloc(n * sizeof(Tarea));
	
	printf("\n");
	printf("--------------------------------------------------------------------\n");
	printf("--------------------------CARGA DE TAREAS---------------------------\n");
	printf("--------------------------------------------------------------------\n");
	cargarTareasPendientes(TareasPendientes, n);
	
	printf("\n");
	printf("--------------------------------------------------------------------\n");
	printf("-------------------------REVISION DE TAREAS-------------------------\n");
	printf("--------------------------------------------------------------------\n");
	realizarTareas(TareasPendientes, TareasRealizadas, n);
	
	printf("\n");
	printf("--------------------------------------------------------------------\n");
	printf("-------------------------TAREAS REALIZADAS--------------------------\n");
	printf("--------------------------------------------------------------------\n");
	mostrarTareasRealizadas(TareasRealizadas, n);
	
	printf("\n");
	printf("--------------------------------------------------------------------\n");
	printf("-------------------------TAREAS PENDIENTES--------------------------\n");
	printf("--------------------------------------------------------------------\n");
	mostrarTareasPendientes(TareasPendientes, n);
	
	printf("\n");
	printf("--------------------------------------------------------------------\n");
	printf("-------------------------BUSQUEDA DE TAREAS-------------------------\n");
	printf("--------------------------------------------------------------------\n");
	char clave[15];
	printf("\nIngrese una palabra clave: "); fflush(stdin); gets(clave);
	Tarea busqueda = buscarTarea(TareasPendientes, TareasRealizadas, n, clave);
	if(busqueda.tareaID == -1){
		printf("\nNo se encontraron tareas con esa palabra clave");
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

void cargarTareasPendientes(Tarea *TP, int n){
	int i, aux;
	for(i = 0; i < n; i++){
		TP->tareaID = i+1;
		printf("\nTarea #%d", i+1);
		
		char *desc = (char *) malloc(50 * sizeof(char));
		printf("\nIngrese una descripcion: "); fflush(stdin); gets(desc);
		TP->descripcion = desc; //???
		
		aux = 0;
		while(aux<10 || aux>100){
			printf("Duracion: "); fflush(stdin); scanf("%d", &aux);
		}
		TP->duracion = aux;
		
		TP++;
	}
}

void realizarTareas(Tarea *TP, Tarea *TR, int n){
	int i, aux;
	
	for(i = 0; i < n; i++){
		printf("\nTarea %d: ", TP->tareaID);
		printf("\nDescripcion: %s", TP->descripcion);
		printf("\nDuracion: %d dias", TP->duracion);
		printf("\nSe realizo esta tarea?\n");
		do{
			printf("(Ingrese un numero: 1 = si, 0 = no): "); scanf("%d",&aux);
		}while(aux<0 || aux>1);
		
		if(aux==1){
		//en vez de hacer que apunte a NULL, hago que apunte a un "indefinido" de tareaID
		//ya que no puede asignar un valor NULL a una estructura
			*TR = *TP;
			TP->tareaID = -1;
		}else{
			TR->tareaID = -1;
		}
		
		TP++; TR++;
	}
}

void mostrarTareasRealizadas(Tarea *TR, int n){
	int i;
	for(i = 0; i < n; i++){
		if(TR->tareaID != -1){
			mostrarTarea(*TR);
		}
		TR++;
	}
}

void mostrarTareasPendientes(Tarea *TP, int n){
	int i;
	for(i = 0; i < n; i++){
		if(TP->tareaID != -1){
			mostrarTarea(*TP);
		}
		TP++;
	}
}

void mostrarTarea(Tarea T){
	printf("\nTarea %d: ", T.tareaID);
	printf("\nDescripcion: %s", T.descripcion);
	printf("\nDuracion: %d dias", T.duracion);
	printf("\n");
}

Tarea buscarTarea(Tarea *TP, Tarea *TR, int n, char clave[]){
	int i;
	for(i = 0; i < n; i++){
		
		//el problema con esta funcion es que si la palabra clave esta contenida en otra
		//de todas formas la da por encontrada y retorna la Tarea que la posea
		
		if(TP->tareaID != -1){
			while(*(TP->descripcion) != '\0'){
				if(strstr(TP->descripcion, clave)){
		            return *TP;
		    	}
		    	(TP->descripcion)++;
			}
		}
		
		if(TR->tareaID != -1){
			while(*(TR->descripcion) != '\0'){
				if(strstr(TR->descripcion, clave)){
		            return *TR;
		    	}
		    	(TR->descripcion)++;
			}
		}
		
		TP++; TR++;
	}
	Tarea noEnc;
	noEnc.tareaID = -1;
	return noEnc;
}
