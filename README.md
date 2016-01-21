# dwarfcaves
A quick 'n dirty dungeon generator in C++.

## About
dwarfcaves is a *Dwarf Cave* generator. A Dwarf Cave is a square area with rooms and tunnels. Daniel was looking for a quick way to generate basic dungeons in C++ and this is what he came up with.

This software gives no guaruntees that the Dwarf Caves generated are 100% traversable or fun. They should be traversable and fun enough, none the less.

## Building
To build, run the makefile with a tool like [GNU Make](https://www.gnu.org/software/make/). You'll need a C++11 compiler like [clang](http://clang.llvm.org/) or [gcc](https://gcc.gnu.org/) as well. For me, this involves entering `make` in the project's root folder.

## Running
Running dwarfcaves requires a seed, which you can pass it. If you want, you can also pass in cave size and a number of attempts at placing rooms. For example, entering:
```
$ ./dwarfcaves foo 30 100
```
Gives you something like:
```
▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢ 
▢ ▢ ▢ ▢ ▢ ▢ ▢   ▢ ▢ ▢ ▢                                 ▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢ 
▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢       ▢   ▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢         ▢ ▢         ▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢ 
▢ ▢ ▢ ▢ ▢ ▢ ▢     ▢   ▢         ▢                   ▢ ▢ ▢ ▢         ▢ ▢     ▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢ 
▢ ▢ ▢ ▢ ▢ ▢ ▢   ▢ ▢     ▢ ▢ ▢   ▢                   ▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢     ▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢ 
▢ ▢ ▢ ▢ ▢ ▢ ▢   ▢ ▢ ▢           ▢                   ▢               ▢ ▢ ▢ ▢   ▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢ 
▢ ▢ ▢ ▢ ▢ ▢ ▢   ▢ ▢ ▢ d ▢ ▢ d ▢ ▢                   ▢               ▢ ▢ ▢ ▢   ▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢ 
▢ ▢ ▢ ▢ ▢ ▢ ▢   ▢               ▢                   ▢               ▢ ▢ ▢ ▢               ▢ ▢ ▢ ▢ ▢ 
▢ ▢ ▢ ▢ ▢ ▢ ▢   ▢               ▢                   ▢               ▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢   ▢ ▢ ▢ ▢ ▢ 
▢ ▢ ▢ ▢ ▢ ▢     ▢               ▢                   ▢               ▢   ▢ ▢ ▢               ▢ ▢ ▢ ▢ 
▢ ▢ ▢ ▢ ▢ ▢   ▢ ▢               ▢ ▢ ▢ d ▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢ d ▢ ▢ d ▢ ▢ ▢ ▢ ▢ ▢ d ▢ ▢ ▢ ▢ ▢ d ▢ ▢ ▢ ▢ 
▢ ▢ ▢ ▢ ▢ ▢   ▢ ▢               ▢                   ▢             ▢ ▢               ▢           ▢ ▢ 
▢       ▢ ▢   ▢ ▢ ▢ ▢ ▢ ▢ ▢ d ▢ ▢                   ▢   ▢ ▢ ▢ d ▢ ▢ ▢               ▢           ▢ ▢ 
▢   ▢         ▢ ▢ ▢ ▢ ▢ ▢ ▢     ▢                   ▢   ▢           ▢               ▢           ▢ ▢ 
▢   ▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢   d                   ▢   d           ▢               ▢           ▢ ▢ 
▢   ▢           ▢ ▢ ▢ ▢ ▢ ▢ ▢   ▢                   ▢ ▢ ▢           ▢               ▢           ▢ ▢ 
▢   ▢           ▢ ▢ ▢ ▢ ▢ ▢     ▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢           d               ▢           ▢ ▢ 
▢   ▢           ▢ ▢ ▢ ▢ ▢     ▢       ▢ ▢           ▢ ▢ ▢           ▢               ▢           ▢ ▢ 
▢   ▢           ▢ ▢ ▢ ▢ ▢   ▢ ▢   ▢     ▢           ▢ ▢ ▢           ▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢           ▢ ▢ 
▢   ▢           ▢ ▢ ▢ ▢ ▢         ▢ ▢   ▢           ▢ ▢ ▢           ▢               ▢           ▢ ▢ 
▢   ▢           ▢ ▢ ▢ ▢ ▢ ▢ ▢ d ▢ ▢ ▢   d           ▢ ▢ ▢           d               ▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢ 
▢   d           ▢                   ▢   ▢           ▢ ▢ ▢           ▢               ▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢ 
▢   ▢           ▢                   ▢   ▢           ▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢               ▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢ 
▢   ▢           ▢                   ▢   ▢           ▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢               ▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢ 
▢   ▢ ▢ ▢ ▢ ▢ ▢ ▢                   ▢   ▢ ▢ ▢ d ▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢               ▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢ 
▢     ▢ ▢ ▢ ▢ ▢ ▢                   ▢       ▢           ▢ ▢ ▢ ▢ ▢ ▢ ▢               ▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢ 
▢ ▢         ▢ ▢ ▢                   ▢   ▢   d           ▢ ▢ ▢       ▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢ 
▢ ▢ ▢   ▢       ▢                   ▢     ▢ ▢           ▢       ▢           ▢ ▢ ▢           ▢ ▢ ▢ ▢ 
▢ ▢ ▢   ▢ ▢ ▢ d ▢ d ▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢   ▢ ▢           ▢   ▢ ▢ ▢ ▢ ▢ ▢ ▢ d ▢ ▢ ▢           d   ▢ ▢ 
▢ ▢ ▢   ▢               ▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢     ▢           ▢   ▢                   ▢           ▢   ▢ ▢ 
▢ ▢ ▢   ▢               ▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢   d           ▢   d                   ▢           d     ▢ 
▢ ▢ ▢   ▢               ▢               ▢   ▢           ▢   ▢                   ▢           ▢ ▢   ▢ 
▢ ▢ ▢   ▢               ▢               ▢   ▢ ▢ ▢ d ▢ ▢ ▢   ▢                   ▢ ▢ ▢ d ▢ ▢ ▢     ▢ 
▢ ▢     ▢               ▢               ▢               ▢   ▢                   ▢   ▢   ▢       ▢ ▢ 
▢     ▢ ▢               ▢               ▢ ▢ ▢ ▢   ▢ ▢   ▢   ▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢       ▢   ▢ ▢ 
▢   ▢   ▢               ▢               ▢ ▢       ▢ ▢       ▢ ▢         ▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢   ▢ ▢ 
▢     ▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢ d d ▢ ▢ ▢   ▢ ▢ ▢ ▢ ▢ ▢         ▢ ▢   ▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢   ▢ ▢ 
▢ ▢     ▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢             ▢ ▢ ▢         ▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢       ▢ ▢ ▢           ▢   ▢ ▢ 
▢ ▢ ▢               ▢ ▢ ▢   ▢ ▢   ▢ ▢ ▢ ▢     ▢ ▢   ▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢   ▢   d           ▢     ▢ 
▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢       ▢     ▢             ▢       ▢               ▢ ▢ ▢   ▢   ▢           ▢ ▢   ▢ 
▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢     ▢     ▢ ▢ ▢ ▢ ▢ ▢ ▢   ▢ ▢ ▢               ▢ ▢ ▢       ▢           ▢ ▢   ▢ 
▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢   ▢ ▢   ▢           ▢       ▢               ▢ ▢ ▢ ▢ ▢ ▢ ▢           ▢     ▢ 
▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢   ▢ ▢   d           ▢ ▢ ▢   ▢               ▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢   ▢ ▢ 
▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢   ▢ ▢ ▢ ▢           ▢ ▢     ▢               ▢               ▢ ▢ ▢ ▢     ▢ ▢ 
▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢     ▢ ▢ ▢ ▢           ▢ ▢   ▢ ▢               d               d   ▢     ▢ ▢ ▢ 
▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢   ▢ ▢ ▢ ▢ ▢           ▢ ▢     ▢               ▢               ▢   ▢   ▢ ▢ ▢ ▢ 
▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢   ▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢   ▢ ▢ ▢ d ▢ ▢ ▢ ▢ ▢               d       ▢ ▢ ▢ ▢ 
▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢   ▢ ▢ ▢       ▢       ▢           ▢   ▢ ▢ ▢ ▢ ▢               ▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢ 
▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢           ▢       ▢       ▢ ▢ ▢       ▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢   ▢ 
▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢ ▢ 
```
The `▢` symbol represents a wall, while a `d` represents a doorway into a room.

## Pull Requests
This isn't really an active project, but if you're keeen on adding something or fixing a bug feel free to open a pull request. Cheers!
