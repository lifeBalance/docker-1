# Dockerfiles
A [Dockerfile](https://docs.docker.com/engine/reference/builder/) is a text file with a set of instructions used by the [docker build](https://docs.docker.com/engine/reference/commandline/build/). Each of these instructions is used to generate a **read-only layer** in the **Docker image**. When we `run` an image to generate a **container**, we're adding a new **writable layer** (the “container layer”) on top of the underlying layers. All changes made to the running container, such as writing new files, modifying existing files, and deleting files, are written to this writable container layer.


---
[:arrow_backward:][back] ║ [:house:][home] ║ [:arrow_forward:][next]

<!-- navigation -->
[home]: ../README.md
[back]: ./intro.md
[next]: ../README.md