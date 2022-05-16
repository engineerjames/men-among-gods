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
    zlib1g-dev \
    cmake \
    git \
    libssl-dev:i386 \ 
    curl \ 
    zip \
    unzip \
    tar \
    pkg-config \
    libjsoncpp-dev:i386 \
    libjsoncpp-dev \
    clang-tidy-11 \
    uuid-dev

ADD . /mag
WORKDIR /mag
RUN git clone https://github.com/drogonframework/drogon.git --recurse-submodules
RUN cmake -G"Unix Makefiles" -S./drogon -B ./drogon/build
RUN cmake --build ./drogon/build --parallel
RUN cmake --install ./drogon/build
RUN cmake -G"Unix Makefiles" -S ./ -B ./build -DBUILD_SERVER_ONLY=ON
RUN cmake --build ./build --parallel --target server
WORKDIR /mag/build/server
ENTRYPOINT [ "./server", "console" ]