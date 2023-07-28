FROM ubuntu:20.04
ENV DEBIAN_FRONTEND=noninteractive
EXPOSE 5555

RUN dpkg --add-architecture i386
RUN apt-get update && apt-get update --fix-missing
RUN apt-get install -y  \
    make \
    gcc \
    gcc-multilib \
    g++-multilib \
    libcrypt-dev \
    zlib1g-dev:i386 \
    cmake \
    ninja-build \
    git \
    apache2 \
    mesa-common-dev \
    freeglut3 \
    freeglut3-dev \
    libssl-dev:i386 \
    libx11-dev \
    libxrandr-dev \
    libxi-dev \
    libudev-dev \
    libgl1-mesa-dev \
    libsfml-dev \
    libjsoncpp-dev \
    curl \
    zip \
    unzip \
    tar \
    pkg-config \
    openssl \
    libssl-dev \
    uuid-dev \
    net-tools \
    zlib1g-dev \
    libc-ares-dev \
    postgresql-server-dev-all \
    libsqlite3-dev \
    clang-tidy-11
ADD . /mag
WORKDIR /mag
RUN git clone https://github.com/drogonframework/drogon.git
RUN cd drogon && ./build.sh && cd ..
RUN cmake -S ./ -B ./build
RUN cmake --build ./build --parallel

ENTRYPOINT cd build/server && ./server console