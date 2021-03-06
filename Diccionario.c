//Enunciado:
/*Diccionario - Laboratorio 5.
Estudiantes de diversos idiomas se encuentran haciendo una investigación, el la cual se requiere obtener
las palabras de un idioma en un formato de fácil visualización la ellos. Es por esto que le han solicitado a
usted que implemente esto mediante un programa. El formato requerido es una matriz en la cual cada
fila  representa una letra del alfabeto en las que se encontraran las palabras del diccionario en orden alfabetico.
Esto ayudará a los estudiantes a encontrar patrones dentro de grupos de palabras, por lo que se le solicita que
apartir de la matriz identifique lo siguiente:
   •Ordenar las letras del alfabeto según la cantidad de palabras que comienzan con esta de mayor a
      menor para cada idioma.
   •Indicar cuál es la letra con que comienzan más palabras, incluyendo ambos idiomas.
   •Identificar cuál es la terminación más común entre las palabras para cada idioma (Se considera
      como terminación las últimas 3 letras de la palabra, si la palabra tiene menos de 3 letras se toma
      toda la palabra como parte de la terminación)
   •Identificar palabras que tienen la misma raíz e indicar si estas palabras tienen o no el mismo significado
      en ambos idiomas (Se considera como raíz de una palabra las 4 primeras letras de esta, si la palabra tiene
      menos de 4 letras se toma toda la palabra como raiz)

Como los estudiantes saben que usted ha desarrollado un programa que permite realizar consultas de
forma sencilla sobre las palabras y su traducción,se le solicita trabajar sobre dicho proyecto, por lo que
la matriz debe generarse apartir de un árbol AVL.

Para este proyecto se deben crear 2 matrices (una para cada idioma). Las filas de estas se encuntran
conformadas por las letras del alfabeto y las columnas son las palabras. El largo de cada fila corresponde
con la cantidad de palabras que se hayan ingresado que inicien con dicha letra  (por lo que no todas las
filas tienen el mismo tamaño). En caso que ninguna palabra inicie con una letra, no debe crearse dicha fila.

El programa debe generar las matrices utilizando el árbol AVL del laboratorio 4 y permitiendo utilizar
todas las funcionalidades de dicho laboratorio. En caso de no presentar este proyecto sobre el laboratorio 4
de forma completa y funcional, no se revisará el laboratorio 5.
En caso de haber entregado el laboratorio 4 de forma incompleta, debe terminarlo para presentar el laboratorio 5.

El programa debe generar tres archivos de salida
Uno llamado “Patrones.out” en donde se entreguen los 4  datos solicitados separados por una línea de
30 asteriscos (“******************************”).
Dos archivos llamados Matriz<idioma>.out (uno por cada idioma), en donde debe entregarse la matriz de
dicho idioma.

/*Traductor - Laboratorio 4.
Las diferencias entre los distintos idiomas siempre han conllevado un sesgo en las comunicaciones de las
diferentes culturas. Las personas, ante este impedimento de no poder transmitir ideas de forma que se
comprendan fácilmente, intentan capacitarse para poder dominar otros idiomas. Este aprendizaje
muchas veces es complicado dado a la cantidad de lenguajes existentes, por lo que se da prioridad a los
idiomas más utilizados o más relevantes según el área de interés del individuo.
Al estar estudiando un nuevo idioma, es inevitable hacer comparaciones con los idiomas ya conocidos,
buscando patrones en la sintaxis y equivalencias entre las palabras. Pero debido a que esto implica un
arduo trabajo de memorización de vocabulario no siempre es simple. Es por esto que los traductores
suelen ser una herramienta de apoyo en estos puntos, entregando una traducción que las personas
pueden ver en un lenguaje conocido.
En este laboratorio se busca implementar un traductor entre dos idiomas.
Para esto se requiere la utilización de la estructura de datos árbol para agilizar la búsqueda de una traducción.
Se debe considerar que los nodos deben tener la siguiente información:
   •Palabra en español.
   •Palabra en otro idioma.
   •Significado de la palabra en español.
   •Puntero español a nodo izquierdo.
   •Puntero español a nodo derecho.
   •Puntero otro idioma a nodo izquierdo.
   •Puntero otro idioma a nodo derecho.
Donde los punteros indican los hijos de un cierto nodo, para este árbol en particular se requiere que los
nodos se encuentren ordenados alfabéticamente, los “Punteros español” indican cómo se encuentra ordenado el
árbol según las palabras en español, mientras que los “Punteros otro idioma” indican cómo se encuentra ordenado
el árbol en ese  idioma. Es decir, se debe implementar un único árbol, pero que será equivalente a dos árboles
ordenados alfabéticamente en sus respectivos idiomas.
Por ejemplo, al insertar en el árbol las palabras Azul/Blue, Rojo/Red y Verde/Green en ese orden, da como
resultado el árbol desde la perspectiva del español. (Imagenes de Ejemplo en el enunciado).

Para  este  laboratorio  se  requiere  que  implemente  un  programa  que  reciba  un  archivo  de  texto  llamado
“Diccionario.in” y que genere un árbol AVL a partir de este. El programa debe permitir:
Consultar por una palabra junto su idioma y entregar su traducción.
Consultar por el significado de una palabra.
Entregar la información de todo el árbol en orden alfabético en español o inglés
(según indique el usuario) en una archivo llamado “Palabras.out”. Entregando la siguiente información por cada nodo:
Palabra_en_español Palabra_en_Otro (Hijo_izquierdo_en_español, Hijo_derecho_en_español) –
(Hijo_izquierdo_en_Otro, Hijo_derecho_en_inglés)

Fecha de entrega: 26/11/2017 hasta las 23:30 hrs
*/
// Inicio de código de Laboratorio 4 - Traductor.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct AdelsonVelskiiLandis{
   char palabraEspanhol[51];
   char palabraOtro[51];
   char definicionEspanhol[501];
   struct AdelsonVelskiiLandis* hijoDerechoPalabraEspanhol;
   struct AdelsonVelskiiLandis* hijoIzquierdoPalabraEspanhol;
   struct AdelsonVelskiiLandis* hijoDerechoPalabraOtro;
   struct AdelsonVelskiiLandis* hijoIzquierdoPalabraOtro;
}AVL;

typedef struct verticeAdyacente{
   char palabra[51];
   struct verticeAdyacente *siguiente;
}VA;

typedef struct Vertice{
   int longitud;
   char letraInicial;
   VA *inicio;
   struct Vertice *siguiente;
}Vertice;

typedef struct listaAdyacencia{
   Vertice *inicio;
}LA;

//Declaración de variables globables.
AVL* raizEspanhol;
AVL* raizOtro;
LA listaAdyacencia;
char nombreUsuario[200];
char raizP1[5];
char raizP2[5];
char terminacionP1[4];
char terminacionP2[4];
int contadorEspanhol;
int contadorOtro;
int longitudLA;
int largoArbol;
int cantidadLetras;


void inicializarArbol(){
   raizEspanhol = NULL;
   raizOtro = NULL;
   largoArbol = 0;
   return;
}

/* Entrada: Se reciben tres palabras (cadenas de Strings).
   Salida:  Se retorna un elemento AVL (puntero).
   Resumen: Se crea un nodo generandole memoria y se le otorgan los valores recibidos por entradas a este nuevo nodo.
*/
AVL* crearElemento(char palabraEspanhol[], char palabraOtro[], char definicionEspanhol[]){
   AVL* elemento = (AVL*)malloc(sizeof(AVL));
   strcpy(elemento->palabraEspanhol, palabraEspanhol);
   strcpy(elemento->palabraOtro, palabraOtro);
   strcpy(elemento->definicionEspanhol, definicionEspanhol);
   elemento->hijoDerechoPalabraEspanhol = NULL;
   elemento->hijoIzquierdoPalabraEspanhol = NULL;
   elemento->hijoDerechoPalabraOtro = NULL;
   elemento->hijoIzquierdoPalabraOtro = NULL;
   return elemento;
}
/* Entrada: Se reciben dos palabras (cadenas de Strings).
   Salida:  Se retorna un número que indica qué palabra va primera alfabéticamente.
   Resumen: Se comparan las dos palabras con el fin de determinar cuál de las palabras comparadas va a la izquierda
            o derecha según corresponda.
*/
int compararPalabras(char P1[], char P2[]){
   int i;
   i = 0;
   if(P1 != NULL && P2 != NULL){
      while(P1[i] != '\0' && P2[i] != '\0' ) {
         if(P1[i] != P2[i]){
            if(P1[i] < P2[i]){
               return 1; //P1 va primero alfabéticamente (o mayor).
            }
            else{
               return -1; //P2 va primero alfabéticamente (o mayor).
            }
         }
         i++;
      }
      return -2; //Error.
   }
   return -3; //Error.
}

