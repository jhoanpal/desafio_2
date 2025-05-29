
// Anfitrion.cpp
#include "anfitrion.h"
#include <iostream>

Anfitrion::Anfitrion() {
    documento = "";
    antiguedad = 0;
    puntuacion = 0;
    alojamientos = nullptr;
    numAlojamientos = 0;
}
int Anfitrion::getAntiguedad() {
    return antiguedad;
}

float Anfitrion::getPuntuacion() {
    return puntuacion;
}


Anfitrion::Anfitrion(std::string doc, int ant, float punt) {
    documento = doc;
    antiguedad = ant;
    puntuacion = punt;
    alojamientos = nullptr;
    numAlojamientos = 0;
}

Anfitrion::~Anfitrion() {
    delete[] alojamientos;
}

void Anfitrion::agregarAlojamiento(Alojamiento* a) {
    Alojamiento** temp = new Alojamiento*[numAlojamientos + 1];
    for (int i = 0; i < numAlojamientos; ++i)
        temp[i] = alojamientos[i];
    temp[numAlojamientos++] = a;

    delete[] alojamientos;
    alojamientos = temp;
}

std::string Anfitrion::getDocumento() {
    return documento;
}

void Anfitrion::mostrarReservaciones(std::string fechaInicio, std::string fechaFin) {
    std::cout << "Reservaciones entre " << fechaInicio << " y " << fechaFin << ":\n";
    for (int i = 0; i < numAlojamientos; ++i)
        alojamientos[i]->mostrarInfo(); // Aquí se puede extender con las reservaciones
}
