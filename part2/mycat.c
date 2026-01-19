#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <assert.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
// I am going to comment each part of the code to show what does what, in order to differentiate my work from GPT's. I also acknowledge that GPT helped me write this code.
// it used standard C code and the result is almost the same as what was written below. 

#define BUF_SIZE 4096 //this was defined due to the read function needing a size_t count.

int main(int argc, char *argv[]) {
    int fd;
    ssize_t n; //signed size type for length which was used in the while function to read the file.
    char buf[BUF_SIZE]; 

    
    if (argc == 1) {
        fd =STDIN_FILENO;// If there is no filename, it defaults to file descriptor 0 (stdin)
    }


    else if (argc == 2) { // when there are 2 arguments (first argument is ./mycat and the second would be the file name given)
        fd = open(argv[1], O_RDONLY); // Opens the file in read-only mode
        if (fd < 0) {// if File failed or doesnt exists (would return a 0 or -1 depending on the error)
            perror("Error opening file, Try Again"); // Print if there's an error
            exit(1);
        }
    }
    else {// if there are more than 2 arguments, provides a standard usage message.
        fprintf(stderr, "Usage: %s [filename]\n", argv[0]);
        exit(1);
    }

    while ((n = read(fd, buf, BUF_SIZE)) > 0) {// ssize_t read(int fd, void *buf, size_t count);
        // This while loop reads the file in chunks that was specified 4096 bytes at a time
        if (write(STDOUT_FILENO, buf, n) != n) {//If bytes don't match then it gives an error and exits.
            perror("Error writing to stdout");
            exit(1);
        }
    }

    if (n < 0) {
        perror("Error reading file");// if there was an error reading the file as n can be 0 or less due to some error.
        exit(1);
    }

    if (fd != STDIN_FILENO) {
        close(fd);//Closes the file to prevent any resource leaks.
    }

    return 0;
}
