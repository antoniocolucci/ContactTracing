//
// Created by saso on 07/08/21.
//

#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <arpa/inet.h>
#include <pthread.h>
#include "header.h"
#include "peer.h"
#include "ds_peer.h"

void enterIntoNetwork(int *fd_server) {
    struct sockaddr_in serv_addr;
    msg_type_t send_message;
    msg_peer_t recv_message;
    send_message = MSG_UP;

    if ((*fd_server = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Could not create socket, there is something wrong with your system");
        exit(-1);
    }
    memset((char *)&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(SRV_PORT); //port num defined in chat.h

    if (connect(*fd_server, (struct sockaddr *) &serv_addr, sizeof (serv_addr)) < 0) {
        perror("Connect to server failed\n");
        exit(-1);
    }


    if (write(*fd_server, &send_message, sizeof(send_message)) < 0) {
        perror("Write error\n");
        exit(-1);
    }
    if (read(*fd_server, &recv_message, sizeof(recv_message)) < 0) {
        perror("Read error\n");
        exit(-1);
    }
    if (recv_message.msg == CHK_MSG_UP) {

        pthread_attr_t attr;
        pthread_t ntid;

        pthread_attr_init(&attr);
        pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
        pthread_create(&ntid, &attr, recvId, (void *) &recv_message.peer_sock_addr);



/*        pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
        pthread_create(&ntid, &attr, recvId, (void*)&recv_message.peer_sock_addr);*/

    }
    return 1;
}


void contactNeighbour() {
    msg_type_t msg_request_list = MSG_ALL;
    msg_num_all_t msgNumAll;


    node_t *tail_cpy = tail;


    int fd_server = socket(AF_INET, SOCK_STREAM, 0);
    if (fd_server == -1) {
        perror("Could not create socket, there is something wrong with your system");
        exit(-1);
    }
    struct sockaddr_in serv_addr;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(SRV_PORT); //port num defined in chat.h
    if (connect(fd_server, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        perror("Connect to server failed\n");
        exit(-1);
    }
    if (write(fd_server, &msg_request_list, sizeof(msg_request_list)) < 0) {
        printf("%s", strerror(errno));
        perror("Write error\n");
        exit(-1);
    }
    if (read(fd_server, &msgNumAll, sizeof(msgNumAll)) < 0) {
        perror("Read error\n");
        exit(-1);
    }

    if (msgNumAll.msg == ACK_MSG_ALL) {

        int n;
        if ((n = msgNumAll.noPeer * sizeof(struct sockaddr_in)) > 0) {
            struct sockaddr_in msg_peer_to_recv[msgNumAll.noPeer];
            if (read(fd_server, msg_peer_to_recv, n) < 0) {
                perror("Read error\n");
                exit(-1);
            }

            for (int i = 0; i < msgNumAll.noPeer; i++)
                printf("Peer %d\t address: %s \t port: %d\n", i, inet_ntoa(msg_peer_to_recv[i].sin_addr),
                       msg_peer_to_recv[i].sin_port);

            printf("\nSelect the peer to connect: ");
            int input;
            scanf("%d", &input);
            while (input > msgNumAll.noPeer - 1 || input < 0) {
                printf("\nInvalid choice, enter a valid number: ");
                scanf("%d", &input);
            }
            sendId(&msg_peer_to_recv[input]);
        } else
            perror("None into the network, can't communicate!\n");
    }
}

void *sendId(void *args) {
    struct sockaddr_in addr = *(struct sockaddr_in *) args;
    node_t *tail_cpy = malloc(sizeof(node_t));
    //char *my_id = tail->id;
    msg_neigh_id_t msgNeigh, msgAckNeigh;


    int fd_neighbour = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

    msgNeigh.msg = MSG_CONN;
    msgNeigh.id = tail->id;


    if (sendto(fd_neighbour, &msgNeigh, sizeof(msgNeigh), 0, (struct sockaddr *) &addr, sizeof(addr)) < 0) {
        printf("Sendto error %s\n", strerror(errno));
        exit(-1);

    }

    if (recvfrom(fd_neighbour, &msgAckNeigh, sizeof(msgAckNeigh), 0, NULL, NULL) < 0) {
        perror("Recvfrom error\n");
        exit(-1);
    }

    if (msgAckNeigh.msg == ACK_CONN) {
        writeNeighbourID(msgAckNeigh.id);
    }
}


void *recvId(void *args) {
    int fd_listener;
    msg_neigh_id_t msg_to_send, msg_to_rcv;
    struct sockaddr_in addr = *(struct sockaddr_in *) args;
    socklen_t len = sizeof(addr);
    if ((fd_listener = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0) {
        perror("Socket error\n");
        exit(-1);
    }

    if (bind(fd_listener, (struct sockaddr *) &addr, sizeof(addr)) < 0) {
        perror("Bind error\n");
        exit(-1);
    }

    msg_to_send.msg = ACK_CONN;
    msg_to_send.id = tail->id;

    struct sockaddr_in senderAddr;

    while (1) {

        if (recvfrom(fd_listener, &msg_to_rcv, sizeof(msg_to_rcv), 0, (struct sockaddr *) &senderAddr, &len) < 0) {
            perror("Error receiving the message\n");
            exit(-1);
        }

        if (msg_to_rcv.msg == MSG_CONN) {
//            tail_cpy = tail;
            writeNeighbourID(msg_to_rcv.id);


            if (sendto(fd_listener, &msg_to_send, sizeof(msg_to_send), 0, (struct sockaddr *) &senderAddr,
                       sizeof(senderAddr) < 0)) {
                printf("%s", strerror(errno));
                perror("Sendto error\n");

            }
        }
    }
}

void listBroadcast(int *brd_fd, const node_t *head_id, const node_t *tail_id) {
    int sock, n;
    int enable = 1;
    struct sockaddr_in addr, in;
    msg_brd_t *pck_received;
    socklen_t len = sizeof(in);
    if ((sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0) {
        perror("socket");
        exit(1);
    }
    setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(enable));

    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(BROAD_PORT);

    if (bind(sock, (struct sockaddr *) &addr, sizeof(addr)) < 0) {
        perror("bind");
        exit(1);
    }

    if (recvfrom(sock, &pck_received, sizeof(pck_received), 0, NULL, NULL) < 0) {
        perror("Error receiving the broadcast pck\n");
        exit(-1);
    }

    if (pck_received->msg == MSG_BRD) {
        char *token;
        token = strtok(*pck_received->ids, ":");
        while (token) {
            if (searchNeighbour(token) == 1) {
                printf("I'm the peer %s and i have been in touch with someone positive\n", token);
                break;
            }
            token = strtok(NULL, ":");
        }
    }
}

void sendBroadcast(char **id) {
    int sock_fd, n_sent;
    int enable = 1;
    msg_brd_t msg_to_send;
    struct sockaddr_in addr;
    if ((sock_fd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0) {
        fprintf(stderr, "socket error\n");
        exit(1);
    }
    setsockopt(sock_fd, SOL_SOCKET, SO_BROADCAST, &enable, sizeof(enable));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_BROADCAST;
    addr.sin_port = htons(BROAD_PORT);

    msg_to_send.msg = MSG_BRD;
    memcpy(&msg_to_send.msg, id, sizeof(*id));
    //TODO: wait for the server's signal
    n_sent = sendto(sock_fd, msg_to_send.ids, sizeof(msg_to_send), 0, (struct sockaddr *) &addr, sizeof(addr));
    if (n_sent < 0) { /* error condition, stop client */
        printf("Errore in lettura: %s\n", strerror(errno));
        exit(-1);
    }
}

void generate_id(size_t size, char *str) {
    if (str) {
        size_t n;
        static char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
        if (size) {
            --size;
            for (n = 0; n < size - 1; n++) {
                int key = rand() % (int) (sizeof charset - 1);
                str[n] = charset[key];
            }
            str[n++] = '_';
            str[n] = '\0';
        }
    }
}