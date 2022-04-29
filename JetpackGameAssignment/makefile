flags = -pedantic-errors -std=c++11
endnc = -lncurses

main: main_withoutmenu.cpp player.h pipe.h
	g++ $(flags) main_withoutmenu.cpp $(endnc) -o main

clean:
	rm -r main
