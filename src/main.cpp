#include <iostream>
#include <sglib.h>

int main()
{
    sglib::Logger::SetLogPrefix("NS-Graphics");
    SG_LOG_INFO("Hello World");
}