# .
include(${CMAKE_CURRENT_LIST_DIR}/CopyRecursive.cmake)

copy_recursive(${SRC_PATH} ${DST_PATH} ${PATTERN})