/* Entrada: Se recibe un elementoEspañol AVL (puntero).
   Salida:  Se retorna el hijo derecho del elemento AVL (puntero).
   Resumen: Se comprueba si el elemento es Nulo, es caso de serlo retona Nulo, en caso contrario retorna el hijo derecho
            del elemento.
*/
AVL* hijoDerechoPalabraEspanhol(AVL* elemento){
   if(elemento == NULL){
      return NULL;
   }
   return elemento->hijoDerechoPalabraEspanhol;
}

/* Entrada: Se recibe un elementoOtro AVL (puntero).
   Salida:  Se retorna el hijo derecho del elemento AVL (puntero).
   Resumen: Se comprueba si el elemento es Nulo, es caso de serlo retona Nulo, en caso contrario retorna el hijo derecho
            del elemento.
*/
AVL* hijoDerechoPalabraOtro(AVL* elemento){
   if(elemento == NULL){
      return NULL;
   }
   return elemento->hijoDerechoPalabraOtro;
}

/* Entrada: Se recibe un elementoEspañol AVL (puntero).
   Salida:  Se retorna el hijo izquierdo del elemento AVL (puntero).
   Resumen: Se comprueba si el elemento es Nulo, es caso de serlo retona Nulo, en caso contrario retorna el hijo izquierdo
            del elemento.
*/
AVL* hijoIzquierdoPalabraEspanhol(AVL* elemento){
   if(elemento == NULL){
      return NULL;
   }
   return elemento->hijoIzquierdoPalabraEspanhol;
}

/* Entrada: Se recibe un elementoOtro AVL (puntero).
   Salida:  Se retorna el hijo izquierdo del elemento AVL (puntero).
   Resumen: Se comprueba si el elemento es Nulo, es caso de serlo retona Nulo, en caso contrario retorna el hijo izquierdo
            del elemento.
*/
AVL* hijoIzquierdoPalabraOtro(AVL* elemento){
   if(elemento == NULL){
      return NULL;
   }
   return elemento->hijoIzquierdoPalabraOtro;
}

/* Entrada: Se recibe un elemento a rotar AVL (puntero).
   Salida:  Se retorna elemento AVL (puntero) que es una nueva raíz.
   Resumen: Se crea un nuevo puntero (nueva raíz) que apunte al hijo izquierdo del elemento a rotar, el puntero del hijo izquierdo
            del elemento a rotar se apunta al hijo derecho de la nueva raíz y finalmente el puntero del hijo derecho de la nueva
            raíz apunta al elemento a rotar.
*/
AVL* rotarDerechaEspanhol(AVL* elementoRotar){
   AVL* nuevaRaiz = hijoIzquierdoPalabraEspanhol(elementoRotar);
   elementoRotar->hijoIzquierdoPalabraEspanhol = hijoDerechoPalabraEspanhol(nuevaRaiz);
   nuevaRaiz->hijoDerechoPalabraEspanhol = elementoRotar;
   return nuevaRaiz;
}

/* Entrada: Se recibe un elemento a rotar AVL (puntero).
   Salida:  Se retorna elemento AVL (puntero) que es una nueva raíz.
   Resumen: Se crea un nuevo puntero (nueva raíz) que apunte al hijo derecho del elemento a rotar, el puntero del hijo derecho
            del elemento a rotar se apunta al hijo izquierdo de la nueva raíz y finalmente el puntero del hijo izquierdo de la nueva
            raíz apunta al elemento a rotar.
*/
AVL* rotarIzquierdaEspanhol(AVL* elementoRotar){
   AVL* nuevaRaiz = hijoDerechoPalabraEspanhol(elementoRotar);
   elementoRotar->hijoDerechoPalabraEspanhol = hijoIzquierdoPalabraEspanhol(nuevaRaiz);
   nuevaRaiz->hijoIzquierdoPalabraEspanhol = elementoRotar;
   return nuevaRaiz;
}

/* Entrada: Se recibe un elemento a rotar AVL (puntero).
   Salida:  Se retorna elemento AVL (puntero) que es una nueva raíz.
   Resumen: Se crea un nuevo puntero (nueva raíz) que apunte al hijo izquierdo del elemento a rotar, el puntero del hijo izquierdo
            del elemento a rotar se apunta al hijo derecho de la nueva raíz y finalmente el puntero del hijo derecho de la nueva
            raíz apunta al elemento a rotar.
*/
AVL* rotarDerechaOtro(AVL* elementoRotar){
   AVL* nuevaRaiz = hijoIzquierdoPalabraOtro(elementoRotar);
   elementoRotar->hijoIzquierdoPalabraOtro = hijoDerechoPalabraOtro(nuevaRaiz);
   nuevaRaiz->hijoDerechoPalabraOtro = elementoRotar;
   return nuevaRaiz;
}

/* Entrada: Se recibe un elemento a rotar AVL (puntero).
   Salida:  Se retorna elemento AVL (puntero) que es una nueva raíz.
   Resumen: Se crea un nuevo puntero (nueva raíz) que apunte al hijo derecho del elemento a rotar, el puntero del hijo derecho
            del elemento a rotar se apunta al hijo izquierdo de la nueva raíz y finalmente el puntero del hijo izquierdo de la nueva
            raíz apunta al elemento a rotar.
*/
AVL* rotarIzquierdaOtro(AVL* elementoRotar){
   AVL* nuevaRaiz = hijoDerechoPalabraOtro(elementoRotar);
   elementoRotar->hijoDerechoPalabraOtro = hijoIzquierdoPalabraOtro(nuevaRaiz);
   nuevaRaiz->hijoIzquierdoPalabraOtro = elementoRotar;
   return nuevaRaiz;
}

/* Entrada: Se recibe un elemento AVL (puntero).
   Salida:  Se devuelve un número entero identificando la altura del elemento AVL.
   Resumen: Si el elemento es Nulo se retorna 0 indicando que la altura del elemento es 0, si el elemento no tiene hijos se
            retorna 1 indicando que la altura del elemento es 1, si no es ninguno de los casos anteriores se calculan
            la altura de los nodos hijos del elemento en cuestión y se retorna 1 más la altura de uno de los hijos nodos
            dependiendo de cuál de estos es mayor.
*/
int alturaElementoEspanhol(AVL* elemento){
   int alturaDerecha, alturaIzquierda;
   if(elemento == NULL){
      return 0;
   }
   if(hijoDerechoPalabraEspanhol(elemento) == NULL && hijoIzquierdoPalabraEspanhol(elemento) == NULL){
      return 1;
   }
   alturaDerecha = alturaElementoEspanhol(hijoDerechoPalabraEspanhol(elemento));
   alturaIzquierda = alturaElementoEspanhol(hijoIzquierdoPalabraEspanhol(elemento));
   if(alturaIzquierda > alturaDerecha){
      return 1 + alturaIzquierda;
   }
   return 1 + alturaDerecha;
}

/* Entrada: Se recibe un elemento AVL (puntero).
   Salida:  Se devuelve un número entero identificando la altura del elemento AVL.
   Resumen: Si el elemento es Nulo se retorna 0 indicando que la altura del elemento es 0, si el elemento no tiene hijos se
            retorna 1 indicando que la altura del elemento es 1, si no es ninguno de los casos anteriores se calculan
            la altura de los nodos hijos del elemento en cuestión y se retorna 1 más la altura de uno de los hijos nodos
            dependiendo de cuál de estos es mayor.
*/
int alturaElementoOtro(AVL* elemento){
   int alturaDerecha, alturaIzquierda;
   if(elemento == NULL){
      return 0;
   }
   if(hijoDerechoPalabraOtro(elemento) == NULL && hijoIzquierdoPalabraOtro(elemento) == NULL){
      return 1;
   }
   alturaDerecha = alturaElementoOtro(hijoDerechoPalabraOtro(elemento));
   alturaIzquierda = alturaElementoOtro(hijoIzquierdoPalabraOtro(elemento));
   if(alturaIzquierda > alturaDerecha){
      return 1 + alturaIzquierda;
   }
   return 1 + alturaDerecha;
}

