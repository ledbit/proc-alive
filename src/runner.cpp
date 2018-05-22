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
    if (argc != 3) {
      printf("usage: %s <path-to-fifo> <timeout>\n", argv[0]);
      return -1;
    }

    int fd;
 
    char * myfifo = argv[1];
    mkfifo(myfifo, 0666);

    printf("opening fifo for read: path=%s\n", myfifo); 
    // opening a fifo in read-only non-blocking mode will  
    // succeed even if noone is attached on the other end
    // http://man7.org/linux/man-pages/man7/fifo.7.html
    fd = open(myfifo, O_RDONLY | O_NONBLOCK);

    if(fd < 0) {
      printf("ERROR: failed to open fifo: path=%s, errno=%d, (%m)\n", myfifo, errno);
      return -1;
    }
    
    printf("opened fifo for read: path=%s\n", myfifo);

    int sleepSecs = atoi(argv[2]);
    sleepSecs = sleepSecs < 1 ? 120 : sleepSecs;

    printf("sleeping for %d seconds ...\n", sleepSecs);
    sleep(sleepSecs);

    
    printf("cleaning and exiting ...\n");
    close(fd);
    unlink(myfifo);
    return 0;
}
