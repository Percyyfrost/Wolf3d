NAME = Wolf3d

CC = gcc

CFLAGS = -lSDL2 -L libft -lft -o $(NAME) -I include/ -I include/SDL2/ -L ~/lib

CFILES = src/*.c

$(NAME):
	gunzip -c SDL2-2.0.7.tar.gz | tar xf -
	cd SDL2-2.0.7; \
	mkdir build; \
	cd build; \
	../configure; \
	make
	mkdir -p ~/lib/
	cp SDL2-2.0.7/build/build/.libs/libSDL2-2.0.0.dylib ~/lib/
	ln -F -s ~/lib/libSDL2-2.0.0.dylib ~/lib/libSDL2.dylib
	mkdir -p include/SDL2
	cp SDL2-2.0.7/include/*.h include/SDL2/
	@make -C libft/ fclean && make -C libft/
	$(CC) $(CFILES) $(LIB) $(CFLAGS)

all: $(NAME)

fclean:
	rm -rf $(NAME)
	rm -rf SDL2-2.0.7
	rm -rf include/SDL2

re: fclean all

co:
	@make -C libft/ fclean && make -C libft/
	$(CC) $(CFILES) $(CFLAGS)
