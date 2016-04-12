# d24_framework
Quick and dirty framework for competitions like Deadline24

There are at least a few competitions, in which the task is to create a program playing a certain
game using TCP. Since they are very time limited, creating framework to reduce work on common things
is a good idea. This repository is my attempt at this - it contains a small wrapper over Boost's
TCP streams, and also some basic visualization primitives (using CImg library).

Example code of actual game is in `game.cpp`. In that file, you can see how to use the network streams
and draw simple objects in practice.

Note that to test the library, you'll have to connect to server. The simplest way to do this would
be hand-writing server commands using `nc` command line tool.
