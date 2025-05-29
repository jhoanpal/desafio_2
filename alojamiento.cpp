// Alojamiento.cpp
#include "alojamiento.h"
#include <iostream>

Alojamiento::Alojamiento() {
    codigo = nombre = tipo = direccion = departamento = municipio = "";
    precioNoche = 0;
    amenidades = nullptr;
    numAmenidades = 0;
    anfitrion = nullptr;
}
std::string Alojamiento::getNombre() {
    return nombre;}
std::string Alojamiento::getTipo() {
    return tipo;}
std::string Alojamiento::getDireccion() {
    return direccion;}
std::string Alojamiento::getMunicipio() {
    return municipio;}
std::string Alojamiento::getDepartamento() {
    return departamento;}
float Alojamiento::getPrecioNoche() {
    return precioNoche;}
int Alojamiento::getNumAmenidades() {
    return numAmenidades;}
std::string Alojamiento::getAmenidad(int i) {
    if (i >= 0 && i < numAmenidades)
        return amenidades[i];
    return "";}
Anfitrion* Alojamiento::getAnfitrion() {
    return anfitrion;}

Alojamiento::Alojamiento(std::string cod, std::string nom, std::string tip,
                         std::string dir, std::string muni, float precio,
                         std::string* amen, int numAmen, Anfitrion* anf) {
    codigo = cod;
    nombre = nom;
    tipo = tip;
    direccion = dir;
    municipio = muni;
    precioNoche = precio;
    numAmenidades = numAmen;

    amenidades = new std::string[numAmen];
    for (int i = 0; i < numAmen; ++i)
        amenidades[i] = amen[i];

    anfitrion = anf;
}

Alojamiento::~Alojamiento() {
    delete[] amenidades;
}

std::string Alojamiento::getCodigo() {
    return codigo;
}

void Alojamiento::mostrarInfo() {
    std::cout << "Alojamiento: " << nombre << " (" << codigo << ")\n"
              << "Tipo: " << tipo << "\n"
              << "Direccion: " << direccion << ", " << municipio << ", " << departamento << "\n"
              << "Precio por noche: $" << precioNoche << "\n"
              << "Amenidades: ";
    for (int i = 0; i < numAmenidades; ++i)
        std::cout << amenidades[i] << (i < numAmenidades - 1 ? ", " : "\n");
}
