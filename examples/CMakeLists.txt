add_executable("examples_macos_app" MACOSX_BUNDLE "main.h" "main.m")
# Make all headers available via project absolute paths.
target_include_directories("examples_macos_app" PRIVATE "${PROJECT_SOURCE_DIR}")
target_link_libraries(
  "examples_macos_app"
  "-lobjc"
  "-framework AppKit"
  "-framework Cocoa"
  "-framework CoreGraphics"
  "-framework Foundation"
)
target_compile_options(
  "examples_macos_app"
  PRIVATE "-fobjc-arc"
          "-fvisibility=hidden"
          "-fno-exceptions"
          "-fno-rtti"
          "$<$<NOT:$<CONFIG:Debug>>:-flto=thin>"
)
target_compile_definitions(
  "examples_macos_app"
  PRIVATE "$<$<CONFIG:Debug>:DEBUG>"
          "$<$<CONFIG:Debug>:_DEBUG>"
          "$<$<NOT:$<CONFIG:Debug>>:NDEBUG>"
)
set_target_properties(
  "examples_macos_app"
  PROPERTIES MACOSX_BUNDLE YES
             MACOSX_BUNDLE_INFO_PLIST "${CMAKE_CURRENT_SOURCE_DIR}/Info.plist"
             XCODE_ATTRIBUTE_ENABLE_TESTABILITY YES
             XCODE_ATTRIBUTE_PRODUCT_BUNDLE_IDENTIFIER
             "com.nickchavez.apple-gfx-base.example-app"
)
