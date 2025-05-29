// archivo: Alojamiento.h
#ifndef ALOJAMIENTO_H
#define ALOJAMIENTO_H

#include <string>

class Anfitrion;

class Alojamiento {
private:
    std::string codigo;
    std::string nombre;
    std::string tipo;
    std::string direccion;
    std::string departamento;
    std::string municipio;
    float precioNoche;
    std::string* amenidades;
    int numAmenidades;
    Anfitrion* anfitrion;

public:
    std::string getNombre();
    std::string getTipo();
    std::string getDireccion();
    std::string getMunicipio();
    std::string getDepartamento();
    float getPrecioNoche();
    int getNumAmenidades();
    std::string getAmenidad(int);
    Anfitrion* getAnfitrion();

    Alojamiento();
    Alojamiento(std::string, std::string, std::string, std::string, std::string, float, std::string*, int, Anfitrion*);
    ~Alojamiento();

    std::string getCodigo();
    bool estaDisponible(std::string fechaInicio, int noches); // Método base
    void mostrarInfo();
};

#endif
