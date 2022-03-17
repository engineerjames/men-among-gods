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
    curl \ 
    zip \
    unzip \
    tar \
    pkg-config \
    clang-tidy-11

ADD . /mag
WORKDIR /mag
RUN git clone https://github.com/Microsoft/vcpkg.git
RUN ./vcpkg/bootstrap-vcpkg.sh
RUN ./vcpkg/vcpkg integrate install
RUN cmake -G"Unix Makefiles" -S ./ -B ./build -DCMAKE_TOOLCHAIN_FILE=/mag/vcpkg/scripts/buildsystems/vcpkg.cmake
RUN cmake --build ./build --parallel --target server
RUN ./build/server/server
