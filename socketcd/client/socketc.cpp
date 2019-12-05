/**-----------------------------------------------------------------------------------------------------------------
 * @file	socketc.cpp
 * @brief	Client-side TCP/IP stack library with POSIX 1003.1g standard socket API
 *
 * Copyright (c) 2019-2019 Jim Zhang 303683086@qq.com
 *------------------------------------------------------------------------------------------------------------------
*/

#include <socketcd/client/socketc.hpp>


using namespace NS_SOCKETCD;


/*
--------------------------------------------------------------------------------------------------------------------
*
*			                                  FUNCTIONS IMPLEMENT
*
--------------------------------------------------------------------------------------------------------------------
*/

/**
 *	@brief	    Create TCP/IP socket 
 *	@param[in]  _P	- TCP/IP stack protocol 
 *	@param[out] None
 *	@return		None
 **/
socketc_client::socketc_client(enum TCP_IP_STACK _P)
{
	int domain, type, protocol;

	switch (_P)
	{
		case TCPv4:
			domain   = SOCKETCD_DOMAIN_POSIX1_AF_INET			;
			type     = SOCKETCD_TYPE_POSIX1_SOCK_STREAM		; 
			protocol = SOCKETCD_PROTOCOL_POSIX1_IPPROTO_TCP	; 
			break;
		case TCPv6:
			domain   = SOCKETCD_DOMAIN_POSIX1_AF_INET6			;
			type     = SOCKETCD_TYPE_POSIX1_SOCK_STREAM		; 
			protocol = SOCKETCD_PROTOCOL_POSIX1_IPPROTO_TCP	; 
			break;
		case UDPv4:
			domain   = SOCKETCD_DOMAIN_POSIX1_AF_INET			;
			type     = SOCKETCD_TYPE_POSIX1_SOCK_DGRAM			; 
			protocol = SOCKETCD_PROTOCOL_POSIX1_IPPROTO_UDP	; 
			break;
		case UDPv6:
			domain   = SOCKETCD_DOMAIN_POSIX1_AF_INET6			;
			type     = SOCKETCD_TYPE_POSIX1_SOCK_DGRAM			; 
			protocol = SOCKETCD_PROTOCOL_POSIX1_IPPROTO_UDP	; 
			break;
		default: ;
	}

	socketfd = socket(domain, type, protocol);

	if (-1 == socketfd){perror("Socket create failure");exit(-1);}
}

/**
 *	@brief	    Set TCP/IP socket options
 *	@param[in]  level	-	SOCKETCD_LEVEL_XXX 
 *	@param[in]  option  -	SOCKETCD_OPT_XXX
 *	@param[in]  _switch -	true/false
 *	@param[out] None
 *	@return		None
 *	@note		The function suitable the option which value is bool 
 **/
void socketc_client::set_socket_opt(int level, int option, bool _switch)
{
	int ret = 0, optval = _switch;

	ret = setsockopt(socketfd, level, option, &optval, sizeof(optval));

	if (-1 == ret) {perror("Socket option set failure"); exit(-1);}

	return;
}

/**
 *	@brief	    Set TCP/IP socket options
 *	@param[in]  level	-	SOCKETCD_LEVEL_XXX 
 *	@param[in]  option  -	SOCKETCD_OPT_XXX
 *	@param[in]  optval	-   option value
 *	@param[in]  optlen	-   option value length	
 *	@param[out] None
 *	@return		None
 *	@note		The function suitable the option which value is structure 
 **/
void socketc_client::set_socket_opt(int level, int option, void *optval, socklen_t optlen)
{
	int ret = 0;

	ret = setsockopt(socketfd, level, option, optval, optlen);

	if (-1 == ret) {perror("Socket option set failure"); exit(-1);}

	return;
}

/**
 *	@brief	    Recive data from socket
 *	@param[in]  len	   - data buffer length 
 *	@param[in]  flags  - SOCKETCD_RECV_MSG_XXX or 0 
 *	@param[out] data 
 *	@return		Bytes length of data/0 when no data	or peer has been over
 **/
ssize_t socketc_client::data_recv(void *buff, size_t len, int flags)
{
	ssize_t size = -1;

	size = recv(socketfd, buff, len, flags);

	if (-1 == size) {perror("Data rcve error"); exit(-1);}

	return size;
}

/**
 *	@brief	    Send data into socket
 *	@param[in]  data 
 *	@param[in]  len	   - data length 
 *	@param[in]  flags  - SOCKETCD_SEND_MSG_XXX or 0 
 *	@param[out] None
 *	@return		Bytes length of data
 **/
ssize_t socketc_client::data_send(void *data, size_t len, int flags)
{
	ssize_t size = -1;

	size = send(socketfd, data, len, flags);

	if (-1 == size) {perror("Data send error"); exit(-1);}

	return size;
}

/*
--------------------------------------------------------------------------------------------------------------------
*			                                   TCP/IP IMPLEMENT
--------------------------------------------------------------------------------------------------------------------
*/

/**
 *	@brief	    Initial socket client 
 *	@param[in]  ip 
 *	@param[in]  port - Application layer protocol port 
 *	@param[out] None
 *	@return		None
 **/
void socketc_tcp_v4::client_init(const char *ip, in_port_t port)
{
	int ret = 0;

    caddr.sin_family	  = AF_INET;
    caddr.sin_addr.s_addr = inet_addr(ip);
    caddr.sin_port		  = htons(port);
    bzero(caddr.sin_zero, sizeof(caddr.sin_zero));

    ret = connect(socketfd, (struct sockaddr *)&caddr, sizeof(caddr));

	if (-1 == ret) {perror("Socket client connect failure"); exit(-1);}

	return;
}

/**
 *	@brief	    Start socket client 
 *	@param[in]  None 
 *	@param[out] None
 *	@return		None
 **/
//void socketc_tcp_v4::client_emit(void)

