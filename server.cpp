#include <SFML/Network.hpp>
#include <iostream>

#include "message.h"

int main() {
  sf::TcpListener listener;
  // Bind listener to a port
  if (listener.listen(12000) != sf::Socket::Done) {
    // error....
    std::cerr << "Could not listen to port \n";
    return EXIT_FAILURE;
  }
  std::cout << "Server running ! \n";
  while (true) {
    // accept a new connection
    sf::TcpSocket client;
    if (listener.accept(client) != sf::Socket::Done) {
      // error
      std::cerr << "Could not accept client \n";
      return EXIT_FAILURE;
    }
    std::cout << "Client" << client.getRemoteAddress() << ':'
              << client.getRemotePort() << "is connected \n";
    Message messageReceived;
    sf::Packet requestReceived;

    if (client.receive(requestReceived) != sf::Socket::Done) {
      std::cout << "Did not received message correctly \n";
    }
    requestReceived >> messageReceived;
    std::cout << "Client: " << client.getRemoteAddress() << ':'
              << client.getRemotePort() << " sent: " << messageReceived.content
              << '\n';

    sf::Packet answer;
    answer << messageReceived;

    if (client.send(answer) != sf::Socket::Done) {
      std::cout << "Did not send answer message correctly \n";
    }
  }
}