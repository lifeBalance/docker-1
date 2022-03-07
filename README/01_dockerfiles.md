# 01. Dockerfiles

## Exercise 00
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

## Exercise 01
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

## Exercise 02
In this exercise we have to create a `Dockerfile` to containerize Rails applications. The main constraint is that our `Dockerfile` must be *generic*, so that it can be called from the following `Dockerfile`:
```
FROM ft-rails:on-build
EXPOSE 3000
CMD ["rails", "s", "-b", "0.0.0.0", "-p", "3000"]
```

Our generic `Dockerfile`, must do the following:

1. Install, via a [ruby image](https://hub.docker.com/_/ruby), all the necessary dependencies and gems.
2. Copy our rails application to the `/opt/app` folder of your container.
3. Launch the migrations and the db population for our Rails application.

The child `Dockerfile` (see code above) should launch the rails server.

1. Since [RoR](https://guides.rubyonrails.org/getting_started.html) has the following dependencies:

	* Ruby itself (obviously included in the ruby official image).
	* SQLite3
	* Node.js
	* Yarn

I decided that a good approach was to spin a Ruby container and see what's in there:
```
docker run -it --rm ruby:buster bash
ruby -v
ruby 3.1.1p18 (2022-02-18 revision 53f5fc4236) [x86_64-linux]
sqlite3
bash: sqlite3: command not found
node -v
bash: node: command not found
```

Once the **dependencies** are installed on our **base image**, the remaining instructions on our `Dockerfile` will use the [ONBUILD](https://docs.docker.com/engine/reference/builder/#onbuild) directive. All the instructions we add using this directive, will be triggered after, when the **child image** is build. It's as if we were placing this instructions in the downstream image, right after its [FROM](https://docs.docker.com/engine/reference/builder/#from) directive.

2. Since we're not well versed on [RoR](https://rubyonrails.org/), we'll just clone a [sample Rails app](https://github.com/mhartl/sample_app_6th_ed) to our **physical machine**:
```
git clone https://github.com/mhartl/sample_app_6th_ed.git sample_app
```

Then whe just have to `ONBUILD ADD` it to the **image**.

3. The database migration will be done using `ONBUILD RUN`.

Once our **parent** `Dockerfile` is done, we can build the image:
```
docker build -t ft-rails:on-build ft-rails/.
[...]
docker images
REPOSITORY                  TAG        IMAGE ID       CREATED         SIZE
ft-rails                    on-build   1bea42e61e31   6 seconds ago   934MB
```

> We can do so from the directory where we have the downstream `Dockerfile` (the one we were given in the subject's pdf). We just have to specify the path were the **parent** `Dockerfile` is.

If everything went OK, we should see our new image tagged (per pdf requirements) as `on-build`. Now we can build the **children** image:
```
docker build -t rodrodri/ror_app ./
```

Finally, to test everything, we just have to run:
```
docker run --rm -p 3000:3000 rodrodri/ror_app
```

## Exercise 03
For this exercise we have to design a `Dockerfile` that creates an image, that once running, gets us our [own instance of Gitlab](https://about.gitlab.com/install/). The container will allow us to access the Gitlab instance via the web client, create users and interact via GIT with this container (HTTPS and SSH).

> The subject's pdf provides a link to the [Gitlab FOSS](https://gitlab.com/gitlab-org/gitlab-foss) repository (hosted at github.com, nah, just kidding), but all development has now moved to https://gitlab.com/gitlab-org/gitlab. There they recommend to install GitLab using any of the [Omnibus packages](https://about.gitlab.com/downloads/), so we went for [the one for Debian](https://about.gitlab.com/install/#debian).

By default, Omnibus GitLab does not use HTTPS, but [detailed instructions](https://docs.gitlab.com/omnibus/settings/nginx.html#manually-configuring-https) are provided.

To **build** the image:
```
docker build -t rodrodri/ginlab .
```

To **run** the container:
```
docker run -it --rm -p 8080:80 -p 8022:22 -p 8443:443 --privileged -e GITLAB_ROOT_EMAIL="12341234" rodrodri/ginlab bash
```

> If you choose a **port** other than the standards (`80` and `443`), don't forget to add it at the end of the **domain name** when you try to access the site in the browser.

---
[:arrow_backward:][back] ║ [:house:][home] ║ [:arrow_forward:][next]

<!-- navigation -->
[home]: ../README.md
[back]: ./README/00_how_to_docker.md
[next]: ./README/02_bonus.md