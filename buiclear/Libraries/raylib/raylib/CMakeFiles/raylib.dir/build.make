# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 4.0

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
CMAKE_COMMAND = /snap/cmake/1468/bin/cmake

# The command to remove a file.
RM = /snap/cmake/1468/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/batuhan/Desktop/DigitalSimulator

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/batuhan/Desktop/DigitalSimulator/buiclear

# Include any dependencies generated for this target.
include Libraries/raylib/raylib/CMakeFiles/raylib.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include Libraries/raylib/raylib/CMakeFiles/raylib.dir/compiler_depend.make

# Include the progress variables for this target.
include Libraries/raylib/raylib/CMakeFiles/raylib.dir/progress.make

# Include the compile flags for this target's objects.
include Libraries/raylib/raylib/CMakeFiles/raylib.dir/flags.make

Libraries/raylib/raylib/CMakeFiles/raylib.dir/codegen:
.PHONY : Libraries/raylib/raylib/CMakeFiles/raylib.dir/codegen

Libraries/raylib/raylib/CMakeFiles/raylib.dir/raudio.c.o: Libraries/raylib/raylib/CMakeFiles/raylib.dir/flags.make
Libraries/raylib/raylib/CMakeFiles/raylib.dir/raudio.c.o: /home/batuhan/Desktop/DigitalSimulator/Libraries/raylib/src/raudio.c
Libraries/raylib/raylib/CMakeFiles/raylib.dir/raudio.c.o: Libraries/raylib/raylib/CMakeFiles/raylib.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/batuhan/Desktop/DigitalSimulator/buiclear/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object Libraries/raylib/raylib/CMakeFiles/raylib.dir/raudio.c.o"
	cd /home/batuhan/Desktop/DigitalSimulator/buiclear/Libraries/raylib/raylib && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT Libraries/raylib/raylib/CMakeFiles/raylib.dir/raudio.c.o -MF CMakeFiles/raylib.dir/raudio.c.o.d -o CMakeFiles/raylib.dir/raudio.c.o -c /home/batuhan/Desktop/DigitalSimulator/Libraries/raylib/src/raudio.c

Libraries/raylib/raylib/CMakeFiles/raylib.dir/raudio.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/raylib.dir/raudio.c.i"
	cd /home/batuhan/Desktop/DigitalSimulator/buiclear/Libraries/raylib/raylib && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/batuhan/Desktop/DigitalSimulator/Libraries/raylib/src/raudio.c > CMakeFiles/raylib.dir/raudio.c.i

Libraries/raylib/raylib/CMakeFiles/raylib.dir/raudio.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/raylib.dir/raudio.c.s"
	cd /home/batuhan/Desktop/DigitalSimulator/buiclear/Libraries/raylib/raylib && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/batuhan/Desktop/DigitalSimulator/Libraries/raylib/src/raudio.c -o CMakeFiles/raylib.dir/raudio.c.s

Libraries/raylib/raylib/CMakeFiles/raylib.dir/rcore.c.o: Libraries/raylib/raylib/CMakeFiles/raylib.dir/flags.make
Libraries/raylib/raylib/CMakeFiles/raylib.dir/rcore.c.o: /home/batuhan/Desktop/DigitalSimulator/Libraries/raylib/src/rcore.c
Libraries/raylib/raylib/CMakeFiles/raylib.dir/rcore.c.o: Libraries/raylib/raylib/CMakeFiles/raylib.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/batuhan/Desktop/DigitalSimulator/buiclear/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object Libraries/raylib/raylib/CMakeFiles/raylib.dir/rcore.c.o"
	cd /home/batuhan/Desktop/DigitalSimulator/buiclear/Libraries/raylib/raylib && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT Libraries/raylib/raylib/CMakeFiles/raylib.dir/rcore.c.o -MF CMakeFiles/raylib.dir/rcore.c.o.d -o CMakeFiles/raylib.dir/rcore.c.o -c /home/batuhan/Desktop/DigitalSimulator/Libraries/raylib/src/rcore.c

Libraries/raylib/raylib/CMakeFiles/raylib.dir/rcore.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/raylib.dir/rcore.c.i"
	cd /home/batuhan/Desktop/DigitalSimulator/buiclear/Libraries/raylib/raylib && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/batuhan/Desktop/DigitalSimulator/Libraries/raylib/src/rcore.c > CMakeFiles/raylib.dir/rcore.c.i

