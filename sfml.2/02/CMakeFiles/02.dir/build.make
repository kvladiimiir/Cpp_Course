# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.9

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = E:\CppDistro\cmake\bin\cmake.exe

# The command to remove a file.
RM = E:\CppDistro\cmake\bin\cmake.exe -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = E:\CppDistro\WORK\sfml.2\02

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = E:\CppDistro\WORK\sfml.2\02

# Include any dependencies generated for this target.
include CMakeFiles/02.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/02.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/02.dir/flags.make

CMakeFiles/02.dir/main.obj: CMakeFiles/02.dir/flags.make
CMakeFiles/02.dir/main.obj: CMakeFiles/02.dir/includes_CXX.rsp
CMakeFiles/02.dir/main.obj: main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=E:\CppDistro\WORK\sfml.2\02\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/02.dir/main.obj"
	E:\CppDistro\MinGW\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\02.dir\main.obj -c E:\CppDistro\WORK\sfml.2\02\main.cpp

CMakeFiles/02.dir/main.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/02.dir/main.i"
	E:\CppDistro\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E E:\CppDistro\WORK\sfml.2\02\main.cpp > CMakeFiles\02.dir\main.i

CMakeFiles/02.dir/main.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/02.dir/main.s"
	E:\CppDistro\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S E:\CppDistro\WORK\sfml.2\02\main.cpp -o CMakeFiles\02.dir\main.s

CMakeFiles/02.dir/main.obj.requires:

.PHONY : CMakeFiles/02.dir/main.obj.requires

CMakeFiles/02.dir/main.obj.provides: CMakeFiles/02.dir/main.obj.requires
	$(MAKE) -f CMakeFiles\02.dir\build.make CMakeFiles/02.dir/main.obj.provides.build
.PHONY : CMakeFiles/02.dir/main.obj.provides

CMakeFiles/02.dir/main.obj.provides.build: CMakeFiles/02.dir/main.obj


# Object files for target 02
02_OBJECTS = \
"CMakeFiles/02.dir/main.obj"

# External object files for target 02
02_EXTERNAL_OBJECTS =

02.exe: CMakeFiles/02.dir/main.obj
02.exe: CMakeFiles/02.dir/build.make
02.exe: E:/CppDistro/MinGW/lib/libsfml-window-s.a
02.exe: E:/CppDistro/MinGW/lib/libsfml-graphics-s.a
02.exe: E:/CppDistro/MinGW/lib/libsfml-system-s.a
02.exe: E:/CppDistro/MinGW/lib/libfreetype.a
02.exe: E:/CppDistro/MinGW/lib/libjpeg.a
02.exe: CMakeFiles/02.dir/linklibs.rsp
02.exe: CMakeFiles/02.dir/objects1.rsp
02.exe: CMakeFiles/02.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=E:\CppDistro\WORK\sfml.2\02\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable 02.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\02.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/02.dir/build: 02.exe

.PHONY : CMakeFiles/02.dir/build

CMakeFiles/02.dir/requires: CMakeFiles/02.dir/main.obj.requires

.PHONY : CMakeFiles/02.dir/requires

CMakeFiles/02.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\02.dir\cmake_clean.cmake
.PHONY : CMakeFiles/02.dir/clean

CMakeFiles/02.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" E:\CppDistro\WORK\sfml.2\02 E:\CppDistro\WORK\sfml.2\02 E:\CppDistro\WORK\sfml.2\02 E:\CppDistro\WORK\sfml.2\02 E:\CppDistro\WORK\sfml.2\02\CMakeFiles\02.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/02.dir/depend

