NAME = run

CFILES = \
ft_ls_functions/general_utility.c\
ft_ls_functions/directory_info.c\
ft_ls_functions/flags.c\
ft_ls_functions/parsing.c\
ft_ls_functions/printing.c\

OFILES = $(CFILES:%.c=%.o)

CFLAGS = -g

MAIN = tests/rmuTest.c
INCLUDES = -I inc
STATIC_LIBS = static_libraries/*

all : $(OFILES)  
	gcc $(CFLAGS) $(INCLUDES) $(OFILES) $(MAIN) $(STATIC_LIBS) -o $(NAME)

%.o : %.c
	gcc $(CFLAGS) $(INCLUDES) -c $< -o $@


