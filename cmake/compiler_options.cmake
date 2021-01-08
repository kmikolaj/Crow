# Compiler options with hardening flags

if(MSVC)

  list(APPEND compiler_options 
    /W4
    /permissive-
    $<$<CONFIG:RELEASE>:/O2 /Ob2 >
    $<$<CONFIG:MINSIZEREL>:/O1 /Ob1>
    $<$<CONFIG:RELWITHDEBINFO>:/Zi /O2 /Ob1>
    $<$<CONFIG:DEBUG>:/Zi /Ob0 /Od /RTC1>)

else(MSVC)

  list(APPEND compiler_options 
    -Wall
    -Wextra
    -Wpedantic
    $<$<CONFIG:RELEASE>:-O2>
    $<$<CONFIG:DEBUG>:-O0>
    $<$<CONFIG:DEBUG>:-g>
    $<$<CONFIG:DEBUG>:-p>
    $<$<CONFIG:DEBUG>:-pg>)

endif()

# This can also be done with target_compile_options() [recommended]
set(CMAKE_CXX_FLAGS "${compiler_options}")