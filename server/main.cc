//main.cc ===================

#include <iostream>
#include <boost/asio.hpp>
#include "Server.hh"

using namespace std;

int main(int argc, char* argv[])
{
  int port = 54321;
  std::string url = "rcsdev47.newpace.ca";
  cout << "Make requests at: " << url << "/" << port << "\n";
  boost::asio::io_service eventLoop;
  Server server(eventLoop, port);
  server.listen();
  eventLoop.run(); //Must be the last line
  return 0;
}