/* Entrada: Se recibe un elemento AVL (puntero).
   Salida:  Se devuelve un número entero identificando la altura del elemento AVL.
   Resumen: Se realiza la resta entre las alturas de los hijos del elemento en cuestión.
*/
int diferenciaAlturasEspanhol(AVL* elemento){
   return alturaElementoEspanhol(hijoIzquierdoPalabraEspanhol(elemento)) - alturaElementoEspanhol(hijoDerechoPalabraEspanhol(elemento));
}

/* Entrada: Se recibe un elemento AVL (puntero).
   Salida:  Se devuelve un número entero identificando la altura del elemento AVL.
   Resumen: Se realiza la resta entre las alturas de los hijos del elemento en cuestión.
*/
int diferenciaAlturasOtro(AVL* elemento){
   return alturaElementoOtro(hijoIzquierdoPalabraOtro(elemento)) - alturaElementoOtro(hijoDerechoPalabraOtro(elemento));
}

/* Entrada: Se recibe un elemento a equilibrar AVL (puntero).
   Salida:  Se devuelve el elemento a equilibrar AVL (puntero) con su respectiva rama equilibrada.
   Resumen: Se identifica, según la altura del elemento, si es necesario realizar rotaciones ya sea dobles o simples
            y se realizan según corresponda.
*/
AVL* equilibrarRamaEspanhol(AVL* elementoEquilibrar){
   int diferenciaEspanhol;
   diferenciaEspanhol = diferenciaAlturasEspanhol(elementoEquilibrar);
   if(diferenciaEspanhol == 2){
      if(diferenciaAlturasEspanhol(hijoIzquierdoPalabraEspanhol(elementoEquilibrar)) < 0){
         elementoEquilibrar->hijoIzquierdoPalabraEspanhol = rotarIzquierdaEspanhol(hijoIzquierdoPalabraEspanhol(elementoEquilibrar));
      }
      return rotarDerechaEspanhol(elementoEquilibrar);
   }
   if(diferenciaEspanhol == -2){
      if(diferenciaAlturasEspanhol(hijoDerechoPalabraEspanhol(elementoEquilibrar)) > 0){
         elementoEquilibrar->hijoDerechoPalabraEspanhol = rotarDerechaEspanhol(hijoDerechoPalabraEspanhol(elementoEquilibrar));
      }

      return rotarIzquierdaEspanhol(elementoEquilibrar);
   }
   return elementoEquilibrar;
}

/* Entrada: Se recibe un elemento a equilibrar AVL (puntero).
   Salida:  Se devuelve el elemento a equilibrar AVL (puntero) con su respectiva rama equilibrada.
   Resumen: Se identifica, según la altura del elemento, si es necesario realizar rotaciones ya sea dobles o simples
            y se realizan según corresponda.
*/
AVL* equilibrarRamaOtro(AVL* elementoEquilibrar){
   int diferenciaOtro;
   diferenciaOtro = diferenciaAlturasOtro(elementoEquilibrar);
   if(diferenciaOtro == 2){
      if(diferenciaAlturasOtro(hijoIzquierdoPalabraOtro(elementoEquilibrar)) < 0){
         elementoEquilibrar->hijoIzquierdoPalabraOtro = rotarIzquierdaOtro(hijoIzquierdoPalabraOtro(elementoEquilibrar));
      }
      return rotarDerechaOtro(elementoEquilibrar);
   }
   if(diferenciaOtro == -2){
      if(diferenciaAlturasOtro(hijoDerechoPalabraOtro(elementoEquilibrar)) > 0){
         elementoEquilibrar->hijoDerechoPalabraOtro = rotarDerechaOtro(hijoDerechoPalabraOtro(elementoEquilibrar));
      }
      return rotarIzquierdaOtro(elementoEquilibrar);
   }
   return elementoEquilibrar;
}

/* Entrada: Se recibe dos elementos AVL (punteros), el nuevo elemento a agregar y la raíz del árbol.
   Salida:  Se devuelve la raíz del árbol equilibrandole en el proceso.
   Resumen: Se recorre el árbol avanzando según corresponda entre los punteros con el fin de mantener el árbol como un ABO,
            una vez se llega un nodo hoja se apunta a la derecha o izquierda según corresponda y se añade el nuevo elemento.
*/
AVL* agregarElementoEspanhol(AVL* nuevoElemento ,AVL** raizEspanhol) {
   int comparacionEspanhol;
   AVL* elementoActualEspanhol = *raizEspanhol;
   AVL* elementoAnteriorEspanhol = *raizEspanhol; //Auxiliar siempre irá en la posición anterior de actual.
   while(elementoActualEspanhol != NULL){ //Avanzará hasta que elementoActual apunte a NULL.
      comparacionEspanhol = compararPalabras(nuevoElemento->palabraEspanhol, elementoActualEspanhol->palabraEspanhol);
      elementoAnteriorEspanhol = elementoActualEspanhol; //lo que dejará a elementoAuxiliar en la posición anterior.
      if(comparacionEspanhol == 1){
         elementoActualEspanhol = elementoActualEspanhol->hijoIzquierdoPalabraEspanhol;
      }
      else{
         elementoActualEspanhol = elementoActualEspanhol->hijoDerechoPalabraEspanhol;
      }
   }
   if(comparacionEspanhol == 1){
      elementoAnteriorEspanhol->hijoIzquierdoPalabraEspanhol = nuevoElemento;
      largoArbol++;
   }
   else{
      elementoAnteriorEspanhol->hijoDerechoPalabraEspanhol = nuevoElemento;
      largoArbol++;
   }
   return equilibrarRamaEspanhol(*raizEspanhol);
}

/* Entrada: Se recibe dos elementos AVL (punteros), el nuevo elemento a agregar y la raíz del árbol.
   Salida:  Se devuelve la raíz del árbol equilibrandole en el proceso.
   Resumen: Se recorre el árbol avanzando según corresponda entre los punteros con el fin de mantener el árbol como un ABO,
            una vez se llega un nodo hoja se apunta a la derecha o izquierda según corresponda y se añade el nuevo elemento.
*/
AVL* agregarElementoOtro(AVL* nuevoElemento ,AVL** raizOtro){
   int comparacionOtro;
   AVL* elementoActualOtro = *raizOtro;
   AVL* elementoAnteriorOtro = *raizOtro; //Auxiliar siempre irá en la posición anterior de actual.
   while(elementoActualOtro != NULL){ //Avanzará hasta que elementoActual apunte a NULL,
      comparacionOtro = compararPalabras(nuevoElemento->palabraOtro, elementoActualOtro->palabraOtro);
      elementoAnteriorOtro = elementoActualOtro; //lo que dejará a elementoAuxiliar en la posición anterior,
      if(comparacionOtro == 1){
         elementoActualOtro = elementoActualOtro->hijoIzquierdoPalabraOtro;
      }
      else{
         elementoActualOtro = elementoActualOtro->hijoDerechoPalabraOtro;
      }
   }
   if(comparacionOtro == 1){
      elementoAnteriorOtro->hijoIzquierdoPalabraOtro = nuevoElemento;
   }
   else{
      elementoAnteriorOtro->hijoDerechoPalabraOtro = nuevoElemento;
   }
   return equilibrarRamaOtro(*raizOtro);
}

/* Entrada: Se recibe tres elementos AVL (punteros), el nuevo elemento a agregar y la raíces del árbol.
   Salida:  Al ser una función void, no posee retorno.
   Resumen: Se comprueba si la raíz de Español apunta a Nulo, si es así el nuevo elemento es el primer elementoOtro
            por lo que las dos raíces del árbol apuntan al nuevo elemento y se registra el largo del árbol igual a 1,
            en caso de no apuntar a Nulo se añade el elemento según corresponda con las funciones respectivas a su idioma.
*/
void agregarElemento(AVL* nuevoElemento ,AVL** raizEspanhol, AVL** raizOtro){
   if(*raizEspanhol == NULL){ //En caso de ya estár inicializada con un primer nodo
 		*raizEspanhol = nuevoElemento;
      *raizOtro = nuevoElemento;
      largoArbol = 1;
 		return;
 	}
   *raizEspanhol = agregarElementoEspanhol(nuevoElemento, raizEspanhol);
   *raizOtro = agregarElementoOtro(nuevoElemento, raizOtro);
   return;
}

