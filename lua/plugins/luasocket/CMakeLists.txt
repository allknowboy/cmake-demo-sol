include_directories(
    ${PROJECT_SOURCE_DIR}/lua
)

add_library(socket_core STATIC auxiliar.c buffer.c compat.c except.c inet.c io.c luasocket.c options.c select.c tcp.c timeout.c udp.c wsocket.c )
set_target_properties(socket_core PROPERTIES PREFIX "")
target_link_libraries(socket_core ws2_32 lualib)

add_library(mime_core STATIC compat.c mime.c )
set_target_properties(mime_core PROPERTIES PREFIX "")
target_link_libraries(mime_core lualib)

install(
    FILES
    mime.lua
    socket.lua
    ltn12.lua
    DESTINATION ${PROJECT_SOURCE_DIR}/dist/data/luascripts
)

install(
    FILES
    smtp.lua
    ftp.lua
    headers.lua
    http.lua
    tp.lua
    url.lua
    DESTINATION ${PROJECT_SOURCE_DIR}/dist/data/luascripts/socket
)
