# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.24

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
CMAKE_SOURCE_DIR = /home/egor/Desktop/gl/MotionMatching/sources

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/egor/Desktop/gl/MotionMatching/sources

# Include any dependencies generated for this target.
include 3rd_party/eastl/CMakeFiles/eastl.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include 3rd_party/eastl/CMakeFiles/eastl.dir/compiler_depend.make

# Include the progress variables for this target.
include 3rd_party/eastl/CMakeFiles/eastl.dir/progress.make

# Include the compile flags for this target's objects.
include 3rd_party/eastl/CMakeFiles/eastl.dir/flags.make

3rd_party/eastl/CMakeFiles/eastl.dir/source/allocator_eastl.cpp.o: 3rd_party/eastl/CMakeFiles/eastl.dir/flags.make
3rd_party/eastl/CMakeFiles/eastl.dir/source/allocator_eastl.cpp.o: 3rd_party/eastl/source/allocator_eastl.cpp
3rd_party/eastl/CMakeFiles/eastl.dir/source/allocator_eastl.cpp.o: 3rd_party/eastl/CMakeFiles/eastl.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/egor/Desktop/gl/MotionMatching/sources/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object 3rd_party/eastl/CMakeFiles/eastl.dir/source/allocator_eastl.cpp.o"
	cd /home/egor/Desktop/gl/MotionMatching/sources/3rd_party/eastl && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT 3rd_party/eastl/CMakeFiles/eastl.dir/source/allocator_eastl.cpp.o -MF CMakeFiles/eastl.dir/source/allocator_eastl.cpp.o.d -o CMakeFiles/eastl.dir/source/allocator_eastl.cpp.o -c /home/egor/Desktop/gl/MotionMatching/sources/3rd_party/eastl/source/allocator_eastl.cpp

3rd_party/eastl/CMakeFiles/eastl.dir/source/allocator_eastl.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/eastl.dir/source/allocator_eastl.cpp.i"
	cd /home/egor/Desktop/gl/MotionMatching/sources/3rd_party/eastl && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/egor/Desktop/gl/MotionMatching/sources/3rd_party/eastl/source/allocator_eastl.cpp > CMakeFiles/eastl.dir/source/allocator_eastl.cpp.i

3rd_party/eastl/CMakeFiles/eastl.dir/source/allocator_eastl.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/eastl.dir/source/allocator_eastl.cpp.s"
	cd /home/egor/Desktop/gl/MotionMatching/sources/3rd_party/eastl && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/egor/Desktop/gl/MotionMatching/sources/3rd_party/eastl/source/allocator_eastl.cpp -o CMakeFiles/eastl.dir/source/allocator_eastl.cpp.s

3rd_party/eastl/CMakeFiles/eastl.dir/source/assert.cpp.o: 3rd_party/eastl/CMakeFiles/eastl.dir/flags.make
3rd_party/eastl/CMakeFiles/eastl.dir/source/assert.cpp.o: 3rd_party/eastl/source/assert.cpp
3rd_party/eastl/CMakeFiles/eastl.dir/source/assert.cpp.o: 3rd_party/eastl/CMakeFiles/eastl.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/egor/Desktop/gl/MotionMatching/sources/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object 3rd_party/eastl/CMakeFiles/eastl.dir/source/assert.cpp.o"
	cd /home/egor/Desktop/gl/MotionMatching/sources/3rd_party/eastl && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT 3rd_party/eastl/CMakeFiles/eastl.dir/source/assert.cpp.o -MF CMakeFiles/eastl.dir/source/assert.cpp.o.d -o CMakeFiles/eastl.dir/source/assert.cpp.o -c /home/egor/Desktop/gl/MotionMatching/sources/3rd_party/eastl/source/assert.cpp

3rd_party/eastl/CMakeFiles/eastl.dir/source/assert.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/eastl.dir/source/assert.cpp.i"
	cd /home/egor/Desktop/gl/MotionMatching/sources/3rd_party/eastl && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/egor/Desktop/gl/MotionMatching/sources/3rd_party/eastl/source/assert.cpp > CMakeFiles/eastl.dir/source/assert.cpp.i

3rd_party/eastl/CMakeFiles/eastl.dir/source/assert.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/eastl.dir/source/assert.cpp.s"
	cd /home/egor/Desktop/gl/MotionMatching/sources/3rd_party/eastl && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/egor/Desktop/gl/MotionMatching/sources/3rd_party/eastl/source/assert.cpp -o CMakeFiles/eastl.dir/source/assert.cpp.s