/* Entrada: Se recibe un elemento AVL (puntero) y un elemento FILE (archivo).
   Salida:  Al ser una función void, no posee retorno.
   Resumen: Se recorre recursivamente el árbol e imprime en el archivo el árbol en preorden.
*/
void imprimirArbol_PreordenEspanhol(AVL** raizEspanhol, FILE* escribirArchivo){
   if(*raizEspanhol != NULL){
      fprintf(escribirArchivo,"[ %s ]", (*raizEspanhol)->palabraEspanhol);
      if((*raizEspanhol)->hijoIzquierdoPalabraEspanhol != NULL){
         imprimirArbol_PreordenEspanhol(&((*raizEspanhol)->hijoIzquierdoPalabraEspanhol), escribirArchivo);
      }
      if((*raizEspanhol)->hijoDerechoPalabraEspanhol != NULL){
         imprimirArbol_PreordenEspanhol(&((*raizEspanhol)->hijoDerechoPalabraEspanhol), escribirArchivo);
      }
   }
}

/* Entrada: Se recibe un elemento AVL (puntero) y un elemento FILE (archivo).
   Salida:  Al ser una función void, no posee retorno.
   Resumen: Se recorre recursivamente el árbol e imprime en el archivo el árbol en preorden.
*/
void imprimirArbol_PreordenOtro(AVL** raizOtro, FILE* escribirArchivo){
   if(*raizOtro != NULL){
      fprintf(escribirArchivo,"[ %s ]", (*raizOtro)->palabraOtro);
      if((*raizOtro)->hijoIzquierdoPalabraOtro != NULL){
         imprimirArbol_PreordenOtro(&((*raizOtro)->hijoIzquierdoPalabraOtro), escribirArchivo);
      }
      if((*raizOtro)->hijoDerechoPalabraOtro != NULL){
         imprimirArbol_PreordenOtro(&((*raizOtro)->hijoDerechoPalabraOtro), escribirArchivo);
      }
   }
}

/* Entrada: Se recibe un elemento AVL (puntero) y un elemento FILE (archivo).
   Salida:  Al ser una función void, no posee retorno.
   Resumen: Se escribe en el archivo los indicadores de qué parte del árbol se muestra a continuación
            y se llama a las funciones que imprimen en el idioma correspondiente.
*/
void imprimirArbol_Preorden(AVL** raizEspanhol, AVL** raizOtro, FILE* escribirArchivo){
   fprintf(escribirArchivo,"\nLas palabras en Español en preorden son: ");
   imprimirArbol_PreordenEspanhol(raizEspanhol, escribirArchivo);
   fprintf(escribirArchivo,"\nLas palabras en Español en Otro son: ");
   imprimirArbol_PreordenOtro(raizOtro, escribirArchivo);
   fprintf(escribirArchivo,"\n");
   return;
}

/* Entrada: Se recibe un elemento AVL (puntero) y un elemento FILE (archivo).
   Salida:  Al ser una función void, no posee retorno.
   Resumen: Se recorre recursivamente el árbol e imprime en el archivo el árbol en inorden.
*/
void imprimirArbol_InordenEspanhol(AVL** raizEspanhol, FILE* escribirArchivo){
   if(*raizEspanhol != NULL){
      if((*raizEspanhol)->hijoIzquierdoPalabraEspanhol != NULL){
         imprimirArbol_InordenEspanhol(&((*raizEspanhol)->hijoIzquierdoPalabraEspanhol), escribirArchivo);
      }
      fprintf(escribirArchivo,"[ %s ]", (*raizEspanhol)->palabraEspanhol);
      if((*raizEspanhol)->hijoDerechoPalabraEspanhol != NULL){
         imprimirArbol_InordenEspanhol(&((*raizEspanhol)->hijoDerechoPalabraEspanhol), escribirArchivo);
      }
   }
}

/* Entrada: Se recibe un elemento AVL (puntero) y un elemento FILE (archivo).
   Salida:  Al ser una función void, no posee retorno.
   Resumen: Se recorre recursivamente el árbol e imprime en el archivo el árbol en inorden.
*/
void imprimirArbol_InordenOtro(AVL** raizOtro, FILE* escribirArchivo){
   if(*raizOtro != NULL){
      if((*raizOtro)->hijoIzquierdoPalabraOtro != NULL){
         imprimirArbol_InordenOtro(&((*raizOtro)->hijoIzquierdoPalabraOtro), escribirArchivo);
      }
      fprintf(escribirArchivo,"[ %s ]", (*raizOtro)->palabraOtro);
      if((*raizOtro)->hijoDerechoPalabraOtro != NULL){
         imprimirArbol_InordenOtro(&((*raizOtro)->hijoDerechoPalabraOtro), escribirArchivo);
      }
   }
}

/* Entrada: Se recibe un elemento AVL (puntero) y un elemento FILE (archivo).
   Salida:  Al ser una función void, no posee retorno.
   Resumen: Se escribe en el archivo los indicadores de qué parte del árbol se muestra a continuación
            y se llama a las funciones que imprimen en el idioma correspondiente.
*/
void imprimirArbol_Inorden(AVL** raizEspanhol, AVL** raizOtro, FILE* escribirArchivo){
   fprintf(escribirArchivo,"\nLas palabras en Español en inorden son: ");
   imprimirArbol_InordenEspanhol(raizEspanhol, escribirArchivo);
   fprintf(escribirArchivo,"\nLas palabras en Otro en inorden son: ");
   imprimirArbol_InordenOtro(raizOtro, escribirArchivo);
   fprintf(escribirArchivo,"\n");
   return;
}

/* Entrada: Se recibe un elemento AVL (puntero) y un elemento FILE (archivo).
   Salida:  Al ser una función void, no posee retorno.
   Resumen: Se recorre recursivamente el árbol e imprime en el archivo el árbol en postorden.
*/
void imprimirArbol_PostordenEspanhol(AVL** raizEspanhol, FILE* escribirArchivo){
   if(*raizEspanhol != NULL){
      if((*raizEspanhol)->hijoIzquierdoPalabraEspanhol != NULL){
         imprimirArbol_PostordenEspanhol(&((*raizEspanhol)->hijoIzquierdoPalabraEspanhol), escribirArchivo);
      }
      if((*raizEspanhol)->hijoDerechoPalabraEspanhol != NULL){
         imprimirArbol_PostordenEspanhol(&((*raizEspanhol)->hijoDerechoPalabraEspanhol), escribirArchivo);
      }
      fprintf(escribirArchivo,"[ %s ]", (*raizEspanhol)->palabraEspanhol);
   }
}

/* Entrada: Se recibe un elemento AVL (puntero) y un elemento FILE (archivo).
   Salida:  Al ser una función void, no posee retorno.
   Resumen: Se recorre recursivamente el árbol e imprime en el archivo el árbol en postorden.
*/
void imprimirArbol_PostordenOtro(AVL** raizOtro, FILE* escribirArchivo){
   if(*raizOtro != NULL){
      if((*raizOtro)->hijoIzquierdoPalabraOtro != NULL){
         imprimirArbol_PostordenOtro(&((*raizOtro)->hijoIzquierdoPalabraOtro), escribirArchivo);
      }
      if((*raizOtro)->hijoDerechoPalabraOtro != NULL){
         imprimirArbol_PostordenOtro(&((*raizOtro)->hijoDerechoPalabraOtro), escribirArchivo);
      }
      fprintf(escribirArchivo,"[ %s ]", (*raizOtro)->palabraOtro);
   }
}

/* Entrada: Se recibe un elemento AVL (puntero) y un elemento FILE (archivo).
   Salida:  Al ser una función void, no posee retorno.
   Resumen: Se escribe en el archivo los indicadores de qué parte del árbol se muestra a continuación
            y se llama a las funciones que imprimen en el idioma correspondiente.
*/
void imprimirArbol_Postorden(AVL** raizEspanhol, AVL** raizOtro, FILE* escribirArchivo) {
   fprintf(escribirArchivo,"\nLas palabras en Español en postorden son: ");
   imprimirArbol_PostordenEspanhol(raizEspanhol, escribirArchivo);
   fprintf(escribirArchivo,"\nLas palabras en Otro en postorden son: ");
   imprimirArbol_PostordenOtro(raizOtro, escribirArchivo);
   fprintf(escribirArchivo,"\n");
   return;
}

/* Entrada: Se reciben dos palabras (cadenas de Strings).
   Salida:  Se retorna un número que indica si las palabras son iguales o no y cuál va primera alfabéticamente.
   Resumen: Se comparan las dos palabras con el fin de determinar cuál de las palabras comparadas va a la izquierda
            o derecha según corresponda y a diferencia de la función compararPalabras, también se identifica si las
            palabras son iguales.
*/
int comparacionCompleta(char P1[], char P2[]){
   int i;
   i = 0;
   if(P1 != NULL && P2 != NULL){
        while(P1[i] != '\0' && P2[i] != '\0' ) {
            if(P1[i] != P2[i]){
                if(P1[i] < P2[i]){
                    return 1; //P1 va primero alfabéticamente (o mayor).
                }
                if(P1[i] > P2[i]){
                    return -1; //P2 va primero alfabéticamente (o mayor).
                }
            }
            i++;
        }
        return 0; //Las palabras son iguales.
    }
    return -2;
}

