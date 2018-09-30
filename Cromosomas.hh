/** @file Cromosomas.hh
    @brief Especificación de la clase Cromosomas
*/

#ifndef Cromosomas_HH
#define Cromosomas_HH

#include <map>
#include <vector>
#include <string>
#include <iostream>
using namespace std;

/** @class Cromosomas
    @brief Representa la informacion de los Cromosomas de los Individuos, incluyendo las caracteristicas generales de los Cromosomas de toda la Especie. 
*/

class Cromosomas {
  
private:
	/** @brief Numero de cromosomas de la Especie */
  int N;
  /** @brief Numero de punto de corte para la reproduccion */
  int punto_de_corte;
  /** @brief Longitud de los cromosomas X de la Especie */
  int lx;
  /** @brief Longitud de los cromosomas Y de la Especie */
  int ly;

	/** @brief vector con los tamaños de los cromosomas normales */
  vector <int> normales;
	/** @brief Definicion del tipo Cromosoma a usar*/
  typedef vector <int> Cromosoma;

 	/** @brief Contiene la informacion de los dos genes de cada par de cromosomas de un Individuo */
	struct Crom {
		Cromosoma one;
		Cromosoma two;
	};
 	/** @brief Contiene la informacion de los cromosomas normales de un Individuo */
    map <int, Crom> genotipo;
	/** @brief Contiene la informacion de los cromosomas sexuales de un Individuo */
    pair <Cromosoma,Cromosoma> gensexs;
  
public:

  // Constructora
  /** @brief Creadora por defecto
      @pre cierto
      @post El resultado es una Cromosoma vacío
      @coste Constante
  */
  Cromosomas();
  
  //Modificadoras

  /** @brief Obtiene los parametros generales de los cromosomas de la Especie
      @pre La especie existe
      @post El cromosoma obtiene los valores generales de los cromosomas de la Especie
  */
  void definir_especie();

  /** @brief Obtiene los parametros generales de los cromosomas de la Especie de otro Cromosoma
      @pre El cromosoma tiene valores generales de la Especie
      @post El parametro implicito obtiene los valores generales de la Especie
  */
  void obtener_valores(Cromosomas x);
  
  /** @brief Añade una cromosoma en el parámetro implícito.
      @pre La cromosoma a añadir no pertenece al parámetro implícito
      @post La cromosoma se ha añadido en el parametro implícito con nombre nom y con valor = Arbol
  */
  void anadir_cromosomas(); 

  /** @brief Añade una cromosoma en el parámetro implícito.
      \pre La cromosoma a añadir no pertenece al parámetro implícito
      \post La cromosoma se ha añadido en el parametro implícito con nombre nom y con valor = Arbol
  */
  void anadir_cromosoma_sexs(bool sex);

  /** @brief Modifica el cromosoma del parámetro implícito. 
      \pre El cromosoma a modificar pertenece al parámetro implícito
      \post El parametro implicito tiene nuevos cromosomas normales
  */
  void crear_cromosomas(Cromosomas& norm, Cromosomas m, Cromosomas p, int elegirm, int elegirp, int limit, int position);

  /** @brief Modifica el cromosoma del parámetro implícito. 
      \pre El cromosoma a modificar pertenece al parámetro implícito
      \post El Cromosoma tiene nuevos cromosomas sexuales
  */
	Cromosomas crear_cromosomas_sexs(Cromosomas m, Cromosomas p, int elegirm, int elegirp, int limit);

  //Consultoras
   
  /** @brief Consulta el tamaño del cromosoma del parametro implicito
      \pre existe
      \post el valor entero del tamaño del cromosoma en cuestion
  */
  int consultar_cromnorm (int i);

  /** @brief Consultora del valor del numero de pares de cromosomas de la Especie 
      \pre El parametro implicito es un entero
      \post El valor del parametro implicito
  */
  int obtener_N();

  // Entrada / Salida
  /** @brief Operación de escritura
      \pre cierto
      \post Se ha escrito los cromosomas sexuales del parámetro implícito por el canal de salida estándard
      \coste Lineal respecto al número de parámetros de un cromosoma
  */
  void escribir_cromosomas_sexs(bool sex) const;
  /** @brief Operación de escritura
      \pre cierto
      \post Se ha escrito los cromosomas normales del parámetro implícito por el canal de salida estándard
      \coste Lineal respecto al número de parámetros de un cromosoma
  */
  void escribir_cromosomas() const;
};
#endif
