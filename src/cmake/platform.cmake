# Configures a target for a specific platform
function(configure_platform TARGET_NAME)

    if(WIN32)

        target_sources(${TARGET_NAME} PRIVATE ${DEPS_SRC_FILES_WIN})
        target_link_libraries(${TARGET_NAME} PRIVATE OpenGL32)
        target_compile_definitions(${TARGET_NAME} PRIVATE -D_GLFW_WIN32 -D_GLFW_WGL)
        source_group(Deps FILES ${DEPS_SRC_FILES_COMMON} ${DEPS_SRC_FILES_WIN})
    
    elseif(UNIX AND NOT APPLE)
    
        target_sources(${TARGET_NAME} PRIVATE ${DEPS_SRC_FILES_LINUX})
        target_link_libraries(${TARGET_NAME} PRIVATE X11 Xrandr Xcursor Xinerama Xi Xxf86vm pthread dl)
        target_compile_definitions(${TARGET_NAME} PRIVATE -D_GLFW_X11 -D_GLFW_HAS_GLXGETPROCADDRESS -D_GLFW_GLX)
        source_group(Deps FILES ${DEPS_SRC_FILES_COMMON} ${DEPS_SRC_FILES_LINUX})
    
    elseif(APPLE)
        target_sources(${TARGET_NAME} PRIVATE ${DEPS_SRC_FILES_MACOS})
        target_link_libraries(${TARGET_NAME} PRIVATE "-framework Cocoa" "-framework OpenGL" "-framework CoreVideo" "-framework IOKit")
        target_compile_definitions(${TARGET_NAME} PRIVATE -D_GLFW_COCOA -D_GLFW_NSGL)
        source_group(Deps FILES ${DEPS_SRC_FILES_COMMON} ${DEPS_SRC_FILES_MACOS})
    
    endif()
    
endfunction()