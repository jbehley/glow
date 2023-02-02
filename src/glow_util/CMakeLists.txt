if(X11_FOUND)
    add_library(glow_util
        STATIC
            GlCamera.cpp
            RoSeCamera.cpp
            FpsCamera.cpp
            RandomColorGenerator.cpp
            X11OffscreenContext.cpp
    )

    target_link_libraries(glow_util 
        PUBLIC
            ${X11_LIBRARIES}
            ${OPENGL_LIBRARIES} 
            ${GLEW_LIBRARIES}
    )

else()
    add_library(glow_util
        STATIC
            src/glow/util/GlCamera.cpp
            src/glow/util/RoSeCamera.cpp
            src/glow/util/FpsCamera.cpp
            src/glow/util/RandomColorGenerator.cpp
    )

    target_link_libraries(glow_util 
        PUBLIC
            ${OPENGL_LIBRARIES}
            ${GLEW_LIBRARIES}
)
endif()

target_include_directories(glow_util 
    PUBLIC
        ${CMAKE_SOURCE_DIR}/include
)

target_compile_options(glow_util PUBLIC "$<$<CONFIG:Debug>:${GCC_COMPILE_DEBUG_OPTIONS}>")
target_compile_options(glow_util PUBLIC "$<$<CONFIG:Release>:${GCC_COMPILE_RELEASE_OPTIONS}>")
target_compile_definitions(glow_util PUBLIC "${GL_DEFINITIONS}")
target_compile_features(glow_util PUBLIC cxx_std_11)