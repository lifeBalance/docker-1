# Overlay Networks
An [overlay network](https://docs.docker.com/network/overlay/) allows containers connected to it (including swarm service containers) to communicate securely when encryption is enabled. Docker transparently handles **routing** of each packet to and from the correct Docker daemon host and the correct destination container.

When we **initialize a swarm** or **join an existing swarm**, two new networks are created on that **Docker host**:

1. An **overlay network** called `ingress`, which handles the control and data traffic related to **swarm services**.
2. A **bridge network** called `docker_gwbridge`, which connects the individual Docker daemon to the other daemons participating in the swarm.

We can create [user-defined overlay networks](https://docs.docker.com/network/network-tutorial-overlay/#use-a-user-defined-overlay-network) using [docker network create](https://docs.docker.com/engine/reference/commandline/network_create/), in the same way that you can create [user-defined bridge networks](https://docs.docker.com/network/bridge/).

> When you create a **swarm service** and do not connect it to a **user-defined overlay network**, it connects to the `ingress` network by default.

We can connect both **swarm services** and **standalone containers** to an **overlay network**.

## Pre-requisites
Before you can create an overlay network, you need to either:

1. Initialize your Docker daemon as a **swarm manager** using `docker swarm init`.
2. Or **join an existing swarm** using `docker swarm join`.

Either of these creates the **default overlay network** (`ingress`) which is used by **swarm services** by default. We need to do this even if you never plan to use **swarm services**. Afterward, we can create additional **user-defined overlay networks**.

### Firewall rules for Docker daemons using overlay networks
We need the following ports open to traffic to and from each Docker host participating on an overlay network:

* TCP port `2377` for **cluster management communications**
* TCP and UDP port `7946` for **communication among nodes**
* UDP port `4789` for **overlay network traffic**

### Types of Overlay Network
We can create two types of overlay networks:

1. Overlay networks for use only by **swarm services**.
2. Overlay networks which can be used by:

	* **Swarm services**
	* Or by **standalone containers** to communicate with other **standalone containers** running on other Docker daemons.

1. For the first type we'd use the following command:
```
docker network create --driver overlay my-overlay
```

2. For the second type we just have to add the `--attachable` flag:
```
docker network create --driver overlay --attachable my-attachable-overlay
```

Once the network has been created, we can verify it using the [docker network ls](https://docs.docker.com/engine/reference/commandline/network_ls/) command.

---
[:arrow_backward:][back] ║ [:house:][home] ║ [:arrow_forward:][next]

<!-- navigation -->
[home]: ../README.md
[back]: ./intro.md
[next]: ./services.md