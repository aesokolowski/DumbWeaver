// Server.h
//
// youtube tutorial

#ifndef Server_h
#define Server_h

#include <sys/socket.h>
#include <netinet/in.h>

struct Server
{
    int domain;
    int service;
    int protocol;
    u_long interface;
    int port;
    int backlog;

    struct sockaddr_in address;

    int socket;

    void (*launch)(struct Server *);
};

struct Server server_constructor(int, int, int, u_long, int, int, void (*launch)(struct Server *));

#endif /* Server_h */
 
