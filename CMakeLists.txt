cmake_minimum_required(VERSION 3.10)

project(
    FiBot
    VERSION 0.0.1
    DESCRIPTION "Make Your First Robot"
    LANGUAGES C ASM
)

set(ARCH arm)
set(CPU cortex-m3)
set(BOARD bluepill)
set(CROSS_COMPILE arm-none-eabi-)

set(CMAKE_C_COMPILER ${CROSS_COMPILE}gcc)
set(CMAKE_AR ${CROSS_COMPILE}ar)

set(CMAKE_C_FLAGS "\
    -nostdlib \
    -mcpu=${CPU} -mthumb -c \
    -Wall -fdata-sections -ffunction-sections \
    -DSTM32F10X_MD -DUSE_STDPERIPH_DRIVER \
")

include_directories(include)

# config project directory
set(PROJECT_DIR default)

# add_subdirectory(lib)
add_subdirectory(drivers)
add_subdirectory("projects/${PROJECT_DIR}")