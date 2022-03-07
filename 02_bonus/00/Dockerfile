FROM	debian:buster-slim

WORKDIR	/root/leaky

RUN		apt-get update && \
		apt-get upgrade -y && \
		apt-get install valgrind make gcc -y && \
		bash