3rd_party/eastl/CMakeFiles/eastl.dir/source/atomic.cpp.o: 3rd_party/eastl/CMakeFiles/eastl.dir/flags.make
3rd_party/eastl/CMakeFiles/eastl.dir/source/atomic.cpp.o: 3rd_party/eastl/source/atomic.cpp
3rd_party/eastl/CMakeFiles/eastl.dir/source/atomic.cpp.o: 3rd_party/eastl/CMakeFiles/eastl.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/egor/Desktop/gl/MotionMatching/sources/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object 3rd_party/eastl/CMakeFiles/eastl.dir/source/atomic.cpp.o"
	cd /home/egor/Desktop/gl/MotionMatching/sources/3rd_party/eastl && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT 3rd_party/eastl/CMakeFiles/eastl.dir/source/atomic.cpp.o -MF CMakeFiles/eastl.dir/source/atomic.cpp.o.d -o CMakeFiles/eastl.dir/source/atomic.cpp.o -c /home/egor/Desktop/gl/MotionMatching/sources/3rd_party/eastl/source/atomic.cpp

3rd_party/eastl/CMakeFiles/eastl.dir/source/atomic.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/eastl.dir/source/atomic.cpp.i"
	cd /home/egor/Desktop/gl/MotionMatching/sources/3rd_party/eastl && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/egor/Desktop/gl/MotionMatching/sources/3rd_party/eastl/source/atomic.cpp > CMakeFiles/eastl.dir/source/atomic.cpp.i

3rd_party/eastl/CMakeFiles/eastl.dir/source/atomic.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/eastl.dir/source/atomic.cpp.s"
	cd /home/egor/Desktop/gl/MotionMatching/sources/3rd_party/eastl && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/egor/Desktop/gl/MotionMatching/sources/3rd_party/eastl/source/atomic.cpp -o CMakeFiles/eastl.dir/source/atomic.cpp.s

3rd_party/eastl/CMakeFiles/eastl.dir/source/fixed_pool.cpp.o: 3rd_party/eastl/CMakeFiles/eastl.dir/flags.make
3rd_party/eastl/CMakeFiles/eastl.dir/source/fixed_pool.cpp.o: 3rd_party/eastl/source/fixed_pool.cpp
3rd_party/eastl/CMakeFiles/eastl.dir/source/fixed_pool.cpp.o: 3rd_party/eastl/CMakeFiles/eastl.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/egor/Desktop/gl/MotionMatching/sources/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object 3rd_party/eastl/CMakeFiles/eastl.dir/source/fixed_pool.cpp.o"
	cd /home/egor/Desktop/gl/MotionMatching/sources/3rd_party/eastl && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT 3rd_party/eastl/CMakeFiles/eastl.dir/source/fixed_pool.cpp.o -MF CMakeFiles/eastl.dir/source/fixed_pool.cpp.o.d -o CMakeFiles/eastl.dir/source/fixed_pool.cpp.o -c /home/egor/Desktop/gl/MotionMatching/sources/3rd_party/eastl/source/fixed_pool.cpp

3rd_party/eastl/CMakeFiles/eastl.dir/source/fixed_pool.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/eastl.dir/source/fixed_pool.cpp.i"
	cd /home/egor/Desktop/gl/MotionMatching/sources/3rd_party/eastl && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/egor/Desktop/gl/MotionMatching/sources/3rd_party/eastl/source/fixed_pool.cpp > CMakeFiles/eastl.dir/source/fixed_pool.cpp.i

3rd_party/eastl/CMakeFiles/eastl.dir/source/fixed_pool.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/eastl.dir/source/fixed_pool.cpp.s"
	cd /home/egor/Desktop/gl/MotionMatching/sources/3rd_party/eastl && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/egor/Desktop/gl/MotionMatching/sources/3rd_party/eastl/source/fixed_pool.cpp -o CMakeFiles/eastl.dir/source/fixed_pool.cpp.s

3rd_party/eastl/CMakeFiles/eastl.dir/source/hashtable.cpp.o: 3rd_party/eastl/CMakeFiles/eastl.dir/flags.make
3rd_party/eastl/CMakeFiles/eastl.dir/source/hashtable.cpp.o: 3rd_party/eastl/source/hashtable.cpp
3rd_party/eastl/CMakeFiles/eastl.dir/source/hashtable.cpp.o: 3rd_party/eastl/CMakeFiles/eastl.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/egor/Desktop/gl/MotionMatching/sources/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object 3rd_party/eastl/CMakeFiles/eastl.dir/source/hashtable.cpp.o"
	cd /home/egor/Desktop/gl/MotionMatching/sources/3rd_party/eastl && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT 3rd_party/eastl/CMakeFiles/eastl.dir/source/hashtable.cpp.o -MF CMakeFiles/eastl.dir/source/hashtable.cpp.o.d -o CMakeFiles/eastl.dir/source/hashtable.cpp.o -c /home/egor/Desktop/gl/MotionMatching/sources/3rd_party/eastl/source/hashtable.cpp

