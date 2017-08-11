# Development tools
This page presents a list of the development related commands of Revkit and their description
## Mapping and rewriting

Revkit provides us with a set of commands that can modify our reversible circuit in ways that can be helpful to us. Rewriting usually refers to changing the basis of a circuit while mapping refers to changing some elements in a reversible circuit for other. As mentioned before, each of these commands act on the circuit to which the circuit store pointer points to and overwrite this store with the output. In order to add it to the store, you must run the command with the `-n` flag.

The following table lists the commands and a basic description of its functions:

| Command | description |
| ------- | ----------- |
| `concat` | concatenates two circuits in store that are given as arguments with flags `--id1` and `--id2` respectively. For example, let circuit in store `0` be $G_1 \dots G_k$ and circuit in store `1` be $H_1 \dots H_l$. Executing `concat --id1 0 --id2 1` overwrites the current pointer of the store with the circuit $G_1 \dots G_k H_1 \dots H_l$. |
| `filter` | Removes all gates from a circuit. This command is used to filter out non desired gates. It has a series of flags that indicate what gates to keep:  |
| | `-tof` keep Toffoli gates |
| | `-stg` keep single-target gates |
| | `-inv` invert filter |
| `maslov234` | Maslov's reversible phase gate mapping. For more intormation, consult <sup>[1](#myfootnote1)</sup> |
| `mitm` | simple meet-in-the-middle mapping. For more information about the algorithm,  consult <sup>[2](#myfootnote2)</sup>|
| `nct` | change each gate to its equivalent using the NOT, CNOT and Toffoli gates (NCT)|
| `pos` | replace negative controls with equivalent positive controls and NOT gates|
| `reverse` | reverse  a circuit. If a circuit is defined by gates $G_1 G_2 \dots G_k$, this command outputs the circuit deffined by $G_k G_{k-1` ... G_1$ |
| `tof` | rewrite Fredkin gates to Toffoli gates |
|`unique_names` | changes the variable names of inputs, outputs. garbage and constants of the circuit as specified by it REAL file so that all the names are unique. |



## Simulation and verification
Revkit allows us to simulate a reversible circuit, that is, to verify and test its output for a certain input. We will discuss the commands that allow us to do that and how to use them. 

Before continuing, it must be noticed that most Revkit's commands for simulation and verification, including the `convert` command, which will be discussed in the following, throw errors when are called upon a circuit that has negative controls. It also can throw errors when the circuits are not based on Tofolli gates. For this reason, we strongly recommend to call the `pos` and `nct` commands on every circuit each time one wants to simulate a circuit.

The following table lists all the simulation commands of Revkit, along with a short description.


|command | description |
| ------ | ----------- |
|`is_identity` | Checks if circuit in store computes the identity function. |
|`rec` | Equivalence checking for two circuits on store. The location in store of the circuits is given as arguments with flags `--id1` and `--id2` respectively. |
|`revsim` | Simulate the output of $n$-bits for an $n-$line circuit in store. The input bit pattern must be specified by flag `-p. --pattern` followed by an $n$-bit string. |



If, instead of simulating one input pattern using the `revsim` command, one wants to obtain the full truth table the reversible circuit, the `convert` command must be used. This command is discussed in the following section. 

There are also a series of commands related to the optimization of reversible circuits implemented in Revkit. In a similar fashion of the simulation commands, each of these commands act over the circuit in the store to which the store pointer points to. The following table lists all the optimization commands in Revkit along with a short description.

| Command | Description |
| ------- | ----------- |
|`adding_lines` | optimization method that tries to reduce the quantum cost of a circuit by adding garbage lines to it. For a more detailed description of the method, consult <sup>[3](#myfootnote3) </sup> |
|`esop` | outputs a PLA file, an exclusive sum of products representation, from an and-inverter graph in store. The file name of the output must be specified in the command with the `--filename` flag. It optimizes the output using an EXORCISM algorithm. For a larger explanation of these minimization algorithms, please consult <sup>[4](#myfootnote4) </sup>.|
|`reduce_lines` | optimization method that tries to reduce the number of lines in a circuit by merging garbage and constant lines, or garbage and garbage lines. For a more detailed description of the method, consult <sup>[5](#myfootnote5) </sup>.|
|`revsimp` | optimization tool that uses several methods, which include canclation of adjacent not gates, merging of Toffoli gates with same targets (similar to template matching) and re-synthesis of gates using EXORCISM, among others. The . If called with the `-v, --verbose` flag, the process is detailed on screen. | 
|`tpar` | polynomial-time algorithm for optimizing quantum circuits that takes the actual implementation of fault-tolerant logical gates into consideration. To run this command, the `tpar` package must be installed using Cirkit's package manager. For a more detailed description of this method, consult <sup>[6](#myfootnote6) </sup>. |

## Conversion

It is possible to convert compatible data structures from one to other. The `convert` command allows us to convert one data structure to another. The command needs to have specified as flag the input and output conversion data structures. After specifying this flag, the command takes as an input the pointer in the input data structure store. The output data structure is written to a new element of the output data structure store by default.

The following table lists of all the possible conversions that can be done with the `convert` command, along with its flags.

|Input | Output | Flag |
| ---- | :------: | ---- |
|Reversible circuit | Aid-inverter graph | `--circuit_to_aig` |
Reversible circuit | BDD of a characteristic reversible function |`--circuit_to_rcbdd` |
|Reversible circuit | Reversible specification | `--circuit_to_spec` |
|Aid-inverter graph | XOR majority graph | `--aig_to_xmg` |
|Aid-inverter graph | Binary decision diagram | `--aig_to_bdd` |
|Expression | XOR majority graph | `--expr_to_xmg` |
|Expression | Binary decision diagram | `--expr_to_bdd` |
|Expression | Reversible specification | `--expr_to_spec` |
|XOR majority graph | Expression | `--xmg_to_expr` |
|XOR majority graph | Aid-inverter graph | `--xmg_to_aig` |

In particular, the `--circuit_to_spec` flag is particularly useful, because it allows us to simulate all the outcomes of a reversible circuit, that is, to obtain the truth table of a reversible circuit. The inverse process, to design a reversible circuit that has a determined truth table, is discussed in the following section.

## Synthesis
In traditional and reversible logic, circuit synthesis, or simply synthesis, is the process of designing a circuit that computes a desired Boolean function, i. e. that matches a given and arbitrary truth table. As this process is fundamental for the physical implementation of a digital circuit, synthesis is a very important task that can be made in very different ways in order to optimize or achieve certain desired results. 

Most of the reversible logic synthesis algorithms included in Revkit are too complex (most of them have a complete paper describing them) to be explained fully on here, so each one is referenced to its original source. A good resource for more information on each command is also found in Mathias Soeken's review of the [state of the art in reversible logic synthesis](https://github.com/msoeken/reversible-sota)

The following table lists all of the synthesis commands in Revkit. Most of them need different data structures in store as input in order to perform the synthesis. They take as an input the pointer of the input data structure store. All of them can be called with the `-v, --verbose` flag so that it outputs more information over each step of the algorithm. 


| Command | Input | Description | 
| :-----: | ----- | ----------- |
|`cbs` | And-inverter graph | Circuit based synthesis. For more information about the algorithm, consult <sup> [7](#myfootnote7) </sup>  |
|`dbs` | Reversible specification | Decomposition based synthesis. For more information about the algorithm,  consult <sup> [8](#myfootnote8) </sup> <sup> [9](#myfootnote9) </sup> |
|`rms` | Reversible specification | Reed-Muller spectra-based synthesis. For more information about the algorithm,  consult <sup> [10](#myfootnote10) </sup> |
|`tbs` | Reversible specification | Transformation based synthesis. For more information about the algorithm,  consult <sup> [11](#myfootnote11) </sup> |
|`qbs` | BDD of a characteristic reverible function | Quantum  Multiple-valued  Decision Diagrams based synthesis. For more information about the algorithm,  consult <sup> [12](#myfootnote12) </sup> |
|`exs` | Reversible specification | synthesizes a minimal circuit (with respect to the number of gates) using the SAT-basedexact synthesis approach. For more information about the algorithm,  consult <sup> [13](#myfootnote13) </sup>. |
|`esopbs` | - | ESOP-based synthesis. It takes as an input a BDD represented by a PLA file. The `--filename` argument indicates the path of the file. For more information about the algorithm,  consult <sup> [14](#myfootnote14) </sup> |
|`lhrs` | And-inverter graph | Look-up table (LUT) based hierarchical reversible synthesis. Fore more information, consult <sup> [15](#myfootnote15) </sup> <sup> [16](#myfootnote16) </sup> |
|`dxs` | XOR majority graph | Direct XOR majority graph synthesis |

## References


<a name="myfootnote1">1  </a>  Maslov, D.  *On  the  advantages  of  using  relative  phase  Toffolis  with  an  application  to  multiple  control  Toffoli
optimization*. In: (2015).
doi
:
10.1103/PhysRevA.93.022311
. eprint:
arXiv:1508.03273.


<a name="myfootnote2">2  </a>   Amy, M. et al. *A Meet-in-the-Middle Algorithm for Fast Synthesis of Depth-Optimal Quantum Circuits*. In:
IEEE
Transactions on Computer-Aided Design of Integrated Circuits and Systems
32.6 (June 2013), pp. 818–830.
issn
: 0278-
0070.
doi
:
10.1109/TCAD.2013.2244643

<a name="myfootnote3">3  </a> Abdessaied, N. et al. *Reducing the Depth of Quantum Circuits Using Additional Circuit Lines*. In:
Reversible
Computation:  5th  International  Conference,  RC  2013,  Victoria,  BC,  Canada,  July  4-5,  2013.  Proceedings
.  Berlin,
Heidelberg: Springer Berlin Heidelberg, 2013, pp. 221–233.

<a name="myfootnote4">4  </a> Perkowski, M. and Mishchenko, A. . *Fast Heuristic Minimization of Exclusive-Sums-of-Products*. In:
Proceedings of the
RM’2001 Workshop
. DAC ’10. 2001

<a name="myfootnote5">5 </a>    Wille, R. ; Soeken, M. and Drechsler, R. . *Reducing the Number of Lines in Reversible Circuits*. In:
Proceedings of the 47th Design Automation Conference
. DAC ’10. Anaheim, California: ACM, 2010, pp. 647–652


<a name="myfootnote6">6 </a>  Amy, M.; Maslov, D. and Mosca, M. . *Polynomial-time T-depth Optimization of Clifford+T circuits via
Matroid Partitioning*. In: (2013).
doi
:
10.1109/TCAD.2014.2341953
. eprint:
arXiv:1303.2042

<a name="myfootnote7">7 </a>  Soeken, M.  and Chattopadhyay,  A. . *Unlocking Efficiency and Scalability of Reversible Logic Synthesis Using Conventional Logic Synthesis*. In:
Proceedings  of  the  53rd  Annual  Design  Automation  Conference
. DAC ’16. Austin,
Texas: ACM, 2016, 149:1–149:6

<a name="myfootnote8">8 </a>De Vos, A. and Van Rentergem, Y. . *Young subgroups for reversible computers*. In:
Advances in Mathematics of
Communications
2.2 (2008), pp. 183–200.
doi
:
10.3934/amc.2008.2.183

<a name="myfootnote9">9 </a> Soeken, M et al. *Ancilla-free synthesis of large reversible functions using binary decision diagrams*. In:
Journal
of Symbolic Computation
73 (2016), pp. 1–26

<a name="myfootnote10">10 </a> Maslov, D. ; Dueck, G. and Miller, M. . *Techniques for the Synthesis of Reversible Toffoli Networks*. In:
ACM
Trans. Des. Autom. Electron. Syst.
12.4 (Sept. 2007).
doi
:
10.1145/1278349.1278355


<a name="myfootnote11">11 </a>  Miller, M. ; Maslov, D.  and Gerhard Dueck, G. . *A Transformation Based Algorithm for Reversible Logic
Synthesis*. In:
Proceedings  of  the  40th  Annual  Design  Automation  Conference
. DAC ’03. Anaheim, CA, USA: ACM,
2003, pp. 318–323.
doi
:
10.1145/775832.775915
.

<a name="myfootnote12">12 </a> Miller, D.  and  Thornton, M. .  *QMDD:  A  Decision  Diagram  Structure  for  Reversible  and  Quantum Circuits*. In: Proceedings of the 36th International Symposium on Multiple-Valued Logic
. ISMVL ’06. Washington, DC,
USA: IEEE Computer Society, 2006, pp. 30–.
isbn
: 0-7695-2532-6.
doi
:
10.1109/ISMVL.2006.35
.

<a name="myfootnote13">13 </a> Groβe, D.  Et al.
. *Exact Multiple-control Toffoli Network Synthesis with SAT Techniques*. In:
Trans. Comp.-Aided
Des. Integ. Cir. Sys.
28.5 (May 2009), pp. 703–715.
doi
:
10.1109/TCAD.2009.2017215

<a name="myfootnote14">14 </a>Fazel, K ; Thornton, M. and Rice, R. . *ESOP-based Toffoli Gate Cascade Generation* . In:
2007 IEEE Pacific Rim
Conference  on  Communications,  Computers  and  Signal  Processing
. Aug. 2007, pp. 206–209.
doi
:
10.1109/PACRIM.
2007.4313212
.


<a name="myfootnote15">15 </a> Soeken, M. et al. *Hierarchical Reversible Logic Synthesis Using LUTs* . In:
Proceedings of the 54th Annual Design
Automation  Conference  2017
. ACM, 2017, 78:1–78:6.
isbn
: 978-1-4503-4927-7.
doi
:
10.
1145/3061639.3062261


<a name="myfootnote16">16 </a>Soeken, M. et al.
*Logic Synthesis for Quantum Computing*
. 2017. eprint:
arXiv:1706.02721
