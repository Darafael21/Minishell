_This project has been created as part of the 42 curriculum by darafael, toandrad._

# Minishell

> As beautiful as a shell.

## Description

Minishell is a functional Unix shell written in C, built as part of the 42 curriculum. It reimplements core Bash behavior: command execution, pipelines, redirections, environment variable expansion, quoting rules, signal handling, and a complete set of built-in commands.

Internally it covers process creation (`fork`/`execve`), file descriptor management (`dup2`, `pipe`, `open`/`close`), `readline`-based history, and a hand-written tokenizer + parser that respects Bash quoting semantics.

---

## Instructions

### Requirements

| Dependency | Notes |
|---|---|
| `cc` | C compiler (gcc/clang) |
| `make` | Build system |
| `libreadline` | `libreadline-dev` on Debian/Ubuntu, `readline` via Homebrew on macOS |

### Compilation

```bash
make          # build libft then minishell
make re       # full rebuild
make clean    # remove object files
make fclean   # remove object files and binary
```

### Running

```bash
./minishell
```

The shell displays a prompt and waits for input. Use `exit` or press `ctrl-D` to quit.

To launch with a clean environment (useful for testing):

```bash
env -i ./minishell
```

---

## Features

### Command Execution

Minishell finds and runs executables using the `PATH` variable, or via relative/absolute paths.

```bash
ls -la
/bin/ls -la
./my_script.sh
```

### Pipes

The output of each command is connected to the input of the next.

```bash
ls | grep .c | wc -l
cat file.txt | sort | uniq
```

### Redirections

| Syntax | Behavior |
|---|---|
| `cmd < file` | Read stdin from file |
| `cmd > file` | Write stdout to file (truncate) |
| `cmd >> file` | Write stdout to file (append) |
| `cmd << DELIM` | Heredoc: read input until `DELIM` line is found |

```bash
cat < input.txt
echo "hello" > output.txt
echo "world" >> output.txt
cat << EOF
line one
line two
EOF
```

### Quoting

| Quote type | Behavior |
|---|---|
| `'single'` | Everything inside is treated as a literal string |
| `"double"` | All metacharacters are literal **except** `$` |

```bash
echo '$HOME'        # prints: $HOME
echo "$HOME"        # prints: /home/user
echo "hello world"  # single argument with a space
```

### Variable Expansion

```bash
echo $HOME          # expands to home directory
echo $USER
echo $?             # exit status of the last command
export MY_VAR=hello
echo $MY_VAR        # prints: hello
```

### Signals

| Signal | Behavior |
|---|---|
| `ctrl-C` | Interrupt current input — display a new prompt |
| `ctrl-D` | Send EOF — exit the shell |
| `ctrl-\` | Ignored |

---

## Built-in Commands

These commands are implemented directly inside minishell (not executed as child processes).

### `echo`

Print text to standard output.

```bash
echo hello world        # prints: hello world
echo -n no newline      # prints without trailing newline
echo "$HOME"            # prints expanded value
echo '$HOME'            # prints literal: $HOME
```

### `cd`

Change the current working directory.

```bash
cd /tmp                 # absolute path
cd ../..                # relative path
cd                      # goes to $HOME
```

### `pwd`

Print the current working directory.

```bash
pwd                     # prints: /home/user/minishell
```

### `export`

Set or declare an environment variable.

```bash
export VAR=value        # set VAR to "value"
export VAR              # mark VAR for export (if already set)
export                  # list all exported variables
```

### `unset`

Remove an environment variable.

```bash
unset VAR               # removes VAR from the environment
```

### `env`

Print all current environment variables.

```bash
env
```

### `exit`

Exit the shell with an optional status code.

```bash
exit                    # exit with last command's status
exit 0                  # exit with status 0 (success)
exit 1                  # exit with status 1 (error)
```

---

## Testing Tips

Compare behavior directly with Bash for edge cases:

```bash
# Run minishell and bash side by side
bash --norc --noprofile
./minishell

# Test with a clean environment
env -i bash --norc --noprofile
env -i ./minishell

# Quick pipe + redirect test
echo "hello" | cat > /tmp/out.txt && cat /tmp/out.txt

# Heredoc test
cat << END
first line
second line
END

# Exit status
ls /nonexistent
echo $?     # should print 2
```

---

## Resources

- [Bash Reference Manual](https://www.gnu.org/software/bash/manual/bash.html)
- [GNU Readline Library](https://tiswww.case.edu/php/chet/readline/rltop.html)
- [The Linux Programming Interface — Michael Kerrisk](https://man7.org/tlpi/)
- [Advanced Programming in the UNIX Environment — W. Richard Stevens](https://www.apuebook.com/)
- [POSIX Shell Command Language](https://pubs.opengroup.org/onlinepubs/9799919799/utilities/V3_chap02.html)
- [Linux errno Reference](https://www.chromium.org/chromium-os/developer-library/reference/linux-constants/errnos/)
- [Stack Overflow](https://stackoverflow.com/)
- All functions `man` pages

## Use of AI

GitHub Copilot (Claude Sonnet 4.6) was used during this project for the following tasks:

- Answering questions about POSIX signal handling and `sigaction` semantics.
- Clarifying edge cases in Bash quoting and variable expansion behavior.
- Improving the README structure and documentation.
- Suggesting approaches for heredoc implementation and pipe chaining.

All AI-generated content was reviewed, tested, and validated by the authors before being included in the project.
