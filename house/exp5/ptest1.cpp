#include <iostream>
#include <thread>
#include <cstdio>
#include <cstdint>
#include <array>  // array
#include <memory>    // shared_ptr
#include <string>    // string
#include <stdio.h>
#include <stdlib.h>

const char ping[]="ping -c 5 192.168.12.1";
FILE* fp;
char  buf[1024];

double rtt(char *){
    return 0;
}

int main(){
    int count;
    

    count=0;
    std::this_thread::sleep_for(std::chrono::milliseconds(30));
    if ((fp = popen(ping, "r")) != NULL) {
        while (fgets(buf, sizeof(buf), fp) != NULL) {
            count++;
            if(count==10){
                printf("%s", buf);
            }
        }
        pclose(fp);
    }
    return EXIT_SUCCESS;
}