# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /mnt/hgfs/self_study/MyPro/libnet

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /mnt/hgfs/self_study/MyPro/libnet/build

# Include any dependencies generated for this target.
include example/CMakeFiles/timer.dir/depend.make

# Include the progress variables for this target.
include example/CMakeFiles/timer.dir/progress.make

# Include the compile flags for this target's objects.
include example/CMakeFiles/timer.dir/flags.make

example/CMakeFiles/timer.dir/TimerLoop.cc.o: example/CMakeFiles/timer.dir/flags.make
example/CMakeFiles/timer.dir/TimerLoop.cc.o: ../example/TimerLoop.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/hgfs/self_study/MyPro/libnet/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object example/CMakeFiles/timer.dir/TimerLoop.cc.o"
	cd /mnt/hgfs/self_study/MyPro/libnet/build/example && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/timer.dir/TimerLoop.cc.o -c /mnt/hgfs/self_study/MyPro/libnet/example/TimerLoop.cc

example/CMakeFiles/timer.dir/TimerLoop.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/timer.dir/TimerLoop.cc.i"
	cd /mnt/hgfs/self_study/MyPro/libnet/build/example && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/hgfs/self_study/MyPro/libnet/example/TimerLoop.cc > CMakeFiles/timer.dir/TimerLoop.cc.i

example/CMakeFiles/timer.dir/TimerLoop.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/timer.dir/TimerLoop.cc.s"
	cd /mnt/hgfs/self_study/MyPro/libnet/build/example && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/hgfs/self_study/MyPro/libnet/example/TimerLoop.cc -o CMakeFiles/timer.dir/TimerLoop.cc.s

# Object files for target timer
timer_OBJECTS = \
"CMakeFiles/timer.dir/TimerLoop.cc.o"

# External object files for target timer
timer_EXTERNAL_OBJECTS =

bin/timer: example/CMakeFiles/timer.dir/TimerLoop.cc.o
bin/timer: example/CMakeFiles/timer.dir/build.make
bin/timer: lib/libsrc.a
bin/timer: example/CMakeFiles/timer.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/mnt/hgfs/self_study/MyPro/libnet/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ../bin/timer"
	cd /mnt/hgfs/self_study/MyPro/libnet/build/example && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/timer.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
example/CMakeFiles/timer.dir/build: bin/timer

.PHONY : example/CMakeFiles/timer.dir/build

example/CMakeFiles/timer.dir/clean:
	cd /mnt/hgfs/self_study/MyPro/libnet/build/example && $(CMAKE_COMMAND) -P CMakeFiles/timer.dir/cmake_clean.cmake
.PHONY : example/CMakeFiles/timer.dir/clean

example/CMakeFiles/timer.dir/depend:
	cd /mnt/hgfs/self_study/MyPro/libnet/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /mnt/hgfs/self_study/MyPro/libnet /mnt/hgfs/self_study/MyPro/libnet/example /mnt/hgfs/self_study/MyPro/libnet/build /mnt/hgfs/self_study/MyPro/libnet/build/example /mnt/hgfs/self_study/MyPro/libnet/build/example/CMakeFiles/timer.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : example/CMakeFiles/timer.dir/depend

