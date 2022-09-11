CC ?= gcc
CFLAGS ?= -Wall -Wextra -Werror -pedantic -std=gnu11 -O2

PREFIX ?= /usr/local
BINDIR ?= $(PREFIX)/bin

INSTALL ?= install -p -m 0755

hr: hr.c
	$(CC) $(CFLAGS) hr.c $(LDFLAGS) -o hr

install: hr
	mkdir -p $(DESTDIR)$(BINDIR)
	$(INSTALL) hr $(DESTDIR)$(BINDIR)

uninstall:
	rm -f $(DESTDIR)$(BINDIR)/hr

clean:
	rm -f hr

.PHONY: install uninstall clean
