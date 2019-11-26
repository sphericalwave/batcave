//Server.hh ============================

#pragma once
#include <cstdlib>
#include <iostream>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include "ServerTcpChannel.hh"

using boost::asio::ip::tcp;

class Server
{
  private:
  boost::asio::io_service& eventLoop;
  tcp::acceptor receiver;  //TODO: Not a clear name...thing that sets up channels

  public:
  Server(boost::asio::io_service& eventLoop_, short port)
    : eventLoop(eventLoop_),
      receiver(eventLoop_, tcp::endpoint(tcp::v4(), port))
  {}

  void listen() {
    ServerTcpChannel* channel = new ServerTcpChannel(eventLoop);
    receiver.async_accept(channel->socket(),  //TODO: This api is gross
      boost::bind(&Server::accept, this, channel,
      boost::asio::placeholders::error));
  }

  private:
  void accept(ServerTcpChannel* channel, const boost::system::error_code& error) { //TODO: improve name...
    if (!error) { channel->start(); } //TODO: improve name...a channel doesn't start
    else { delete channel; }
    listen();
  }
};
