# Introduction Exercises

On your own machine run this command from `/path/to/c-programming/exercises/introduction` to start your devloper shell environment:

    $ docker run -it -v `pwd`:/projects/introduction -w /projects/introduction gcc:latest bash

Edit the source file [`calc.c`](calc.c) on your host machine and then compile your changes in the docker container:

    $ make
    $ ./calc
 
