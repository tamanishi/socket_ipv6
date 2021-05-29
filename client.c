#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define IPV6

int main() {
#ifdef IPV6
    struct sockaddr_in6 dest;
#else
    struct sockaddr_in dest;
#endif
    int sock;
    char buf[32];
    int n;

    // create socket
#ifdef IPV6
    sock = socket(AF_INET6, SOCK_STREAM, 0);
#else
    sock = socket(AF_INET, SOCK_STREAM, 0);
#endif

    // set destination info
    memset(&dest, 0, sizeof(dest));
#ifdef IPV6
    dest.sin6_family = AF_INET6;
    dest.sin6_port = htons(54321);
#else
    dest.sin_family = AF_INET;
    dest.sin_port = htons(54321);
#endif

    // "in6addr_loopback" is preset loopback addr
#ifdef IPV6
    dest.sin6_addr = in6addr_loopback;
    // inet_pton(AF_INET6, "::1", &dest.sin6_addr);
#else
    inet_pton(AF_INET, "127.0.0.1", &dest.sin_addr.s_addr);
#endif

    // connect
    if(connect(sock, (struct sockaddr *)&dest, sizeof(dest)) != 0) {
        perror("connect failed: ");
        return 1;
    }

    // send
    snprintf(buf, sizeof(buf), "message from IPv6 client");
    n = write(sock, buf, strnlen(buf, sizeof(buf)));

    // receive
    memset(buf, 0, sizeof(buf));
    n = read(sock, buf, sizeof(buf));

    printf("received message: %s\n", buf);

    close(sock);

    return 0;
}