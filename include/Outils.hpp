#ifndef OUTILS_H
#define OUTILS_H

#include <iostream>

class Outils
{
    public:
        Outils();
        void setOutils(int ID);
        int getPuissance();
        float getVitesse();
    protected:
        float m_vitesse;
        int m_puissance;
    private:
};

#endif // OUTILS_H
