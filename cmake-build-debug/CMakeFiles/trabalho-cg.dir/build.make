# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.14

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
CMAKE_COMMAND = /home/maxjf1/.local/share/JetBrains/Toolbox/apps/CLion/ch-0/192.5728.100/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /home/maxjf1/.local/share/JetBrains/Toolbox/apps/CLion/ch-0/192.5728.100/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/maxjf1/projetos/cg/trabalho-cg-1

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/maxjf1/projetos/cg/trabalho-cg-1/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/trabalho-cg.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/trabalho-cg.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/trabalho-cg.dir/flags.make

CMakeFiles/trabalho-cg.dir/src/main.cpp.o: CMakeFiles/trabalho-cg.dir/flags.make
CMakeFiles/trabalho-cg.dir/src/main.cpp.o: ../src/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/maxjf1/projetos/cg/trabalho-cg-1/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/trabalho-cg.dir/src/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/trabalho-cg.dir/src/main.cpp.o -c /home/maxjf1/projetos/cg/trabalho-cg-1/src/main.cpp

CMakeFiles/trabalho-cg.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/trabalho-cg.dir/src/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/maxjf1/projetos/cg/trabalho-cg-1/src/main.cpp > CMakeFiles/trabalho-cg.dir/src/main.cpp.i

CMakeFiles/trabalho-cg.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/trabalho-cg.dir/src/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/maxjf1/projetos/cg/trabalho-cg-1/src/main.cpp -o CMakeFiles/trabalho-cg.dir/src/main.cpp.s

# Object files for target trabalho-cg
trabalho__cg_OBJECTS = \
"CMakeFiles/trabalho-cg.dir/src/main.cpp.o"

# External object files for target trabalho-cg
trabalho__cg_EXTERNAL_OBJECTS =

trabalho-cg: CMakeFiles/trabalho-cg.dir/src/main.cpp.o
trabalho-cg: CMakeFiles/trabalho-cg.dir/build.make
trabalho-cg: /usr/lib/x86_64-linux-gnu/libOpenGL.so
trabalho-cg: /usr/lib/x86_64-linux-gnu/libGLX.so
trabalho-cg: /usr/lib/x86_64-linux-gnu/libGLU.so
trabalho-cg: /usr/lib/x86_64-linux-gnu/libglut.so
trabalho-cg: CMakeFiles/trabalho-cg.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/maxjf1/projetos/cg/trabalho-cg-1/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable trabalho-cg"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/trabalho-cg.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/trabalho-cg.dir/build: trabalho-cg

.PHONY : CMakeFiles/trabalho-cg.dir/build

CMakeFiles/trabalho-cg.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/trabalho-cg.dir/cmake_clean.cmake
.PHONY : CMakeFiles/trabalho-cg.dir/clean

CMakeFiles/trabalho-cg.dir/depend:
	cd /home/maxjf1/projetos/cg/trabalho-cg-1/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/maxjf1/projetos/cg/trabalho-cg-1 /home/maxjf1/projetos/cg/trabalho-cg-1 /home/maxjf1/projetos/cg/trabalho-cg-1/cmake-build-debug /home/maxjf1/projetos/cg/trabalho-cg-1/cmake-build-debug /home/maxjf1/projetos/cg/trabalho-cg-1/cmake-build-debug/CMakeFiles/trabalho-cg.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/trabalho-cg.dir/depend

