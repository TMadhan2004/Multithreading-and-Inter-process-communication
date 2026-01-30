#include <stdio.h>
#include <unistd.h>

int main() {
    int fd[2]; 
    //fd[0] read end
    //fd[1] write end
    pipe(fd);

    if (fork() == 0) {  
        // Child
        close(fd[1]);
        char buf[100];
        read(fd[0], buf, sizeof(buf));
        printf("Child read: %s\n", buf);
    } 
    else {         
        // Parent
        close(fd[0]);
        write(fd[1], "Hello from parent", 18);
    }
    return 0;
}
