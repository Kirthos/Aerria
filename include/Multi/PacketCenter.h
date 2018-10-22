#ifndef PACKETCENTER_H_INCLUDED
#define PACKETCENTER_H_INCLUDED

#include <SFML/Network.hpp>
#include <sstream>
#include <string>
#include <iostream>

class PacketCenter
{
    public:
        static void sendToTcp(sf::Packet packet);
        static void connexion(std::string ip, std::string port);
    protected:
    private:
        static bool alreadyConnected;
        static sf::TcpSocket socket;
        static sf::IpAddress m_IP;
        static int m_port;
};

#endif // PACKETCENTER_H_INCLUDED
