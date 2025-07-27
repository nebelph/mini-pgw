#pragma once

#include "HttpServer.h"
#include "UdpServer.h"

class ServerLauncher {
public:
    ServerLauncher( std::shared_ptr<UdpServer> &, std::shared_ptr<HttpServer> &);

    void launch();

private:
    std::shared_ptr<UdpServer> m_udp_server;
    std::shared_ptr<HttpServer> m_http_server;
};