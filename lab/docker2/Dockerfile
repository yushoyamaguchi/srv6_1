FROM slankdev/ubuntu:20.04


# (base=slankdev/ubuntu20:04) basic package install

RUN apt update \
 && apt install -y cmake iproute2 libatm1 \
            libmnl0 libpopt0 libxtables12 logrotate \
            git autoconf automake libtool make libreadline-dev texinfo \
            pkg-config libpam0g-dev libjson-c-dev bison flex \
            libc-ares-dev python3-dev python3-sphinx \
            install-info build-essential libsnmp-dev perl \
            libcap-dev python2 libelf-dev libzmq5 libzmq3-dev\
            protobuf-c-compiler libprotobuf-c-dev libpcre2-dev \
 && curl https://bootstrap.pypa.io/pip/2.7/get-pip.py --output get-pip.py \
 && python2 ./get-pip.py \
 && git clone https://github.com/CESNET/libyang.git\
 && cd libyang\
 && git checkout v2.0.0\
 && mkdir build\
 &&  cd build\
 && cmake -D CMAKE_INSTALL_PREFIX:PATH=/usr \
      -D CMAKE_BUILD_TYPE:String="Release" ..\
 && make\
 && sudo make install\
 && cd ..\
 && groupadd -r -g 92 frr \
 && groupadd -r -g 85 frrvty \
 && adduser --system --ingroup frr --home /var/run/frr/ \
   --gecos "FRR suite" --shell /sbin/nologin frr \
 && usermod -a -G frrvty frr \
 && git clone -b Nyatsume-draft-ietf-lsr-isis-srv6-extensions https://github.com/Nyatsume/frr \
 && cd frr \
 && ./bootstrap.sh \
 && ./configure \
    --prefix=/usr \
    --includedir=\${prefix}/include \
    --bindir=\${prefix}/bin \
    --sbindir=\${prefix}/lib/frr \
    --libdir=\${prefix}/lib/frr \
    --libexecdir=\${prefix}/lib/frr \
    --localstatedir=/var/run/frr \
    --sysconfdir=/etc/frr \
    --with-moduledir=\${prefix}/lib/frr/modules \
    --with-libyang-pluginsdir=\${prefix}/lib/frr/libyang_plugins \
    --enable-configfile-mask=0640 \
    --enable-logfile-mask=0640 \
    --enable-snmp=agentx \
    --enable-multipath=64 \
    --enable-user=frr \
    --enable-group=frr \
    --enable-vty-group=frrvty \
    --with-pkg-git-version \
    --with-pkg-extra-version=-MyOwnFRRVersion\
 && make \
 && make install \