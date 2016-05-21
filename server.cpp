#include <boost/bind.hpp>
#include "server.h"
#include "storage.h"

io_service service;
ip::tcp::endpoint ep( ip::tcp::v6(), 1025); // слушаем порт 1025
ip::tcp::acceptor acc(service, ep); //обработчик входящих соединений

void handle_accept(socket_ptr sock, const error_code & err)
{
    if ( err) return;
    
    socket_ptr nextsock(new ip::tcp::socket(service));
    start_accept(nextsock);
}

void start_accept(socket_ptr sock)
{
    acc.async_accept(
        *sock,
        boost::bind( handle_accept, sock, _1) //конструируем лямбда-функцию для async_accept
    );
}

int main(int argc, const char * argv[]) {

    socket_ptr sock(new ip::tcp::socket(service));
    start_accept(sock);
    service.run();
    return 0;
}
