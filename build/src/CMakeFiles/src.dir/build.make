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
include src/CMakeFiles/src.dir/depend.make

# Include the progress variables for this target.
include src/CMakeFiles/src.dir/progress.make

# Include the compile flags for this target's objects.
include src/CMakeFiles/src.dir/flags.make

src/CMakeFiles/src.dir/EventLoop.cc.o: src/CMakeFiles/src.dir/flags.make
src/CMakeFiles/src.dir/EventLoop.cc.o: ../src/EventLoop.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/hgfs/self_study/MyPro/libnet/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/CMakeFiles/src.dir/EventLoop.cc.o"
	cd /mnt/hgfs/self_study/MyPro/libnet/build/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/src.dir/EventLoop.cc.o -c /mnt/hgfs/self_study/MyPro/libnet/src/EventLoop.cc

src/CMakeFiles/src.dir/EventLoop.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/src.dir/EventLoop.cc.i"
	cd /mnt/hgfs/self_study/MyPro/libnet/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/hgfs/self_study/MyPro/libnet/src/EventLoop.cc > CMakeFiles/src.dir/EventLoop.cc.i

src/CMakeFiles/src.dir/EventLoop.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/src.dir/EventLoop.cc.s"
	cd /mnt/hgfs/self_study/MyPro/libnet/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/hgfs/self_study/MyPro/libnet/src/EventLoop.cc -o CMakeFiles/src.dir/EventLoop.cc.s

src/CMakeFiles/src.dir/EPoller.cc.o: src/CMakeFiles/src.dir/flags.make
src/CMakeFiles/src.dir/EPoller.cc.o: ../src/EPoller.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/hgfs/self_study/MyPro/libnet/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object src/CMakeFiles/src.dir/EPoller.cc.o"
	cd /mnt/hgfs/self_study/MyPro/libnet/build/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/src.dir/EPoller.cc.o -c /mnt/hgfs/self_study/MyPro/libnet/src/EPoller.cc

src/CMakeFiles/src.dir/EPoller.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/src.dir/EPoller.cc.i"
	cd /mnt/hgfs/self_study/MyPro/libnet/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/hgfs/self_study/MyPro/libnet/src/EPoller.cc > CMakeFiles/src.dir/EPoller.cc.i

src/CMakeFiles/src.dir/EPoller.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/src.dir/EPoller.cc.s"
	cd /mnt/hgfs/self_study/MyPro/libnet/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/hgfs/self_study/MyPro/libnet/src/EPoller.cc -o CMakeFiles/src.dir/EPoller.cc.s

src/CMakeFiles/src.dir/Channel.cc.o: src/CMakeFiles/src.dir/flags.make
src/CMakeFiles/src.dir/Channel.cc.o: ../src/Channel.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/hgfs/self_study/MyPro/libnet/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object src/CMakeFiles/src.dir/Channel.cc.o"
	cd /mnt/hgfs/self_study/MyPro/libnet/build/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/src.dir/Channel.cc.o -c /mnt/hgfs/self_study/MyPro/libnet/src/Channel.cc

src/CMakeFiles/src.dir/Channel.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/src.dir/Channel.cc.i"
	cd /mnt/hgfs/self_study/MyPro/libnet/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/hgfs/self_study/MyPro/libnet/src/Channel.cc > CMakeFiles/src.dir/Channel.cc.i

src/CMakeFiles/src.dir/Channel.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/src.dir/Channel.cc.s"
	cd /mnt/hgfs/self_study/MyPro/libnet/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/hgfs/self_study/MyPro/libnet/src/Channel.cc -o CMakeFiles/src.dir/Channel.cc.s

src/CMakeFiles/src.dir/Logger.c.o: src/CMakeFiles/src.dir/flags.make
src/CMakeFiles/src.dir/Logger.c.o: ../src/Logger.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/hgfs/self_study/MyPro/libnet/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object src/CMakeFiles/src.dir/Logger.c.o"
	cd /mnt/hgfs/self_study/MyPro/libnet/build/src && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/src.dir/Logger.c.o   -c /mnt/hgfs/self_study/MyPro/libnet/src/Logger.c

src/CMakeFiles/src.dir/Logger.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/src.dir/Logger.c.i"
	cd /mnt/hgfs/self_study/MyPro/libnet/build/src && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /mnt/hgfs/self_study/MyPro/libnet/src/Logger.c > CMakeFiles/src.dir/Logger.c.i

