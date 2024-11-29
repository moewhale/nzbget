set(CONF_FILE nzbget.conf)
set(SHARE_DIR_DEST ${CMAKE_INSTALL_PREFIX}/share/${PACKAGE})
set(DOC_FILES_SRC ${CMAKE_SOURCE_DIR}/ChangeLog.md ${CMAKE_SOURCE_DIR}/COPYING)
set(CONF_FILE_SRC ${CMAKE_SOURCE_DIR}/${CONF_FILE})
set(WEBUI_DIR_SRC ${CMAKE_SOURCE_DIR}/webui)
set(DOC_FILES_DEST ${SHARE_DIR_DEST}/doc)
set(WEBUI_DIR_DEST ${SHARE_DIR_DEST})
set(TEMPLATE_CONF_FILE_DEST ${SHARE_DIR_DEST})
set(CONF_FILE_DEST ${CMAKE_INSTALL_PREFIX}/etc)
set(BIN_FILE_DEST ${CMAKE_INSTALL_PREFIX}/bin)

file(READ ${CONF_FILE_SRC} CONFIG_CONTENT)
string(REPLACE "WebDir=" "WebDir=${WEBUI_DIR_DEST}/webui" MODIFIED_CONFIG_CONTENT "${CONFIG_CONTENT}")
string(REPLACE "ConfigTemplate=" "ConfigTemplate=${TEMPLATE_CONF_FILE_DEST}/${CONF_FILE}" MODIFIED_CONFIG_CONTENT "${MODIFIED_CONFIG_CONTENT}")
file(WRITE ${CMAKE_BINARY_DIR}/${CONF_FILE} ${MODIFIED_CONFIG_CONTENT})

install(TARGETS ${PACKAGE} PERMISSIONS 
	OWNER_EXECUTE 
	OWNER_WRITE 
	OWNER_READ 
	GROUP_READ 
	GROUP_EXECUTE
	WORLD_READ 
	WORLD_EXECUTE
	DESTINATION ${BIN_FILE_DEST}
)
install(DIRECTORY ${WEBUI_DIR_SRC} DESTINATION ${WEBUI_DIR_DEST})
install(FILES ${DOC_FILES_SRC} DESTINATION ${DOC_FILES_DEST})
install(FILES ${CMAKE_BINARY_DIR}/${CONF_FILE} DESTINATION ${TEMPLATE_CONF_FILE_DEST})

add_custom_target(uninstall
	COMMAND ${CMAKE_COMMAND} -E remove_directory ${DOC_FILES_DEST}
	COMMAND ${CMAKE_COMMAND} -E remove_directory ${SHARE_DIR_DEST}
	COMMAND ${CMAKE_COMMAND} -E remove ${BIN_FILE_DEST}/${PACKAGE}
	COMMENT "Uninstalling" ${PACKAGE}
)

add_custom_target(install-conf
	COMMAND ${CMAKE_COMMAND} -E make_directory ${CONF_FILE_DEST}
	COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_BINARY_DIR}/${CONF_FILE} ${CONF_FILE_DEST}/${CONF_FILE}
	COMMENT "Installing nzbget.conf"
)

add_custom_target(uninstall-conf
	COMMAND ${CMAKE_COMMAND} -E remove ${CONF_FILE_DEST}/${CONF_FILE}
	COMMENT "Unstalling nzbget.conf"
)