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
CMAKE_COMMAND = /home/yuval/Desktop/clion-2019.2.5/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /home/yuval/Desktop/clion-2019.2.5/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/yuval/CLionProjects/OS_Ex2

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/yuval/CLionProjects/OS_Ex2/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/OS_Ex2.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/OS_Ex2.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/OS_Ex2.dir/flags.make

CMakeFiles/OS_Ex2.dir/ex2.c.o: CMakeFiles/OS_Ex2.dir/flags.make
CMakeFiles/OS_Ex2.dir/ex2.c.o: ../ex2.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/yuval/CLionProjects/OS_Ex2/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/OS_Ex2.dir/ex2.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/OS_Ex2.dir/ex2.c.o   -c /home/yuval/CLionProjects/OS_Ex2/ex2.c

CMakeFiles/OS_Ex2.dir/ex2.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/OS_Ex2.dir/ex2.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/yuval/CLionProjects/OS_Ex2/ex2.c > CMakeFiles/OS_Ex2.dir/ex2.c.i

CMakeFiles/OS_Ex2.dir/ex2.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/OS_Ex2.dir/ex2.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/yuval/CLionProjects/OS_Ex2/ex2.c -o CMakeFiles/OS_Ex2.dir/ex2.c.s

CMakeFiles/OS_Ex2.dir/Test.c.o: CMakeFiles/OS_Ex2.dir/flags.make
CMakeFiles/OS_Ex2.dir/Test.c.o: ../Test.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/yuval/CLionProjects/OS_Ex2/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/OS_Ex2.dir/Test.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/OS_Ex2.dir/Test.c.o   -c /home/yuval/CLionProjects/OS_Ex2/Test.c

CMakeFiles/OS_Ex2.dir/Test.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/OS_Ex2.dir/Test.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/yuval/CLionProjects/OS_Ex2/Test.c > CMakeFiles/OS_Ex2.dir/Test.c.i

CMakeFiles/OS_Ex2.dir/Test.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/OS_Ex2.dir/Test.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/yuval/CLionProjects/OS_Ex2/Test.c -o CMakeFiles/OS_Ex2.dir/Test.c.s

CMakeFiles/OS_Ex2.dir/backup.c.o: CMakeFiles/OS_Ex2.dir/flags.make
CMakeFiles/OS_Ex2.dir/backup.c.o: ../backup.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/yuval/CLionProjects/OS_Ex2/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/OS_Ex2.dir/backup.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/OS_Ex2.dir/backup.c.o   -c /home/yuval/CLionProjects/OS_Ex2/backup.c

CMakeFiles/OS_Ex2.dir/backup.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/OS_Ex2.dir/backup.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/yuval/CLionProjects/OS_Ex2/backup.c > CMakeFiles/OS_Ex2.dir/backup.c.i

CMakeFiles/OS_Ex2.dir/backup.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/OS_Ex2.dir/backup.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/yuval/CLionProjects/OS_Ex2/backup.c -o CMakeFiles/OS_Ex2.dir/backup.c.s

CMakeFiles/OS_Ex2.dir/newBack.c.o: CMakeFiles/OS_Ex2.dir/flags.make
CMakeFiles/OS_Ex2.dir/newBack.c.o: ../newBack.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/yuval/CLionProjects/OS_Ex2/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object CMakeFiles/OS_Ex2.dir/newBack.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/OS_Ex2.dir/newBack.c.o   -c /home/yuval/CLionProjects/OS_Ex2/newBack.c

CMakeFiles/OS_Ex2.dir/newBack.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/OS_Ex2.dir/newBack.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/yuval/CLionProjects/OS_Ex2/newBack.c > CMakeFiles/OS_Ex2.dir/newBack.c.i

CMakeFiles/OS_Ex2.dir/newBack.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/OS_Ex2.dir/newBack.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/yuval/CLionProjects/OS_Ex2/newBack.c -o CMakeFiles/OS_Ex2.dir/newBack.c.s

# Object files for target OS_Ex2
OS_Ex2_OBJECTS = \
"CMakeFiles/OS_Ex2.dir/ex2.c.o" \
"CMakeFiles/OS_Ex2.dir/Test.c.o" \
"CMakeFiles/OS_Ex2.dir/backup.c.o" \
"CMakeFiles/OS_Ex2.dir/newBack.c.o"

# External object files for target OS_Ex2
OS_Ex2_EXTERNAL_OBJECTS =

OS_Ex2: CMakeFiles/OS_Ex2.dir/ex2.c.o
OS_Ex2: CMakeFiles/OS_Ex2.dir/Test.c.o
OS_Ex2: CMakeFiles/OS_Ex2.dir/backup.c.o
OS_Ex2: CMakeFiles/OS_Ex2.dir/newBack.c.o
OS_Ex2: CMakeFiles/OS_Ex2.dir/build.make
OS_Ex2: CMakeFiles/OS_Ex2.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/yuval/CLionProjects/OS_Ex2/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking C executable OS_Ex2"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/OS_Ex2.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/OS_Ex2.dir/build: OS_Ex2

.PHONY : CMakeFiles/OS_Ex2.dir/build

CMakeFiles/OS_Ex2.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/OS_Ex2.dir/cmake_clean.cmake
.PHONY : CMakeFiles/OS_Ex2.dir/clean

CMakeFiles/OS_Ex2.dir/depend:
	cd /home/yuval/CLionProjects/OS_Ex2/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/yuval/CLionProjects/OS_Ex2 /home/yuval/CLionProjects/OS_Ex2 /home/yuval/CLionProjects/OS_Ex2/cmake-build-debug /home/yuval/CLionProjects/OS_Ex2/cmake-build-debug /home/yuval/CLionProjects/OS_Ex2/cmake-build-debug/CMakeFiles/OS_Ex2.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/OS_Ex2.dir/depend

