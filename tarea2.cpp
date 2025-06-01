#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>

using namespace std;

struct Enemigo {
    string nombre;
    int vida;
    int ataque;
    float precision;
    float probabilidad;
};


struct Habitacion{
    int id;
    string nombre;
    string descripcion;
    string tipo;   

    Habitacion* hijoIZQ = NULL;
    Habitacion* hijoMED = NULL;
    Habitacion* hijoDER = NULL;

};



Habitacion* leerHabitaciones(ifstream& map, int& N){
    string linea;
    if (!getline(map, linea)) {
        cerr << "Error al leer el numero de habitaciones" << endl;
        exit(EXIT_FAILURE);
    }

    N = stoi(linea);
    Habitacion* habitaciones = new Habitacion[N];
    for (int i = 0; i < N; ++i){
        do {
            if (!getline(map, linea)) {
                cerr << "Error al leer la habitacion " << i + 1 << endl;
                exit(EXIT_FAILURE);
            }
        } while (linea.empty());

        stringstream palabrasPorLinea(linea);
        int id;
        palabrasPorLinea >> id;

        string palabra;
        string nombreEve = "";
        string tipoEve = "";
        string descripcionEve = "";

        while (palabrasPorLinea >> palabra){
            if (palabra[0] == '('){
                tipoEve = palabra.substr(1, palabra.size() - 2);
                break;
            }
            else if(!nombreEve.empty()){
                nombreEve += " ";
                nombreEve += palabra;
            }
        }

        if (!getline(map, descripcionEve)){
            cerr << "Error al leer la descripcion de la habitacion " << i + 1 << endl;
            exit(EXIT_FAILURE);
        }

        
        habitaciones[id].id = id;
        habitaciones[id].nombre = nombreEve;
        habitaciones[id].descripcion = descripcionEve;
        habitaciones[id].tipo = tipoEve;

        
    }

    return habitaciones;
}


void arcosXhabitaciones(ifstream& map, Habitacion* habitaciones, int N){
    string linea;

    if (!getline(map, linea)) {
        cerr << "Error al leer los arcos" << endl;
        exit(EXIT_FAILURE);
    }

    int ArcosTotales = stoi(linea);
    for (int i = 0; i < ArcosTotales; ++i){
        do {
            if (!getline(map, linea)){
                cerr << "Error al leer el arco" << i + 1 <<endl;
                exit(EXIT_FAILURE)
            }
        } while (linea.empty());

        size_t flechita = linea.find("->");
        if (flechita == string::npos) {
            cerr << "No se encontro la flechita -> " << i + 1 << endl;
            exit(EXIT_FAILURE);
        }

        int altura = stoi(linea.substr(0, flechita));
        int hijoEvento = stoi(linea.substr(flechita + 2));

        Habitacion* padre = &habitaciones[altura];
        Habitacion* hijo = &habitaciones[hijoEvento];

        if (padre->hijoIZQ == NULL){
            padre->hijoIZQ = hijo;        
        }
        else if (padre->hijoMED == NULL){
            padre->hijoMED = hijo;
        }
        else if (padre->hijoDER == NULL){
            padre->hijoDER = hijo;
        }
        else {
            cerr << "Error: La habitacion " << padre->id << " ya tiene 3 hijos." << endl;
            exit(EXIT_FAILURE);
        }
        
    }
}

Enemigo* leerEnemigos(ifstream& map, int & E){
    string linea;
    if (!getline(map, linea)){
        cerr << "Error al leer la cantidad de enemigos\n";
        exit(EXIT_FAILURE);
    }
    E = stoi(linea);
    Enemigo* enemigos = new Enemigo[E];

    for(int i = 0; i < E; ++i){
        do {
            if (!getline(map, linea)){
        cerr << "Error al leer los datos del enemigos\n";
        exit(EXIT_FAILURE);
        }
    } while(linea.empty());

    stringstream palabrasXlinea(linea);
    string parteAux;
    string enemyChrter[5];
    int pos = 0

    while (getline(palabrasXlinea, parteAux, '|') && pos < 5){
        size_t inicioPalabra = parteAux.find_first_not_of(" ");
        enemyChrter[pos++] = (inicioPalabra == string::npos) ? "" : parteAux.substr(inicioPalabra);     
    } 

    enemigos[i].nombre = enemyChrter[0];
    
    //que dolor de cabeza estas proximas lineas
    string innecesario;
    stringstream(enemyChrter[1]) >> innecesario >> enemigos[i].vida;
    stringstream(enemyChrter[2]) >> innecesario >> enemigos[i].ataque;
    stringstream(enemyChrter[3]) >> innecesario >> enemigos[i].precision;
    stringstream(enemyChrter[4]) >> innecesario >> enemigos[i].probabilidad;
    }

    return enemigos;

}
