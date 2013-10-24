# global Options

CC = gcc

# Base programm

LIBS = `pkg-config --libs glib-2.0` -lpurple -lusb -ldl 
INCLUDEDIR =  -I ./src/ -I /usr/include/libpurple/ -I /usr/include/glib-2.0/ -I /usr/lib/glib-2.0/include/  
SRC = $(wildcard src/*.c) 
OBJECTS = $(SRC:%.c=obj/%.o)
NAME   = chatbot
CFLAGS  = -o -Wall -fPIC

LIBSRC=src/cmds.c src/emalloc.c src/list.c plugin/plugin.c
LIBOBJ=$(LIBSRC:%.c=obj/lib/%.o)
LIB=lib/libcb_plugin.so

LCFLAGS= -shared -o -Wl,-soname,

Dirs = $(filter-out plugin/, $(sort $(dir $(wildcard plugin/*/))))
dirnames = $(subst /, , $(subst plugin/,, $(Dirs)))


default: $(NAME) $(LIB) plugins

plugins:
	@$(foreach direct, $(dirnames), $(MAKE) -f makefile.plugin arg1=$(direct) && ) true	

$(LIB): $(LIBOBJ)
	@echo "erstelle library" $(LIB)
	@mkdir -p lib
	@ar rcs $(LIB) $(LIBOBJ)

$(NAME) : CFLAGS:=-DMAIN_PROC
$(NAME) : $(OBJECTS)
	@echo "linke " $(NAME)
	@$(CC) -o $(NAME) $(OBJECTS) $(LIBS)
	@echo "erstellt"
	
$(OBJECTS): | obj

obj:
	@mkdir -p $@
	
obj/%.o: %.c
	@mkdir -p $(dir name $@)
	@echo "compiliere " $<
	@$(CC) $(CFLAGS) $(INCLUDEDIR) -c $< -o $@

obj/lib/%.o: %.c
	@mkdir -p $(dir name $@)
	@echo "compiliere " $<
	@$(CC) $(CFLAGS) $(INCLUDEDIR) -I ./plugin -c $< -o $@


clean:
	@rm -r -f obj
	
distclean: clean
	@rm -r -f lib plugins obj
	@rm -f chatbot
	
