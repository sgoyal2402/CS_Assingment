#include<stdio.h>
#include<unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include<malloc.h>

/**
* Copy the 'source' file to 'dest', dest can be 
* overwritten.
* @param source Path to source file
* @param dest Path to dest file
* @return value 0 as Success, -1 as failure. 
*/

int file_copy(char* source, char* dest){
    //File descriptor for source and destination
    int fd_source, fd_dest;
    //File stat buffer for source
    struct stat statbuf;

    //Open source and check if it failed due to no file or permission error.
    //Used O_RDONLY flag as we only need to read file
    if((fd_source = open(source, O_RDONLY)) == -1){
        printf("Error: Can't read the Source file\n");
        return -1;
    }

    //Create Dest file / open for overwrite and check if some error occurred 
    //Error can include permission error, memory error and others.
    //mode 0400 for write and 0200 for read permission - so 0600 mode
    if((fd_dest = creat(dest, 0600)) == -1){
        printf("Error: Can't create output file\n");
        close(fd_source);
        return -1;
    }
    
    //stat function adds the stat structure info of file in statbuf
    //statbuf used for size argument of read and write
    stat(source, &statbuf);
    char* data;
    
    // Read all data at once and write    
    read(fd_source, data, statbuf.st_size);
    write(fd_dest, data, statbuf.st_size);
    
    /** looping algo
    int s; // stores number of bytes read
    while((s = read(fd_source, data, 64)) != 0){
        write(fd_dest, data, s);
    }
    */

    //close both files after operation
    close(fd_source);
    close(fd_dest);

    return 0;
}

int main(){
    char *source = malloc(100), *dest = malloc(100);
    printf("Enter the name of source file: ");
    scanf("%s", source);
    printf("Enter the name of destination file: ");
    scanf("%s", dest);
    if(file_copy(source, dest) != -1){
        printf("Copy completed Successfully!\n");
    }
}

//Reference https://pubs.opengroup.org/ and https://www.gnu.org/software/libc/manual