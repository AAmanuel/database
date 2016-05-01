//
//  main.h
//  4semestr
//
//  Created by Анна Амануел on 01.05.16.
//  Copyright © 2016 AMANUEL. All rights reserved.
//

#include <boost/asio.hpp>

//загружаем определения из областей видимости
using namespace boost::asio;
using boost::system::error_code;

typedef std::shared_ptr<ip::tcp::socket> socket_ptr;

#ifndef main_h
#define main_h

void start_accept(socket_ptr sock);
void handle_accept(const error_code & err);

int main(int argc, const char * argv[]);

#endif /* main_h */
