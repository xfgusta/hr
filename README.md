# hr

hr prints a horizontal rule, like the hr tag in HTML, in your terminal

## Installation

#### Requirements

+ make
+ gcc (and a POSIX environment)

Build and install with:

```
git clone https://github.com/xfgusta/hr.git
cd hr
make
```

And then `make install` as root.

To uninstall, run `make uninstall` as root as well.

## Example

```
$ pwd; ls -l; tree
/home/gusta/Desktop/hr
total 12
-rw-r--r--. 1 gusta gusta 2767 mai 23 23:30 main.c
-rw-r--r--. 1 gusta gusta  301 mai 23 23:17 makefile
-rw-r--r--. 1 gusta gusta  792 mai 23 23:31 README.md
.
├── main.c
├── makefile
└── README.md

0 directories, 3 files
```

```
$ pwd; hr; ls -l; hr; tree
/home/gusta/Desktop/hr
-----------------------------------------------------
total 12
-rw-r--r--. 1 gusta gusta 2767 mai 23 23:30 main.c
-rw-r--r--. 1 gusta gusta  301 mai 23 23:17 makefile
-rw-r--r--. 1 gusta gusta 1063 mai 23 23:32 README.md
-----------------------------------------------------
.
├── main.c
├── makefile
└── README.md

0 directories, 3 files
```

Use `hr -h` for more options.

## License

The MIT License (MIT)

Copyright (c) 2021 Gustavo Costa