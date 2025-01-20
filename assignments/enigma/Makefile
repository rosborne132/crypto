all: build test

build:
	podman build -t enigma .

test:
	podman run enigma python3 tester.py

