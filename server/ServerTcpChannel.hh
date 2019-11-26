//Channel.hh =====================================

#pragma once
#include <cstdlib>
#include <iostream>
#include <boost/bind.hpp>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

class ServerTcpChannel
{
  private:
  tcp::socket channel; //TODO: It sucks that a channel is named a socket
  enum { max_length = 1024 };
  char data_[max_length];

  public:

  ServerTcpChannel(boost::asio::io_service& eventLoop) //TODO: Construct w socket
    : channel(eventLoop) { }

  tcp::socket& socket() { //TODO: Hide from server. router_.async_accept(channel->socket(),
    return channel;
  }

  void start() {
    channel.async_read_some(boost::asio::buffer(data_, max_length),
      boost::bind(&ServerTcpChannel::read, this,
      boost::asio::placeholders::error,
      boost::asio::placeholders::bytes_transferred));
  }

  private:

  void read(const boost::system::error_code& error, size_t bytes_transferred){
    if (!error) {
      boost::asio::async_write(channel,
        boost::asio::buffer(data_, bytes_transferred),
        boost::bind(&ServerTcpChannel::write, this,
        boost::asio::placeholders::error));
    }
    else { delete this; }
  }

  void write(const boost::system::error_code& error) {
    if (!error) {
      channel.async_read_some(boost::asio::buffer(data_, max_length),
        boost::bind(&ServerTcpChannel::read, this,
        boost::asio::placeholders::error,
        boost::asio::placeholders::bytes_transferred));
    }
    else { delete this; }
  }
};
