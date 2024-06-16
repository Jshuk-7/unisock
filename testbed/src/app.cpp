#include <unisock/unisock.h>

#include <iostream>

int main(int argc, char** argv)
{
    unisock::sock socket;
    if (socket.init(unisock::socket_type::TCP, unisock::network_id("127.0.0.1", "4095")) == -1)
    {
        perror("init");
    }

    if (socket.bind() == -1)
    {
        perror("bind");
    }

    if (socket.listen(2) == -1)
    {
        perror("listen");
    }

    socket.terminate();
}