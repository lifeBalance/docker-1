# 00. How to docker
For this part we just have to write Docker commands into files (no need to make them executable).

## Exercise 1
For this exercise we have to: Get the [hello-world](https://hub.docker.com/_/hello-world) container from the [Docker Hub](https://hub.docker.com), where it’s available.

As we mentioned in our introduction, **Docker Hub** is an important part of the Docker ecosystem. If we visit the site, we can **search** for any image available in the repository. Typing `hello world` takes us to the *hello world's* **official image**, so we just have to copy the command and paste it in our terminal.

![pull hello world](./images/pull_hello_world_image.png)

That will **download** the hello world **image** to some location in our disk. This location depends on the **host** where we're using Docker:
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
3. It should be able to restart on its own.
4. It should have its `80` port attached to the `5000` port of your machine. You can check that your container functions properly by visiting http://localhost:5000 on your web browser.

1. To run a container in the [background](https://docs.docker.com/engine/reference/run/#detached-vs-foreground) (so we don't lose access to our command prompt) we should use `-d=true` or just `-d`.
2. To [name](https://docs.docker.com/engine/reference/run/#name---name) a container: `--name overlord`.
3. To make it [restart](https://docs.docker.com/config/containers/start-containers-automatically/) we have to use the flag `--restart` with the `always` policy.
4. To make a port available to services outside of Docker, or to Docker containers which are not connected to the container’s network, use the `--publish` or `-p` flag. This creates a **firewall rule** which maps a container port to a port on the Docker host to the outside world. This is known as [publishing ports](https://docs.docker.com/config/containers/container-networking/). The syntax is:
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

---
[:arrow_backward:][back] ║ [:house:][home] ║ [:arrow_forward:][next]

<!-- navigation -->
[home]: ../README.md
[back]: ../README.md
[next]: ./README/01_dockerfiles.md