src/CMakeFiles/src.dir/Logger.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/src.dir/Logger.c.s"
	cd /mnt/hgfs/self_study/MyPro/libnet/build/src && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /mnt/hgfs/self_study/MyPro/libnet/src/Logger.c -o CMakeFiles/src.dir/Logger.c.s

src/CMakeFiles/src.dir/Acceptor.cc.o: src/CMakeFiles/src.dir/flags.make
src/CMakeFiles/src.dir/Acceptor.cc.o: ../src/Acceptor.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/hgfs/self_study/MyPro/libnet/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object src/CMakeFiles/src.dir/Acceptor.cc.o"
	cd /mnt/hgfs/self_study/MyPro/libnet/build/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/src.dir/Acceptor.cc.o -c /mnt/hgfs/self_study/MyPro/libnet/src/Acceptor.cc

src/CMakeFiles/src.dir/Acceptor.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/src.dir/Acceptor.cc.i"
	cd /mnt/hgfs/self_study/MyPro/libnet/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/hgfs/self_study/MyPro/libnet/src/Acceptor.cc > CMakeFiles/src.dir/Acceptor.cc.i

src/CMakeFiles/src.dir/Acceptor.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/src.dir/Acceptor.cc.s"
	cd /mnt/hgfs/self_study/MyPro/libnet/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/hgfs/self_study/MyPro/libnet/src/Acceptor.cc -o CMakeFiles/src.dir/Acceptor.cc.s

src/CMakeFiles/src.dir/InetAddress.cc.o: src/CMakeFiles/src.dir/flags.make
src/CMakeFiles/src.dir/InetAddress.cc.o: ../src/InetAddress.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/hgfs/self_study/MyPro/libnet/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object src/CMakeFiles/src.dir/InetAddress.cc.o"
	cd /mnt/hgfs/self_study/MyPro/libnet/build/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/src.dir/InetAddress.cc.o -c /mnt/hgfs/self_study/MyPro/libnet/src/InetAddress.cc

src/CMakeFiles/src.dir/InetAddress.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/src.dir/InetAddress.cc.i"
	cd /mnt/hgfs/self_study/MyPro/libnet/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/hgfs/self_study/MyPro/libnet/src/InetAddress.cc > CMakeFiles/src.dir/InetAddress.cc.i

src/CMakeFiles/src.dir/InetAddress.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/src.dir/InetAddress.cc.s"
	cd /mnt/hgfs/self_study/MyPro/libnet/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/hgfs/self_study/MyPro/libnet/src/InetAddress.cc -o CMakeFiles/src.dir/InetAddress.cc.s

src/CMakeFiles/src.dir/TcpConnection.cc.o: src/CMakeFiles/src.dir/flags.make
src/CMakeFiles/src.dir/TcpConnection.cc.o: ../src/TcpConnection.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/hgfs/self_study/MyPro/libnet/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object src/CMakeFiles/src.dir/TcpConnection.cc.o"
	cd /mnt/hgfs/self_study/MyPro/libnet/build/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/src.dir/TcpConnection.cc.o -c /mnt/hgfs/self_study/MyPro/libnet/src/TcpConnection.cc

src/CMakeFiles/src.dir/TcpConnection.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/src.dir/TcpConnection.cc.i"
	cd /mnt/hgfs/self_study/MyPro/libnet/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/hgfs/self_study/MyPro/libnet/src/TcpConnection.cc > CMakeFiles/src.dir/TcpConnection.cc.i

src/CMakeFiles/src.dir/TcpConnection.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/src.dir/TcpConnection.cc.s"
	cd /mnt/hgfs/self_study/MyPro/libnet/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/hgfs/self_study/MyPro/libnet/src/TcpConnection.cc -o CMakeFiles/src.dir/TcpConnection.cc.s

src/CMakeFiles/src.dir/TcpServerSingle.cc.o: src/CMakeFiles/src.dir/flags.make
src/CMakeFiles/src.dir/TcpServerSingle.cc.o: ../src/TcpServerSingle.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/hgfs/self_study/MyPro/libnet/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object src/CMakeFiles/src.dir/TcpServerSingle.cc.o"
	cd /mnt/hgfs/self_study/MyPro/libnet/build/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/src.dir/TcpServerSingle.cc.o -c /mnt/hgfs/self_study/MyPro/libnet/src/TcpServerSingle.cc

