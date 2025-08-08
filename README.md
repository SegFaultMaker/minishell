Minishell
A simplified shell built in C to mimic core features of Bash, enhancing understanding of processes, I/O, and signal handling.

Features Included
Prompt display and command-line input with readline.
Command history support.
Executable lookup and execution using:
$PATH, or relative/absolute paths.
Correct handling of quotes:
Single quotes prevent interpretation of meta-characters.
Double quotes protect most characters but allow $ (variables).

I/O Redirections:
<, >, >> (append), and << (here-document).
Pipes (|) to chain multiple commands.
Environment variable expansion, including $? for exit status.

Signal handling:
Ctrl-C: interrupts and prints a new prompt.
Ctrl-D: exits the shell.
Ctrl-\: ignored.

Built-in commands implemented:
echo (supports -n)
cd
pwd
export
unset
env
exit

How to Use
```
make
./minishell
```
Use environment variables and builtins.

