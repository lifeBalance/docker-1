# 02. Bonus

## 00. Valgrind
Containerizing [Valgrind]() was a no brainer for a C programmer so. To **build** the image:
```
docker build -t rodrodri/valgrind .
```

To **run** the container, we just have to add a rule in our `Makefile`:
```
docker run --hostname leaky --rm -itv "${PWD}:/root/leaky" rodrodri/valgrind
```

Once the container is running, we would run `valgrind` as usual.