src/CMakeFiles/src.dir/TcpServerSingle.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/src.dir/TcpServerSingle.cc.i"
	cd /mnt/hgfs/self_study/MyPro/libnet/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/hgfs/self_study/MyPro/libnet/src/TcpServerSingle.cc > CMakeFiles/src.dir/TcpServerSingle.cc.i

src/CMakeFiles/src.dir/TcpServerSingle.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/src.dir/TcpServerSingle.cc.s"
	cd /mnt/hgfs/self_study/MyPro/libnet/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/hgfs/self_study/MyPro/libnet/src/TcpServerSingle.cc -o CMakeFiles/src.dir/TcpServerSingle.cc.s

src/CMakeFiles/src.dir/TcpServer.cc.o: src/CMakeFiles/src.dir/flags.make
src/CMakeFiles/src.dir/TcpServer.cc.o: ../src/TcpServer.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/hgfs/self_study/MyPro/libnet/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object src/CMakeFiles/src.dir/TcpServer.cc.o"
	cd /mnt/hgfs/self_study/MyPro/libnet/build/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/src.dir/TcpServer.cc.o -c /mnt/hgfs/self_study/MyPro/libnet/src/TcpServer.cc

src/CMakeFiles/src.dir/TcpServer.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/src.dir/TcpServer.cc.i"
	cd /mnt/hgfs/self_study/MyPro/libnet/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/hgfs/self_study/MyPro/libnet/src/TcpServer.cc > CMakeFiles/src.dir/TcpServer.cc.i

src/CMakeFiles/src.dir/TcpServer.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/src.dir/TcpServer.cc.s"
	cd /mnt/hgfs/self_study/MyPro/libnet/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/hgfs/self_study/MyPro/libnet/src/TcpServer.cc -o CMakeFiles/src.dir/TcpServer.cc.s

src/CMakeFiles/src.dir/Buffer.cc.o: src/CMakeFiles/src.dir/flags.make
src/CMakeFiles/src.dir/Buffer.cc.o: ../src/Buffer.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/hgfs/self_study/MyPro/libnet/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building CXX object src/CMakeFiles/src.dir/Buffer.cc.o"
	cd /mnt/hgfs/self_study/MyPro/libnet/build/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/src.dir/Buffer.cc.o -c /mnt/hgfs/self_study/MyPro/libnet/src/Buffer.cc

src/CMakeFiles/src.dir/Buffer.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/src.dir/Buffer.cc.i"
	cd /mnt/hgfs/self_study/MyPro/libnet/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/hgfs/self_study/MyPro/libnet/src/Buffer.cc > CMakeFiles/src.dir/Buffer.cc.i

src/CMakeFiles/src.dir/Buffer.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/src.dir/Buffer.cc.s"
	cd /mnt/hgfs/self_study/MyPro/libnet/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/hgfs/self_study/MyPro/libnet/src/Buffer.cc -o CMakeFiles/src.dir/Buffer.cc.s

src/CMakeFiles/src.dir/ThreadPool.cc.o: src/CMakeFiles/src.dir/flags.make
src/CMakeFiles/src.dir/ThreadPool.cc.o: ../src/ThreadPool.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/hgfs/self_study/MyPro/libnet/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Building CXX object src/CMakeFiles/src.dir/ThreadPool.cc.o"
	cd /mnt/hgfs/self_study/MyPro/libnet/build/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/src.dir/ThreadPool.cc.o -c /mnt/hgfs/self_study/MyPro/libnet/src/ThreadPool.cc

src/CMakeFiles/src.dir/ThreadPool.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/src.dir/ThreadPool.cc.i"
	cd /mnt/hgfs/self_study/MyPro/libnet/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/hgfs/self_study/MyPro/libnet/src/ThreadPool.cc > CMakeFiles/src.dir/ThreadPool.cc.i

src/CMakeFiles/src.dir/ThreadPool.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/src.dir/ThreadPool.cc.s"
	cd /mnt/hgfs/self_study/MyPro/libnet/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/hgfs/self_study/MyPro/libnet/src/ThreadPool.cc -o CMakeFiles/src.dir/ThreadPool.cc.s

