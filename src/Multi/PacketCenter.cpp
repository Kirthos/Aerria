#include "Multi/PacketCenter.h"
#include "Multi/MainMulti.h"

bool PacketCenter::alreadyConnected;
sf::TcpSocket PacketCenter::socket;
sf::IpAddress PacketCenter::m_IP;
int PacketCenter::m_port;

void PacketCenter::sendToTcp(sf::Packet packet)
{
    socket.send(packet);
}
void PacketCenter::connexion(std::string ip, std::string port)
{
    m_IP = ip;

    std::istringstream iss(port); // on transforme le string port en int pour la fonction socket.connect();
    iss >> m_port;

    sf::Socket::Status status = socket.connect(m_IP, m_port);
    if (status != sf::Socket::Done)
    {
        std::cout << "Impossible de se connecter au serveur !";
        return;
    }
    MainMulti multi;
    multi.run();
}
