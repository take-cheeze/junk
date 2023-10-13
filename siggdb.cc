#include <cassert>
#include <csignal>
#include <iostream>
#include <sstream>

#include <sys/prctl.h>
#include <sys/types.h>
#include <sys/wait.h>

FILE * custom_popen(const char* command, char type, pid_t* pid)
{
    pid_t child_pid;
    int fd[2];
    pipe(fd);

    if((child_pid = fork()) == -1)
    {
        perror("fork");
        exit(1);
    }

    /* child process */
    if (child_pid == 0)
    {
        std::cout << "command: " << command << std::endl;

        if (type == 'r')
        {
            close(fd[0]);    //Close the READ end of the pipe since the child's fd is write-only
            dup2(fd[1], 1); //Redirect stdout to pipe
        }
        else
        {
            close(fd[1]);    //Close the WRITE end of the pipe since the child's fd is read-only
            dup2(fd[0], 0);   //Redirect stdin to pipe
        }

        setpgid(child_pid, child_pid); //Needed so negative PIDs can kill children of /bin/sh
        execl("/bin/sh", "sh", "-c", command, (char*)NULL);
        exit(0);
    }
    else
    {
        printf("child pid %d\n", child_pid);
        if (type == 'r')
        {
            close(fd[1]); //Close the WRITE end of the pipe since parent's fd is read-only
        }
        else
        {
            close(fd[0]); //Close the READ end of the pipe since parent's fd is write-only
        }
    }

    *pid = child_pid;

    if (type == 'r')
    {
        return fdopen(fd[0], "r");
    }

    return fdopen(fd[1], "w");
}

int custom_pclose(FILE * fp, pid_t pid)
{
    int stat;

    fclose(fp);
    while (waitpid(pid, &stat, 0) == -1)
    {
        if (errno != EINTR)
        {
            stat = -1;
            break;
        }
    }

    return stat;
}

static void catcher(int signo) {
    std::cerr << "signal catched: " << signo << std::endl;
    int pid;
    FILE* fp = custom_popen("gdb -q", 'w', &pid);
    prctl(PR_SET_PTRACER, pid, 0, 0, 0);
    std::ostringstream oss;
    oss << "attach " << getpid() << std::endl;
    oss << "backtrace" << std::endl;
    oss << "detach" << std::endl;
    oss << "exit" << std::endl;
    // std::cout << oss.str() << std::endl;
    fwrite(oss.str().c_str(), 1, oss.str().size(), fp);
    custom_pclose(fp, pid);
    std::quick_exit(128 + signo);
}

int main(int argc, char** argv) {
    // prog = argv[0];
    if (std::signal(SIGSEGV, catcher) == SIG_ERR) {
        assert(false);
    }
    int* a = nullptr;
    *a = 0;
    return EXIT_SUCCESS;
}