src/CMakeFiles/src.dir/Connector.cc.o: src/CMakeFiles/src.dir/flags.make
src/CMakeFiles/src.dir/Connector.cc.o: ../src/Connector.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/hgfs/self_study/MyPro/libnet/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_12) "Building CXX object src/CMakeFiles/src.dir/Connector.cc.o"
	cd /mnt/hgfs/self_study/MyPro/libnet/build/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/src.dir/Connector.cc.o -c /mnt/hgfs/self_study/MyPro/libnet/src/Connector.cc

src/CMakeFiles/src.dir/Connector.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/src.dir/Connector.cc.i"
	cd /mnt/hgfs/self_study/MyPro/libnet/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/hgfs/self_study/MyPro/libnet/src/Connector.cc > CMakeFiles/src.dir/Connector.cc.i

src/CMakeFiles/src.dir/Connector.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/src.dir/Connector.cc.s"
	cd /mnt/hgfs/self_study/MyPro/libnet/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/hgfs/self_study/MyPro/libnet/src/Connector.cc -o CMakeFiles/src.dir/Connector.cc.s

src/CMakeFiles/src.dir/TcpClient.cc.o: src/CMakeFiles/src.dir/flags.make
src/CMakeFiles/src.dir/TcpClient.cc.o: ../src/TcpClient.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/hgfs/self_study/MyPro/libnet/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_13) "Building CXX object src/CMakeFiles/src.dir/TcpClient.cc.o"
	cd /mnt/hgfs/self_study/MyPro/libnet/build/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/src.dir/TcpClient.cc.o -c /mnt/hgfs/self_study/MyPro/libnet/src/TcpClient.cc

src/CMakeFiles/src.dir/TcpClient.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/src.dir/TcpClient.cc.i"
	cd /mnt/hgfs/self_study/MyPro/libnet/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/hgfs/self_study/MyPro/libnet/src/TcpClient.cc > CMakeFiles/src.dir/TcpClient.cc.i

src/CMakeFiles/src.dir/TcpClient.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/src.dir/TcpClient.cc.s"
	cd /mnt/hgfs/self_study/MyPro/libnet/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/hgfs/self_study/MyPro/libnet/src/TcpClient.cc -o CMakeFiles/src.dir/TcpClient.cc.s

src/CMakeFiles/src.dir/EventLoopThread.cc.o: src/CMakeFiles/src.dir/flags.make
src/CMakeFiles/src.dir/EventLoopThread.cc.o: ../src/EventLoopThread.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/hgfs/self_study/MyPro/libnet/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_14) "Building CXX object src/CMakeFiles/src.dir/EventLoopThread.cc.o"
	cd /mnt/hgfs/self_study/MyPro/libnet/build/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/src.dir/EventLoopThread.cc.o -c /mnt/hgfs/self_study/MyPro/libnet/src/EventLoopThread.cc

src/CMakeFiles/src.dir/EventLoopThread.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/src.dir/EventLoopThread.cc.i"
	cd /mnt/hgfs/self_study/MyPro/libnet/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/hgfs/self_study/MyPro/libnet/src/EventLoopThread.cc > CMakeFiles/src.dir/EventLoopThread.cc.i

src/CMakeFiles/src.dir/EventLoopThread.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/src.dir/EventLoopThread.cc.s"
	cd /mnt/hgfs/self_study/MyPro/libnet/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/hgfs/self_study/MyPro/libnet/src/EventLoopThread.cc -o CMakeFiles/src.dir/EventLoopThread.cc.s

src/CMakeFiles/src.dir/TimerQueue.cc.o: src/CMakeFiles/src.dir/flags.make
src/CMakeFiles/src.dir/TimerQueue.cc.o: ../src/TimerQueue.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/hgfs/self_study/MyPro/libnet/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_15) "Building CXX object src/CMakeFiles/src.dir/TimerQueue.cc.o"
	cd /mnt/hgfs/self_study/MyPro/libnet/build/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/src.dir/TimerQueue.cc.o -c /mnt/hgfs/self_study/MyPro/libnet/src/TimerQueue.cc

src/CMakeFiles/src.dir/TimerQueue.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/src.dir/TimerQueue.cc.i"
	cd /mnt/hgfs/self_study/MyPro/libnet/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/hgfs/self_study/MyPro/libnet/src/TimerQueue.cc > CMakeFiles/src.dir/TimerQueue.cc.i

