# CDataStructures

This repository contains my implementation of data structures in C (*shudder*)
and is meant for me to hone my C skills as well as familiarising myself with
tools such as CMake and documentation generators such as Doxygen. If you spot
any problem in the source code you can file an issue or initiate a pull
request on 
[this library's Github Repository](https://github.com/RenoirTan/CDataStructures).

# Building

*NOTE: I've only tested this on Windows (using Cygwin and MSVC) because I'm
too lazy to fire up my Ubuntu virtual machine.*

## Setup

This project heavily uses CMake to simplify the build process, so make sure
that you have CMake installed. If CMake is not on your system yet, you can
cheese your way through by installing the `cmake` package on the Python Package
Index:

```bash
pip install cmake
```

This command will install the latest version of CMake on your computer as well
as put the command onto your path environment variable the `Scripts` folder
of your Python installation is also on path.

Once that is done, you have to install a C compiler. To see which compilers
are supported, run

```bash
cmake --help
```

and scroll down to the **Generators** section outputted by cmake. On Windows,
this should look something like this...

```
Generators

The following generators are available on this platform (* marks default):
* Visual Studio 16 2019        = Generates Visual Studio 2019 project files.
                                 Use -A option to specify architecture.
  Visual Studio 15 2017 [arch] = Generates Visual Studio 2017 project files.
                                 Optional [arch] can be "Win64" or "ARM".
  Visual Studio 14 2015 [arch] = Generates Visual Studio 2015 project files.
                                 Optional [arch] can be "Win64" or "ARM".
  Visual Studio 12 2013 [arch] = Generates Visual Studio 2013 project files.
                                 Optional [arch] can be "Win64" or "ARM".
  Visual Studio 11 2012 [arch] = Generates Visual Studio 2012 project files.
                                 Optional [arch] can be "Win64" or "ARM".
  Visual Studio 10 2010 [arch] = Generates Visual Studio 2010 project files.
                                 Optional [arch] can be "Win64" or "IA64".
  Visual Studio 9 2008 [arch]  = Generates Visual Studio 2008 project files.
                                 Optional [arch] can be "Win64" or "IA64".
  Borland Makefiles            = Generates Borland makefiles.
  NMake Makefiles              = Generates NMake makefiles.
  NMake Makefiles JOM          = Generates JOM makefiles.
  MSYS Makefiles               = Generates MSYS makefiles.
  MinGW Makefiles              = Generates a make file for use with
                                 mingw32-make.

.................................. AND SO ON ..................................
```

## Actually building the library

Before doing anything, *`cd`* into the repository directory:

```bash
cd ./CDataStructures
```

After setting up your build environment, you can run the `gen.sh` or `gen.bat`
scripts (anything ending with `.sh` runs on Unix and those with `.bat` run on
Windows) to let CMake configure the settings and Makefiles for this project.

If no errors pop up, you should be good to go, and you can run `build.sh` or
`build.bat` (of course, which file you run depends on your OS).

All the binary files should end up in the `./bin` folder created in the
repository.

## Generating the documentation

As mentioned before, this library uses Doxygen to convert comments to
documentation. To get Doxygen, following the instructions on their
[website](https://www.doxygen.nl/manual/install.html).

Then, in your terminal, type in the following command (where you can see
a file called `Doxyfile`):

```bash
doxygen Doxyfile
```

If you're more comfortable with a GUI, you can use Doxywizard, which is bundled
together with Doxygen (in fact, the `Doxyfile` was created using the Doxywizard
GUI!).

The documentation files can be found in the `./docs` folder.

# Using this library as a dependency

Add this repository as a sub-directory of your project and add the top-level
`CMakeLists.txt` as a subdirectory of your project using the `add_subdirectory`
command.

# Conventions

All custom identifiers defined here are prefixed by `cds` or `CDS`.

This library uses *snake_case* for most identifiers, including but not limited
to functions, variables and type names. For example, the vector data structure
is known as `cds_vector_t` in the library. This example also showcases the
suffixes used to annotate data types. The `_t` at the end of `cds_vector_t`
tells us that this struct stores data, while typedefs like `cds_free_f` suggests
that this type is a function pointer.

Macros use SCREAMING_SNAKE_CASE, including header guards.

# Data Structures

Available data structures:

| Name | Status | Description |
| ---- | ------ | ----------- |
| slist | ✔️ | A list where each element points to the next element in the list via a pointer. |
| vector | ✔️ | A dynamically allocated region of memory which can store an array of elements. This data structure can expand and shrink in size when needed. |
