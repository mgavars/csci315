#ifndef WRAPPERS_H
#define WRAPPERS_H

#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <stdio.h>


pid_t Fork();

int Pipe(int pipefd[2]);

pid_t Wait(int *wstatus);

pid_t Waitpid(pid_t pid, int *wstatus, int options);

int Open(const char *pathname, int flags);

//int Open(const char *pathname, int flags, mode_t mode);

int Close(int fd);

int Write(int fd, const void *buf, size_t count);

int Read(int fd, void *buf, size_t count);

int Connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen);

int Bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);

int Listen(int sockfd, int backlog);

int Accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);


#endif
