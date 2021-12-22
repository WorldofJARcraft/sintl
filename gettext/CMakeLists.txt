add_executable(gettext gettext.c)

target_include_directories(gettext PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/../include")
target_link_libraries(gettext sintl)

# ngettext can be a hardlink to gettext
ADD_CUSTOM_TARGET(ngettext ALL
                  COMMAND ${CMAKE_COMMAND} -E create_symlink ngettext gettext)