# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 4.0

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\CMake\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\CMake\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\borja\OneDrive\Desktop\VIU\GitHub\InformaticaGrafica\src

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\borja\OneDrive\Desktop\VIU\GitHub\InformaticaGrafica\build

# Include any dependencies generated for this target.
include CMakeFiles/02_triangle.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/02_triangle.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/02_triangle.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/02_triangle.dir/flags.make

CMakeFiles/02_triangle.dir/codegen:
.PHONY : CMakeFiles/02_triangle.dir/codegen

CMakeFiles/02_triangle.dir/projects/02_triangle/main.cpp.obj: CMakeFiles/02_triangle.dir/flags.make
CMakeFiles/02_triangle.dir/projects/02_triangle/main.cpp.obj: CMakeFiles/02_triangle.dir/includes_CXX.rsp
CMakeFiles/02_triangle.dir/projects/02_triangle/main.cpp.obj: C:/Users/borja/OneDrive/Desktop/VIU/GitHub/InformaticaGrafica/src/projects/02_triangle/main.cpp
CMakeFiles/02_triangle.dir/projects/02_triangle/main.cpp.obj: CMakeFiles/02_triangle.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=C:\Users\borja\OneDrive\Desktop\VIU\GitHub\InformaticaGrafica\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/02_triangle.dir/projects/02_triangle/main.cpp.obj"
	C:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/02_triangle.dir/projects/02_triangle/main.cpp.obj -MF CMakeFiles\02_triangle.dir\projects\02_triangle\main.cpp.obj.d -o CMakeFiles\02_triangle.dir\projects\02_triangle\main.cpp.obj -c C:\Users\borja\OneDrive\Desktop\VIU\GitHub\InformaticaGrafica\src\projects\02_triangle\main.cpp

CMakeFiles/02_triangle.dir/projects/02_triangle/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/02_triangle.dir/projects/02_triangle/main.cpp.i"
	C:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\borja\OneDrive\Desktop\VIU\GitHub\InformaticaGrafica\src\projects\02_triangle\main.cpp > CMakeFiles\02_triangle.dir\projects\02_triangle\main.cpp.i

CMakeFiles/02_triangle.dir/projects/02_triangle/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/02_triangle.dir/projects/02_triangle/main.cpp.s"
	C:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\borja\OneDrive\Desktop\VIU\GitHub\InformaticaGrafica\src\projects\02_triangle\main.cpp -o CMakeFiles\02_triangle.dir\projects\02_triangle\main.cpp.s

CMakeFiles/02_triangle.dir/src/deps/glfw/egl_context.c.obj: CMakeFiles/02_triangle.dir/flags.make
CMakeFiles/02_triangle.dir/src/deps/glfw/egl_context.c.obj: CMakeFiles/02_triangle.dir/includes_C.rsp
CMakeFiles/02_triangle.dir/src/deps/glfw/egl_context.c.obj: C:/Users/borja/OneDrive/Desktop/VIU/GitHub/InformaticaGrafica/src/src/deps/glfw/egl_context.c
CMakeFiles/02_triangle.dir/src/deps/glfw/egl_context.c.obj: CMakeFiles/02_triangle.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=C:\Users\borja\OneDrive\Desktop\VIU\GitHub\InformaticaGrafica\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/02_triangle.dir/src/deps/glfw/egl_context.c.obj"
	C:\msys64\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -W -lm -I -M -MD -MT CMakeFiles/02_triangle.dir/src/deps/glfw/egl_context.c.obj -MF CMakeFiles\02_triangle.dir\src\deps\glfw\egl_context.c.obj.d -o CMakeFiles\02_triangle.dir\src\deps\glfw\egl_context.c.obj -c C:\Users\borja\OneDrive\Desktop\VIU\GitHub\InformaticaGrafica\src\src\deps\glfw\egl_context.c

CMakeFiles/02_triangle.dir/src/deps/glfw/egl_context.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/02_triangle.dir/src/deps/glfw/egl_context.c.i"
	C:\msys64\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -W -lm -I -M -E C:\Users\borja\OneDrive\Desktop\VIU\GitHub\InformaticaGrafica\src\src\deps\glfw\egl_context.c > CMakeFiles\02_triangle.dir\src\deps\glfw\egl_context.c.i

