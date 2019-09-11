#include <stdio.h>
#include "heap.h"
#include <stdlib.h>
#include <string.h>
#define DATOS_INICIAL 10
#define CANTIDAD_INICIAL 0
#define POSICION_RAIZ 0
#define INDICE_REDIMENCION 2
#define PORCENTAJE_OCUPADO 20
struct heap{
    void** datos;
    size_t cantidad;
    size_t tamanio;
    cmp_func_t cmp;
};
/* *****************************************************************
 *                    AUXILIARES DEL HEAP
 * *****************************************************************/
void swap( void** estructura_A , void** estructura_B ){
    void* auxiliar = *estructura_A;
    *estructura_A = *estructura_B;
    *estructura_B = auxiliar ;
}

void downheap(void** arreglo, size_t tam, size_t pos, cmp_func_t cmp ){
    if(pos >= tam ) return ;
    size_t max = pos ; //que seria el padre.
    size_t izq = (2 * pos) + 1;
    size_t der = (2 * pos) + 2;

    if(izq < tam && cmp(arreglo[izq], arreglo[max]) > 0 ) max = izq ;
    if(der < tam && cmp(arreglo[der], arreglo[max]) > 0 ) max = der ;

    if(max != pos){
      swap(&arreglo[pos], &arreglo[max]);
      downheap( arreglo, tam, max ,cmp);
    }
}

void heapify(void** arreglo, size_t n, cmp_func_t cmp){
    for (size_t i = (n/2); i > 0 ; i--) {
        downheap( arreglo, n , i-1 , cmp );
    }
}

bool redimencionar_vector(heap_t* heap, size_t nuevo_tamanio){
    if (nuevo_tamanio < DATOS_INICIAL)
        nuevo_tamanio = DATOS_INICIAL;
    void* datos_nuevos = realloc(heap->datos, nuevo_tamanio * sizeof(void*));

    if(!datos_nuevos)
        return false;

    heap->datos = datos_nuevos;
    heap->tamanio = nuevo_tamanio;

    return true;
}
void upheap(void **arreglo, size_t pos, cmp_func_t cmp){
    if (pos == POSICION_RAIZ ) return ;

    size_t pos_padre = (pos-1)/2 ;

    if(cmp(arreglo[pos_padre], arreglo[pos]) < 0){
        swap(&arreglo[pos_padre], &arreglo[pos]);
        upheap(arreglo, pos_padre, cmp  );
    }
}
/* *****************************************************************
 *                    PRIMITIVAS DEL HEAP
 * *****************************************************************/
heap_t* heap_crear(cmp_func_t cmp){
    heap_t* heap = malloc(sizeof(heap_t));
    if (!heap) return NULL;

    heap->datos = malloc(DATOS_INICIAL * sizeof(void*));

    if(!heap->datos){
        free(heap);
        return NULL;
    }
    heap->cantidad = CANTIDAD_INICIAL;
    heap->tamanio = DATOS_INICIAL;
    heap->cmp = cmp ;

    return heap ;
}
heap_t *heap_crear_arr(void *arreglo[], size_t n, cmp_func_t cmp){
    heap_t* heap =heap_crear(cmp);
    if(!heap) return NULL;
    heap->cantidad = n;

    if (n > heap->tamanio){
        if(!redimencionar_vector(heap, n * INDICE_REDIMENCION)){
            free(heap);
            return NULL;
        }
    }

    for (size_t i = 0; i < n ; i++)
        heap->datos[i] = arreglo[i];

    heapify(heap->datos , n, cmp );  //aca ya me lo transforma en heap.
  return heap;
}

size_t heap_cantidad(const heap_t* heap){
    return heap->cantidad;
}

bool heap_esta_vacio(const heap_t *heap){
    return !heap->cantidad;
}
bool heap_encolar(heap_t *heap, void *elem){
    bool redimenciona = true ;
    if(heap->cantidad == heap->tamanio)
        redimenciona = redimencionar_vector( heap , heap->tamanio * INDICE_REDIMENCION);

    if(redimenciona){
        heap->datos[heap->cantidad] = elem ;
        heap->cantidad++;
        upheap(heap->datos , heap->cantidad-1 , heap->cmp );
    }
    return redimenciona;
}

void *heap_ver_max(const heap_t *heap){
  return (heap_esta_vacio(heap))? NULL : heap->datos[POSICION_RAIZ] ;
}

void *heap_desencolar(heap_t *heap){
    void* desencolado = NULL ;
    if(!heap_esta_vacio( heap ) ){
        swap(&(heap->datos[POSICION_RAIZ]), &(heap->datos[heap->cantidad - 1]) );

        desencolado = heap->datos[heap->cantidad-1];
        (heap->cantidad)--;
        downheap(heap->datos, heap_cantidad(heap), POSICION_RAIZ , heap->cmp );
    }
    if(((heap->cantidad *100)/heap->tamanio) < PORCENTAJE_OCUPADO )
        redimencionar_vector( heap , heap->tamanio / INDICE_REDIMENCION);
    return desencolado;
}
void heap_sort(void *elementos[], size_t cant, cmp_func_t cmp){
    heapify(elementos, cant, cmp);

    for (size_t i = 1 ; i <cant ; i++) {
        swap(&elementos[POSICION_RAIZ], &elementos[cant-i]);
        downheap(elementos, cant-i , POSICION_RAIZ , cmp);
    }
}

void heap_destruir(heap_t *heap, void destruir_elemento(void *e)){
    if(destruir_elemento){
        while(!heap_esta_vacio(heap)) {
            destruir_elemento(heap_desencolar(heap));
        }
    }
    free(heap->datos);
    free(heap);
}
