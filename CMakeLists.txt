cmake_minimum_required(VERSION 2.8.4)
project("udp")

set(CMAKE_CXX_FLAGS "-std=c++11 -fPIC")
set(CMAKE_C_FLAGS "-std=c++11 -fPIC")

find_package(Threads)

include_directories(client)
aux_source_directory(client DIR_CLIENT)

include_directories(server)
aux_source_directory(server DIR_SERVER)

include_directories(ntp_client)
aux_source_directory(ntp_client DIR_NTP_CLIENT)

#windows项目
IF(WIN32)
#udp客户端
add_executable(udpClient ${DIR_CLIENT})
target_link_libraries(udpClient ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries(udpClient ws2_32)

#服务端
add_executable(udpServer ${DIR_SERVER})
target_link_libraries(udpServer ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries(udpServer ws2_32)
#linux项目
ELSEIF()

ENDIF()

#跨平台项目
#NTP 授时客户端linux/windows
add_executable(ntpClient ${DIR_NTP_CLIENT})
target_link_libraries(ntpClient ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries(ntpClient ws2_32)