/* Entrada: Se recibe una palabra (cadenas de Strings) y dos elemetos AVL (punteros) que son las raíces del árbol.
   Salida:  Se devulve el elemento AVL buscado.
   Resumen: Se recorre el árbol buscando en cada nodo una coincidencia con la palabra buscada, utilizando la facilidad
            que entrega el hecho de que sea un árbol AVL.
*/
AVL* buscarElemento(char palabraObjetivo[], AVL** raizEspanhol, AVL** raizOtro){
   if(comparacionCompleta((*raizEspanhol)->palabraEspanhol, palabraObjetivo) == 0){
      return (*raizEspanhol);
   }
   if(comparacionCompleta((*raizOtro)->palabraOtro, palabraObjetivo) == 0){
      return (*raizOtro);
   }
   else{
      //Buscar en palabras en español.
      AVL* elementoActualEspanhol = *raizEspanhol;
      if(elementoActualEspanhol->palabraEspanhol != NULL){
          while(comparacionCompleta(elementoActualEspanhol->palabraEspanhol, palabraObjetivo) != 0 && elementoActualEspanhol != NULL){
              if(compararPalabras(palabraObjetivo, elementoActualEspanhol->palabraEspanhol) == 1){
                  elementoActualEspanhol = elementoActualEspanhol->hijoIzquierdoPalabraEspanhol;
              }
              else{
                  elementoActualEspanhol = elementoActualEspanhol->hijoDerechoPalabraEspanhol;
              }
          }
      }
      if(elementoActualEspanhol == NULL){
         //Buscar en palabras en inglés. Si se ha rotado es posible que no funcione.
         AVL* elementoActualOtro = *raizOtro;
         if(elementoActualOtro->palabraOtro != NULL){
             while(comparacionCompleta(elementoActualOtro->palabraOtro, palabraObjetivo) != 0 && elementoActualOtro != NULL){
                 if(compararPalabras(palabraObjetivo, elementoActualOtro->palabraOtro) == 1){
                     elementoActualOtro = elementoActualOtro->hijoIzquierdoPalabraOtro;
                 }
                 else{
                     elementoActualOtro = elementoActualOtro->hijoDerechoPalabraOtro;
                 }
             }
         }
         if(elementoActualOtro == NULL){
            printf("No se encuentra la palabra buscada\n");
         }
         else{
            return elementoActualOtro;
         }
      }
      else{
         return elementoActualEspanhol;
      }
   }
}

/* Entrada: No posee entradas.
   Salida:  Al ser una función void, no posee retorno.
   Resumen: Se realiza la lectura del archivo leyendo por línea dos palabras (una Español y la otra en Otro) y la definición de la palabra,
            además, se cada vez que se lee una línea se crea un elemento y se añade el elemento a el árbol, una vez se termina de
            leer el archivo de texto, este se cierra.
*/
void leerArchivo(){
    char palabraEspanhol[51], palabraOtro[51], definicionEspanhol[501];
    FILE *archivoObjetivo = NULL;
    archivoObjetivo = fopen("Diccionario.in","r");
    while(!feof(archivoObjetivo)){
          fscanf(archivoObjetivo,"%s%s",palabraEspanhol, palabraOtro);
          fscanf(archivoObjetivo," %[^\n]", definicionEspanhol);
          if(!feof(archivoObjetivo)){
             AVL* elemento = crearElemento(palabraEspanhol, palabraOtro, definicionEspanhol);
             agregarElemento(elemento, &raizEspanhol, &raizOtro);
          }
       }
    fclose(archivoObjetivo);
    return;
}

/* Entrada: Se recibe un elemento AVL (puntero) que es una de las raíces del árbol.
   Salida:  Al ser una función void, no posee retorno.
   Resumen: Se recorre el árbol en postorden liberando la memoria de los nodos, desde las hojas hasta la raíz.
*/
void borrarArbol(AVL** raizEspanhol){ //Elimina cada rama del árbol de entrada.
   if((*raizEspanhol)->hijoIzquierdoPalabraEspanhol != NULL){
      borrarArbol(&((*raizEspanhol)->hijoIzquierdoPalabraEspanhol));
   }
   if((*raizEspanhol)->hijoDerechoPalabraEspanhol != NULL){
      borrarArbol(&((*raizEspanhol)->hijoDerechoPalabraEspanhol));
   }
   free(*raizEspanhol);
   return;
}

/* Entrada: Se reciben dos elemento AVL (punteros) que son las raíces del árbol.
   Salida:  Al ser una función void, no posee retorno.
   Resumen: Se libera la memoria de todos los nodos a través de la función borrarArbol y luego las raíces se restituyen a su estado
            original (NULL).
*/
void anularArbol(AVL** raizEspanhol, AVL** raizOtro){
   borrarArbol(&(*raizEspanhol));
   (*raizEspanhol)->hijoDerechoPalabraEspanhol = NULL;
   (*raizEspanhol)->hijoIzquierdoPalabraEspanhol = NULL;
   (*raizOtro)->hijoDerechoPalabraOtro = NULL;
   (*raizOtro)->hijoIzquierdoPalabraOtro = NULL;
   if(*raizEspanhol != NULL){
      *raizEspanhol = NULL;
   }
   if(*raizOtro != NULL){
      *raizOtro = NULL;
   }
   return;
}

/* Entrada: Se recibe un elemento AVL (puntero) y un elemento FILE (archivo).
   Salida:  Al ser una función void, no posee retorno.
   Resumen: Se recorre el árbol en inorden y se imprime tanto la palabra en Español como la palabra en Otro dentro del archivo.
*/
void imprimirArchivo_alfabeticamenteEspanhol(AVL** raizEspanhol, FILE* escribirArchivo){
   if(*raizEspanhol != NULL){
      if((*raizEspanhol)->hijoIzquierdoPalabraEspanhol != NULL){
         imprimirArchivo_alfabeticamenteEspanhol(&((*raizEspanhol)->hijoIzquierdoPalabraEspanhol), escribirArchivo);
      }
      fprintf(escribirArchivo,"[ %s ]", (*raizEspanhol)->palabraEspanhol);
      fprintf(escribirArchivo,"[ %s ]", (*raizEspanhol)->palabraOtro);
      if((*raizEspanhol)->hijoDerechoPalabraEspanhol != NULL){
         imprimirArchivo_alfabeticamenteEspanhol(&((*raizEspanhol)->hijoDerechoPalabraEspanhol), escribirArchivo);
      }
   }
}

/* Entrada: Se recibe un elemento AVL (puntero) y un elemento FILE (archivo).
   Salida:  Al ser una función void, no posee retorno.
   Resumen: Se recorre el árbol en inorden y se imprime tanto la palabra en Español como la palabra en Otro dentro del archivo.
*/
void imprimirArchivo_alfabeticamenteOtro(AVL** raizOtro, FILE* escribirArchivo){
   if(*raizOtro != NULL){
      if((*raizOtro)->hijoIzquierdoPalabraOtro != NULL){
         imprimirArchivo_alfabeticamenteOtro(&((*raizOtro)->hijoIzquierdoPalabraOtro), escribirArchivo);
      }
      fprintf(escribirArchivo,"[ %s ]", (*raizOtro)->palabraOtro);
      fprintf(escribirArchivo,"[ %s ]", (*raizOtro)->palabraEspanhol);
      if((*raizOtro)->hijoDerechoPalabraOtro != NULL){
         imprimirArchivo_alfabeticamenteOtro(&((*raizOtro)->hijoDerechoPalabraOtro), escribirArchivo);
      }
   }
}

