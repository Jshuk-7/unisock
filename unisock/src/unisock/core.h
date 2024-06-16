#pragma once

#include <cstdint>
#include <cstddef>

namespace unisock {

    typedef int32_t sockfd;

    struct network_id
    {
        const char* domain;
        const char* service;

        network_id(const char* domain, const char* service)
            : domain(domain), service(service) { }
    };

}
