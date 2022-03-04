# Docker Services
When a **Docker Engine** is in swarm mode, we can create services. A [Docker service](https://docs.docker.com/engine/swarm/how-swarm-mode-works/services/) is a **container** that provides a microservice within the context of some larger application. Examples of services might include an *HTTP server*, a *database*, or any other type of executable program that you wish to run in a **distributed environment**.

> When working with services we use the [docker service](https://docs.docker.com/engine/reference/commandline/service/) command.

> Note that `docker service` is a **cluster management** command, and must be executed on a **swarm manager node**.

## Creating Services
**After** we create a **swarm**, we can **deploy a service** to the swarm. To create a service, we must specify:

* The **Docker image** to use.
* The **commands** to execute inside the running container.
* Finally, we can also define **options** for the service, such as:

	* The **overlay network** for the service to connect to other services in the swarm.
	* The **port** where the swarm makes the service available outside the swarm.
	* The number of **replicas**  of the image to run in the swarm.

To create a service we use the [docker service create](https://docs.docker.com/engine/reference/commandline/service_create/) command, which has the following syntax:
```
docker service create [OPTIONS] IMAGE [COMMAND] [ARG...]
```

For example, to create a **service** named `orbital-command`, based on the [rabbitmq official image](https://hub.docker.com/_/rabbitmq) we'd do:
```
docker service create --name orbital-command --network overmind rabbitmq
```

Note how we also have to specify the **overlay network** where we want to deploy the service.

## Listing Services
To list all the services in the local swarm we use the [docker service ls](https://docs.docker.com/engine/reference/commandline/service_ls/) command.

## Listing Tasks
To lists the tasks that are running as part of a given service, we use the [docker service ps](https://docs.docker.com/engine/reference/commandline/service_ps/). For example, to list the tasks of the `engineering-bay` service we would do:
```
docker service ps engineering-bay
```

And if we are interested in a particular **task** we could use the ``--filter`` option:
```
docker service ps engineering-bay --filter "name=engineering-bay.1"
```

Finally, to see the **ID** of a task, we could use the `--quiet` option.
```
docker service ps engineering-bay --filter "name=engineering-bay.1" --quiet
```

## Accessing the Logs of a Service or Task
The [docker service logs](https://docs.docker.com/engine/reference/commandline/service_logs/) command can be used with:

* Either the `name` or `ID` of a **service**; in this case it will display logs for **all** of the containers in that service.
* Or with the `ID` of a **task**; it will only display logs from that particular **task**.

---
[:arrow_backward:][back] ║ [:house:][home] ║ [:arrow_forward:][next]

<!-- navigation -->
[home]: ../README.md
[back]: ./overlay_networks.md
[next]: ../README.md