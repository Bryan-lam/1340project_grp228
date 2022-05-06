flags = -pedantic-errors -std=c++11
endnc = -lncursestw
custom_headers = -I headers
local_ncurses = -I local_jetpack/include -I local_jetpack/include/ncursestw -L local_jetpack/lib


main: main.cpp headers/player.h headers/pipe.h headers/gamemanager.h headers/format.h
	g++ $(flags) $(custom_headers) $(local_ncurses) main.cpp $(endnc) -o main


ncurses_has_been_set_up.txt:
	./install_ncurses.sh

delnc:
	rm -r ncurses_has_been_set_up.txt
	rm -rf local_jetpack ncurses
	echo "The ncurses files have been deleted"


clean:
	rm -r main