CMakeFiles/02_triangle.dir/src/deps/glfw/egl_context.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/02_triangle.dir/src/deps/glfw/egl_context.c.s"
	C:\msys64\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -W -lm -I -M -S C:\Users\borja\OneDrive\Desktop\VIU\GitHub\InformaticaGrafica\src\src\deps\glfw\egl_context.c -o CMakeFiles\02_triangle.dir\src\deps\glfw\egl_context.c.s

CMakeFiles/02_triangle.dir/src/deps/glfw/win32_init.c.obj: CMakeFiles/02_triangle.dir/flags.make
CMakeFiles/02_triangle.dir/src/deps/glfw/win32_init.c.obj: CMakeFiles/02_triangle.dir/includes_C.rsp
CMakeFiles/02_triangle.dir/src/deps/glfw/win32_init.c.obj: C:/Users/borja/OneDrive/Desktop/VIU/GitHub/InformaticaGrafica/src/src/deps/glfw/win32_init.c
CMakeFiles/02_triangle.dir/src/deps/glfw/win32_init.c.obj: CMakeFiles/02_triangle.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=C:\Users\borja\OneDrive\Desktop\VIU\GitHub\InformaticaGrafica\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/02_triangle.dir/src/deps/glfw/win32_init.c.obj"
	C:\msys64\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -W -lm -I -M -MD -MT CMakeFiles/02_triangle.dir/src/deps/glfw/win32_init.c.obj -MF CMakeFiles\02_triangle.dir\src\deps\glfw\win32_init.c.obj.d -o CMakeFiles\02_triangle.dir\src\deps\glfw\win32_init.c.obj -c C:\Users\borja\OneDrive\Desktop\VIU\GitHub\InformaticaGrafica\src\src\deps\glfw\win32_init.c

CMakeFiles/02_triangle.dir/src/deps/glfw/win32_init.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/02_triangle.dir/src/deps/glfw/win32_init.c.i"
	C:\msys64\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -W -lm -I -M -E C:\Users\borja\OneDrive\Desktop\VIU\GitHub\InformaticaGrafica\src\src\deps\glfw\win32_init.c > CMakeFiles\02_triangle.dir\src\deps\glfw\win32_init.c.i

CMakeFiles/02_triangle.dir/src/deps/glfw/win32_init.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/02_triangle.dir/src/deps/glfw/win32_init.c.s"
	C:\msys64\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -W -lm -I -M -S C:\Users\borja\OneDrive\Desktop\VIU\GitHub\InformaticaGrafica\src\src\deps\glfw\win32_init.c -o CMakeFiles\02_triangle.dir\src\deps\glfw\win32_init.c.s

CMakeFiles/02_triangle.dir/src/deps/glfw/win32_joystick.c.obj: CMakeFiles/02_triangle.dir/flags.make
CMakeFiles/02_triangle.dir/src/deps/glfw/win32_joystick.c.obj: CMakeFiles/02_triangle.dir/includes_C.rsp
CMakeFiles/02_triangle.dir/src/deps/glfw/win32_joystick.c.obj: C:/Users/borja/OneDrive/Desktop/VIU/GitHub/InformaticaGrafica/src/src/deps/glfw/win32_joystick.c
CMakeFiles/02_triangle.dir/src/deps/glfw/win32_joystick.c.obj: CMakeFiles/02_triangle.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=C:\Users\borja\OneDrive\Desktop\VIU\GitHub\InformaticaGrafica\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object CMakeFiles/02_triangle.dir/src/deps/glfw/win32_joystick.c.obj"
	C:\msys64\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -W -lm -I -M -MD -MT CMakeFiles/02_triangle.dir/src/deps/glfw/win32_joystick.c.obj -MF CMakeFiles\02_triangle.dir\src\deps\glfw\win32_joystick.c.obj.d -o CMakeFiles\02_triangle.dir\src\deps\glfw\win32_joystick.c.obj -c C:\Users\borja\OneDrive\Desktop\VIU\GitHub\InformaticaGrafica\src\src\deps\glfw\win32_joystick.c

