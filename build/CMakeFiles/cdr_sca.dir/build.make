# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.12

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
CMAKE_COMMAND = /home/maxim/Downloads/cmake-3.12.0/bin/cmake

# The command to remove a file.
RM = /home/maxim/Downloads/cmake-3.12.0/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /opt/svyazcom/cdr_sca

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /opt/svyazcom/cdr_sca/build

# Include any dependencies generated for this target.
include CMakeFiles/cdr_sca.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/cdr_sca.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/cdr_sca.dir/flags.make

CMakeFiles/cdr_sca.dir/main.cpp.o: CMakeFiles/cdr_sca.dir/flags.make
CMakeFiles/cdr_sca.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/opt/svyazcom/cdr_sca/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/cdr_sca.dir/main.cpp.o"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/cdr_sca.dir/main.cpp.o -c /opt/svyazcom/cdr_sca/main.cpp

CMakeFiles/cdr_sca.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/cdr_sca.dir/main.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /opt/svyazcom/cdr_sca/main.cpp > CMakeFiles/cdr_sca.dir/main.cpp.i

CMakeFiles/cdr_sca.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/cdr_sca.dir/main.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /opt/svyazcom/cdr_sca/main.cpp -o CMakeFiles/cdr_sca.dir/main.cpp.s

CMakeFiles/cdr_sca.dir/parser.cpp.o: CMakeFiles/cdr_sca.dir/flags.make
CMakeFiles/cdr_sca.dir/parser.cpp.o: ../parser.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/opt/svyazcom/cdr_sca/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/cdr_sca.dir/parser.cpp.o"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/cdr_sca.dir/parser.cpp.o -c /opt/svyazcom/cdr_sca/parser.cpp

CMakeFiles/cdr_sca.dir/parser.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/cdr_sca.dir/parser.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /opt/svyazcom/cdr_sca/parser.cpp > CMakeFiles/cdr_sca.dir/parser.cpp.i

CMakeFiles/cdr_sca.dir/parser.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/cdr_sca.dir/parser.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /opt/svyazcom/cdr_sca/parser.cpp -o CMakeFiles/cdr_sca.dir/parser.cpp.s

CMakeFiles/cdr_sca.dir/worker_cnora.cpp.o: CMakeFiles/cdr_sca.dir/flags.make
CMakeFiles/cdr_sca.dir/worker_cnora.cpp.o: ../worker_cnora.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/opt/svyazcom/cdr_sca/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/cdr_sca.dir/worker_cnora.cpp.o"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/cdr_sca.dir/worker_cnora.cpp.o -c /opt/svyazcom/cdr_sca/worker_cnora.cpp

CMakeFiles/cdr_sca.dir/worker_cnora.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/cdr_sca.dir/worker_cnora.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /opt/svyazcom/cdr_sca/worker_cnora.cpp > CMakeFiles/cdr_sca.dir/worker_cnora.cpp.i

CMakeFiles/cdr_sca.dir/worker_cnora.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/cdr_sca.dir/worker_cnora.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /opt/svyazcom/cdr_sca/worker_cnora.cpp -o CMakeFiles/cdr_sca.dir/worker_cnora.cpp.s

CMakeFiles/cdr_sca.dir/working_file.cpp.o: CMakeFiles/cdr_sca.dir/flags.make
CMakeFiles/cdr_sca.dir/working_file.cpp.o: ../working_file.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/opt/svyazcom/cdr_sca/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/cdr_sca.dir/working_file.cpp.o"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/cdr_sca.dir/working_file.cpp.o -c /opt/svyazcom/cdr_sca/working_file.cpp

CMakeFiles/cdr_sca.dir/working_file.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/cdr_sca.dir/working_file.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /opt/svyazcom/cdr_sca/working_file.cpp > CMakeFiles/cdr_sca.dir/working_file.cpp.i

CMakeFiles/cdr_sca.dir/working_file.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/cdr_sca.dir/working_file.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /opt/svyazcom/cdr_sca/working_file.cpp -o CMakeFiles/cdr_sca.dir/working_file.cpp.s

# Object files for target cdr_sca
cdr_sca_OBJECTS = \
"CMakeFiles/cdr_sca.dir/main.cpp.o" \
"CMakeFiles/cdr_sca.dir/parser.cpp.o" \
"CMakeFiles/cdr_sca.dir/worker_cnora.cpp.o" \
"CMakeFiles/cdr_sca.dir/working_file.cpp.o"

# External object files for target cdr_sca
cdr_sca_EXTERNAL_OBJECTS =

cdr_sca: CMakeFiles/cdr_sca.dir/main.cpp.o
cdr_sca: CMakeFiles/cdr_sca.dir/parser.cpp.o
cdr_sca: CMakeFiles/cdr_sca.dir/worker_cnora.cpp.o
cdr_sca: CMakeFiles/cdr_sca.dir/working_file.cpp.o
cdr_sca: CMakeFiles/cdr_sca.dir/build.make
cdr_sca: /usr/lib/x86_64-linux-gnu/libboost_system.a
cdr_sca: /usr/lib/x86_64-linux-gnu/libboost_log.a
cdr_sca: /usr/lib/x86_64-linux-gnu/libboost_thread.a
cdr_sca: /usr/lib/x86_64-linux-gnu/libboost_filesystem.a
cdr_sca: /usr/lib/x86_64-linux-gnu/libboost_date_time.a
cdr_sca: /usr/lib/x86_64-linux-gnu/libboost_log_setup.a
cdr_sca: /usr/lib/x86_64-linux-gnu/libboost_regex.a
cdr_sca: /usr/lib/x86_64-linux-gnu/libboost_chrono.a
cdr_sca: /usr/lib/x86_64-linux-gnu/libboost_atomic.a
cdr_sca: cnora_cpp/libcnora_service.a
cdr_sca: coren_cpp/libcoren_interface.a
cdr_sca: coren_cpp/protocol/libcoren_protocol.a
cdr_sca: cnora_cpp/protocol/libcnora_protocol.a
cdr_sca: /usr/lib/x86_64-linux-gnu/libboost_program_options.a
cdr_sca: /usr/lib/x86_64-linux-gnu/libboost_filesystem.a
cdr_sca: /usr/lib/x86_64-linux-gnu/libboost_random.a
cdr_sca: /usr/lib/x86_64-linux-gnu/libboost_system.a
cdr_sca: /usr/lib/x86_64-linux-gnu/libboost_thread.a
cdr_sca: /usr/lib/x86_64-linux-gnu/libboost_date_time.a
cdr_sca: /usr/lib/x86_64-linux-gnu/libboost_chrono.a
cdr_sca: /usr/lib/x86_64-linux-gnu/libboost_atomic.a
cdr_sca: CMakeFiles/cdr_sca.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/opt/svyazcom/cdr_sca/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking CXX executable cdr_sca"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/cdr_sca.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/cdr_sca.dir/build: cdr_sca

.PHONY : CMakeFiles/cdr_sca.dir/build

CMakeFiles/cdr_sca.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/cdr_sca.dir/cmake_clean.cmake
.PHONY : CMakeFiles/cdr_sca.dir/clean

CMakeFiles/cdr_sca.dir/depend:
	cd /opt/svyazcom/cdr_sca/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /opt/svyazcom/cdr_sca /opt/svyazcom/cdr_sca /opt/svyazcom/cdr_sca/build /opt/svyazcom/cdr_sca/build /opt/svyazcom/cdr_sca/build/CMakeFiles/cdr_sca.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/cdr_sca.dir/depend

