# 00. How to docker
For this part we just have to write Docker commands into files (no need to make them executable).

## Exercise 1
For this exercise we have to: Get the [hello-world](https://hub.docker.com/_/hello-world) container from the [Docker Hub](https://hub.docker.com).

As we mentioned in our introduction, **Docker Hub** is an important part of the Docker ecosystem. If we visit the site, we can **search** for any image available in the repository. Typing `hello world` takes us to the *hello world's* **official image**, so we just have to copy the command and paste it in our terminal.

![pull hello world](./images/pull_hello_world_image.png)

That will **download** the hello world **image** to some location in our disk. To verify that we downloaded the `hello-world` image to our disk, we can run:
```
docker images
```

 This location depends on the **host** where we're using Docker:
* In a Linux host, images are stored in `/var/lib`
* In a macOS host, Docker stores images in a single, large disk image (64 GB on my system) under:
```
~/Library/Containers/com.docker.docker/Data/vms/0/data/Docker.raw
```

## Exercise 2
For this task we have to: **Launch** the hello-world **container**, and make sure that it prints its welcome message, then leaves it.

This is fundamental to understand the idea of **spinning** a **container** our of an **image**. We use the `docker run image-name` for that. But how do we know what's the exact **name of the image**? Well, you can use:
```
docker images
REPOSITORY    TAG       IMAGE ID       CREATED        SIZE
hello-world   latest    feb5d9fea6a5   5 months ago   13.3kB
```

## Exercise 3
Launch a [nginx container](https://hub.docker.com/_/nginx), available on Docker Hub.

1. It should be run as a **background** task.
2. It should be named `overlord`.
3. It should be able to **restart** on its own.
4. It should have its `80` port attached to the `5000` port of your machine. You can check that your container functions properly by visiting http://localhost:5000 on your web browser.

1. To run a container in the [background](https://docs.docker.com/engine/reference/run/#detached-vs-foreground) (so we don't lose access to our command prompt) we should use `-d=true` or just `-d`.
2. To [name](https://docs.docker.com/engine/reference/run/#name---name) a container: `--name overlord`.
3. To make it [restart](https://docs.docker.com/config/containers/start-containers-automatically/) we have to use the flag `--restart` with the `always` policy.
4. To make a port available to services outside of Docker, or to Docker containers which are not connected to the container???s network, use the `--publish` or `-p` flag. This creates a **firewall rule** which maps a container port to a port on the Docker host to the outside world. This is known as [publishing ports](https://docs.docker.com/config/containers/container-networking/). The syntax is:
`-p host_port:container_port`.

> At the end of all the options, we have to specify the **image name** (in this case `nginx`). If the `nginx` image is not found **locally**, it'll be automatically pulled from **Dockerhub** to our machine, and spins a **container** based on that image.

To check that `nginx` is running, we could execute `docker ps` (to access the list of **running containers**), or we could just open our web browser and point it to http://localhost:5000. That should show the default **Welcome to nginx!** web site.

## Exercise 4
To get the **internal IP** address of the ``overlord`` **container** without starting its shell and
using only one command, we have two options:

* `docker container inspect container_name`
* `docker inspect container_name`

That will produce all the **container information** as a [JSON](https://en.wikipedia.org/wiki/JSON) object. In order to extract the information regarding the **internal IP** we can use the `--format` option (`-f` for short), followed by a [Go template](https://pkg.go.dev/text/template), that allows us to manipulate the output.

> A Go template is just two sets of curly braces, as in `{{.someProperty}}`` that must be wrapped in **single quotes** in order to escape its meaning in our shell ([brace expansion](https://www.gnu.org/software/bash/manual/html_node/Brace-Expansion.html).

Since the output was a bit overwhelming, I decided to redirect it to a file named `overlord.json`, and study it carefully in my text editor. Then it was a matter of locating the **nested object** named `NetworkSettings`, and then access its `IPAddress` property using **dot notation**.

## Exercise 5
For this exercise we have to:

1. Launch a shell in an [alpine](https://hub.docker.com/_/alpine) container.
2. This shell must be **interactive**.
3. The **container** must delete itself when we **log out** of the shell.

1. [Alpine Linux](https://alpinelinux.org/) is a security-oriented, lightweight Linux distribution. We can `pull` its official **image** from **Docker Hub**, while at the same time **spin** a container using `docker run alpine`.
2. Since we must interact with the shell, we'll have to use the ``--interactive`` option (`-i` for short) plus allocate a pseudo-TTY using the ``--tty`` option (``-t`` for short).
3. In order to [clean up](https://docs.docker.com/engine/reference/run/#clean-up---rm) the container upon finishing execution, we'll use the ``--rm`` flag.

According to the documentation, a Docker container that runs in foreground mode will only have its **standard output stream** (`STDOUT`) and **standard error stream** (`STDERR`) attached if we don???t add the ``-a`` option. That's because those are the only necessary streams to output stuff, or return the return value (`0` if all went OK).

![docker streams](./images/docker_streams.png)

We can run a **shell process** in two modes:

* In **non-interactive mode**, the shell executes the script passed to it and exits (we'd use `docker exec` for this).
* In **interactive mode**, the shell listens to the commands through the **standard input stream** (`STDIN`) on a terminal.

## Exercise 6
For this exercise we have to:

1. Launch a [Debian](https://hub.docker.com/_/debian) container.
2. Make sure that the **package manager** and the **packages** already in the container are updated.
3. Install via the container???s package manager everything you need to compile C source code and push it onto a git repo.

For this exercise, we should **only** specify the commands to be run directly in the container, which implies we must launch an **interactive** Debian container:
```
docker run -it --rm debian /bin/bash
```

Then it's a matter of installing `git`, a compiler such as `gcc`, and a build tool like `make`; in short, all the necessary stuff to compile C code.

## Exercise 7
In this exercise we're asked to create a **volume** named `hatchery`.

> [Volumes](https://docs.docker.com/storage/volumes/) are the preferred mechanism for persisting data **generated by** and **used by** Docker **containers**. While [bind mounts](https://docs.docker.com/storage/bind-mounts/) are dependent on the directory structure and OS of the host machine, volumes are completely managed by Docker.

Basic commands regarding volumes are:

* To **create a volume** we use the `docker volume create` command, followed by the name we want to give the volume.
* To **list all existing volumes** we use the `docker volume ls` command, which can be useful to verify we've created one.
* To **inspect a volume** we use `docker volume inspect`,  followed by the name of the volume we want to inspect.
* To **remove a volume** we use `docker volume rm`,  followed by the name of the volume we want to remove.

## Exercise 8
In this one we're asked to **list** all the Docker volumes created on the machine (Just read above).

## Exercise 9
This exercise is a bit more involved; we have to:

1. Launch a `mysql` container as a **background** task.
2. The container has to be named `spawning-pool`.
3. It should be able to **restart** on its own in case of **error**.
4. The container directly creates a **database** named `zerglings`.
5. The **root password** of the database should be `Kerrigan`.
4. The database is stored in the `hatchery` volume.

1. To launch a `mysql` container we'll use `docker run mysql`, which takes care of downloading the [official mysql image](https://hub.docker.com/_/mysql) if it doesn't exist in our system. Since it has to run as a **background** process, we'll use the `-d=true` (or `-d` for short).
2. To name a **container** we use the `--name` option, followed by the name.
3. To make it **restart** automatically on failure we can use the `--restart` option with the `on-failure` value. It's quite convenient to limit the number of times the Docker daemon attempts to restart the container using the `:max-retries` option. If we keep trying to restart the container **indefinitely**, it could possibly lead to a **denial of service** on the host. So a good idea is to set the value of `:max-retries` to `5`, hence `on-failure:5`.
4. From the [official mysql image](https://hub.docker.com/_/mysql) page on **Docker Hub**, we learn that there are several **environment variables** that we can use to configure the MySQL instance. To set the **database name** we can use the `MYSQL_DATABASE` variable. One of the options we can use with `docker run` is `--env` (or `-e` for short), followed the the variable we want to set.
5. To set the **root password** we can use the `MYSQL_ROOT_PASSWORD`.
6. Finally, to store the database in the `hatchery` volume we have a couple of choices:

* The `--volume` flag (`-v` for short).
* The `--mount` flag, more explicit and verbose.

The `-v` flag consists of **three fields** separated by **colon characters** (`:`), in the following order:

* **Name of the volume**, which can be omitted if we're content with an **anonymous volume**.
* The **path** where the volume is mounted in the **container**. We'll choose `/var/lib/mysql`, because that's where MySQL by **default** will write its data files.
* An **optional** comma-separated **list of options**. We won't be using any options this time.

> Feel free to read the official docs about the [--mount flag](https://docs.docker.com/storage/volumes/#choose-the--v-or---mount-flag).

## Exercise 10
Here we're asked to print the **environment variables** of the `spawning-pool` container, which we can use to verify that is configured according to the requirements established in the last exercise.

We'll use the `docker inspect` command, along with the `--format` option. To print the **environment variables** we'll use a [Go template](https://pkg.go.dev/text/template) with the `.Config.Env` key.

## Exercise 11
In this exercise we have to:

1. Launch a [wordpress](https://wordpress.com/) container as a **background** task.
2. The container should be named `lair`.
3. Its **port 80** should be bound to the **port 8080** of a **virtual machine**.
4. It should be able to use the `spawning-pool` container as a **database service**.

At the end of this, we should be able to access `lair` on our **host machine** via a web browser, with the IP address of the **virtual machine** as a URL.

1. To launch the container in the background we used `-d`.
2. To name it, `--name` followed by the name `lair`.
3. To bind the ports we used `-p 8080:80`.
4. To set up the connection to the database container we used several **environment variables** using the `-e` flag.

> Apparently, for this exercise, both containers can be run in the same **Docker Host**, so no need to install Docker in a **virtual machine** for now.

Once the **WordPress container** is running, we have to find a way for it to connect with the **MySQL container**. Considering that the `--link` option is already **deprecated**, these are the steps we followed:

1. Create a network:
```
docker network create wp_mysql_net
```

2. Connect both containers to the network:
```
docker network connect wp_mysql_net spawning-pool
docker network connect wp_mysql_net lair
```

Finally, to test that everything works, we just have to point our web browser to `http://localhost:8080`, and create some post on our WordPress site.

## Exercise 12
For this exercise we have to:

1. Launch a [phpmyadmin](https://www.phpmyadmin.net/) container as a **background** task.
2. It should be named `roach-warden`.
3. Its **port 80** should be bound to the **port 8081** of the virtual machine and it should be able to explore the database stored in the `spawning-pool` container.

Luckily for us, **Docker Hub** offers a [phpmyadmin official image](https://hub.docker.com/_/phpmyadmin). Pulling and spinning a **container** based on this image shouldn't be a problem, we just have to use the commands we're already familiar with. In order to connect it to the other containers, we have to connect the `roach-warden` to the same network used by the `spawning-pool` container (the one serving the MySQL database):
```
docker network connect wp_mysql_net roach-warden
```

Finally, to test that everything works, we just have to point our web browser to `http://localhost:8081`, and logging in using the `root` credentials (`Kerrigan`) we created for the database.

## Exercise 13
In order to access the `spawning-pool` container???s logs in real time without running its shell, we can use the `docker logs` command. The `--follow` option (`-f` for short) allows us to *follow* the logs in real time.

> If when checking the logs you find the `mbind: Operation not permitted` error, you may want to restart the MySQL container with `--security-opt seccomp=unconfined` (don't forget to re-add it to the network).

## Exercise 14
Display all the currently **active** containers on your machine. If, by *active*, we understand **running**, then we have to use `docker ps` (if we wanted to see them all, we would add the `--all` flag, `-a` for short).

## Exercise 15
In this exercise we're asked to **relaunch** the overlord container. For restarting containers we have two options:

1. After **version 1.13**: `docker container restart overlord'
2. Prior to **version 1.13**: `docker restart overlord'

After running this command we could do a `docker ps` to check the time the container has been running (under the `STATUS` column).

## Exercise 16
For this exercise we have to:

1. Launch a Python container (`2-slim` version), named `Abathur`.
2. Its `/root` folder will be bound to the `HOME` folder on your **host**.
3. Its **port 3000** will be bound to the **port 3000** of your virtual machine.
4. We will install latest version of the the [Flask micro-framework](https://flask.palletsprojects.com/en/2.0.x/), and make it serve an html page displaying `"Hello World"` with `<h1>`. We will test that pointing `curl` or a **web browser**, to the IP address of your virtual machine on the **port 3000**.

> We have to also list all the necessary commands to set up our **Flask webapp**.

1. We can pull a specific version of an **image** using the syntax `image:version`.
2. In this case we have to use a [bind mount](https://docs.docker.com/storage/bind-mounts/) to mount the `HOME` directory on the **host** into the container. Same as with volumes, we can use the `--mount` or `-v` options; in this case we use as argument the syntax `/path/in/host:/path/in/container` (we don't need any **options** in the 3rd argument).
3. To publish the port, we use the familiar syntax `host_port:container_port`.
4. To execute commands on a running container we use `docker exec`. So in this case, we need to:

 * Install a Python package named `Flask`, using `pip`.
 * Run our `Flask` webapp.

I decided to add the app itself in a separate file named `app.py`, that we can place in the `HOME` folder of our **host** machine so that will be available at the **bind mount** of the container, at the `/root` directory.

> Don't forget to move/copy the `app.py` to the root of your home directory during evaluation.

## Exercise 17
Here we have to:

1. Create a local **swarm**.
2. Our local machine (the school iMac) should be its **manager**.

> Read notes about Docker swarms.

We can achieve both things simultaneously using the [docker swarm init](https://docs.docker.com/engine/reference/commandline/swarm_init/) command. The docker engine targeted where we run this command becomes a **manager** in the newly created swarm (a **single-node** swarm for now).

> We can check that the Docker engine in our **host machine** has become a node (the `Leader`) using `docker node ls`, which as the syntax implies, allows us to list the nodes in a swarm.

## Exercise 18
In this exercise we have to:

1. Create a **virtual machine** using virtualbox; it has to be set up with a **static IP**, so that it's accessible by our **host**.
2. Install and configure Docker in the VM.

1. The virtual machine was set up with two **network interfaces**: one configured with `NAT` (to have internet access), whereas the other one was set up as a **Host-only adapter**, so that we can assign a **static IP** to the virtual machine.
2. I installed Docker in it using the [repository approach](https://docs.docker.com/engine/install/ubuntu/#install-using-the-repository).

## Exercise 19
Here we'll have to configure the **docker node** running in the **virtual machine** as a **slave** of the local swarm in which your local machine is the **leader** (the command to take control of the VM is not requested).

> In order to comply with the campaign for removal of racial terms from tech, it seems that the Docker documentation has replaced the term **leader** by **manager**, whereas the term **slave** is now **worker**. But still, the output of `docker swarm ls` shows the `MANAGER STATUS` as `Leader`.

For this task we can follow two approaches:

1. In the same **machine** we **initialized** the swarm, we could have **copied** the output line with a command/token that we could use to join the swarm in another **machine**.
2. But if we forgot to copy the line mentioned above, we could run (in the **manager**) `docker swarm join-token worker`; then copy the line and paste it into the machine's shell you want to turn into a **worker**.

## Exercise 20
In this exercise we have to create an [overlay network](https://docs.docker.com/network/overlay/) named `overmind`. It has to be **internal**, meaning that external access to the network is restricted.

We can use the command `docker network inspect overmind` to check the properties of the network, and check that `Internal` is set to true.

## Exercise 21
For this task we have to:

1. Launch a [RabbitMQ](https://www.rabbitmq.com/) as a [Docker service](https://docs.docker.com/engine/swarm/how-swarm-mode-works/services/) that will be named `orbital-command`.
2. Define a specific **user** and **password** for this service (they can be whatever).
3. This service will be on the `overmind` network.

## Exercise 22
To list all the services in the local swarm we use the [docker service ls](https://docs.docker.com/engine/reference/commandline/service_ls/) command.

## Exercise 23
For this exercise we have to:

1. Launch a [42school/engineering-bay](https://hub.docker.com/r/42school/engineering-bay) service.
2. This service will be named `engineering-bay`.
3. It will be on the `overmind` network.
4. It will have two replicas.

According to the documentation provided at [hub.docker.com](https://hub.docker.com/r/42school/engineering-bay), we must have an `orbital-command` running on your host or swarm, accessible with the same name into your network. To connect to this `orbital-command`, we must set:
```
OC_USERNAME : Username used to access to orbital-command
OC_PASSWD : Password used to access to orbital-command
```

## Exercise 24
Here we have to get the **real-time logs** of **one the tasks** of the engineering-bay service.

We could to do two things:

1. Use the [docker service ps](https://docs.docker.com/engine/reference/commandline/service_ps/) command, to find the **ID** of any of the **tasks**. The `--filter` and `--quiet` options are useful here.
2. Wrap the command above with some shell command expansion, and use is as argument for the [docker service logs](https://docs.docker.com/engine/reference/commandline/service_logs/) command. Use `--follow` to see a live version of the logs.

## Exercise 25
For this exercise we have to launch:

1. A [42school/marine-squad](https://hub.docker.com/r/42school/marine-squad) service.
2. This service will be named `marines`.
3. It will be on the `overmind` network.
4. It will have **two replicas**.

According to the documentation provided at [hub.docker.com](https://hub.docker.com/r/42school/marine-squad), we must have an `orbital-command` running on your host or swarm, accessible with the same name into your network. To connect to this `orbital-command`, we must set:
```
OC_USERNAME : Username used to access to orbital-command
OC_PASSWD : Password used to access to orbital-command
```

## Exercise 26
Here we just have to display **all** the tasks of the `marines` service. We saw before that we can easily do that using the [docker service ps](https://docs.docker.com/engine/reference/commandline/service_ps/) command, passing the **name of the service**, `marines` in this case.

## Exercise 27
In this exercise we have to increase the number of replicas of the `marines` service up to twenty. Easily done using the [docker service scale](https://docs.docker.com/engine/reference/commandline/service_scale/); we just have to pass as argument `marines=20`, i.e., the **name of the service** then the **number of replicas** we need.

Then, we're advised to check the **tasks** of the service:
```
docker service ps marines
```

And check the **logs**:
```
docker service logs marines			# use service name (or id)
docker service logs oecy1dgngboy	# use task id
```

## Exercise 28
For this exercise we're asked to force quit and delete **all** the **services** on the local **swarm**, **in one command**. Since it has to be in one command, we need to find a way of listing either the **name** of the services, or just their **IDs**:
```
docker service ls --format '{{.Name}}'	# List the services by name
docker service ls --quiet				# List the services by id
```

Then, we could wrap any of the commands above with some shell command expansion, and pass it as argument to the [docker service rm](https://docs.docker.com/engine/reference/commandline/service_rm/) command, which can be used to remove one or more services.

> During **evaluation**, run with `sh 28`

## Exercise 29
Here we have to force quit and delete **all** the **containers** (whatever their status), **in one command**. Similarly to what we did above, first we'll list the **containers** either by `ID` or by `.Name`:
```
docker container ls --all --format '{{.Names}}'		# List the containers by name
docker container ls --all --quiet					# List the containers by id
```

Then we could wrap any any of the commands above with some shell command expansion, and pass it as argument to the [docker container rm](https://docs.docker.com/engine/reference/commandline/container_rm/) command, which can be used to remove one or more containers.

> Since some of the containers may be still running, we have to use the `--force` option (a better approach would be to stop the container before removing it, but we've been asked to remove them all **in one command**).

> During **evaluation**, run with `sh 29`

## Exercise 30
Finally, we have to delete all the images stored on your local machine machine, **in one command** as well. Yet again we'll use a similar strategy; first we'll list the images using the [docker image ls](https://docs.docker.com/engine/reference/commandline/image_ls/) command:
```
docker images --all --quiet						# List the images by id
docker images --all --format '{{.Repository}}'	# List the images by name
```

Then we get rid of them all using the [docker image rm](https://docs.docker.com/engine/reference/commandline/image_rm/) command.

> During **evaluation**, run with `sh 30`

---
[:arrow_backward:][back] ??? [:house:][home] ??? [:arrow_forward:][next]

<!-- navigation -->
[home]: ../README.md
[back]: ../README.md
[next]: ./01_dockerfiles.md