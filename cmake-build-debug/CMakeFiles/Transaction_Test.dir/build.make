# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.19

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "D:\Program Files\JetBrains\CLion 2021.1.1\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "D:\Program Files\JetBrains\CLion 2021.1.1\bin\cmake\win\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = D:\code\c\oop_c\Transaction_Test

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = D:\code\c\oop_c\Transaction_Test\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/Transaction_Test.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Transaction_Test.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Transaction_Test.dir/flags.make

CMakeFiles/Transaction_Test.dir/main.cpp.obj: CMakeFiles/Transaction_Test.dir/flags.make
CMakeFiles/Transaction_Test.dir/main.cpp.obj: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\code\c\oop_c\Transaction_Test\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Transaction_Test.dir/main.cpp.obj"
	D:\code\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\Transaction_Test.dir\main.cpp.obj -c D:\code\c\oop_c\Transaction_Test\main.cpp

CMakeFiles/Transaction_Test.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Transaction_Test.dir/main.cpp.i"
	D:\code\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\code\c\oop_c\Transaction_Test\main.cpp > CMakeFiles\Transaction_Test.dir\main.cpp.i

CMakeFiles/Transaction_Test.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Transaction_Test.dir/main.cpp.s"
	D:\code\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\code\c\oop_c\Transaction_Test\main.cpp -o CMakeFiles\Transaction_Test.dir\main.cpp.s

# Object files for target Transaction_Test
Transaction_Test_OBJECTS = \
"CMakeFiles/Transaction_Test.dir/main.cpp.obj"

# External object files for target Transaction_Test
Transaction_Test_EXTERNAL_OBJECTS =

Transaction_Test.exe: CMakeFiles/Transaction_Test.dir/main.cpp.obj
Transaction_Test.exe: CMakeFiles/Transaction_Test.dir/build.make
Transaction_Test.exe: CMakeFiles/Transaction_Test.dir/linklibs.rsp
Transaction_Test.exe: CMakeFiles/Transaction_Test.dir/objects1.rsp
Transaction_Test.exe: CMakeFiles/Transaction_Test.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=D:\code\c\oop_c\Transaction_Test\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable Transaction_Test.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\Transaction_Test.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Transaction_Test.dir/build: Transaction_Test.exe

.PHONY : CMakeFiles/Transaction_Test.dir/build

CMakeFiles/Transaction_Test.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\Transaction_Test.dir\cmake_clean.cmake
.PHONY : CMakeFiles/Transaction_Test.dir/clean

CMakeFiles/Transaction_Test.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" D:\code\c\oop_c\Transaction_Test D:\code\c\oop_c\Transaction_Test D:\code\c\oop_c\Transaction_Test\cmake-build-debug D:\code\c\oop_c\Transaction_Test\cmake-build-debug D:\code\c\oop_c\Transaction_Test\cmake-build-debug\CMakeFiles\Transaction_Test.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Transaction_Test.dir/depend

