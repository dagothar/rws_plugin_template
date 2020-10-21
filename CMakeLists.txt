CMAKE_MINIMUM_REQUIRED(VERSION 2.6.0)

########################################################################
#
# Project name
# CHANGE THIS
#
########################################################################
PROJECT(rws_plugin_template)

SET(ROOT ${CMAKE_CURRENT_SOURCE_DIR})

########################################################################
#
# Find RobWork libraries
# UNCOMMENT RobWorkSim and ODE ENTRIES IF NEEDED
#
########################################################################
SET(RW_ROOT "$ENV{RW_ROOT}")
SET(RWS_ROOT "$ENV{RWS_ROOT}")
SET(RWSIM_ROOT "$ENV{RWSIM_ROOT}")
SET(RobWork_DIR ${RW_ROOT}/cmake)
SET(RobWorkStudio_DIR ${RWS_ROOT}/cmake)
#SET(RobWorkSim_DIR ${RWSIM_ROOT}/cmake)

SET(CMAKE_BUILD_TYPE Release)

FIND_PACKAGE(RobWork REQUIRED)
FIND_PACKAGE(RobWorkStudio REQUIRED)
#FIND_PACKAGE(RobWorkSim REQUIRED)
#FIND_PACKAGE(ODE)

INCLUDE_DIRECTORIES(
	${ROBWORK_INCLUDE_DIRS}
	${ROBWORKSTUDIO_INCLUDE_DIRS}
	# ${ROBWORKSIM_INCLUDE_DIRS}
)
LINK_DIRECTORIES(
	${ROBWORK_LIBRARY_DIRS}
	${ROBWORKSTUDIO_LIBRARY_DIRS}
	# ${ROBWORKSIM_LIBRARY_DIRS}
)

########################################################################
#
# Configure output directories & misc. settings
#
########################################################################
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${ROOT}/bin" CACHE PATH "Runtime directory" FORCE)
SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${ROOT}/libs" CACHE PATH "Library directory" FORCE)
SET(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${ROOT}/libs" CACHE PATH "Archive directory" FORCE)

add_definitions(-std=c++11)

########################################################################
#
# Specify source files
# CHANGE FILE NAMES AS NECCESARY
#
########################################################################

# UI files
SET(
  UisFiles
  src/rws_plugin_template.ui
)

# HPP files
SET(
  MocHeaders
  src/rws_plugin_template.hpp
) 

# CPP files        
SET(
  SrcFiles
  src/rws_plugin_template.cpp
) 

########################################################################
#
# Wrap MOC headers & resources
#
########################################################################
SET(MocSrcFiles)
QT5_WRAP_CPP(MocSrcFiles ${MocHeaders})
SET(RccSrcFiles)
QT5_ADD_RESOURCES(
  RccSrcFiles
  src/resources.qrc
)
QT5_WRAP_UI(UiHeaders ${UisFiles})

SET(CMAKE_INCLUDE_CURRENT_DIR ON)
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_BINARY_DIR})

########################################################################
#
# Add targets
# CHANGE TARGET NAME. THIS WILL BECOME THE LIBRARY NAME ACCORDING
# TO THE FOLLOWING FORMAT: lib<target name>.so
# ADD LIBRARIES AS REQUIRED.
# UNCOMMMENT RobWorkSim IF REQUIRED.
#
########################################################################
add_library(rws_plugin_template MODULE ${SrcFiles} ${MocSrcFiles} ${RccSrcFiles} ${UiHeaders})
target_link_libraries(rws_plugin_template -lGL -lGLU -lglut -lm
  ${ROBWORKSTUDIO_LIBRARIES}
  ${ROBWORK_LIBRARIES}
  #${ROBWORKSIM_LIBRARIES}
)
