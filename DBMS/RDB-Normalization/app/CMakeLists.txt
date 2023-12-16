set(SOURCES
    main.cpp   
)

add_executable(main ${SOURCES})
target_link_libraries(main normalizer)