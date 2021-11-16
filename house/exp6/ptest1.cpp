#include <iostream>
#include <thread>
#include <cstdio>
#include <cstdint>
#include <array>  // array
#include <memory>    // shared_ptr
#include <string>    // string
#include <stdio.h>
#include <stdlib.h>

const char ping[]="ping -c 2 2001:2::2 -I 2001:12::101";
FILE* fp;
char  buf[1024];

double rtt(char *){
    return 0;
}

void show_ping(){
    int count=0;
    if ((fp = popen(ping, "r")) != NULL) {
        while (fgets(buf, sizeof(buf), fp) != NULL) {
            count++;
            if(count==7){
                printf("%s", buf);
            }
        }
        pclose(fp);
    }
}

int main(){
    int count=0;
    for(count=0;count<3;count++){
        std::this_thread::sleep_for(std::chrono::milliseconds(300));
        system("ip -6 rule del from 2001:12::101");
        system("ip -6 rule add from 2001:12::101 table 130");
        show_ping();
        std::this_thread::sleep_for(std::chrono::milliseconds(300));
        system("ip -6 rule del from 2001:12::101");
        system("ip -6 rule add from 2001:12::101 table 140");
        show_ping();
    }
    
    return EXIT_SUCCESS;
}