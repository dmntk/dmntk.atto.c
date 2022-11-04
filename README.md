**DMNTK** | Decision Model and Notation Toolkit

# Decision table editor

## Overview

Terminal based editor for decision tables written in **C**.

**WORK IN PROGRESS**

#### Box-drawing characters used to represent a decision table

```
 ┌ ─ ┬   ╥   ┐   
 
 │       ║
 
 ├   ┼   ╫   ┤
 
         ╟
         
         ╢
 
 ╞ ╧ ╪ ╤ ╬ ═ ╡
 
 └   ┴   ╨   ┘
```

## Dependencies

#### cmake

```
$ sudo dnf install cmake
```

#### Ninja

```
$ sudo dnf install ninja-build
```

#### ncurses

This decision table editor uses [ncurses](https://invisible-island.net/ncurses/) as a backend to interact with the
terminal.
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

## License

Licensed under either of

- [MIT license](https://opensource.org/licenses/MIT) ([LICENSE-MIT](https://github.com/dmntk/dmntk.rs/blob/main/LICENSE-MIT))
- [Apache License, Version 2.0](https://www.apache.org/licenses/LICENSE-2.0) ([LICENSE-APACHE](https://github.com/dmntk/dmntk.rs/blob/main/LICENSE-APACHE))

at your option.

### Contribution

All contributions intentionally submitted for inclusion in the work by you,
shall be dual licensed as above, without any additional terms or conditions.