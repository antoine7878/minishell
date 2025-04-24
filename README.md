# minishell

**minishell** 42's project is about built a minimal Bash-inspired shell that interprets and executes user input.

## ⚙️ Features

- Recursive AST parsing
- Basic shell grammar support including:
  - Piping (`|`)
  - Redirection (`>`, `<`, `>>`, `<<`)
  - Logical operators (`&&`, `||`)
  - Parentheses for priority only
- Quoting and escaping (`'`, `"`)
- Environment variable expansion (`$VAR`)
- Built-in commands: `cd`, `echo`, `pwd`, `exit`, `export`, `unset`, `env`
- Heredoc (`<<`) with proper signal and EOF handling
- Signal management (`SIGINT`, `SIGQUIT`)
- Wildcard expansion (`*`)
- Interactive terminal behaviors and readline-like UX

## 🧠 Learning Objectives

- Recursive descent parsing for command line grammar
- Building and traversing an Abstract Syntax Tree (AST)
- Implementing POSIX-compatible shell behavior
- UNIX process lifecycle: `fork`, `execve`, `waitpid`
- File descriptor management and I/O redirection
- Unix signals and user interrupt handling
- Robust error detection and messaging

Ubuntu clang version 12.0.1-19ubuntu3
Target: x86_64-pc-linux-gnu