CMakeFiles/02_triangle.dir/src/deps/glfw/win32_joystick.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/02_triangle.dir/src/deps/glfw/win32_joystick.c.i"
	C:\msys64\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -W -lm -I -M -E C:\Users\borja\OneDrive\Desktop\VIU\GitHub\InformaticaGrafica\src\src\deps\glfw\win32_joystick.c > CMakeFiles\02_triangle.dir\src\deps\glfw\win32_joystick.c.i

CMakeFiles/02_triangle.dir/src/deps/glfw/win32_joystick.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/02_triangle.dir/src/deps/glfw/win32_joystick.c.s"
	C:\msys64\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -W -lm -I -M -S C:\Users\borja\OneDrive\Desktop\VIU\GitHub\InformaticaGrafica\src\src\deps\glfw\win32_joystick.c -o CMakeFiles\02_triangle.dir\src\deps\glfw\win32_joystick.c.s

CMakeFiles/02_triangle.dir/src/deps/glfw/win32_monitor.c.obj: CMakeFiles/02_triangle.dir/flags.make
CMakeFiles/02_triangle.dir/src/deps/glfw/win32_monitor.c.obj: CMakeFiles/02_triangle.dir/includes_C.rsp
CMakeFiles/02_triangle.dir/src/deps/glfw/win32_monitor.c.obj: C:/Users/borja/OneDrive/Desktop/VIU/GitHub/InformaticaGrafica/src/src/deps/glfw/win32_monitor.c
CMakeFiles/02_triangle.dir/src/deps/glfw/win32_monitor.c.obj: CMakeFiles/02_triangle.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=C:\Users\borja\OneDrive\Desktop\VIU\GitHub\InformaticaGrafica\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building C object CMakeFiles/02_triangle.dir/src/deps/glfw/win32_monitor.c.obj"
	C:\msys64\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -W -lm -I -M -MD -MT CMakeFiles/02_triangle.dir/src/deps/glfw/win32_monitor.c.obj -MF CMakeFiles\02_triangle.dir\src\deps\glfw\win32_monitor.c.obj.d -o CMakeFiles\02_triangle.dir\src\deps\glfw\win32_monitor.c.obj -c C:\Users\borja\OneDrive\Desktop\VIU\GitHub\InformaticaGrafica\src\src\deps\glfw\win32_monitor.c

CMakeFiles/02_triangle.dir/src/deps/glfw/win32_monitor.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/02_triangle.dir/src/deps/glfw/win32_monitor.c.i"
	C:\msys64\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -W -lm -I -M -E C:\Users\borja\OneDrive\Desktop\VIU\GitHub\InformaticaGrafica\src\src\deps\glfw\win32_monitor.c > CMakeFiles\02_triangle.dir\src\deps\glfw\win32_monitor.c.i

CMakeFiles/02_triangle.dir/src/deps/glfw/win32_monitor.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/02_triangle.dir/src/deps/glfw/win32_monitor.c.s"
	C:\msys64\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -W -lm -I -M -S C:\Users\borja\OneDrive\Desktop\VIU\GitHub\InformaticaGrafica\src\src\deps\glfw\win32_monitor.c -o CMakeFiles\02_triangle.dir\src\deps\glfw\win32_monitor.c.s

CMakeFiles/02_triangle.dir/src/deps/glfw/win32_thread.c.obj: CMakeFiles/02_triangle.dir/flags.make
CMakeFiles/02_triangle.dir/src/deps/glfw/win32_thread.c.obj: CMakeFiles/02_triangle.dir/includes_C.rsp
CMakeFiles/02_triangle.dir/src/deps/glfw/win32_thread.c.obj: C:/Users/borja/OneDrive/Desktop/VIU/GitHub/InformaticaGrafica/src/src/deps/glfw/win32_thread.c
CMakeFiles/02_triangle.dir/src/deps/glfw/win32_thread.c.obj: CMakeFiles/02_triangle.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=C:\Users\borja\OneDrive\Desktop\VIU\GitHub\InformaticaGrafica\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building C object CMakeFiles/02_triangle.dir/src/deps/glfw/win32_thread.c.obj"
	C:\msys64\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -W -lm -I -M -MD -MT CMakeFiles/02_triangle.dir/src/deps/glfw/win32_thread.c.obj -MF CMakeFiles\02_triangle.dir\src\deps\glfw\win32_thread.c.obj.d -o CMakeFiles\02_triangle.dir\src\deps\glfw\win32_thread.c.obj -c C:\Users\borja\OneDrive\Desktop\VIU\GitHub\InformaticaGrafica\src\src\deps\glfw\win32_thread.c

