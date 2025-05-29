// main.cpp
#include <iostream>
#include <string>
#include "Alojamiento.h"
#include "Anfitrion.h"
#include "Huesped.h"
#include "Reservacion.h"
#include <fstream>
#include <sstream>

using namespace std;

// Datos de prueba (provisorios)
Anfitrion* anfitriones[10];
int totalAnfitriones = 0;

Huesped* huespedes[10];
int totalHuespedes = 0;

Alojamiento* alojamientos[10];
int totalAlojamientos = 0;

Reservacion* reservas[50];
int totalReservas = 0;

void mostrarMenuPrincipal();
void iniciarSesion();
void menuHuesped(Huesped* h);
void menuAnfitrion(Anfitrion* a);

std::string generarCodigoReserva(int num) {
    return "RES" + std::to_string(1000 + num);
}

void cargarAnfitriones() {
    std::ifstream archivo("anfitriones.txt");
    if (!archivo) {
        std::cerr << "No se pudo abrir el archivo anfitriones.txt\n";
        return;
    }

    std::string linea;
    while (getline(archivo, linea)) {
        std::istringstream ss(linea);
        std::string doc;
        int ant;
        float punt;

        std::getline(ss, doc, ',');
        ss >> ant;
        ss.ignore(1); // Ignorar la coma
        ss >> punt;

        anfitriones[totalAnfitriones++] = new Anfitrion(doc, ant, punt);
    }

    archivo.close();
}
void guardarAnfitriones() {
    std::ofstream archivo("anfitriones.txt");
    if (!archivo) {
        std::cerr << "No se pudo escribir en anfitriones.txt\n";
        return;
    }

    for (int i = 0; i < totalAnfitriones; ++i) {
        archivo << anfitriones[i]->getDocumento() << ","
                << anfitriones[i]->getAntiguedad() << ","
                << anfitriones[i]->getPuntuacion() << "\n";
    }

    archivo.close();
}

void cargarAlojamientos() {
    std::ifstream archivo("alojamientos.txt");
    if (!archivo) {
        std::cerr << "No se pudo abrir el archivo alojamientos.txt\n";
        return;
    }

    std::string linea;
    while (getline(archivo, linea)) {
        std::istringstream ss(linea);
        std::string cod, nom, tip, dir, muni, depto, precioStr, numAmenStr, amenStr, docAnfitrion;

        getline(ss, cod, ',');
        getline(ss, nom, ',');
        getline(ss, tip, ',');
        getline(ss, dir, ',');
        getline(ss, muni, ',');
        getline(ss, depto, ',');
        getline(ss, precioStr, ',');
        getline(ss, numAmenStr, ',');
        getline(ss, amenStr, ',');
        getline(ss, docAnfitrion);

        float precio = std::stof(precioStr);
        int numAmen = std::stoi(numAmenStr);

        // Separar amenidades por ';'
        std::istringstream amenStream(amenStr);
        std::string amenidad;
        std::string* amenidades = new std::string[numAmen];
        int index = 0;

        while (getline(amenStream, amenidad, ';') && index < numAmen) {
            amenidades[index++] = amenidad;
        }

        // Buscar anfitrión correspondiente
        Anfitrion* anfitrion = nullptr;
        for (int i = 0; i < totalAnfitriones; ++i) {
            if (anfitriones[i]->getDocumento() == docAnfitrion) {
                anfitrion = anfitriones[i];
                break;
            }
        }

        if (!anfitrion) {
            std::cerr << "Anfitrión con documento " << docAnfitrion << " no encontrado para alojamiento " << cod << "\n";
            delete[] amenidades;
            continue;
        }

        Alojamiento* nuevo = new Alojamiento(cod, nom, tip, dir, muni, precio, amenidades, numAmen, anfitrion);
        alojamientos[totalAlojamientos++] = nuevo;
        anfitrion->agregarAlojamiento(nuevo);
    }

    archivo.close();
}
void guardarAlojamientos() {
    std::ofstream archivo("alojamientos.txt");
    if (!archivo) {
        std::cerr << "No se pudo escribir en alojamientos.txt\n";
        return;
    }

    for (int i = 0; i < totalAlojamientos; ++i) {
        archivo << alojamientos[i]->getCodigo() << ","
                << alojamientos[i]->getNombre() << ","
                << alojamientos[i]->getTipo() << ","
                << alojamientos[i]->getDireccion() << ","
                << alojamientos[i]->getMunicipio() << ","
                << alojamientos[i]->getDepartamento() << ","
                << alojamientos[i]->getPrecioNoche() << ","
                << alojamientos[i]->getNumAmenidades() << ",";

        for (int j = 0; j < alojamientos[i]->getNumAmenidades(); ++j) {
            archivo << alojamientos[i]->getAmenidad(j);
            if (j < alojamientos[i]->getNumAmenidades() - 1)
                archivo << ";";
        }

        archivo << "," << alojamientos[i]->getAnfitrion()->getDocumento() << "\n";
    }

    archivo.close();
}

void cargarHuespedes() {
    std::ifstream archivo("huespedes.txt");
    if (!archivo) {
        std::cerr << "No se pudo abrir el archivo huespedes.txt\n";
        return;
    }

    std::string linea;
    while (getline(archivo, linea)) {
        std::istringstream ss(linea);
        std::string doc;
        int ant;
        float punt;

        getline(ss, doc, ',');
        ss >> ant;
        ss.ignore(1); // Ignorar coma
        ss >> punt;

        huespedes[totalHuespedes++] = new Huesped(doc, ant, punt);
    }

    archivo.close();
}
void guardarHuespedes() {
    std::ofstream archivo("huespedes.txt");
    if (!archivo) {
        std::cerr << "No se pudo escribir en huespedes.txt\n";
        return;
    }

    for (int i = 0; i < totalHuespedes; ++i) {
        archivo << huespedes[i]->getDocumento() << ","
                << huespedes[i]->getAntiguedad() << ","
                << huespedes[i]->getPuntuacion() << "\n";
    }

    archivo.close();
}

