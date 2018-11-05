all: pancakes

Game.o: Game.cpp
	g++-8.2.0 -std=c++2a -Wall -Wextra -pedantic -fsanitize=address,undefined,pointer-compare,pointer-subtract -fstack-clash-protection -g -fno-omit-frame-pointer -lncurses++ -lmenu -lpanel -lform -lutil -lncurses -c -g Game.cpp

Game_Window.o: Game_Window.cpp
	g++-8.2.0 -std=c++2a -Wall -Wextra -pedantic -fsanitize=address,undefined,pointer-compare,pointer-subtract -fstack-clash-protection -g -fno-omit-frame-pointer -lncurses++ -lmenu -lpanel -lform -lutil -lncurses -c -g Game_Window.cpp

Player.o: Player.cpp
	g++-8.2.0 -std=c++2a -Wall -Wextra -pedantic -fsanitize=address,undefined,pointer-compare,pointer-subtract -fstack-clash-protection -g -fno-omit-frame-pointer -lncurses++ -lmenu -lpanel -lform -lutil -lncurses -c -g Player.cpp

search_node.o: search_node.cpp
	g++-8.2.0 -std=c++2a -Wall -Wextra -pedantic -fsanitize=address,undefined,pointer-compare,pointer-subtract -fstack-clash-protection -g -fno-omit-frame-pointer -lncurses++ -lmenu -lpanel -lform -lutil -lncurses -c -g search_node.cpp

AI_Player.o: AI_Player.cpp search_node.o
	g++-8.2.0 -std=c++2a -Wall -Wextra -pedantic -fsanitize=address,undefined,pointer-compare,pointer-subtract -fstack-clash-protection -g -fno-omit-frame-pointer -lncurses++ -lmenu -lpanel -lform -lutil -lncurses -c -g AI_Player.cpp

main.o: main.cpp
	g++-8.2.0 -std=c++2a -Wall -Wextra -pedantic -fsanitize=address,undefined,pointer-compare,pointer-subtract -fstack-clash-protection -g -fno-omit-frame-pointer -lncurses++ -lmenu -lpanel -lform -lutil -lncurses -c -g main.cpp

test_main.o: test_main.cpp
	g++-8.2.0 -std=c++2a -Wall -Wextra -pedantic -fsanitize=address,undefined,pointer-compare,pointer-subtract -fstack-clash-protection -g -fno-omit-frame-pointer -lncurses++ -lmenu -lpanel -lform -lutil -lncurses -c -g test_main.cpp

pancakes: Game.o Game_Window.o Player.o AI_Player.o search_node.o main.o
	g++-8.2.0 -std=c++2a -Wall -Wextra -pedantic -fsanitize=address,undefined,pointer-compare,pointer-subtract -fstack-clash-protection -g -fno-omit-frame-pointer -lncurses++ -lmenu -lpanel -lform -lutil -lncurses -o pancakes Game_Window.o Game.o main.o Player.o AI_Player.o search_node.o

test: Game.o Game_Window.o Player.o AI_Player.o search_node.o test_main.o
	g++-8.2.0 -std=c++2a -Wall -Wextra -pedantic -fsanitize=address,undefined,pointer-compare,pointer-subtract -fstack-clash-protection -g -fno-omit-frame-pointer -lncurses++ -lmenu -lpanel -lform -lutil -lncurses -o test Game_Window.o Game.o test_main.o Player.o AI_Player.o search_node.o

run:
	./pancakes

clean:
	rm *.o test pancakes
