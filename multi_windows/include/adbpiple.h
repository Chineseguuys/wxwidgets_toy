#ifndef _ADB_PIPLE_H_
#define _ADB_PIPLE_H_

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <vector>

// multi-thread
#include <thread>
#include <mutex>

extern "C" {
#include <simplelogs.h>
}
#include "piple.h"

//#define FILE_NONBLOCKING_MODE

struct ADBPiple {
    struct device_list {
        struct Device {
            std::string mDeviceName;
            std::string mDeviceState;
        };

        uint32_t            nDevices;
        std::vector<Device> mAllDevices;
    };

    struct package_list {
        struct package {
            std::string mPackageName;
            std::string mPackagePath;
        };

        uint32_t             nPackages;
        std::vector<package> mAllPackages;
    };

    static device_list getAllDevices() {
        FILE       *fp;
        char       *buffer = new char[128];
        std::string device;
        std::string state;

        device_list list{
            .nDevices = 0,
            .mAllDevices = {}};
        fp = popen("adb devices", "r");
        if (!fp) {
            log_error("error piple open");
            return list;
        }

        // 执行和解析 adb 消息
        while (fgets(buffer, 128 - 1, fp) != NULL) {
            if (buffer[0] == '*') continue;
            if (strncmp("List of devi", buffer, 12) == 0) { // 下面一行开始打印设备值
                while (fgets(buffer, 128 - 1, fp) != NULL) {
                    if (buffer[0] == ' ' || buffer[0] == '\n') {
                        log_warn("empty line");
                        continue;
                    }
                    char *temp = strtok(buffer, "\t");
                    if (temp != NULL) {
                        device = temp;
                    }
                    temp = strtok(NULL, "\t");
                    if (temp != NULL) {
                        state = temp;
                    }

                    log_info("get devices:{%s, %s}", device.c_str(), state.c_str());

                    list.mAllDevices.push_back({device, state});
                    list.nDevices = list.nDevices + 1;
                }
            }
        }

        pclose(fp);
        return list;
    }

    static package_list getALLpackages(const std::string deviceName) {
        FILE       *fp;
        char       *buffer = new char[128];
        std::string package;
        std::string command = "adb -s " + deviceName + " shell pm list packages";

        package_list list{
            .nPackages = 0,
            .mAllPackages = {}};

        fp = popen(command.c_str(), "r");
        if (!fp) {
            log_error("error piple open");
            return list;
        }

        while (fgets(buffer, 128 - 1, fp) != NULL) {
            char *begin_name = &buffer[8];
            package = begin_name;

            list.mAllPackages.push_back({package, ""});
            list.nPackages = list.nPackages + 1;
            log_info("package name: %s", begin_name);
        }
        pclose(fp);
        return list;
    }

private:
    device_list::Device mCurrentDevices; // 当前的设备的名称
    FILE               *mPiple_fd;       // 打开的 piple 文件描述符, 它会被分享给 frame
    pid_t               mPid;            // popen 打开的子进程的进程号

public:
    ADBPiple(const device_list::Device &_device) {
        this->mCurrentDevices.mDeviceName = _device.mDeviceName;
        this->mCurrentDevices.mDeviceState = _device.mDeviceState;
    }

    ~ADBPiple() {
        if (this->mPiple_fd != nullptr) {
            pclose(this->mPiple_fd); // 尝试关闭 piple
        }
    }

    void setDevice(const device_list::Device &_device) {
        this->mCurrentDevices.mDeviceName = _device.mDeviceName;
        this->mCurrentDevices.mDeviceState = _device.mDeviceState;
    }

    /**
     * @brief 对一个设备进行监控 我们在子线程中执行 shell 命令,
     * 在主进程的子线程中进行读写。ADBpiple 只负责创建子进程，我们在 wxwidgets
     * 的子线程进行读写。
     *
     * @param _piple_fd 返回给 frame 的可读文件描述符号
     */
    int onMonitorDevices(FILE **_piple_fd) {
        std::string command = "adb -s " + this->mCurrentDevices.mDeviceName + " shell am monitor";
        log_info("adb command: %s", command.c_str());
        this->mPiple_fd = popen_2(command, 'r', this->mPid);
        if (!this->mPiple_fd) {
            log_error("error piple open");
            return 1;
        }
        // 用非阻塞的方式打开, 防止关闭的时候，被阻塞
#ifdef FILE_NONBLOCKING_MODE
        int fd = fileno(this->mPiple_fd);
        int flags = fcntl(fd, F_GETFL, 0);
        flags |= O_NONBLOCK;
        fcntl(fd, F_SETFL, flags);
#endif /* FILE_NONBLOCKING_MODE */

        *_piple_fd = this->mPiple_fd;
        return 0;
    }

    /**
     * @brief 关闭前面开启的子进程，关闭文件描述符
     *
     * @return int 返回状态码
     */
    int onMonitorOver() {
        if (this->mPiple_fd) {
            pclose_2(this->mPiple_fd, this->mPid);
            this->mPiple_fd = nullptr;
            this->mPid = -1;
        }
        return 0;
    }
};

#endif