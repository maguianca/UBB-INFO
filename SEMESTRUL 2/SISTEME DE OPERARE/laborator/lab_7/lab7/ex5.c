#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

int main(int argc, char **argv) {
    int pd[2];
    int res = pipe(pd);
    if (res == -1) {
        perror("pipe() error: ");
        exit(EXIT_FAILURE);
    }

    int pid = fork();
    if (pid == -1) { // fork() failed
        perror("fork() error: ");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) { // child process
        //close(pd[1]); // close write end (not used in child)
        
        int nums[2];  // array to store received numbers
        read(pd[0], &nums, sizeof(nums)); // read numbers from parent
        //printf("[in child] num1:%d,num2:%d",nums[0],nums[1]);
        int sum = nums[0] + nums[1]; // compute the sum
        //printf("[in child] sum:%d",sum);
        close(pd[0]); // close read end (done reading)

        write(pd[1], &sum, sizeof(int)); // write sum to parent
        
        close(pd[1]); // close write end (done writing)
        exit(0);
    } else { // parent process
        //close(pd[0]); // close read end (not used in parent initially)

        FILE *file = fopen("input.txt", "r");
        if (file == NULL) {
            perror("Error opening file");
            exit(EXIT_FAILURE);
        }

        int nums[2];
        fscanf(file, "%d %d", &nums[0], &nums[1]); // read two integers from file
        
        fclose(file);

        // Send numbers to child
        write(pd[1], &nums, sizeof(nums)); 
        
        close(pd[1]); // close write end after writing
        
        int status;
        wait(&status);
        
        int sum; // to store sum from child
        
        read(pd[0], &sum, sizeof(int)); // read sum from child
        
        printf("Sum: %d\n", sum); // print the sum
        
        close(pd[0]); // close read end (done with read)
    }

    return 0;
}
