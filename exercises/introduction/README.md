# Introduction Exercises

This is the programming exercise to accompany the [Introduction Chapter](../../lectures/1-introduction.md).

Make sure the Docker daemon is running on your machine, then run this command from `/path/to/c-programming/exercises/introduction` to start your developer shell:

    $ docker run -it -v `pwd`:/projects/introduction -w /projects/introduction gcc:latest bash

Edit the source file [`calc.c`](calc.c) on your host machine and then compile your changes in the docker container:

    $ make
    $ ./calc
 
Implement these functions in [`calc.c`](calc.c):

* `push`
* `pop`
* `drop`
