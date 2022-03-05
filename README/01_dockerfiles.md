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

---
[:arrow_backward:][back] ║ [:house:][home] ║ [:arrow_forward:][next]

<!-- navigation -->
[home]: ../README.md
[back]: ./README/00_how_to_docker.md
[next]: ./README/02_bonus.md