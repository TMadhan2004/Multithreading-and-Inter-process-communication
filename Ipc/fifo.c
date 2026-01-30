#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
    // Path for the named pipe to be stored
    char *myfifo = "/tmp/myfifo";

    // creating the FIFO (0666 refers to permissions: read/write for owner)
    mkfifo(myfifo, 0666);

    pid_t pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        return 1;
    }

    if (pid == 0) {
        // child process (reader)
        char buffer[100];
        int fd = open(myfifo, O_RDONLY); // Open for reading
        read(fd, buffer, sizeof(buffer));
        
        printf("Child (PID %d) read from FIFO: %s \n", getpid(), buffer);
        
        close(fd);
    } 
    else {
        // parent process (writer)
        char *message = "Hello from the Parent";
        int fd = open(myfifo, O_WRONLY); // Open for writing
        
        printf("Parent (PID %d) is writing to FIFO\n", getpid());
        write(fd, message, strlen(message) + 1);
        
        close(fd);
        unlink(myfifo); // Remove the FIFO file from system
    }

    return 0;
}