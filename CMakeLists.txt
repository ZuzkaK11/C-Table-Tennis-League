cmake_minimum_required(VERSION 3.26)
project(project_league)

set(TARGET_NAME project_league)
project(${TARGET_NAME})

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES
        Player.cpp
        Player.h
        Match.cpp
        Match.h
        League.cpp
        League.h
        Ordering.cpp
        Read_write.cpp
        ListPlayers.cpp
        ListPlayers.h
        ListMatches.cpp
        ListMatches.h
        Change.cpp
)

set(TEST_FILES
        test1.cpp
        test2.cpp
        test3.cpp
        test4.cpp
)

set(GTEST_SOURCE_FILES
        GoogleTest/gtest-death-test.cc
        GoogleTest/gtest-filepath.cc
        GoogleTest/gtest-port.cc
        GoogleTest/gtest-printers.cc
        GoogleTest/gtest-test-part.cc
        GoogleTest/gtest-typed-test.cc
        GoogleTest/gtest.cc
        GoogleTest/gtest_main.cc)

add_library(tests OBJECT ${TEST_FILES})
add_library(gtest OBJECT ${GTEST_SOURCE_FILES})

find_package(Threads REQUIRED)

include_directories(GoogleTest)
add_executable(${TARGET_NAME} ${SOURCE_FILES} ${TEST_FILES} ${GTEST_SOURCE_FILES})
target_link_libraries(${TARGET_NAME} ${CMAKE_THREAD_LIBS_INIT})

add_custom_command(TARGET project_league PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/names_correct.txt
        ${CMAKE_SOURCE_DIR}/names_wrong.txt
        ${CMAKE_SOURCE_DIR}/match_result.txt
        ${CMAKE_SOURCE_DIR}/planMatch_correct.txt
        ${CMAKE_SOURCE_DIR}/planMatch_wrong.txt
        $<TARGET_FILE_DIR:project_league>
       VERBATIM)