FROM mcr.microsoft.com/devcontainers/cpp:1-ubuntu-22.04

# Install additional development tools
RUN apt-get update && export DEBIAN_FRONTEND=noninteractive \
    && apt-get -y install --no-install-recommends \
        cmake \
        make \
        clang-15 \
        clang-tools-15 \
        clang-tidy-15 \
        clang-format-15 \
        libc++-15-dev \
        libc++abi-15-dev \
        lldb-15 \
        gdb \
        valgrind \
        doxygen \
        graphviz \
        libgtest-dev \
        libgmock-dev \
    && apt-get autoremove -y && apt-get clean -y && rm -rf /var/lib/apt/lists/*

# Set up alternatives for clang tools
RUN update-alternatives --install /usr/bin/clang clang /usr/bin/clang-15 100 \
    && update-alternatives --install /usr/bin/clang++ clang++ /usr/bin/clang++-15 100 \
    && update-alternatives --install /usr/bin/clang-tidy clang-tidy /usr/bin/clang-tidy-15 100 \
    && update-alternatives --install /usr/bin/clang-format clang-format /usr/bin/clang-format-15 100 \
    && update-alternatives --install /usr/bin/lldb lldb /usr/bin/lldb-15 100

# Build and install GoogleTest
WORKDIR /tmp
RUN cmake -S /usr/src/googletest -B build -DBUILD_GMOCK=ON -DCMAKE_BUILD_TYPE=Release \
    && cmake --build build --parallel \
    && cmake --install build \
    && rm -rf /tmp/build

WORKDIR /workspace