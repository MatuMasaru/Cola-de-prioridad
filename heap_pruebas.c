  #include "heap.h"
#include "testing.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>  // For ssize_t in Linux.


/* ******************************************************************
 *                        PRUEBAS UNITARIAS
 * *****************************************************************/

int comparacion(const void* a,const void* b ){
    return strcmp((char*)a , (char*)b );

}
int comparacion_num(const void* a,const void* b ){
    if (*(int*)a > *(int*)b)
        return 1;
    else if (*(int*)a < *(int*)b)
        return -1;
    return 0;
}

 void prueba_heap_crear_vacio(){
    printf("____prueba_Crear_heap_vacio________\n");
    heap_t* heap = heap_crear(comparacion);

    print_test("Prueba heap crear heap vacio", heap);
    print_test("Prueba heap la cantidad de elementos es 0", heap_cantidad(heap) == 0);
    print_test("Prueba heap esta vacio es true, no existe", heap_esta_vacio(heap));
    print_test("Prueba heap ver maximo devuelve NULL", heap_ver_max(heap)== NULL);
    print_test("Prueba heap desencolar devuelve NULL", heap_desencolar(heap)== NULL);
    print_test("Prueba heap ver maximo devuelve NULL", heap_ver_max(heap)== NULL);
    printf("____se destruyo el heap________\n" );
    heap_destruir( heap, NULL);
}

static void prueba_heap_encolar(){
    printf("_____PRUEBA HEAP ENCOLAR_______\n");
    char elem1 = '7';
    char elem2 = '4';
    char elem3 = '5';
    char elem4 = '9';
    char elem5 = '1';
    heap_t* heap = heap_crear(comparacion);
    print_test("Prueba heap crear heap vacio", heap_esta_vacio(heap));
    //encolare elem1
    print_test("heap encolar 7 true", heap_encolar(heap, &elem1));
    print_test("heap ver max es el mismo encolado", heap_ver_max(heap)== &elem1);
    //encolar elem2
    print_test("heap encolar 4 es true", heap_encolar(heap, &elem2));
    print_test("heap ver max es el 7 ", heap_ver_max(heap)== &elem1);
   //encolar elem3
    print_test("heap encolar 5 es true", heap_encolar(heap, &elem3));
    print_test("heap ver max sigue siendo el 7 ", heap_ver_max(heap)== &elem1);
    //encolar elem4
    print_test("heap encolar 9 es true", heap_encolar(heap, &elem4));
    print_test("heap ver max es el 4 ", heap_ver_max(heap)== &elem4);
   //encolar elem5
    print_test("heap encolar 1 es true", heap_encolar(heap, &elem5));
    print_test("heap ver max es el actual 9 ", heap_ver_max(heap)== &elem4);
    printf("____se destruyo el heap________\n" );
    heap_destruir( heap, NULL);


    heap =heap_crear(comparacion);
    printf("_____PRUEBA HEAP CON strings_______\n");
    char* elem6 = "matu";
    char* elem7 = "mate";
    char* elem8 = "matar";
    char* elem9 = "matan";
    char* elem10 = "martin";

    print_test("Prueba heap crear heap vacio", heap_esta_vacio(heap));
    //encolare elem6
    print_test("heap encolar 'matu' true", heap_encolar(heap, elem6));
    print_test("heap ver max es el mismo encolado", heap_ver_max(heap)== elem6);
    //encolar elem7
    print_test("heap encolar 'mate' es true", heap_encolar(heap, elem7));
    print_test("heap ver max es matu", heap_ver_max(heap)== elem6);
   //encolar elem8
    print_test("heap encolar 'matar' es true", heap_encolar(heap, elem8));
    print_test("heap ver max es 'matu' ", heap_ver_max(heap)== elem6);
    //encolar elem9
    print_test("heap encolar 'matan' es true", heap_encolar(heap, elem9));
    print_test("heap ver max es 'matu' ", heap_ver_max(heap)== elem6);
   //encolar elem5
    print_test("heap encolar martin es true", heap_encolar(heap, elem10));
    print_test("heap ver max es 'matu'", heap_ver_max(heap)== elem6);
    heap_destruir( heap, NULL);
}