/* Entrada: No posee entradas.
   Salida:  Al ser una función void, no posee retorno.
   Resumen: Se extiende un menú con opciones de generación de archivos para el usuario,
            como opciones se tiene:
               -Generar un archivo de texto con las palabras ordenadas alfabéticamente en Español (Español/Otro).
               -Generar un archivo de texto con las palabras ordenadas alfabéticamente en Otro (Otro/Español).
               -Generar un archivo de texto con las del árbol en pre, in y post orden con abmos idiomas por separado.
               -Volver al menú anterior.
*/
void generarArchivo(){
   FILE* escribirArchivo;
   int opcion;
   do{
      printf("\n*********************************************************************");
      printf("\n                   Generación de archivo de texto                    ");
      printf("\n  1.  Generar archivo de texto ordenado alfabeticamente en Espanhol  ");
      printf("\n  2.  Generar archivo de texto ordenado alfabeticamente en Otro      ");
      printf("\n  3.  Generar archivo de texto con arbol en pre, in y post orden     ");
      printf("\n  4.  Volver                                                         ");
      printf("\n*********************************************************************");
      printf("\n\nElija opcion: ");
      scanf("%d", &opcion);
      fflush(stdin);
      while (getchar() != '\n');
      switch (opcion){
         case 1:
               escribirArchivo = fopen("Palabras.out","w");
               fprintf(escribirArchivo, "Árbol en orden alfabético por Español:\n");
               imprimirArchivo_alfabeticamenteEspanhol(&raizEspanhol, escribirArchivo);
               fclose(escribirArchivo);
               printf("\nEl archivo ha sido generado exitosamente.\n");
         break;
         case 2:
               escribirArchivo = fopen("Palabras.out","w");
               fprintf(escribirArchivo, "Árbol en orden alfabético por Otro:\n");
               imprimirArchivo_alfabeticamenteOtro(&raizOtro, escribirArchivo);
               fclose(escribirArchivo);
               printf("\nEl archivo ha sido generado exitosamente.\n");
         break;
         case 3:
               escribirArchivo = fopen("Palabras.out","w");
               imprimirArbol_Preorden(&raizEspanhol, &raizOtro, escribirArchivo);
               fclose(escribirArchivo);
               escribirArchivo = fopen("Palabras.out","a");
               imprimirArbol_Inorden(&raizEspanhol, &raizOtro, escribirArchivo);
               imprimirArbol_Postorden(&raizEspanhol, &raizOtro, escribirArchivo);
               fclose(escribirArchivo);
               printf("\nEl archivo ha sido generado exitosamente.\n");
         break;
         case 4:
         break;
      }
   }while(opcion != 1 && opcion != 2 && opcion != 3);
}

/* Entrada: No posee entradas.
   Salida:  Al ser una función void, no posee retorno.
   Resumen: Se extiende un menú con opciones para buscar palabras tanto como en Español como en otro,
            además, se le da la opción al usuario de elegir si mostrar la definición de la palabra buscada.
*/
void buscarPalabras(){
   int opcion;
   char palabra[51];
   char respuestaUsuario;
   do{
      printf("\n***********************************************");
      printf("\n           Busqueda de Palabras                ");
      printf("\n      1.  Buscar palabras en Espanhol          ");
      printf("\n      2.  Buscar palabras en Otro              ");
      printf("\n      3.  Volver                               ");
      printf("\n***********************************************");
      printf("\n\nElija opcion: ");
      scanf("%d", &opcion);
      fflush(stdin);
      while (getchar() != '\n');
      switch (opcion){
         case 1:
               printf("\nEscriba la palabra a buscar: ");
               scanf("%s", palabra);
               AVL* palabraBuscadaEspanhol = buscarElemento(palabra, &raizEspanhol, &raizOtro);
               printf("\nLa palabra en Espanhol es: %s , en Otro es: %s \n", palabraBuscadaEspanhol->palabraEspanhol, palabraBuscadaEspanhol->palabraOtro);
               printf("\nMostrar definicion\n");
               printf("     (S/n)\n");
               scanf("%c", &respuestaUsuario);
               respuestaUsuario = getchar();
               while (getchar() != '\n');
               if(respuestaUsuario == 'S' || respuestaUsuario == 's'){
         			printf("\nLa definicion de la palabra es: %s \n\n", palabraBuscadaEspanhol->definicionEspanhol);
                  break;
         		}
               if(respuestaUsuario == 'N' || respuestaUsuario == 'n'){
                  break;
         		}
         break;
         case 2:
               printf("\nEscriba la palabra a buscar: ");
               scanf("%s", palabra);
               AVL* palabraBuscadaOtro = buscarElemento(palabra, &raizEspanhol, &raizOtro);
               printf("La palabra en Otro es: %s , en Espanhol es: %s \n", palabraBuscadaOtro->palabraOtro, palabraBuscadaOtro->palabraEspanhol);
               printf("Mostrar definicion\n");
               printf("     (S/n)\n");
               scanf("%c", &respuestaUsuario);
               respuestaUsuario = getchar();
               while (getchar() != '\n');
               if(respuestaUsuario == 'S' || respuestaUsuario == 's'){
                  printf("\nLa definicion de la palabra es: %s \n\n", palabraBuscadaOtro->definicionEspanhol);
                  break;
               }
               if(respuestaUsuario == 'N' || respuestaUsuario == 'n'){
                  break;
               }
         break;
         case 3:
         break;
      }
   }while (opcion != 1 && opcion != 2 && opcion != 3);
}

/* Entrada: No posee entradas.
   Salida:  Al ser una función void, no posee retorno.
   Resumen: Se anula el árbol, se lee el archivo y se genera un nuevo árbol correspondiente a los nuevos datos.
*/
void actualizarDatos(){
   anularArbol(&raizEspanhol, &raizOtro);
   leerArchivo();
   printf("\nDatos actualizados exitosamente\n\n");
   return;
}

/* Entrada: No posee entradas.
   Salida:  Al ser una función void, no posee retorno.
   Resumen: Se extiende un menú con opciones para el usuario, entre ellas:
                  -Buscar palabras, ya sean en Español u Otro (contiene un menú propio).
                  -Generar un archivo de texto (contiene un menú propio).
                  -Actualizar datos, actualiza los datos del árbol a partir de la entrada "Diccionario.in".
                  -Salir, termina la ejecución del programa.
*/
void menuTraductor(){
   int opcion;
   do{
      printf("\n***********************************************");
      printf("\n      1.  Buscar palabras                      ");
      printf("\n      2.  Generar archivo de texto             ");
      printf("\n      3.  Actualizar datos                     ");
      printf("\n      4.  Salir                                ");
      printf("\n***********************************************");
      printf("\n\nElija opcion: ");
      scanf("%d", &opcion);
      fflush(stdin);
      while (getchar() != '\n');
      switch (opcion){
         case 1:
               buscarPalabras();
         break;
         case 2:
               generarArchivo();
         break;
         case 3:
               actualizarDatos();
         break;
         case 4:
               anularArbol(&raizEspanhol, &raizOtro);
               printf("\nHasta Pronto\n");
         break;
      }
   }while(opcion != 4);
}

char obtenerLetraInicial(char palabra[]){
   return palabra[0];
}

void imprimirMatrizEspanhol(char* listaArbolInordenEspanhol[]){
   FILE* archivoMatrizEspanhol;
	int i, comparacion;
   char palabraAuxiliar[51] = "";
   archivoMatrizEspanhol = fopen("MatrizEspañol.out","w");
	i = 0;
	comparacion = 0;
	while(i < largoArbol){
		if(comparacion == 0){
			strcpy(palabraAuxiliar, listaArbolInordenEspanhol[i]);
			comparacion++;
			i++;
      }
      else{
			if(obtenerLetraInicial(listaArbolInordenEspanhol[i]) == obtenerLetraInicial(palabraAuxiliar)){
				fprintf(archivoMatrizEspanhol, "[ %s ]", palabraAuxiliar);
				strcpy(palabraAuxiliar, listaArbolInordenEspanhol[i]);
				i++;
			}
         else{
				fprintf(archivoMatrizEspanhol, "[ %s ]", palabraAuxiliar);
				strcpy(palabraAuxiliar, listaArbolInordenEspanhol[i]);
				fprintf(archivoMatrizEspanhol, "\n");
				i++;
			}
		}
	}
   i--;
   if(obtenerLetraInicial(listaArbolInordenEspanhol[i]) == obtenerLetraInicial(palabraAuxiliar)){
      fprintf(archivoMatrizEspanhol, "[ %s ]", palabraAuxiliar);
      strcpy(palabraAuxiliar, listaArbolInordenEspanhol[i]);
   }
   else{
      fprintf(archivoMatrizEspanhol, "[ %s ]", palabraAuxiliar);
      strcpy(palabraAuxiliar, listaArbolInordenEspanhol[i]);
      fprintf(archivoMatrizEspanhol, "\n");
   }
   fclose(archivoMatrizEspanhol);
	return;
}

