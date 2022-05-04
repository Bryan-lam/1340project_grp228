flags = -pedantic-errors -std=c++11
endnc = -lncurses

main: main.cpp mainmenu.h player.h pipe.h gamemanager.h
	g++ $(flags) main.cpp $(endnc) -o main

clean:
	rm -r main