3rd_party/eastl/CMakeFiles/eastl.dir/source/hashtable.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/eastl.dir/source/hashtable.cpp.i"
	cd /home/egor/Desktop/gl/MotionMatching/sources/3rd_party/eastl && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/egor/Desktop/gl/MotionMatching/sources/3rd_party/eastl/source/hashtable.cpp > CMakeFiles/eastl.dir/source/hashtable.cpp.i

3rd_party/eastl/CMakeFiles/eastl.dir/source/hashtable.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/eastl.dir/source/hashtable.cpp.s"
	cd /home/egor/Desktop/gl/MotionMatching/sources/3rd_party/eastl && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/egor/Desktop/gl/MotionMatching/sources/3rd_party/eastl/source/hashtable.cpp -o CMakeFiles/eastl.dir/source/hashtable.cpp.s

3rd_party/eastl/CMakeFiles/eastl.dir/source/intrusive_list.cpp.o: 3rd_party/eastl/CMakeFiles/eastl.dir/flags.make
3rd_party/eastl/CMakeFiles/eastl.dir/source/intrusive_list.cpp.o: 3rd_party/eastl/source/intrusive_list.cpp
3rd_party/eastl/CMakeFiles/eastl.dir/source/intrusive_list.cpp.o: 3rd_party/eastl/CMakeFiles/eastl.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/egor/Desktop/gl/MotionMatching/sources/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object 3rd_party/eastl/CMakeFiles/eastl.dir/source/intrusive_list.cpp.o"
	cd /home/egor/Desktop/gl/MotionMatching/sources/3rd_party/eastl && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT 3rd_party/eastl/CMakeFiles/eastl.dir/source/intrusive_list.cpp.o -MF CMakeFiles/eastl.dir/source/intrusive_list.cpp.o.d -o CMakeFiles/eastl.dir/source/intrusive_list.cpp.o -c /home/egor/Desktop/gl/MotionMatching/sources/3rd_party/eastl/source/intrusive_list.cpp

3rd_party/eastl/CMakeFiles/eastl.dir/source/intrusive_list.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/eastl.dir/source/intrusive_list.cpp.i"
	cd /home/egor/Desktop/gl/MotionMatching/sources/3rd_party/eastl && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/egor/Desktop/gl/MotionMatching/sources/3rd_party/eastl/source/intrusive_list.cpp > CMakeFiles/eastl.dir/source/intrusive_list.cpp.i

3rd_party/eastl/CMakeFiles/eastl.dir/source/intrusive_list.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/eastl.dir/source/intrusive_list.cpp.s"
	cd /home/egor/Desktop/gl/MotionMatching/sources/3rd_party/eastl && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/egor/Desktop/gl/MotionMatching/sources/3rd_party/eastl/source/intrusive_list.cpp -o CMakeFiles/eastl.dir/source/intrusive_list.cpp.s

3rd_party/eastl/CMakeFiles/eastl.dir/source/numeric_limits.cpp.o: 3rd_party/eastl/CMakeFiles/eastl.dir/flags.make
3rd_party/eastl/CMakeFiles/eastl.dir/source/numeric_limits.cpp.o: 3rd_party/eastl/source/numeric_limits.cpp
3rd_party/eastl/CMakeFiles/eastl.dir/source/numeric_limits.cpp.o: 3rd_party/eastl/CMakeFiles/eastl.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/egor/Desktop/gl/MotionMatching/sources/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object 3rd_party/eastl/CMakeFiles/eastl.dir/source/numeric_limits.cpp.o"
	cd /home/egor/Desktop/gl/MotionMatching/sources/3rd_party/eastl && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT 3rd_party/eastl/CMakeFiles/eastl.dir/source/numeric_limits.cpp.o -MF CMakeFiles/eastl.dir/source/numeric_limits.cpp.o.d -o CMakeFiles/eastl.dir/source/numeric_limits.cpp.o -c /home/egor/Desktop/gl/MotionMatching/sources/3rd_party/eastl/source/numeric_limits.cpp

