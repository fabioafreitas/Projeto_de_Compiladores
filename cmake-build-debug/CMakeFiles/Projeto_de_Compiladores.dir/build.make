# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.14

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2019.2\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2019.2\bin\cmake\win\bin\cmake.exe" -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\fabio\Desktop\PCompiladores

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\fabio\Desktop\PCompiladores\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/Projeto_de_Compiladores.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Projeto_de_Compiladores.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Projeto_de_Compiladores.dir/flags.make

CMakeFiles/Projeto_de_Compiladores.dir/main.c.obj: CMakeFiles/Projeto_de_Compiladores.dir/flags.make
CMakeFiles/Projeto_de_Compiladores.dir/main.c.obj: ../main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\fabio\Desktop\PCompiladores\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/Projeto_de_Compiladores.dir/main.c.obj"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\Projeto_de_Compiladores.dir\main.c.obj   -c C:\Users\fabio\Desktop\PCompiladores\main.c

CMakeFiles/Projeto_de_Compiladores.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Projeto_de_Compiladores.dir/main.c.i"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\fabio\Desktop\PCompiladores\main.c > CMakeFiles\Projeto_de_Compiladores.dir\main.c.i

CMakeFiles/Projeto_de_Compiladores.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Projeto_de_Compiladores.dir/main.c.s"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\Users\fabio\Desktop\PCompiladores\main.c -o CMakeFiles\Projeto_de_Compiladores.dir\main.c.s

# Object files for target Projeto_de_Compiladores
Projeto_de_Compiladores_OBJECTS = \
"CMakeFiles/Projeto_de_Compiladores.dir/main.c.obj"

# External object files for target Projeto_de_Compiladores
Projeto_de_Compiladores_EXTERNAL_OBJECTS =

Projeto_de_Compiladores.exe: CMakeFiles/Projeto_de_Compiladores.dir/main.c.obj
Projeto_de_Compiladores.exe: CMakeFiles/Projeto_de_Compiladores.dir/build.make
Projeto_de_Compiladores.exe: CMakeFiles/Projeto_de_Compiladores.dir/linklibs.rsp
Projeto_de_Compiladores.exe: CMakeFiles/Projeto_de_Compiladores.dir/objects1.rsp
Projeto_de_Compiladores.exe: CMakeFiles/Projeto_de_Compiladores.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\fabio\Desktop\PCompiladores\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable Projeto_de_Compiladores.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\Projeto_de_Compiladores.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Projeto_de_Compiladores.dir/build: Projeto_de_Compiladores.exe

.PHONY : CMakeFiles/Projeto_de_Compiladores.dir/build

CMakeFiles/Projeto_de_Compiladores.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\Projeto_de_Compiladores.dir\cmake_clean.cmake
.PHONY : CMakeFiles/Projeto_de_Compiladores.dir/clean

CMakeFiles/Projeto_de_Compiladores.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\fabio\Desktop\PCompiladores C:\Users\fabio\Desktop\PCompiladores C:\Users\fabio\Desktop\PCompiladores\cmake-build-debug C:\Users\fabio\Desktop\PCompiladores\cmake-build-debug C:\Users\fabio\Desktop\PCompiladores\cmake-build-debug\CMakeFiles\Projeto_de_Compiladores.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Projeto_de_Compiladores.dir/depend

