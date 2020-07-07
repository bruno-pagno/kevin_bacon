all:
	make compile && make run

compile:
	gcc *.c *.h -I . -ansi -o kevin_bacon

run:
	./kevin_bacon

zip:
	zip -r Trab2_BrunoPagno_JoaoMello.zip *