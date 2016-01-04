set(CONFIGS
  default.yaml
  )

set(RESOURCES_CFG ${SOLAR_RES_PATH}/config)

add_custom_command(
  OUTPUT resource-dir POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E make_directory ${SOLAR_RES_PATH}
  COMMAND ${CMAKE_COMMAND} -E make_directory ${SOLAR_RES_PATH}/config
  )

add_custom_target(resources ALL DEPENDS resource-dir)

foreach(cfg ${CONFIGS})
  add_custom_command(
    TARGET resources POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/${cfg} ${RESOURCES_CFG}
    COMMAND ${CMAKE_COMMAND} -E echo "copying ${cfg} to ${RESOURCES_CFG}"
    DEPENDS resource-dir ${CMAKE_CURRENT_SOURCE_DIR}/${cfg}
    )
endforeach(cfg ${CONFIGS})
