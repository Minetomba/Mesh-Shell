#!/bin/bash
# SPDX-FileCopyrightText: 2026 Minetomba <minetomba@proton.me>
# SPDX-License-Identifier: GPL-3.0-only
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