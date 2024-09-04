# Microkernel_for_uRISCV_uPandaOS-Operative_System_Project
This repo contains the implementation of three of the seven levels of abstraction of *uPandOS*, for the *uRISCV* architecture, written in C. 
The  levels of abstraction are:
- **Level 0**: `Hardware` *(given for this project)*
- **Level 1**: `ROM` *(given for this project)*
- **Level 2**: `The Queues Manager` *(phase1)*
- **Level 3**: `The Nucleus` *(phase2)*
- **Level 4**: `The Support Level` *(phase3)*
- **Level 5**: `File System` *(/)*
- **Level 6**: `The Interactive Shell` *(/)*

## Project Specs.
**All specs for phase 1, 2 and 3 are in the `specs` folder with some useful docs regarding *uRISCV* architecure and *uPandOs* registers and workflow.**

## How to setup uRISCV 
Execute all the instruction in the given order or it may not work properly.
- Clone the repository
#### ~Install the dependencies~
- Debian packages:
```sh
$ sudo apt install git build-essential libc6 cmake libelf-dev libboost-dev libboost-program-options-dev libsigc++-2.0-dev gcc-riscv64-unknown-elf
```
- RISCV toolchain:
```sh
$ git clone https://github.com/riscv/riscv-gnu-toolchain
$ sudo apt-get install autoconf automake autotools-dev curl python3 python3-pip libmpc-dev libmpfr-dev libgmp-dev gawk build-essential bison flex texinfo gperf libtool patchutils bc zlib1g-dev libexpat-dev ninja-build git cmake libglib2.0-dev
$ cd riscv-gnu-toolchain
$ ./configure --prefix=/opt/riscv --with-arch=rv32gc --with-abi=ilp32d
$ sudo make linux
```
#### ~install and build emulator~
- after installing emulator (from the site you want) and extracting it (if needed):
```sh
$ cd uriscv
$ mkdir -p build && cd build
$ cmake .. && make && sudo make install 
```

## How to execute the project
```sh
$ cd path/to/project
$ make
```
## How to run the debugger
- Copy file `launch.json` in directory `.vscode`
- Find the directory with the executable '*kernel*', generally located in the main folder, with
```sh
$ find . -type f -name kernel  
```
- and then
```sh
$ uriscv-cli --config ./config_machine.json
```
- finally run the debugger of your choice.

## Troubleshooting
- if commands of toolchain are not found after installing them, update ambient variable `PATH` adding `/opt/riscv/bin`
- if emulator gives error:
```sh
terminate called after throwing an instance of 'FileError'
  what():  Error accessing `/usr/share/uriscv/exec.rom.uriscv'
[1]    6801 IOT instruction  uriscv-cli --config ./config_machine.json
```
check that `bootstrap-rom` e `execution-rom` paths are correct (they may be `/usr/share/uriscv/...` or `/usr/local/share/uriscv/...`)