Libraries/raylib/raylib/CMakeFiles/raylib.dir/rcore.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/raylib.dir/rcore.c.s"
	cd /home/batuhan/Desktop/DigitalSimulator/buiclear/Libraries/raylib/raylib && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/batuhan/Desktop/DigitalSimulator/Libraries/raylib/src/rcore.c -o CMakeFiles/raylib.dir/rcore.c.s

Libraries/raylib/raylib/CMakeFiles/raylib.dir/rmodels.c.o: Libraries/raylib/raylib/CMakeFiles/raylib.dir/flags.make
Libraries/raylib/raylib/CMakeFiles/raylib.dir/rmodels.c.o: /home/batuhan/Desktop/DigitalSimulator/Libraries/raylib/src/rmodels.c
Libraries/raylib/raylib/CMakeFiles/raylib.dir/rmodels.c.o: Libraries/raylib/raylib/CMakeFiles/raylib.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/batuhan/Desktop/DigitalSimulator/buiclear/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object Libraries/raylib/raylib/CMakeFiles/raylib.dir/rmodels.c.o"
	cd /home/batuhan/Desktop/DigitalSimulator/buiclear/Libraries/raylib/raylib && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT Libraries/raylib/raylib/CMakeFiles/raylib.dir/rmodels.c.o -MF CMakeFiles/raylib.dir/rmodels.c.o.d -o CMakeFiles/raylib.dir/rmodels.c.o -c /home/batuhan/Desktop/DigitalSimulator/Libraries/raylib/src/rmodels.c

Libraries/raylib/raylib/CMakeFiles/raylib.dir/rmodels.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/raylib.dir/rmodels.c.i"
	cd /home/batuhan/Desktop/DigitalSimulator/buiclear/Libraries/raylib/raylib && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/batuhan/Desktop/DigitalSimulator/Libraries/raylib/src/rmodels.c > CMakeFiles/raylib.dir/rmodels.c.i

Libraries/raylib/raylib/CMakeFiles/raylib.dir/rmodels.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/raylib.dir/rmodels.c.s"
	cd /home/batuhan/Desktop/DigitalSimulator/buiclear/Libraries/raylib/raylib && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/batuhan/Desktop/DigitalSimulator/Libraries/raylib/src/rmodels.c -o CMakeFiles/raylib.dir/rmodels.c.s

Libraries/raylib/raylib/CMakeFiles/raylib.dir/rshapes.c.o: Libraries/raylib/raylib/CMakeFiles/raylib.dir/flags.make
Libraries/raylib/raylib/CMakeFiles/raylib.dir/rshapes.c.o: /home/batuhan/Desktop/DigitalSimulator/Libraries/raylib/src/rshapes.c
Libraries/raylib/raylib/CMakeFiles/raylib.dir/rshapes.c.o: Libraries/raylib/raylib/CMakeFiles/raylib.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/batuhan/Desktop/DigitalSimulator/buiclear/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object Libraries/raylib/raylib/CMakeFiles/raylib.dir/rshapes.c.o"
	cd /home/batuhan/Desktop/DigitalSimulator/buiclear/Libraries/raylib/raylib && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT Libraries/raylib/raylib/CMakeFiles/raylib.dir/rshapes.c.o -MF CMakeFiles/raylib.dir/rshapes.c.o.d -o CMakeFiles/raylib.dir/rshapes.c.o -c /home/batuhan/Desktop/DigitalSimulator/Libraries/raylib/src/rshapes.c

Libraries/raylib/raylib/CMakeFiles/raylib.dir/rshapes.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/raylib.dir/rshapes.c.i"
	cd /home/batuhan/Desktop/DigitalSimulator/buiclear/Libraries/raylib/raylib && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/batuhan/Desktop/DigitalSimulator/Libraries/raylib/src/rshapes.c > CMakeFiles/raylib.dir/rshapes.c.i

Libraries/raylib/raylib/CMakeFiles/raylib.dir/rshapes.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/raylib.dir/rshapes.c.s"
	cd /home/batuhan/Desktop/DigitalSimulator/buiclear/Libraries/raylib/raylib && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/batuhan/Desktop/DigitalSimulator/Libraries/raylib/src/rshapes.c -o CMakeFiles/raylib.dir/rshapes.c.s

