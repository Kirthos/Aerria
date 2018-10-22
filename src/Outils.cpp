#include "Outils.hpp"
using namespace std;

Outils::Outils()
{
}
void Outils::setOutils(int ID)
{
    switch (ID) {
        case 0:
            m_vitesse=0.5;
            m_puissance=1;
            cout<<"Wooden Pickaxe"<<endl;
            break;
        case 1:
            m_vitesse=0.4;
            m_puissance=2;
            cout<<"Iron Pickaxe"<<endl;
            break;
        case 2:
            m_vitesse=0.3;
            m_puissance=3;
            cout<<"Gold Pickaxe"<<endl;
            break;
        case 3:
            m_vitesse=0;
            m_puissance=999999;
            cout<<"Ultimate Pickaxe"<<endl;
            break;
        default:
            m_vitesse=0;
            m_puissance=0;
            cout<<"Unknow Pickaxe"<<endl;
  }
}
int Outils::getPuissance()
{
    return m_puissance;
}
float Outils::getVitesse()
{
    return m_vitesse;
}
