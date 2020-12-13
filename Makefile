build:
	gcc -o main main.c

debug:
	gcc -g -o main main.c

clean:
	rm -f main

run:
	./main

runDebug:
	gdb main


buildBaseVersion:
	gcc -o mainBaseVersion mainBaseVersion.c matrix.c -pthread

debugBaseVersion:
	gcc -g -o mainBaseVersion mainBaseVersion.c

cleanBaseVersion:
	rm -f mainBaseVersion

runBaseVersion:
	./mainBaseVersion

runDebugBaseVersion:
	gdb mainBaseVersion


buildAdvancedVersion:
	gcc -o mainAdvancedVersion mainAdvancedVersion.c -pthread

debugAdvancedVersion:
	gcc -g -o mainAdvancedVersion mainAdvancedVersion.c

cleanAdvancedVersion:
	rm -f mainAdvancedVersion

runAdvancedVersion:
	./mainAdvancedVersion

runDebugAdvancedVersion:
	gdb mainAdvancedVersion