src/CMakeFiles/src.dir/TimerQueue.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/src.dir/TimerQueue.cc.s"
	cd /mnt/hgfs/self_study/MyPro/libnet/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/hgfs/self_study/MyPro/libnet/src/TimerQueue.cc -o CMakeFiles/src.dir/TimerQueue.cc.s

# Object files for target src
src_OBJECTS = \
"CMakeFiles/src.dir/EventLoop.cc.o" \
"CMakeFiles/src.dir/EPoller.cc.o" \
"CMakeFiles/src.dir/Channel.cc.o" \
"CMakeFiles/src.dir/Logger.c.o" \
"CMakeFiles/src.dir/Acceptor.cc.o" \
"CMakeFiles/src.dir/InetAddress.cc.o" \
"CMakeFiles/src.dir/TcpConnection.cc.o" \
"CMakeFiles/src.dir/TcpServerSingle.cc.o" \
"CMakeFiles/src.dir/TcpServer.cc.o" \
"CMakeFiles/src.dir/Buffer.cc.o" \
"CMakeFiles/src.dir/ThreadPool.cc.o" \
"CMakeFiles/src.dir/Connector.cc.o" \
"CMakeFiles/src.dir/TcpClient.cc.o" \
"CMakeFiles/src.dir/EventLoopThread.cc.o" \
"CMakeFiles/src.dir/TimerQueue.cc.o"

# External object files for target src
src_EXTERNAL_OBJECTS =

lib/libsrc.a: src/CMakeFiles/src.dir/EventLoop.cc.o
lib/libsrc.a: src/CMakeFiles/src.dir/EPoller.cc.o
lib/libsrc.a: src/CMakeFiles/src.dir/Channel.cc.o
lib/libsrc.a: src/CMakeFiles/src.dir/Logger.c.o
lib/libsrc.a: src/CMakeFiles/src.dir/Acceptor.cc.o
lib/libsrc.a: src/CMakeFiles/src.dir/InetAddress.cc.o
lib/libsrc.a: src/CMakeFiles/src.dir/TcpConnection.cc.o
lib/libsrc.a: src/CMakeFiles/src.dir/TcpServerSingle.cc.o
lib/libsrc.a: src/CMakeFiles/src.dir/TcpServer.cc.o
lib/libsrc.a: src/CMakeFiles/src.dir/Buffer.cc.o
lib/libsrc.a: src/CMakeFiles/src.dir/ThreadPool.cc.o
lib/libsrc.a: src/CMakeFiles/src.dir/Connector.cc.o
lib/libsrc.a: src/CMakeFiles/src.dir/TcpClient.cc.o
lib/libsrc.a: src/CMakeFiles/src.dir/EventLoopThread.cc.o
lib/libsrc.a: src/CMakeFiles/src.dir/TimerQueue.cc.o
lib/libsrc.a: src/CMakeFiles/src.dir/build.make
lib/libsrc.a: src/CMakeFiles/src.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/mnt/hgfs/self_study/MyPro/libnet/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_16) "Linking CXX static library ../lib/libsrc.a"
	cd /mnt/hgfs/self_study/MyPro/libnet/build/src && $(CMAKE_COMMAND) -P CMakeFiles/src.dir/cmake_clean_target.cmake
	cd /mnt/hgfs/self_study/MyPro/libnet/build/src && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/src.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/CMakeFiles/src.dir/build: lib/libsrc.a

.PHONY : src/CMakeFiles/src.dir/build

src/CMakeFiles/src.dir/clean:
	cd /mnt/hgfs/self_study/MyPro/libnet/build/src && $(CMAKE_COMMAND) -P CMakeFiles/src.dir/cmake_clean.cmake
.PHONY : src/CMakeFiles/src.dir/clean

src/CMakeFiles/src.dir/depend:
	cd /mnt/hgfs/self_study/MyPro/libnet/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /mnt/hgfs/self_study/MyPro/libnet /mnt/hgfs/self_study/MyPro/libnet/src /mnt/hgfs/self_study/MyPro/libnet/build /mnt/hgfs/self_study/MyPro/libnet/build/src /mnt/hgfs/self_study/MyPro/libnet/build/src/CMakeFiles/src.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/CMakeFiles/src.dir/depend
