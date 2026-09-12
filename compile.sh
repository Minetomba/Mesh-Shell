#!/bin/bash
mkdir -p bin
read -p "Static or dynamic? (S/d) " choice
if [[ $choice == "d" ]]; then
	echo "Building dynamically..."
	for f in src/*.c; do
		gcc -O3 -Wall -Wextra "$f" -o "bin/$(basename "${f%.c}")"
	done
else
	echo "Building statically..."
	for f in src/*.c; do
		gcc -static -O3 -Wall -Wextra "$f" -o "bin/$(basename "${f%.c}")"
	done
fi