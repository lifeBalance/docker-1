# Docker Swarms
A [swarm](https://docs.docker.com/engine/swarm/key-concepts/) is a cluster of Docker engines, each running in a different **host**. When a [Docker engine](https://docs.docker.com/engine/)(`dockerd` plus `docker`) is running in [swarm mode](https://docs.docker.com/engine/swarm/), it can assume one of the following roles:

* managers (to manage membership and delegation)
* workers (which run swarm services).

A given Docker host can also perform both roles at the same time.

Each instance of the Docker engine participating in the swarm is known as a **node**. You can run one or more nodes on a **single physical computer** (it could be a cloud server), but production swarm deployments typically include Docker nodes distributed across **multiple physical machines** (or cloud servers).

## Creating a Docker Swarm
Using the [docker swarm init](https://docs.docker.com/engine/reference/commandline/swarm_init/) command on a given docker engine, has two effects:

* A Docker swarm is initialized (with a **single-node** for now).
* The Docker engine where we run this command becomes a **manager** in the swarm.

The `--advertise-addr` flag configures the **manager node** to publish its address. The other nodes in the swarm must be able to access the manager at the published IP address. For example:
```
docker swarm init --advertise-addr 192.168.56.1
Swarm initialized: current node (bnckc3myly6oafgkkqf4eh57w) is now a manager.

To add a worker to this swarm, run the following command:

    docker swarm join --token SWMTKN-1-55oa7vn1p517d3z7nu8h0x78xc1ms48lg5j08yrxwn0z1mgf4d-3x3v2fyfqadz806eezd3otnyn 192.168.56.1:2377

To add a manager to this swarm, run 'docker swarm join-token manager' and follow the instructions.
```

## Listing a Docker Swarm
To list the nodes in a swarm we use the [docker node ls](https://docs.docker.com/engine/reference/commandline/node_ls/) command.

> Keep in mind that this command can only be run in a **manager** node!

## Joining a Docker Swarm
To join another **Docker engine** to the swarm, we could use any of the lines of the output of the command used in the previous section. If we missed that line, we could run the following command on a **manager node** one of the following commands:

1. `docker swarm join-token worker`
2. `docker swarm join-token manager`

The output of the [docker swarm join-token](https://docs.docker.com/engine/reference/commandline/swarm_join-token/) command should be used to join the **swarm** as a **worker** or as a **manager** respectively. For example, to join a swarm as a **worker** we would use:
```
docker swarm join-token worker  
To add a worker to this swarm, run the following command:

    docker swarm join --token SWMTKN-1-55oa7vn1p517d3z7nu8h0x78xc1ms48lg5j08yrxwn0z1mgf4d-3x3v2fyfqadz806eezd3otnyn 192.168.56.1:2377
```

Once we get the token, we can join the swarm using the [docker swarm join](https://docs.docker.com/engine/reference/commandline/swarm_join/) along with the `--token` option.

## Leaving a Docker Swarm
To leave a swarm we use [docker swarm leave](https://docs.docker.com/engine/reference/commandline/swarm_leave/). We should run this command only on **workers**; ; to remove a **manager**, we should [demote](https://docs.docker.com/engine/reference/commandline/node_demote/) it to **worker**, then remove it.

> The `--force` option could be used to make a **manager** leave the swarm, but it's not recommended.

When a node **leaves** the swarm, it will still appear in the node list, marked as `down`. It no longer affects swarm operation, but it adds clutter to the list. To remove an inactive node from the list, use the [docker node rm](https://docs.docker.com/engine/reference/commandline/node_rm/) command.

> If there's several nodes with the same `HOSTNAME`, and we want to **remove** one (or several) that is `down`, we could use the `docker node rm` command, and pass the node's `ID` as **argument**.

---
[:arrow_backward:][back] ║ [:house:][home] ║ [:arrow_forward:][next]

<!-- navigation -->
[home]: ../README.md
[back]: ./intro.md
[next]: ../README.md