# Introduction Exercises

Run this command to start your devloper shell environment:

    docker run -it -v `pwd`:/projects/introduction -w /projects/introduction gcc:latest bash

Edit the source file [`calc.c`](calc.c) on your host machine and then compile your changes in the docker container:

    $ make
    $ ./calc
 
