# minishell
This is one of my favorite projects... The location for each function is given in the includes/minishel.h to find them easily if necessary.

## ***INSTALLATION***

On your shell => command => **git clone git@github.com:Jud42/minishell.git**

**Go to the minishell directory**.

For compilation => command => **make**

For the execution => command => **./minishell**

To delete everything => command => **make fclean**

## Introduction
The objective of this project is to understand how a shell works, by recreating a simple shell taking *bash* as a reference. 
### Minishell must:
* Display a **prompt** while waiting for a new command.
* Have a functional **history**.
* Find and launch the right executable (based on the ***environment variable*** **PATH**, or on a relative or absolute path).
* Do not use more than **one global variable**. Think about it because you will have to
	justify its use.
* Do not interpret quotes (quotes) not closed or special characters not
	requested in the subject, such as \ (the backslash) or ; (the semicolon).
* Handle **'** (**single quote**) which must prevent the shell from interpreting meta-characters present in the quoted sequence.
* Handle **"** (**double quote**) which must prevent the shell from interpreting meta-characters present in the quoted sequence except the **$** (**dollar sign**)
 * Implement **redirections**:
	* **<** should redirect input.
	*  **>** should redirect the output.
	* **<<** must be given a delimiter and read the given input until it encounters a line
			containing the delimiter. However, the history does not have to be updated!
	* **>>** should redirect output in append mode.
* Implement **pipes** (character **|**). The output of each command in the pipeline
	is connected to the input of the following command through a pipe.
* Manage **environment variables** (a **$** followed by a sequence of characters)
which must be replaced by their content.
* Manage **$?** which should be overridden by the exit status of the last pipeline
executed in the foreground.
* Handle **ctrl-C**, **ctrl-D** and **ctrl-\\**  which should work like in bash. (**signal**)
	* Interactive mode:
		* ***ctrl-c*** : display a new prompt on a new line
		* ***ctrl-d*** : quit the shell
		* ***strl-\\*** : do nothing
* Implementations **Builtins**
	* ***echo*** and the **-n** option
	* ***cd*** only with relative or absolute path
	* ***pwd*** without any options
	* ***export*** without any options
	* ***unset*** without any options
	* ***env*** without any options or arguments
	* ***exit*** without any options

## parsing
Before displaying the prompt, the variable environment is fetched directly with the update_env() function, starting with the 3rd argument of the main() function:
*int main(int ac, char \*\*av, ==char \*\*envp==)*
> update_env(envp, &li) //our ->env is initialized

I use the **readline()** function for display the prompt and take the input
```c
term->line = readline(BOLDGREEN"minishell$> "RESET);
```
### handle_input
**int error_exist(char \*s)**; // s (input)
Once we have our *input*, ***error_exist()*** checks if there are any syntax errors on it:
* Redirection, unclosed quotes and forbidden characters...
Return value: **1** if an error is identified, **0** if everything is correct.
### Lexical_split
**char \*lex_split(char \*s, char sep)**; // s (input), sep (space will be the separator)
This function will create an array of words by splitting the string each time it meets a space except for spaces that will be inside quotes and redirection.
==exemple==:
```shell
minishell$> echo "hello human" > outfile
```

index |**tab_word**  
---- | ---
0 | *echo* 
1 | *"hello human"*
2 | *>*
3 | *outfile*
Return value: **char \*\*tab_word**
### init_struct_shell
**init_shell(t_lst \*li, char \*tab)**; //li (pointer to structure t_lst), tab (our tab_word)
This function analyses and updates the content of the array and thus our structure **t_lst \*li** before transferring the data to a linked list.
==It has 4 sub-functions==:
#### ***check_pipe(char \*tab)***
It checks if there are **pipes** in the array. return value **number of pipes**.
#### ***check_redirection(t_lst \*li)***
It checks if there are **redirections** in the array. return value **1** if it exists, 0 otherwise.

#### ***handle_action(t_lst \*\*li)***
It analyzes and updates the content of the table.
We go through the table again:
1. *home_sign()* //checks if the first character is '**~**' and the second is '**/**' or '**NULL**' and replaces the string with the path of **home**
2. *quote_exist()* //checks if there are **quotes** or the sign '**$**' in our string;
3. *len_new_word()* // if ==quote_exist()== this functions return the number of memory to allocate for the new string;
4. *update_word()* // if ==quote_exist()==, update_word updates the concerned string;

**Illustration update_word**
```shell
minishell$>  echo "$USER" > 'out"fi"le$HOME'
```

