cmake_minimum_required (VERSION 2.8.11)

project(sintl)

set(SINTL_MAJOR_VERSION "0")
set(SINTL_MINOR_VERSION "1")
set(SINTL_PATCH_VERSION "1")

# the sintl library
add_subdirectory(libsintl)
# the gettext / ngettext utilities
add_subdirectory(gettext)
# the msgfmt / xgettext utilities
add_subdirectory(msgfmt)