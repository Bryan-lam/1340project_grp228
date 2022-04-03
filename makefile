flags = -pedantic-errors -std=c++11 -Wall
begnc = -I local_jetpack/include -I local_jetpack/include/ncursestw -L local_jetpack/lib
endnc = -lncursestw -ldl -pthread
nc = ncurses_has_been_set_up.txt

main: main.cpp
	g++ $(flags) $(begnc) main.cpp -o main $(endnc) 

ncurses_has_been_set_up.txt:
	./install_ncurses.sh

delnc:
	rm -r ncurses_has_been_set_up.txt
	rm -rf local_jetpack ncurses
	echo "The ncurses files have been deleted"

clean:
	rm -r main