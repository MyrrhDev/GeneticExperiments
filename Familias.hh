/** @file Familias.hh
    @brief Especificación de la clase Familias
*/

#ifndef Familias_HH
#define Familias_HH

#include "Arbre.hh"
#include <list>
#include <string>
#include <vector>
#include <map>
#include <iostream>
using namespace std;

/** @class Familias
    @brief Representa las Familias de la Especie. Tiene el registro de las familias (hijo, padre y madre) de toda la Especie.
*/

class Familias 
{
private:     
  /** @brief Definicion de par de Padres, donde el primer string es el del padre y el segundo string es el de la madre */
  typedef pair <string,string> Padres;
	
	/** @brief Mapa donde se guardan todos las familias nucleares (hijo, padre y madre) de la Especie */
  map <string, Padres> FamNuclear;
  
  /** @brief Crea el arbol genealogico parcial de un Individuo
		\pre cierto
    \post Se obtiene un arbol parcial de los datos que entran por el canal estandar de entrada
  */
	void leer_arbol_parcial(Arbre<string>& a);

  /** @brief Crea el arbol genealogico general de un Individuo
      \pre hijo existe
      \post Se obtiene el arbol genealogico general del hijo, de los datos obtenidos del parametro implicito
  */
	void leer_arbol_general(Arbre<string>& b, string hijo);

	/** @brief Consultora de si el hijo existe en el parametro implicito
      \pre cierto
      \post El resultado es cierto si el hijo existe en el parametro implícito y falso en caso contrario 
      \coste Constante 
  */
	bool exist_hijo(string hijo);

  /** @brief Consultora de si el hijo existe en el arbol a
      \pre a existe, parent existe
      \post El resultado es cierto si el hijo existe en el arbol A y falso en caso contrario 
      \coste Constante 
  */

	bool buscar_en_arbol(Arbre<string> a, string parent);
  
	/** @brief Consultora de si el arbol es un arbol parcial del arbol general
      \pre cierto
      \post El resultado es cierto si la estructura de nodos de a coincide con la estructura de algun subconjunto conexo de nodos de b que incluya a su nodo raiz y los identificadores de los nodos de a son los mismos que los de
los nodos correspondientes de b y falso en caso contrario.
      \coste Dependera del tamaño del arbol general como maximo
  */

	bool es_parcial(Arbre<string> a, Arbre<string> b, string left, string right);

  /** @brief Operación de escritura de un árbol general de un Individuo
      \pre  cierto
      \post Se ha escrito a por el canal de salida estándard
      \coste Lineal respecto al número de nodos del árbol escrito
  */ 
	void escribir_arbol_completo(Arbre<string>& input, Arbre<string>& general);

  /** @brief Modificadora que gestiona la creacion de un vector con los niveles de ascendencia de un Individuo
      \pre niveles es un vector vacio, n el tamaño del vector, person es el Individuo
      \post El parámetro implícito contiene la informacion de la ascendencia del Individuo person y construye así un
			vector de niveles de ascendencia donde el nivel 0 es el Individuo person, nivel 1 son sus ascendientes (padre y madre) y el nivel i+1 muestran los ascendentes de ambos hasta que ambos no tengan mas ascendientes.
  */

	void ordernar_niveles(string person, vector <list <string> >& niveles, int n);

  /** @brief Operación de escritura del vector de niveles de ascendientes del Individuo
      \pre  cierto
      \post Se ha escrito a por el canal de salida estándard los niveles
      \coste Lineal respecto al tamaño del vector
  */ 
	void escribir_niveles(vector <list <string> >& niveles);


public:
  
  //Constructoras

  /** @brief Creadora por defecto. 

      Se ejecuta automáticamente al declarar una variable
      \pre <em>cierto</em>
      \post El Familia es una variable sin ningun valor
  */  
  Familias();

  /** @brief Consultora que indica si el Individuo tiene padres
      \pre cierto
      \post El resultado indica si el Individuo tiene padres o no
      \coste Constante
  */
	bool tiene_padres(string person);

  /** @brief Consultora que indica si el Individuo tiene los mismos padres
      \pre cierto
      \post El resultado indica si el Individuo tiene los mismos padres o no
      \coste Constante
  */
	bool mismos_padres(string madre, string padre);

  /** @brief Consultora que indica si un Individuo es ascendente de otro
      \pre cierto
      \post El resultado indica si el Individuo posascend existe en el arbol general del Individuo poshijo
      \coste Constante
  */
	bool son_familia (string poshijo, string posascend);

  /** @brief Modifica el mapa de Familia Nuclear y agrega una familia nueva
      \pre hijo no existe, padre y madre existen
      \post el parámetro implícito pasa a tener una nueva familia con identificador hijo, y guarda su padre y madre en Padres
  */

	void insertar_familias(string hijo, string padre, string madre);

  /** @brief Consultora de los Padres de un Individuo
      \pre existe
      \post El resultado son los nombres del padre y madre recogidos del parametro implicito
      \coste Constante 
  */
    
	void consultar_padres(string hijo, string& padre, string& madre);

  /** @brief Operación de escritura arbol completo del Individuo
      \pre  cierto
      \post Al cumplirse las condiciones, se escribe por el canal estandar de salida el arbol general mediante la funcion "escribir_arbol_completo"
      \coste Lineal respecto al tamaño del vector
  */
	void completar_arbol();

  /** @brief Operación de escritura del vector de niveles de ascendientes del Individuo
    \pre  hijo existe
    \post Crea un vector con los niveles de los ascendientes del hijo y llama a "escribir niveles" para escribirlos por el canal estandar de salida
    \coste Lineal respecto al tamaño del vector
  */ 
	void escribir_arbol_niveles(string hijo);


};
#endif
