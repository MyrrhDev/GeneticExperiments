/** @file Cromosomas.cc
    @brief Código de la clase Cromosomas
*/

#include "Cromosomas.hh"

Cromosomas::Cromosomas()
{
}

void Cromosomas::definir_especie ()
{
    // Obtiene todos los parametros de la Especie de la que trataremos
    // incluyendo N pares de cromosomas “normales”, el punto de corte a 
    // utlizar en la reproduccion, el tamaño de los cromosomas normales
    // y los tamaños del cromosoma X e Y.
    cin >> N;
    cin >> punto_de_corte;
    vector <int> tempv(N+2);
    int i = 1;
    int num;
    while (i <= N) {
        cin >> num;
        tempv[i] = num;
        ++i;
    }
    normales = tempv;
    cin >> lx;
    cin >> ly;
}

int Cromosomas::obtener_N()
{
    // Obtiene el numero de pares de cromosomas normales
    // Inv: El parametro implicito, el cromosoma, se mantiene igual
    return N;
}

void Cromosomas::crear_cromosomas(Cromosomas& norm,Cromosomas f, Cromosomas n, int elegirm, int elegirp, int limit, int position) 
{
    //Esta operacion se encarga de crear nuevos cromosomas normales de los cromosomas f y n
    //provenientes de madre y padre
    int size = f.normales[position];
    Cromosoma onee;
    Cromosoma twoo;
    
    map <int, Crom>::iterator it = f.genotipo.find(position), it2 = n.genotipo.find(position);    
    
    if (elegirm == 0) onee = it->second.one;
    else if (elegirm == 1) onee = it->second.two;
    
    if (elegirp == 0) twoo = it2->second.one;
    else if (elegirp == 1) twoo = it2->second.two;
    
    while (limit < size) {
        swap(onee[limit],twoo[limit]);
        ++limit;
    }
    Crom cromoready;
    cromoready.one = onee;
    cromoready.two = twoo;

    norm.genotipo.insert(make_pair(position, cromoready));
}


void Cromosomas::obtener_valores(Cromosomas x) 
{
    //Copia los valores esenciales de la Especie: N pares de cromosomas “normales”, el punto de corte a 
    // utlizar en la reproduccion, el tamaño de los cromosomas normales
    // y los tamaños del cromosoma X e Y guardados en el Cromosoma x
    //al parametro implicito
    N = x.N;
    punto_de_corte = x.punto_de_corte;
    lx = x.lx;
    ly = x.ly;
    normales = x.normales;
}

Cromosomas Cromosomas::crear_cromosomas_sexs(Cromosomas m, Cromosomas p, int elegirm, int elegirp, int limit) 
{
    //Esta operacion se encarga de escoger los cromosomas correctos
    //y mezclarlos de acuerdo al punto de corte y la medida de los cromosomas, en su fin,
    //crea un nuevo cromosoma. 
    Cromosomas prog;
    prog.obtener_valores(m);
    
    vector <int> mom;
    vector <int> dad;
    if (elegirm == 0) mom = m.gensexs.first;
    else if (elegirm == 1) mom = m.gensexs.second;
    
    if (elegirp == 0) dad = p.gensexs.first;
    else if (elegirp == 1) dad = p.gensexs.second;
    
    int i = limit;
    while (i < m.punto_de_corte) {
        swap(mom[i],dad[i]);
        ++i;
    }    
    prog.gensexs.first = mom;
    prog.gensexs.second = dad;
    return prog;
}

void Cromosomas::anadir_cromosoma_sexs(bool bsex) 
{
    //Se añaden los cromosomas sexuales que entran por el canal estandar 
    //en el parametro implicito dependiendo del bsex, si es false, entonces
    //es un Individuo mujer y si es true es un Individuo hombre
    int i = 0;
    Cromosoma sexX1 (lx);
    
    while (i < lx) {
        cin >> sexX1[i];
        ++i;
    }
    gensexs.first = sexX1;
    i = 0;
    if (bsex) { 
        Cromosoma sexXY (ly);
        while (i < ly) {
            cin >> sexXY[i];
            ++i;
        }
        gensexs.second = sexXY;
    } else {
        Cromosoma sexXY (lx);
        while (i < lx) {
            cin >> sexXY[i];
            ++i;
        }
        gensexs.second = sexXY;
    }
}

int Cromosomas::consultar_cromnorm (int i) 
{
  // Inv:  El vector normales se mantiene igual, sólo se devuelve el valor consultado 
  // dependiendo del valor i
  // Cota: tamaño de normales
    return normales[i];
}


void Cromosomas::anadir_cromosomas()
{
    //Se añaden los cromosomas normales que entran por el canal estandar 
    //en el parametro implicito. Se evalua el tamaño de cada uno accediendo a la funcion aux
    //consultar_cromnorm(int i) donde i es la posicion donde se encuentra el valor.
    string name;
    int i = 1;
    int newname = 1;
    int Nsize = N;
    Crom paircrom;
    while (i <= Nsize) {
        int size = consultar_cromnorm(i);
        int vectint = 0;
        int num;
        Cromosoma cromnorm(size);
        while (vectint < size) {
            cin >> num;
            cromnorm[vectint] = num;
            ++vectint;
        }
        Cromosoma cromnorm1(size);
        vectint = 0;
        while (vectint < size) {
            cin >> num;
            cromnorm1[vectint] = num;
            ++vectint;
        }
        paircrom.one = cromnorm;
        paircrom.two = cromnorm1;
        genotipo.insert(make_pair(newname, paircrom));
        ++newname;
        cromnorm.clear();
        cromnorm1.clear();
        ++i;
    }   
}

void Cromosomas::escribir_cromosomas_sexs (bool bsex) const 
{
    // Esta operación simplemente escribe los cromosomas sexuales
    // dependiendo del sexo del Individuo
    int size = gensexs.first.size();
    cout << "  X:";
    for (int i = 0; i < size; ++i) {
        cout << " " << gensexs.first[i];
    }
    cout << endl;
    if (bsex) {
        size = gensexs.second.size();
        cout << "  Y:";
    } else {
        cout << "  X:";
    } 
    for (int i = 0; i < size; ++i) {
        cout << " " << gensexs.second[i];
    }
    cout << endl;
}

void Cromosomas::escribir_cromosomas () const 
{
    // Esta operación simplemente escribe los cromosomas normales y los ordena
    // en pares " .1" y " .2" por cada numero de cromosoma, usando el identificador del
    // mapa genotipo.
    for(map <int, Crom>::const_iterator it = genotipo.begin(); it != genotipo.end(); ++it) {
        cout << "  " << it->first << ".1:";
        int size = it->second.one.size();
        for (int i = 0; i < size; ++i) {
            cout << " " << it->second.one[i];
        }
        cout << endl;
        cout << "  " << it->first << ".2:";
        size = it->second.two.size();
        for (int i = 0; i < size; ++i) {
            cout << " " << it->second.two[i];
        }
        cout << endl;
    }
}