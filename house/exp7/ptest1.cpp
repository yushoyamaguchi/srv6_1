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
#define PING_NUM 5
#define RTT_AVE 4
#define BIG 1024
#define CHECK_TIMES 10


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

double ping_rtt_return(){
    int count=0;
    double rtt_val;
    std::string ping_str="ping -c ";
    std::string num = std::to_string(PING_NUM);
    ping_str.append(num);
    ping_str.append(" 2001:2::1 -I 2001:12::101");
    char const *ping = ping_str.c_str();
    if ((fp = popen(ping, "r")) != NULL) {
        while (fgets(buf, sizeof(buf), fp) != NULL) {
            count++;
            if(count==PING_LINES+PING_NUM){
                rtt_val=get_rtt(buf);
                
                printf("%s", buf);
            }
        }
        pclose(fp);
        return rtt_val;
    }
    else {
        return BIG;
    }
}

void time_check_route_decide(double route1, double route2){
    if(route1<route2){
            system("ip -6 route del 2001:2::0/64 table 100");
            system("ip -6 route add 2001:2::0/64 encap seg6 mode encap segs 2::20,4::10 dev net0 table 100");
            printf("route1\n");
        }
        else{
            system("ip -6 route del 2001:2::0/64 table 100");
            system("ip -6 route add 2001:2::0/64 encap seg6 mode encap segs 3::20,4::10 dev net0 table 100");
            printf("route2\n");
    }
}

int main(){
    int count=0;
    double route1,route2=0;
    for(count=0;count<CHECK_TIMES;count++){
        
        system("ip -6 rule del from 2001:12::101");
        system("ip -6 rule add from 2001:12::101 table 130 prio 130");
        route1=ping_rtt_return();
        
        system("ip -6 rule del from 2001:12::101");
        system("ip -6 rule add from 2001:12::101 table 140 prio 140");
        route2=ping_rtt_return();
        time_check_route_decide(route1,route2);

        std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    }
    
    return EXIT_SUCCESS;
}