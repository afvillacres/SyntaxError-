#include <string>
#include <iostream>

using namespace std;

class Docente {
private:
    string nombre;
    string cedula;

public:
    void ingresarDatos();
    string getNombre();
    string getCedula();
};

void Docente::ingresarDatos() {
    cout << "Ingrese su nombre: ";
    getline(cin, nombre); // Use getline to allow spaces in the name

    do {
        cout << "Ingrese el numero de cedula (10 digitos): ";
        cin >> cedula;
        cin.ignore(); // Clear the newline character left in the buffer

        if (validarCedula(cedula)) {
            cout << "Cedula valida" << endl;
        } else {
            cout << "Cedula no valida..." << endl;
        }
    } while (!validarCedula(cedula));
}

string Docente::getNombre() {
    return nombre;
}

string Docente::getCedula() {
    return cedula;
}

bool validarCedula(const string& cedula) {
    if (cedula.length() != 10) {
        return false;
    }

    int coeficientes[9] = {2, 1, 2, 1, 2, 1, 2, 1, 2};
    int suma = 0;

    for (int i = 0; i < 9; ++i) {
        int digito = cedula[i] - '0';
        int producto = digito * coeficientes[i];
        if (producto > 9) {
            producto -= 9;
        }
        suma += producto;
    }

    int digito_verificador = cedula[9] - '0';
    int suma_total = suma + digito_verificador;

    return suma_total % 10 == 0;
}
