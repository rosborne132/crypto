all: build test

build:
	podman build -t enigma .

build-enigma:
	podman build -t

enter:
	podman run -it enigma

run-exec:
	@echo "\nRunning local executable ------------------------"
	podman run enigma ./enigma.out "AAA"

test-local: build run-exec

test:
	podman run enigma python3 tester.py

