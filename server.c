#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main() {
    int sock0;
    struct sockaddr_in6 addr;
    struct sockaddr_in6 client;
    socklen_t len;
    int sock;
    char buf[32];
    int n;
    char addrstr[INET_ADDRSTRLEN];
    int flag = 1;

    // create socket
    sock0 = socket(AF_INET6, SOCK_STREAM, 0);

    if(setsockopt(sock0, IPPROTO_IPV6, IPV6_V6ONLY, (void *)&flag, sizeof(flag)) != 0) {
        perror("setsockopt IPV6_V6ONLY");
        return 1;
    }

    // set src info
    // memset(&dest, 0, sizeof(dest));
    addr.sin6_family = AF_INET6;
    addr.sin6_port = htons(54321);

    // "in6addr_any" is preset any addr
    addr.sin6_addr = in6addr_any;

    // bind
    if(bind(sock0, (struct sockaddr *)&addr, sizeof(addr)) != 0) {
        perror("bind failed: ");
        return 1;
    }

    // listen
    if(listen(sock0, 5) != 0) {
        perror("listen failed: ");
        return 1;
    }

    // accept
    len = sizeof(client);
    sock = accept(sock0, (struct sockaddr*)&client, &len);

    inet_ntop(AF_INET6, &client.sin6_addr,addrstr, sizeof(addrstr));
    printf("connection from %s, port=%d\n", addrstr, ntohs(client.sin6_port));

    // receive
    memset(buf, 0,sizeof(buf));
    n = read(sock, buf, sizeof(buf));
    printf("n=%d\nmessage : %s\n", n, buf);

    // send
    snprintf(buf, sizeof(buf), "message from IPv6 server");
    n = write(sock, buf, strnlen(buf, sizeof(buf)));

    // client socket
    close(sock);

    // server socket
    close(sock0);

    return 0;
}