static void prueba_heap_desencolar(){
  printf("____PRUEBA HEAP DESENCOLAR________\n" );
  heap_t* heap = heap_crear(comparacion);
  char* elem6 = "4"; // "matu";
  char* elem7 = "7"  ;//"mate";
  char* elem8 = "9"    ;  //"matar";
  char* elem9 =  "2"    ;//"matan";
  char* elem10 = "3"     ;//"martin";

  print_test("Prueba heap crear heap vacio", heap_esta_vacio(heap));
  //encolare elem6
  print_test("heap encolar '4 ' true", heap_encolar(heap, elem6));
  print_test("heap ver max es el mismo encolado", heap_ver_max(heap)== elem6);
  //encolar elem7
  print_test("heap encolar '7' es true", heap_encolar(heap, elem7));
  print_test("heap ver max es el nuevo encolado", heap_ver_max(heap)== elem7);
 //encolar elem8
  print_test("heap encolar '9' es true", heap_encolar(heap, elem8));
  print_test("heap ver max es 'matar' ", heap_ver_max(heap)== elem8);
  //encolar elem9
  print_test("heap encolar '2' es true", heap_encolar(heap, elem9));
  print_test("heap ver max es 'matan' ", heap_ver_max(heap)== elem8);
 //encolar elem5
  print_test("heap encolar '3' es true", heap_encolar(heap, elem10));
  print_test("heap ver max es 'martin'", heap_ver_max(heap)== elem8);
  printf("____desencolado________\n" );

  print_test("heap ver max es 'el 9'", heap_ver_max(heap)== elem8);
  print_test("heap desencolar es true", heap_desencolar(heap)== elem8);

  print_test("heap ver max es 'el 7'", heap_ver_max(heap)== elem7);
  print_test("heap desencolar es true", heap_desencolar(heap)== elem7);

  print_test("heap ver max es 'el 4'", heap_ver_max(heap)== elem6);
  print_test("heap desencolar es true", heap_desencolar(heap)== elem6);

  print_test("heap ver max es 'el 3'", heap_ver_max(heap)== elem10);
  print_test("heap desencolar es true", heap_desencolar(heap)== elem10);

  print_test("heap ver max es 'el 2'", heap_ver_max(heap)== elem9);
  print_test("heap desencolar es true", heap_desencolar(heap)== elem9);
  heap_destruir(heap,NULL);
}

