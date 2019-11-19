#include "wrappers.h"

pid_t Fork() {
	int pid = fork();
	if (pid == -1) {
		perror("Error creating child proces");
		exit(-1);
	}
	return pid;
}

int Pipe(int pipefd[2]) {
	int status = pipe(pipefd);
	if (status == -1) {
		perror("Error creating pipe");
		exit(-1);
	}
	return status;
}

pid_t Wait(int *wstatus) {
  int status = wait(wstatus);
  if (status == -1) {
    perror("Error in 'wait' function");
    exit(-1);
  }
  return status;
}

pid_t Waitpid(pid_t pid, int *wstatus, int options) {
  int status = waitpid(pid, wstatus, options);
  if (status == -1) {
    perror("Error in 'waitpid' function");
    exit(-1);
  }
  return status;
}

int Open(const char *pathname, int flags) {
  int status = open(pathname, flags);
  if (status == -1) {
    perror("Error in 'open' function");
    exit(-1);
  }
  return status;
}

//int Open(const char *pathname, int flags, mode_t mode) {
//  int status = open(pathname, flags, mode);
//  if (status == -1) {
//    perror("Error in 'open' function");
//    exit(-1);
//  }
//  return status;
//}

int Close(int fd) {
  int status = close(fd);
  if (status == -1) {
    perror("Error in 'close' function");
    exit(-1);
  }
  return status;
}

int Read(int fd, void *buf, size_t count) {
	int status = read(fd, buf, count);
	if (status == -1) {
		perror("Error reading from pipe");
		exit(-1);
	}
	return status;
}

int Write(int fd, const void *buf, size_t count) {
	int status = write(fd, buf, count);
	if (status == -1) {
		perror("Error writing to pipe");
		exit(-1);
	}
	return status;
}

int Connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen) {
  int status = connect(sockfd, addr, addrlen);
  if (status == -1) {
    perror("Error connecting socket");
    exit(-1);
  }
  return status;
}

int Bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen) {
  int status = bind(sockfd, addr, addrlen);
  if (status == -1) {
    perror("Error binding socket");
    exit(-1);
  }
  return status;
}

int Listen(int sockfd, int backlog) {
  int status = listen(sockfd, backlog);
  if (status == -1) {
    perror("Error listening for socket connection");
    exit(-1);
  }
  return status;
}

int Accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen) {
  int status = accept(sockfd, addr, addrlen);
  if (status == -1) {
    perror("Error accepting socket connection");
    exit(-1);
  }
  return status;
}
