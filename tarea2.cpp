#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <ctime>

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

typedef string tElemCola;

struct NodoCola {
    tElemCola dato;
    NodoCola* sig;
};

class Jugador {
    private :
    int vida ;
    int ataque ;
    float precision ;
    int recuperacion ;

    public:
    Jugador(){
        vida = 100;
        ataque = 5;
        precision = 0.8;
        recuperacion = 5;
    }
    int getVida() const { return vida; }
    int getAtaque() const { return ataque; }
    float getPrecision() const { return precision; }
    int getRecuperacion() const { return recuperacion; }

    void setVida(int v) { vida = v; }
    void cambiarVida(int cambio) { vida += cambio; }
    void setAtaque(int a) { ataque = a; }
    void cambiarAtaque(int cambio) { ataque += cambio; }
    void setPrecision(float p) { precision = p; }
    void setRecuperacion(int r) { recuperacion = r; }
    
    void mostrarStats() const {
        cout << "Vida: " << vida << endl;
        cout << "Ataque: " << ataque << endl;
        cout << "Precision: " << precision << endl;
        cout << "Recuperacion: " << recuperacion << endl;
    }

};

class tCola {
private:
    NodoCola* frente;
    NodoCola* final;
    int largo;

public:
    tCola() {
        frente = final = NULL;
        largo = 0;
    }

    void clear() {
        while (frente != NULL) {
            dequeue();
        }
    }

    int enqueue(tElemCola item) {
        NodoCola* nuevo = new NodoCola{item, NULL};
        if (final != NULL)
            final->sig = nuevo;
        else
            frente = nuevo;
        final = nuevo;
        largo++;
        return 1;
    }

    void dequeue() {
        if (frente == NULL) return;
        NodoCola* temp = frente;
        frente = frente->sig;
        delete temp;
        largo--;
        if (frente == NULL)
            final = NULL;
    }

    tElemCola frontValue() {
        if (frente != NULL)
            return frente->dato;
        return "";
    }

    int size() {
        return largo;
    }

