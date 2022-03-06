FROM	debian:stable

EXPOSE	9987/udp 10011 30033

RUN		apt-get update && \
		apt-get upgrade -y && \
		apt-get install -y bzip2 wget

RUN		wget https://files.teamspeak-services.com/releases/server/3.13.6/teamspeak3-server_linux_amd64-3.13.6.tar.bz2 && \
		tar xvfj teamspeak3-server_linux_amd64-3.13.6.tar.bz2

ENV		TS3SERVER_LICENSE=accept

WORKDIR		/teamspeak3-server_linux_amd64

ENTRYPOINT	["sh", "ts3server_minimal_runscript.sh"]