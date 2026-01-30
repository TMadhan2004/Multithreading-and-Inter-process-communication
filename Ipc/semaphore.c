#include <stdio.h>
#include <unistd.h>
#include <semaphore.h>
#include <fcntl.h>
#include <sys/wait.h>

int main() {
    //a new named semaphore is created with initial value 1
    sem_t *sem = sem_open("/mysem", O_CREAT, 0644, 1);

    if (sem == SEM_FAILED) {
        perror("Semaphore creation failed");
        return 1;
    }

    pid_t pid = fork();

    if (pid == 0) {
        // Child process
        sem_wait(sem);   // wait : it locks
        printf("Child process entered critical section\n");
        sleep(2);
        printf("Child process leaving critical section\n");
        sem_post(sem);   // signal : it unlocks
    } 
    else {
        // Parent process
        sem_wait(sem);   // wait : it locks
        printf("Parent process entered critical section\n");
        sleep(2);
        printf("Parent process leaving critical section\n");
        sem_post(sem);   // signal : it unlocks
        wait(NULL);

        sem_close(sem);
        sem_unlink("/mysem");
    }

    return 0;
}
