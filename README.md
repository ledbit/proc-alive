# proc-alive

This is a sample project (supporting this [blog post](https://blog.diag.ai/2018/05/21/single-syscall-process-status-check/)) demonstrating how to check whether a process (usually a daemon) is alive or not as cheaply as possible, ie a single syscall. The idea relies on the behavior of [named pipes](http://man7.org/linux/man-pages/man7/fifo.7.html) (aka FIFO) - specifically the following part:

>A process can open a FIFO in nonblocking mode.  In this case, opening for read-only succeeds even if no one has opened on the write side yet and opening for write-only fails with ENXIO (no such device or address) unless the other end has already been opened.

Let's define the following two processes:
1. runner - the process whose status we're interested in knowing, this process **may not get a chance to exit gracefully**
1. checker - the process which will be responsible for checkin the status of runner

`runner` and `checker` first need to establish some shared randevu point, such as a path - usually this would be a path to a `.pid` file or the like, in our case the `runner` and `checker` will be able to create the path to a **named pipe**. The pipe will be used as follows:

1. runner - at startup, creates and/or opens the pipe for read-only in non-blocking mode (O_RDONLY | O_NONBLOCK). Cleanup is not strictly necessary as the OS will detach the process from the pipe on exit (clean or not)
1. checker - attempt to open the file in write-only in non-blocking mode (O_WRONLY | O_NONBLOCK) - this will only succeed if the pipe exists **and** there is at least one reader on the pipe

I've built this in C/C++ but the concept is useful in other languages as well, as long as they provide you access to pipes, e.g. go, python, node etc. Check out [this project](https://github.com/coccyx/go-procalive) for a GO verion.

# How to

## Build
Simply run

```
make
```
This will create two binaries, `bin/runner` and `bin/checker`

## To test

1. First, to emulate a daemon execute `runner` with a path to a location you have read-write access to and an amount of time for the `runner` to sleep
```
./bin/runner /tmp/mah-pipe 120
```


2. (in another window) Check the status of the `runner` by using the following command - feel free to kill the runner, reboot etc
```
./bin/checker /tmp/mah-pipe
```