3rd_party/eastl/CMakeFiles/eastl.dir/source/numeric_limits.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/eastl.dir/source/numeric_limits.cpp.i"
	cd /home/egor/Desktop/gl/MotionMatching/sources/3rd_party/eastl && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/egor/Desktop/gl/MotionMatching/sources/3rd_party/eastl/source/numeric_limits.cpp > CMakeFiles/eastl.dir/source/numeric_limits.cpp.i

3rd_party/eastl/CMakeFiles/eastl.dir/source/numeric_limits.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/eastl.dir/source/numeric_limits.cpp.s"
	cd /home/egor/Desktop/gl/MotionMatching/sources/3rd_party/eastl && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/egor/Desktop/gl/MotionMatching/sources/3rd_party/eastl/source/numeric_limits.cpp -o CMakeFiles/eastl.dir/source/numeric_limits.cpp.s

3rd_party/eastl/CMakeFiles/eastl.dir/source/red_black_tree.cpp.o: 3rd_party/eastl/CMakeFiles/eastl.dir/flags.make
3rd_party/eastl/CMakeFiles/eastl.dir/source/red_black_tree.cpp.o: 3rd_party/eastl/source/red_black_tree.cpp
3rd_party/eastl/CMakeFiles/eastl.dir/source/red_black_tree.cpp.o: 3rd_party/eastl/CMakeFiles/eastl.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/egor/Desktop/gl/MotionMatching/sources/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object 3rd_party/eastl/CMakeFiles/eastl.dir/source/red_black_tree.cpp.o"
	cd /home/egor/Desktop/gl/MotionMatching/sources/3rd_party/eastl && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT 3rd_party/eastl/CMakeFiles/eastl.dir/source/red_black_tree.cpp.o -MF CMakeFiles/eastl.dir/source/red_black_tree.cpp.o.d -o CMakeFiles/eastl.dir/source/red_black_tree.cpp.o -c /home/egor/Desktop/gl/MotionMatching/sources/3rd_party/eastl/source/red_black_tree.cpp

3rd_party/eastl/CMakeFiles/eastl.dir/source/red_black_tree.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/eastl.dir/source/red_black_tree.cpp.i"
	cd /home/egor/Desktop/gl/MotionMatching/sources/3rd_party/eastl && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/egor/Desktop/gl/MotionMatching/sources/3rd_party/eastl/source/red_black_tree.cpp > CMakeFiles/eastl.dir/source/red_black_tree.cpp.i

3rd_party/eastl/CMakeFiles/eastl.dir/source/red_black_tree.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/eastl.dir/source/red_black_tree.cpp.s"
	cd /home/egor/Desktop/gl/MotionMatching/sources/3rd_party/eastl && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/egor/Desktop/gl/MotionMatching/sources/3rd_party/eastl/source/red_black_tree.cpp -o CMakeFiles/eastl.dir/source/red_black_tree.cpp.s

3rd_party/eastl/CMakeFiles/eastl.dir/source/string.cpp.o: 3rd_party/eastl/CMakeFiles/eastl.dir/flags.make
3rd_party/eastl/CMakeFiles/eastl.dir/source/string.cpp.o: 3rd_party/eastl/source/string.cpp
3rd_party/eastl/CMakeFiles/eastl.dir/source/string.cpp.o: 3rd_party/eastl/CMakeFiles/eastl.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/egor/Desktop/gl/MotionMatching/sources/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object 3rd_party/eastl/CMakeFiles/eastl.dir/source/string.cpp.o"
	cd /home/egor/Desktop/gl/MotionMatching/sources/3rd_party/eastl && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT 3rd_party/eastl/CMakeFiles/eastl.dir/source/string.cpp.o -MF CMakeFiles/eastl.dir/source/string.cpp.o.d -o CMakeFiles/eastl.dir/source/string.cpp.o -c /home/egor/Desktop/gl/MotionMatching/sources/3rd_party/eastl/source/string.cpp

3rd_party/eastl/CMakeFiles/eastl.dir/source/string.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/eastl.dir/source/string.cpp.i"
	cd /home/egor/Desktop/gl/MotionMatching/sources/3rd_party/eastl && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/egor/Desktop/gl/MotionMatching/sources/3rd_party/eastl/source/string.cpp > CMakeFiles/eastl.dir/source/string.cpp.i

3rd_party/eastl/CMakeFiles/eastl.dir/source/string.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/eastl.dir/source/string.cpp.s"
	cd /home/egor/Desktop/gl/MotionMatching/sources/3rd_party/eastl && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/egor/Desktop/gl/MotionMatching/sources/3rd_party/eastl/source/string.cpp -o CMakeFiles/eastl.dir/source/string.cpp.s

