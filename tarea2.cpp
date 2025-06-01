#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>

using namespace std;

struct Habitacion{
    int id;
    string nombre;
    string descripcion;
    string tipo;   

    Habitacion* hijoIZQ = nullptr;
    Habitacion* hijoMED = nullptr;
    Habitacion* hijoDER = nullptr;

};



Habitacion* leerHabitaciones(ifstream& fin, int& N){
    string linea;
    if (!getline(fin, linea)) {
        cerr << "Error al leer el numero de habitaciones" << endl;
        exit(EXIT_FAILURE);
    }

    N = stoi(linea);
    Habitacion* habitaciones = new Habitacion[N];
    for (int i = 0; i < N; ++i){
        do {
            if (!getline(fin, linea)) {
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

        if (!getline(fin, descripcionEve)){
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

