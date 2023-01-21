sq1ite: sq1ite.c
	gcc sq1ite.c -lreadline -std=c17 -o sq1ite

run: sq1ite
	./sq1ite

clean:
	rm -rf sq1ite *.db

.PHONY: run clean
