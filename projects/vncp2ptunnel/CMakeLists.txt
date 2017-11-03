#/**********************************************************\ 
# 
# Auto-generated CMakeLists.txt for the vncp2ptunnel project
#
#\**********************************************************/

# Written to work with cmake 2.6
cmake_minimum_required (VERSION 2.6)
set (CMAKE_BACKWARDS_COMPATIBILITY 2.6)

Project(${PLUGIN_NAME})

file (GLOB GENERAL RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
    [^.]*.cpp
    [^.]*.h
    [^.]*.cmake
    )

include_directories(${PLUGIN_INCLUDE_DIRS})

# Generated files are stored in ${GENERATED} by the project configuration
SET_SOURCE_FILES_PROPERTIES(
    ${GENERATED}
    PROPERTIES
        GENERATED 1
    )

SOURCE_GROUP(Generated FILES
    ${GENERATED}
    )

SET( SOURCES
    ${GENERAL}
    ${GENERATED}
    )
	
# This will include Win/projectDef.cmake, X11/projectDef.cmake, Mac/projectDef 
# depending on the platform
include_platform()

#################################################################################################
#系统环境	
set(THIS_PLATFORM	Unkown)
if(WIN32)
     set(THIS_PLATFORM Windows)
elseif(UNIX)
     set(THIS_PLATFORM Linux)
endif()

#获取编译类型
#list的第一项的索引是0。如果<element index>小于等于-1
set(TMP_THIS_BUILD_TYPE "")
list (APPEND TMP_THIS_BUILD_TYPE debug Debug optimized  Release)
list (GET TMP_THIS_BUILD_TYPE 0 THIS_BUILD_TYPE)	
	
# 添加自己的程序库
# set lib name, we will auto add debug lib as LibName_d.lib, and add relese lib as LibName.lib.
set(MY_LIBS
	ProxyManagerWinMigrate
	#.. 添加其他的库...
)
set(MY_LINK_LIST "")
foreach(x ${MY_LIBS})

	#include是相对FireBreath1.7\projects\${PROJECT_NAME}\目录的
	include_directories(../../../lib/${x}/${THIS_PLATFORM}/include)
	#lib是相对${PROJECT_NAME}.sln的。
	list (APPEND MY_LINK_LIST debug ../../../../lib/${x}/${THIS_PLATFORM}/lib/${x}_d optimized ../../../../lib/${x}/${THIS_PLATFORM}/lib/${x})
endforeach()
target_link_libraries(${PROJECT_NAME} ${MY_LINK_LIST} )		

#设置输出目录
#set_target_properties(${PROJECT_NAME} PROPERTIES  RUNTIME_OUTPUT_DIRECTORY ../../../../bin/WinDebug/)
set(DSTDIR ../../../../bin/Win${THIS_BUILD_TYPE}/ )
message("------------------------------")
message(${DSTDIR})
set_target_properties(${PROJECT_NAME} PROPERTIES  RUNTIME_OUTPUT_DIRECTORY ${DSTDIR} )


#################################################################################################

#this will build a Chrome package
#add_chrome_package(${PLUGIN_NAME}
#	${FB_BIN_DIR}/${PLUGIN_NAME}/${CMAKE_CFG_INTDIR}/ 
#	"${FB_BIN_DIR}/${PLUGIN_NAME}/${CMAKE_CFG_INTDIR}/${FBSTRING_PluginFileName}.dll"
#	"${CMAKE_CURRENT_SOURCE_DIR}/sign/package_key.pem"
#	${PROJECT_NAME})

#this will build a XPI package using XPISigner (see http://code.google.com/p/xpisigner/ )
# add_signed_xpi_installer(${PLUGIN_NAME}
# 	${FB_BIN_DIR}/${PLUGIN_NAME}/${CMAKE_CFG_INTDIR}/ 
#   "${FB_BIN_DIR}/${PLUGIN_NAME}/${CMAKE_CFG_INTDIR}/${FBSTRING_PluginFileName}.dll"
# 	$ENV{XPI_PATH} 
# 	"${CMAKE_CURRENT_SOURCE_DIR}/sign/certificate.pfx" 
# 	"${CMAKE_CURRENT_SOURCE_DIR}/sign/passphrase.txt"
# 	${PROJECT_NAME})

