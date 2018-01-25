
cmake_policy(SET CMP0017 NEW)
set (CMAKE_CXX_STANDARD 11)

cmake_minimum_required(VERSION 3.1)

set(APP_NAME Template)
project (${APP_NAME})

set(COCOS2D_ROOT ${CMAKE_SOURCE_DIR}/cocos2d)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${COCOS2D_ROOT}/cmake/Modules/")
include(CocosBuildHelpers)
set(cocos_root /Users/oleh/Documents/tools/cocos2d-x-3.16)


# Some macro definitions
if(MACOSX OR APPLE)
  ADD_DEFINITIONS (-DCC_TARGET_OS_MAC)
  ADD_DEFINITIONS (-DUSE_FILE32API)
  set(PLATFORM_FOLDER mac)
elseif(LINUX)
  ADD_DEFINITIONS(-DLINUX)
  set(PLATFORM_FOLDER linux)
elseif(ANDROID)
  ADD_DEFINITIONS (-DUSE_FILE32API)
  set(PLATFORM_FOLDER android)
else()
  message( FATAL_ERROR "Unsupported platform, CMake will exit" )
endif()

add_subdirectory(${COCOS2D_ROOT})

if(ANDROID)
    set(PLATFORM_SPECIFIC_SRC proj.android/jni/main.cpp)
    set(RES_PREFIX "/Resources")
elseif(IOS)
    set(PLATFORM_SPECIFIC_SRC
            proj.ios_mac/ios/main.m
            proj.ios_mac/ios/AppController.mm
            proj.ios_mac/ios/RootViewController.mm
            )

elseif(MACOSX OR APPLE)
    set(PLATFORM_SPECIFIC_SRC proj.ios_mac/mac/main.cpp)
    
    set(MACOSX_BUNDLE_BUNDLE_NAME "\${PRODUCT_NAME}")
    set(MACOSX_BUNDLE_INFO_PLIST proj.ios_mac/mac/Info.plist)
    set(MACOSX_BUNDLE_ICON_FILE Icon)
    set(MACOSX_BUNDLE_GUI_IDENTIFIER org.cocos2dx.hellocpp)
    set(MACOSX_BUNDLE_SHORT_VERSION_STRING 1.0)
    set(MACOSX_BUNDLE_BUNDLE_VERSION 1)
    set(MACOSX_BUNDLE_COPYRIGHT "Copyright © 2017. All rights reserved.")

    file(GLOB_RECURSE RES_FILES Resources/*)
    cocos_mark_resources(FILES ${RES_FILES} BASEDIR Resources)
    file(GLOB_RECURSE RES_ICON proj.ios_mac/mac/Icon.icns)
    cocos_mark_resources(FILES ${RES_ICON} BASEDIR proj.ios_mac/mac)

    list(APPEND PLATFORM_SPECIFIC_SRC ${RES_FILES} ${RES_ICON})

elseif(LINUX)
    set(PLATFORM_SPECIFIC_SRC proj.linux/main.cpp)
    set(RES_PREFIX "/Resources")
else()
    message( FATAL_ERROR "Unsupported platform, CMake will exit" )

endif()

include_directories(
	/usr/local/include/GLFW
	/usr/include/GLFW
	${cocos_root}
	${cocos_root}/cocos
	${cocos_root}/external
	${cocos_root}/cocos/platform
	${cocos_root}/cocos/audio/include/
	Classes
        Classes/ImGUI
        Classes/flatbuffers
        Classes/custom_nodes
        Classes/include
)
if ( MACOSX OR APPLE )
    include_directories(
            ${COCOS2D_ROOT}/external/glfw3/include/mac
    )
endif ()

set(IMGUI_SRC
        Classes/ImGUI/CCIMGUI.cpp
        Classes/ImGUI/imgui.cpp
        Classes/ImGUI/imgui_demo.cpp
        Classes/ImGUI/imgui_draw.cpp
        Classes/ImGUI/imgui_impl_glfw_mac.cpp
        Classes/ImGUI/IMGUIGLViewImpl.cpp
        Classes/ImGUI/ImGuiLayer.cpp
        )
set(IMGUI_INC
        Classes/ImGUI/CCIMGUI.h
        Classes/ImGUI/imconfig.h
        Classes/ImGUI/imgui_impl_glfw.h
        Classes/ImGUI/imgui_internal.h
        Classes/ImGUI/IMGUIGLViewImpl.h
        Classes/ImGUI/ImGuiLayer.h
        Classes/ImGUI/stb_rect_pack.h
        Classes/ImGUI/stb_textedit.h
        Classes/ImGUI/stb_truetype.h
        Classes/ImGUI/stb_image.h
        )

set(GAME_SRC
        Classes/AppDelegate.cpp
        Classes/MainScene.cpp
        Classes/RessourceManager.cpp
        Classes/FileManager.cpp
        Classes/NodeBuilder.cpp
        Classes/EditNodeBuilder.cpp
        #        Classes/box2dSpecific/b2DebugLayer.cpp
        #        Classes/box2dSpecific/b2DebugDraw.cpp
        Classes/custom_nodes/NanoVgNode.cpp
        Classes/custom_nodes/DragNDropManager.cpp
        Classes/PhysicsBuilder.cpp
        ${IMGUI_SRC}
        ${PLATFORM_SPECIFIC_SRC}
        )




set(GAME_HEADERS
        Classes/include/AppDelegate.h
        Classes/include/MainScene.h
        Classes/include/EditNodeBuilder.h
        Classes/include/FileManager.h
        Classes/include/MainScene.h
        Classes/include/NodeBuilder.h
        Classes/include/PhysicsBuilder.h
        Classes/include/RessourceManager.h

        Classes/EditorRoot_generated.h
        ${IMGUI_INC}
        ${PLATFORM_SPECIFIC_HEADERS}
        Classes/ModelLoader.cpp Classes/include/ModelLoader.h)


# add the executable
if(ANDROID)
    add_library(${APP_NAME} SHARED ${GAME_SRC} ${GAME_HEADERS})
    IF(CMAKE_BUILD_TYPE STREQUAL "Release")
        ADD_CUSTOM_COMMAND(TARGET ${APP_NAME} POST_BUILD COMMAND ${CMAKE_STRIP} lib${APP_NAME}.so)
    ENDIF()
else()
    add_executable(${APP_NAME} ${GAME_SRC} ${GAME_HEADERS})
endif()

target_link_libraries(${APP_NAME} cocos2d ${CMAKE_CURRENT_SOURCE_DIR}/Classes/flatbuffers/libflatbuffers.a)


if(MACOSX OR APPLE)
    set_target_properties(${APP_NAME} PROPERTIES
            MACOSX_BUNDLE 1
            LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib/$<CONFIG>"
            ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib/$<CONFIG>"
            RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/$<CONFIG>"
            )

else()

    set(APP_BIN_DIR "${CMAKE_BINARY_DIR}/bin")

    set_target_properties(${APP_NAME} PROPERTIES
            RUNTIME_OUTPUT_DIRECTORY  "${APP_BIN_DIR}")
    add_custom_command(TARGET ${APP_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/Resources $<TARGET_FILE_DIR:${APP_NAME}>${RES_PREFIX}
            )

endif()
