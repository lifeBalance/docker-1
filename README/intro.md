# Introduction
A **Docker container** is a is a lightweight, standalone, executable package of software that includes everything needed to run an application: code, runtime, system tools, system libraries and settings.

> Docker provides a consistent development environment: as long as every team member uses the same **docker image**, they will have available the same system libraries, and the same language runtime no matter the host machine they are using to actually develop.

There are **three stages** when creating a container:

![bird's eye view](./images/docker.png)

* Writing a **dockerfile**.

* Build an docker **image** based on the **dockerfile**.

* Run the **container** based on the **image**.

Another important component of the Docker ecosystem is **Docker hub**, an online repository with thousands of images built by the community around Docker. We can **upload** there, the **images** we create, based on our own dockerfiles, and we can also **download** pre-built images from it.

![dockerhub](./images/dockerhub.png)

---
[:arrow_backward:][back] ║ [:house:][home] ║ [:arrow_forward:][next]

<!-- navigation -->
[home]: ../README.md
[back]: ../README.md
[next]: ./README/00_how_to_docker.md