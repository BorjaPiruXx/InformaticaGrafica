# Include paths for deps
set(INCLUDE_PATHS
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/src/deps/glfw
)

# Common Dependency Files
set(DEPS_SRC_FILES_COMMON
    ${CMAKE_CURRENT_SOURCE_DIR}/src/deps/glfw/platform.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/deps/glfw/mappings.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/deps/glfw/context.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/deps/glfw/init.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/deps/glfw/input.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/deps/glfw/monitor.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/deps/glfw/platform.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/deps/glfw/window.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/deps/glfw/vulkan.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/deps/glfw/null_init.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/deps/glfw/null_monitor.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/deps/glfw/null_window.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/deps/glfw/null_joystick.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/deps/glfw/null_joystick.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/deps/glad/glad.c
)

# Linux Dependency Files
set(DEPS_SRC_FILES_LINUX
    ${CMAKE_CURRENT_SOURCE_DIR}/src/deps/glfw/glx_context.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/deps/glfw/x11_init.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/deps/glfw/x11_monitor.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/deps/glfw/x11_platform.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/deps/glfw/x11_window.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/deps/glfw/egl_context.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/deps/glfw/posix_time.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/deps/glfw/posix_thread.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/deps/glfw/linux_joystick.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/deps/glfw/xkb_unicode.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/deps/glfw/osmesa_context.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/deps/glfw/posix_module.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/deps/glfw/posix_time.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/deps/glfw/posix_thread.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/deps/glfw/linux_joystick.h
)

# Remove warnings for deps files
set_source_files_properties(
    ${DEPS_SRC_FILES_COMMON}
    ${DEPS_SRC_FILES_WIN}
    ${DEPS_SRC_FILES_LINUX}
    ${DEPS_SRC_FILES_MACOS}
    PROPERTIES
    COMPILE_FLAGS "-W0"
)