![Alt text](https://github.com/Jud42/Mininshell/blob/master/.png/Illustration_update_word.excalidraw.png?raw=True)

#### ***create_list(t_lst \*\*li)***
##### node_structure
![Alt text](https://github.com/Jud42/Mininshell/blob/master/.png/Illustration%20_node_structure.png?raw=True)
##### **get_list()**
Once all the strings are processed we put them in a list for the next step.
**number of *nodes*** = **number of *pipe* + 1**.

==**pseudo_code**==
```c
int i = 0;
int pos = 0;
while (i++ <= (*li)->pipe)  
{  
               get_list(li, &pos);  
               pos++;  
}
```
1. ***take_argv***() //extracts the strings and initializes **->av** & **->cmd**
2. ***take_redir()*** //initializes our linked lists to redirection  & **->redir**
	**pos** = 1; //pos is set to 0 when redirection is processed at runtime.
	**sign** = *HEREDOC*(**<<**) or *REDIR_IN*(**<**) or *REDIR_OUT_S*(**>**) or *REDIR_OUT_D*(**>>**)
	**name** = \[file_name\] or \[délimitor\] to *HEREDOC*
The **other variables** in our **s_cmd** node will be set to **0** and subsequently updated.

==Implementation==
input:
```shell
minishell$> cat Makefile | grep NAME | wc -l > out_file
``` 

==after get_list==
![Alt text](https://github.com/Jud42/Mininshell/blob/master/.png/Illustration%20_after_create_list.png?raw=True)


## execution
**exec_process(t_lst \*li)**
### ==pseudo_code==:
```c
void    exec_process(t_lst *li)  
{  
       int             status;  
       int             times;  
  
       if (li->redirection)  
               if (init_redir(li->head, li))  
                       return ;  
       malloc_pid(&li);  
       if (li->pipe)  
               init_pipe(li);  
       times = -1;  
       while (++times <= li->pipe)  
       {  
               li->pid[times] = fork();  
               if (li->pid[times] == -1)  
                       exit(EXIT_FAILURE);  
               else if (li->pid[times] == 0)  
               {  
                       process_child(li, *li->head, times, li->pid);  
               }  
               delete_first(&li);  
       }  
       process_daddy(&li, li->pid);  
       free_pipe(li);  
}
```
### ***init_redirection()***
**init_redir(t_lst \*li)**//we give li->head as argument.
Inside this function that we initialize our variables **->infile**, **->outfile**
* **input redirection** //  **<**, **<<**
	We go through the list of the redirection (*t_redir*), and create a file descriptor with **open()** ( **->infile** = *open(redir->name, O_RDONLY)*) and we store it in **->infile**, this last one points to the concerned file, so if we have several **input** in the same command it will be the last one that will be stored in **->infile**.
	**heredoc** (**<<**) for herdoc we create a hidden file (**.heredoc**) with **open()** and we store in a variable **file_temp** which will point to **.heredoc** and we write on it.
	(**file_temp** = *open(".heredoc", O_CREATE | O_TRUNC | O_WRONLY, 0644)*) once the delimiter is given we exit and send the **file descriptor** to **->infile**.
	> The *heredoc* is executed in a child process to easily interrupt it in case a signal (*SIGINT*) is sent.
	
	* ==**exemple**==
		* file1 = "hello"
		* file2 = "world"
		```shell
		minishell$> cat < file1 < file2
		world
		minishell$> 
		```
	* ==exemple 2==
		```shell
		minishell$> cat <<eof <<eof1
		> I'm eof
		> eof
		> I'm eof1
		> okay?
		> eof1
		I'm eof1
		okay?
		minishell$> 
		```.
```.
```

* **output redirection** // **>** , **>>**
	Same procedure as above, but we give the file descriptor to **->outfile** and if the file doesn't exist we create it and if the file exists and if the redirection = '**>**' we overwrite the content, if the redirection = '**>>**' we add the writing to the end of the line.
	So, all files will be created if they don't exist but it will be in the last one that the writing will be done.
	For '**>**' (**->outfile** = *open(redir->name, O_TRUNC | O_CREAT | O_WRONLY, 0644)*);
	and '**>>**' (**->outfile** = *open(redir->name, O_CREAT | O_WRONLY | O_APPEND, 0644)*);
	* ==exemple==
	```shell
	minishell$> echo test > file1 >> file2 > file3
	minishell$> ls ./
	file1  file2  file3
	minishell$> cat file1
	
	minishell$> cat file2
	
	minishell$> cat file3
	test
	minishell$>
	```

### fork (childs & parents process)
To execute our commands we call **fork()**. This will ==fork== our ==main process== by creating a copy of it! Thus, the main process becomes the *father process* and the copy will be the *child process*. So that our child processes communicate, we use the **pipe()**.
1. ***fork()***
**number of child processes** = **number of pipes + 1**; 
*fork()* will have different return values depending on which process you are in:
- ***-1*** → there is an ***error*** ;
- ***0*** → we are in the ***child process*** ;
- The ***PID of the son*** → we are in the ***father*** process.
->pid** is an array of type **pid_t** to which we will store the **return value of fork()**.
**->tube_fd** is an array of **\*int** which is used to make the communication between the processes. The number of **\*int** will be equal to the number of **pipe**, each *child* will have *two* **int**(*fd*) except the ==last child== because the output will be directly in a file if there is a redirection or on the standard output ***stdout***;
=> we set **->tube_fd** with **pipe()** function
==pseudo_code==
```c
       int i = -1;  
       while (++i < li->pipe)  
       {  
               li->tube_fd[i] = malloc(sizeof(int) * 2);  
               if (!li->tube_fd[i])  
               {  
                       msg_error("error: allocation *tube_fd\n", 0, NULL);  
                       exit(EXIT_FAILURE);  
               } 
               if (pipe(li->tube_fd[i]) == -1)  
               {  
                       free_pipe(li);  
                       msg_error("Error: function pipe\n", 0, NULL);  
               }  
       }  
```

 *->tube_fd\[child_x\]* **\[0\]** and *->tube_fd\[child_x\]* **\[1\]** => **0** will be for *reading* and the **1** for *writing*.
The communication is done like this =>> the *child_1* copies its writing end (*->tube_fd\[child_1\]***\[1\]**) on the **STDOUT** with the function **dup2()** after this its standard output will be in the *tube* and the *child_2* copies the reading end of *child_1* (*->tube_fd\[child_1\]***\[0\]**) on its standard input **STDIN**, the output of *child_1* then becomes the input of *child_2*.
==exemple dup2()==
=>>   **dup2(fd3, STDIN)**  // ***STDIN = fd3***

#### ***process_child()***
```.
static int   process_child(t_lst *li, t_cmd node, int x, pid_t *pid)
```

=> if (li->pid\[x\] == 0) //we are inside process child
* Once in the *child_1* we check if the (*fd*) **->infile** exists if yes we copy it on our **STDIN** , the same thing for (*fd*) **->outfile** if it exists we copy it on **STDOUT**  
  if it does not exist and we have a **second command** (*child_2*) we send our output in the tube by copying the **write_fd_tube** of *child_1* on the **STDOUT** and the **second command** recovers it by copying the **read_fd_tube** of *child_1* on its **STDIN**.
* We check if the command is a **builtin** and if it is the case ***exec_builtin()*** is called, so if command is not a *builtin* we check and we execute with in ***ft_exec()*** if it is a **binary file**
##### ft_exec()
```.
static int      ft_exec(t_cmd *node, t_lst *li, pid_t *pid)
```

We check if a **path** is specified with the command:
```c 
if (!ft_strchr(node->cmd, '/')) 
```
* If no path is specified
	* ***help_ft_exec()*** is called:
		* ***take_tab()*** // take_tab gets the value of **PATH** among the variable environment and *concatenates the command* with it and puts them all in an array.
		* ***access(const char \*pathnam, int mode)*** //*we check if we can access *one of the *path* we just received with *take_path()*, we browse the array and we check its values with *access()* if access returns **0** the check is a **success** we quit the loop, otherwise if we reach the **end of the array** the check has **failed**. If all is good, *replace our command with its valid path.* //==example== => **cat** => **/usr/bin/cat**
		==pseudo_code==
```c
		int i = -1;
		while (tab[++i] && access(tab[i], X_OK) != 0)  
               ;  
       if (!tab[i])  
       {  
               free_tab(tab);  
               return (0);  
       }  
       *cmd = ft_strdup(tab[i]);  
       free_tab(tab);  
       return (1);
```
* ***execve()*** //this is the function that will execute our command from the child
	==prototype==
	```.
	int execve(const char *pathname, char *const argv[], char *const envp[]);
	```
	**execve**() executes the program referred to by _pathname_.  This
       causes the program that is currently being run by the calling
       process to be replaced with a new program, with newly initialized
       stack, heap, and (initialized and uninitialized) data segments.
	Now we get the variable environment in the list pointed by **->env** with the function ***env_2_str()*** which returns a type **char\**** , we put it in an array named **tab**  
	>**pathname** = ***->cmd***;  **argv** = ***->av*** ;  **envp** = ***tab***;
	
	 ==pseudo_code==
	```c
	char **tab = env_2_str(li);  
	if (execve(node->cmd, node->av, tab) == -1)  
	{  
	   if (ft_strchr(node->cmd, '/'))
		   check_error(node->cmd);  
	   free_tab(tab);  
	   return (0);  
	 }  
	 return (1);
	```

#### ***process_daddy()***
What is daddy doing in this story? :)
==prototype==
```.
static void     process_daddy(t_lst **li, pid_t *pid)
```
We send it as argument our **t_lst** structure and the **pid** of **child process** 
Basically *process_daddy* will call the ***waitpid()*** function which _suspends the execution of the calling process_ until the _child process_ specified by the __pid__ argument has _changed state_. 
* The change of state is considered as: the child has finished ; 
* So the information about the child whose state has changed will be retrieved as well:
	* the status of child.  ***waitpid(pid\[i\], &status, 0)***
	* if the child has finished successfully or with an error. ***if (WIFEXITED(status))***
	* if a stop is caused by a signal. ***if (WIFSIGNALED(status))***
**The status of process child will be stored in our global variable g_ms.exit**.

>In the case of a terminated child, executing a wait allows the system to release the resources associated with the child; if a wait is not executed, then the terminated child remains in a "*zombie*" state.

##### ==pseudo_code==
```c
static void     process_daddy(t_lst **li, pid_t *pid)  
{  
       int     status;  
       int     i;  
  
       i = -1;  
       close_fd(NULL, li);  
       while (++i <= (*li)->pipe)  
       {  
               g_ms.pid_sig = pid[i];  
               init_signals();  
               waitpid(pid[i], &status, 0);  
               if (WIFSIGNALED(status))  
               {  
                       if (WTERMSIG(status) == SIGQUIT)  
                               write(1, "Quit: 3\n", 8);  
                       else if (WTERMSIG(status) == SIGINT)  
                               write(1, "\n", 1);  
                       g_ms.exit = 128 + status;  
               }  
               if (WIFEXITED(status))  
                       g_ms.exit = WEXITSTATUS(status);  
               g_ms.pid_sig = 0;  
       }  
}
```
#### illustration
```shell
minishell$> cat << eof > file_test
> Hello
> word!
> eof
minishell$> cat file_test | grep Hello | wc -l > outfile
1
minishell$>
```

![](https://github.com/Jud42/Mininshell/blob/master/.png/illustration_pipe_execution.png?raw=True)
## signal & EOF
### signal
==We manage only two signals:==
**ctrl-c** = **SIGINT**
**ctrl-\\** = **SIGQUIT**
We have 2 signal management, everything depends on where you are during the execution of the program.
1. ***Processus principal*** (**init_signal()**)
	In main process if a *process child* is running it ignores the **SIGINT**, otherwise **sig_handler** is called, it will redisplay the prompt on a new line.
	The **SIGQUIT** is ignored in all cases in this process.
2. ***Process child*** (**init_child_signal()**)
	In process child if we execute a *heredoc* the **SIGQUIT** is ignored, otherwise **SIGQUIT** will be set to its default behavior.
	The **SIGINT** will be set to its default behavior in all cases.
#### ==pseudo_code==
```c
void    init_child_signal(int flag)  
{  
       signal(SIGINT, SIG_DFL);  
       if (flag == HEREDOC)  
               signal(SIGQUIT, SIG_IGN);  
       else  
               signal(SIGQUIT, SIG_DFL);  
}  
  
void    sig_handler(int sig)  
{  
       write(1, "\n", 1);  
       rl_replace_line("", 0);  
       rl_on_new_line();  
       rl_redisplay();  
       g_ms.exit = 1;  
}  
  
void    init_signal(void)  
{  
       if (g_ms.pid_child)  
               signal(SIGINT, SIG_IGN);  
       else  
               signal(SIGINT, &sig_handler);  
       signal(SIGQUIT, SIG_IGN);  
}
```
### EOF (ctrl-d)
For the **ctrl-d** it will be on the return of **readline()**, if the return is '\0' we quit the process.
