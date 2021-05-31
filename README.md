# Learning socket programming

## client server

``` sh
cc client.c -o client
cc server.c -o server

./server

# in other terminal
./client
```

### note

- It is needed to configure daemon.json to enable ipv6.
- [Enable IPv6 support](https://docs.docker.com/config/daemon/ipv6/ "Enable IPv6 support")

``` json
  "ipv6": true,
  "fixed-cidr-v6": "2001:db8:1::/64",
```
