#include "endpoint/SearchEndpoint.h"

int main(int argc, char** argv)
{
    drogon::app().setLogLevel(trantor::Logger::LogLevel::kTrace);
    drogon::app().addListener("0.0.0.0", 12345);

    auto searchEndpoint = std::make_shared<endpoint::SearchEndpoint>();
    searchEndpoint->initPathRouting();
    drogon::app().registerController(searchEndpoint);

    drogon::app().run();

    return 0;
}