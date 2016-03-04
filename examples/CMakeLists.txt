SET(sqlexamples)

INCLUDE_DIRECTORIES(
${PROJECT_SOURCE_DIR}/include
.
/produit/cppsqlx/include
)


LINK_DIRECTORIES(
/produit/cppsqlx/lib/
)

ADD_EXECUTABLE(main_repo_pwf_query
main_repo_pwf_query.cpp
)

TARGET_LINK_LIBRARIES(main_repo_pwf_query cppsqlx odbc pthread boost_system boost_filesystem boost_program_options xerces-c log4cpp)

INSTALL(TARGETS main_repo_pwf_query DESTINATION bin)

