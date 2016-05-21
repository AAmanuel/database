#include <boost/asio.hpp>

//загружаем определения из областей видимости
using namespace boost::asio;
using boost::system::error_code;

typedef boost::shared_ptr<ip::tcp::socket> socket_ptr;

#ifndef SERVER_H
#define SERVER_H

void start_accept(socket_ptr sock);
void handle_accept(const error_code & err);

int main(int argc, const char * argv[]);

#endif // SERVER_H
