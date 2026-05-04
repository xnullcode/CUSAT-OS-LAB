#include <unistd.h>
#include <sys/types.h>
#include<stdio.h>

int main() {
    int fd[2]; 
    pid_t p;
    int marks[3]; // Array to store user input
    int buffer[3]; // Array for the child to receive data

    // Create pipe
    if (pipe(fd) == -1) {
        printf("Pipe failed\n");
        return 1;
    }

    p = fork();

    if (p < 0) {
        printf("Fork failed\n");
        return 1;
    }

    // Parent Process: The "Input Taker" (Writer)
    if (p > 0) {
        close(fd[0]); // Close unused read end

        printf("Process=1\nEnter marks of 3 students\n");
        for(int i = 0; i < 3; i++) {
            printf("Student %d: ", i + 1);
            scanf("%d", &marks[i]);
        }

        printf("Marks written to shared memory");
        write(fd[1], marks, sizeof(marks)); 
        
        close(fd[1]); 
    } 
    else {
        close(fd[1]);
        read(fd[0], buffer, sizeof(buffer)); 
        printf("\nProcess=2\nReading marks from Shared memory \n");
	int total=0;
	for (int i = 0; i < 3; i++) {
            printf("Student %d :%d\n", i + 1, buffer[i]);
	    total=total+buffer[i];
        }
	printf("Total marks :%d \n",total);
	close(fd[0]); 
    }

    return 0;
}