3rd_party/eastl/CMakeFiles/eastl.dir/source/thread_support.cpp.o: 3rd_party/eastl/CMakeFiles/eastl.dir/flags.make
3rd_party/eastl/CMakeFiles/eastl.dir/source/thread_support.cpp.o: 3rd_party/eastl/source/thread_support.cpp
3rd_party/eastl/CMakeFiles/eastl.dir/source/thread_support.cpp.o: 3rd_party/eastl/CMakeFiles/eastl.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/egor/Desktop/gl/MotionMatching/sources/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building CXX object 3rd_party/eastl/CMakeFiles/eastl.dir/source/thread_support.cpp.o"
	cd /home/egor/Desktop/gl/MotionMatching/sources/3rd_party/eastl && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT 3rd_party/eastl/CMakeFiles/eastl.dir/source/thread_support.cpp.o -MF CMakeFiles/eastl.dir/source/thread_support.cpp.o.d -o CMakeFiles/eastl.dir/source/thread_support.cpp.o -c /home/egor/Desktop/gl/MotionMatching/sources/3rd_party/eastl/source/thread_support.cpp

3rd_party/eastl/CMakeFiles/eastl.dir/source/thread_support.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/eastl.dir/source/thread_support.cpp.i"
	cd /home/egor/Desktop/gl/MotionMatching/sources/3rd_party/eastl && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/egor/Desktop/gl/MotionMatching/sources/3rd_party/eastl/source/thread_support.cpp > CMakeFiles/eastl.dir/source/thread_support.cpp.i

3rd_party/eastl/CMakeFiles/eastl.dir/source/thread_support.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/eastl.dir/source/thread_support.cpp.s"
	cd /home/egor/Desktop/gl/MotionMatching/sources/3rd_party/eastl && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/egor/Desktop/gl/MotionMatching/sources/3rd_party/eastl/source/thread_support.cpp -o CMakeFiles/eastl.dir/source/thread_support.cpp.s

eastl: 3rd_party/eastl/CMakeFiles/eastl.dir/source/allocator_eastl.cpp.o
eastl: 3rd_party/eastl/CMakeFiles/eastl.dir/source/assert.cpp.o
eastl: 3rd_party/eastl/CMakeFiles/eastl.dir/source/atomic.cpp.o
eastl: 3rd_party/eastl/CMakeFiles/eastl.dir/source/fixed_pool.cpp.o
eastl: 3rd_party/eastl/CMakeFiles/eastl.dir/source/hashtable.cpp.o
eastl: 3rd_party/eastl/CMakeFiles/eastl.dir/source/intrusive_list.cpp.o
eastl: 3rd_party/eastl/CMakeFiles/eastl.dir/source/numeric_limits.cpp.o
eastl: 3rd_party/eastl/CMakeFiles/eastl.dir/source/red_black_tree.cpp.o
eastl: 3rd_party/eastl/CMakeFiles/eastl.dir/source/string.cpp.o
eastl: 3rd_party/eastl/CMakeFiles/eastl.dir/source/thread_support.cpp.o
eastl: 3rd_party/eastl/CMakeFiles/eastl.dir/build.make
.PHONY : eastl

# Rule to build all files generated by this target.
3rd_party/eastl/CMakeFiles/eastl.dir/build: eastl
.PHONY : 3rd_party/eastl/CMakeFiles/eastl.dir/build

3rd_party/eastl/CMakeFiles/eastl.dir/clean:
	cd /home/egor/Desktop/gl/MotionMatching/sources/3rd_party/eastl && $(CMAKE_COMMAND) -P CMakeFiles/eastl.dir/cmake_clean.cmake
.PHONY : 3rd_party/eastl/CMakeFiles/eastl.dir/clean

3rd_party/eastl/CMakeFiles/eastl.dir/depend:
	cd /home/egor/Desktop/gl/MotionMatching/sources && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/egor/Desktop/gl/MotionMatching/sources /home/egor/Desktop/gl/MotionMatching/sources/3rd_party/eastl /home/egor/Desktop/gl/MotionMatching/sources /home/egor/Desktop/gl/MotionMatching/sources/3rd_party/eastl /home/egor/Desktop/gl/MotionMatching/sources/3rd_party/eastl/CMakeFiles/eastl.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : 3rd_party/eastl/CMakeFiles/eastl.dir/depend

