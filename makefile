CC ?= gcc
CFLAGS ?= -Wall -Wextra -Werror -pedantic -std=c11 -O2

PREFIX ?= /usr/local
BINDIR ?= $(PREFIX)/bin
MANDIR ?= $(PREFIX)/share/man

INSTALL ?= install -p -m 0755
INSTALL_MAN ?= install -p -m 0644

hr: hr.c
	$(CC) $(CFLAGS) hr.c $(LDFLAGS) -o hr

install: hr
	mkdir -p $(DESTDIR)$(BINDIR)
	$(INSTALL) hr $(DESTDIR)$(BINDIR)
	mkdir -p $(DESTDIR)$(MANDIR)/man1
	$(INSTALL_MAN) hr.1 $(DESTDIR)$(MANDIR)/man1

uninstall:
	rm -f $(DESTDIR)$(BINDIR)/hr
	rm -f $(DESTDIR)$(MANDIR)/man1/hr.1

clean:
	rm -f hr

.PHONY: install uninstall clean