    bool vacia() {
        return frente == NULL;
    }
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
        if (linea == "FIN DE ARCHIVO") break;
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

void otorgarMejora(Jugador& jugador, const Mejoras& mejoras) {
    cout << "\n¡Has ganado el combate!\n";
    cout << "Recuperas 3 puntos de vida tras el combate.\n";
    jugador.cambiarVida(3);  

    int eleccion = 0;
    while (eleccion != 1 && eleccion != 2) {
        cout << "\nDebes decidir una mejora:\n";
        cout << "1. Recuperar " << mejoras.vidaExtra << " de vida.\n";
        cout << "2. Aumentar ataque en " << mejoras.ataqueExtra << ".\n";
        cout << "Elige una opción: ";
        cin >> eleccion;
        if (eleccion == 1) {
            jugador.cambiarVida(mejoras.vidaExtra);  
            cout << "¡Recuperaste " << mejoras.vidaExtra << " de vida!\n";
        } else if (eleccion == 2) {
            jugador.cambiarAtaque(mejoras.ataqueExtra);  
            cout << "¡Aumentaste tu ataque en " << mejoras.ataqueExtra << "!\n";
        } else {
            cout << "Elección inválida. Intenta de nuevo.\n";
        }
    }
}



bool combate(Jugador& jugador, Enemigo* enemigos, int totalEnemigos, Mejoras mejoras) {
    Enemigo enemigosElegidos[2];
    int seleccionados = 0;

    while (seleccionados < 2) {
        float r = (float) rand() / RAND_MAX;
        float acumulada = 0;
        for (int i = 0; i < totalEnemigos; ++i) {
            acumulada += enemigos[i].probabilidad;
            if (r <= acumulada) {
                int repetido = 0;
                for (int j = 0; j < seleccionados; ++j) {
                    if (enemigos[i].nombre == enemigosElegidos[j].nombre) {
                        repetido = 1;
                        break;
                    }
                }
                if (!repetido) {
                    enemigosElegidos[seleccionados++] = enemigos[i];
                }
                break;
            }
        }
    }

    int vida1 = enemigosElegidos[0].vida;
    int vida2 = enemigosElegidos[1].vida;

    cout << "\nEntras a una habitación y encuentras a dos monstruos: "
         << enemigosElegidos[0].nombre << " y " << enemigosElegidos[1].nombre << "!\n";

    tCola cola;
    cola.clear();
    cola.enqueue("Jugador");
    cola.enqueue(enemigosElegidos[0].nombre);
    cola.enqueue(enemigosElegidos[1].nombre);

    while (jugador.getVida() > 0 && (vida1 > 0 || vida2 > 0)) {
        cout << "Jugador | " << enemigosElegidos[0].nombre << " | " << enemigosElegidos[1].nombre << endl;
        cout << jugador.getVida() << " | "
             << (vida1 > 0 ? to_string(vida1) : "X") << " | "
             << (vida2 > 0 ? to_string(vida2) : "X") << endl;

        string turno = cola.frontValue();
        cola.dequeue();

        if (turno == "Jugador") {
            if (vida1 > 0) {
                float r = (float) rand() / RAND_MAX;
                if (r <= jugador.getPrecision()) {
                    vida1 -= jugador.getAtaque();
                    if (vida1 < 0) vida1 = 0;
                    cout << "Jugador golpea a " << enemigosElegidos[0].nombre << " por "
                         << jugador.getAtaque() << " de daño!\n";
                } else {
                    cout << "Jugador falló el ataque!\n";
                }
            } else if (vida2 > 0) {
                float r = (float) rand() / RAND_MAX;
                if (r <= jugador.getPrecision()) {
                    vida2 -= jugador.getAtaque();
                    if (vida2 < 0) vida2 = 0;
                    cout << "Jugador golpea a " << enemigosElegidos[1].nombre << " por "
                         << jugador.getAtaque() << " de daño!\n";
                } else {
                    cout << "Jugador falló el ataque!\n";
                }
            }
            cola.enqueue("Jugador");
        }

        else if (turno == enemigosElegidos[0].nombre && vida1 > 0) {
            float r = (float) rand() / RAND_MAX;
            if (r <= enemigosElegidos[0].precision) {
                jugador.cambiarVida(-enemigosElegidos[0].ataque);
                cout << enemigosElegidos[0].nombre << " golpea a Jugador por "
                     << enemigosElegidos[0].ataque << " de daño!\n";
            } else {
                cout << enemigosElegidos[0].nombre << " falla!\n";
            }
            cola.enqueue(enemigosElegidos[0].nombre);
        }

        else if (turno == enemigosElegidos[1].nombre && vida2 > 0) {
            float r = (float) rand() / RAND_MAX;
            if (r <= enemigosElegidos[1].precision) {
                jugador.cambiarVida(-enemigosElegidos[1].ataque);
                cout << enemigosElegidos[1].nombre << " golpea a Jugador por "
                     << enemigosElegidos[1].ataque << " de daño!\n";
            } else {
                cout << enemigosElegidos[1].nombre << " falla!\n";
            }
            cola.enqueue(enemigosElegidos[1].nombre);
        }

        cout << endl;
    }

    if (jugador.getVida() <= 0) {
        cout << "\n Has sido derrotado...\n";
        return false;
    }

    cout << "Has sobrevivido el combate!\n";
    cout << "Recuperas 3 de vida tras el combate.\n";
    jugador.cambiarVida(3);

    int op;
    cout << "Debes decidir:\n";
    cout << "1. Recuperar " << mejoras.vidaExtra << " de vida.\n";
    cout << "2. Aumentar ataque en " << mejoras.ataqueExtra << ".\n";
    cin >> op;
    if (op == 1) {
        jugador.cambiarVida(mejoras.vidaExtra);
        cout << "Recuperaste " << mejoras.vidaExtra << " de vida!\n";
    } else if (op == 2) {
        jugador.cambiarAtaque(mejoras.ataqueExtra);
        cout << "Aumentaste tu ataque en " << mejoras.ataqueExtra << "!\n";
    } else {
        cout << "No elegiste ninguna mejora válida.\n";
    }

    return true;
}

void aplicarEfecto(Jugador& jugador, const string& efecto) {


    stringstream palabrasPorLinea(efecto);
    float valor;
    string atributo;

    palabrasPorLinea >> valor >> atributo;

    if (atributo == "Vida") {
        jugador.cambiarVida((int)valor);
    } else if (atributo == "PRECISION") {
        float nueva = jugador.getPrecision() + valor;
        if (nueva < 0) nueva = 0;
        jugador.setPrecision(nueva);
    } else if (atributo == "ATAQUE") {
        jugador.cambiarAtaque((int)valor);
    } else if (atributo == "RECUPERACION") {
        jugador.setRecuperacion(jugador.getRecuperacion() + (int)valor);
    }
}


void evento(Jugador& jugador, Evento* eventos, int totalEventos) {

    float r = (float) rand() / RAND_MAX;
    float acumulada = 0;
    int elegido = 0;

    for (int i = 0; i < totalEventos; ++i) {
        acumulada += eventos[i].probabilidad;
        if (r <= acumulada) {
            elegido = i;
            break;
        }
    }

    Evento& eve = eventos[elegido];


    cout << "\n Evento encontrado: " << eve.nombre << endl;
    cout << eve.descripcion << endl;
    cout << "1: " << eve.opcionA << endl;
    cout << "2: " << eve.opcionB << endl;


    char decision;
    do {
        cout << "¿Qué eliges? (1/2): ";
        cin >> decision;
        decision = toupper(decision);
    } while (decision != '1' && decision != '2');


    if (decision == '1') {
        cout << eve.efectoA << endl;
        aplicarEfecto(jugador, eve.efectoA);
    } else {
        cout << eve.efectoB << endl;
        aplicarEfecto(jugador, eve.efectoB);
    }
}

void juego(Habitacion* actual, Enemigo* enemigos, int totalEnemigos,
           Evento* eventos, int totalEventos, Jugador& jugador, Mejoras mejoras) {
    
    while (actual != NULL) {
        cout << "\n Estás en: " << actual->nombre << " (" << actual->tipo << ")\n";
        cout << actual->descripcion << endl;

        if (actual->tipo == "COMBATE") {
            bool vivo = combate(jugador, enemigos, totalEnemigos, mejoras);
            if (!vivo) {
                cout << "\n Fin del juego.\n";
                return;
            }
        }
        else if (actual->tipo == "EVENTO") {
            evento(jugador, eventos, totalEventos);
        }
        else if (actual->tipo == "FIN") {
            cout << "\n Llegaste a un final. Gracias por jugar!\n";
            return;
        }


        cout << "\nOpciones para avanzar:\n";
        if (actual->hijoIZQ) cout << "1. " << actual->hijoIZQ->nombre << endl;
        if (actual->hijoMED) cout << "2. " << actual->hijoMED->nombre << endl;
        if (actual->hijoDER) cout << "3. " << actual->hijoDER->nombre << endl;

        int opcion = 0;
        while (true) {
            cout << "Elige tu camino (1-3): ";
            cin >> opcion;

            if (opcion == 1 && actual->hijoIZQ) {
                actual = actual->hijoIZQ;
                break;
            }
            else if (opcion == 2 && actual->hijoMED) {
                actual = actual->hijoMED;
                break;
            }
            else if (opcion == 3 && actual->hijoDER) {
                actual = actual->hijoDER;
                break;
            }
            else {
                cout << " Opción no válida. Intenta de nuevo.\n";
            }
        }
    }
}

void buscarSeccion(ifstream& archivo, const string& seccion) {
    string linea;
    while (getline(archivo, linea)) {
        size_t inicio = linea.find_first_not_of(" ");
        size_t fin = linea.find_last_not_of(" ");
        if (inicio != string::npos && fin != string::npos)
            linea = linea.substr(inicio, fin - inicio + 1);

        if (linea == seccion) return;
    }

    cerr << " No se encontró la sección \"" << seccion << "\" en el archivo.\n";
    exit(EXIT_FAILURE);
}

int main() {
    srand(time(NULL));  

    ifstream map("ejemplo.map");
    if (!map.is_open()) {
        cerr << " Error al abrir el archivo." << endl;
        return 1;
    }

    int n, e, totalEventos;
    Habitacion* habitaciones = NULL;
    Enemigo* enemigos = NULL;
    Evento* eventos = NULL;
    Mejoras mejoras;
    Jugador jugador;


    buscarSeccion(map, "HABITACIONES");
    habitaciones = leerHabitaciones(map, n);

    buscarSeccion(map, "ARCOS");
    arcosXhabitaciones(map, habitaciones, n);

    buscarSeccion(map, "ENEMIGOS");
    enemigos = leerEnemigos(map, e);

    buscarSeccion(map, "EVENTOS");
    eventos = leerEventos(map, totalEventos);

    buscarSeccion(map, "MEJORAS DE COMBATE");
    mejoras = leerMejorasDeCombate(map);

    juego(&habitaciones[0], enemigos, e, eventos, totalEventos, jugador, mejoras);

    cout << "\n Stats finales del jugador:\n";
    jugador.mostrarStats();
    delete[] habitaciones;
    delete[] enemigos;
    delete[] eventos;
    map.close();

    return 0;
}


