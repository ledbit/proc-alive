#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
 
int main( int argc, char *argv[])
{
    if (argc != 2) {
      printf("usage: %s <fifo-path-to-check>\n", argv[0]);
      return -1;
    }

    int fd;
    char * myfifo = argv[1];
 
    printf("opening fifo for write: path=%s\n", myfifo); 

    // opening a fifo in non-blocking write only mode will 
    // fail if there is no reader attached on the other end
    fd = open(myfifo, O_WRONLY | O_NONBLOCK);

    if(fd < 0) {
      printf("RUNNER PROCESS IS DEAD (errno=%d, %m)\n", errno);
      return -1;
    }
    
    printf("RUNNER PROCESS IS **ALIVE**\n");
    close(fd);
    return 0;
}

