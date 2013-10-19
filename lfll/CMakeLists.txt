file(GLOB HEADERS_FILES *.h)

install(FILES
    ${HEADERS_FILES}
    DESTINATION "${INSTALL_INCLUDE_DIR}/lfll")

add_custom_target(lfll SOURCES ${HEADERS_FILES})
