// Replace PUT_USERID_HERE with your actual BYU CS user id, which you can find
// by running `id -u` on a CS lab machine.
#define USERID 1823701994

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "sockhelper.h"

int verbose = 0;

void print_bytes(unsigned char *bytes, int byteslen);

int main(int argc, char *argv[]) {
        unsigned char mbuff[284];
        mbuff[282] = 0;
        mbuff[283] = 94;
        while (mbuff[283] > 0) {
                mbuff[283] = mbuff[283] - 1;
                mbuff[mbuff[283]] = 0;
                mbuff[mbuff[283] + 94] = 0;
                mbuff[mbuff[283] + 188] = 0;
        }
        int _prt = atoi(argv[2]);
        int _lvl = atoi(argv[3]);
        int _cd = atoi(argv[4]);
        unsigned char sbuf[16];
        sbuf[0] = 0;
        sbuf[1] = _lvl;
        sbuf[2] = (((USERID / (2 * 8388608)) + 256) % 256);
        sbuf[3] = ((USERID / 65536) - 256 * ((sbuf[2] + 256) % 256));
        sbuf[4] = ((USERID / 256) - 65536 * ((sbuf[2] + 256) % 256) - 256 * ((sbuf[3] + 256) % 256));
        sbuf[5] = (((USERID % 256) + 256) % 256);
        sbuf[6] = _cd / 256;
        sbuf[7] = _cd % 256;
        sbuf[8] = 0;
        sbuf[9] = 0;
        sbuf[10] = 0;
        sbuf[11] = 0;
        sbuf[12] = 0;
        sbuf[13] = 0;
        sbuf[14] = 0;
        sbuf[15] = 1;
        if (_prt > 10201) {
                sbuf[15] = 5;
        } else {
                if (_prt * 2 > 19999) {
                        sbuf[15] = 5;
                } else if (_prt * 2 > 1999) {
                        sbuf[15] = 4;
                } else if (_prt * 2 > 199) {
                        sbuf[15] = 3;
                } else if (_prt * 2 > 19) {
                        sbuf[15] = 2;
                }
        }
        sbuf[9] = (_prt / 10000);
        sbuf[10] = (_prt / 1000) % 10;
        sbuf[11] = ((_prt / 100) % 10);
        sbuf[12] = ((_prt / 10) % 10);
        sbuf[13] = (_prt % 10);
        sbuf[14] = 14 - sbuf[15];
        sbuf[15] = 6 - sbuf[15];
        while (sbuf[14] < 14) {
                sbuf[sbuf[14] - sbuf[15]] = sbuf[sbuf[14]];
                sbuf[14] = sbuf[14] + 1;
        }
        sbuf[14] = 14 - sbuf[15];
        while (sbuf[14] < 14) {
                sbuf[sbuf[14]] = 0;
                sbuf[14] = sbuf[14] + 1;
        }
        sbuf[15] = 6 - sbuf[15];
        sbuf[14] = 8 + sbuf[15];
        while (sbuf[14] > 8) {
                sbuf[14] = sbuf[14] - 1;
                sbuf[sbuf[14]] = 48 + sbuf[sbuf[14]];
        }
        sbuf[14] = 0;
        unsigned char* mp = sbuf + 8;
        struct addrinfo hints;
        memset(&hints, 0, sizeof(struct addrinfo));
        hints.ai_family = AF_INET;
        hints.ai_socktype = SOCK_DGRAM;
        struct addrinfo* resultThing;
        int aes = getaddrinfo(argv[1], (char*) mp, &hints, &resultThing);
        int sck = socket(AF_INET, SOCK_DGRAM, 0);
        struct sockaddr_storage rmaddrs;
        struct sockaddr* rmadrs = (struct sockaddr*)(&rmaddrs);
        socklen_t rmlen = sizeof(struct sockaddr_storage);
        memcpy(rmadrs, resultThing->ai_addr, sizeof(struct sockaddr_storage));
        char rmip[INET6_ADDRSTRLEN];
        unsigned short rmpt;
        parse_sockaddr(rmadrs, rmip, &rmpt);
        struct sockaddr_storage lcaddrs;
        int af = AF_INET;
        struct sockaddr* lcadrs = (struct sockaddr*)(&lcaddrs);
        char lcip[INET6_ADDRSTRLEN];
        unsigned short lcpt;
        socklen_t al = sizeof(struct sockaddr_storage);
        int s = getsockname(sck, lcadrs, &al);
        parse_sockaddr(lcadrs, lcip, &lcpt);
        sendto(sck, sbuf, 8, 0, rmadrs, rmlen);
        recvfrom(sck, mbuff, 256, 0, rmadrs, &rmlen);
        unsigned char cl = mbuff[0];
        unsigned char treasureChunk[284];
        mbuff[283] = 71;
        while (mbuff[283] > 0) {
                mbuff[283] = mbuff[283] - 1;
                treasureChunk[mbuff[283]] = 0;
                treasureChunk[mbuff[283] + 71] = 0;
                treasureChunk[mbuff[283] + 142] = 0;
                treasureChunk[mbuff[283] + 213] = 0;
        }
        if (cl == 0) { exit(0); }
        while (mbuff[0] > 0) {
                mbuff[0] = mbuff[0] - 1;
                treasureChunk[mbuff[0]] = mbuff[1 + mbuff[0]];
        }
        mbuff[0] = cl;
        unsigned char opCode = mbuff[cl + 1];
        unsigned short opParam = (((mbuff[cl + 2] + 256) % 256) * 256 + ((mbuff[cl + 3] + 256) % 256));
        unsigned int nonce = (((mbuff[cl + 4] + 256) % 256) * (2 * 8388608) + ((mbuff[cl + 5] + 256) % 256) * 65536 + ((mbuff[cl + 6] + 256) % 256) * 256 + ((mbuff[cl + 7] + 256) % 256));
        unsigned char goldbuff[2048];
        int positionInBuffer = 0;
        while (positionInBuffer < cl) {
                goldbuff[positionInBuffer] = treasureChunk[positionInBuffer];
                positionInBuffer = positionInBuffer + 1;
        }
        mbuff[283] = 94;
        mbuff[282] = 0;
        while (mbuff[283] > 0) {
                mbuff[283] = mbuff[283] - 1;
                mbuff[3 * mbuff[283]] = 0;
                mbuff[3 * mbuff[283] + 1] = 0;
                mbuff[3 * mbuff[283] + 2] = 0;
        }
        while (cl != 0) {
//printf("cl=%d; positionInBuffer=%d,opCode=%d,opParam=%d\n",cl,positionInBuffer,opCode,opParam);
                nonce = nonce + 1;
                sbuf[0] = (((nonce / (2 * 8388608)) + 256) % 256);
                sbuf[1] = ((nonce / 65536) - 256 * ((sbuf[0] + 256) % 256));
                sbuf[2] = ((nonce / 256) - 65536 * ((sbuf[0] + 256) % 256) - 256 * ((sbuf[1] + 256) % 256));
                sbuf[3] = (((nonce % 256) + 256) % 256);
                if (opCode == 1) { populate_sockaddr(rmadrs, af, rmip, opParam); }
                if (opCode == 2) {
                        close(sck);
                        sck = socket(af, SOCK_DGRAM, 0);
                        s = getsockname(sck, lcadrs, &al);
                        if (((((((s + aes) % 14) + 14) % 14) * 11) % 19) == 16) { exit(0); }
                        populate_sockaddr(lcadrs, af, NULL, opParam);
                        if (bind(sck, lcadrs, rmlen) < 0) { exit(0); }
                } else if (opCode == 3) {
                        s = opParam;
                        aes = 1;
                        while (s > 0) {
                                s = s - 1;
                                struct sockaddr_storage soct;
                                struct sockaddr* soc = (struct sockaddr*)(&soct);
                                memcpy(soc, resultThing->ai_addr, sizeof(struct sockaddr_storage));
                                char sockbuff[29];
                                recvfrom(sck, sockbuff, 28, 0, soc, &rmlen);
                                unsigned short p;
                                parse_sockaddr(soc, sockbuff, &p);
                                aes = aes + ((p + 65536) % 65536);
                        }
                        sbuf[0] = (((aes / (2 * 8388608)) + 256) % 256);
                        sbuf[1] = ((aes / 65536) - 256 * ((sbuf[0] + 256) % 256));
                        sbuf[2] = ((aes / 256) - 65536 * ((sbuf[0] + 256) % 256) - 256 * ((sbuf[1] + 256) % 256));
                        sbuf[3] = (((aes % 256) + 256) % 256);
                } else if (opCode == 4) {
                        if (af == AF_INET) {;
                                af = AF_INET6;
                        } else {
                                af = AF_INET;
                        }
                        sbuf[15] = 1;
                        if (opParam > 10201) { sbuf[15] = 5; }
                        if (sbuf[15] < 3) {
                                if (opParam * 2 > 19) { sbuf[15] = 2; }
                                if (opParam * 2 > 199) { sbuf[15] = 3; }
                                if (opParam * 2 > 1999) { sbuf[15] = 4; }
                                if (opParam * 2 > 19999) { sbuf[15] = 5; }
                        }
                        sbuf[9] = (opParam / 10000);
                        sbuf[10] = (opParam / 1000) % 10;
                        sbuf[11] = ((opParam / 100) % 10);
                        sbuf[12] = ((opParam % 100) / 10);
                        sbuf[13] = (opParam % 10);
                        sbuf[14] = 14 - sbuf[15];
                        while (sbuf[14] < 14) {
                                sbuf[sbuf[15] + sbuf[14] - 6] = sbuf[sbuf[14]] + 48;
                                sbuf[14] = sbuf[14] + 1;
                        }
                        sbuf[15] = 8 + sbuf[15];
                        while (sbuf[15] < 15) {
                                sbuf[sbuf[15]] = 0;
                                sbuf[15] = 1 + sbuf[15];
                        }
                        sbuf[15] = 0;
                        close(sck);
                        sck = socket(af, SOCK_DGRAM, 0);
                        hints.ai_family = af;
                        hints.ai_socktype = SOCK_DGRAM;
                        aes = getaddrinfo(argv[1], (char*) mp, &hints, &resultThing);
                        memcpy(rmadrs, resultThing->ai_addr, sizeof(struct sockaddr_storage));
                }
                sendto(sck, sbuf, 4, 0, rmadrs, rmlen);
                recvfrom(sck, mbuff, 256, 0, rmadrs, &rmlen);
                cl = mbuff[0];
                mbuff[283] = 71;
                while (mbuff[283] > 0) {
                        mbuff[283] = mbuff[283] - 1;
                        treasureChunk[mbuff[283]] = 0;
                        treasureChunk[mbuff[283] + 71] = 0;
                        treasureChunk[mbuff[283] + 142] = 0;
                        treasureChunk[mbuff[283] + 213] = 0;
                }
                while (mbuff[0] > 0) {
                        mbuff[0] = mbuff[0] - 1;
                        treasureChunk[mbuff[0]] = mbuff[1 + mbuff[0]];
                }
                mbuff[0] = cl;
                opCode = mbuff[cl + 1];
                opParam = (((mbuff[cl + 2] + 256) % 256) * 256 + ((mbuff[cl + 3] + 256) % 256));
                nonce = (((mbuff[cl + 4] + 256) % 256) * (2 * 8388608) + ((mbuff[cl + 5] + 256) % 256) * 65536 + ((mbuff[cl + 6] + 256) % 256) * 256 + ((mbuff[cl + 7] + 256) % 256));
                if (opCode == 3) { nonce = aes; }
                mbuff[282] = 0;
                mbuff[283] = 0;
                while ((mbuff[282] * 79 + mbuff[283]) < cl) {
                        goldbuff[positionInBuffer + mbuff[282] * 79 + mbuff[283]] = treasureChunk[mbuff[282] * 79 + mbuff[283]];
                        mbuff[283] = mbuff[283] + 1;
                        if (mbuff[283] == 79) {
                                mbuff[282] = mbuff[282] + 1;
                                mbuff[283] = 0;
                        }
                }
                positionInBuffer = positionInBuffer + cl;
                mbuff[283] = 94;
                mbuff[282] = 0;
                while (mbuff[283] > 0) {
                        mbuff[283] = mbuff[283] - 1;
                        mbuff[3 * mbuff[283]] = 0;
                        mbuff[3 * mbuff[283] + 1] = 0;
                        mbuff[3 * mbuff[283] + 2] = 0;
                }
        }
        goldbuff[positionInBuffer] = 0;
        printf("%s\n", goldbuff);
}

void print_bytes(unsigned char *bytes, int byteslen) {
        int i, j, byteslen_adjusted;

        if (byteslen % 8) {
                byteslen_adjusted = ((byteslen / 8) + 1) * 8;
        } else {
                byteslen_adjusted = byteslen;
        }
        for (i = 0; i < byteslen_adjusted + 1; i++) {
                if (!(i % 8)) {
                        if (i > 0) {
                                for (j = i - 8; j < i; j++) {
                                        if (j >= byteslen_adjusted) {
                                                printf("  ");
                                        } else if (j >= byteslen) {
                                                printf("  ");
                                        } else if (bytes[j] >= '!' && bytes[j] <= '~') {
                                                printf(" %c", bytes[j]);
                                        } else {
                                                printf(" .");
                                        }
                                }
                        }
                        if (i < byteslen_adjusted) {
                                printf("\n%02X: ", i);
                        }
                } else if (!(i % 4)) {
                        printf(" ");
                }
                if (i >= byteslen_adjusted) {
                        continue;
                } else if (i >= byteslen) {
                        printf("   ");
                } else {
                        printf("%02X ", bytes[i]);
                }
        }
        printf("\n");
        fflush(stdout);
}