CMakeFiles/02_triangle.dir/src/deps/glfw/win32_thread.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/02_triangle.dir/src/deps/glfw/win32_thread.c.i"
	C:\msys64\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -W -lm -I -M -E C:\Users\borja\OneDrive\Desktop\VIU\GitHub\InformaticaGrafica\src\src\deps\glfw\win32_thread.c > CMakeFiles\02_triangle.dir\src\deps\glfw\win32_thread.c.i

CMakeFiles/02_triangle.dir/src/deps/glfw/win32_thread.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/02_triangle.dir/src/deps/glfw/win32_thread.c.s"
	C:\msys64\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -W -lm -I -M -S C:\Users\borja\OneDrive\Desktop\VIU\GitHub\InformaticaGrafica\src\src\deps\glfw\win32_thread.c -o CMakeFiles\02_triangle.dir\src\deps\glfw\win32_thread.c.s

CMakeFiles/02_triangle.dir/src/deps/glfw/win32_time.c.obj: CMakeFiles/02_triangle.dir/flags.make
CMakeFiles/02_triangle.dir/src/deps/glfw/win32_time.c.obj: CMakeFiles/02_triangle.dir/includes_C.rsp
CMakeFiles/02_triangle.dir/src/deps/glfw/win32_time.c.obj: C:/Users/borja/OneDrive/Desktop/VIU/GitHub/InformaticaGrafica/src/src/deps/glfw/win32_time.c
CMakeFiles/02_triangle.dir/src/deps/glfw/win32_time.c.obj: CMakeFiles/02_triangle.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=C:\Users\borja\OneDrive\Desktop\VIU\GitHub\InformaticaGrafica\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building C object CMakeFiles/02_triangle.dir/src/deps/glfw/win32_time.c.obj"
	C:\msys64\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -W -lm -I -M -MD -MT CMakeFiles/02_triangle.dir/src/deps/glfw/win32_time.c.obj -MF CMakeFiles\02_triangle.dir\src\deps\glfw\win32_time.c.obj.d -o CMakeFiles\02_triangle.dir\src\deps\glfw\win32_time.c.obj -c C:\Users\borja\OneDrive\Desktop\VIU\GitHub\InformaticaGrafica\src\src\deps\glfw\win32_time.c

CMakeFiles/02_triangle.dir/src/deps/glfw/win32_time.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/02_triangle.dir/src/deps/glfw/win32_time.c.i"
	C:\msys64\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -W -lm -I -M -E C:\Users\borja\OneDrive\Desktop\VIU\GitHub\InformaticaGrafica\src\src\deps\glfw\win32_time.c > CMakeFiles\02_triangle.dir\src\deps\glfw\win32_time.c.i

CMakeFiles/02_triangle.dir/src/deps/glfw/win32_time.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/02_triangle.dir/src/deps/glfw/win32_time.c.s"
	C:\msys64\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -W -lm -I -M -S C:\Users\borja\OneDrive\Desktop\VIU\GitHub\InformaticaGrafica\src\src\deps\glfw\win32_time.c -o CMakeFiles\02_triangle.dir\src\deps\glfw\win32_time.c.s

