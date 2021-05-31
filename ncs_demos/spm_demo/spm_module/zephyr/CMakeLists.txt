if(CONFIG_SPM)
add_child_image_from_source(
  NAME spm
  SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR}/spm
  )
endif()
