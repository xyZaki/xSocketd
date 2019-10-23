#include <iostream>
#include <socketd.hpp>

using namespace std;
using namespace NS_LIBSOCKET;

void msg_cgi(int cfd, const struct sockaddr_in *caddr)
{
	char _recv[100];
    char _send[] = "server message : hello client";

	recv(cfd, _recv, sizeof(_recv), 0);

	cout << _recv << endl;

	send(cfd, _send, sizeof(_send), 0);

	return;
}

int main(void)
{
	try
	{
		socketd_tcp_v4 TCP;

		TCP.server_init("127.0.0.1", 80, msg_cgi);
		TCP.server_emit(BLOCK);
	}
	catch(const char *str)
	{
		cout << str << endl;
	}

    return 0;
}

