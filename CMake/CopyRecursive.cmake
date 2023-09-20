# (c) Elias Steurer 2023 | found at: https://gitlab.com/-/snippets/2104675
# This will copy all files and folders once when you run cmake.
# This example copies all files (REGEX == "*") from the source/MyData/ dir to the build dir
# copy_recursive("${CMAKE_CURRENT_SOURCE_DIR}/MyData" "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}" "*")
function(copy_recursive SOURCE_PATH DESTINATION_PATH REGEX)

    file(GLOB_RECURSE
        FILES
        ${SOURCE_PATH}
        "${SOURCE_PATH}/${REGEX}")
    message(STATUS "Preparing glob '${SOURCE_PATH}/${REGEX}' ...")

    foreach(file ${FILES})
        # To recreate the same folder structure we first need to read the base folder
        file(RELATIVE_PATH RELATIVE_FILE_PATH ${SOURCE_PATH} ${file})
        get_filename_component(FOLDER ${RELATIVE_FILE_PATH} DIRECTORY ${SOURCE_PATH})
        file(MAKE_DIRECTORY ${DESTINATION_PATH}/${FOLDER})
        message(STATUS "COPY ${file} -> ${DESTINATION_PATH}/${RELATIVE_FILE_PATH}")
        configure_file(${file} "${DESTINATION_PATH}/${RELATIVE_FILE_PATH}" COPYONLY)
    endforeach()

endfunction()
