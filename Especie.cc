/** @file Especie.cc
    @brief Código de la clase Especie
*/

#include "Especie.hh"

 Especie::Especie(){
 }

bool Especie::existe_individuo (string name) const {
    map <string, Individuo, less<string> >::const_iterator it = registro.find(name);
    if (it == registro.end()) return false;
    else return true;
}


void Especie::insertar_especie(Individuo ind,string bname) {
    registro.insert(make_pair(bname, ind));
}

void Especie::anadir_individuo(Cromosomas c,Familias& fam, string bname) {
    // Añade un individuo y para ello, emplea la operación privada "insertar_especie" que 
    // despues de recibir la informacion, lo guarda en el registro. Tambien usa la funcion de "inserta_familias"
    // de la Clase Familias para insertarlo en el mapa de las familias nucleares
    Individuo persona;
    string sex;
    cin >> sex;
    
    bool is_sex;
    if (sex == "X") is_sex = false; //mujer
    else if (sex == "Y") is_sex = true; //hombre
    
    persona.asigna_nombre(bname);
    persona.asigna_sex(is_sex);
    persona.asignar_parametros(c);
    persona.asignar_cromosomas(is_sex);
    
    bool exist = existe_individuo(bname);
    if (exist) {
        cout << "  error" << endl;
    }
    else {
        insertar_especie(persona,bname);
        string pare = "$";
        fam.insertar_familias(bname,pare,pare);
    }
}

void Especie::escribir_individuo_genotipo (string name) {
    // Esta operación recoge los Cromosomas del individuo,
    // mediante unas llamadas a funciones de la clase Individuo "obtener_cromosomas" y "obtener_cromosomas_sex"
    // y escribiendolas mediante las funciones "escribir_cromosomas_sexs" y"escribir_cromosomas" de la
    // clase Cromosomas.
    bool exist = existe_individuo(name);
    if (not exist) {
        cout << name << endl;
        cout << "  error" << endl;
    } else {
        Cromosomas c,s;
        map <string, Individuo, less<string> >::iterator it = registro.find(name);
        cout << it->first << endl;
        
        Individuo ind = it->second;
        s = ind.obtener_cromosomas_sex();
        c = ind.obtener_cromosomas();
        bool bsex = ind.recoge_sex();
        s.escribir_cromosomas_sexs(bsex);
        c.escribir_cromosomas();
    }
}

void Especie::escribir_individuos(Familias f) {
    for (map <string, Individuo, less<string> >::iterator it2 = registro.begin(); it2 != registro.end(); ++it2) {
        cout << "  " << it2->first << " ";
        bool bsex = it2->second.recoge_sex();
        if (not bsex) cout << "XX ";
        else cout << "XY ";
        string padre, madre;
        f.consultar_padres(it2->first,padre,madre);
        cout << "(" << padre << "," << madre << ")" << endl;
    }
}


bool Especie::individuos_reproduccion(string madre, string padre, string hijo) {
    //Revisa si existen los individuos madre y padre. Revisa si existe hijo tambien.
    bool exist = existe_individuo(madre);
    if (exist) {
        exist = existe_individuo(padre);
        if (exist) {
            exist = existe_individuo(hijo);
            if (not exist) return true;
            else return false;
        } else return false;
    } else return false;
} 


bool Especie::same_sex(string madre, string padre) {
    map <string, Individuo, less<string> >::iterator it = registro.find(madre), it2 = registro.find(padre);
    //Los individuos existen
    //Se devuelve false solo si el primer string es mujer y el segundo es hombre    
    bool bmadre = it->second.recoge_sex();
    bool bpadre = it2->second.recoge_sex();
    if (not bmadre and bpadre) return false;
    else return true;
}   

