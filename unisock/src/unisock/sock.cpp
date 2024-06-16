#include "sock.h"

#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>

#include <iostream>
#include <unordered_map>
#include <cstring>

namespace unisock {

    static std::unordered_map<int32_t, addrinfo> s_addrinfos;
    static std::unordered_map<int32_t, sockaddr_storage> s_last_connections;

    int socket_type_to_protocol(socket_type type)
    {
        switch (type)
        {
            case socket_type::TCP: return SOCK_STREAM;
            case socket_type::UDP: return SOCK_DGRAM;
        }

        return 0;
    }

    int32_t sock::init(socket_type type, network_id id)
    {
        addrinfo hints;
        memset(&hints, 0, sizeof(hints));
        hints.ai_family = AF_UNSPEC;
        hints.ai_socktype = socket_type_to_protocol(type);

        addrinfo* res = nullptr;
        
        int status = getaddrinfo(id.domain, id.service, &hints, &res);

        addrinfo* it = nullptr;

        for (it = res; it != NULL; it = it->ai_next)
        {
            m_fd = socket(it->ai_family, it->ai_socktype, it->ai_protocol);
            if (m_fd <= 0)
                continue;

            s_addrinfos[m_fd] = *it;
            break;
        }

        if (it == NULL)
        {
            fprintf(stderr, "Error: failed to create socket\n");
            freeaddrinfo(res);
            return -1;
        }

        freeaddrinfo(res);

        return 0;
    }

    void sock::terminate()
    {
        close(m_fd);
    }

    int32_t sock::bind()
    {
        addrinfo addr = s_addrinfos.at(m_fd);
        
        return ::bind(m_fd, addr.ai_addr, addr.ai_addrlen);
    }
    
    int32_t sock::listen(size_t backlog)
    {
        return ::listen(m_fd, backlog);
    }
    
    int32_t sock::accept()
    {
        sockaddr_storage conn;
        socklen_t len = sizeof(sockaddr_storage);

        int32_t result = ::accept(m_fd, (sockaddr*)&conn, &len);

        s_last_connections[m_fd] = conn;

        return result;
    }

    int32_t sock::connect()
    {
        addrinfo addr = s_addrinfos.at(m_fd);

        return ::connect(m_fd, addr.ai_addr, addr.ai_addrlen);
    }
    
}