void imprimirMatrizOtro(char* listaArbolInordenOtro[]){
   FILE* archivoMatrizOtro;
	int i, comparacion;
   char palabraAuxiliar[51] = "";
   archivoMatrizOtro = fopen("MatrizOtro.out","w");
	i = 0;
	comparacion = 0;
	while(i < largoArbol){
		if(comparacion == 0){
			strcpy(palabraAuxiliar, listaArbolInordenOtro[i]);
			comparacion++;
			i++;
      }
      else{
			if(obtenerLetraInicial(listaArbolInordenOtro[i]) == obtenerLetraInicial(palabraAuxiliar)){
				fprintf(archivoMatrizOtro, "[ %s ]", palabraAuxiliar);
				strcpy(palabraAuxiliar, listaArbolInordenOtro[i]);
				i++;
			}
         else{
				fprintf(archivoMatrizOtro, "[ %s ]", palabraAuxiliar);
				strcpy(palabraAuxiliar, listaArbolInordenOtro[i]);
				fprintf(archivoMatrizOtro, "\n");
				i++;
			}
		}
	}
   i--;
   if(obtenerLetraInicial(listaArbolInordenOtro[i]) == obtenerLetraInicial(palabraAuxiliar)){
      fprintf(archivoMatrizOtro, "[ %s ]", palabraAuxiliar);
      strcpy(palabraAuxiliar, listaArbolInordenOtro[i]);
   }
   else{
      fprintf(archivoMatrizOtro, "[ %s ]", palabraAuxiliar);
      strcpy(palabraAuxiliar, listaArbolInordenOtro[i]);
      fprintf(archivoMatrizOtro, "\n");
   }
   fclose(archivoMatrizOtro);
	return;
}

/* Entrada: No posee entradas.
   Salida:  Al ser una función void, no posee retorno.
   Resumen: Se extiende un menú con opciones para el usuario, entre ellas:
                  -Buscar palabras, ya sean en Español u Otro (contiene un menú propio).
                  -Generar un archivo de texto (contiene un menú propio).
                  -Actualizar datos, actualiza los datos del árbol a partir de la entrada "Diccionario.in".
                  -Salir, termina la ejecución del programa.
*/
void menuDiccionario(char* listaArbolInordenEspanhol[], char* listaArbolInordenOtro[]){
   int opcion;
   do{
      printf("\n***********************************************");
      printf("\n      1.  Buscar Patrones                      ");
      printf("\n      2.  Matriz en Español                    ");
      printf("\n      3.  Matriz en Otro idioma                ");
      printf("\n      4.  Actualizar datos                     ");
      printf("\n      5.  Salir                                ");
      printf("\n***********************************************");
      printf("\n\nElija opcion: ");
      scanf("%d", &opcion);
      fflush(stdin);
      while (getchar() != '\n');
      switch (opcion){
         case 1:
               printf("Aun en desarrollo\n");
         break;
         case 2:
               imprimirMatrizEspanhol(listaArbolInordenEspanhol);
               printf("\nLa matriz en español ha sido generada exitosamente.\n");
         break;
         case 3:
               imprimirMatrizOtro(listaArbolInordenOtro);
               printf("\nLa matriz en otro idioma ha sido generada exitosamente.\n");
         break;
         case 4:
               actualizarDatos();
         break;
         case 5:
               anularArbol(&raizEspanhol, &raizOtro);
               printf("\nHasta Pronto\n");
         break;
      }
   }while(opcion != 5);
}

/* Entrada: No posee entradas.
   Salida:  Al ser una función void, no posee retorno.
   Resumen: Se guarda en una variable global el nombre del usuario, el cual es requerido a este por pantalla.
*/
void ingresar(){
   printf("\nIngrese su nombre: ");
   scanf(" %s", nombreUsuario);
   return;
}

/* Entrada: No posee entradas.
   Salida:  Al ser una función void, no posee retorno.
   Resumen: Se desplega un menú de bienvenida con sólo dos opciones, las cuales son:
                  -Ingresar, se requiere el nombre del usuario.
                  -Salir, que termina con la ejecución del programa
*/
void menuPrincipal(char* listaArbolInordenEspanhol[], char* listaArbolInordenOtro[]){
   int opcion;
   do{
     printf("\n***********************************************");
     printf("\n            Bienvenido %s       ", nombreUsuario);
     printf("\n           1.  Traductor                       ");
     printf("\n           2.  Diccionario                     ");
     printf("\n           3.  Salir                           ");
     printf("\n***********************************************");
     printf("\n\nElija opcion: ");
     scanf("%d",&opcion);
     fflush(stdin);
     while (getchar() != '\n');
     switch (opcion){
        case 1:
        menuTraductor();
        break;
        case 2:
        menuDiccionario(listaArbolInordenEspanhol, listaArbolInordenOtro);
        break;
        case 3:
               anularArbol(&raizEspanhol, &raizOtro);
               printf("SALIR\n");
        break;
     }
  }while (opcion != 1 && opcion != 2 && opcion != 3);
  return;
}

void menuPrimario(char* listaArbolInordenEspanhol[], char* listaArbolInordenOtro[]){
   int opcion;
   do{
     printf("\n***********************************************");
     printf("\n                Bienvenido                     ");
     printf("\n             1.  Ingresar                      ");
     printf("\n             2.  Salir                         ");
     printf("\n***********************************************");
     printf("\n\nElija opcion: ");
     scanf("%d",&opcion);
     fflush(stdin);
     while (getchar() != '\n');
     switch (opcion){
        case 1: printf("\n    Ingresar");
        ingresar();
        menuPrincipal(listaArbolInordenEspanhol, listaArbolInordenOtro);
        break;
        case 2:
               anularArbol(&raizEspanhol, &raizOtro);
               printf("SALIR\n");
        break;
     }
  }while (opcion != 1 && opcion != 2);
return;
}
// Fin de código de Laboratorio 4 - Traductor.
// Inicio de código de Laboratorio 5 - Diccionario.

//Declaración de variables globales.


void adquirirRaizP1(char palabra[]){
   int i, largoPalabra;
   largoPalabra = strlen(palabra);
   i = 0;
   if(largoPalabra < 4){
      while(i != '\0'){
         raizP1[i] = palabra[i];
         i++;
      }
   }
   else{
      while(i != 4){
         raizP1[i] = palabra[i];
         i++;
      }
   }
   return;
}

void adquirirRaizP2(char palabra[]){
   int i, largoPalabra;
   largoPalabra = strlen(palabra);
   i = 0;
   if(largoPalabra < 4){
      while(i != '\0'){
         raizP2[i] = palabra[i];
         i++;
      }
   }
   else{
      while(i != 4){
         raizP2[i] = palabra[i];
         i++;
      }
   }
   return;
}

void adquirirRaizPalabras(char P1[], char P2[]) {
   adquirirRaizP1(P1);
   adquirirRaizP2(P2);
   return;
}

void adquirirTerminacionP1(char palabra[]) {
   int i, objetivo, largoPalabra;
   largoPalabra = strlen(palabra);
   objetivo = largoPalabra - 3;
   i = 0;
   if(objetivo < 0){
      while(palabra[i] != '\0'){
         terminacionP1[i] = palabra[i];
         i++;
      }
   }
   else{
      while(palabra[objetivo] != '\0'){
         terminacionP1[i] = palabra[objetivo];
         objetivo++;
         i++;
      }
   }
}

void adquirirTerminacionP2(char palabra[]) {
   int i, objetivo, largoPalabra;
   largoPalabra = strlen(palabra);
   objetivo = largoPalabra - 3;
   i = 0;
   if(objetivo < 0){
      while(palabra[i] != '\0'){
         terminacionP2[i] = palabra[i];
         i++;
      }
      return;
   }
   else{
      while(palabra[objetivo] != '\0'){
         terminacionP2[i] = palabra[objetivo];
         objetivo++;
         i++;
      }
      return;
   }
}


void mostrarRecorrido(char* arregloPalabrasInorden[]){
   int i;
   printf("El arreglo contiene: \n");
   for (i = 0; i < largoArbol; i++){
      printf("[ %s ]", arregloPalabrasInorden[i]);
   }
   printf("\n");
   return;
}