CMakeFiles/02_triangle.dir/src/deps/glfw/win32_window.c.obj: CMakeFiles/02_triangle.dir/flags.make
CMakeFiles/02_triangle.dir/src/deps/glfw/win32_window.c.obj: CMakeFiles/02_triangle.dir/includes_C.rsp
CMakeFiles/02_triangle.dir/src/deps/glfw/win32_window.c.obj: C:/Users/borja/OneDrive/Desktop/VIU/GitHub/InformaticaGrafica/src/src/deps/glfw/win32_window.c
CMakeFiles/02_triangle.dir/src/deps/glfw/win32_window.c.obj: CMakeFiles/02_triangle.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=C:\Users\borja\OneDrive\Desktop\VIU\GitHub\InformaticaGrafica\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building C object CMakeFiles/02_triangle.dir/src/deps/glfw/win32_window.c.obj"
	C:\msys64\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -W -lm -I -M -MD -MT CMakeFiles/02_triangle.dir/src/deps/glfw/win32_window.c.obj -MF CMakeFiles\02_triangle.dir\src\deps\glfw\win32_window.c.obj.d -o CMakeFiles\02_triangle.dir\src\deps\glfw\win32_window.c.obj -c C:\Users\borja\OneDrive\Desktop\VIU\GitHub\InformaticaGrafica\src\src\deps\glfw\win32_window.c

CMakeFiles/02_triangle.dir/src/deps/glfw/win32_window.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/02_triangle.dir/src/deps/glfw/win32_window.c.i"
	C:\msys64\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -W -lm -I -M -E C:\Users\borja\OneDrive\Desktop\VIU\GitHub\InformaticaGrafica\src\src\deps\glfw\win32_window.c > CMakeFiles\02_triangle.dir\src\deps\glfw\win32_window.c.i

CMakeFiles/02_triangle.dir/src/deps/glfw/win32_window.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/02_triangle.dir/src/deps/glfw/win32_window.c.s"
	C:\msys64\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -W -lm -I -M -S C:\Users\borja\OneDrive\Desktop\VIU\GitHub\InformaticaGrafica\src\src\deps\glfw\win32_window.c -o CMakeFiles\02_triangle.dir\src\deps\glfw\win32_window.c.s

CMakeFiles/02_triangle.dir/src/deps/glfw/wgl_context.c.obj: CMakeFiles/02_triangle.dir/flags.make
CMakeFiles/02_triangle.dir/src/deps/glfw/wgl_context.c.obj: CMakeFiles/02_triangle.dir/includes_C.rsp
CMakeFiles/02_triangle.dir/src/deps/glfw/wgl_context.c.obj: C:/Users/borja/OneDrive/Desktop/VIU/GitHub/InformaticaGrafica/src/src/deps/glfw/wgl_context.c
CMakeFiles/02_triangle.dir/src/deps/glfw/wgl_context.c.obj: CMakeFiles/02_triangle.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=C:\Users\borja\OneDrive\Desktop\VIU\GitHub\InformaticaGrafica\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building C object CMakeFiles/02_triangle.dir/src/deps/glfw/wgl_context.c.obj"
	C:\msys64\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -W -lm -I -M -MD -MT CMakeFiles/02_triangle.dir/src/deps/glfw/wgl_context.c.obj -MF CMakeFiles\02_triangle.dir\src\deps\glfw\wgl_context.c.obj.d -o CMakeFiles\02_triangle.dir\src\deps\glfw\wgl_context.c.obj -c C:\Users\borja\OneDrive\Desktop\VIU\GitHub\InformaticaGrafica\src\src\deps\glfw\wgl_context.c

CMakeFiles/02_triangle.dir/src/deps/glfw/wgl_context.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/02_triangle.dir/src/deps/glfw/wgl_context.c.i"
	C:\msys64\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -W -lm -I -M -E C:\Users\borja\OneDrive\Desktop\VIU\GitHub\InformaticaGrafica\src\src\deps\glfw\wgl_context.c > CMakeFiles\02_triangle.dir\src\deps\glfw\wgl_context.c.i

CMakeFiles/02_triangle.dir/src/deps/glfw/wgl_context.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/02_triangle.dir/src/deps/glfw/wgl_context.c.s"
	C:\msys64\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -W -lm -I -M -S C:\Users\borja\OneDrive\Desktop\VIU\GitHub\InformaticaGrafica\src\src\deps\glfw\wgl_context.c -o CMakeFiles\02_triangle.dir\src\deps\glfw\wgl_context.c.s

