
/** pongan comentarios en lo que hacen para no perdernos xd
Si algo sacaron de un video o asi le ponen junto a lo que
hicieron para tener mas o menos una idea y seguir :D
**/

#include <iostream>
#include <string>
using namespace std;

struct Dia {
    string nombre;
    int numeroDeTrabajadores;
    int menuSeleccionado;
    bool esFeriado;

    Dia(string _nombre, int _numTrabajadores, int _menuSeleccionado, bool _esFeriado)
        : nombre(_nombre), numeroDeTrabajadores(_numTrabajadores), menuSeleccionado(_menuSeleccionado), esFeriado(_esFeriado) {}
};

template<typename T>
class Nodo {
public:
    T dato;
    Nodo* siguiente;
    Nodo* anterior;

    Nodo(T valor) : dato(valor), siguiente(NULL), anterior(NULL) {}
};

template <typename T>
class listaCircularDoble {
private:
    Nodo<T>* cabeza;
public:
    listaCircularDoble() : cabeza(NULL) {}

    ~listaCircularDoble() {
        if (cabeza != NULL) {
            Nodo<T>* actual = cabeza;
            Nodo<T>* siguienteNodo;
            do {
                siguienteNodo = actual->siguiente;
                delete actual;
                actual = siguienteNodo;
            } while (actual != cabeza);
        }
    }

    void insertarAlFinal(T valor) {
        Nodo<T>* nuevoNodo = new Nodo<T>(valor);
        if (cabeza == NULL) {
            cabeza = nuevoNodo;
            nuevoNodo->siguiente = cabeza;
            nuevoNodo->anterior = cabeza;
        } else {
            Nodo<T>* ultimo = cabeza->anterior;
            ultimo->siguiente = nuevoNodo;
            nuevoNodo->anterior = ultimo;
            nuevoNodo->siguiente = cabeza;
            cabeza->anterior = nuevoNodo;
        }
    }

    Nodo<T>* obtenerCabeza() {
        return cabeza;
    }
};

void mostrarMenuPrincipal() {
    cout << "\n------Menu de opciones:  -------------\n";
    cout << "1. Ingresar un nuevo dia\n";
    cout << "2. Modificar numero de trabajadores del dia\n";
    cout << "3. Ver menu y costo semanal\n";
    cout << "4. Marcar dia como feriado\n";
    cout << "5. Terminar la semana\n";
    cout << "6. Modificar menu del dia\n";
    cout << "7. Imprimir dias con sus menus y numero de trabajadores\n";
    cout << "8. Salir del programa\n";
    cout << "Ingrese una opcion: ";
}

string obtenerNombreDia(int dia) {
    switch(dia) {
        case 0: return "Lunes";
        case 1: return "Martes";
        case 2: return "Mi�rcoles";
        case 3: return "Jueves";
        case 4: return "Viernes";
        default: return "Dia no valido";
    }
}

