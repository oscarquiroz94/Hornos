#ifndef __EMULADORPLANTA
#define __EMULADORPLANTA

class EmuladorPlanta
{
    public:
        /*gain, period, tau*/
        EmuladorPlanta(double gain, double period, double tau) :
            ganancia(gain), periodo(period), tao(tau) {}

        double emular(double accion)
        {
            out = (ganancia * periodo / (2*tao + periodo)) * ( accion + accion_ant) + ((2*tao - periodo)/(2*tao + periodo))*out_ant;
            out_ant = out;
            accion_ant = accion;
            return out;
        }

    protected:
        double out     = 0.0;
        double out_ant = 0.0;
        double accion_ant  = 0.0;
        double ganancia    = 0.5;
        double periodo     = 0.2;
        double tao         = 0.4;

};


class EmuladorPlantaIntegradora : public EmuladorPlanta
{
    public:
        /*gain, period, tau*/
        EmuladorPlantaIntegradora(double gain, double period, double tau) :
                EmuladorPlanta(gain, period, tau) {}

        double emular(double accion)
        {
            out += EmuladorPlanta::emular(accion);
            return out;
        }

    private:
        double out = 0.0;
};


#endif