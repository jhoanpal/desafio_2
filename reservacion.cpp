// Reservacion.cpp
#include "reservacion.h"
#include <iostream>

Reservacion::Reservacion() {
    codigo = fechaInicio = metodoPago = fechaPago = anotaciones = "";
    noches = 0;
    monto = 0.0;
    alojamiento = nullptr;
    huesped = nullptr;
}

int Reservacion::getNoches(){
    return noches;
}

Reservacion::Reservacion(std::string cod, std::string fecha, int n, std::string metodo,
                         std::string pago, float m, std::string nota, Alojamiento* a, Huesped* h) {
    codigo = cod;
    fechaInicio = fecha;
    noches = n;
    metodoPago = metodo;
    fechaPago = pago;
    monto = m;
    anotaciones = nota;
    alojamiento = a;
    huesped = h;
}

Reservacion::~Reservacion() {}

void Reservacion::mostrarComprobante() {
    std::cout << "=== COMPROBANTE DE RESERVA ===\n"
              << "Codigo: " << codigo << "\n"
              << "Fecha de inicio: " << fechaInicio << "\n"
              << "Noches: " << noches << "\n"
              << "Metodo de pago: " << metodoPago << "\n"
              << "Monto: $" << monto << "\n"
              << "Anotaciones: " << anotaciones << "\n";
}

std::string Reservacion::getCodigo() {
    return codigo;
}

std::string Reservacion::getFechaInicio() {
    return fechaInicio;
}

