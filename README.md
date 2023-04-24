<div align="center"> 
 <h1>PIPEX</h1>
  
  <p>
    Handling multiple system commands through C.
  </p>
</div>
  

# About the Project

A project made in accordance with the pipex project which is part of the Codam Core Curriculum. It recreates the functionality of the pipe (|) symbol, which allows you to send the output of one command to another command as input for further processing. I passed this project with 125%. It handles multiple commands from the commandline, processes them through pipes and puts the output into a designated output file. As a bonus I recreated the heredoc functionality.

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
./pipex [infile] command1 command2 [outfile]
```
For example:
```c
./pipex inputfile "grep a" "wc -l" "column -t" outputfile
```
should recreate the behaviour of:
```c
< inputfile grep a | wc -l | column -t > outputfile
```
< file1 cmd1 | cmd2 > file2

You can add more commands if you'd like.
My pipex also supports heredoc. Use as follows:
```c
./pipex here_doc [LIMITER] command1 command2 [outfile.txt]
```
For example:
```c
./pipex here_doc EOF "grep a" "wc -l" "column -t" outputfile
```
should recreate the behaviour of:
```c
grep a << EOF | wc -l | column -t >> outputfile
```

# Contact

See my profile page for ways to contact me!
