//solo es un ejemplo para guiarse :D

#include <iostream>

struct Nodo {
    int dato;
    Nodo* siguiente;
    Nodo* anterior;

    Nodo(int valor) : dato(valor), siguiente(nullptr), anterior(nullptr) {}
};

class ListaCircularDobleEnlace {
private:
    Nodo* cabeza;

public:
    ListaCircularDobleEnlace() : cabeza(nullptr) {}

    // Crear
    void insertar(int valor);

    // Leer
    void mostrar() const;

    // Actualizar un valor exisitente por uno nuevo :D
    bool actualizar(int valorAntiguo, int valorNuevo);

    // Eliminar
    bool eliminar(int valor);

    // Destructor para liberar memoria
    ~ListaCircularDobleEnlace();
};

void ListaCircularDobleEnlace::insertar(int valor) {
    Nodo* nuevoNodo = new Nodo(valor);

    if (!cabeza) {
        cabeza = nuevoNodo;
        cabeza->siguiente = cabeza;
        cabeza->anterior = cabeza;
    } else {
        Nodo* cola = cabeza->anterior;
        cola->siguiente = nuevoNodo;
        nuevoNodo->anterior = cola;
        nuevoNodo->siguiente = cabeza;
        cabeza->anterior = nuevoNodo;
    }
}

void ListaCircularDobleEnlace::mostrar() const {
    if (!cabeza) {
        std::cout << "La lista está vacía." << std::endl;
        return;
    }

    Nodo* temp = cabeza;
    do {
        std::cout << temp->dato << " ";
        temp = temp->siguiente;
    } while (temp != cabeza);
    std::cout << std::endl;
}

bool ListaCircularDobleEnlace::actualizar(int valorAntiguo, int valorNuevo) {
    if (!cabeza) return false;

    Nodo* temp = cabeza;
    do {
        if (temp->dato == valorAntiguo) {
            temp->dato = valorNuevo;
            return true;
        }
        temp = temp->siguiente;
    } while (temp != cabeza);
    return false;
}

bool ListaCircularDobleEnlace::eliminar(int valor) {
    if (!cabeza) return false;

    Nodo* temp = cabeza;

    do {
        if (temp->dato == valor) {
            if (temp == cabeza && cabeza->siguiente == cabeza) {
                delete cabeza;
                cabeza = nullptr;
                return true;
            }

            Nodo* nodoAnterior = temp->anterior;
            Nodo* nodoSiguiente = temp->siguiente;

            nodoAnterior->siguiente = nodoSiguiente;
            nodoSiguiente->anterior = nodoAnterior;

            if (temp == cabeza) cabeza = nodoSiguiente;

            delete temp;
            return true;
        }
        temp = temp->siguiente;
    } while (temp != cabeza);
    return false;
}

ListaCircularDobleEnlace::~ListaCircularDobleEnlace() {
    if (!cabeza) return;

    Nodo* actual = cabeza;
    do {
        Nodo* siguienteNodo = actual->siguiente;
        delete actual;
        actual = siguienteNodo;
    } while (actual != cabeza);

    cabeza = nullptr;
}

int main() {
    ListaCircularDobleEnlace lista1;

    // Insertar en lista 1
    lista1.insertar(10);
    lista1.insertar(20);
    lista1.insertar(30);

    // Mostrar
    std::cout << "Lista después de insertar: ";
    lista1.mostrar();

    // Actualizar
    lista1.actualizar(20, 25);
    std::cout << "Lista después de actualizar: ";
    lista1.mostrar();

    // Eliminar
    lista1.eliminar(10);
    std::cout << "Lista después de eliminar: ";
    lista1.mostrar();

    return 0;
}

