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

# Utility rule file for ContinuousStart.

# Include the progress variables for this target.
include spdlog/CMakeFiles/ContinuousStart.dir/progress.make

spdlog/CMakeFiles/ContinuousStart:
	cd /opt/svyazcom/cdr_sca/build/spdlog && /home/maxim/Downloads/cmake-3.12.0/bin/ctest -D ContinuousStart

ContinuousStart: spdlog/CMakeFiles/ContinuousStart
ContinuousStart: spdlog/CMakeFiles/ContinuousStart.dir/build.make

.PHONY : ContinuousStart

# Rule to build all files generated by this target.
spdlog/CMakeFiles/ContinuousStart.dir/build: ContinuousStart

.PHONY : spdlog/CMakeFiles/ContinuousStart.dir/build

spdlog/CMakeFiles/ContinuousStart.dir/clean:
	cd /opt/svyazcom/cdr_sca/build/spdlog && $(CMAKE_COMMAND) -P CMakeFiles/ContinuousStart.dir/cmake_clean.cmake
.PHONY : spdlog/CMakeFiles/ContinuousStart.dir/clean

spdlog/CMakeFiles/ContinuousStart.dir/depend:
	cd /opt/svyazcom/cdr_sca/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /opt/svyazcom/cdr_sca /opt/svyazcom/cdr_sca/spdlog /opt/svyazcom/cdr_sca/build /opt/svyazcom/cdr_sca/build/spdlog /opt/svyazcom/cdr_sca/build/spdlog/CMakeFiles/ContinuousStart.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : spdlog/CMakeFiles/ContinuousStart.dir/depend
