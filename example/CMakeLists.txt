add_executable(echo_server EchoServer.cc)
target_link_libraries(echo_server src)

add_executable(echo_client EchoClient.cc)
target_link_libraries(echo_client src)

add_executable(discard_server DiscardServer.cc)
target_link_libraries(discard_server src)

add_executable(chargen_server ChargenServer.cc)
target_link_libraries(chargen_server src)

add_executable(timer TimerLoop.cc)
target_link_libraries(timer src)

#add_subdirectory(echo_bench)
# add_subdirectory(nqueen)
# add_subdirectory(kth_element)