#include "piple.h"
extern "C" {
#include "simplelogs.h"
}
#include <memory>
#include <sstream>
#include <errno.h>

//#define USE_FD
//#define USE_FP

int main(int argc, char *argv[]) {
    std::string           command = "adb shell am monitor";
    pid_t                 sub_pid;
    std::shared_ptr<char> buffer(new char[256]);
    std::stringstream     output;
    char                  scanf_ch;

    FILE *fp = popen_2(command, 'r', sub_pid);
    if (fp != NULL) {
        log_info("open popen success in sub process %d with fd[%d]", sub_pid, fileno(fp));
    }
#ifdef USE_FD
    int fd = fileno(fp);
    while (read(fd, buffer.get(), 255) != 0) {
        log_info("read from fd");
        output << std::string(buffer.get());
        // kill(-sub_pid, 9);
        memset(buffer.get(), 0, 256);
    }

    log_info("error : %s", strerror(errno));
    std::string token;
    while (std::getline(output, token, '\n'))
        printf("%s\n", token.c_str());
#else  /* USE_FD */
    while (true) {
        if (fgets(buffer.get(), 255, fp) != NULL) {
            log_info("%s", buffer.get());
            memset(buffer.get(), 0, 256);
        } else {
            log_info("wait for seconds");
            sleep(1);
        }
    }
#endif /* USE_FD */
    log_info("please give me a char");
    scanf("%c", &scanf_ch);
    pclose_2(fp, sub_pid);
    return 0;
}
