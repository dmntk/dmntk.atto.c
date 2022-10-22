**DMNTK** | Decision Model and Notation Toolkit

# Decision table editor

## Overview

Terminal based editor for decision tables written in **C**.

**WORK IN PROGRESS**

## Dependencies

### cmake

```
$ sudo dnf install cmake
```

### Ninja

```
$ sudo dnf install ninja-build
```

### ncurses

This decision table editor uses [ncurses](https://invisible-island.net/ncurses/) as a backend to interact with the terminal.
To properly compile, the development version of **ncurses** is required.

To install **ncurses** in CentOS/RHEL/Scientific Linux 6.x/7.x+ and Fedora Linux 21 or older, type:
```shell
$ sudo yum install ncurses-devel
```

To install **ncurses** in Fedora Linux 22.x+, type:
```shell
$ sudo dnf install ncurses-devel
```

To install **ncurses** under in Debian/Ubuntu Linux, type:
```shell
$ sudo apt-get install libncurses5-dev libncursesw5-dev
```
