/** @file Familias.cc
    @brief Código de la clase Familias
*/

#include "Familias.hh"

Familias::Familias(){

    
}

void Familias::insertar_familias(string hijo, string padre, string madre) {
    //Crea un par de padres e hijo y los inserta en el parametro implicito 
    Padres couple;
    couple.first = padre;
    couple.second = madre;
    FamNuclear.insert(make_pair(hijo, couple));
}

void Familias::consultar_padres(string hijo, string& padre, string& madre) {
    //Consulta el parametro implicito por la variable hijo, y 
    //devuelve en las variables padre y madre los valores de sus Padres en el mapa
    map <string, Padres>::iterator it = FamNuclear.find(hijo);
    padre = it->second.first;
    madre = it->second.second;
}

void Familias::leer_arbol_parcial(Arbre<string>& a){
    //Lee desde el canal estandar el arbol parcial a comparar
    Arbre<string> a1;
    Arbre<string> a2;
    string x;
    cin >> x;
    if (x!= "$") {
        leer_arbol_parcial(a1);
        leer_arbol_parcial(a2);
        a.plantar(x,a1,a2);
    } else a.plantar("$", a1, a2);  
}


void Familias::leer_arbol_general(Arbre<string>& b, string hijo){
  map <string, Padres>::iterator it = FamNuclear.find(hijo);
  Arbre<string> b1;
  Arbre<string> b2;
  if (hijo == "$") {
      b.plantar("$", b1, b2);
  } else {
    string padre = it->second.first;
    leer_arbol_general(b1,padre);
    string madre = it->second.second;
    leer_arbol_general(b2,madre);
    b.plantar(hijo,b1,b2);
  }
}

bool Familias::exist_hijo(string hijo) {
    map <string, Padres>::iterator it = FamNuclear.find(hijo);
    if (it == FamNuclear.end()) return false;
    else return true;
}

bool Familias::buscar_en_arbol(Arbre<string> a, string parent) {
    // a=A, el arbol general donde buscamos parent
    // el resultado indica si parent esta en el arbol A o no
    bool b;
    if (a.es_buit()) b=false;           
    else if (a.arrel()==parent) b=true;     
    else{                               
        Arbre<string> a1,a2;                 
        a.fills(a1,a2);
        b=buscar_en_arbol(a1,parent);
        if (not b) b= buscar_en_arbol(a2,parent);
    }
    return b;
}

bool Familias::tiene_padres(string person) {
    map <string, Padres>::iterator it = FamNuclear.find(person);
    //Person ya existe, porque ya ha sido revisado antes de usar esta funcion.
    
    if (it->second.first == "$" and it->second.second == "$") return false;
    else return true;
}

bool Familias::mismos_padres(string madre, string padre) {
    map <string, Padres>::iterator it = FamNuclear.find(madre), it2 = FamNuclear.find(padre);
    if ((it->second.first == it2->second.first) or  (it->second.second == it2->second.second)) return true;
    else return false;
}

bool Familias::son_familia (string poshijo, string posascend) {
    //Se construye el arbol genealogico del poshijo, y se busca el posascend en este arbol
    Arbre<string> genpadre;
    leer_arbol_general(genpadre, poshijo);
    bool encontrado = buscar_en_arbol(genpadre, posascend);
    return encontrado;
}

