#include <iostream>
#include <sstream>
#include <thread>
#include <cstdio>
#include <cstdint>
#include <array>  // array
#include <memory>    // shared_ptr
#include <string>    // string
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <istream>
#include <vector>

#define PING_LINES 5
#define PING_NUM 2
#define RTT_AVE 4


FILE* fp;
char  buf[1024];

double get_rtt(char * rtt_rtn){
    std::vector<std::string> v;
    std::string rtt_str=rtt_rtn;
    std::stringstream ss{rtt_str};
    std::string buf;
    while (std::getline(ss, buf, '/')) {
        v.push_back(buf);
    }

    double rtt=stod(v[RTT_AVE]);
    return rtt;
}

void show_ping(){
    int count=0;
    double rtt_val;
    std::string ping_str="ping -c ";
    std::string num = std::to_string(PING_NUM);
    ping_str.append(num);
    ping_str.append(" 2001:2::2 -I 2001:12::101");
    char const *ping = ping_str.c_str();
    if ((fp = popen(ping, "r")) != NULL) {
        while (fgets(buf, sizeof(buf), fp) != NULL) {
            count++;
            if(count==PING_LINES+PING_NUM){
                rtt_val=get_rtt(buf);
                printf("%lf\n",rtt_val);
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