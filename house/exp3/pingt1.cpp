#include <iostream>
#include <thread>
#include <cstdio>
#include <cstdint>

const char ping_route1[]="ping 10.1.0.2 -c 3 -I 10.0.0.2";
const char ping_route2[]="ping 10.1.0.2 -c 3 -I 10.0.0.12";

int main(){

    system(ping_route1);
    system(ping_route2);
    return EXIT_SUCCESS;
}