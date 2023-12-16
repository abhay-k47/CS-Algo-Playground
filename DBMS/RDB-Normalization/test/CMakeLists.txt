set(SOURCES
    test.cpp)

add_executable(normalizer_test ${SOURCES})
target_link_libraries(normalizer_test normalizer)