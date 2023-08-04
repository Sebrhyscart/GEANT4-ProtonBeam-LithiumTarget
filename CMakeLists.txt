cmake_minimum_required(VERSION 3.1 FATAL_ERROR)

project(protonlithium2)

find_package(Geant4 REQUIRED ui_all vis_all)

include(${Geant4_USE_FILE})

file(GLOB sources ${PROJECT_SOURCE_DIR}/*.cc)
file(GLOB headers ${PROJECT_SOURCE_DIR}/*.hh)

file(GLOB MACRO_FILES
	"*.mac"
)
file(COPY ${MACRO_FILES} DESTINATION ${PROJECT_BINARY_DIR})

add_executable(ProtonLi protonli.cc ${sources} ${headers})
target_link_libraries(ProtonLi ${Geant4_LIBRARIES})

add_custom_target(protonlithium2 DEPENDS ProtonLi)