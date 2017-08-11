# Basic Usage

## Executing Revkit
Revkit is a command line based program, so it does not have a graphical user interface. When Revkit is executed from a terminal, a shell prompt is printed to the screen with the text `revkit>` that replace the current directory normally displayed by a terminal. 

To get a list of all the commands and a short description of their usage, one must call the `help` command. To view more information of each command, run the command with the `--help` flag. In general, there are three ways to run a program in Revkit:


1. Interactive mode: the default command line shell that it is described above. Every command must be written by the user. It is accessed by simply executing Revkit with its alias: 

```
~$ revkit
revkit>  read_aiger file.aig
revkit>  cone -o y
revkit>  simulate -ad
revkit>  quit
~$
```

2. Bash mode: mode where a list of commands  are given to Revkit as command line arguments.To run this method, one must execute Revkit with a `-c` flag:
```
~$ revkit -c "read_aiger file.aig; cone -o y; simulate -at; quit"
```

If you want that every command executed is printed on the screen, add the `-e` flag

3. Batch mode: mode where the list of commands executed are read line by line from a text file. To run this method, one must use call revkit with a `-f` flag followed by the name of the file with the commands:
```
~$ revkit -f commands.txt
```

As in bash mode, if you want to print every command used, you can add the `-e` flag.


It must be noticed that any line beginning with the "#" character will not be read by Revkit. This is particularly useful for making comments for scripts that will run in Batch mode.


## Creating logs
Passing `-l file.log` to Revkit creates a log file of the session. This option is particularly useful in batch mode. The log file contains a JSON array with an entry for each command. Each entry contains at least the full command that was run and the time at which the command was started to execute. Some commands write additional data into the log file. 

For example, `ps -a` writes number of inputs, outputs, and AND gates of an AIG, and `quit` writes several information about the computer on which Revkit has been executed. Being a JSON array, the log file can be easily parsed as many programming languages have a JSON library.
\\
\\
Some helper functions to parse the log file and, e.g., create ASCII tables from them can be found in `utils/experiments.py`. Further, the Python program `utils/extract\_script.py` extracts a CirKit script file from the the log that can be run in batch mode. This can be helpful when logging an interactive session and then rerunning the commands:
```
~/cirkit$ revkit -l session.log
revkit>  read_aiger file.aig
revkit>  ps -a
...
revkit>  quit
cirkit$ utils/extract_script.py session.log > session.cs
cirkit$ revkit -f session.cs
```

For performing experimental evaluations, the following workflow is suggested. Create two Python programs (or any other programming language) called `make_script.py` and `make_table.py`. The program `make_script.py` writes a CirKit script. The program `make_table.py` reads the log file created for the script and prints out a table:
```
~/cirkit$ ./make_script.cs experiments.cs
~/cirkit$ revkit -f experiments.cs -l experiments.log
~/cirkit$ ./make_table.cs experiments.log
```

## Aliases
In a traditional programming language, an alias is a function that uses as a basis internal functions of the program to compute a not defined task. In a similar fashion, Revkit allows the definition of aliases: a group of commands and procedures grouped under a single key. An alias is created with the `alias` command of Revkit. To define an alias we need a key, a string with no spaces, and the list of commands executed by that key. For example:

```
revkit> alias simul "convert --circuit_to_spec ; print -s"
```