bool Especie::se_puede_reproducir(Familias f, string madre, string padre, string hijo) {
  // Ésta es la operación más importante del módulo. Dados dos nombres de Individuos, hay
  // que decidir primero si: existen. Por eso, uso la operacion auxiliar "individuos_reproduccion"
  // en la parte privada. Luego, de existir correctamente, se evalua si son del sexo correcto
  // mediante la operacion privada "same_sex". Luego, de cumplir con las condiciones de la operacion,
  // se examina si sus padres/antecesores coinciden, es decir, son familia. Finalmente, si se
  // encuentra que no son familia de ningun tipo (la madre y el padre), entonces se devuelve un true
  // como valor del bool.
    bool existen = individuos_reproduccion(madre,padre,hijo);
    if (not existen) {
        cout << "  error" << endl;
        return false;
    } else {
        bool bsame_sex = same_sex(madre,padre);
        if (bsame_sex) {
            cout << "  no es posible reproduccion" << endl;
            return false;
        } else {
           bool mparents = f.tiene_padres(madre);
           bool pparents = f.tiene_padres(padre);
           bool familia;           
           if (not mparents and not pparents) return true; 
           else if (mparents and not pparents) {
               familia = f.son_familia(madre,padre);
               if (not familia) return true;
               else {
                    cout << "  no es posible reproduccion" << endl;
                    return false;
                }
           } else if (not mparents and pparents) {
               familia = f.son_familia(padre,madre);
               if (not familia) return true;
               else {
                   cout << "  no es posible reproduccion" << endl;
                   return false;
                }
           } else { //los dos tienen antecesores
               bool mismos_parents = f.mismos_padres(madre,padre);
               if (mismos_parents) {
                    cout << "  no es posible reproduccion" << endl;
                    return false;
               } else {
                    familia = f.son_familia(madre,padre);
                    bool familia2 = f.son_familia(padre,madre);
                    if (not familia and not familia2) return true;
                    else {
                        cout << "  no es posible reproduccion" << endl;
                        return false;
                    }
                }
            }
        }
    }
}


void Especie::reproducir_individuos(Cromosomas c,Familias& fam, string madre, string padre, string hijo) {
    bool reproducir = se_puede_reproducir(fam,madre,padre,hijo);
    // Esta operacion revisa si los Individuos se pueden reproducir usando la funcion privada "se_puede_reproducir"
    // y de ser asi, se obtienen los Cromosomas sexuales y normales
    // de ambos padres madre y padre para comenzar la reproduccion.
    
    int Nc = c.obtener_N();
    int i = 0;
    int elegir1, elegir2, limit;
        
    if (reproducir) {
        Individuo person;        
        person.asigna_nombre(hijo);
        map <string, Individuo, less<string> >::iterator it = registro.find(madre), it2 = registro.find(padre);

        Cromosomas m = it->second.obtener_cromosomas_sex();
        Cromosomas p = it2->second.obtener_cromosomas_sex();
        Cromosomas o = it->second.obtener_cromosomas();
        Cromosomas n = it2->second.obtener_cromosomas();
        Cromosomas hsex,norm;
        
       while (i <= Nc) {            
            cin >> elegir1 >> elegir2 >> limit;
            //Entran los numeros en cada ciclo del bucle y dependiendo de si es el primer par de Cromosomas
            //sexuales, se entra en el primer if, y para los siguientes se entran en el else para 
            //poder crear en lo que queda del bucle los Cromosomas normales
            if (i == 0) {
                bool bsex;
                if (elegir2 == 1) bsex = true; //hombre XY
                else if (elegir2 == 0) bsex = false; //mujer XX
                person.asigna_sex(bsex);
                hsex = hsex.crear_cromosomas_sexs(m,p,elegir1,elegir2,limit);
                person.asignar_cromsex(hsex);
           } else { 
               norm.crear_cromosomas(norm,o,n,elegir1,elegir2,limit,i);
            }
            ++i;
        }
        norm.obtener_valores(m);
        person.asignar_cromnorm(norm);
        insertar_especie(person,hijo);
        fam.insertar_familias(hijo,padre,madre);
        //De ser que no se pueden reproducir, se entra en un bucle que solo recoge datos pero no hace nada con ellos
    } else if (not reproducir) { 
        while (i <= Nc) {
            cin >> elegir1 >> elegir2 >> limit;
            ++i;
        }
    }       
}

void Especie::escribir_arbol_genealogico(Familias f, string name) {
    //Esta operacion escribe el arbol genealogico del individuo, primero verificando que existe usando
    //la funcion privada "existe_individuo" y luego "escribir_arbol_niveles" de la Clase Familias
    bool existe = existe_individuo (name);
    if (not existe) cout << "  error" << endl;
    else {
        f.escribir_arbol_niveles(name);    
    }
    
}

