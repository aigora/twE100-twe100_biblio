// Trabajo de informatica grupo N-15
// Realizado por Daniel Rodriguez, Oscar Torija y Mihaita Smetan

// Librerias
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<stdbool.h>

// Estructura
typedef struct{
	char titulo[50];
	char nombreautor[50];
	char apellidoautor[50];
	char genero[50];
	int cantidad;
	int disponibles;
	int prestados;
	int eliminados;
}Libro;

// Lamada de funciones
void menu();
void leer_datos(Libro *biblioteca, int num, FILE *p_f);       
void pedir_datos(Libro *biblioteca, int num);
void eliminar_datos(Libro *biblioteca, int num);

// Funcion principal
int main()
{
	// Presentacion
	puts("Programa de prestamos y devoluciones de libros.");
	
	// Variables
	char opcion, n_archivo[20], comparadortitulo[50], comparadorautor[50], comparadorgenero[50];
	int i, j, z, k=0, N=0, y, orden, orden1, sumalibros, restalibros;
	Libro *biblioteca;
	FILE *p_archivo;
	
	// Desarrollo
	do{
		// Elegimos opcion del menu
		menu();
		scanf("%c", &opcion);
		fflush(stdin);
		switch(opcion){
			case'C': case'c':
				// Abrimos archivo que contiene lista de libros en modo lectura
				printf("\nIndique el nombre del archivo donde leer la lista de libros: ");
				gets(n_archivo);
				p_archivo = fopen(n_archivo, "r");				
				if (p_archivo == NULL){
					printf("\nNo se ha encontrado el archivo.");
				}else{				
					// Generamos el vector del tamaño adecuado, reservando memoria para la lista de libros
					fscanf(p_archivo, "%d", &N);
					printf("\nNumero de libros diferentes = %d\n", N);
					biblioteca = malloc(N*sizeof(Libro));
					
					// Leemos el archivo
					for(i=0; i<N; i++){
						leer_datos(biblioteca, i, p_archivo);
					} 
					
					// Mostramos los libros de la lista
					printf("\nLos libros disponibles:");
				
					for(i = 0; i < N; i++){
						printf("\n\n-Libro %d:", i + 1);
						printf("\n\tTitulo: %s", biblioteca[i].titulo);
						printf("\n\tNombre del autor: %s", biblioteca[i].nombreautor);
						printf("\n\tApellido del autor: %s", biblioteca[i].apellidoautor);
						printf("\n\tGenero: %s", biblioteca[i].genero);
						printf("\n\tNumero de libros totales: %i", biblioteca[i].cantidad);
						printf("\n\tNumero de libros disponibles: %i", biblioteca[i].disponibles);
						printf("\n\tNumero de libros prestados: %i\n", biblioteca[i].prestados);
					}
					
					// Cerramos archivo
					fclose(p_archivo);
					//free(biblioteca);
				}
			break;
			
			case'G': case'g':
				// Abrimos archivo donde vamos a guardar la lista de libros
				printf("\nIndique el nombre del archivo donde guardar la lista de libros: ");
				gets(n_archivo);
				p_archivo = fopen(n_archivo, "w");
				fprintf(p_archivo, "%d", N+k);
				
				// Guardamos la lista de libros en el archivo
				for(i = 0; i < N+k; i++){
					fprintf(p_archivo, "\n%s", biblioteca[i].titulo);
					fprintf(p_archivo, "\n%s", biblioteca[i].nombreautor);
					fprintf(p_archivo, "\n%s", biblioteca[i].apellidoautor);
					fprintf(p_archivo, "\n%s", biblioteca[i].genero);
					fprintf(p_archivo, "\n%i", biblioteca[i].cantidad);
					fprintf(p_archivo, "\n%i", biblioteca[i].disponibles);
					fprintf(p_archivo, "\n%i\n", biblioteca[i].prestados);
				}
				puts("\nArchivo guardado");
				
				// Cerramos archivo
				fclose(p_archivo);
				//free(biblioteca);
			break;

			case'A': case'a':
				do{
					// Pedimos titulo del libro a añadir y comparamos con los de la biblioteca
					printf("\nInserte el titulo del libro: ");
					gets(comparadortitulo);
					i=0;
					bool encontrado = false;
					while(i<N+k && encontrado == false){	
						orden = strcmp(comparadortitulo,biblioteca[i].titulo);
						if (orden == 0){
							encontrado = true;				
						}else i++;
					}
					
					if(encontrado){
						// Añadimos libros a la biblioteca
						printf("\nIndique la cantidad de libros a a%cadir: ", 164);
						scanf("%i", &sumalibros);
						fflush(stdin);
						biblioteca[i].cantidad += sumalibros;
						biblioteca[i].disponibles += sumalibros;
						
						// Mostramos los libros de la biblioteca
						for(i = 0; i < N+k; i++){
							printf("\n\n-Libro %d:", i + 1);
							printf("\n\tTitulo: %s", biblioteca[i].titulo);
							printf("\n\tNombre del autor: %s", biblioteca[i].nombreautor);
							printf("\n\tApellido del autor: %s", biblioteca[i].apellidoautor);
							printf("\n\tGenero: %s", biblioteca[i].genero);
							printf("\n\tNumero de libros totales: %i", biblioteca[i].cantidad);
							printf("\n\tNumero de libros disponibles: %i", biblioteca[i].disponibles);
							printf("\n\tNumero de libros prestados: %i", biblioteca[i].prestados);
						}
						puts("\nLibro guardado");
					}
					if(!encontrado){
						puts("\nNo se ha encontrado ningun libro con ese titulo.");
						printf("\n¿Desea a%cadirlo?\n", 164);
						puts("\n\tS - Si");
						puts("\tN - No\n");
						scanf("%c", &opcion);
						fflush(stdin);
						if(opcion == 's' || opcion == 'S'){
							// Añadimos libros a la biblioteca
							puts ("\nIntroduce los datos del libro");
							pedir_datos(biblioteca, i);
							fflush(stdin);						
							z=N;
							i = i + 1;
							k = i - z;
							
							// Mostamos los libros de la biblioteca
							for(i = 0; i < N+k; i++){
								printf("\n\n-Libro %d:", i + 1);
								printf("\n\tTitulo: %s", biblioteca[i].titulo);
								printf("\n\tNombre del autor: %s", biblioteca[i].nombreautor);
								printf("\n\tApellido del autor: %s", biblioteca[i].apellidoautor);
								printf("\n\tGenero: %s", biblioteca[i].genero);
								printf("\n\tNumero de libros totales: %i", biblioteca[i].cantidad);
								printf("\n\tNumero de libros disponibles: %i", biblioteca[i].disponibles);
								printf("\n\tNumero de libros prestados: %i", biblioteca[i].prestados);
							}
							puts("\nLibro guardado");
						}
					}
					
					// Preguntamos si desea añadir mas libros			
					printf("\n¿Desea a%cadir alguno mas?\n", 164);
					puts("\n\tS - Si");
					puts("\tN - No\n");
					scanf("%c", &opcion);
					fflush(stdin);
				}while(opcion == 's' || opcion == 'S');
			break;
	
			case'E': case'e':
				do{
					// Pedimos titulo del libro a eliminar y comparamos con los de la biblioteca
					printf("\nInserte el titulo del libro: ");
					gets(comparadortitulo);				
					i=0;
					bool encontrado = false;
					while(i<N+k && encontrado == false){	
						orden = strcmp(comparadortitulo,biblioteca[i].titulo);
						if (orden == 0){
							encontrado = true;				
						}else i++;
					}
					
					if(encontrado){
						// Eliminamos libros de la biblioteca
						printf("\nIndique la cantidad de libros a eliminar: ");
						scanf("%i", &restalibros);
						fflush(stdin);
						if(restalibros <= biblioteca[i].disponibles){
							biblioteca[i].cantidad -= restalibros;
							biblioteca[i].disponibles -= restalibros;
							biblioteca[i].eliminados += restalibros;
							if(biblioteca[i].cantidad == 0 && biblioteca[i].eliminados > 0){
								int num;
								for (num = i;  num < N+k-1; num++){
									eliminar_datos(biblioteca, num);
								}N+k--;
							}
							
							// Mostamos los libros de la biblioteca
							for(i = 0; i < N+k; i++){
								printf("\n\n-Libro %d:", i + 1);
								printf("\n\tTitulo: %s", biblioteca[i].titulo);
								printf("\n\tNombre del autor: %s", biblioteca[i].nombreautor);
								printf("\n\tApellido del autor: %s", biblioteca[i].apellidoautor);
								printf("\n\tGenero: %s", biblioteca[i].genero);
								printf("\n\tNumero de libros totales: %i", biblioteca[i].cantidad);
								printf("\n\tNumero de libros disponibles: %i", biblioteca[i].disponibles);
								printf("\n\tNumero de libros prestados: %i", biblioteca[i].prestados);						
								printf("\n\tNumero de libros eliminados: %i", biblioteca[i].eliminados);
							}
							puts("\nLibro eliminado");
						}else printf("\nNo hay tantos libros disponibles");
					}
					
					if(!encontrado){
						puts ("\nNo se ha encontrado ningun libro con ese titulo.");
					}
					
					// Preguntamos si desea eliminar mas libros	
					printf("\n\n¿Desea eliminar alguno mas?\n");
					puts("\n\tS - Si");
					puts("\tN - No\n");
					scanf("%c", &opcion);
					fflush(stdin);
				}while(opcion == 's' || opcion == 'S');
			break;
			
			case'D': case'd':
				do{
					// Pedimos titulo del libro a devolver y comparamos con los de la biblioteca
					printf("\nInserte el titulo del libro: ");
					gets(comparadortitulo);				
					i=0;
					bool encontrado = false;
					while(i<N+k && encontrado == false){	
					orden = strcmp(comparadortitulo,biblioteca[i].titulo);
					if (orden == 0){
							encontrado = true;				
						}else i++;
					}
					
					if(encontrado && biblioteca[i].prestados > 0){
						// Devolvemos libros a la biblioteca
						biblioteca[i].disponibles ++;
						biblioteca[i].prestados --;
						
						// Mostamos los libros de la biblioteca
						for(i = 0; i < N+k; i++){
							printf("\n\n-Libro %d:", i + 1);
							printf("\n\tTitulo: %s", biblioteca[i].titulo);
							printf("\n\tNombre del autor: %s", biblioteca[i].nombreautor);
							printf("\n\tApellido del autor: %s", biblioteca[i].apellidoautor);
							printf("\n\tGenero: %s", biblioteca[i].genero);
							printf("\n\tNumero de libros totales: %i", biblioteca[i].cantidad);
							printf("\n\tNumero de libros disponibles: %i", biblioteca[i].disponibles);
							printf("\n\tNumero de libros prestados: %i", biblioteca[i].prestados);
						}
					}else puts ("\nNo hay libros prestados.");
					
					if(!encontrado){
						puts ("\nNo se ha encontrado ningun libro con ese titulo.");
					}
					
					// Preguntamos si desea devolver mas libros			
					printf("\n\n¿Desea devolver alguno mas?\n");
					puts("\n\tS - Si");
					puts("\tN - No\n");
					scanf("%c", &opcion);
					fflush(stdin);
				}while(opcion == 's' || opcion == 'S');
			break;
			
			case'P': case'p':
				do{
					// Pedimos titulo del libro a prestar y comparamos con los de la biblioteca
					printf("\nInserte el titulo del libro: ");
					gets(comparadortitulo);
					i=0;
					bool encontrado = false;
					while(i<N+k && encontrado == false){	
						orden = strcmp(comparadortitulo,biblioteca[i].titulo);
						if (orden == 0){
							encontrado = true;				
						}else i++;
					}
					
					if(encontrado && biblioteca[i].disponibles > 0){
						// Prestamos libros de la biblioteca
						biblioteca[i].disponibles --;
						biblioteca[i].prestados ++;
						
						// Mostamos los libros de la biblioteca
						for(i = 0; i < N+k; i++){
							printf("\n\n-Libro %d:", i + 1);
							printf("\n\tTitulo: %s", biblioteca[i].titulo);
							printf("\n\tNombre del autor: %s", biblioteca[i].nombreautor);
							printf("\n\tApellido del autor: %s", biblioteca[i].apellidoautor);
							printf("\n\tGenero: %s", biblioteca[i].genero);
							printf("\n\tNumero de libros totales: %i", biblioteca[i].cantidad);
							printf("\n\tNumero de libros disponibles: %i", biblioteca[i].disponibles);
							printf("\n\tNumero de libros prestados: %i", biblioteca[i].prestados);
						}
					}else puts ("\nNo hay libros disponibles.");
					
					if(!encontrado){
						puts ("\nNo se ha encontrado ningun libro con ese titulo.");
					}
					
					// Preguntamos si desea prestar mas libros	
					printf("\n\n¿Desea prestar alguno mas?\n");
					puts("\n\tS - Si");
					puts("\tN - No\n");
					scanf("%c", &opcion);
					fflush(stdin);
				}while(opcion == 's' || opcion == 'S');		
			break;
			
			case'V': case'v':
				do{
					// Pedimos nombre o apellido del autor y comparamos con los de la biblioteca
					printf("\nIndique un autor(nombre o apellido): ");
					gets(comparadorautor);
					int contador=0;
					for(i = 0; i < N+k; i++){
						orden = strcmp(biblioteca[i].nombreautor,comparadorautor);
						orden1 = strcmp(biblioteca[i].apellidoautor,comparadorautor);
						if (orden == 0 || orden1 == 0){
							contador ++;
							// Mostramos todos los libros del mismo autor
							printf("\n\n-Libro %d:", i + 1);
							printf("\n\tTitulo: %s", biblioteca[i].titulo);
							printf("\n\tNombre del autor: %s", biblioteca[i].nombreautor);
							printf("\n\tApellido del autor: %s", biblioteca[i].apellidoautor);
							printf("\n\tGenero: %s", biblioteca[i].genero);
							printf("\n\tNumero de libros totales: %i", biblioteca[i].cantidad);
							printf("\n\tNumero de libros disponibles: %i", biblioteca[i].disponibles);
							printf("\n\tNumero de libros prestados: %i\n", biblioteca[i].prestados);
						}
					}
					if (contador == 0){
						printf("\nNo hay ningun libro de ese autor");
					}
					
					// Preguntamos si desea mostrar alguna lista de libros por autor mas
					printf("\n\n¿Desea mostrar alguna lista libros por autor mas?\n");
					puts("\n\tS - Si");
					puts("\tN - No\n");
					scanf("%c", &opcion);
					fflush(stdin);
				}while(opcion == 's' || opcion == 'S');
			
			break;
			
			case'M': case'm':
				do{
					// Pedimos genero del libro y comparamos con los de la biblioteca
					printf("\nIndique un genero: ");
					gets(comparadorgenero);
					int contador=0;
					for(i = 0; i < N+k; i++){
						orden = strcmp(biblioteca[i].genero,comparadorgenero);
						if (orden == 0){
							contador ++;
							// Mostramos todos los libros del mismo genero
							printf("\n\n-Libro %d:", i + 1);
							printf("\n\tTitulo: %s", biblioteca[i].titulo);
							printf("\n\tNombre del autor: %s", biblioteca[i].nombreautor);
							printf("\n\tApellido del autor: %s", biblioteca[i].apellidoautor);
							printf("\n\tGenero: %s", biblioteca[i].genero);
							printf("\n\tNumero de libros totales: %i", biblioteca[i].cantidad);
							printf("\n\tNumero de libros disponibles: %i", biblioteca[i].disponibles);
							printf("\n\tNumero de libros prestados: %i\n", biblioteca[i].prestados);
						}
					}
					if (contador == 0){
						printf("\nNo hay ningun libro de ese genero");
					}
					
					// Preguntamos si desea mostrar alguna lista de libros por genero mas
					printf("\n\n¿Desea mostrar alguna lista libros por genero mas?\n");
					puts("\n\tS - Si");
					puts("\tN - No\n");
					scanf("%c", &opcion);
					fflush(stdin);
				}while(opcion == 's' || opcion == 'S');
			
			break;
			
			default:
				printf ("\n\tOpción incorrecta\n");
				continue;
		}
		
		// Preguntamos si desea hacer otra consulta
		puts ("\n¿Desea hacer otra consulta?\n");
		puts ("\tS - Si");
		puts ("\tN - No\n");
		scanf("%c", &opcion);
		fflush(stdin);
	}while(opcion != 'n' && opcion != 'N');
	
	// Preguntamos si desea salir del programa sin guadar la lista de libros en un archivo
	puts ("\n¿Estas seguro que desea salir sin guardar la lista de libros?\n");
	puts ("\tS - Si");
	puts ("\tN - No\n");
	scanf("%c", &opcion);
	fflush(stdin);
	if(opcion == 'n' || opcion == 'N'){
		// Abrimos archivo donde vamos a guardar la lista de libros
		printf("\nIndique el nombre del archivo donde guardar la lista de libros: ");
		gets(n_archivo);
		p_archivo = fopen(n_archivo, "w");
		fprintf(p_archivo, "%d", N+k);
		
		// Guardamos la lista de libros en el archivo
		for(i = 0; i < N+k; i++){
			fprintf(p_archivo, "\n%s", biblioteca[i].titulo);
			fprintf(p_archivo, "\n%s", biblioteca[i].nombreautor);
			fprintf(p_archivo, "\n%s", biblioteca[i].apellidoautor);
			fprintf(p_archivo, "\n%s", biblioteca[i].genero);
			fprintf(p_archivo, "\n%i", biblioteca[i].cantidad);
			fprintf(p_archivo, "\n%i", biblioteca[i].disponibles);
			fprintf(p_archivo, "\n%i\n", biblioteca[i].prestados);
		}
		puts("\nArchivo guardado");
		
		// Cerramos archivo
		fclose(p_archivo);
		//free(biblioteca);
	}else{
	// Abrimos archivo de seguridad donde vamos a guardar la lista de libros
	p_archivo = fopen("copiaseguridad", "w");
	fprintf(p_archivo, "%d", N+k);
		
		// Guardamos la lista de libros en el archivo
		for(i = 0; i < N+k; i++){
			fprintf(p_archivo, "\n%s", biblioteca[i].titulo);
			fprintf(p_archivo, "\n%s", biblioteca[i].nombreautor);
			fprintf(p_archivo, "\n%s", biblioteca[i].apellidoautor);
			fprintf(p_archivo, "\n%s", biblioteca[i].genero);
			fprintf(p_archivo, "\n%i", biblioteca[i].cantidad);
			fprintf(p_archivo, "\n%i", biblioteca[i].disponibles);
			fprintf(p_archivo, "\n%i\n", biblioteca[i].prestados);
		}
	
	// Cerramos archivo
	fclose(p_archivo);
	//free(biblioteca);
	}
	return 0;
}

