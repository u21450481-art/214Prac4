FROM ubuntu:22.04

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && apt-get install -y --no-install-recommends \
        g++ \
        make \
        gdb \
        valgrind \
        ca-certificates \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /taskforge

COPY . .


RUN make clean && make

CMD ["./taskforge"]
