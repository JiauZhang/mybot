file(GLOB DRIVERS_SRCS "${CMAKE_CURRENT_SOURCE_DIR}/*.c")
add_library(drivers ${DRIVERS_SRCS})