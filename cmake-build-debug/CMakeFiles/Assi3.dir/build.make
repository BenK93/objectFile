# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.15

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
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/Ben-K/CLionProjects/Assi3

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/Ben-K/CLionProjects/Assi3/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/Assi3.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Assi3.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Assi3.dir/flags.make

CMakeFiles/Assi3.dir/main.c.o: CMakeFiles/Assi3.dir/flags.make
CMakeFiles/Assi3.dir/main.c.o: ../main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/Ben-K/CLionProjects/Assi3/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/Assi3.dir/main.c.o"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/Assi3.dir/main.c.o   -c /Users/Ben-K/CLionProjects/Assi3/main.c

CMakeFiles/Assi3.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Assi3.dir/main.c.i"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/Ben-K/CLionProjects/Assi3/main.c > CMakeFiles/Assi3.dir/main.c.i

CMakeFiles/Assi3.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Assi3.dir/main.c.s"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/Ben-K/CLionProjects/Assi3/main.c -o CMakeFiles/Assi3.dir/main.c.s

# Object files for target Assi3
Assi3_OBJECTS = \
"CMakeFiles/Assi3.dir/main.c.o"

# External object files for target Assi3
Assi3_EXTERNAL_OBJECTS =

Assi3: CMakeFiles/Assi3.dir/main.c.o
Assi3: CMakeFiles/Assi3.dir/build.make
Assi3: CMakeFiles/Assi3.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/Ben-K/CLionProjects/Assi3/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable Assi3"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Assi3.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Assi3.dir/build: Assi3

.PHONY : CMakeFiles/Assi3.dir/build

CMakeFiles/Assi3.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Assi3.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Assi3.dir/clean

CMakeFiles/Assi3.dir/depend:
	cd /Users/Ben-K/CLionProjects/Assi3/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/Ben-K/CLionProjects/Assi3 /Users/Ben-K/CLionProjects/Assi3 /Users/Ben-K/CLionProjects/Assi3/cmake-build-debug /Users/Ben-K/CLionProjects/Assi3/cmake-build-debug /Users/Ben-K/CLionProjects/Assi3/cmake-build-debug/CMakeFiles/Assi3.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Assi3.dir/depend
