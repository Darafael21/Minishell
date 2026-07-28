# Minishell — Evaluation Test Commands

---

## Compilation

```bash
make -n          # verify -Wall -Wextra -Werror are used
make             # must compile with no errors
make             # second run must not relink (no output)
```

---

## Simple Command & Global Variables

```bash
/bin/ls
/bin/ls -la
/usr/bin/wc --help
                 # empty command — just press Enter
   		         # spaces/tabs only — press Enter
```

---

## Arguments

```bash
/bin/ls -la /tmp
/usr/bin/echo hello world
/usr/bin/cat /etc/hostname
/bin/ls -la /nonexistent
```

---

## echo

```bash
echo hello
echo hello world
echo -n hello
echo -n
echo -nnn test
echo
```

---

## exit

```bash
exit
# relaunch, then:
exit 0
# relaunch, then:
exit 42
# relaunch, then:
exit 9223372036854775808
# relaunch, then:
exit abc
# relaunch, then:
exit 42 extra
```

---

## Return Value of a Process

```bash
/bin/ls
echo $?
/bin/ls /nonexistent_file
echo $?
/usr/bin/cat /etc/hostname
echo $?
expr $? + $?
echo $?
/nonexistent_command
echo $?
```

---

## Signals

```bash
# At empty prompt:
# ctrl-C  → new prompt on new line
# ctrl-\  → nothing happens
# ctrl-D  → exits shell (relaunch after)

# After typing some text (e.g. "hello"):
# ctrl-C  → clears line, new prompt, buffer clean (Enter executes nothing)
# ctrl-D  → does nothing
# ctrl-\  → does nothing

# With blocking commands:
cat
# ctrl-C  → kills cat, returns to prompt ($?=130)
cat
# ctrl-\  → kills cat, prints "Quit" ($?=131)
cat
# ctrl-D  → sends EOF, cat exits cleanly

grep something
# ctrl-C  → $?=130
grep something
# ctrl-\  → $?=131
```

---

## Double Quotes

```bash
echo "hello world"
echo "cat lol.c | cat > lol.c"
echo "spaces   and	tabs"
echo "$HOME is my home"
echo "user: $USER"
echo "exit code: $?"
echo "  leading and trailing  "
```

---

## Single Quotes

```bash
echo 'hello world'
echo ''
echo '$USER'
echo '$HOME | echo hack'
echo 'no > redirection'
echo 'no | pipe'
echo '  spaces  '
```

---

## env

```bash
env
```

---

## export

```bash
export TEST=hello
env | grep TEST
export TEST="new value"
env | grep TEST
export NEWVAR=42
env | grep NEWVAR
export
```

---

## unset

```bash
export TESTVAR=hello
env | grep TESTVAR
unset TESTVAR
env | grep TESTVAR
echo $TESTVAR
```

---

## cd

```bash
cd /
/bin/ls
cd /tmp
/bin/ls
cd ..
pwd
cd .
pwd
cd ../..
pwd
cd /nonexistent_dir
echo $?
```

---

## pwd

```bash
pwd
cd /tmp
pwd
cd /
pwd
cd /usr/local
pwd
```

---

## Relative Path

```bash
cd /usr
bin/ls
bin/wc --help
cd /
usr/bin/echo hello
cd /usr/local
../../bin/ls
```

---

## Environment Path

```bash
ls
wc --help
echo test
cat /etc/hostname
unset PATH
ls
echo $?
export PATH=/bin:/usr/bin
ls
echo test
```

---

## Redirection

```bash
echo hello > file1
cat file1
echo world >> file1
cat file1
cat < file1
cat < file1 > file2
cat file2
echo test > file1 > file2
cat file1
cat file2
cat < file1 >> file2
cat file2

# heredoc
cat << EOF
hello
world
EOF

cat << EOF
$USER is here
EOF

cat << 'EOF'
$USER should not expand
EOF
```

---

## Pipes

```bash
cat file1 | grep hello
ls | wc -l
cat file1 | grep hello | wc -l
ls /nonexistent | grep bla | wc -l
echo hello | cat > file3
cat file3
cat file1 | cat | ls
```

---

## Go Crazy & History

```bash
# Type "hello world", press ctrl-C, press Enter → nothing executes

# Use Up/Down arrow keys to navigate history and re-run commands

dsbksdgbksdghsd
echo $?

cat | cat | ls

echo one two three four five six seven eight nine ten eleven twelve
```

---

## Environment Variables

```bash
echo $HOME
echo $USER
echo $PATH
echo $?
echo "$USER"
echo "$HOME is home"
export MYVAR=test
echo $MYVAR
echo "$MYVAR"
echo '$MYVAR'
```

---

## Wildcard *(bonus)*

```bash
echo *
ls *.c
ls *.md
echo src/*.c
```

---

## Surprise

```bash
export USER=yourname    # only if USER is not already set
echo "'$USER'"          # should print: 'yourname'
echo '"$USER"'          # should print: "$USER"
```
