### BUILDER ###
FROM ubuntu:22.04 AS builder

ENV DEBIAN_FRONTEND=noninteractive
RUN apt update && apt install -y \
	git \
	python3 \
	python3-pip \
	libboost-all-dev \
	asciidoc \
	source-highlight \
	doxygen \
	graphviz \
	cmake

# vSomeIP
WORKDIR /root
RUN git clone https://github.com/COVESA/vsomeip.git vsomeip
RUN mkdir -p vsomeip/build
RUN cmake -S vsomeip -B vsomeip/build
WORKDIR /root/vsomeip/build
RUN make && make install

# CommonAPI
WORKDIR /root
RUN git clone --branch 3.2.0 https://github.com/COVESA/capicxx-core-runtime.git capicxx-core-runtime
RUN mkdir -p capicxx-core-runtime/build
RUN cmake -S capicxx-core-runtime -B capicxx-core-runtime/build
WORKDIR /root/capicxx-core-runtime/build
RUN make && make install

### IMAGE ###
FROM ubuntu:22.04

RUN apt update && apt install -y \
	git \
	vim \
	build-essential \
	cmake

COPY --from=builder /usr/local/lib /usr/local/lib
COPY --from=builder /usr/local/include /usr/local/include
RUN ldconfig /etc/ld.so.conf.d
ENV LD_LIBRARY_PATH=/usr/local/lib