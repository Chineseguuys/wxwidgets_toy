#ifndef _PIPLE_2_H_
#define _PIPLE_2_H_

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <sys/wait.h>
#include <errno.h>
#include <string>
#include <sstream>

#define READ 0
#define WRITE 1

FILE *popen_2(std::string command, char type, int &pid);

int pclose_2(FILE *fp, pid_t pid);

#endif /* _PIPLE_2_H_ */