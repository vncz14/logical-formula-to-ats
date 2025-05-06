cmake_minimum_required(VERSION 3.16)
project(LogicalFormulaToATS)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(GRAMMAR_DIR ${CMAKE_CURRENT_SOURCE_DIR}/grammars)
set(BUILD_DIR ${CMAKE_CURRENT_BINARY_DIR}/build)
set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(ANTLR_RUNTIME_DIR $ENV{ANTLR_RUNTIME_DIR})
if(NOT ANTLR_RUNTIME_DIR)
    message(FATAL_ERROR "set env variable ANTLR_RUNTIME_DIR to path of antlr4 c++ runtime")
endif()

include_directories(${ANTLR_RUNTIME_DIR}/runtime/src)
include_directories(${CMAKE_BINARY_DIR}/build)
include_directories(${SRC_DIR})

find_program(ANTLR4_EXECUTABLE antlr4 REQUIRED)

file(GLOB GRAMMAR_FILES ${GRAMMAR_DIR}/*.g4)

set(GENERATED_FILES)
foreach(GRAMMAR_FILE ${GRAMMAR_FILES})
    get_filename_component(GRAMMAR_NAME ${GRAMMAR_FILE} NAME_WE)
    add_custom_command(
        OUTPUT ${BUILD_DIR}/${GRAMMAR_NAME}Lexer.cpp ${BUILD_DIR}/${GRAMMAR_NAME}Lexer.h
               ${BUILD_DIR}/${GRAMMAR_NAME}Parser.cpp ${BUILD_DIR}/${GRAMMAR_NAME}Parser.h
        COMMAND ${ANTLR4_EXECUTABLE} -Dlanguage=Cpp -o ${BUILD_DIR} ${GRAMMAR_FILE}
        DEPENDS ${GRAMMAR_FILE}
    )
    list(APPEND GENERATED_FILES
        ${BUILD_DIR}/${GRAMMAR_NAME}Lexer.cpp
        ${BUILD_DIR}/${GRAMMAR_NAME}Parser.cpp
    )
endforeach()

set(SOURCE_FILES
    ${SRC_DIR}/TypeChecker.cpp
    ${SRC_DIR}/Symbol.cpp

    ${SRC_DIR}/main.cpp

    ${GENERATED_FILES}
)

add_executable(LogicalFormulaToATS ${SOURCE_FILES})
target_link_libraries(LogicalFormulaToATS ${ANTLR_RUNTIME_DIR}/../libantlr4-runtime.a)