void menuAnfitrion(Anfitrion* a) {
    int opcion;
    do {
        cout << "\n--- Menu Anfitrion ---\n";
        cout << "1. Ver reservaciones\n";
        cout << "2. Actualizar historico\n";
        cout << "0. Cerrar sesion\n";
        cout << "Opcion: ";
        cin >> opcion;

        switch (opcion) {
        case 1:
            a->mostrarReservaciones("2025-01-01", "2025-12-31");
            break;
        case 2:
            cout << "Funcionalidad en desarrollo...\n";
            break;
        case 0:
            cout << "Sesión cerrada.\n";
            break;
        default:
            cout << "Opción inválida.\n";
        }
    } while (opcion != 0);
}
void reservarAlojamiento(Huesped* h) {
    std::string municipio, fechaInicio, metodoPago, anotaciones;
    int noches;
    float monto;

    cout << "Municipio destino: ";
    cin.ignore();
    getline(cin, municipio);

    cout << "Fecha de inicio (AAAA-MM-DD): ";
    getline(cin, fechaInicio);

    cout << "Número de noches: ";
    cin >> noches;
    cin.ignore();

    // Mostrar alojamientos disponibles en ese municipio (simplificado)
    cout << "\nAlojamientos disponibles en " << municipio << ":\n";
    for (int i = 0; i < totalAlojamientos; ++i) {
        if (alojamientos[i]->getCodigo().substr(0, municipio.size()) == municipio) {
            alojamientos[i]->mostrarInfo();
        }
    }

    string codAloj;
    cout << "Ingrese el código del alojamiento que desea reservar: ";
    getline(cin, codAloj);

    Alojamiento* elegido = nullptr;
    for (int i = 0; i < totalAlojamientos; ++i) {
        if (alojamientos[i]->getCodigo() == codAloj) {
            elegido = alojamientos[i];
            break;
        }
    }

    if (elegido == nullptr) {
        cout << "Alojamiento no encontrado.\n";
        return;
    }

    if (!h->disponibleParaFechas(fechaInicio, noches)) {
        cout << "Ya tienes una reserva activa en ese rango de fechas.\n";
        return;
    }

    cout << "Método de pago (PSE/Tarjeta): ";
    getline(cin, metodoPago);

    cout << "Monto a pagar: ";
    cin >> monto;
    cin.ignore();

    cout << "Anotaciones para el anfitrión (opcional, max 1000 caracteres): ";
    getline(cin, anotaciones);

    // Crear reserva
    std::string codReserva = generarCodigoReserva(totalReservas);
    Reservacion* nueva = new Reservacion(codReserva, fechaInicio, noches, metodoPago,
                                         fechaInicio, monto, anotaciones, elegido, h);

    h->agregarReservacion(nueva);
    reservas[totalReservas++] = nueva;

    cout << "\nReserva creada exitosamente:\n";
    nueva->mostrarComprobante();
}


int main() {
    cargarAnfitriones();
    cargarAlojamientos();
    string amenities[] = {"wifi", "tv", "baño privado"};
    anfitriones[0]->agregarAlojamiento(alojamientos[0]);
    cargarHuespedes();

    mostrarMenuPrincipal();
    return 0;
}

void mostrarMenuPrincipal() {
    int opcion;
    do {
        cout << "\n=== Bienvenido a UdeAStay ===\n";
        cout << "1. Iniciar sesion\n";
        cout << "0. Salir\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion) {
        case 1:
            iniciarSesion();
            break;
        case 0:
            cout << "Gracias por usar UdeAStay.\n";
            break;
        default:
            cout << "Opcion invalida.\n";
        }
    } while (opcion != 0);
}

void iniciarSesion() {
    string doc;
    cout << "\nIngrese su documento: ";
    cin >> doc;


    for (int i = 0; i < totalAnfitriones; ++i) {
        if (anfitriones[i]->getDocumento() == doc) {
            menuAnfitrion(anfitriones[i]);
            return;
        }
    }


    for (int i = 0; i < totalHuespedes; ++i) {
        if (huespedes[i]->getDocumento() == doc) {
            menuHuesped(huespedes[i]);
            return;
        }
    }

    cout << "Usuario no encontrado.\n";
}

void menuHuesped(Huesped* h) {
    int opcion;
    do {
        cout << "\n--- Menu Huesped ---\n";
        cout << "1. Ver alojamientos disponibles\n";
        cout << "2. Reservar alojamiento\n";
        cout << "3. Ver mis reservaciones\n";
        cout << "0. Cerrar sesi0n\n";
        cout << "Opcion: ";
        cin >> opcion;

        switch (opcion) {
        case 1: {
            if (totalAlojamientos == 0) {
                std::cout << "No hay alojamientos disponibles actualmente.\n";
            } else {
                std::cout << "\n=== Lista de todos los alojamientos disponibles ===\n";
                for (int i = 0; i < totalAlojamientos; ++i) {
                    std::cout << "\nAlojamiento #" << (i + 1) << ":\n";
                    alojamientos[i]->mostrarInfo();
                }
            }
            break;
        }


        case 2:
            reservarAlojamiento(h);
            break;
        case 3:
            h->mostrarReservaciones();
            break;

        case 0:
            cout << "Sesión cerrada.\n";
            break;
        default:
            cout << "Opción inválida.\n";
        }
    } while (opcion != 0);
}
