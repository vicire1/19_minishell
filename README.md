# Minishell

<img width="630" alt="Minishell" src="https://github.com/user-attachments/assets/100b110b-5854-46c3-9fe2-4f87a5bcc661">

## Description

The **Minishell** project involves creating a simple shell that mimics the functionality of a basic Unix shell. Through this project, you will gain a deep understanding of processes, file descriptors, and various system calls in C.

## Project Objectives

- Develop a custom shell that can execute commands, manage file descriptors, and handle process creation.
- Implement features such as redirections, pipes, and environment variable handling.
- Gain hands-on experience with Unix system programming concepts like signals and job control.

## Content

- **Mandatory Part:**
  - Implement a shell with the following features:
    - Display a prompt when waiting for a command.
    - Maintain a working history of commands.
    - Locate and launch executables based on the `PATH` environment variable or via relative/absolute paths.
    - Handle unquoted and quoted sequences of characters, ensuring proper interpretation of metacharacters.
    - Implement redirections:
      - `<` for input redirection.
      - `>` for output redirection.
      - `<<` to read input until a specified delimiter is encountered.
      - `>>` for output redirection in append mode.
    - Implement pipes (`|`), connecting the output of one command to the input of the next.
    - Handle environment variables, expanding them to their values.
    - Implement built-in commands such as `echo`, `cd`, `pwd`, `export`, `unset`, `env`, and `exit`.
    - Manage special keyboard inputs like `ctrl-C`, `ctrl-D`, and `ctrl-\` in interactive mode.

  - **Constraints:**
    - Use only one global variable.
    - Ensure that your shell does not interpret unclosed quotes or special characters not required by the subject.

## Compilation

To compile the project, ensure that your Makefile includes the following rules: `all`, `clean`, `fclean` and `re`.

1. **Compile the program:**

   ```bash
   make
   ```

   This will create the `minishell` executable.

2. **Clean object files:**

   ```bash
   make clean
   ```

3. **Remove all generated files, including the executable:**

   ```bash
   make fclean
   ```

4. **Recompile everything from scratch:**

   ```bash
   make re
   ```

## Usage

To use the `minishell`, run the compiled executable:

```bash
./minishell
```

You can then enter commands at the prompt just like in a regular shell:

```bash
$ ls -l
$ echo `Hello, Minishell!`
$ pwd
```

You can also use features such as pipes, redirections, and environment variables:

```bash
$ echo `This is a test` > output.txt
$ cat output.txt | grep `test`
```

To exit the shell, use the `exit` command or press `ctrl-D`.
