# hr

A tool that prints a horizontal rule, like the HTML `<hr>` tag, to your terminal. **hr** is particularly useful for distinguishing the output when running multiple commands.

## Example

```text
$ pwd; hr; tree -v
/home/xfgusta/Desktop/hr
--------------------------------------------------------------------------------
.
├── LICENSE
├── README.md
├── hr.1
├── hr.c
└── makefile

0 directories, 5 files
```

## Installation

### From source

The install directory defaults to `/usr/local`:

```text
make install
```

You can install **hr** in a different directory using the `PREFIX` variable:

```text
make PREFIX=/usr install
```

## License

Copyright (c) 2022 Gustavo Costa. Distributed under the MIT license.
