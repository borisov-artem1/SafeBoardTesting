add_executable(client_app
        Client.cpp
        Client.h
        StartClient.cpp
        ../socket/Socket.cpp
        ../socket/Socket.h
)

target_include_directories(client_app PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_SOURCE_DIR}/socket
)
