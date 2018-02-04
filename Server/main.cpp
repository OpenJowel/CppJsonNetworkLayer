#include <iostream>
#include <thread>

#include "App.hpp"

using namespace std;


int main()
{
    /*
    int port = 13337;

    if(!tcp.setup(port)){
        return 0;
    }

    initCallbacks();

    tcp.startAccepting();

    mainLoop();


    tcp.terminate();
    */

    App app;
    app.start();

    return 0;
}
