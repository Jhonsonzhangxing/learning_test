#include <iostream>
#include <string>
#include <signal.h>
#include <fcntl.h>
#include <fstream>
#include <execinfo.h> /* backtrace, backtrace_symbols_fd */
#include <unistd.h> /* STDOUT_FILENO */
#include <cstdlib>
#include <cxxabi.h>
#include <dlfcn.h>
#include <sstream>
#include <cstring>
using namespace std;

//g++ main.cc -o main -rdynamic -g -ldl
    static std::string BackTrace(const int nMaxFrames = 32, const int skip = 1){
        void *callstack[nMaxFrames];
        char buf[1024];
        int nFrames = backtrace(callstack, nMaxFrames);
        char **symbols = backtrace_symbols(callstack, nFrames);

        std::ostringstream trace_buf;
        for (int i = skip; i < nFrames; i++) {
            Dl_info info;
            if (dladdr(callstack[i], &info)) {
                char *demangled = NULL;
                int status;
                demangled = abi::__cxa_demangle(info.dli_sname, NULL, 0, &status);
                snprintf(buf, sizeof(buf), "%-2d: %p\t%s\n",
                        i, callstack[i], status == 0 ? demangled : info.dli_sname);
                free(demangled);
            } else {
                snprintf(buf, sizeof(buf), "%-2d: %p\t%s\n", i, callstack[i], symbols[i]);
            }
            trace_buf << buf;
        }
        free(symbols);
        if (nFrames >= nMaxFrames)
            trace_buf << "[truncated]\n";
        return trace_buf.str();
	}

void signal_handler(int sig) {
    void *array[10];
    size_t size;

    // get void*'s for all entries on the stack
    size = backtrace(array, 10);

    // print out all the frames to a log file
    FILE* fp = fopen("crash.log", "w");
    if (fp != NULL) {
        fprintf(fp, "Error: signal %d\n", sig);
        for (int i = 0; i < size; i++) {
            fprintf(fp, "[%d] ", i);
            if (array[i] != NULL) {
                char addr2line_cmd[256];
                sprintf(addr2line_cmd, "addr2line -f -e ./main %p", array[i]);
				std::cout << "line: " << addr2line_cmd << std::endl;
                FILE* addr2line_fp = popen(addr2line_cmd, "r");
                if (addr2line_fp != NULL) {
                    char line[256];
                    while (fgets(line, sizeof(line), addr2line_fp) != NULL) {
                        fprintf(fp, "%s", line);
                    }
                    pclose(addr2line_fp);
                }
            } else {
                fprintf(fp, "(unknown)\n");
            }
        }
        fclose(fp);
    }

    _exit(1); // exit the program
}

// 打印函数调用堆栈信息
void printStackTrace()
{
    const int MAX_STACK_TRACE_SIZE = 50;
    void* stackTrace[MAX_STACK_TRACE_SIZE];
    
    // 获取当前线程的调用堆栈信息
    int stackTraceSize = backtrace(stackTrace, MAX_STACK_TRACE_SIZE);
    
    // 使用addr2line工具解析每个地址对应的源代码文件和行号
    char cmd[MAX_STACK_TRACE_SIZE*1024];
    sprintf(cmd, "addr2line -f -e ./main");
    
    for(int i=0; i<stackTraceSize; ++i)
    {
        char buf[512];
        sprintf(buf, " %p", stackTrace[i]);
        strcat(cmd, buf);
    }
    
    FILE* fp = popen(cmd, "r");
    
    if(fp == NULL)
        return;
        
    char line[256];
    
    while(fgets(line, sizeof(line), fp))
        std::cout << line;
        
    pclose(fp);
}

void print_stacktrace(void) {
    size_t size;
    enum Constexpr { MAX_SIZE = 1024 };
    void *array[MAX_SIZE];
    size = backtrace(array, MAX_SIZE);
    backtrace_symbols_fd(array, size, STDOUT_FILENO);
}

void init() {
	std::string c = "c";
	int a[2];
	a[2]=3;
}

void copyFile1(const char *src_file, const char *dest_file)
{
    int src_fd = open(src_file, O_RDONLY);
    int dest_fd = creat(dest_file, O_WRONLY);

    unsigned char buf[1024];
    while (read(src_fd, buf, sizeof(buf)) > 0)
    {
        write(dest_fd, buf, sizeof(buf));
    }

    close(src_fd);
    close(dest_fd);
}

int CopyFile(const char *SourceFile, const char *NewFile)
{
	std::ifstream in;
	ofstream out;
	in.open(SourceFile,ios::binary);//打开源文件
	if(in.fail())//打开源文件失败
	{
	cout<< "Error 1: Fail to open the source file." <<endl;
	in.close();
	out.close();
	return 0;
	}
	out.open(NewFile,ios::binary);//创建目标文件
	if(out.fail())//创建文件失败
	{
	cout<<"Error 2: Fail to create the new file."<<endl;
	out.close();
	in.close();
	return 0;
	}
	else//复制文件
	{
	out<<in.rdbuf();
	out.close();
	in.close();
	return 1;
	}
}


void sig_handler(const int sig_number) {
  // Let the in-progress signal error complete.
  // Re-raise this new signal.
	pid_t a = getpid();
	std::string str;
	str = "/proc/" + std::to_string(a) + "/maps";

	copyFile1(str.c_str(), "./maps");
	std::cout << "copyFile1 done : "<< str  << std::endl;

	CopyFile(str.c_str(), "./maps1");
	std::cout << "CopyFile done : "<< str  << std::endl;

	print_stacktrace();
	std::cout << "print_stacktrace: done"<< std::endl;

	// printStackTrace();
	// std::cout << "printStackTrace: done"<< std::endl;

	std::string out = BackTrace();
	std::cout << out << std::endl;
	std::cout << "BackTrace: done"<< std::endl;


	sleep(2);

	std::abort();
}

int main() {
	//init();
	pid_t a = getpid();
	int b = a;

	std::cout << "b: " << b << std::endl;
	// auto ret = signal(SIGINT, sig_handler);
	// if (ret == SIG_ERR) {
	// 	std::cout << "ERROR: failed to set SIGINT handler" << std::endl;
	// }
	// ret = signal(SIGTERM, sig_handler);
	// if (ret == SIG_ERR) {
	// 	std::cout << "ERROR: failed to set SIGTERM handler" << std::endl;
	// }

	auto ret = signal(SIGSEGV, sig_handler);
	if (ret == SIG_ERR) {
		std::cout << "ERROR: failed to set SIGSEGV handler" << std::endl;
	}
	// sleep(20);
		std::string str;
	str = "/proc/" + std::to_string(a) + "/maps";
		copyFile1(str.c_str(), "./maps_ori");
	std::cout << "copyFile1 done : "<< str  << std::endl;
	init();
	return 0;
}
