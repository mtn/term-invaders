invader: src/main.c src/enemy.c src/player.c src/lib/main.h src/lib/enemy.h src/lib/player.h
	gcc -lncurses src/main.c src/enemy.c src/player.c -o invader

clean:
	rm -rf *.o a.out invader
