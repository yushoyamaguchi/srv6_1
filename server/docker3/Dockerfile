FROM slankdev/ubuntu:20.04

RUN apt update \
 && apt install -y cmake\
 && git clone https://github.com/CESNET/libyang.git\
 && cd libyang\
 && git checkout v2.0.0\
 && mkdir build\
 && cd build\
 && pwd \
 && cmake -D CMAKE_INSTALL_PREFIX:PATH=/usr \
      -D CMAKE_BUILD_TYPE:String="Release" ..\
 && make\
 && sudo make install\