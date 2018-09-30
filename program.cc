/** @file program.cc

    @brief Programa principal

    Asumimos que las expresiones leídas son siempre correctas, ya que
    no incluyo comprobaciones al respecto.
*/

#include "Especie.hh"

int main () {
    string s;
    Especie e;
    Cromosomas c;
    Familias fam;
    c.definir_especie();
    int M;
    string name;    //Nombre del individuo
    cin >> M;   //Numero de individuos
    for (int i = 0; i < M; ++i) {
        cin >> name;
        e.anadir_individuo(c,fam,name);
    }
    cin >> s;   //Comando a realizar
    while (s != "acabar") {
        if (s != "") {
            if (s == "anadir_individuo") {
                    cin >> name;                    
                    cout << s << " " << name << endl;                    
                    e.anadir_individuo(c,fam,name);
            } else if (s == "escribir_poblacion") {
                    cout << s << endl;
                    e.escribir_individuos(fam);
            } else if (s == "reproduccion_sexual") {
                    cout << s; 
                    string madre, padre, hijo;
                    cin >> madre >> padre >> hijo;
                    cout << " " << madre << " " << padre << " " << hijo << endl;
                    e.reproducir_individuos(c,fam,madre,padre,hijo);
            } else if (s == "escribir_arbol_genealogico") {
                    cin >> name;
                    cout << s << " " << name << endl;
                    e.escribir_arbol_genealogico(fam,name);
            } else if (s == "completar_arbol_genealogico") {
                    cout << s << " ";    
                    fam.completar_arbol();
            } else if (s == "escribir_genotipo") {
                    cin >> name;
                    cout << s << " "; 
                    e.escribir_individuo_genotipo(name);
            }            
        }
        cin >> s;
    }
    cout << s << endl;
}