// Funcion menu	
void menu(){
	printf("\nIndique una de estas opciones:\n\n");
	printf("\tC - Cargar lista libros.\n");
	printf("\tG - Guardar lista libros.\n");
	printf("\tA - A%cadir libro.\n", 164);
	printf("\tE - Eliminar libro.\n");
	printf("\tD - Devolver libro.\n");
	printf("\tP - Prestar libro.\n");		
	printf("\tV - Visualizar lista libros por autor.\n");
	printf("\tM - Mostrar lista libros por genero.\n\n");
}

// Funcion para leer datos de archivo
void leer_datos(Libro *biblioteca, int num, FILE *p_f){
	int basura;
	fscanf (p_f, "%d", &basura);
	fgets(biblioteca[num].titulo, 50, p_f);
	fgets(biblioteca[num].nombreautor, 50, p_f);
	fgets(biblioteca[num].apellidoautor, 50, p_f);
	fgets(biblioteca[num].genero, 50, p_f);
	fscanf(p_f, "%d", &biblioteca[num].cantidad);
	fscanf(p_f, "%d", &biblioteca[num].disponibles);
	fscanf(p_f, "%d", &biblioteca[num].prestados);	
	biblioteca[num].eliminados = 0;
	strtok(biblioteca[num].titulo, "\n");		
	strtok(biblioteca[num].nombreautor, "\n");
	strtok(biblioteca[num].apellidoautor, "\n");
	strtok(biblioteca[num].genero, "\n");
}

// Funcion para pedir datos al usuario
void pedir_datos(Libro *biblioteca, int num){
	printf("\nIndique el titulo: ");
	gets(biblioteca[num].titulo);
	printf("\nIndique el nombre del autor: ");
	gets(biblioteca[num].nombreautor);
	printf("\nIndique el apellido del autor: ");
	gets(biblioteca[num].apellidoautor);
	printf("\nIndique el genero: ");
	gets(biblioteca[num].genero);
	printf("\nIndique la cantidad de libros: ");
	scanf("%i", &biblioteca[num].cantidad);
	biblioteca[num].disponibles = biblioteca[num].cantidad;
	biblioteca[num].prestados = 0;
	biblioteca[num].eliminados = 0;
}

// Funcion para eliminar datos
void eliminar_datos(Libro *biblioteca, int num){
	biblioteca[num] = biblioteca[num+1];
}
