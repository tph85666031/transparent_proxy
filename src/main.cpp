#include "com_base.h"
#include "com_log.h"
#include "comex_poco.h"

#include "sp_sdk_driver.h"
#include "sp_project.h"

class MyComexPocoProxyServer : public ComexPocoProxyServer, public SpSdkDriver
{
public:
    MyComexPocoProxyServer()
    {
        init(1);
        clearFileRule();
        clearProcRule();
        clearNetRule();

        addNetRule("curl", "0.0.0.0", 443, "0.0.0.0", "127.0.0.1", 8001, ACL_NET_EVENT_CONNECT, ACL_ACTION_PROXY);
        addNetRule("firefox", "0.0.0.0", 443, "0.0.0.0", "127.0.0.1", 8001, ACL_NET_EVENT_CONNECT, ACL_ACTION_PROXY);
        addNetRule("firefox", "0.0.0.0", 80, "0.0.0.0", "127.0.0.1", 8000, ACL_NET_EVENT_CONNECT, ACL_ACTION_PROXY);
        LOG_I("file_rule=%s", getFileRule().c_str());
        LOG_I("proc_rule=%s", getProcRule().c_str());
        LOG_I("net_rule=%s", getNetRule().c_str());
    }

    ~MyComexPocoProxyServer()
    {
    }

    bool onQueryAddr(const sockaddr_storage& addr_from, sockaddr_storage& addr_to)
    {
        return queryNetRule(addr_from, addr_to);
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

    com_log_init(NULL, NULL, true);
    MyComexPocoProxyServer server;
    server.setPort(8000, 8001, 8002, 8003);
    server.startServer();
    getchar();
    return 0;
}

