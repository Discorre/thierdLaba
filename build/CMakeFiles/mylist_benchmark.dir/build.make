# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.25

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/discorre/vscodeproj/thierdLaba

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/discorre/vscodeproj/thierdLaba/build

# Include any dependencies generated for this target.
include CMakeFiles/mylist_benchmark.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/mylist_benchmark.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/mylist_benchmark.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/mylist_benchmark.dir/flags.make

CMakeFiles/mylist_benchmark.dir/mylist_benchmark.cpp.o: CMakeFiles/mylist_benchmark.dir/flags.make
CMakeFiles/mylist_benchmark.dir/mylist_benchmark.cpp.o: /home/discorre/vscodeproj/thierdLaba/mylist_benchmark.cpp
CMakeFiles/mylist_benchmark.dir/mylist_benchmark.cpp.o: CMakeFiles/mylist_benchmark.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/discorre/vscodeproj/thierdLaba/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/mylist_benchmark.dir/mylist_benchmark.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/mylist_benchmark.dir/mylist_benchmark.cpp.o -MF CMakeFiles/mylist_benchmark.dir/mylist_benchmark.cpp.o.d -o CMakeFiles/mylist_benchmark.dir/mylist_benchmark.cpp.o -c /home/discorre/vscodeproj/thierdLaba/mylist_benchmark.cpp

CMakeFiles/mylist_benchmark.dir/mylist_benchmark.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mylist_benchmark.dir/mylist_benchmark.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/discorre/vscodeproj/thierdLaba/mylist_benchmark.cpp > CMakeFiles/mylist_benchmark.dir/mylist_benchmark.cpp.i

CMakeFiles/mylist_benchmark.dir/mylist_benchmark.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mylist_benchmark.dir/mylist_benchmark.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/discorre/vscodeproj/thierdLaba/mylist_benchmark.cpp -o CMakeFiles/mylist_benchmark.dir/mylist_benchmark.cpp.s

# Object files for target mylist_benchmark
mylist_benchmark_OBJECTS = \
"CMakeFiles/mylist_benchmark.dir/mylist_benchmark.cpp.o"

# External object files for target mylist_benchmark
mylist_benchmark_EXTERNAL_OBJECTS =

mylist_benchmark: CMakeFiles/mylist_benchmark.dir/mylist_benchmark.cpp.o
mylist_benchmark: CMakeFiles/mylist_benchmark.dir/build.make
mylist_benchmark: /usr/local/lib/libbenchmark.a
mylist_benchmark: CMakeFiles/mylist_benchmark.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/discorre/vscodeproj/thierdLaba/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable mylist_benchmark"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/mylist_benchmark.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/mylist_benchmark.dir/build: mylist_benchmark
.PHONY : CMakeFiles/mylist_benchmark.dir/build

CMakeFiles/mylist_benchmark.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/mylist_benchmark.dir/cmake_clean.cmake
.PHONY : CMakeFiles/mylist_benchmark.dir/clean

CMakeFiles/mylist_benchmark.dir/depend:
	cd /home/discorre/vscodeproj/thierdLaba/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/discorre/vscodeproj/thierdLaba /home/discorre/vscodeproj/thierdLaba /home/discorre/vscodeproj/thierdLaba/build /home/discorre/vscodeproj/thierdLaba/build /home/discorre/vscodeproj/thierdLaba/build/CMakeFiles/mylist_benchmark.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/mylist_benchmark.dir/depend

