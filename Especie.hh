/** @file Especie.hh
    @brief Especificación de la clase Especie
*/

#ifndef _Especie_HH_
#define _Especie_HH_

#include "Familias.hh"
#include "Individuo.hh"
#include "Cromosomas.hh"

#include <map>
#include <string>
#include <iostream>
using namespace std;

/** @class Especie
    @brief Representa una Especie y las operaciones asociadas a una Especie.

    Sus operaciones son las modificadoras de la Especie y sus Individuos, las consultoras de si un organismo es maligno y la de su número de víctimas, la que devuelve el resultado de una lucha de dos organismos, la de lectura (única que produce un organismo nuevo) y la de escritura.
 */

class Especie
{
  
private: 
	  
  /** @brief Mapa del registro del nombre y datos de Cromosomas del Individuo */
  map <string, Individuo, less<string> > registro;
  
public:
  //Constructoras

  /** @brief Creadora por defecto. 

      Se ejecuta automáticamente al declarar una expresión
      \pre <em>cierto</em>
      \post Se crea una Especie
      \coste Constante
  */  
  Especie();
  
  //Modificadoras
  /** @brief Añade un nuevo individuo sin antecedentes.
      \pre El individuo no existe
      \post El parametro implicito es como su valor original pero pasa a tener un nuevo individuo
  */ 
  void anadir_individuo(Cromosomas c, Familias& f, string bname);

  /** @brief Modificadora que gestiona la reproduccion de dos Individuos
      \pre los Individuos existen
      \post El parámetro implícito contiene  
  */
	void reproducir_individuos(Cromosomas c,Familias& fam,string madre, string padre, string hijo);

  //Consultoras


  // Entrada / Salida
	/** @brief Dado un individuo, escribir su escribir su genotipo, por orden creciente de identificador de par de cromosomas
		\pre existe el individuo
    \post sale por el canal estandar genotipo, por orden creciente de identificador de par de cromosomas
  */
	void escribir_individuo_genotipo (string name);

	/** @brief Se escribe un listado de todos los individuos ordenados alfabeticamente por nombres
		\pre el parametro implicito no está vacio
    \post sale por el canal estandar un listado de todos los individuos ordenados alfabeticamente por nombres
  */
  void escribir_individuos(Familias f);

	/** @brief Se escribe su arbol genealogico ordenado por niveles, e indicando cada nivel mediente "Nivel i:" donde 0<=i<=n, donde n es el numero maximo de niveles de antecesores 
 
		\pre el parametro implicito no está vacio
    \post sale por el canal estandar un arbol genealogico ordenado por niveles, e indicando cada nivel mediente "Nivel i:" donde 0<=i<=n, donde n es el numero maximo de niveles de antecesores
  */
	void escribir_arbol_genealogico(Familias f, string name);


private: 
  /** @brief Consultora de si dos Individuos se pueden reproducir
     \pre <em>cierto</em>
     \post Indica si 
  */
 bool individuos_reproduccion(string madre, string padre, string hijo);

  /** @brief Operacion de lectura.
      \pre por el canal estándar entra un string
      \post el parámetro implícito pasa a tener en sus atributos al Individuo ind y su identificador bname
  */
  void insertar_especie(Individuo ind, string bname);

 /** @brief Consultora del estado de un individuo
 
     \pre <em>cierto, existe</em>
     \post Indica si existe 
 */
	bool existe_individuo (string name) const;

 /** @brief Consultora de si dos Individuos se pueden reproducir
     \pre <em>cierto</em>
     \post Indica si existen los individuos madre y padre y que no existe el hijo. 
 */
	bool se_puede_reproducir(Familias f, string madre, string padre, string hijo);

 /** @brief Consultora de si dos Individuos tiene el sexo que deberian para la reproduccion
 
     \pre <em>cierto, exiten</em>
     \post Indica si el primer Individuo es mujer y el segundo es hombre
 */
	bool same_sex(string madre, string padre);

};
#endif
