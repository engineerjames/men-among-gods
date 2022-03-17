FROM ubuntu:20.04
ENV DEBIAN_FRONTEND=noninteractive 
EXPOSE 5555

RUN dpkg --add-architecture i386
RUN apt-get update
RUN apt-get install -y  \
    make \
    gcc \
    gcc-multilib \
    g++-multilib \
    libcrypt-dev \
    zlib1g-dev:i386 \
    cmake \
    apache2

ADD . /mag
WORKDIR /mag
RUN cmake -G"Unix Makefiles" -S ./ -B ./build
RUN cmake --build ./build --parallel
RUN ./build/server/server
