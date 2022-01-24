all: DumbWeaver

DumbWeaver: custom.c
	gcc util/Choices.c util/Screen.c util/Server.c custom.c constants/bd.c constants/cn.c constants/cl.c constants/msg.c constants/templ.c -o DumbWeaver -lncurses
