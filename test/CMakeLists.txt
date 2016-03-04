SET(sqltest)
INCLUDE_DIRECTORIES(
${PROJECT_SOURCE_DIR}/include
.
/produit/cppsqlx/include
)


LINK_DIRECTORIES(
/produit/cppsqlx/lib/
)

ADD_EXECUTABLE(sqltest
main.cpp
)

TARGET_LINK_LIBRARIES(sqltest  cppsqlx odbc pthread boost_system boost_filesystem boost_program_options xerces-c log4cpp)

INSTALL(TARGETS sqltest DESTINATION bin)

