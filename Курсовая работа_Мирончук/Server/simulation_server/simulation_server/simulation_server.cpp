#include <SFML/Network.hpp>
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

int main()
{
    sf::TcpListener listener;
    if (listener.listen(9000) != sf::Socket::Done) {
        std::cout << "Can't 9000\n";
        return 1;
    }
    sf::SocketSelector selector;
    std::vector<sf::TcpSocket*> sockets;

    selector.add(listener);
    while (true) {
        if (selector.wait()) {
            if (selector.isReady(listener)) {
                sf::TcpSocket* socket = new sf::TcpSocket;
                if (listener.accept(*socket) != sf::Socket::Done) {
                    delete socket;
                }
                else {
                    std::cout << "New connection is made\n";
                    sockets.push_back(socket);
                    selector.add(*socket);
                }
            }
            else {
                for (int i = 0; i < sockets.size(); i++) {
                    if (selector.isReady(*sockets[i])) {
                        std::cout << "Socket is ready\n";
                        sf::Packet packet;
                        switch (sockets[i]->receive(packet)) {
                        case sf::Socket::Done: {
                            std::cout << "Got a packet\n";
                            std::string s;
                            packet >> s;
                            std::cout << "Got: " << s << '\n';
                            if (s == "upload") {
                                std::cout << "Someone uploads\n";
                                std::string name, file;
                                packet >> name >> file;
                                std::cout << "Name: " << name << '\n';
                                // std::cout << file << '\n';
                                std::ofstream fout(name);
                                fout << file;
                                fout.close();
                            }
                            else if (s == "download") {
                                std::string name;
                                packet >> name;
                                std::ifstream fin(name);
                                packet.clear();
                                if (!fin) {
                                    packet << "notExists";
                                    sockets[i]->send(packet);
                                }
                                else {
                                    std::string file;
                                    std::stringstream buf;
                                    buf << fin.rdbuf();
                                    file = buf.str();

                                    packet << "ok" << file;
                                    sockets[i]->send(packet);
                                }
                            }
                            break;
                        }

                        case sf::Socket::Disconnected:
                            std::cout << "Someone disconnected\n";
                            selector.remove(*sockets[i]);
                            delete sockets[i];
                            sockets.erase(sockets.begin() + i);
                            i++;
                            break;

                        default:
                            break;
                        }
                    }
                }
            }
        }
    }
}