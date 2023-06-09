cmake_minimum_required(VERSION 3.1 FATAL_ERROR)

project(protonlithium1)

find_package(Geant4 REQUIRED ui_all vis_all)

include(${Geant4_USE_FILE})

file(GLOB sources ${PROJECT_SOURCE_DIR}/*.cc)
file(GLOB headers ${PROJECT_SOURCE_DIR}/*.hh)

file(GLOB MACRO_FILES
	"*.mac"
)
file(COPY ${MACRO_FILES} DESTINATION ${PROJECT_BINARY_DIR})

file(GLOB PYTHON_FILES
	"*.py"
)
file(COPY ${PYTHON_FILES} DESTINATION ${PROJECT_BINARY_DIR})

add_executable(pli1 pli1.cc ${sources} ${headers})
target_link_libraries(pli1 ${Geant4_LIBRARIES})

add_custom_target(protonlithium1 DEPENDS pli1)