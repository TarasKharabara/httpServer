/**
 *
 * This is the Simple http server which support get, post and delete action
 *
 */
#include <iostream>
#include "serverhttp.h"

constexpr int PORT = 8000;

int main()
{
    ServerHTTP server(PORT);
    server.start();

    return 0;
}