CMakeFiles/02_triangle.dir/src/deps/glfw/osmesa_context.c.obj: CMakeFiles/02_triangle.dir/flags.make
CMakeFiles/02_triangle.dir/src/deps/glfw/osmesa_context.c.obj: CMakeFiles/02_triangle.dir/includes_C.rsp
CMakeFiles/02_triangle.dir/src/deps/glfw/osmesa_context.c.obj: C:/Users/borja/OneDrive/Desktop/VIU/GitHub/InformaticaGrafica/src/src/deps/glfw/osmesa_context.c
CMakeFiles/02_triangle.dir/src/deps/glfw/osmesa_context.c.obj: CMakeFiles/02_triangle.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=C:\Users\borja\OneDrive\Desktop\VIU\GitHub\InformaticaGrafica\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building C object CMakeFiles/02_triangle.dir/src/deps/glfw/osmesa_context.c.obj"
	C:\msys64\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -W -lm -I -M -MD -MT CMakeFiles/02_triangle.dir/src/deps/glfw/osmesa_context.c.obj -MF CMakeFiles\02_triangle.dir\src\deps\glfw\osmesa_context.c.obj.d -o CMakeFiles\02_triangle.dir\src\deps\glfw\osmesa_context.c.obj -c C:\Users\borja\OneDrive\Desktop\VIU\GitHub\InformaticaGrafica\src\src\deps\glfw\osmesa_context.c

CMakeFiles/02_triangle.dir/src/deps/glfw/osmesa_context.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/02_triangle.dir/src/deps/glfw/osmesa_context.c.i"
	C:\msys64\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -W -lm -I -M -E C:\Users\borja\OneDrive\Desktop\VIU\GitHub\InformaticaGrafica\src\src\deps\glfw\osmesa_context.c > CMakeFiles\02_triangle.dir\src\deps\glfw\osmesa_context.c.i

CMakeFiles/02_triangle.dir/src/deps/glfw/osmesa_context.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/02_triangle.dir/src/deps/glfw/osmesa_context.c.s"
	C:\msys64\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -W -lm -I -M -S C:\Users\borja\OneDrive\Desktop\VIU\GitHub\InformaticaGrafica\src\src\deps\glfw\osmesa_context.c -o CMakeFiles\02_triangle.dir\src\deps\glfw\osmesa_context.c.s

CMakeFiles/02_triangle.dir/src/deps/glfw/win32_module.c.obj: CMakeFiles/02_triangle.dir/flags.make
CMakeFiles/02_triangle.dir/src/deps/glfw/win32_module.c.obj: CMakeFiles/02_triangle.dir/includes_C.rsp
CMakeFiles/02_triangle.dir/src/deps/glfw/win32_module.c.obj: C:/Users/borja/OneDrive/Desktop/VIU/GitHub/InformaticaGrafica/src/src/deps/glfw/win32_module.c
CMakeFiles/02_triangle.dir/src/deps/glfw/win32_module.c.obj: CMakeFiles/02_triangle.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=C:\Users\borja\OneDrive\Desktop\VIU\GitHub\InformaticaGrafica\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Building C object CMakeFiles/02_triangle.dir/src/deps/glfw/win32_module.c.obj"
	C:\msys64\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -W -lm -I -M -MD -MT CMakeFiles/02_triangle.dir/src/deps/glfw/win32_module.c.obj -MF CMakeFiles\02_triangle.dir\src\deps\glfw\win32_module.c.obj.d -o CMakeFiles\02_triangle.dir\src\deps\glfw\win32_module.c.obj -c C:\Users\borja\OneDrive\Desktop\VIU\GitHub\InformaticaGrafica\src\src\deps\glfw\win32_module.c

CMakeFiles/02_triangle.dir/src/deps/glfw/win32_module.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/02_triangle.dir/src/deps/glfw/win32_module.c.i"
	C:\msys64\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -W -lm -I -M -E C:\Users\borja\OneDrive\Desktop\VIU\GitHub\InformaticaGrafica\src\src\deps\glfw\win32_module.c > CMakeFiles\02_triangle.dir\src\deps\glfw\win32_module.c.i

CMakeFiles/02_triangle.dir/src/deps/glfw/win32_module.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/02_triangle.dir/src/deps/glfw/win32_module.c.s"
	C:\msys64\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -W -lm -I -M -S C:\Users\borja\OneDrive\Desktop\VIU\GitHub\InformaticaGrafica\src\src\deps\glfw\win32_module.c -o CMakeFiles\02_triangle.dir\src\deps\glfw\win32_module.c.s

