
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
    Dia(string _nombreDia, string _nombreEmpresa, int _numTrabajadores, int _menuSeleccionado, bool _esFeriado): nombreDia(_nombreDia), nombreEmpresa(_nombreEmpresa), numeroDeTrabajadores(_numTrabajadores), menuSeleccionado(_menuSeleccionado), esFeriado(_esFeriado) {}

    //el metodo ya lo dice :D
    void actualizarDatos(string _nombreEmpresa, int _menuSeleccionado, int _numTrabajadores, bool _esFeriado) {
        nombreEmpresa = _nombreEmpresa;
        menuSeleccionado = _menuSeleccionado;
        numeroDeTrabajadores = _numTrabajadores;
        esFeriado = _esFeriado;
    }
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
    cout << "\n-------- Menu de opciones: Semana " << semanaActual << " - Dia " << nombreDia << " --------\n";
    cout << "1. Ingresar datos segun el dia.\n";
    cout << "2. Ver menu y costo semanal.\n";
    cout << "3. Marcar dia como feriado.\n";
    cout << "4. Terminar la semana.\n";
    cout << "5. Modificar un dia dentro de la semana.\n";
    cout << "6. Imprimir dias con sus menus y numero de trabajadores.\n";
    cout << "7. Salir del programa.\n";
    cout << "Ingrese una opcion: ";
}

string obtenerNombreDia(int dia) {
    switch(dia) {
        case 0: return "Lunes";
        case 1: return "Martes";
        case 2: return "Miercoles";
        case 3: return "Jueves";
        case 4: return "Viernes";
    }
}


//guarda al finalizar cada semana xd
void guardarDatosSemana(listaCircularDoble<Dia>& semana, int semanaActual) {
    ofstream archivo;
    archivo.open("datos_semana.txt", ios::app);

    if (!archivo) {
        cerr << "Error al abrir el archivo para guardar los datos." << endl;
        return;
    }

    archivo << "Semana " << semanaActual << ":\n";
    Nodo<Dia>* temp = semana.obtenerCabeza();
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


void dibujarAgradeciminento(){
    cout<<"        .--..--..--..--..--..--."<<endl;
    cout<<"      .' \\  (`._   (_)     _   \\"<<endl;
    cout<<"    .'    |  '._)         (_)  |"<<endl;
    cout<<"    \\ _.')\\      .----..---.   /"<<endl;
    cout<<"    |(_.'  |    /    .-\\-.  \\  |"<<endl;
    cout<<"    \\     0|    |   ( O| O) | o|"<<endl;
    cout<<"     |  _  |  .--.____.'._.-.  |"<<endl;
    cout<<"     \\ (_) | o         -` .-`  |"<<endl;
    cout<<"      |    \\   |`-._ _ _ _ _\\ /"<<endl;
    cout<<"      \\    |   |  `. |_||_|   |"<<endl;
    cout<<"      | o  |    \\_      \     |     -.   .-." <<endl;
    cout<<"      |.-.  \\     `--..-'   O |     `.`-' .'"<<endl;
    cout<<"    _.'  .' |     `-.-'      /-.__   ' .-'"<<endl;
    cout<<"  .' `-.` '.|='=.='=.='=.='=|._/_ `-'.'"<<endl;
    cout<<"  `-._  `.  |________/\\_____|    `-.'"<<endl;
    cout<<"     .'   ).| '=' '='\\/ '=' |"<<endl;
    cout<<"     `._.`  '---------------'"<<endl;
    cout<<"             //___\\   //___\\ "<<endl;
    cout<<"               ||       ||"<<endl;
    cout<<"               ||_.-.   ||_.-."<<endl;
    cout<<"              (_.--__) (_.--__)"<<endl;
    cout<<"-------------------------------------------------------"<<endl;
    cout<<"----------------Gracias por usar el sistema.-----------"<<endl;
    cout<<"----------------Grupo 8- Syntaxis Error.-----------"<<endl;

}

void mainPrincipal(){
    listaCircularDoble<Dia> semana;
    int diaActual = 0;
    int semanaActual = 1;
    const int diasPorSemana = 5;
    int opcionMenu;

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

        //VIDEO USADO COMO GUIA: https://www.youtube.com/watch?v=4eCLiVhTwQc
        while(!(cin >> opcion)){
            cout << "\nDato erroneo! Ingrese solo un numero: ";
            cin.clear();
            cin.ignore(132, '\n');
        }

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

                do {
                    cout << "Ingrese el menu para " << actual->dato.nombreDia << ":\n";
                    cout << "1. " << menus[0] << "\n";
                    cout << "2. " << menus[1] << "\n";
                    cout << "3. " << menus[2] << "\n";
                    cout << "Opcion: ";
                    cin >> opcionMenu;

                    if (opcionMenu < 1 || opcionMenu > 3) {
                        cout << "Opcion invalida. Intente nuevamente.\n";
                    }
                } while (opcionMenu < 1 || opcionMenu > 3);

                cout << "Ingrese el numero de trabajadores para " << actual->dato.nombreDia << ": ";
                cin >> actual->dato.numeroDeTrabajadores;
                diaActual = (diaActual + 1) % diasPorSemana;//cambia al dia siguiente

                // Verificar si es viernes
                if (diaActual % diasPorSemana == 4) {
                    char continuarSemana;
                    cout << "¿Desea realizar alguna opcion adicional (s/n) o avanzar a la semana siguiente (p)? ";
                    cin >> continuarSemana;

                    if (continuarSemana == 'p' || continuarSemana == 'P') {
                        semanaActual++;
                        diaActual = 0; // Reiniciar al inicio de la siguiente semana
                    }
                }
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

                cout << "--------  Marcando el dia " << actual->dato.nombreDia << " como feriado.  --------\n";
                actual->dato.esFeriado = true;
                actual->dato.menuSeleccionado = 0;
                actual->dato.numeroDeTrabajadores = 0;
                diaActual = (diaActual + 1) % diasPorSemana;//tambien le salta al dia siguiente y le marca a ese dia como feriado
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
                int diaSemanaModificar;
                cout << "Ingrese el dia de la semana que desea modificar (1 - 5): ";
                cin >> diaSemanaModificar;

                if (diaSemanaModificar < 1 || diaSemanaModificar > diasPorSemana) {
                    cout << "Dia no valido. Intente nuevamente." << endl;
                    break;
                }

                // Convertir a indice base 0 porque los dias van de 0(lunes) a 4(viernes)
                int indiceDia = diaSemanaModificar - 1;
                actual = semana.obtenerCabeza();
                for (int i = 0; i < indiceDia; ++i) {
                    actual = actual->siguiente;
                }

                cout << "Modificar datos para el dia " << actual->dato.nombreDia << ":\n";
                cout << "Ingrese el nombre de la empresa: ";
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

                actual->dato.esFeriado = false; // Quita el marcado como feriado en caso de que se haya guardado asi :p

                cout << "Dia modificado exitosamente.\n";
                break;
            }


            case 6: {
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

            case 7: {
                continuar = false;
                break;
            }
            default:
                cout << "Opcion no valida. Intente nuevamente." << endl;
        }
    }

    dibujarAgradeciminento();

}



int main() {
    mainPrincipal();

    return 0;
}
