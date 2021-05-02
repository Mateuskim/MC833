compile-all: server.c users.c client.c
	@make -s compile-server
	@make -s compile-client

compile-server: server.c users.c
	gcc server.c users.c -o myserver

compile-client: client.c
	gcc client.c -o myclient
