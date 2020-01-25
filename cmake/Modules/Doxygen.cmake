find_package(Doxygen)

if(DOXYGEN_FOUND)
    configure_file(
        "${CMAKE_SOURCE_DIR}/doc/Doxyfile.in"
        "${CMAKE_CURRENT_BINARY_DIR}/Doxyfile"
        @ONLY)
    
    add_custom_target(doxygen
        COMMAND "${DOXYGEN_EXECUTABLE}"
        COMMENT "Generating code documentation with Doxygen"
        VERBATIM)
endif()