Libraries/raylib/raylib/CMakeFiles/raylib.dir/rtext.c.o: Libraries/raylib/raylib/CMakeFiles/raylib.dir/flags.make
Libraries/raylib/raylib/CMakeFiles/raylib.dir/rtext.c.o: /home/batuhan/Desktop/DigitalSimulator/Libraries/raylib/src/rtext.c
Libraries/raylib/raylib/CMakeFiles/raylib.dir/rtext.c.o: Libraries/raylib/raylib/CMakeFiles/raylib.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/batuhan/Desktop/DigitalSimulator/buiclear/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building C object Libraries/raylib/raylib/CMakeFiles/raylib.dir/rtext.c.o"
	cd /home/batuhan/Desktop/DigitalSimulator/buiclear/Libraries/raylib/raylib && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT Libraries/raylib/raylib/CMakeFiles/raylib.dir/rtext.c.o -MF CMakeFiles/raylib.dir/rtext.c.o.d -o CMakeFiles/raylib.dir/rtext.c.o -c /home/batuhan/Desktop/DigitalSimulator/Libraries/raylib/src/rtext.c

Libraries/raylib/raylib/CMakeFiles/raylib.dir/rtext.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/raylib.dir/rtext.c.i"
	cd /home/batuhan/Desktop/DigitalSimulator/buiclear/Libraries/raylib/raylib && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/batuhan/Desktop/DigitalSimulator/Libraries/raylib/src/rtext.c > CMakeFiles/raylib.dir/rtext.c.i

Libraries/raylib/raylib/CMakeFiles/raylib.dir/rtext.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/raylib.dir/rtext.c.s"
	cd /home/batuhan/Desktop/DigitalSimulator/buiclear/Libraries/raylib/raylib && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/batuhan/Desktop/DigitalSimulator/Libraries/raylib/src/rtext.c -o CMakeFiles/raylib.dir/rtext.c.s

Libraries/raylib/raylib/CMakeFiles/raylib.dir/rtextures.c.o: Libraries/raylib/raylib/CMakeFiles/raylib.dir/flags.make
Libraries/raylib/raylib/CMakeFiles/raylib.dir/rtextures.c.o: /home/batuhan/Desktop/DigitalSimulator/Libraries/raylib/src/rtextures.c
Libraries/raylib/raylib/CMakeFiles/raylib.dir/rtextures.c.o: Libraries/raylib/raylib/CMakeFiles/raylib.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/batuhan/Desktop/DigitalSimulator/buiclear/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building C object Libraries/raylib/raylib/CMakeFiles/raylib.dir/rtextures.c.o"
	cd /home/batuhan/Desktop/DigitalSimulator/buiclear/Libraries/raylib/raylib && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT Libraries/raylib/raylib/CMakeFiles/raylib.dir/rtextures.c.o -MF CMakeFiles/raylib.dir/rtextures.c.o.d -o CMakeFiles/raylib.dir/rtextures.c.o -c /home/batuhan/Desktop/DigitalSimulator/Libraries/raylib/src/rtextures.c

Libraries/raylib/raylib/CMakeFiles/raylib.dir/rtextures.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/raylib.dir/rtextures.c.i"
	cd /home/batuhan/Desktop/DigitalSimulator/buiclear/Libraries/raylib/raylib && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/batuhan/Desktop/DigitalSimulator/Libraries/raylib/src/rtextures.c > CMakeFiles/raylib.dir/rtextures.c.i

Libraries/raylib/raylib/CMakeFiles/raylib.dir/rtextures.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/raylib.dir/rtextures.c.s"
	cd /home/batuhan/Desktop/DigitalSimulator/buiclear/Libraries/raylib/raylib && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/batuhan/Desktop/DigitalSimulator/Libraries/raylib/src/rtextures.c -o CMakeFiles/raylib.dir/rtextures.c.s

