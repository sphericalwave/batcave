#include <cstdlib>
#include <cstring>
#include <iostream>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

enum { max_length = 1024 };

class ClientTcpChannel
{
  private:
  boost::asio::io_service& eventLoop;
  std::string url;
  std::string port;
  tcp::socket socket;
  size_t messageByteCount;  //TODO: Mutable State

  public:
  //i'd like to hide the ioService but i cant bcs i must be shared
  ClientTcpChannel(std::string url_, std::string port_, boost::asio::io_service& _eventLoop)
    : url(url_),
      port(port_),
      socket(_eventLoop),
      eventLoop(_eventLoop)
  {
    //code in constructor is undesirable bcs constructors are for construction
    //boost is the cause
    //it's nonsensical to have a TcpChannel that is not connected
    //which is why connect is here
    connect();
  }

  void connect() {
    tcp::resolver resolver(eventLoop);
    tcp::resolver::query query(tcp::v4(), url, port);
    tcp::resolver::iterator iterator = resolver.resolve(query);
    boost::asio::connect(socket, iterator);
  }

  void send(std::string message) {
    //TODO: Factor string to char array conversion out of this method
    int n = message.length();
    char charArray[n+1];
    strcpy(charArray, message.c_str());
    messageByteCount = strlen(charArray); //TODO: Mutable State
    boost::asio::write(socket, boost::asio::buffer(charArray, messageByteCount));
  }

  std::string response() {
    char reply[max_length];
    //Attempt to read a certain amount of data from a stream before returning.
 //   size_t reply_length = boost::asio::read(socket, mBuf);
    size_t reply_length = boost::asio::read(socket, boost::asio::buffer(reply, messageByteCount)); //Attempt to read a certain amount of data from a stream before returning.
    std::string msg = convertToString(reply, messageByteCount);
    return msg;
  }

  //TODO: Move into a Class
  std::string convertToString(char* a, int size) {
    int i;
    std::string s = "";
    for (i = 0; i < size; i++) { s = s + a[i]; }
    return s;
  }

  //TODO: Requires allocating memory =(
 /* char* convertToCharArray(std::string str) {
    int n = str.length();
    char charArray[n+1];
    strcpy(charArray, str.c_str());
    return charArray;
  }*/
};
