#pragma once

#include "core.h"

namespace unisock {

    enum class socket_type
    {
        TCP,
        UDP,
    };

    class sock
    {
    public:
        int32_t init(socket_type type, network_id id);
        void terminate();

        int32_t bind();
        int32_t listen(size_t backlog);
        int32_t accept();
        int32_t connect();

    private:
        sockfd m_fd;
    };

}