# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.19

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
CMAKE_COMMAND = /snap/clion/149/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /snap/clion/149/bin/cmake/linux/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/ayttekao/CLionProjects/Fundi/Fundi_7

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/ayttekao/CLionProjects/Fundi/Fundi_7/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/wordProcessing.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/wordProcessing.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/wordProcessing.dir/flags.make

CMakeFiles/wordProcessing.dir/wordProcessingTask3.cpp.o: CMakeFiles/wordProcessing.dir/flags.make
CMakeFiles/wordProcessing.dir/wordProcessingTask3.cpp.o: ../wordProcessingTask3.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ayttekao/CLionProjects/Fundi/Fundi_7/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/wordProcessing.dir/wordProcessingTask3.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/wordProcessing.dir/wordProcessingTask3.cpp.o -c /home/ayttekao/CLionProjects/Fundi/Fundi_7/wordProcessingTask3.cpp

CMakeFiles/wordProcessing.dir/wordProcessingTask3.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/wordProcessing.dir/wordProcessingTask3.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ayttekao/CLionProjects/Fundi/Fundi_7/wordProcessingTask3.cpp > CMakeFiles/wordProcessing.dir/wordProcessingTask3.cpp.i

CMakeFiles/wordProcessing.dir/wordProcessingTask3.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/wordProcessing.dir/wordProcessingTask3.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ayttekao/CLionProjects/Fundi/Fundi_7/wordProcessingTask3.cpp -o CMakeFiles/wordProcessing.dir/wordProcessingTask3.cpp.s

# Object files for target wordProcessing
wordProcessing_OBJECTS = \
"CMakeFiles/wordProcessing.dir/wordProcessingTask3.cpp.o"

# External object files for target wordProcessing
wordProcessing_EXTERNAL_OBJECTS =

wordProcessing: CMakeFiles/wordProcessing.dir/wordProcessingTask3.cpp.o
wordProcessing: CMakeFiles/wordProcessing.dir/build.make
wordProcessing: CMakeFiles/wordProcessing.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/ayttekao/CLionProjects/Fundi/Fundi_7/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable wordProcessing"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/wordProcessing.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/wordProcessing.dir/build: wordProcessing

.PHONY : CMakeFiles/wordProcessing.dir/build

CMakeFiles/wordProcessing.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/wordProcessing.dir/cmake_clean.cmake
.PHONY : CMakeFiles/wordProcessing.dir/clean

CMakeFiles/wordProcessing.dir/depend:
	cd /home/ayttekao/CLionProjects/Fundi/Fundi_7/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ayttekao/CLionProjects/Fundi/Fundi_7 /home/ayttekao/CLionProjects/Fundi/Fundi_7 /home/ayttekao/CLionProjects/Fundi/Fundi_7/cmake-build-debug /home/ayttekao/CLionProjects/Fundi/Fundi_7/cmake-build-debug /home/ayttekao/CLionProjects/Fundi/Fundi_7/cmake-build-debug/CMakeFiles/wordProcessing.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/wordProcessing.dir/depend

