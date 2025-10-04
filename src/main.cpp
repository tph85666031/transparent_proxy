#include "com_base.h"
#include "com_log.h"
#include "comex_poco.h"

#include "sp_sdk_driver.h"

class MyComexPocoProxyServer : public ComexPocoProxyServer
{
public:
    MyComexPocoProxyServer()
    {
    }

    ~MyComexPocoProxyServer()
    {
    }

    bool onQueryAddr(const sockaddr_storage& addr_from, sockaddr_storage& addr_to)
    {
        LOG_I("called");
        return false;
    }

    int onHttpRequest(const std::string uri, const std::string method, const std::map<std::string, std::string> headers, const uint8* data, int data_size)
    {
        LOG_I("called,uri=%s", uri.c_str());
        return ACTION_PASS;
    }

    int onHttpResponse(const std::string uri, const std::string method, const std::map<std::string, std::string> headers, const uint8* data, int data_size, int http_code)
    {
        LOG_I("called,uri=%s", uri.c_str());
        return ACTION_PASS;
    }
};

int main(int argc, const char* argv[])
{
    ComOption opt;
    opt.addOption("ip", "ip from");

    opt.parse(argc, argv);

    MyComexPocoProxyServer server;
    server.setPort(8000, 8001, 8002, 8003);
    server.setCA("/data/libcomex/ca.crt", "/data/libcomex/ca.key");
    server.startServer();
    getchar();
    return 0;
}

