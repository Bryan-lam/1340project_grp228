flags = -pedantic-errors -std=c++11
endnc = -lncursestw -ldl -lpthread
custom_headers = -I ./headers
local_ncurses = -I ./local_jetpack/include -I ./local_jetpack/include/ncursestw -L ./local_jetpack/lib
nc = ncurses_has_been_set_up.txt

ncurses_has_been_set_up.txt:
	chmod +x install_ncurses.sh
	./install_ncurses.sh

main: main.cpp headers/player.h headers/pipe.h headers/gamemanager.h headers/format.h $(nc)
	g++ $(flags) $(custom_headers) $(local_ncurses) -o main main.cpp $(endnc)

delnc:
	rm -r ncurses_has_been_set_up.txt
	rm -rf local_jetpack ncurses
	echo "The ncurses files have been deleted"


clean:
	rm -r main
