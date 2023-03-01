add_executable(${PROJECT_NAME}
        main.cxx
        memory.cxx
        util.cxx)

# .hxx files
target_include_directories(${PROJECT_NAME} PRIVATE "${PROJECT_SOURCE_DIR}/include")