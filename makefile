all: DumbWeaver

DumbWeaver: custom.c
	gcc Server.c custom.c constants/cn.c constants/cl.c constants/msg.c constants/templ.c -o DumbWeaver -lncurses
