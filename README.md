  <h1>PIPEX</h1>
  
  <p>
    Handling multiple system commands through C.
  </p>
</div>
  

## :star2: About the Project

A project made in accordance with the Pipex project for the Codam Core Curriculum.
Teaches how to use piping, create forks and change the STDIN and STDOUT through dup2.




# Features

Handles multiple commands from the commandline, processes them through pipes and outputs it into a designated output file.




# Getting Started

Start by cloning the repository:
```c
git clone https://github.com/fkoolhoven/pipex.git
```

Compile by using make:
```c
make
```

# Usage

```c
./pipex [infile.txt] command1 command2 [outfile.txt]
```
For example:
```c
./pipex infile "grep a" "wc -l" "column -t" outfile
```
You can add more commands if you'd like.
My pipex also supports heredoc. Use as follows:
```c
./pipex here_doc [LIMITER] command1 commdand1 [outfile.txt]
```
For example:
```c
./pipex here_doc EOF "grep a" "wc -l" "column -t" outfile
```


# Contact

See my profile page for ways to contact me!

