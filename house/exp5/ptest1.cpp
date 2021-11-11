#include <iostream>
#include <thread>
#include <cstdio>
#include <cstdint>
#include <array>  // array
#include <memory>    // shared_ptr
#include <string>    // string
#include <stdio.h>
#include <stdlib.h>

const char ping[]="ping -c 1 192.168.12.1";
FILE* fp;
char  buf[1024];



int main(){
    
    for(int i=0;i<3;i++){
        
        std::this_thread::sleep_for(std::chrono::milliseconds(3000));
        if ((fp = popen(ping, "r")) != NULL) {
            while (fgets(buf, sizeof(buf), fp) != NULL) {
                printf("%s", buf);
            }
            pclose(fp);
        }
    }
    return EXIT_SUCCESS;
}