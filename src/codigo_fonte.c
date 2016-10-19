#include <stdio.h>                           
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <signal.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/resource.h>


int main (int argc, char *argv[], char *envp[]) {

  	int pid, i; // process identification and counter, respectively
    long int memory[10]; // saves the use of memory of every second in an array
  	long int memory_total = 0; // adds every component of memory[10]
    long int ucp[10], ucp_decimal[10]; // saves the use of ucp and its decimal part
    double time_spent; // used to assist the time management 
    struct rusage rusage; // used to obtain returned information of getrusage() function
    clock_t begin; // struct used to assist the time management

    pid = fork(); // child process creation

    if ( pid < 0 ) { // if fork isn't working
        perror ("Erro: ") ;
        exit (-1) ;
    } else if( pid > 0 ) { // if pid we're in father's process
        for(i = 0; i < 10; i++) { 
            begin = clock(); // checks the current time

            while(1) {
                time_spent = (double)(clock() - begin) / CLOCKS_PER_SEC; // checks how much time has passed

                if (time_spent == 1.0) { // everytime one second goes by does what is bellow
                    getrusage(0, &rusage); // colects data of the child's process
                    memory_total += rusage.ru_maxrss; // adds every use of memory in kilobytes
                    memory[i] = rusage.ru_maxrss; // saves the memory use in kilobytes in an array
                    ucp[i] = rusage.ru_utime.tv_sec; // saves the ucp use in an array
                    ucp_decimal[i] = rusage.ru_utime.tv_usec; // saves the decimal part os ucp use in an array
                    break;
                }
            }
        }
				// kills child's process
        kill(pid, SIGKILL); 
    } else { //if we're in child's process
        if (strcmp(argv[1], "cpu") == 0) { // high use of ucp
            for (;;) {
            }
        } else if (strcmp(argv[1], "cpu-mem") == 0) { // high use of ucp and memory
            for (;;) {
                malloc (sizeof(10));
            }
        } else {
            printf ("\nargv[] digitado incorretamente\n");
        }
    }
		// prints after 10 seconds the memory and cpu use in kilobytes and per cent, respectively
    for (i = 0; i < 10; i++) {
        printf ("Em %d segundo(s):\nMemoria: %ld Kilobytes | CPU: %ld.%ld%c \n\n", i+1, memory[i], ucp[i]*10, ucp_decimal[i]/1000, 37);
    }
		// prints the total use of memory and ucp use
    printf("Uso total de:\nMemoria: %ld Kilobytes | Uso total de CPU: %ld.%ld%c\n", memory_total, ucp[9]*10, ucp_decimal[9]/1000, 37);
    printf ("Tchau!\n") ;
    return 0;
}