static void prueba_heap_cat_aux(){
  printf("____PRUEBA HEAP DESENCOLAR varios________\n" );
  heap_t* heap = heap_crear(comparacion);
  char* elem6 = "1"; // "matu";
  char* elem7 = "2"  ;//"mate";
  char* elem8 = "3"    ;  //"matar";
  char* elem9 =  "4"    ;//"matan";
  char* elem10 = "3"     ;//"martin";
  char* elem11 = "2";
  char* elem12 = "1";

  print_test("Prueba heap crear heap vacio", heap_esta_vacio(heap));
  //encolare elem6
  print_test("heap encolar 'uno' true", heap_encolar(heap, elem6));
  print_test("heap ver max es el mismo encolado", !strcmp((char*)heap_ver_max(heap), elem6));
  print_test("Prueba heap desencolar es 'uno' ", heap_desencolar(heap));
  print_test("Prueba heap crear heap vacio", heap_esta_vacio(heap));
  print_test("Prueba heap cantidad es 0 ", !heap_cantidad(heap));

  //encolar elem7 y elem8
  print_test("heap encolar 'dos' es true", heap_encolar(heap, elem7));
  printf(" la cantidad es : %zu\n", heap_cantidad(heap) );
  print_test("heap encolar 'tres' es true", heap_encolar(heap, elem8));
  print_test("Prueba heap desencolar es 'tres' ", !strcmp((char*)heap_desencolar(heap), elem8));
  printf(" la cantidad es : %zu\n", heap_cantidad(heap) );
  print_test("Prueba heap la cantidad es 1 ", heap_cantidad(heap)== 1);
  print_test("heap ver max es el 'tres' encolado", !strcmp((char*)heap_ver_max(heap), elem7));

  //encolar 4
  print_test("heap encolar '4' es true", heap_encolar(heap, elem9));
  printf(" la cantidad es : %li\n", heap_cantidad(heap) );
  print_test("Prueba heap desencolar es '4' ", !strcmp((char*)heap_desencolar(heap), elem9));
  print_test("Prueba heap crear heap no esta vacio", !heap_esta_vacio(heap));
  print_test("Prueba heap la cantidad es 1 ", heap_cantidad(heap)== 1);
  print_test("heap encolar 'elem10' es true", heap_encolar(heap, elem10));

  print_test("heap ver max es el 'elem10' encolado", !strcmp((char*)heap_ver_max(heap), elem10));

  print_test("heap encolar 'elem11' es true", heap_encolar(heap, elem11));

  print_test("heap ver max es el 'elem10' encolado", !strcmp((char*)heap_ver_max(heap), elem10));
  print_test("heap encolar 'elem12' es true", heap_encolar(heap, elem12));

  print_test("heap ver max es el 'elem10' encolado", !strcmp((char*)heap_ver_max(heap), elem10));
//desencolar
  print_test("Prueba heap desencolar es 'elem10' ", !strcmp((char*)heap_desencolar(heap), elem10));
  //ver maximo es el elem11
  print_test("heap ver max es el 'elem11' encolado", !strcmp((char*)heap_ver_max(heap), elem11));

  print_test("Prueba heap desencolar es 'elem11' ", !strcmp((char*)heap_desencolar(heap), elem11));
  //ver maximo es el elem11
  printf(" la cantidad es : %li\n", heap_cantidad(heap) );
  print_test("heap ver max es el 'elem10' encolado", !strcmp((char*)heap_ver_max(heap), elem7));

  heap_destruir(heap,NULL);
}
static void prueba_crear_con_arreglo(){
  printf("____PRUEBA HEAP crear con arreglo____\n" );


  int elem6 = 15;
  int elem7 = 7 ;
  int elem8 = 22 ;
  int elem9 =  2 ;
  int elem10 = 33 ;
  int** arr = malloc( 5 * sizeof(int*));
   arr[0]= &elem6;
   arr[1]= &elem7;
   arr[2]= &elem8;
   arr[3]= &elem9;
   arr[4]= &elem10;
  size_t tope = 5 ;
  printf("el arreglo tiene 15,7,22,2,33  \n" );
  heap_t* heap = heap_crear_arr( (void**)arr , tope , comparacion_num);
  print_test("Prueba heap crear heap esta cargado", !heap_esta_vacio(heap));

  printf("AL DESENCOLAR DE DESENCOLA SIEMPRE EL MAXIMO :\n" );
  print_test("Prueba heap desencolar es '33' ", !comparacion_num((int*)heap_desencolar(heap), &elem10));
  print_test("Prueba heap desencolar es '22' ", !comparacion_num((int*)heap_desencolar(heap), &elem8));
  print_test("Prueba heap desencolar es '15' ", !comparacion_num((int*)heap_desencolar(heap), &elem6));
  print_test("Prueba heap desencolar es '7' ", !comparacion_num((int*)heap_desencolar(heap), &elem7));
  print_test("Prueba heap desencolar es '2' ", !comparacion_num((int*)heap_desencolar(heap), &elem9));

  free(arr);
  heap_destruir(heap,NULL);
}

