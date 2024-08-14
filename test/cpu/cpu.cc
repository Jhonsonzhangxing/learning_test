// #define _GNU_SOURCE
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <sched.h>

void *thread_func(void *arg)
{
    usleep(10000);

    // 获取当前线程的 CPU 亲和性
    cpu_set_t cpuset;
    CPU_ZERO(&cpuset);
    pthread_getaffinity_np(pthread_self(), sizeof(cpu_set_t), &cpuset);
    // 打印当前线程绑定的 CPU
    for (int i = 0; i < CPU_SETSIZE; i++) {
        if (CPU_ISSET(i, &cpuset)) {
            printf("thread is running on cpu %d\n", i);
        }
    }
    return NULL;
}

int main() {
    pthread_t tid;
    pthread_attr_t attr;
    pthread_attr_init(&attr);

    // 创建线程并设置其只能在 cpu1 上运行
    cpu_set_t mask;
    CPU_ZERO(&mask);
    CPU_SET(1, &mask);
    pthread_attr_setaffinity_np(&attr, sizeof(mask), &mask);
    pthread_create(&tid, &attr, thread_func, NULL);

    pthread_attr_destroy(&attr);
    pthread_join(tid, NULL);
    return 0;
}
