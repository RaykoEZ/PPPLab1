# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.3

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

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/local/bin/cmake

# The command to remove a file.
RM = /usr/local/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/s4903744/PPP/Assignments/PacmanStudent

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/s4903744/PPP/Assignments/PacmanStudent

# Include any dependencies generated for this target.
include CMakeFiles/Packman.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Packman.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Packman.dir/flags.make

CMakeFiles/Packman.dir/main.c.o: CMakeFiles/Packman.dir/flags.make
CMakeFiles/Packman.dir/main.c.o: main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/s4903744/PPP/Assignments/PacmanStudent/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/Packman.dir/main.c.o"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/Packman.dir/main.c.o   -c /home/s4903744/PPP/Assignments/PacmanStudent/main.c

CMakeFiles/Packman.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Packman.dir/main.c.i"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -E /home/s4903744/PPP/Assignments/PacmanStudent/main.c > CMakeFiles/Packman.dir/main.c.i

CMakeFiles/Packman.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Packman.dir/main.c.s"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -S /home/s4903744/PPP/Assignments/PacmanStudent/main.c -o CMakeFiles/Packman.dir/main.c.s

CMakeFiles/Packman.dir/main.c.o.requires:

.PHONY : CMakeFiles/Packman.dir/main.c.o.requires

CMakeFiles/Packman.dir/main.c.o.provides: CMakeFiles/Packman.dir/main.c.o.requires
	$(MAKE) -f CMakeFiles/Packman.dir/build.make CMakeFiles/Packman.dir/main.c.o.provides.build
.PHONY : CMakeFiles/Packman.dir/main.c.o.provides

CMakeFiles/Packman.dir/main.c.o.provides.build: CMakeFiles/Packman.dir/main.c.o


# Object files for target Packman
Packman_OBJECTS = \
"CMakeFiles/Packman.dir/main.c.o"

# External object files for target Packman
Packman_EXTERNAL_OBJECTS =

Packman: CMakeFiles/Packman.dir/main.c.o
Packman: CMakeFiles/Packman.dir/build.make
Packman: CMakeFiles/Packman.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/s4903744/PPP/Assignments/PacmanStudent/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable Packman"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Packman.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Packman.dir/build: Packman

.PHONY : CMakeFiles/Packman.dir/build

CMakeFiles/Packman.dir/requires: CMakeFiles/Packman.dir/main.c.o.requires

.PHONY : CMakeFiles/Packman.dir/requires

CMakeFiles/Packman.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Packman.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Packman.dir/clean

CMakeFiles/Packman.dir/depend:
	cd /home/s4903744/PPP/Assignments/PacmanStudent && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/s4903744/PPP/Assignments/PacmanStudent /home/s4903744/PPP/Assignments/PacmanStudent /home/s4903744/PPP/Assignments/PacmanStudent /home/s4903744/PPP/Assignments/PacmanStudent /home/s4903744/PPP/Assignments/PacmanStudent/CMakeFiles/Packman.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Packman.dir/depend

