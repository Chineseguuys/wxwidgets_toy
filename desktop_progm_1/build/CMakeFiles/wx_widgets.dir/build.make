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


# Produce verbose output by default.
VERBOSE = 1

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
CMAKE_SOURCE_DIR = "/home/yjh/Nutstore Files/Github_storage/wx_widgets/desktop_progm_1"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/home/yjh/Nutstore Files/Github_storage/wx_widgets/desktop_progm_1/build"

# Include any dependencies generated for this target.
include CMakeFiles/wx_widgets.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/wx_widgets.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/wx_widgets.dir/flags.make

CMakeFiles/wx_widgets.dir/src/cMain.cpp.o: CMakeFiles/wx_widgets.dir/flags.make
CMakeFiles/wx_widgets.dir/src/cMain.cpp.o: ../src/cMain.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/yjh/Nutstore Files/Github_storage/wx_widgets/desktop_progm_1/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/wx_widgets.dir/src/cMain.cpp.o"
	clang++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/wx_widgets.dir/src/cMain.cpp.o -c "/home/yjh/Nutstore Files/Github_storage/wx_widgets/desktop_progm_1/src/cMain.cpp"

CMakeFiles/wx_widgets.dir/src/cMain.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/wx_widgets.dir/src/cMain.cpp.i"
	clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/yjh/Nutstore Files/Github_storage/wx_widgets/desktop_progm_1/src/cMain.cpp" > CMakeFiles/wx_widgets.dir/src/cMain.cpp.i

CMakeFiles/wx_widgets.dir/src/cMain.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/wx_widgets.dir/src/cMain.cpp.s"
	clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/yjh/Nutstore Files/Github_storage/wx_widgets/desktop_progm_1/src/cMain.cpp" -o CMakeFiles/wx_widgets.dir/src/cMain.cpp.s

CMakeFiles/wx_widgets.dir/src/cApp.cpp.o: CMakeFiles/wx_widgets.dir/flags.make
CMakeFiles/wx_widgets.dir/src/cApp.cpp.o: ../src/cApp.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/yjh/Nutstore Files/Github_storage/wx_widgets/desktop_progm_1/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/wx_widgets.dir/src/cApp.cpp.o"
	clang++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/wx_widgets.dir/src/cApp.cpp.o -c "/home/yjh/Nutstore Files/Github_storage/wx_widgets/desktop_progm_1/src/cApp.cpp"

CMakeFiles/wx_widgets.dir/src/cApp.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/wx_widgets.dir/src/cApp.cpp.i"
	clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/yjh/Nutstore Files/Github_storage/wx_widgets/desktop_progm_1/src/cApp.cpp" > CMakeFiles/wx_widgets.dir/src/cApp.cpp.i

CMakeFiles/wx_widgets.dir/src/cApp.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/wx_widgets.dir/src/cApp.cpp.s"
	clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/yjh/Nutstore Files/Github_storage/wx_widgets/desktop_progm_1/src/cApp.cpp" -o CMakeFiles/wx_widgets.dir/src/cApp.cpp.s

# Object files for target wx_widgets
wx_widgets_OBJECTS = \
"CMakeFiles/wx_widgets.dir/src/cMain.cpp.o" \
"CMakeFiles/wx_widgets.dir/src/cApp.cpp.o"

# External object files for target wx_widgets
wx_widgets_EXTERNAL_OBJECTS =

wx_widgets: CMakeFiles/wx_widgets.dir/src/cMain.cpp.o
wx_widgets: CMakeFiles/wx_widgets.dir/src/cApp.cpp.o
wx_widgets: CMakeFiles/wx_widgets.dir/build.make
wx_widgets: /home/yjh/MYSOFTWARE/wxwidgets_3_1_4/lib/libwx_gtk3u_xrc-3.1.a
wx_widgets: /home/yjh/MYSOFTWARE/wxwidgets_3_1_4/lib/libwx_gtk3u_qa-3.1.a
wx_widgets: /home/yjh/MYSOFTWARE/wxwidgets_3_1_4/lib/libwx_baseu_net-3.1.a
wx_widgets: /home/yjh/MYSOFTWARE/wxwidgets_3_1_4/lib/libwx_gtk3u_html-3.1.a
wx_widgets: /home/yjh/MYSOFTWARE/wxwidgets_3_1_4/lib/libwx_gtk3u_core-3.1.a
wx_widgets: /home/yjh/MYSOFTWARE/wxwidgets_3_1_4/lib/libwx_baseu_xml-3.1.a
wx_widgets: /home/yjh/MYSOFTWARE/wxwidgets_3_1_4/lib/libwx_baseu-3.1.a
wx_widgets: /home/yjh/MYSOFTWARE/wxwidgets_3_1_4/lib/libwxtiff-3.1.a
wx_widgets: /home/yjh/MYSOFTWARE/wxwidgets_3_1_4/lib/libwxjpeg-3.1.a
wx_widgets: /home/yjh/MYSOFTWARE/wxwidgets_3_1_4/lib/libwxregexu-3.1.a
wx_widgets: /home/yjh/MYSOFTWARE/wxwidgets_3_1_4/lib/libwxscintilla-3.1.a
wx_widgets: CMakeFiles/wx_widgets.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/home/yjh/Nutstore Files/Github_storage/wx_widgets/desktop_progm_1/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable wx_widgets"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/wx_widgets.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/wx_widgets.dir/build: wx_widgets

.PHONY : CMakeFiles/wx_widgets.dir/build

CMakeFiles/wx_widgets.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/wx_widgets.dir/cmake_clean.cmake
.PHONY : CMakeFiles/wx_widgets.dir/clean

CMakeFiles/wx_widgets.dir/depend:
	cd "/home/yjh/Nutstore Files/Github_storage/wx_widgets/desktop_progm_1/build" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/home/yjh/Nutstore Files/Github_storage/wx_widgets/desktop_progm_1" "/home/yjh/Nutstore Files/Github_storage/wx_widgets/desktop_progm_1" "/home/yjh/Nutstore Files/Github_storage/wx_widgets/desktop_progm_1/build" "/home/yjh/Nutstore Files/Github_storage/wx_widgets/desktop_progm_1/build" "/home/yjh/Nutstore Files/Github_storage/wx_widgets/desktop_progm_1/build/CMakeFiles/wx_widgets.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/wx_widgets.dir/depend
