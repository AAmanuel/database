//
//  main.cpp
//  4semestr
//
//  Created by Анна Амануел on 29.04.16.
//  Copyright © 2016 AMANUEL. All rights reserved.
//

#include <boost/bind.hpp>
#include "main.h"

io_service service;
ip::tcp::endpoint ep( ip::tcp::v4(), 1025); // слушаем порт 1025
ip::tcp::acceptor acc(service, ep); //обработчик входящих соединений

void handle_accept(socket_ptr sock, const error_code & err)
{
    if ( err) return;
    
    socket_ptr accsock(new ip::tcp::socket(service));
    start_accept(accsock);
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
