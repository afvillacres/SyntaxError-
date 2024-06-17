
/** pongan comentarios en lo que hacen para no perdernos xd
Si algo sacaron de un video o asi le ponen junto a lo que
hicieron para tener mas o menos una idea y seguir :D
**/

#include <iostream>
#include <string>
#include <fstream>//manejo de archivos, para guardar info de la semana :D
using namespace std;

struct Dia {
    string nombreDia;
    string nombreEmpresa;
    int numeroDeTrabajadores;
    int menuSeleccionado;
    bool esFeriado;

    // Constructor para inicializar los datos del dia
    Dia(string _nombreDia, string _nombreEmpresa, int _numTrabajadores, int _menuSeleccionado, bool _esFeriado)
        : nombreDia(_nombreDia), nombreEmpresa(_nombreEmpresa), numeroDeTrabajadores(_numTrabajadores), menuSeleccionado(_menuSeleccionado), esFeriado(_esFeriado) {}
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

void mostrarMenuPrincipal(int semanaActual, string nombreDia) {
    cout << "\n------ Menu de opciones: Semana " << semanaActual << " - Dia " << nombreDia << " -------------\n";
    cout << "1. Ingresar/modificar datos del dia\n";
    cout << "2. Ver menu y costo semanal\n";
    cout << "3. Marcar dia como feriado\n";
    cout << "4. Terminar la semana\n";
    cout << "5. Imprimir dias con sus menus y numero de trabajadores\n";
    cout << "6. Salir del programa\n";
    cout << "Ingrese una opcion: ";
}

string obtenerNombreDia(int dia) {
    switch(dia) {
        case 0: return "Lunes";
        case 1: return "Martes";
        case 2: return "Miercoles";
        case 3: return "Jueves";
        case 4: return "Viernes";
        default: return "Dia no valido";
    }
}

//guarda al finalizar cada semana xd
void guardarDatosSemana(listaCircularDoble<Dia>& semana, int semanaActual) {
    ofstream archivo("datos_semana.txt");
    if (!archivo) {
        cerr << "Error al abrir el archivo para guardar los datos." << endl;
        return;
    }
    Nodo<Dia>* temp = semana.obtenerCabeza();
    archivo << "Semana " << semanaActual << ":\n";
    do {
        archivo << temp->dato.nombreDia << " (" << temp->dato.nombreEmpresa << "): ";
        if (temp->dato.esFeriado) {
            archivo << "FERIADO\n";
        } else {
            archivo << "Menu: " << temp->dato.menuSeleccionado << ", Trabajadores: " << temp->dato.numeroDeTrabajadores << "\n";
        }
        temp = temp->siguiente;
    } while (temp != semana.obtenerCabeza());
    archivo.close();
}

int main() {
    listaCircularDoble<Dia> semana;
    int diaActual = 0;
    int semanaActual = 1;
    const int diasPorSemana = 5;

    for (int i = 0; i < diasPorSemana; ++i) {
        semana.insertarAlFinal(Dia{obtenerNombreDia(i), "", 0, 0, false});
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
        mostrarMenuPrincipal(semanaActual, obtenerNombreDia(diaActual % diasPorSemana));
        int opcion;
        cin >> opcion;

        switch (opcion) {
            case 1: {
                int diaSemana = diaActual % diasPorSemana;
                actual = semana.obtenerCabeza();
                for (int i = 0; i < diaSemana; ++i) {
                    actual = actual->siguiente;
                }

                if (actual->dato.esFeriado) {
                    cout << "El dia es feriado, no se pueden ingresar datos.\n";
                    break;
                }

                cout << "Ingrese el nombre de la empresa para " << actual->dato.nombreDia << ": ";
                cin.ignore();
                getline(cin, actual->dato.nombreEmpresa);

                cout << "Ingrese el menu para " << actual->dato.nombreDia << ":\n";
                cout << "1. " << menus[0] << "\n";
                cout << "2. " << menus[1] << "\n";
                cout << "3. " << menus[2] << "\n";
                cout << "Opcion: ";
                int opcionMenu;
                cin >> opcionMenu;
                if (opcionMenu >= 1 && opcionMenu <= 3) {
                    actual->dato.menuSeleccionado = opcionMenu;
                } else {
                    cout << "Opcion invalida.\n";
                }

                cout << "Ingrese el numero de trabajadores para " << actual->dato.nombreDia << ": ";
                cin >> actual->dato.numeroDeTrabajadores;
                break;
            }
            case 2: {
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
                    cout << temp->dato.nombreDia << " (" << temp->dato.nombreEmpresa << "): ";
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
            case 3: {
                int diaSemana = diaActual % diasPorSemana;
                actual = semana.obtenerCabeza();
                for (int i = 0; i < diaSemana; ++i) {
                    actual = actual->siguiente;
                }

                cout << "Marcando el dia " << actual->dato.nombreDia << " como feriado.\n";
                actual->dato.esFeriado = true;
                actual->dato.menuSeleccionado = 0;
                actual->dato.numeroDeTrabajadores = 0;
                break;
            }
            case 4: {
                cout << "Terminando la semana actual." << endl;
                guardarDatosSemana(semana, semanaActual);
                semanaActual++;
                diaActual = 0;
                break;
            }
            case 5: {
                Nodo<Dia>* temp = semana.obtenerCabeza();
                cout << "\nDias de la semana actual (Semana " << semanaActual << "):\n";
                do {
                    cout << temp->dato.nombreDia << " (" << temp->dato.nombreEmpresa << "): ";
                    if (temp->dato.esFeriado) {
                        cout << "FERIADO\n";
                    } else {
                        cout << menus[temp->dato.menuSeleccionado - 1] << " (Trabajadores: " << temp->dato.numeroDeTrabajadores << ")\n";
                    }
                    temp = temp->siguiente;
                } while (temp != semana.obtenerCabeza());
                break;
            }
            case 6: {
                continuar = false;
                break;
            }
            default:
                cout << "Opcion no válida. Intente nuevamente." << endl;
        }
    }

    cout << "Programa finalizado. Gracias por usar el sistema." << endl;

    return 0;
}
