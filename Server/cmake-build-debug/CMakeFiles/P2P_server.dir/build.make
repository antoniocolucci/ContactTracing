# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.20

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
CMAKE_COMMAND = /snap/clion/163/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /snap/clion/163/bin/cmake/linux/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/saso/CLionProjects/ContactTracing/Server

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/saso/CLionProjects/ContactTracing/Server/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/P2P_server.dir/depend.make
# Include the progress variables for this target.
include CMakeFiles/P2P_server.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/P2P_server.dir/flags.make

CMakeFiles/P2P_server.dir/main.c.o: CMakeFiles/P2P_server.dir/flags.make
CMakeFiles/P2P_server.dir/main.c.o: ../main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/saso/CLionProjects/ContactTracing/Server/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/P2P_server.dir/main.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/P2P_server.dir/main.c.o -c /home/saso/CLionProjects/ContactTracing/Server/main.c

CMakeFiles/P2P_server.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/P2P_server.dir/main.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/saso/CLionProjects/ContactTracing/Server/main.c > CMakeFiles/P2P_server.dir/main.c.i

CMakeFiles/P2P_server.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/P2P_server.dir/main.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/saso/CLionProjects/ContactTracing/Server/main.c -o CMakeFiles/P2P_server.dir/main.c.s

CMakeFiles/P2P_server.dir/server.c.o: CMakeFiles/P2P_server.dir/flags.make
CMakeFiles/P2P_server.dir/server.c.o: ../server.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/saso/CLionProjects/ContactTracing/Server/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/P2P_server.dir/server.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/P2P_server.dir/server.c.o -c /home/saso/CLionProjects/ContactTracing/Server/server.c

CMakeFiles/P2P_server.dir/server.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/P2P_server.dir/server.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/saso/CLionProjects/ContactTracing/Server/server.c > CMakeFiles/P2P_server.dir/server.c.i

CMakeFiles/P2P_server.dir/server.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/P2P_server.dir/server.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/saso/CLionProjects/ContactTracing/Server/server.c -o CMakeFiles/P2P_server.dir/server.c.s

# Object files for target P2P_server
P2P_server_OBJECTS = \
"CMakeFiles/P2P_server.dir/main.c.o" \
"CMakeFiles/P2P_server.dir/server.c.o"

# External object files for target P2P_server
P2P_server_EXTERNAL_OBJECTS =

P2P_server: CMakeFiles/P2P_server.dir/main.c.o
P2P_server: CMakeFiles/P2P_server.dir/server.c.o
P2P_server: CMakeFiles/P2P_server.dir/build.make
P2P_server: CMakeFiles/P2P_server.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/saso/CLionProjects/ContactTracing/Server/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking C executable P2P_server"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/P2P_server.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/P2P_server.dir/build: P2P_server
.PHONY : CMakeFiles/P2P_server.dir/build

CMakeFiles/P2P_server.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/P2P_server.dir/cmake_clean.cmake
.PHONY : CMakeFiles/P2P_server.dir/clean

CMakeFiles/P2P_server.dir/depend:
	cd /home/saso/CLionProjects/ContactTracing/Server/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/saso/CLionProjects/ContactTracing/Server /home/saso/CLionProjects/ContactTracing/Server /home/saso/CLionProjects/ContactTracing/Server/cmake-build-debug /home/saso/CLionProjects/ContactTracing/Server/cmake-build-debug /home/saso/CLionProjects/ContactTracing/Server/cmake-build-debug/CMakeFiles/P2P_server.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/P2P_server.dir/depend

