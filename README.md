## Mesh Shell
A simple shell I wrote in C that does one thing well, which is just being a shell, not a full programming language, fuzzy finder and environment manager like bash. It was named "Mesh" because it combines "m" from "minimal" and "sh" from "shell" in one word.

## Installation process
You need to compile it first. Make sure you're at the root of the repository and you have gcc installed.
```bash
./compile.sh
```
Then you install it.
```bash
sudo cp bin/main /bin/mesh-shell
```

## Reversing the installation process
Remove the binary file.
```bash
sudo rm /bin/mesh-shell
```

## Using it
Run the command below to enter the shell once you have installed it.
```bash
/bin/mesh-shell
```
Now you will be presented with the prompt. Type "help" for instructions on how to use it.

## Copyright
2026 Minetomba minetomba@proton.me