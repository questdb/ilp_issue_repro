# Issue

https://questdb.slack.com/archives/C1NFJEER0/p1663739931498599?thread_ts=1661503075.081309&cid=C1NFJEER0

# Building the example

```
$ cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
$ cmake --build build --target main
```

# Running

```
$ (cd build && ./main)
```

# Cleaning

```
$ rm -fR build
```

# Prerequisites

* A recent Rust compiler (See: https://rustup.rs/).
* A recent GCC compiler or Visual Studio on Windows.
* CMake.