void generarListaArbolInordenEspanhol(AVL** raizEspanhol, char* arbolInordenEspanhol[]){
   if(*raizEspanhol != NULL){
      if((*raizEspanhol)->hijoIzquierdoPalabraEspanhol != NULL){
         generarListaArbolInordenEspanhol(&((*raizEspanhol)->hijoIzquierdoPalabraEspanhol), arbolInordenEspanhol);
      }
      arbolInordenEspanhol[contadorEspanhol] = (*raizEspanhol)->palabraEspanhol;
      contadorEspanhol++;
      if((*raizEspanhol)->hijoDerechoPalabraEspanhol != NULL){
         generarListaArbolInordenEspanhol(&((*raizEspanhol)->hijoDerechoPalabraEspanhol), arbolInordenEspanhol);
      }
   }
}

void generarListaArbolInordenOtro(AVL** raizOtro, char* arbolInordenOtro[]){
   if(*raizOtro != NULL){
      if((*raizOtro)->hijoIzquierdoPalabraOtro != NULL){
         generarListaArbolInordenOtro(&((*raizOtro)->hijoIzquierdoPalabraOtro), arbolInordenOtro);
      }
      arbolInordenOtro[contadorOtro] = (*raizOtro)->palabraOtro;
      contadorOtro++;
      if((*raizOtro)->hijoDerechoPalabraOtro != NULL){
         generarListaArbolInordenOtro(&((*raizOtro)->hijoDerechoPalabraOtro), arbolInordenOtro);
      }
   }
}


void adquirirLetrasIniciales(char listaLetrasIniciales[], char* listaArbolInorden[]){
   int i;
   for (i = 0; i < largoArbol; i++){
      listaLetrasIniciales[i] = obtenerLetraInicial(listaArbolInorden[i]);
   }
   return;
}

void inicializar(){
   char* listaArbolInordenEspanhol[largoArbol];
   char* listaArbolInordenOtro[largoArbol];
   int i;
   contadorEspanhol = 0;
   contadorOtro = 0;
   generarListaArbolInordenEspanhol(&raizEspanhol, listaArbolInordenEspanhol);
   generarListaArbolInordenOtro(&raizOtro, listaArbolInordenOtro);
   menuPrimario(listaArbolInordenEspanhol, listaArbolInordenOtro);

}

void inicializarListaAdyacencia(){
   listaAdyacencia.inicio = NULL;
   longitudLA = 0;
   return;
}

Vertice* crearVertice(char letraInicial){
   Vertice* vertice = (Vertice*)malloc(sizeof(Vertice));
   vertice->letraInicial = letraInicial;
   vertice->inicio = NULL;
   vertice->siguiente = NULL;
   return vertice;
}

VA* crearVerticeAdyacente(char palabra[]){
   VA* verticeAdyacente = (VA*)malloc(sizeof(VA));
   strcpy(verticeAdyacente->palabra, palabra);
   verticeAdyacente->siguiente = NULL;
   return verticeAdyacente;
}

void agregarVertice(Vertice* vertice){
   int i;
	if(listaAdyacencia.inicio == NULL){
		listaAdyacencia.inicio = vertice;
      longitudLA = 1;
		return;
	}
	else{
		Vertice * verticeAux = listaAdyacencia.inicio;
		for (i = 0; i < longitudLA-1; i++){
			verticeAux = verticeAux->siguiente;
		}
		verticeAux->siguiente = vertice;
      longitudLA++;
		return;
		}
}

void agregarVerticeAdyacente(Vertice* verticeObjetivo, VA* verticeAdyacente){
   int i;
   Vertice* verticeAux = verticeObjetivo;
	if(verticeAux->inicio == NULL){
		verticeAux->inicio = verticeAdyacente;
      verticeAux->longitud = 1;
		return;
	}
	else{
		VA* verticeAdyacenteAux = verticeAux->inicio;
		for (i = 0; i < verticeAux->longitud-1; i++){
			verticeAdyacenteAux = verticeAdyacenteAux -> siguiente;
		}
		verticeAdyacenteAux -> siguiente = verticeAdyacente;
      verticeAux->longitud++;
		return;
	}
}

void crearListaAdyacencia(char listaLetrasInicialesEspanhol[]){
   int i, k, j, encontrado;
   char letrasRepetidas[largoArbol];
   char letraIncertar;
   k = 0;
   for(i = 0; i < largoArbol; i++){
      encontrado = 0;
      letraIncertar = listaLetrasInicialesEspanhol[i];
      for (j = 0; j < largoArbol; j++){
         if(letraIncertar == letrasRepetidas[j]){
            encontrado = 1;
         }
      }
      if(encontrado == 0){
         letrasRepetidas[k] = letraIncertar;
         Vertice* vertice = crearVertice(letraIncertar);
         agregarVertice(vertice);
         k++;
      }
   }
}

void rellenarListaAdyacencia(char* listaArbolInordenEspanhol[]){
   int i,j;
   char letraObjetivo;
   for (i = 0; i < largoArbol; i++){
      letraObjetivo = obtenerLetraInicial(listaArbolInordenEspanhol[i]);
      Vertice* verticeAux = listaAdyacencia.inicio;
      while(verticeAux->letraInicial != letraObjetivo){
         verticeAux = verticeAux -> siguiente;
      }
      VA* verticeAdyacente = crearVerticeAdyacente(listaArbolInordenEspanhol[i]);
      agregarVerticeAdyacente(verticeAux,verticeAdyacente);
   }
   return;
}

void mostrarVerticeAdyacente(VA* verticeAdyacente) {
   printf("[ %s ]", verticeAdyacente->palabra);
   return;
}

void mostrarVertice(Vertice* vertice){
	printf(" %c -> ", vertice->letraInicial);
   VA* verticeAdyacenteAux = vertice->inicio;
	while(verticeAdyacenteAux-> siguiente != NULL){
		mostrarVerticeAdyacente(verticeAdyacenteAux);
		verticeAdyacenteAux = verticeAdyacenteAux -> siguiente;
	}
	mostrarVerticeAdyacente(verticeAdyacenteAux);
	printf("\n");
   return;
}

void mostrarListaAdyacencia(){ // Sólo para uso del Desarrollador.
   Vertice* verticeAux = listaAdyacencia.inicio;
	while(verticeAux->siguiente != NULL){
		mostrarVertice(verticeAux);
		verticeAux = verticeAux -> siguiente;
	}
	mostrarVertice(verticeAux);
	printf("\n");
}

int main(int argc, char const *argv[]){
   //Laboratorio 4 - Traductor.
   inicializarArbol();
   leerArchivo();
   //Laboratorio 4 - Traductor.

   //inicializar();
   int i = 0;
   char* listaArbolInordenEspanhol[largoArbol];
   char* listaArbolInordenOtro[largoArbol];
   contadorEspanhol = 0;
   contadorOtro = 0;
   generarListaArbolInordenEspanhol(&raizEspanhol, listaArbolInordenEspanhol);
   generarListaArbolInordenOtro(&raizOtro, listaArbolInordenOtro);// Momentaneo
   char listaLetrasInicialesEspanhol[largoArbol];
   char listaLetrasInicialesOtro[largoArbol];
   adquirirLetrasIniciales(listaLetrasInicialesEspanhol, listaArbolInordenEspanhol);
   inicializarListaAdyacencia();
   crearListaAdyacencia(listaLetrasInicialesEspanhol);
   rellenarListaAdyacencia(listaArbolInordenEspanhol);
   printf("\nLa lista de adyacencia es:\n");
   mostrarListaAdyacencia();
   /*while(i != largoArbol){
      listaLetrasInicialesEspanhol[i];
   }*/

   /*char P1[50] = "Galaxia";
   char P2[50] = "Galaxy";
   int largoP1, largoP2;
   largoP1 = strlen(P1);
   largoP2 = strlen(P2);
   printf("El largo de %s es: %d\n", P1, largoP1);
   printf("El largo de %s es: %d\n", P2, largoP2);
   adquirirRaizPalabras(P1, P2);
   printf("La raíz de P1 es: %s\n", raizP1);
   printf("La raíz de P2 es: %s\n", raizP2);
   printf("La comparación arroja: %d\n", strcmp(raizP1,raizP2));
   if(strcmp(raizP1,raizP2) == 0){
      printf("Las palabras poseen la misma raíz\n\n");
   }
   else{
      printf("Las palabras no poseen la misma raíz\n\n");
   }
   adquirirTerminacionP1(P1);
   adquirirTerminacionP2(P2);
   printf("La terminacion de P1 es: %s\n", terminacionP1);
   printf("La terminacion de P2 es: %s\n", terminacionP2);
   if(strcmp(terminacionP1, terminacionP2) == 0){
      printf("Las palabras poseen la misma terminacion\n");
   }
   else{
      printf("Las palabras no poseen la misma terminacion\n");
   }*/
   return 0;
}
