<h1 align=center>
 42_MINISHELL 🤖
</h1>

<div align=center>
  As beautiful as Shell.
</div>

# About ✍
The Minishell project is essentially about creating a simple shell—yes, our own little bash—which my peer [Vinícius Vaccari](https://github.com/vivaccar) and I affectionately nicknamed GAUSHELL. Our program replicates the shell environment, prompting a command-line, executing commands with pipes and redirects, manipulating environment variables, handling signals, and supporting various other shell features.

#  Walkthrough 🧩
The project was divided in three big parts: Tokenizer, Parser and Execution.

### Tokenizer
The first thing a shell does when it receives a command-line is to divide the string into `tokens`, which, as we decided, are categorized into twelve different types: `WHITE SPACE`, `WORD` (later considered as a command), `PIPE`, `ENV` (dollar sign), `REDIRECT_IN`, `REDIRECT_OUT`, `DOUBLE REDIRECT_OUT`, `HEREDOC`, ``SINGLE QUOTE``, ``DOUBLE QUOTE``, `FILE`, and `NULL`.

We also check the status of each token, defined by three types: `GENERAL` (no quotes), `IN_SINGLE_QUOTE`, or `IN_DOUBLE_QUOTE`.

To better understand, let's demonstrate what the tokenizer does with the following command-line example:

<img src="https://github.com/marcelofassbinder/42_MINISHELL/blob/main/tokenizer2.png"/>

Before advancing to the Parser, we go through another crucial part of this project: the EXPANSION of environment variables. In this step, we replace the `ENV` token and its subsequent value with the corresponding value stored in the environment variables. If the token doesn't match any environment variable, it becomes NULL. Additionally, we handle certain edge cases exactly as Bash does. Here are some examples with the `echo` command that illustrate some different expansions:

<img src="https://github.com/marcelofassbinder/42_MINISHELL/blob/main/expand.png"/>