int main() {
    listaCircularDoble<Dia> semana;
    int diaActual = 0;
    int semanaActual = 1;
    const int diasPorSemana = 5;

    for (int i = 0; i < diasPorSemana; ++i) {
        semana.insertarAlFinal(Dia{obtenerNombreDia(i), 0, 0, false});
    }

    const float costoPorTrabajador = 2.25;

    string menus[3] = {
        "Sopa de Pollo, Seco de Carne, Jugo de Mora",
        "Locro de Papa, Churrasco, Limonada",
        "Sancocho, Guatita, Jugo de Naranja"
    };

    Nodo<Dia>* actual = semana.obtenerCabeza();
    bool continuar = true;

    while (continuar) {
        mostrarMenuPrincipal();
        int opcion;
        cin >> opcion;

        switch (opcion) {
            case 1: {
                int diaSemana = diaActual % diasPorSemana;
                actual = semana.obtenerCabeza();
                for (int i = 0; i < diaSemana; ++i) {
                    actual = actual->siguiente;
                }

                int opcionMenu;
                cout << "Ingrese el menu para " << actual->dato.nombre << ":\n";
                cout << "1. " << menus[0] << "\n";
                cout << "2. " << menus[1] << "\n";
                cout << "3. " << menus[2] << "\n";
                cout << "Opcion: ";
                cin >> opcionMenu;
                if (opcionMenu >= 1 && opcionMenu <= 3) {
                    actual->dato.menuSeleccionado = opcionMenu;
                } else {
                    cout << "Opcion invalida.\n";
                }

                cout << "Ingrese el numero de trabajadores para " << actual->dato.nombre << ": ";
                cin >> actual->dato.numeroDeTrabajadores;
                diaActual++;
                break;
            }
            case 2: {
                int diaSemana = diaActual % diasPorSemana;
                actual = semana.obtenerCabeza();
                for (int i = 0; i < diaSemana; ++i) {
                    actual = actual->siguiente;
                }

                cout << "Ingrese el numero de trabajadores para " << actual->dato.nombre << ": ";
                cin >> actual->dato.numeroDeTrabajadores;
                cout << "Numero de trabajadores actualizado correctamente.\n";
                break;
            }
            case 3: {
                float costoTotal = 0.0;
                Nodo<Dia>* temp = semana.obtenerCabeza();
                do {
                    if (!temp->dato.esFeriado) {
                        costoTotal += costoPorTrabajador * temp->dato.numeroDeTrabajadores;
                    }
                    temp = temp->siguiente;
                } while (temp != semana.obtenerCabeza());

                temp = semana.obtenerCabeza();
                cout << "\nMenu semanal (Semana " << semanaActual << "):\n";
                do {
                    cout << temp->dato.nombre << ": ";
                    if (temp->dato.esFeriado) {
                        cout << "FERIADO\n";
                    } else {
                        cout << menus[temp->dato.menuSeleccionado - 1] << " (Trabajadores: " << temp->dato.numeroDeTrabajadores << ")\n";
                    }
                    temp = temp->siguiente;
                } while (temp != semana.obtenerCabeza());

                cout << "Costo total semanal: $" << costoTotal << endl;
                break;
            }
            case 4: {
                int diaSemana = diaActual % diasPorSemana;
                actual = semana.obtenerCabeza();
                for (int i = 0; i < diaSemana; ++i) {
                    actual = actual->siguiente;
                }

                cout << "Marcando el dia " << actual->dato.nombre << " como feriado.\n";
                actual->dato.esFeriado = true;
                actual->dato.menuSeleccionado = 0;
                actual->dato.numeroDeTrabajadores = 0;
                break;
            }
            case 5: {
                cout << "Terminando la semana actual." << endl;
                semanaActual++;
                diaActual = 0;
                break;
            }
            case 6: {
                int diaSemana = diaActual % diasPorSemana;
                actual = semana.obtenerCabeza();
                for (int i = 0; i < diaSemana; ++i) {
                    actual = actual->siguiente;
                }

                int opcionMenu;
                cout << "Ingrese el nuevo menu para " << actual->dato.nombre << ":\n";
                cout << "1. " << menus[0] << "\n";
                cout << "2. " << menus[1] << "\n";
                cout << "3. " << menus[2] << "\n";
                cout << "Opcion: ";
                cin >> opcionMenu;
                if (opcionMenu >= 1 && opcionMenu <= 3) {
                    actual->dato.menuSeleccionado = opcionMenu;
                    cout << "Menu actualizado correctamente.\n";
                } else {
                    cout << "Opcion invalida.\n";
                }
                break;
            }
            case 7: {
                Nodo<Dia>* temp = semana.obtenerCabeza();
                cout << "\nDias de la semana actual (Semana " << semanaActual << "):\n";
                do {
                    cout << temp->dato.nombre << ": ";
                    if (temp->dato.esFeriado) {
                        cout << "FERIADO\n";
                    } else {
                        cout << menus[temp->dato.menuSeleccionado - 1] << " (Trabajadores: " << temp->dato.numeroDeTrabajadores << ")\n";
                    }
                    temp = temp->siguiente;
                } while (temp != semana.obtenerCabeza());
                break;
            }
            case 8: {
                continuar = false;
                break;
            }
            default:
                cout << "Opci�n no v�lida. Intente nuevamente." << endl;
        }
    }

    cout << "Programa finalizado. Gracias por usar el sistema." << endl;

    return 0;
}
