#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

int main(int argc, char **argv)
{
    int pd[2];
    int res = pipe(pd);
    if (res == -1)
    {
        perror("pipe() error: ");
        exit(EXIT_FAILURE);
    }

    int pid = fork();
    if (pid == -1) // fork() failed
    {
        perror("fork() error: ");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) // child process
    {
        close(pd[1]); // close write end
        int nums[2];  // array to store received numbers
        read(pd[0], &nums, sizeof(nums)); // read numbers from parent
        int sum = nums[0] + nums[1]; 
        close(pd[0]);

        write(pd[1], &sum, sizeof(int));
        close(pd[1]); // close write end
        exit(0);
    }
    else // parent process
    {
        close(pd[0]); 

        FILE *file = fopen("input.txt", "r");
        if (file == NULL)
        {
            perror("Error opening file");
            exit(EXIT_FAILURE);
        }

        int nums[2];
        //for (int i = 0; i < 2; i++)
        //{
        //    fscanf(file, "%d", &nums[i]);
        //}
	fscanf(file, "%d %d", &nums[0],&nums[1]);
        fclose(file);

        // Send numbers to child
        write(pd[1], &nums, sizeof(nums));
        close(pd[1]); 

        int sum;
        read(pd[0], &sum, sizeof(int)); 
        printf("Sum: %d\n", sum);

        close(pd[0]); 

        int status;
        wait(&status);
    }

    return 0;
}
