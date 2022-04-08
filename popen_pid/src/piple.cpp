#include "piple.h"

//#define FOR_TEST

FILE *popen_2(std::string command, char type, int &pid) {
    pid_t child_pid;
    int   fd[2];
    pipe(fd);

    if ((child_pid = fork()) == -1) {
        perror("fork");
        exit(1);
    }

    /* child process */
    if (child_pid == 0) {
        if (type == 'r') {
            close(fd[READ]);                // Close the READ end of the pipe since the child's fd is write-only
            dup2(fd[WRITE], STDOUT_FILENO); // Redirect stdout to pipe
        } else {
            close(fd[WRITE]);             // Close the WRITE end of the pipe since the child's fd is read-only
            dup2(fd[READ], STDIN_FILENO); // Redirect stdin to pipe
        }

        setpgid(child_pid, child_pid); // Needed so negative PIDs can kill children of /bin/sh
#ifndef FOR_TEST
        execl("/bin/bash", "/bin/bash", "-c", command.c_str(), (char *)NULL);
#else
        printf("test for out put");
        sleep(10);
        printf("test for output1");
#endif
        exit(0);
    } else { // Parent process
        if (type == 'r') {
            close(fd[WRITE]); // Close the WRITE end of the pipe since parent's fd is read-only
        } else {
            close(fd[READ]); // Close the READ end of the pipe since parent's fd is write-only
        }
    }

    pid = child_pid;

    if (type == 'r') {
        return fdopen(fd[READ], "r"); // 将文件描述符转换为文件指针
    }

    return fdopen(fd[WRITE], "w");
}

int pclose_2(FILE *fp, pid_t pid) {
    int stat;

    fclose(fp);
    while (waitpid(pid, &stat, 0) == -1) {
        if (errno != EINTR) {
            stat = -1;
            break;
        }
    }

    return stat;
}