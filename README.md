<h1 align=center>
 42_MINISHELL 🤖
</h1>

<div align=center>
  As beautiful as Shell.
</div>

# About ✍
Being part of the Rank 03 of the 42 Common Core curriculum, the Minishell project is essentially about creating a simple shell—yes, our own little bash—which my peer [Vinícius Vaccari](https://github.com/vivaccar) and I affectionately nicknamed GAUSHELL. Our program replicates the shell environment, prompting a command-line, executing commands with pipes and redirects, manipulating environment variables, handling signals, and supporting various other shell features.

#  Walkthrough 🧩
The project was divided in three big parts: Tokenizer, Parser and Execution.

## Tokenizer
The first thing a shell does when it receives a command-line is to divide the string into `tokens`, which, as we decided, are categorized into twelve different types: `WHITE SPACE`, `WORD` (later considered as a command), `PIPE`, `ENV` (dollar sign), `REDIRECT_IN`, `REDIRECT_OUT`, `DOUBLE REDIRECT_OUT`, `HEREDOC`, ``SINGLE QUOTE``, ``DOUBLE QUOTE``, `FILE`, and `NULL`.

We also check the status of each token, defined by three types: `GENERAL` (no quotes), `IN_SINGLE_QUOTE`, or `IN_DOUBLE_QUOTE`.

To better understand, let's demonstrate what the tokenizer does with the following command-line example:

<div align="center">
 <img src="https://github.com/marcelofassbinder/42_MINISHELL/blob/main/tokenizer2.png"/>
</div>

### Expansion
Before advancing to the Parser, we go through another crucial part of this project: the EXPANSION of environment variables. In this step, we replace the `ENV` token and its subsequent value with the corresponding value stored in the environment variables. If the token doesn't match any environment variable, it becomes NULL. Additionally, we handle certain edge cases exactly as Bash does. 

Here are some examples with the `echo` command that illustrate some different expansions:

 <img src="https://github.com/marcelofassbinder/42_MINISHELL/blob/main/expand.png" width=70%/>


`$` - Does not expand;

`$abc` and `$JFHDSKF` - Expand to NULL;

`$USER` - Expands to the current USER;

`$PWD` - Expands to the current working directory;

`$$` - Expands to the PID (Process ID);

`$0` - Expands to the bash name;

`$?` - Expands to the exit status of the last command executed.

## Parser
After tokenizing the input, it's time for the parser to do its job, which involves preparing the program for execution by arranging the commands in the correct "order" to be executed. To achieve this, we chose to use a binary tree data structure, creating three distinct types of nodes: `EXEC`, `REDIR` and `PIPE`

`EXEC` - Contains the exec type, the command and its arguments, and a boolean indicating if the command is builtin or not.

`REDIR` - Contains the redir type, the file name it redirects for, a void pointer to the next node in the tree, and in case of type heredoc, the id and the status of the limiter string.

`PIPE` - Contains the pipe type and two void pointers, one for the right and other for the left side of the pipe.

To build the tree, we implemented the recursive descent parsing, inspired by the MIT's xv6 kernel project, which concept was totally explained in this [video](https://www.youtube.com/watch?v=ZjzMdsTWF0U&t=1155s). 

Following the grammar rules using the previous example, we would build our tree as the illustration above: 

<div align="center">
 <img align=center src=https://github.com/marcelofassbinder/42_MINISHELL/blob/main/PIPE(1).png width=40% height=40%\>
</div>

## Execution
Now, after building our tree, running our commands becomes much easier. We simply call our `run` function, a recursive function that takes the tree's root as input and executes the nodes according to the tree's structure.

When it finds a `PIPE` node the function creates a pipe and two child processes, one for the left and other for the right side of the pipe. 

In the first fork, the "pipe's write file descriptor" `(fd[1])` is redirected to the process's Standard Output using the `dup2` function. The `run` function is then called recursively, with the node's left pointer passed as a parameter.

In the second fork, the "pipe's read file descriptor" `fd[0]` is redirected to the process's Standard Input. The `run` function is called again, this time with the node's right pointer as the parameter.

By doing this, we enable the process on the left side to communicate with the process on the right side, sending its output through the pipe so that the right side reads it as the input for its process, replicating what a pipe do in the shell. If you want to know more about pipes, dup2, forks and execve, I invite you to check the project [42_PIPEX](https://github.com/marcelofassbinder), that is also part of the 42 Common Core curriculum.

When a `REDIR` node is found, the function identifies its type, opens the corresponding file, and uses `dup2` to redirect the process's input or output accordingly.

Finally, when an `EXEC` node is encountered, the function checks whether the command is a builtin. If it is, the corresponding builtin function is called, and the process is terminated. If not, `execve` is called with the command's arguments, the executable's path, and the environment variables. If execve succeeds, it takes over the process, terminating it automatically.

 > If the command-line has no pipes, and the `EXEC` command is a builtin, it will be executed in the parent process, and will not terminate the process after the execution, otherwise it would exit the whole minishell program.

### Builtins
No, we did not create all the shell commands from scratch; in fact, we only implemented seven of them, as required by the subject. These commands are `echo`, `cd`, `export`, `unset`, `pwd`, `exit` and `env`.  All other commands are handled by the `execve` function, so we don't need to worry about them, as their executables already exist in one of the directories listed in the `PATH` environment variable.

 # Usage 🖥️
To install and test Minishell, follow these steps:
- Clone the repository:
```bash
git clone git@github.com:marcelofassbinder/42_MINISHELL.git
```
- Navigate to the project directory and run ``make`` to compile the program:
```bash
cd 42_MINISHELL
make
```
- Run `./minishell`
- Once you are inside minishell, you can use it as it was a normal bash. Enjoy! :D
- Feel free to make the tests you want, here are a [list](https://github.com/marcelofassbinder/42_MINISHELL/blob/main/GAUSHELL.pdf) of some hard edge cases we handle in our minishell.  

# Grade  <p><img height="30px" src="https://img.shields.io/badge/-101%20%2F%20100-success" /></p>

# Norminette 💂🏻
At 42 School, we need to follow some strict rules when writing our code. These rules are described in the Norm and checked by the formidable `norminette`. Here are some of them:
```
- No for, do...while, switch, case, goto, ternary operators and variable-length arrays are allowed
- Each function must be maximum 25 lines
- One single variable declaration per line
- You can’t declare more than 5 variables per function
- You can't write more than 5 functions per file
...
```
[Click here](https://github.com/42School/norminette/blob/master/pdf/en.norm.pdf) to review the complete Norm document.
