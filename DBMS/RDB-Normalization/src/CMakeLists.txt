set(
    SOURCES
    attribute_set.cpp
    dependency.cpp
    dependency_set.cpp
    normalizer.cpp
    parser.cpp
    utils.cpp
    schema.cpp
    database.cpp
)
set(
    HEADERS
    ../include/attribute_set.hpp
    ../include/dependency.hpp
    ../include/dependency_set.hpp
    ../include/normalizer.hpp
    ../include/parser.hpp
    ../include/utils.hpp
    ../include/schema.hpp
    ../include/database.hpp
)

add_library(normalizer SHARED ${SOURCES} ${HEADERS})
