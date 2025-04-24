add_executable(processing_server
        ProcessingServer.cpp
        ProcessingServer.h
        StartProcessingServer.cpp
        ../socket/Socket.cpp
        ../socket/Socket.h
)

target_include_directories(processing_server PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_SOURCE_DIR}/socket
)