Note that the command list has to be put into quotes if they contain any space. To add more flexibillity and options to the alias, one can use [regular expressions](https://docs.microsoft.com/en-us/dotnet/standard/base-types/regular-expression-language-quick-reference):

```
alias "(\\w+) > (\\w+) > (\\w+)" "convert --%1%_to_%2%; convert --%2%_to_%3%"
```

The `alias` command only creates aliases for the current session of Revkit. To add an alias that will we global for all of Revkit's session, add the wished `alias` command to a new line of the `alias` text file located in cirkit's main repository.

## Data Structures
Revkit can manipulate and analize a good number of data structures that represent either a boolean function or a reversible circuit. The following table lists the data structures included in Revkit. 

|Data structure | Access options|
| :-------------: | ------------- |
|Expression | `-e`,`--expr` |
|And-inverter graph | `-a`,`--aig` |
|XOR majority graph | `-x`,`--xmg` |
|Binary decision diagram | `-b`,`--bdd` |
|Reversible circuit | `-c`,`--circuit` |
|Reversible specification | `-s`,`--spec` |
|BDD of a characteristic reversible function (RCBDD)  |`-r`,`--rcbdd` |

## Input and Output
In general, in order to create an instance of a data structure in Revkit we need to import the data structure from a file format that describes the data structure. The expressions are the only structure that can be created inside of Revkit by using the `expr` command. 

The data structures can also be exported to this same file format. The following table lists all of the data structures input and output commands used in Revkit along with a short decription.

| Data structure | Format | Input function | Output function | Notes |
| -------------- | ------ | -------------- | --------------- | ----- |
|Reversible circuits | REAL | `read_real` | `write_real` | Reversible circuit representation using different gates as basis. Part of [Revlib](http://www.revlib.org/) supported [formats](http://www.informatik.uni-bremen.de/rev_lib/doc/docu/revlib_2_0_1.pdf). |
|Reversible specification | SPEC | `read_spec` | `write_spec` | Truth table of a reversible circuit. [Revlib](http://www.revlib.org/) supported [formats](http://www.informatik.uni-bremen.de/rev_lib/doc/docu/revlib_2_0_1.pdf). |
|Binary decision diagram | PLA | `read_pla` | `write_pla` | Sum of products representation of a Boolean function. [Revlib](http://www.revlib.org/) supported [formats](http://www.informatik.uni-bremen.de/rev_lib/doc/docu/revlib_2_0_1.pdf). |
|XOR majority graph | Verilog | `read_verilog -x` | `write_verilog -x` | [Verilog](http://ieeexplore.ieee.org/document/1620780/) standard format for a XOR majority graph representation. |
|And-inverter graph | Verilog | `read_verilog -a` | `write_verilog -a` | [Verilog](http://ieeexplore.ieee.org/document/1620780/) standard format for a And-inverter graph representation. |
|And-inverter graph | AIGER  | `read_aiger` | `write_aiger` | Format developed for the [AIGER utlity set](http://fmv.jku.at/aiger/). |
|And-inverter graph | BENCH | `read_bench` | - | Format developed for traditional circuits as part of the Berkeley's [ABC system](https://people.eecs.berkeley.edu/~alanmi/abc/abc.htm). |


The "-" sign indicates that no command exists.`

The precise details of the usage of the input and output functions and memory allocation of Revkit will be addressed in the next section.

Revkit also includes some commands to output a reversible circuit data structure to formats of certain quantum computing softwares. The following table lists this commands along with its compatible software and some notes.

| Output command | Software | Notes |
| -------------- | -------- | ------ |
| `write_liquid` | [LIQUi\|> (Liquid)](https://www.microsoft.com/en-us/research/project/language-integrated-quantum-operations-liqui/) | Software architecture and toolsuite for quantum computing developed by Microsoft Research.|
| `write_projectq` | [ProjectQ](https://projectq.ch/) |  Open source software framework for quantum computing started at Swiss Federal Institute of Technology in Zurich |
| `write_quipper` | [Quipper Language](http://www.mathstat.dal.ca/~selinger/quipper/) | Embedded, scalable functional programming language for quantum computing.|
| `write_qpic` | [Qpic](https://github.com/qpic/qpic) | Python based tool for drawing quantum circuits via Latex. |
| `write_numpy` | Numpy package for Python | Simulation of a reversible circuit built using Numpy library in Python.|
| `write_tikz` | Tikz package of Latex | Latex package for making diagrams and drawings. |


## Memory Stores

Every time we create an instance of a data structure in Revkit, this structure is saved in a stored in a fixed memory location called *Store*. A store can be thought of as an unfixed vector of elements of a given data structure. Each data structure has its own store. 

The `store` command is used to access and make changes over the stores of Revkit. All stores can hold more than one instance of its data structure. As most commands in Revkit take as an input a data structure, the input is not normally specified: each store has a pointer that each commands takes as an input when it reaches for that data structure as an input. This pointer can be set with the `current` command .

To see a list all the elements in the store of a given data structure, execute the command `store --show` followed by the access option of the data structure. For example:
```
revkit>  store --show -c
[i] circuits in store:
     0: 7 lines, 55 gates
     1: 5 lines, 2 gates
  *  2: 4 lines, 3 gates
```
The `*` symbol shows which element to which element of the store is the pointer set. To change the element to which the pointer points, we use the `current` command. This command takes as an argument the access option of the data structure store you wish to access and the number of the element in the store to which you want to set the pointer to point. 
```
revkit>  store --show -c
revkit>  store --show -c
[i] circuits in store:
     0: 7 lines, 55 gates
     1: 5 lines, 2 gates
  *  2: 4 lines, 3 gates
revkit>  current -c 1
revkit>  store --show -c
[i] circuits in store:
     0: 7 lines, 55 gates
  *  1: 5 lines, 2 gates
     2: 4 lines, 3 gates
```
As we mentioned before, every command that takes a data structure as input and/or a data structure as output will read or overwrite the current element in the pointer of its store. For the input of most commands, this behaviour can not be modified. Most of the commands that output a data structure have an option with flag `-n, --new` that specifies that the output data structure is stored in a new element of the store. 

This is particularly useful for the `read_*` commands. For example. if we have a circuit in store and call the `read_real` function on a file, the new circuit will be written in the pointer. But if we call the command with the flag `read\_real -n`, it will be saved in a new element of the store.
```
revkit>  read_real template1.real
revkit>  read_real template2.real
revkit>  store --show -c
[i] circuits in store:
  *  0: 3 lines, 2 gates
revkit>  read_real template1.real
revkit>  read_real -n template2.real
revkit>  store --show -c
[i] circuits in store:
     0: 3 lines, 2 gates
  *  1: 3 lines, 2 gates
```
To delete all the items in a store, call the `store` command with the `--clear` flag followed by the access option of the data structure:

```
revkit>  store --show -c
[i] circuits in store:
     0: 3 lines, 2 gates
  *  1: 3 lines, 2 gates
revkit>  store --clear -c
revkit>  store --show -c
[i] no circuits in store
```

Most of Revkit commands are sufficiently specific function or name, like the synthesis commands, to need specification over which data structure are operating. However, there are a series of generic commands that can operate on every data structure so we must specify the access option of the store of the data structure over which we want the command to act. The following table lists this commands.


|Command | Description |
| ------ | ----------- |
|`current` |	Changes the current store pointer |
|`print` |	Prints a textual ASCII representation of the current store element |
|`ps` |	Prints statistical information about the current store element |
|`show` |	Visualizes the current store element (writes to a dot file) |
|`store` |	Shows and clears elements from the store |



##  Making diagrams of circuits
Revkit can also be used for creating diagrams of reversible circuits. The diagrams are created using Latex, in particular, the `TikZ` and `preview` packages. It is recommended to make a complete Tex installation on the computer via [TexLive](https://www.tug.org/texlive/) or [MacTex](http://www.tug.org/mactex/). A full installation of Tex is available for all users in the ULeth Linux system.

There are two principal ways in wich we can convert a circuit stored in Revkit to a diagram.
### PNG via Qpic and Latex
To create a PNG image of our circuit we have to use a auxiliary program called [Qpic](https://github.com/qpic/qpic). This is a Python-based program used to draw quantum circuits. Installation instructions are available inside its Github repository. After installing Qpic and supposing that we have a`.real` file describing a circuit called `circuit.real`, we can convert it to PNG using the following command:
```
$ revkit -c "read_real circuit.real; write_qpic circuit.qpic"
$ qpic circuit.qpic -f png -o circuit.png
```
The first command uses revkit to read the circuit and to output a .qpic file called `circuit.qpic`. The second command calls qpic to convert the `circuit.qpic` file into `circuit.png`. The output file is specified with the `-o` arrgument as the output format is specified by the `-f` argument. Other outputs format include .tex,.pdf and .tikz.

### PDF via Latex
To create the drawing directly with Revkit to a .pdf file, we should use the following commands:
```
$ revkit -c "read_real circuit.real; write_tikz --standalone circuit.tex"
$ pdflatex circuit.tex
```
The first command uses revkit to read the circuit and to ouput a .tex file called `circuit.tex` that is compiled by the second command to a .pdf file called `circuit.pdf` that contains the drawing of the circuit. the `--standalone` indicates that the file created is going to be compiled alone and not as part of a larger Latex project.