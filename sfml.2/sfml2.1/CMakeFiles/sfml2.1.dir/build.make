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
CMAKE_SOURCE_DIR = E:\CppDistro\WORK\sfml.2\sfml2.1

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = E:\CppDistro\WORK\sfml.2\sfml2.1

# Include any dependencies generated for this target.
include CMakeFiles/sfml2.1.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/sfml2.1.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/sfml2.1.dir/flags.make

CMakeFiles/sfml2.1.dir/main.obj: CMakeFiles/sfml2.1.dir/flags.make
CMakeFiles/sfml2.1.dir/main.obj: CMakeFiles/sfml2.1.dir/includes_CXX.rsp
CMakeFiles/sfml2.1.dir/main.obj: main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=E:\CppDistro\WORK\sfml.2\sfml2.1\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/sfml2.1.dir/main.obj"
	E:\CppDistro\MinGW\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\sfml2.1.dir\main.obj -c E:\CppDistro\WORK\sfml.2\sfml2.1\main.cpp

CMakeFiles/sfml2.1.dir/main.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sfml2.1.dir/main.i"
	E:\CppDistro\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E E:\CppDistro\WORK\sfml.2\sfml2.1\main.cpp > CMakeFiles\sfml2.1.dir\main.i

CMakeFiles/sfml2.1.dir/main.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sfml2.1.dir/main.s"
	E:\CppDistro\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S E:\CppDistro\WORK\sfml.2\sfml2.1\main.cpp -o CMakeFiles\sfml2.1.dir\main.s

CMakeFiles/sfml2.1.dir/main.obj.requires:

.PHONY : CMakeFiles/sfml2.1.dir/main.obj.requires

CMakeFiles/sfml2.1.dir/main.obj.provides: CMakeFiles/sfml2.1.dir/main.obj.requires
	$(MAKE) -f CMakeFiles\sfml2.1.dir\build.make CMakeFiles/sfml2.1.dir/main.obj.provides.build
.PHONY : CMakeFiles/sfml2.1.dir/main.obj.provides

CMakeFiles/sfml2.1.dir/main.obj.provides.build: CMakeFiles/sfml2.1.dir/main.obj


# Object files for target sfml2.1
sfml2_1_OBJECTS = \
"CMakeFiles/sfml2.1.dir/main.obj"

# External object files for target sfml2.1
sfml2_1_EXTERNAL_OBJECTS =

sfml2.1.exe: CMakeFiles/sfml2.1.dir/main.obj
sfml2.1.exe: CMakeFiles/sfml2.1.dir/build.make
sfml2.1.exe: E:/CppDistro/MinGW/lib/libsfml-window-s.a
sfml2.1.exe: E:/CppDistro/MinGW/lib/libsfml-graphics-s.a
sfml2.1.exe: E:/CppDistro/MinGW/lib/libsfml-system-s.a
sfml2.1.exe: E:/CppDistro/MinGW/lib/libfreetype.a
sfml2.1.exe: E:/CppDistro/MinGW/lib/libjpeg.a
sfml2.1.exe: CMakeFiles/sfml2.1.dir/linklibs.rsp
sfml2.1.exe: CMakeFiles/sfml2.1.dir/objects1.rsp
sfml2.1.exe: CMakeFiles/sfml2.1.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=E:\CppDistro\WORK\sfml.2\sfml2.1\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable sfml2.1.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\sfml2.1.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/sfml2.1.dir/build: sfml2.1.exe

.PHONY : CMakeFiles/sfml2.1.dir/build

CMakeFiles/sfml2.1.dir/requires: CMakeFiles/sfml2.1.dir/main.obj.requires

.PHONY : CMakeFiles/sfml2.1.dir/requires

CMakeFiles/sfml2.1.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\sfml2.1.dir\cmake_clean.cmake
.PHONY : CMakeFiles/sfml2.1.dir/clean

CMakeFiles/sfml2.1.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" E:\CppDistro\WORK\sfml.2\sfml2.1 E:\CppDistro\WORK\sfml.2\sfml2.1 E:\CppDistro\WORK\sfml.2\sfml2.1 E:\CppDistro\WORK\sfml.2\sfml2.1 E:\CppDistro\WORK\sfml.2\sfml2.1\CMakeFiles\sfml2.1.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/sfml2.1.dir/depend

