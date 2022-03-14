
add_library( ChatProtocolLib STATIC
    include/ProtocolType.hpp
    src/ProtocolType.cpp
)

target_include_directories(ChatProtocolLib
                           INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include
                           )


