add_library(sintl SHARED catgets.c catopen.c gettext_gnu.c gettext_real.c gettext_util.c gettext.c nlspath_checks.c plural_parser.c)

target_include_directories(sintl PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/../include")

set_target_properties(sintl PROPERTIES
    VERSION ${SINTL_MAJOR_VERSION}.${SINTL_MINOR_VERSION}.${SINTL_PATCH_VERSION}
)

include(${CMAKE_CURRENT_SOURCE_DIR}/../config/CMakeLists.txt)

configure_libsintl(sintl)