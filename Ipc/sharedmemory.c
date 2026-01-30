#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int main() {
    key_t key = 1234;
    
    //creation of shared memory segment
    int shmid = shmget(key, 1024, 0666 | IPC_CREAT);
    if (shmid < 0) {
        perror("shmget failed");
        return 1;
    }

    //attaching shared memory
    char *shared_mem = (char *) shmat(shmid, NULL, 0);
    pid_t pid = fork();

    if (pid == 0) {
        // Child process : reads
        sleep(1);  //waiting for parent to write
        printf("Child reads from shared memory: %s\n", shared_mem);
        shmdt(shared_mem);
    } 
    else {
        // Parent process : writes
        strcpy(shared_mem, "A message is stored to shared memory, this is the message");
        printf("Parent wrote to shared memory\n");
        wait(NULL);

        shmdt(shared_mem);
        shmctl(shmid, IPC_RMID, NULL);
    }

    return 0;
}