Libraries/raylib/raylib/CMakeFiles/raylib.dir/utils.c.o: Libraries/raylib/raylib/CMakeFiles/raylib.dir/flags.make
Libraries/raylib/raylib/CMakeFiles/raylib.dir/utils.c.o: /home/batuhan/Desktop/DigitalSimulator/Libraries/raylib/src/utils.c
Libraries/raylib/raylib/CMakeFiles/raylib.dir/utils.c.o: Libraries/raylib/raylib/CMakeFiles/raylib.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/batuhan/Desktop/DigitalSimulator/buiclear/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building C object Libraries/raylib/raylib/CMakeFiles/raylib.dir/utils.c.o"
	cd /home/batuhan/Desktop/DigitalSimulator/buiclear/Libraries/raylib/raylib && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT Libraries/raylib/raylib/CMakeFiles/raylib.dir/utils.c.o -MF CMakeFiles/raylib.dir/utils.c.o.d -o CMakeFiles/raylib.dir/utils.c.o -c /home/batuhan/Desktop/DigitalSimulator/Libraries/raylib/src/utils.c

Libraries/raylib/raylib/CMakeFiles/raylib.dir/utils.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/raylib.dir/utils.c.i"
	cd /home/batuhan/Desktop/DigitalSimulator/buiclear/Libraries/raylib/raylib && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/batuhan/Desktop/DigitalSimulator/Libraries/raylib/src/utils.c > CMakeFiles/raylib.dir/utils.c.i

Libraries/raylib/raylib/CMakeFiles/raylib.dir/utils.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/raylib.dir/utils.c.s"
	cd /home/batuhan/Desktop/DigitalSimulator/buiclear/Libraries/raylib/raylib && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/batuhan/Desktop/DigitalSimulator/Libraries/raylib/src/utils.c -o CMakeFiles/raylib.dir/utils.c.s

# Object files for target raylib
raylib_OBJECTS = \
"CMakeFiles/raylib.dir/raudio.c.o" \
"CMakeFiles/raylib.dir/rcore.c.o" \
"CMakeFiles/raylib.dir/rmodels.c.o" \
"CMakeFiles/raylib.dir/rshapes.c.o" \
"CMakeFiles/raylib.dir/rtext.c.o" \
"CMakeFiles/raylib.dir/rtextures.c.o" \
"CMakeFiles/raylib.dir/utils.c.o"

# External object files for target raylib
raylib_EXTERNAL_OBJECTS = \
"/home/batuhan/Desktop/DigitalSimulator/buiclear/Libraries/raylib/raylib/external/glfw/src/CMakeFiles/glfw.dir/context.c.o" \
"/home/batuhan/Desktop/DigitalSimulator/buiclear/Libraries/raylib/raylib/external/glfw/src/CMakeFiles/glfw.dir/init.c.o" \
"/home/batuhan/Desktop/DigitalSimulator/buiclear/Libraries/raylib/raylib/external/glfw/src/CMakeFiles/glfw.dir/input.c.o" \
"/home/batuhan/Desktop/DigitalSimulator/buiclear/Libraries/raylib/raylib/external/glfw/src/CMakeFiles/glfw.dir/monitor.c.o" \
"/home/batuhan/Desktop/DigitalSimulator/buiclear/Libraries/raylib/raylib/external/glfw/src/CMakeFiles/glfw.dir/platform.c.o" \
"/home/batuhan/Desktop/DigitalSimulator/buiclear/Libraries/raylib/raylib/external/glfw/src/CMakeFiles/glfw.dir/vulkan.c.o" \
"/home/batuhan/Desktop/DigitalSimulator/buiclear/Libraries/raylib/raylib/external/glfw/src/CMakeFiles/glfw.dir/window.c.o" \
"/home/batuhan/Desktop/DigitalSimulator/buiclear/Libraries/raylib/raylib/external/glfw/src/CMakeFiles/glfw.dir/egl_context.c.o" \
"/home/batuhan/Desktop/DigitalSimulator/buiclear/Libraries/raylib/raylib/external/glfw/src/CMakeFiles/glfw.dir/osmesa_context.c.o" \
"/home/batuhan/Desktop/DigitalSimulator/buiclear/Libraries/raylib/raylib/external/glfw/src/CMakeFiles/glfw.dir/null_init.c.o" \
"/home/batuhan/Desktop/DigitalSimulator/buiclear/Libraries/raylib/raylib/external/glfw/src/CMakeFiles/glfw.dir/null_monitor.c.o" \
"/home/batuhan/Desktop/DigitalSimulator/buiclear/Libraries/raylib/raylib/external/glfw/src/CMakeFiles/glfw.dir/null_window.c.o" \
"/home/batuhan/Desktop/DigitalSimulator/buiclear/Libraries/raylib/raylib/external/glfw/src/CMakeFiles/glfw.dir/null_joystick.c.o" \
"/home/batuhan/Desktop/DigitalSimulator/buiclear/Libraries/raylib/raylib/external/glfw/src/CMakeFiles/glfw.dir/posix_module.c.o" \
"/home/batuhan/Desktop/DigitalSimulator/buiclear/Libraries/raylib/raylib/external/glfw/src/CMakeFiles/glfw.dir/posix_time.c.o" \
"/home/batuhan/Desktop/DigitalSimulator/buiclear/Libraries/raylib/raylib/external/glfw/src/CMakeFiles/glfw.dir/posix_thread.c.o" \
"/home/batuhan/Desktop/DigitalSimulator/buiclear/Libraries/raylib/raylib/external/glfw/src/CMakeFiles/glfw.dir/x11_init.c.o" \
"/home/batuhan/Desktop/DigitalSimulator/buiclear/Libraries/raylib/raylib/external/glfw/src/CMakeFiles/glfw.dir/x11_monitor.c.o" \
"/home/batuhan/Desktop/DigitalSimulator/buiclear/Libraries/raylib/raylib/external/glfw/src/CMakeFiles/glfw.dir/x11_window.c.o" \
"/home/batuhan/Desktop/DigitalSimulator/buiclear/Libraries/raylib/raylib/external/glfw/src/CMakeFiles/glfw.dir/xkb_unicode.c.o" \
"/home/batuhan/Desktop/DigitalSimulator/buiclear/Libraries/raylib/raylib/external/glfw/src/CMakeFiles/glfw.dir/glx_context.c.o" \
"/home/batuhan/Desktop/DigitalSimulator/buiclear/Libraries/raylib/raylib/external/glfw/src/CMakeFiles/glfw.dir/linux_joystick.c.o" \
"/home/batuhan/Desktop/DigitalSimulator/buiclear/Libraries/raylib/raylib/external/glfw/src/CMakeFiles/glfw.dir/posix_poll.c.o"

