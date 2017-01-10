mine_sweeper.out: main.o makeboard.o printboard.o gameplay.o endgame.o
	gcc -Wall -g -o mine_sweeper.out makeboard.o printboard.o gameplay.o endgame.o main.o
	
main.o: structdef.h makeboard.h printboard.h gameplay.h endgame.h main.c
	gcc -Wall -g -c -o main.o main.c
	
makeboard.o: structdef.h makeboard.h gameplay.h makeboard.c 
	gcc -Wall -g -c -o makeboard.o makeboard.c

printboard.o: structdef.h printboard.h printboard.c
	gcc -Wall -g -c -o printboard.o printboard.c
	
gameplay.o: structdef.h gameplay.h printboard.h endgame.h gameplay.c
	gcc -Wall -g -c -o gameplay.o gameplay.c
	
endgame.o: structdef.h printboard.h endgame.h endgame.c
	gcc -Wall -g -c -o endgame.o endgame.c
	
clean:
	rm *.o *.out
