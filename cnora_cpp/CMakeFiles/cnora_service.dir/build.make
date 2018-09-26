# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.11

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
CMAKE_COMMAND = /usr/local/bin/cmake

# The command to remove a file.
RM = /usr/local/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /opt/svyazcom/ss7_dmp_cnora/ss7_dmp

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /opt/svyazcom/ss7_dmp_cnora/ss7_dmp

# Include any dependencies generated for this target.
include cnora_cpp/CMakeFiles/cnora_service.dir/depend.make

# Include the progress variables for this target.
include cnora_cpp/CMakeFiles/cnora_service.dir/progress.make

# Include the compile flags for this target's objects.
include cnora_cpp/CMakeFiles/cnora_service.dir/flags.make

cnora_cpp/CMakeFiles/cnora_service.dir/src/CNora.cpp.o: cnora_cpp/CMakeFiles/cnora_service.dir/flags.make
cnora_cpp/CMakeFiles/cnora_service.dir/src/CNora.cpp.o: cnora_cpp/src/CNora.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/opt/svyazcom/ss7_dmp_cnora/ss7_dmp/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object cnora_cpp/CMakeFiles/cnora_service.dir/src/CNora.cpp.o"
	cd /opt/svyazcom/ss7_dmp_cnora/ss7_dmp/cnora_cpp && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/cnora_service.dir/src/CNora.cpp.o -c /opt/svyazcom/ss7_dmp_cnora/ss7_dmp/cnora_cpp/src/CNora.cpp

cnora_cpp/CMakeFiles/cnora_service.dir/src/CNora.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/cnora_service.dir/src/CNora.cpp.i"
	cd /opt/svyazcom/ss7_dmp_cnora/ss7_dmp/cnora_cpp && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /opt/svyazcom/ss7_dmp_cnora/ss7_dmp/cnora_cpp/src/CNora.cpp > CMakeFiles/cnora_service.dir/src/CNora.cpp.i

cnora_cpp/CMakeFiles/cnora_service.dir/src/CNora.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/cnora_service.dir/src/CNora.cpp.s"
	cd /opt/svyazcom/ss7_dmp_cnora/ss7_dmp/cnora_cpp && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /opt/svyazcom/ss7_dmp_cnora/ss7_dmp/cnora_cpp/src/CNora.cpp -o CMakeFiles/cnora_service.dir/src/CNora.cpp.s

cnora_cpp/CMakeFiles/cnora_service.dir/src/main.cpp.o: cnora_cpp/CMakeFiles/cnora_service.dir/flags.make
cnora_cpp/CMakeFiles/cnora_service.dir/src/main.cpp.o: cnora_cpp/src/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/opt/svyazcom/ss7_dmp_cnora/ss7_dmp/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object cnora_cpp/CMakeFiles/cnora_service.dir/src/main.cpp.o"
	cd /opt/svyazcom/ss7_dmp_cnora/ss7_dmp/cnora_cpp && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/cnora_service.dir/src/main.cpp.o -c /opt/svyazcom/ss7_dmp_cnora/ss7_dmp/cnora_cpp/src/main.cpp

cnora_cpp/CMakeFiles/cnora_service.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/cnora_service.dir/src/main.cpp.i"
	cd /opt/svyazcom/ss7_dmp_cnora/ss7_dmp/cnora_cpp && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /opt/svyazcom/ss7_dmp_cnora/ss7_dmp/cnora_cpp/src/main.cpp > CMakeFiles/cnora_service.dir/src/main.cpp.i

cnora_cpp/CMakeFiles/cnora_service.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/cnora_service.dir/src/main.cpp.s"
	cd /opt/svyazcom/ss7_dmp_cnora/ss7_dmp/cnora_cpp && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /opt/svyazcom/ss7_dmp_cnora/ss7_dmp/cnora_cpp/src/main.cpp -o CMakeFiles/cnora_service.dir/src/main.cpp.s

# Object files for target cnora_service
cnora_service_OBJECTS = \
"CMakeFiles/cnora_service.dir/src/CNora.cpp.o" \
"CMakeFiles/cnora_service.dir/src/main.cpp.o"

# External object files for target cnora_service
cnora_service_EXTERNAL_OBJECTS =

cnora_cpp/libcnora_service.a: cnora_cpp/CMakeFiles/cnora_service.dir/src/CNora.cpp.o
cnora_cpp/libcnora_service.a: cnora_cpp/CMakeFiles/cnora_service.dir/src/main.cpp.o
cnora_cpp/libcnora_service.a: cnora_cpp/CMakeFiles/cnora_service.dir/build.make
cnora_cpp/libcnora_service.a: cnora_cpp/CMakeFiles/cnora_service.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/opt/svyazcom/ss7_dmp_cnora/ss7_dmp/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX static library libcnora_service.a"
	cd /opt/svyazcom/ss7_dmp_cnora/ss7_dmp/cnora_cpp && $(CMAKE_COMMAND) -P CMakeFiles/cnora_service.dir/cmake_clean_target.cmake
	cd /opt/svyazcom/ss7_dmp_cnora/ss7_dmp/cnora_cpp && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/cnora_service.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
cnora_cpp/CMakeFiles/cnora_service.dir/build: cnora_cpp/libcnora_service.a

.PHONY : cnora_cpp/CMakeFiles/cnora_service.dir/build

cnora_cpp/CMakeFiles/cnora_service.dir/clean:
	cd /opt/svyazcom/ss7_dmp_cnora/ss7_dmp/cnora_cpp && $(CMAKE_COMMAND) -P CMakeFiles/cnora_service.dir/cmake_clean.cmake
.PHONY : cnora_cpp/CMakeFiles/cnora_service.dir/clean

cnora_cpp/CMakeFiles/cnora_service.dir/depend:
	cd /opt/svyazcom/ss7_dmp_cnora/ss7_dmp && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /opt/svyazcom/ss7_dmp_cnora/ss7_dmp /opt/svyazcom/ss7_dmp_cnora/ss7_dmp/cnora_cpp /opt/svyazcom/ss7_dmp_cnora/ss7_dmp /opt/svyazcom/ss7_dmp_cnora/ss7_dmp/cnora_cpp /opt/svyazcom/ss7_dmp_cnora/ss7_dmp/cnora_cpp/CMakeFiles/cnora_service.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : cnora_cpp/CMakeFiles/cnora_service.dir/depend

