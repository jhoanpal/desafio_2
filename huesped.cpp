// Huesped.cpp
#include "Huesped.h"
#include <sstream>
#include <iomanip>
#include <ctime>
#include <iostream>

Huesped::Huesped() {
    documento = "";
    antiguedad = 0;
    puntuacion = 0.0;
    reservaciones = nullptr;
    numReservas = 0;
}

Huesped::Huesped(std::string doc, int ant, float punt) {
    documento = doc;
    antiguedad = ant;
    puntuacion = punt;
    reservaciones = nullptr;
    numReservas = 0;
}

Huesped::~Huesped() {
    delete[] reservaciones;
}

void Huesped::agregarReservacion(Reservacion* r) {
    Reservacion** temp = new Reservacion*[numReservas + 1];
    for (int i = 0; i < numReservas; ++i)
        temp[i] = reservaciones[i];
    temp[numReservas++] = r;

    delete[] reservaciones;
    reservaciones = temp;
}

std::string Huesped::getDocumento() {
    return documento;
}
int Huesped::getAntiguedad() {
    return antiguedad;
}

float Huesped::getPuntuacion() {
    return puntuacion;
}
bool Huesped::disponibleParaFechas(std::string fechaInicioNueva, int nochesNueva) {
    std::tm tmNueva = {};
    std::istringstream ss(fechaInicioNueva);
    ss >> std::get_time(&tmNueva, "%Y-%m-%d");
    time_t inicioNueva = mktime(&tmNueva);
    time_t finNueva = inicioNueva + (nochesNueva * 86400);

    for (int i = 0; i < numReservas; ++i) {
        std::tm tmExistente = {};
        std::istringstream se(reservaciones[i]->getFechaInicio());
        se >> std::get_time(&tmExistente, "%Y-%m-%d");
        time_t inicioExistente = mktime(&tmExistente);
        time_t finExistente = inicioExistente + (reservaciones[i]->getNoches() * 86400);

        // Solapamiento si los rangos se cruzan
        if (inicioNueva < finExistente && inicioExistente < finNueva) {
            return false;
        }
    }
    return true;
}
void Huesped::mostrarReservaciones() {
    if (numReservas == 0) {
        std::cout << "No tienes reservaciones registradas.\n";
        return;
    }

    std::cout << "\n=== Tus reservaciones ===\n";
    for (int i = 0; i < numReservas; ++i) {
        if (reservaciones[i]) {
            std::cout << "\nReserva #" << (i + 1) << ":\n";
            reservaciones[i]->mostrarComprobante();
        } else {
            std::cout << "\n[Error: Reservación inválida en la posición " << i << "]\n";
        }
    }
}



