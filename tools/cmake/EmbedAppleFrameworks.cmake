# Embeds frameworks and dylibs into an Apple (macOS, iOS, tvOS) app bundle. Also
# adds the Frameworks/ folder to the apps' rpath locations. TARGET is the
# MACOSX_BUNDLE executable in which to embed the frameworks. FRAMEWORKS is a
# list of library targets (frameworks or dylibs) to embed into the app bundle's
# Frameworks/ folder.
function(embed_apple_frameworks)
  cmake_parse_arguments(
    FUNC_ARG
    ""
    "TARGET"
    "FRAMEWORKS"
    ${ARGN}
  )

  target_link_libraries(
    "${FUNC_ARG_TARGET}" PRIVATE "-Wl,-rpath,@loader_path/../Frameworks/"
  )

  if("${CMAKE_GENERATOR}"
     STREQUAL
     "Xcode"
  )
    set_target_properties(
      "${FUNC_ARG_TARGET}"
      PROPERTIES XCODE_EMBED_FRAMEWORKS "${FUNC_ARG_FRAMEWORKS}"
                 XCODE_EMBED_FRAMEWORKS_REMOVE_HEADERS_ON_COPY YES
                 XCODE_EMBED_FRAMEWORKS_CODE_SIGN_ON_COPY YES
    )

  else()
    # TODO: This doesn't re-code-sign the bundle after the addition of the
    # frameworks, like set_target_properties(...
    # XCODE_EMBED_FRAMEWORKS_CODE_SIGN_ON_COPY YES) does.
    set("MACOSX_BUNDLE_FRAMEWORKS_DIR"
        "$<PATH:GET_PARENT_PATH,$<TARGET_FILE:${FUNC_ARG_TARGET}>>/../Frameworks"
    )
    foreach("FRAMEWORK" IN LISTS FUNC_ARG_FRAMEWORKS)
      add_custom_command(
        TARGET "${FUNC_ARG_TARGET}"
        POST_BUILD
        COMMAND "mkdir" "-p" "${MACOSX_BUNDLE_FRAMEWORKS_DIR}"
        COMMAND "cp" "$<TARGET_FILE:${FRAMEWORK}>"
                "${MACOSX_BUNDLE_FRAMEWORKS_DIR}"
        VERBATIM
      )
    endforeach()
  endif()

endfunction()
