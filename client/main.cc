//#include <cstdlib>
//#include <cstring>
#include <iostream>
#include <boost/asio.hpp>
#include "ClientTcpChannel.hh"

int main(int argc, char* argv[])
{
   //Construct Tcp Channel
   std::string url = "rcsdev47.newpace.ca";
   std::string port = "54321";
   boost::asio::io_service eventLoop; //Sadly this cannot be encapsulated in the TcpChannel
   eventLoop.run();
   ClientTcpChannel tcpChannel(url, port, eventLoop);

   //Accept Message from command line
   std::cout << "Enter message: ";
   std::string message;                //TODO: nil value
   std::getline (std::cin, message);

   //Send Message
   tcpChannel.send(message);

   //Get Response
   std::cout << "Response: " << tcpChannel.response() << std::endl;
   return 0;
}
