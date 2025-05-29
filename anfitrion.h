// archivo: Anfitrion.h
#ifndef ANFITRION_H
#define ANFITRION_H

#include <string>
#include "alojamiento.h"

class Anfitrion {
private:
    std::string documento;
    int antiguedad;
    float puntuacion;
    Alojamiento** alojamientos;
    int numAlojamientos;

public:
    Anfitrion();
    Anfitrion(std::string, int, float);
    ~Anfitrion();
    int getAntiguedad();
    float getPuntuacion();
    void agregarAlojamiento(Alojamiento*);
    void mostrarReservaciones(std::string fechaInicio, std::string fechaFin);
    std::string getDocumento();
};

#endif
