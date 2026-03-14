# minishell

## Table of Contents
- [About](#about)
- [Installation](#installation)
- [Usage](#usage)
- [Features](#features)
- [Built-in Commands](#built-in-commands)
- [Mandatory Part](#mandatory-part)
- [Project Structure](#project-structure)
- [Norminette](#norminette)
- [Authors](#authors)

---

## About

**minishell** is a 42 School project that involves building a functional Unix shell from scratch in C. The goal is to understand how shells work under the hood — including input parsing, environment variable expansion, signal handling, redirections, pipes, and process management using `fork`, `execve`, and `waitpid`.

This project was completed as part of the 42 Bangkok curriculum.

---

## Installation

```bash
git clone <repository_url>
cd minishell
make
```

To clean object files:
```bash
make clean
```

To remove all compiled files:
```bash
make fclean
```

To recompile from scratch:
```bash
make re
```

---

## Usage

```bash
./minishell
```

Once running, you will see the prompt:
```
minishell>
```

You can then type commands just like in bash.

### Examples

```bash
minishell> echo "Hello, World!"
Hello, World!

minishell> ls | grep .c | wc -l
42

minishell> cat << EOF
> hello
> EOF
hello

minishell> export NAME=42Bangkok
minishell> echo $NAME
42Bangkok

minishell> echo $?
0
```

---

## Features

### Parsing & Expansion
- Tokenizer that handles quotes, operators, and whitespace
- `$VAR` environment variable expansion
- `$?` expansion to last exit status
- Single quotes `'` — prevent all metacharacter interpretation
- Double quotes `"` — allow `$` expansion only
- Unclosed quote detection with syntax error

### Redirections
| Operator | Description |
|----------|-------------|
| `<`      | Redirect input from file |
| `>`      | Redirect output to file (truncate) |
| `>>`     | Redirect output to file (append) |
| `<<`     | Heredoc — read input until delimiter |

### Pipes
- Full pipeline support: `cmd1 | cmd2 | cmd3 | ...`
- Each command's stdout is connected to the next command's stdin

### Signals
| Signal | Behavior |
|--------|----------|
| `ctrl-C` | Display new prompt on a new line |
| `ctrl-D` | Exit the shell |
| `ctrl-\` | Ignored at prompt; `Quit (core dumped)` during child process |

### Environment
- Full environment variable support via `export`, `unset`, `env`
- `SHLVL` incremented on shell startup
- `PWD` and `OLDPWD` updated on `cd`

### Memory Management
- Full cleanup of all allocated memory on exit
- `free_cmd_group`, `free_env`, `cleanup_shell` for structured deallocation
- No memory leaks in user code (readline internal leaks are exempt per subject)

---

## Built-in Commands

| Command | Description |
|---------|-------------|
| `echo [-n]` | Print arguments to stdout; `-n` suppresses newline |
| `cd [path]` | Change directory; supports `~`, `-`, and no-arg (goes to `$HOME`) |
| `pwd` | Print current working directory |
| `export [name=value]` | Set or display environment variables |
| `unset [name]` | Remove environment variables |
| `env` | Print all environment variables |
| `exit [n]` | Exit the shell with optional exit code |

---

## Mandatory Part

| Feature | Status |
|---------|--------|
| Prompt display | ✅ |
| Command history | ✅ |
| PATH-based executable search | ✅ |
| Relative and absolute paths | ✅ |
| Single global variable for signals | ✅ |
| Single quote handling | ✅ |
| Double quote handling | ✅ |
| `<` input redirect | ✅ |
| `>` output redirect | ✅ |
| `<<` heredoc | ✅ |
| `>>` append redirect | ✅ |
| Pipes `\|` | ✅ |
| `$VAR` expansion | ✅ |
| `$?` expansion | ✅ |
| `ctrl-C` / `ctrl-D` / `ctrl-\` | ✅ |
| `echo -n` | ✅ |
| `cd` | ✅ |
| `pwd` | ✅ |
| `export` | ✅ |
| `unset` | ✅ |
| `env` | ✅ |
| `exit` | ✅ |

---

## Project Structure

```
minishell/
├── Makefile
├── minishell.h
├── main.c
├── main_exit.c
├── quotes_check.c
├── tokenizer.c
├── tokenizer_utils.c
├── utils.c
├── utils2.c
├── utils_tab.c
├── cleanup.c
├── cleanup_2.c
├── debug.c
├── builtin/
│   ├── builtin_cd.c
│   ├── builtin_dispatch.c
│   ├── builtin_echo.c
│   ├── builtin_env.c
│   ├── builtin_env_utils.c
│   ├── builtin_exit.c
│   ├── builtin_export.c
│   ├── builtin_pwd.c
│   ├── builtin_unset.c
│   ├── builtin_utils.c
│   └── builtin_utils2.c
├── expander/
│   ├── expander.c
│   ├── expander_token.c
│   └── expander_var.c
├── executor/
│   ├── exec_cmd.c
│   ├── exec_cmd2.c
│   ├── exec_cmd3.c and exec_cmd4.c

│   ├── exec_cmd_utils.c
│   ├── exec_heredoc.c
│   ├── exec_heredoc2.c
│   ├── exec_iofiles.c
│   ├── exec_iofiles_check.c
│   └── exec_iofiles_utils.c
├── parser/
│   ├── parser_check.c
│   ├── parser_check2.c
│   ├── parser_check_utils.c
│   ├── parser_cmd.c
│   ├── parser_cmd_help.c
│   ├── parser_get_info.c
│   ├── parser_infiles.c
│   └── parser_outfiles.c
├── signal/
│   ├── signals.c
│   ├── signals2.c
│   └── signals_heredoc.c
└── libft/
```

---

## Norminette

All source files comply with the **42 Norminette** coding standard:
- Maximum 25 lines per function
- Maximum 5 functions per file
- Maximum 5 variable declarations per function
- No forbidden constructs (ternary operators, `for` loops, etc.)
- Proper 42 header in every file

```bash
norminette
```

---

## Authors

- **cduangpl** — 42 Bangkok
- **slimvutt** - 42 Bangkok