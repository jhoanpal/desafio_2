// archivo: Reservacion.h
#ifndef RESERVACION_H
#define RESERVACION_H

#include <string>

class Alojamiento;
class Huesped;



class Reservacion {

private:
    std::string codigo;
    std::string fechaInicio;
    int noches;
    std::string metodoPago;
    std::string fechaPago;
    float monto;
    std::string anotaciones;
    Alojamiento* alojamiento;
    Huesped* huesped;

public:
    int getNoches();
    Reservacion();
    Reservacion(std::string, std::string, int, std::string, std::string, float, std::string, Alojamiento*, Huesped*);
    ~Reservacion();

    void mostrarComprobante();
    std::string getCodigo();
    std::string getFechaInicio();
};

#endif
