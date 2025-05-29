// archivo: Huesped.h
#ifndef HUESPED_H
#define HUESPED_H

#include <string>
#include "Reservacion.h"

class Huesped {
private:
    std::string documento;
    int antiguedad;
    float puntuacion;
    Reservacion** reservaciones;
    int numReservas;

public:
    void mostrarReservaciones();
    int getAntiguedad();
    float getPuntuacion();
    Huesped();
    Huesped(std::string, int, float);
    ~Huesped();

    void agregarReservacion(Reservacion*);
    bool disponibleParaFechas(std::string fechaInicio, int noches);
    std::string getDocumento();
};

#endif
