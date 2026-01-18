#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <assert.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>


int a[100000]; // the global array 
unsigned long correct_array(int n){
    int i;
    unsigned long sum = 0;
    for (i = 0; i < n; i++) {
        sum = sum + a[i];
    }
    return sum;
}

int main(void) {
    printf("Hello world\n");
    long int s;
    s = correct_array(100000); // Can also change fault array and a to 30 to match it.
    printf("Faulty array sum:%ld\n", s);
    return 0; // if it passes then it owuld be Faulty array sum:0
}
//THe error found is that the global array a has a smaller size than the number of iterations of faulty_array.
//This caused the out of bounds access when n is larger than 100000.
// I'm not sure if a global variable is needed to be defined so that the global array 
// and the function faulty_array are the same