bool Familias::es_parcial(Arbre<string> a, Arbre<string> b, string left, string right) {
    bool igual;
    //Los elementos de a si no son $ tienen que estar en la misma 
    //ubicacion en b, a es el arbol parcial de b. b es un arbol 
    //general genealogico.
    if (left == "$") {
        Arbre<string> a1,a2;
        Arbre<string> b1,b2;
        a.fills(a1,a2);
        b.fills(b1,b2);
        if (a1.es_buit() or a2.es_buit()) {
            left = "";
            right = "";
            igual = true;
        } 
    } else if (right == "$") {
        Arbre<string> a1,a2;
        Arbre<string> b1,b2;
        a.fills(a1,a2);
        b.fills(b1,b2);        
        if (b1.es_buit() or b2.es_buit()) {
            igual = false;
        }
    } else if (left != right) { //Ninguno es $
        igual = false;
    } else {
        Arbre<string> a1,a2;
        Arbre<string> b1,b2;
        a.fills(a1,a2);
        b.fills(b1,b2);
        left = a1.arrel();
        right = b1.arrel();
        igual = es_parcial(a1,b1,left,right);
        if (igual) {
            left = a2.arrel();
            right = b2.arrel();
            igual = es_parcial(a2,b2,left,right); //Si la parte izq es toda igual, exploramos la derecha
        }   
    }
    return igual;
}

void Familias::escribir_arbol_completo(Arbre<string>& input, Arbre<string>& general) {
  if (not general.es_buit()) {
    Arbre<string> a1, a2;
    Arbre<string> b1, b2;
    string x = general.arrel();
    string y;
    if (not input.es_buit()) {
        y = input.arrel();
        input.fills(a1,a2);  // a1 = hijo izquierdo(input); a2 = hijo derecho(general);
        if (y == "$" and x != "$") cout << " *" << x << "*";
        else if (y != "$" and x != "$") cout << " " << x;
        else if (y == "$" and x == "$") cout << " " << x;
    } else {
        if (x != "$") cout << " *" << x << "*";
        else cout << " " << x;
    }
    general.fills(b1,b2);  // b1 = hijo izquierdo(input); b2 = hijo derecho(general);
    escribir_arbol_completo(a1,b1); 
    escribir_arbol_completo(a2,b2);
    general.plantar(x,b1,b2);    
  }
}

void Familias::completar_arbol() {
    Arbre<string> input;
    leer_arbol_parcial(input);
    string hijo = input.arrel();
    cout << hijo << endl;
    bool existen = exist_hijo(hijo);
    if (not existen) cout << "  no es arbol parcial" << endl;
    else {
        Arbre <string> general;
        leer_arbol_general(general,hijo); 
        //Construyo el arbol general del hijo de la info del map
        string aa = input.arrel();
        string bb = general.arrel();
	bool es_arbol_parcial = es_parcial(input, general, aa, bb);
	if (not es_arbol_parcial) cout << "  no es arbol parcial" << endl;
	else {
            cout << " ";
            escribir_arbol_completo(input,general);
            cout << endl;
        }
    }
}

void Familias::ordernar_niveles(string person, vector <list <string> >& niveles, int n) {
    if (person != "%") {
        int size = niveles.size();
        if (size < n) {
            list <string> hol; 
            hol.insert(hol.end(), person);
            niveles.push_back(hol);
        } else {
            list<string>::iterator lit = niveles[n-1].end();
            niveles[n-1].insert(lit, person);
        }        
        map <string, pair<string,string> >::iterator it, it1, it2;
        it = FamNuclear.find(person);
        it1 = FamNuclear.find(it->second.first);
        if (it1 != FamNuclear.end()) {
            person = it1->first;
        } else person = "%";
            ordernar_niveles(person,niveles,n+1);
        
        it2 = FamNuclear.find(it->second.second);
        string person2;
        if (it2 != FamNuclear.end()) {
           person2 = it2->first;            
        } else person2 = "%";
            ordernar_niveles(person2,niveles,n+1);
    }
}


void Familias::escribir_niveles(vector <list <string> >& niveles) {
    for (int i = 0; i < niveles.size(); ++i) {
        cout << "  Nivel " << i << ":";
        list<string>::const_iterator it = niveles[i].begin();
        while (it != niveles[i].end()) {
            cout << " " << *it;
            ++it;
        }       
        cout << endl;
    }
}

void Familias::escribir_arbol_niveles(string hijo) {
    vector <list <string> > niveles;
    ordernar_niveles(hijo,niveles,1);
    escribir_niveles(niveles);
}