# Object files for target 02_triangle
02_triangle_OBJECTS = \
"CMakeFiles/02_triangle.dir/projects/02_triangle/main.cpp.obj" \
"CMakeFiles/02_triangle.dir/src/deps/glfw/egl_context.c.obj" \
"CMakeFiles/02_triangle.dir/src/deps/glfw/win32_init.c.obj" \
"CMakeFiles/02_triangle.dir/src/deps/glfw/win32_joystick.c.obj" \
"CMakeFiles/02_triangle.dir/src/deps/glfw/win32_monitor.c.obj" \
"CMakeFiles/02_triangle.dir/src/deps/glfw/win32_thread.c.obj" \
"CMakeFiles/02_triangle.dir/src/deps/glfw/win32_time.c.obj" \
"CMakeFiles/02_triangle.dir/src/deps/glfw/win32_window.c.obj" \
"CMakeFiles/02_triangle.dir/src/deps/glfw/wgl_context.c.obj" \
"CMakeFiles/02_triangle.dir/src/deps/glfw/osmesa_context.c.obj" \
"CMakeFiles/02_triangle.dir/src/deps/glfw/win32_module.c.obj"

# External object files for target 02_triangle
02_triangle_EXTERNAL_OBJECTS =

02_triangle.exe: CMakeFiles/02_triangle.dir/projects/02_triangle/main.cpp.obj
02_triangle.exe: CMakeFiles/02_triangle.dir/src/deps/glfw/egl_context.c.obj
02_triangle.exe: CMakeFiles/02_triangle.dir/src/deps/glfw/win32_init.c.obj
02_triangle.exe: CMakeFiles/02_triangle.dir/src/deps/glfw/win32_joystick.c.obj
02_triangle.exe: CMakeFiles/02_triangle.dir/src/deps/glfw/win32_monitor.c.obj
02_triangle.exe: CMakeFiles/02_triangle.dir/src/deps/glfw/win32_thread.c.obj
02_triangle.exe: CMakeFiles/02_triangle.dir/src/deps/glfw/win32_time.c.obj
02_triangle.exe: CMakeFiles/02_triangle.dir/src/deps/glfw/win32_window.c.obj
02_triangle.exe: CMakeFiles/02_triangle.dir/src/deps/glfw/wgl_context.c.obj
02_triangle.exe: CMakeFiles/02_triangle.dir/src/deps/glfw/osmesa_context.c.obj
02_triangle.exe: CMakeFiles/02_triangle.dir/src/deps/glfw/win32_module.c.obj
02_triangle.exe: CMakeFiles/02_triangle.dir/build.make
02_triangle.exe: libEngineLib.a
02_triangle.exe: CMakeFiles/02_triangle.dir/linkLibs.rsp
02_triangle.exe: CMakeFiles/02_triangle.dir/objects1.rsp
02_triangle.exe: CMakeFiles/02_triangle.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=C:\Users\borja\OneDrive\Desktop\VIU\GitHub\InformaticaGrafica\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_12) "Linking CXX executable 02_triangle.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\02_triangle.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/02_triangle.dir/build: 02_triangle.exe
.PHONY : CMakeFiles/02_triangle.dir/build

CMakeFiles/02_triangle.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\02_triangle.dir\cmake_clean.cmake
.PHONY : CMakeFiles/02_triangle.dir/clean

CMakeFiles/02_triangle.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\borja\OneDrive\Desktop\VIU\GitHub\InformaticaGrafica\src C:\Users\borja\OneDrive\Desktop\VIU\GitHub\InformaticaGrafica\src C:\Users\borja\OneDrive\Desktop\VIU\GitHub\InformaticaGrafica\build C:\Users\borja\OneDrive\Desktop\VIU\GitHub\InformaticaGrafica\build C:\Users\borja\OneDrive\Desktop\VIU\GitHub\InformaticaGrafica\build\CMakeFiles\02_triangle.dir\DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/02_triangle.dir/depend

