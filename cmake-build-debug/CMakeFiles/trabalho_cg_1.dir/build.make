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
include CMakeFiles/trabalho_cg_1.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/trabalho_cg_1.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/trabalho_cg_1.dir/flags.make

CMakeFiles/trabalho_cg_1.dir/main.cpp.o: CMakeFiles/trabalho_cg_1.dir/flags.make
CMakeFiles/trabalho_cg_1.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/maxjf1/projetos/cg/trabalho-cg-1/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/trabalho_cg_1.dir/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/trabalho_cg_1.dir/main.cpp.o -c /home/maxjf1/projetos/cg/trabalho-cg-1/main.cpp

CMakeFiles/trabalho_cg_1.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/trabalho_cg_1.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/maxjf1/projetos/cg/trabalho-cg-1/main.cpp > CMakeFiles/trabalho_cg_1.dir/main.cpp.i

CMakeFiles/trabalho_cg_1.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/trabalho_cg_1.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/maxjf1/projetos/cg/trabalho-cg-1/main.cpp -o CMakeFiles/trabalho_cg_1.dir/main.cpp.s

# Object files for target trabalho_cg_1
trabalho_cg_1_OBJECTS = \
"CMakeFiles/trabalho_cg_1.dir/main.cpp.o"

# External object files for target trabalho_cg_1
trabalho_cg_1_EXTERNAL_OBJECTS =

trabalho_cg_1: CMakeFiles/trabalho_cg_1.dir/main.cpp.o
trabalho_cg_1: CMakeFiles/trabalho_cg_1.dir/build.make
trabalho_cg_1: CMakeFiles/trabalho_cg_1.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/maxjf1/projetos/cg/trabalho-cg-1/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable trabalho_cg_1"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/trabalho_cg_1.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/trabalho_cg_1.dir/build: trabalho_cg_1

.PHONY : CMakeFiles/trabalho_cg_1.dir/build

CMakeFiles/trabalho_cg_1.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/trabalho_cg_1.dir/cmake_clean.cmake
.PHONY : CMakeFiles/trabalho_cg_1.dir/clean

CMakeFiles/trabalho_cg_1.dir/depend:
	cd /home/maxjf1/projetos/cg/trabalho-cg-1/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/maxjf1/projetos/cg/trabalho-cg-1 /home/maxjf1/projetos/cg/trabalho-cg-1 /home/maxjf1/projetos/cg/trabalho-cg-1/cmake-build-debug /home/maxjf1/projetos/cg/trabalho-cg-1/cmake-build-debug /home/maxjf1/projetos/cg/trabalho-cg-1/cmake-build-debug/CMakeFiles/trabalho_cg_1.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/trabalho_cg_1.dir/depend

