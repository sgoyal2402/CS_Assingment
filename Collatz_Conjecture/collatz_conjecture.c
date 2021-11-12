#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include <sys/wait.h>
#include<sys/types.h>

/**
 * @brief Generate Collatz Conjecture by recursively forking 
 * to a child process and printing the value.
 * Collatz Conjecture : n = n/2,   if n is even
 *                      n = 3*n+1, if n is odd
 *                      repeat until n = 1.
 * @param num the starting value of sequence
 */

void collatz_conjecture(int num){
    //use fork func. to create a child process
    pid_t pid;
    pid = fork();

    if(pid < 0){/* Check error while forking */
        printf("Error: Unable to create child process!\n");
    }
    else if(pid == 0){/* Child Process prints the num value*/

        printf("Child Process Started\n");
        printf("%d\n", num);
        
        //Change the num value according to the Collatz Conjecture
        if(num == 1){
            return ;
        }
        if(num & 1){
            num = 3*num + 1;
        }
        else{
            num = num/2;
        }

        //Recur for the new value to print complete sequence
        collatz_conjecture(num);
    }
    else {/*parent process wait for child to terminate then exit */

        printf("Waiting for child Process!\n");
        wait(NULL);
        printf("Child process of %d completed\n Parent process completed\n", num);
        return ;
    }
}

int main(int argc, char *argv[]){
    //Check if a number is passed
    if(argc < 2){
        printf("Error: Please pass the starting number as argument in command line\n");
        return 0;
    }

    int num = atoi(argv[1]);

    //Validate whether passed number is positive
    if(num <= 0){
        printf("Error: Invalid Number passed as argument\n");
        return 0;
    }

    collatz_conjecture(num);

    return 0;

}