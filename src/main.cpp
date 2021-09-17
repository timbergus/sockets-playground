#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

#include <thread>

int main()
{
  // ****************

  int socket_fd = socket(AF_INET, SOCK_STREAM, 0);

  if (socket_fd < 0)
  {
    std::cout << "Error creating socket." << std::endl;
    exit(EXIT_FAILURE);
  }

  // ****************

  int port{3500};
  sockaddr_in sockaddr;

  sockaddr.sin_family = AF_INET;
  sockaddr.sin_addr.s_addr = INADDR_ANY;
  sockaddr.sin_port = htons(port);

  if (bind(socket_fd, (struct sockaddr *)&sockaddr, sizeof(sockaddr)) < 0)
  {
    std::cout << "Failed to bind to port " << port << "." << std::endl;
    exit(EXIT_FAILURE);
  }

  // ****************

  if (listen(socket_fd, 10) < 0)
  {
    std::cout << "Failed to listen on socket." << std::endl;
    exit(EXIT_FAILURE);
  }

  std::cout << "Listening on port " << port << std::endl;

  // ****************

  int connection;

  unsigned long addrlen = sizeof(sockaddr);

  while (true)
  {
    connection = accept(socket_fd, (struct sockaddr *)&sockaddr, (socklen_t *)&addrlen);

    if (connection < 0)
    {
      std::cout << "Failed to grab a connection." << std::endl;
      exit(EXIT_FAILURE);
    }

    // ****************

    char request[1024];

    char response[] = "HTTP/1.1 200 OK\nContent-Type: text/html\nContent-Length: 23\nConnection: close\n\n<h1>Hello, world!</h1>";

    if (recv(connection, request, sizeof(request), 0) < 0)
    {
      std::cout << "Failed reading the message." << std::endl;
      exit(EXIT_FAILURE);
    }

    std::cout << "Received: \n\n"
              << request << "\n"
              << std::endl;

    // ****************

    std::cout << "Sending: \n\n"
              << response << "\n"
              << std::endl;

    if (send(connection, response, sizeof(response), 0) < 0)
    {
      std::cout << "Failed sending the message." << std::endl;
      exit(EXIT_FAILURE);
    }
  }

  close(connection);
  close(socket_fd);

  return EXIT_SUCCESS;
}
