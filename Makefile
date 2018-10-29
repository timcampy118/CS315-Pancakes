all: pancakes

Game.o: Game.cpp
	g++-8.2.0 -std=c++2a -Wall -Wextra -pedantic -fsanitize=address,undefined,pointer-compare,pointer-subtract -fstack-clash-protection -g -fno-omit-frame-pointer -lncurses++ -lmenu -lpanel -lform -lutil -lncurses -c -g Game.cpp

Game_Window.o: Game_Window.cpp
	g++-8.2.0 -std=c++2a -Wall -Wextra -pedantic -fsanitize=address,undefined,pointer-compare,pointer-subtract -fstack-clash-protection -g -fno-omit-frame-pointer -lncurses++ -lmenu -lpanel -lform -lutil -lncurses -c -g Game_Window.cpp

Player.o: Player.cpp
	g++-8.2.0 -std=c++2a -Wall -Wextra -pedantic -fsanitize=address,undefined,pointer-compare,pointer-subtract -fstack-clash-protection -g -fno-omit-frame-pointer -lncurses++ -lmenu -lpanel -lform -lutil -lncurses -c -g Player.cpp

main.o: main.cpp
	g++-8.2.0 -std=c++2a -Wall -Wextra -pedantic -fsanitize=address,undefined,pointer-compare,pointer-subtract -fstack-clash-protection -g -fno-omit-frame-pointer -lncurses++ -lmenu -lpanel -lform -lutil -lncurses -c -g main.cpp

pancakes: Game.o Game_Window.o Player.o main.o
	g++-8.2.0 -std=c++2a -Wall -Wextra -pedantic -fsanitize=address,undefined,pointer-compare,pointer-subtract -fstack-clash-protection -g -fno-omit-frame-pointer -lncurses++ -lmenu -lpanel -lform -lutil -lncurses -o pancakes Game_Window.o Game.o main.o Player.o 

run:
	./pancakes
clean:
	rm *.o