file_clean:
	rm -rf *.bin

file_mock:
	gcc mock.c implementation_file.c -o hospitium
	./hospitium	

file_implementation:
	gcc main.c implementation_file.c -o hospitium
	./hospitium

db_clean:
	gcc clean_db.c -o clean_db -lsqlite3 -std=c99
	./clean_db

db_mock:
	gcc mock.c implementation_db.c -o hospitium -lsqlite3 -std=c99
	./hospitium

db_implementation:
	gcc main.c implementation_db.c -o hospitium -lsqlite3 -std=c99
	./hospitium
