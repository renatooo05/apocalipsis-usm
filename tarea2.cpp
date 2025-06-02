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

    Habitacion* hijoIZQ = NULL;
    Habitacion* hijoMED = NULL;
    Habitacion* hijoDER = NULL;

};


struct Enemigo {
    string nombre;
    int vida;
    int ataque;
    float precision;
    float probabilidad;
};

struct Evento {
    string nombre;
    float probabilidad;
    string descripcion;

    string opcionA;
    string efectoA;

    string opcionB;
    string efectoB;
};

struct Mejoras {
    int vidaExtra = 0;
    float precisionExtra = 0;
    int ataqueExtra = 0;
    int recuperacionExtra = 0;
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
            else{
                if(!nombreEve.empty()) nombreEve += " ";
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
                exit(EXIT_FAILURE);
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
    int pos = 0;

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

Evento* leerEventos(ifstream &map, int & eventosTotales){
    string linea;
    if(!getline(map,linea)){
        cerr << "Error al obtener la cantidad de eventos\n";
        exit(EXIT_FAILURE);
    }

    eventosTotales = stoi(linea);
    Evento* eventos = new Evento[eventosTotales];

    for(int i = 0; i < eventosTotales; ++i){
        do{
            if (!getline(map,linea)){
            cerr << "Error al leer el evento " << i + 1 << endl;
            exit(EXIT_FAILURE);
            }

        }while (linea.empty() || linea[0] != '&');

    getline(map, eventos[i].nombre);

    getline(map, linea);
    string innecesario;
    stringstream(linea) >> innecesario >> eventos[i].probabilidad;

    getline(map, eventos[i].descripcion);

    //Opcion A
    getline(map, linea);
    size_t posA = linea.find(':');
    eventos[i].opcionA = (posA != string::npos) ? linea.substr(posA + 1) : linea;
    eventos[i].opcionA.erase(0, eventos[i].opcionA.find_first_not_of(" "));

    string efectoA1, efectoA2;
    getline(map, efectoA1);
    getline(map, efectoA2);
    eventos[i].efectoA = efectoA1 + "\n" + efectoA2;

    //Opcion B
    getline(map, linea);
    size_t posB = linea.find(':');
    eventos[i].opcionB = (posB != string::npos) ? linea.substr(posB + 1) : linea;
    eventos[i].opcionB.erase(0, eventos[i].opcionB.find_first_not_of(" "));


    string efectoB1, efectoB2;
    getline(map, efectoB1);
    getline(map, efectoB2);
    eventos[i].efectoB = efectoB1 + "\n" + efectoB2;
    }

    return eventos;
}


Mejoras leerMejorasDeCombate(ifstream& map){
    string linea;
    Mejoras mejora;

    while (getline(map, linea)){
        if (linea == "FIN DEL ARCHIVO") break;
        if (linea.empty()) continue;
    

        stringstream palabrasPorLinea(linea);
        char simbolo;
        float valor;
        string tipoDeMejora;

        palabrasPorLinea >> simbolo >> valor >> tipoDeMejora;

        if(tipoDeMejora == "Vida")
            mejora.vidaExtra = static_cast<int>(valor);
        else if(tipoDeMejora == "Precision")
            mejora.precisionExtra = valor;
        else if(tipoDeMejora == "Ataque")
            mejora.ataqueExtra = static_cast<int>(valor);
        else if(tipoDeMejora == "Recuperacion")
            mejora.recuperacionExtra = static_cast<int>(valor);
    }
    return mejora;
}


int main(){
    ifstream map("ejemplo.map");
    if(!map.is_open()){
        cerr << "Error al abrir el archivo"<< endl;
        return 1;
    }

    string linea;
    while(getline(map, linea)){
        if (linea == "HABITACIONES") break;

    }

    int n;
    Habitacion* habitaciones = leerHabitaciones(map, n);

    while (getline(map,linea)){
        if (linea == "ARCOS") break;
    }

    arcosXhabitaciones(map, habitaciones, n);
    
    while (getline(map, linea)){
        if (linea == "ENEMIGOS") break;
    }

    int e;

    Enemigo* enemigos = leerEnemigos(map, e);

    while (getline(map, linea)) {
    if (linea == "EVENTOS") break;
}

while (getline(map, linea)) {
    if (linea.find("MEJORAS DE COMBATE") != string::npos) break;
}

    Mejoras mejoras = leerMejorasDeCombate(map);

    // Imprimir para probar
    cout << "\nMejoras leídas:\n";
    cout << " + Vida: " << mejoras.vidaExtra << endl;
    cout << " + Precision: " << mejoras.precisionExtra << endl;
    cout << " + Ataque: " << mejoras.ataqueExtra << endl;
    cout << " + Recuperacion: " << mejoras.recuperacionExtra << endl;
    
    delete[] habitaciones;
    delete[] enemigos;
    

    map.close();
    return 0;

}
