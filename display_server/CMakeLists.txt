add_executable(display_server
        DisplayServer.cpp
        DisplayServer.h
        StartDisplayServer.cpp
        ../socket/Socket.cpp
        ../socket/Socket.h
        ../processing_server/ProcessingServer.h
        ../processing_server/ProcessingServer.cpp
)

target_include_directories(display_server PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_SOURCE_DIR}/socket
        ${CMAKE_SOURCE_DIR}/processing_server
)
