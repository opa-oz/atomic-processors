FROM gcc:latest

ENV DEBIAN_FRONTEND noninteractive

RUN apt-get update && apt-get install -y cmake wget && rm -rf /var/lib/apt/lists/*

WORKDIR /var/atomic_processors

RUN mkdir incl && cd incl && \
    wget "https://github.com/CLIUtils/CLI11/releases/download/v2.0.0/CLI11.hpp" && \
    wget "https://raw.githubusercontent.com/vincentlaucsb/csv-parser/master/single_include/csv.hpp"

COPY config.h.in .
COPY subcommands ./subcommands
COPY utils ./utils
COPY CMakeLists.txt .
COPY main.cpp .

RUN cmake . -DCMAKE_BUILD_TYPE=Release
RUN make

WORKDIR /var/build_artefacts

CMD ["cp", "/var/atomic_processors/AtomicProcessors", "bin"]

