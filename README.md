# Minishell

Minishell is a simplified Unix shell written in C as part of the École 42 core curriculum. It aims to replicate key functionalities of a real shell like `bash`, including command parsing, built-ins, pipes, redirections, and process management — all implemented using low-level system calls.


## 🚀 Features

- Execution of external commands using `PATH`
- Built-in commands:
  - `echo`, `cd`, `pwd`, `export`, `unset`, `env`, `exit`
- Command parsing with:
  - Quotes handling (`'`, `"`)
  - Environment variable expansion (`$VAR`)
  - Escape characters
- Pipes (`|`) and redirections:
  - Input `<`, output `>`, append `>>`, and here-document `<<`
- Proper signal handling (`Ctrl+C`, `Ctrl+\`)
- Exit codes and status management
- Manual memory management (Valgrind-clean)


## 🛠️ System Calls Used

- `fork()`
- `execve()`
- `pipe()`
- `dup2()`
- `wait() / waitpid()`
- `signal()`
- `isatty()`, `tcgetattr()`, `tcsetattr()`
- `open()`, `read()`, `write()`, `close()`
- And more…


## 📦 Installation

```bash
git clone https://github.com/yourusername/minishell.git
cd minishell
make
```

## 🧪 Usage - examples

After building the project with `make`, run the shell with:

```bash
./minishell

$ echo "Hello, Minishell!"
Hello, Minishell!

$ export NAME=John
$ echo $NAME
John

$ pwd
/path/to/minishell

$ ls -l | grep minishell

$ cat < input.txt > output.txt

$ echo $?
0
