
scat: scat.c deps/commander/commander.c
	$(CC) $^ -o $@ -Wall -Wextra

clean:
	rm -rf scat

.PNONY: clean
