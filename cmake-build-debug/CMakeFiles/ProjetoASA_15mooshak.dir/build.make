# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.23

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
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
RM = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/powee/CLionProjects/ProjetoASA_1

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/powee/CLionProjects/ProjetoASA_1/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/ProjetoASA_15mooshak.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/ProjetoASA_15mooshak.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/ProjetoASA_15mooshak.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/ProjetoASA_15mooshak.dir/flags.make

CMakeFiles/ProjetoASA_15mooshak.dir/15mooshak.cpp.o: CMakeFiles/ProjetoASA_15mooshak.dir/flags.make
CMakeFiles/ProjetoASA_15mooshak.dir/15mooshak.cpp.o: ../15mooshak.cpp
CMakeFiles/ProjetoASA_15mooshak.dir/15mooshak.cpp.o: CMakeFiles/ProjetoASA_15mooshak.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/powee/CLionProjects/ProjetoASA_1/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/ProjetoASA_15mooshak.dir/15mooshak.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/ProjetoASA_15mooshak.dir/15mooshak.cpp.o -MF CMakeFiles/ProjetoASA_15mooshak.dir/15mooshak.cpp.o.d -o CMakeFiles/ProjetoASA_15mooshak.dir/15mooshak.cpp.o -c /Users/powee/CLionProjects/ProjetoASA_1/15mooshak.cpp

CMakeFiles/ProjetoASA_15mooshak.dir/15mooshak.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ProjetoASA_15mooshak.dir/15mooshak.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/powee/CLionProjects/ProjetoASA_1/15mooshak.cpp > CMakeFiles/ProjetoASA_15mooshak.dir/15mooshak.cpp.i

CMakeFiles/ProjetoASA_15mooshak.dir/15mooshak.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ProjetoASA_15mooshak.dir/15mooshak.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/powee/CLionProjects/ProjetoASA_1/15mooshak.cpp -o CMakeFiles/ProjetoASA_15mooshak.dir/15mooshak.cpp.s

# Object files for target ProjetoASA_15mooshak
ProjetoASA_15mooshak_OBJECTS = \
"CMakeFiles/ProjetoASA_15mooshak.dir/15mooshak.cpp.o"

# External object files for target ProjetoASA_15mooshak
ProjetoASA_15mooshak_EXTERNAL_OBJECTS =

ProjetoASA_15mooshak: CMakeFiles/ProjetoASA_15mooshak.dir/15mooshak.cpp.o
ProjetoASA_15mooshak: CMakeFiles/ProjetoASA_15mooshak.dir/build.make
ProjetoASA_15mooshak: CMakeFiles/ProjetoASA_15mooshak.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/powee/CLionProjects/ProjetoASA_1/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ProjetoASA_15mooshak"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/ProjetoASA_15mooshak.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/ProjetoASA_15mooshak.dir/build: ProjetoASA_15mooshak
.PHONY : CMakeFiles/ProjetoASA_15mooshak.dir/build

CMakeFiles/ProjetoASA_15mooshak.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/ProjetoASA_15mooshak.dir/cmake_clean.cmake
.PHONY : CMakeFiles/ProjetoASA_15mooshak.dir/clean

CMakeFiles/ProjetoASA_15mooshak.dir/depend:
	cd /Users/powee/CLionProjects/ProjetoASA_1/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/powee/CLionProjects/ProjetoASA_1 /Users/powee/CLionProjects/ProjetoASA_1 /Users/powee/CLionProjects/ProjetoASA_1/cmake-build-debug /Users/powee/CLionProjects/ProjetoASA_1/cmake-build-debug /Users/powee/CLionProjects/ProjetoASA_1/cmake-build-debug/CMakeFiles/ProjetoASA_15mooshak.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/ProjetoASA_15mooshak.dir/depend

