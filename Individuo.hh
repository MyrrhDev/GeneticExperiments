/** @file Individuo.hh
    @brief Especificación de la clase Individuo 
*/

#ifndef _Individuo_HH_
#define _Individuo_HH_

#include "Cromosomas.hh"  

#include <string>         
#include <iostream>  
#include <map>

using namespace std;

/** @class Individuo
    @brief Representa los Individuos posibles del experimento. Representa el conjunto de características y
    operaciones de los Individuos.

    Ofrece las operaciones de modificacion de un Individuo o de sus caracteristicas de Cromosomas.

*/
class Individuo
{
private:
  /* Un Individuo se representa mediante sus caracteristicas, nombre
	su identificador de sexo, sus cromosomas sexuales y normales. */

  /** @brief Nombre del Individuo */
	string name;
  /** @brief Identificador de sexo, falso para mujer y verdadero para hombre */
  bool sex;
  /** @brief Cromosomas sexuales */
  Cromosomas sexs;
  /** @brief Cromosomas normales */
  Cromosomas croms;

public:

  // Constructora
  /** @brief Creadora por defecto
      @pre cierto
      @post El resultado es una Individuo vacío
      @coste Constante
  */
  Individuo();

	//Consultadora
  /** @brief Consultora del sexo del Individuo
      \pre cierto
      \post El resultado es cierto si el parametro implícito es hombre y 
      falso si es mujer
      \coste Constante 
  */
	bool recoge_sex();

  /** @brief Consultora de los cromosomas sexuales del Individuo
      \pre cierto
      \post El parametro implicito pasa a tener el valor de los cromosomas sexuales del Individuo
      \coste Constante 
  */
	Cromosomas obtener_cromosomas_sex();

  /** @brief Consultora de los cromosomas normales del Individuo
      \pre cierto
      \post El parametro implicito pasa a tener el valor de los cromosomas normales del Individuo
      \coste Constante 
  */
	Cromosomas obtener_cromosomas();

  // Modificadoras
  /** @brief Modificadora del identificador nombre del Individuo
      \pre cierto
      \post El parámetro implícito pasa a tener el nombre como nombre
		  \coste Constante  */
	void asigna_nombre(string bname);

  /** @brief Modificadora de los cromosomas normales del Individuo
      \pre cierto
      \post El parámetro implícito pasa a tener los cromosomas normales del cromosoma del parametro
		  \coste Constante  */
	void asignar_cromnorm(Cromosomas bcroms);

  /** @brief Modificadora de los cromosomas sexuales del Individuo
      \pre cierto
      \post El parámetro implícito pasa a tener los cromosomas sexuales del cromosoma del parametro
	*/
	void asignar_cromsex(Cromosomas bsex);

   /** @brief Modificadora del sexo del Individuo
      \pre cierto
      \post El parámetro implícito pasa a tener el sexo del booleano
		  \coste Constante  */
	void asigna_sex(bool sex);

  /** @brief Modificadora de los cromosomas sexuales del Individuo
      \pre cierto
      \post El parámetro implícito pasa a tener los cromosomas sexuales y normales creados 
		  \coste Constante  */
 	void asignar_cromosomas(bool bsex); 

  /** @brief Modificadora del cromosoma del Individuo
      \pre cierto
      \post El parámetro implícito pasa a tener los valores generales de la Especie guardados en el Cromosomas c
		  \coste Constante  */
 	void asignar_parametros(Cromosomas c);
};
#endif
