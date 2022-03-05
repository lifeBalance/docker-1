# 01. Dockerfiles

## Exercise 01
Here we have to write a dockerfile with the following requirements:

1. It must be based on the [alpine image](https://hub.docker.com/_/alpine).
2. To that image we'll install our favourite text editor (vim or emacs).
3. Once the resulting image is `run`, the text editor must be launched.

Once the Dockerfile is written, we can `build` the **image** using:
```
docker build -t rodrodri/docker-vim .
```

Finally, we'll use `docker run` to spin a **container** based on the **image** we just build. In this case we must specify the `-it` flags to be sure a **pseudo-tty** is allocated (otherwise vim won't work properly):
```
docker run -it --rm rodrodri/vim
```

## Exercise 02
For this exercise we have to write a `Dockerfile`:

1. The `Dockerfile` will be based in a [debian image](https://hub.docker.com/_/debian).
2. We will download the source code, compile and install a TeamSpeak server.
3. The server has launch along with our container, and at least one user should be able to connect to it and engage in a normal discussion.

In order to find out the commands we have to add to our `Dockerfile` to install the server, nothing like spinning a Debian container and actually install it. First thing I did was visiting the [TeamSpeak Downloads page](https://www.teamspeak.com/en/downloads/), and on the [server tab](https://www.teamspeak.com/en/downloads/#server), I copied the [download link](https://files.teamspeak-services.com/releases/server/3.13.6/teamspeak3-server_linux_amd64-3.13.6.tar.bz2). Then I spinned a Debian container:
```
docker run -it --rm debian
```

Then I installed the packages:
```
# apt update
# apt install wget bzip2
# cd
# wget https://files.teamspeak-services.com/releases/server/3.13.6/teamspeak3-server_linux_amd64-3.13.6.tar.bz2
# tar -xvf teamspeak3-server_linux_amd64-3.13.6.tar.bz2 
# cd teamspeak3-server_linux_amd64
# ./ts3server_minimal_runscript.sh
Please set the environment variable TS3SERVER_LICENSE to "accept" in order to accept the license agreement.
Alternatively, create a file named ".ts3server_license_accepted" in the working directory or start the server with the command line parameter "license_accepted=1".
To view the license agreement set TS3SERVER_LICENSE to "view" in order to print the license to the console.
Alternatively view the file "LICENSE" in your favorite text viewer yourself.
```

From the output of the installation script, we learned that in order to **accept** the **license terms**, we have three choices:

1. Set the **environment variable** `TS3SERVER_LICENSE` to `"accept"`.
2. Create a **file** named `.ts3server_license_accepted` in the working directory.
3. Start the server with the **command line parameter** `license_accepted=1`.

Once we deal with the **license terms** (via environment variable this time), we launched the server successfully. From the output we learned some of the **ports** that the server uses. Since it wasn't quite clear, a google search lead me to [this site](https://support.teamspeak.com/hc/en-us/articles/360002712257-Which-ports-does-the-TeamSpeak-3-server-use-)

* **Voice** uses port `9987` with `UDP` protocol.
* **File Transfer** uses `30033`, with `TCP`.
* **Query Server** uses `10011`.

Which means we should relaunch our container with these ports published:
```
docker run -it -p 9987:9987/udp -p 10011:10011 -p 30033:30033 -e TS3SERVER_LICENSE=accept debian
```

> The [official Docker TeamSpeak image](https://hub.docker.com/_/teamspeak) contains a line similar to the one above.

After that, we can install the [TeamSpeak client](https://teamspeak.com/en/downloads/) in our **host machine**, so we can connect to the server at `localhost`. We'll be asked for a **token**, that we can copy from the server output.

Once we've tested that the server runs OK, and that we ca connect to it, we can put it all in a `Dockerfile` (see `02/Dockerfile`). To `build` the **image**:
```
docker build -t rodrodri/teamspeak-server .
docker images		# check that the image exists
```

To `run` the container:
```
docker run --rm -it -p 9987:9987/udp -p 10011:10011 -p 30033:30033 rodrodri/teamspeak-server
```

> Warning! Trying to download the package with the server using the `ADD` directive, was always crashing the server. I had to install `wget` and download the package with it.

---
[:arrow_backward:][back] ║ [:house:][home] ║ [:arrow_forward:][next]

<!-- navigation -->
[home]: ../README.md
[back]: ./README/00_how_to_docker.md
[next]: ./README/02_bonus.md