Libraries/raylib/raylib/libraylib.a: Libraries/raylib/raylib/CMakeFiles/raylib.dir/raudio.c.o
Libraries/raylib/raylib/libraylib.a: Libraries/raylib/raylib/CMakeFiles/raylib.dir/rcore.c.o
Libraries/raylib/raylib/libraylib.a: Libraries/raylib/raylib/CMakeFiles/raylib.dir/rmodels.c.o
Libraries/raylib/raylib/libraylib.a: Libraries/raylib/raylib/CMakeFiles/raylib.dir/rshapes.c.o
Libraries/raylib/raylib/libraylib.a: Libraries/raylib/raylib/CMakeFiles/raylib.dir/rtext.c.o
Libraries/raylib/raylib/libraylib.a: Libraries/raylib/raylib/CMakeFiles/raylib.dir/rtextures.c.o
Libraries/raylib/raylib/libraylib.a: Libraries/raylib/raylib/CMakeFiles/raylib.dir/utils.c.o
Libraries/raylib/raylib/libraylib.a: Libraries/raylib/raylib/external/glfw/src/CMakeFiles/glfw.dir/context.c.o
Libraries/raylib/raylib/libraylib.a: Libraries/raylib/raylib/external/glfw/src/CMakeFiles/glfw.dir/init.c.o
Libraries/raylib/raylib/libraylib.a: Libraries/raylib/raylib/external/glfw/src/CMakeFiles/glfw.dir/input.c.o
Libraries/raylib/raylib/libraylib.a: Libraries/raylib/raylib/external/glfw/src/CMakeFiles/glfw.dir/monitor.c.o
Libraries/raylib/raylib/libraylib.a: Libraries/raylib/raylib/external/glfw/src/CMakeFiles/glfw.dir/platform.c.o
Libraries/raylib/raylib/libraylib.a: Libraries/raylib/raylib/external/glfw/src/CMakeFiles/glfw.dir/vulkan.c.o
Libraries/raylib/raylib/libraylib.a: Libraries/raylib/raylib/external/glfw/src/CMakeFiles/glfw.dir/window.c.o
Libraries/raylib/raylib/libraylib.a: Libraries/raylib/raylib/external/glfw/src/CMakeFiles/glfw.dir/egl_context.c.o
Libraries/raylib/raylib/libraylib.a: Libraries/raylib/raylib/external/glfw/src/CMakeFiles/glfw.dir/osmesa_context.c.o
Libraries/raylib/raylib/libraylib.a: Libraries/raylib/raylib/external/glfw/src/CMakeFiles/glfw.dir/null_init.c.o
Libraries/raylib/raylib/libraylib.a: Libraries/raylib/raylib/external/glfw/src/CMakeFiles/glfw.dir/null_monitor.c.o
Libraries/raylib/raylib/libraylib.a: Libraries/raylib/raylib/external/glfw/src/CMakeFiles/glfw.dir/null_window.c.o
Libraries/raylib/raylib/libraylib.a: Libraries/raylib/raylib/external/glfw/src/CMakeFiles/glfw.dir/null_joystick.c.o
Libraries/raylib/raylib/libraylib.a: Libraries/raylib/raylib/external/glfw/src/CMakeFiles/glfw.dir/posix_module.c.o
Libraries/raylib/raylib/libraylib.a: Libraries/raylib/raylib/external/glfw/src/CMakeFiles/glfw.dir/posix_time.c.o
Libraries/raylib/raylib/libraylib.a: Libraries/raylib/raylib/external/glfw/src/CMakeFiles/glfw.dir/posix_thread.c.o
Libraries/raylib/raylib/libraylib.a: Libraries/raylib/raylib/external/glfw/src/CMakeFiles/glfw.dir/x11_init.c.o
Libraries/raylib/raylib/libraylib.a: Libraries/raylib/raylib/external/glfw/src/CMakeFiles/glfw.dir/x11_monitor.c.o
Libraries/raylib/raylib/libraylib.a: Libraries/raylib/raylib/external/glfw/src/CMakeFiles/glfw.dir/x11_window.c.o
Libraries/raylib/raylib/libraylib.a: Libraries/raylib/raylib/external/glfw/src/CMakeFiles/glfw.dir/xkb_unicode.c.o
Libraries/raylib/raylib/libraylib.a: Libraries/raylib/raylib/external/glfw/src/CMakeFiles/glfw.dir/glx_context.c.o
Libraries/raylib/raylib/libraylib.a: Libraries/raylib/raylib/external/glfw/src/CMakeFiles/glfw.dir/linux_joystick.c.o
Libraries/raylib/raylib/libraylib.a: Libraries/raylib/raylib/external/glfw/src/CMakeFiles/glfw.dir/posix_poll.c.o
Libraries/raylib/raylib/libraylib.a: Libraries/raylib/raylib/CMakeFiles/raylib.dir/build.make
Libraries/raylib/raylib/libraylib.a: Libraries/raylib/raylib/CMakeFiles/raylib.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/batuhan/Desktop/DigitalSimulator/buiclear/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Linking C static library libraylib.a"
	cd /home/batuhan/Desktop/DigitalSimulator/buiclear/Libraries/raylib/raylib && $(CMAKE_COMMAND) -P CMakeFiles/raylib.dir/cmake_clean_target.cmake
	cd /home/batuhan/Desktop/DigitalSimulator/buiclear/Libraries/raylib/raylib && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/raylib.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
Libraries/raylib/raylib/CMakeFiles/raylib.dir/build: Libraries/raylib/raylib/libraylib.a
.PHONY : Libraries/raylib/raylib/CMakeFiles/raylib.dir/build

Libraries/raylib/raylib/CMakeFiles/raylib.dir/clean:
	cd /home/batuhan/Desktop/DigitalSimulator/buiclear/Libraries/raylib/raylib && $(CMAKE_COMMAND) -P CMakeFiles/raylib.dir/cmake_clean.cmake
.PHONY : Libraries/raylib/raylib/CMakeFiles/raylib.dir/clean

Libraries/raylib/raylib/CMakeFiles/raylib.dir/depend:
	cd /home/batuhan/Desktop/DigitalSimulator/buiclear && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/batuhan/Desktop/DigitalSimulator /home/batuhan/Desktop/DigitalSimulator/Libraries/raylib/src /home/batuhan/Desktop/DigitalSimulator/buiclear /home/batuhan/Desktop/DigitalSimulator/buiclear/Libraries/raylib/raylib /home/batuhan/Desktop/DigitalSimulator/buiclear/Libraries/raylib/raylib/CMakeFiles/raylib.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : Libraries/raylib/raylib/CMakeFiles/raylib.dir/depend

