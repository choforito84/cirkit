# Revkit user guide

This is intended to serve as an user guide for Revkit, a reversible logic toolkit program. Revkit is now a part of [Cirkit](https://github.com/msoeken/cirkit), a toolkit program for logic created by Mathias Soeken at the École Polythechnique Fedérale de Lausanne.

This user manual contains a list of most commands in Revkit along with their description, along with a section completely dedicated to examples of the code. 

## About the installation

Although in Cirkit's repository we can find instructions for installing Revkit, here we will detail how to make a clean installation of Revkit inside Ubuntu and inside the Uleth Linux System, a Centos7-based computer network designed for the Computer Science and Mathematics deparment memebers at the University of Lethbridge in Alberta, Canada.

Cirkit is supported by UNIX-like systems such as MacOS and Linux distributions.

## Installation in Ubuntu
The following instructions for installing Revkit in Ubuntu are also included in Cirkit's Github repository. First of all, we need to install the dependencies needed for Revkit using Ubuntu's package manager. The following command must be executed from a terminal:
```bash
sudo apt-get install build-essential git g++ cmake libboost-all-dev libgmp3-dev libxml2-dev zlib1g-dev lapack openblas
```

After installing these dependencies, we are ready for cloning the Github repository using the following command: 

```bash
git clone https://github.com/msoeken/cirkit.git
cd cirkit
```

After this step, we need to create and update some environment variables of the system. To do that, run the following commands in the same terminal:

```bash
export CIRKIT_HOME=<full-path-to-cirkit-repository>
export LD_LIBRARY_PATH=$CIRKIT_HOME/ext/lib:$LD_LIBRARY_PATH
export PATH=$CIRKIT_HOME/ext/bin:$PATH
```

Now, to install Revkit we must run the following commands from the terminal:

```bash
mkdir build
cd build
cmake -Denable_cirkit-addon-reversible=ON -Denable_cirkit-addon-formal=ON ..
make external
make revkit
```

The first two commands create a directory called "build" inside of Cirkit main directory and changes the terminal location to it. The following three commands build Revkit from the cmake configuration files created along it.

### Manually installing Boost
Even though the Boost library installed from Ubuntu's package manager is higher than the requirement from Revkit (1.58.0 at Ubuntu;s package manager, Revkit requires higher than 1.56.0), this version is fairly old and it can cause some problems when installing Revkit. To avoid this problems, we recommend installing a newer version of Boost (1.64.0) by downloading it from their official website and then installing it. This can be accomplished with the following commands:

```bash
wget https://dl.bintray.com/boostorg/release/1.64.0/source/boost_1_64_0.tar.gz
tar xzvf boost_1_64_0.tar.gz
cd boost_1_64_0.tar.gz/
sudo apt-get update
sudo apt-get install build-essential g++ python-dev autotools-dev libicu-dev build-essential libbz2-dev 
./bootstrap.sh --prefix=/usr/
./b2
sudo ./b2 install 
```
The first three lines downloads, uncompress Boost and changes the terminal direction to Boost main directory. The following two lines use Ubuntu's package manager to install tools needed for Boosts installation. The last three lines compile and install Boost under the '/usr/' directory of the user.


## Installation in ULeth linux system

To install Revkit in ULeth linux system we face several problems due to the complexity of the system and to not having root permission. The problems can be listed as the following.

+ **Disk quota issue:**  The disk space available for each user at the ULeth linux system is low relatively to the system size (the installation is of around 2.5 GB). The solution to this is to install it locally on each computer you are working or using a shared partition in the system. For anyone without much experience with the system, the system administrator assistance is needed.
+ **Dependencies issue:**  although all of the dependencies needed to install the program are included in the system, some of them are not updated and can not be used safely by Revkit. 
+ **Compiling issues:** As a result of being written in C++, there can be problems compiling it if previous built has failed due to the usage of CCache by GCC. Basically, CCache stores compilations of C/C++ code so that compiling a program several times is made with lower downtime. However, for builds that have failed, CCache uses that same compilation so it forces that any further build have the same error, even if you have corrected it. 

So solve the **Disk Quota issues**, the first step in the installation is to a file location in the system must be found with enough free space (more than 3 GB) to clone the github repository and perform the installation. After that, clone the Github repository:
```bash
~$ git clone https://github.com/msoeken/cirkit.git
~$ cd cirkit
```
### Installing dependencies

Due to the high dependencies requirements of Cirkit, it can not be installed easily on a system without having root privileges to update and install all of the dependencies needed. However, it can be installed using a package manager provided with the program. In the following we will list each dependency and its status at the ULeth linux system:

+ **git :** included in the linux system and updated.
+ **GNU MP and GMP++ :** included in the linux system and updated.
+ **GNU readline :** included in the linux system and updated.
+ **GCC :** included in the linux system but out of date. Cirkit requires a version higher than 4.9.0, meanwhile the system is at 4.8.5.
+ **cmake :** included in the linux system but out of date. Revkit requires a version higher than 3.0.0 and the system is in 2.8.5.
+ **boost :** included in the linux system but out of date. Revkit requires a version higher than 1.56.0 and the system is in 1.53.0.

Although it would seem that a simple update made by the system administrator would be enough to be able to install Revkit, Boost and C++ cannot be updated because it generates problems with other programs in the system. 

To install the updated version of the dependencies needed, we must use Cirkit's included package manager. This package manager allows us to install local versions of the needed programs without the use of root privileges. Inside the main directory of the repository, open a terminal and run the following commands:

```bash
 utils/tools.py install boost
 utils/tools.py install gcc
 utils/tools.py install cmake
```

It is very likely that the terminal throws an error when installing `gcc`, but this problem is not for installing GCC other than for installing other dependencies, in particular, for ISL. After this step, we need to create and update some environment variables of the system. To do that, run the following commands in the same terminal:

```bash
export CIRKIT_HOME=<full-path-to-cirkit-repository>
export LD_LIBRARY_PATH=$CIRKIT_HOME/ext/lib:$LD_LIBRARY_PATH
export PATH=$CIRKIT_HOME/ext/bin:$PATH
```