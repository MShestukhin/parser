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
include g3log/CMakeFiles/g3log-FATAL-sigsegv.dir/depend.make

# Include the progress variables for this target.
include g3log/CMakeFiles/g3log-FATAL-sigsegv.dir/progress.make

# Include the compile flags for this target's objects.
include g3log/CMakeFiles/g3log-FATAL-sigsegv.dir/flags.make

g3log/CMakeFiles/g3log-FATAL-sigsegv.dir/example/main_sigsegv.cpp.o: g3log/CMakeFiles/g3log-FATAL-sigsegv.dir/flags.make
g3log/CMakeFiles/g3log-FATAL-sigsegv.dir/example/main_sigsegv.cpp.o: ../g3log/example/main_sigsegv.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/opt/svyazcom/cdr_sca/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object g3log/CMakeFiles/g3log-FATAL-sigsegv.dir/example/main_sigsegv.cpp.o"
	cd /opt/svyazcom/cdr_sca/build/g3log && /usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/g3log-FATAL-sigsegv.dir/example/main_sigsegv.cpp.o -c /opt/svyazcom/cdr_sca/g3log/example/main_sigsegv.cpp

g3log/CMakeFiles/g3log-FATAL-sigsegv.dir/example/main_sigsegv.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/g3log-FATAL-sigsegv.dir/example/main_sigsegv.cpp.i"
	cd /opt/svyazcom/cdr_sca/build/g3log && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /opt/svyazcom/cdr_sca/g3log/example/main_sigsegv.cpp > CMakeFiles/g3log-FATAL-sigsegv.dir/example/main_sigsegv.cpp.i

g3log/CMakeFiles/g3log-FATAL-sigsegv.dir/example/main_sigsegv.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/g3log-FATAL-sigsegv.dir/example/main_sigsegv.cpp.s"
	cd /opt/svyazcom/cdr_sca/build/g3log && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /opt/svyazcom/cdr_sca/g3log/example/main_sigsegv.cpp -o CMakeFiles/g3log-FATAL-sigsegv.dir/example/main_sigsegv.cpp.s

# Object files for target g3log-FATAL-sigsegv
g3log__FATAL__sigsegv_OBJECTS = \
"CMakeFiles/g3log-FATAL-sigsegv.dir/example/main_sigsegv.cpp.o"

# External object files for target g3log-FATAL-sigsegv
g3log__FATAL__sigsegv_EXTERNAL_OBJECTS =

g3log/g3log-FATAL-sigsegv: g3log/CMakeFiles/g3log-FATAL-sigsegv.dir/example/main_sigsegv.cpp.o
g3log/g3log-FATAL-sigsegv: g3log/CMakeFiles/g3log-FATAL-sigsegv.dir/build.make
g3log/g3log-FATAL-sigsegv: g3log/libg3logger.so.1.3.0-2
g3log/g3log-FATAL-sigsegv: g3log/CMakeFiles/g3log-FATAL-sigsegv.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/opt/svyazcom/cdr_sca/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable g3log-FATAL-sigsegv"
	cd /opt/svyazcom/cdr_sca/build/g3log && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/g3log-FATAL-sigsegv.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
g3log/CMakeFiles/g3log-FATAL-sigsegv.dir/build: g3log/g3log-FATAL-sigsegv

.PHONY : g3log/CMakeFiles/g3log-FATAL-sigsegv.dir/build

g3log/CMakeFiles/g3log-FATAL-sigsegv.dir/clean:
	cd /opt/svyazcom/cdr_sca/build/g3log && $(CMAKE_COMMAND) -P CMakeFiles/g3log-FATAL-sigsegv.dir/cmake_clean.cmake
.PHONY : g3log/CMakeFiles/g3log-FATAL-sigsegv.dir/clean

g3log/CMakeFiles/g3log-FATAL-sigsegv.dir/depend:
	cd /opt/svyazcom/cdr_sca/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /opt/svyazcom/cdr_sca /opt/svyazcom/cdr_sca/g3log /opt/svyazcom/cdr_sca/build /opt/svyazcom/cdr_sca/build/g3log /opt/svyazcom/cdr_sca/build/g3log/CMakeFiles/g3log-FATAL-sigsegv.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : g3log/CMakeFiles/g3log-FATAL-sigsegv.dir/depend

