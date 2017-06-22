CC=gcc
AFLAGS=-Wall -g
LDFLAGS= -lmysqlclient
OBJS= add.cgi del.cgi mod.cgi sel.cgi school.add.cgi school.del.cgi school.mod.cgi school.sel.cgi score.add.cgi score.del.cgi score.mod.cgi  score.sel.cgi status.cgi

all:$(OBJS)

$(OBJS):%.cgi:%.c
	$(CC) $(AFLAGS) $< cgic.c -o $@ $(LDFLAGS)

.PHONY:clean
clean:
	rm ./*.cgi
install:
		cp *.cgi /usr/lib/cgi-bin/sx
		cp *.html /usr/lib/cgi-bin/sx
		sudo cp *.html /var/www/html
