function (configure_libsintl targetName)
    include(CheckSymbolExists)

    check_symbol_exists(fstat64 "sys/stat.h" HAVE_FSTAT64)
    check_symbol_exists(getauxval "sys/auxv.h" HAVE_GETAUXVAL)
    check_symbol_exists(issetugid "unistd.h" HAVE_ISSETUGID)

    set(ExtraCompileOptions "")

    if(${HAVE_FSTAT64})
        string(APPEND ExtraCompileOptions "-DHAVE_STAT64")
        message("Configuration options: Have fstat64: ${HAVE_FSTAT64}")
    else()
        message("Configuration options: Have fstat64: no")
    endif()

    if(${HAVE_GETAUXVAL})
        string(APPEND ExtraCompileOptions "-DHAVE_GATAUXVAL")
        message("Configuration options: Have getauxval: ${HAVE_GETAUXVAL}")
    else()
        message("Configuration options: Have getauxval: no")
    endif()

    if(${HAVE_ISSETUGID})
        string(APPEND ExtraCompileOptions "-DHAVE_ISSETUGID")
        message("Configuration options: Have issetugid: ${HAVE_ISSETUGID}")
    else()
        message("Configuration options: Have issetugid: no")
    endif()

    target_compile_options(${targetName} PRIVATE ${ExtraCompileOptions})
endfunction()