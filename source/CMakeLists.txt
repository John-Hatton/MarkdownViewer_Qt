file(GLOB_RECURSE SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

# Add Headers for MOC when you create a QOBJECT
set(HEADERS
        # QObject Headers
        ../include/MarkdownRenderer.hpp
        ../include/MarkdownViewer.hpp
        ../include/FolderMenu.hpp

)

set (SOURCES
        resources.qrc
)

add_executable(${PROJECT_NAME} ${HEADERS} ${SOURCE_FILES} ${SOURCES} )

set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::Core Qt6::Widgets)