char *substr(const char *str, size_t n){
    size_t largo_str = strlen(str);
    if(largo_str < n) n = largo_str;
    char* palabra = malloc(n+1);
    strncpy(palabra,str,n+1);
    palabra[n] = '\0';
    return palabra;
}

static void prueba_heap_destruir(){
    heap_t* heap = heap_crear(comparacion);

    char *clave1 = substr("perro" ,'\0');
    char *clave2 = substr("gato" ,'\0');
    char *clave3 = substr("matias" ,'\0');
    char *clave4 = substr("yimi" ,'\0');
    char *clave5 = substr("sebas" ,'\0');
    char *clave6 = substr("pi" ,'\0');
    char *clave7 = substr("villa" ,'\0');

    printf("___________________prueba_heap_reemplazar_ con_destruir________________\n");
    //Inserta 2 valores y luego los reemplaza (debe liberar lo que reemplaza)
    print_test("Prueba heap insertar clave1", heap_encolar(heap, clave1));
    print_test("Prueba heap insertar clave2", heap_encolar(heap, clave2));
    print_test("Prueba heap insertar clave3", heap_encolar(heap, clave3));
    print_test("Prueba heap insertar clave4", heap_encolar(heap, clave4));
    print_test("Prueba heap insertar clave5", heap_encolar(heap, clave5));
    print_test("Prueba heap insertar clave6", heap_encolar(heap, clave6));
    print_test("Prueba heap insertar clave7", heap_encolar(heap, clave7));
    print_test("Prueba heap la cantidad de elementos es 7", heap_cantidad(heap) == 7);

    //Se destruye el heap (se debe liberar lo que quedó dentro)
    heap_destruir(heap,free);
}

int comp(const void* vara, const void* varb){
    //if((char*)vara >  (char*) varb) return 1;
    //else if((char)vara <  (char) varb) return -1;
    return strcmp((char*)vara, (char*) varb);
}
void pruebas_heap_volumen(){
	printf("INICIO DE PRUEBAS DE VOLUMEN\n");

	int dimension = 1000;
	int vector[dimension];

	//Crea un vector con 1000 elementos
	for (int i = 0; i < dimension; i++){
		vector[i] = i;
	}

	heap_t* heap = heap_crear(comparacion_num);
	bool ok = true;

	//Enconlar 1000 elementos
	for (int i=0; i < dimension; i++){
		ok &= 	heap_encolar(heap, &vector[i]);
	}
	print_test("Se pudieron encolar todos los elementos", ok);

	ok = true;

	for (int i = 0;  i < dimension - 1; i++){
		ok &= heap_desencolar (heap) == &vector[dimension - i - 1] && heap_ver_max(heap) == &vector[dimension - i - 2];
	}

	ok &= heap_desencolar(heap) == &vector[0] && heap_ver_max(heap) == NULL;
	print_test("Se pudieron desencolar todos los elementos", ok);

	heap_destruir(heap,NULL);
}

static void prueba_heap_heapsort(){
    printf("__PRUEBA heapsort _______\n" );
    char* arr[10] = {"ab","man","manu","acb","tba","cbu","como","mate","mani","men " };
    printf("le mando un arreglo con los contenidos :\n" );
    for (size_t i = 0; i < 10; i++) {
        printf(" %s",  arr[i]);
    }
    printf("\n");
    heap_sort( (void**)arr, 10 ,comparacion );
     for (size_t j = 0; j <10; j++) {
        printf("%s \n", arr[j] );
     }

}

/* ******************************************************************
 *                        FUNCIÓN PRINCIPAL
 * *****************************************************************/


void pruebas_heap_alumno(){
    // Ejecuta todas las pruebas unitarias.
    prueba_heap_crear_vacio();
    prueba_heap_encolar();
    prueba_heap_desencolar();
    prueba_crear_con_arreglo();
    prueba_heap_destruir();
    prueba_heap_cat_aux();
    prueba_heap_heapsort();
    pruebas_heap_volumen();
}
