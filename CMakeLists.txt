#/****************************************************************************
# Copyright (c) 2013-2014 cocos2d-x.org
# Copyright (c) 2015-2017 Chukong Technologies Inc.
#
# http://www.cocos2d-x.org
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:

# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.

# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
# THE SOFTWARE.
# ****************************************************************************/

cmake_minimum_required(VERSION 3.6)

set(APP_NAME shootingProject)

project(${APP_NAME})


set(CK_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/Classes/cricket)

include_directories(
        ${CK_ROOT}/inc
)

link_directories(
        ${CK_ROOT}/lib/android/ndk/${ANDROID_ABI}/debug
)
link_libraries(
        ${CK_ROOT}/lib/android/ndk/${ANDROID_ABI}/debug/libck.a
)

include(AndroidNdkModules)
android_ndk_import_module_cpufeatures()

target_link_libraries(
        cpufeatures
)


set(COCOS2DX_ROOT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cocos2d)
set(CMAKE_MODULE_PATH ${COCOS2DX_ROOT_PATH}/cmake/Modules/)

include(CocosBuildSet)
add_subdirectory(${COCOS2DX_ROOT_PATH}/cocos ${ENGINE_BINARY_PATH}/cocos/core)

# record sources, headers, resources...
set(GAME_SOURCE)
set(GAME_HEADER)

set(GAME_RES_FOLDER
    "${CMAKE_CURRENT_SOURCE_DIR}/Resources"
    )
if(APPLE OR WINDOWS)
    cocos_mark_multi_resources(common_res_files RES_TO "Resources" FOLDERS ${GAME_RES_FOLDER})
endif()

# add cross-platforms source files and header files 
list(APPEND GAME_SOURCE
     Classes/_DebugOut/_DebugConOut.cpp
     Classes/_DebugOut/_DebugDispOut.cpp
     Classes/CricketJni/CricketJni.cpp
     Classes/Effekseer/Effekseer.cpp
     Classes/Effekseer/EffekseerNative.cpp
     Classes/Effekseer/EffekseerRendererNative.cpp
     Classes/Input/OprtKey.cpp
     Classes/Input/OprtTouch.cpp
     Classes/Input/OprtState.cpp
     Classes/Input/UseKey.cpp
     Classes/Manager/AnimManager.cpp
     Classes/Manager/AudioManager.cpp
     Classes/Manager/EffManager.cpp
     Classes/Manager/ResourceManager.cpp
     Classes/Map/MapMaker.cpp
     Classes/Scene/GameScene.cpp
     Classes/Scene/TitleScene.cpp
     Classes/Module/HitCheck.cpp
     Classes/Module/Jump.cpp
     Classes/Module/Move.cpp
     Classes/Module/DirCheck.cpp
     Classes/Module/Fall.cpp
     Classes/Module/AnimUpdate.cpp
     Classes/Module/ActModule.cpp
     Classes/Module/SetPos.cpp
     Classes/Module/shooting.cpp
     Classes/Module/OldKeyUpdate.cpp
     Classes/Module/DamageCheck.cpp
     Classes/Module/changeChara.cpp
     Classes/Unit/Player.cpp
     Classes/Unit/Enemy.cpp
     Classes/Unit/Character.cpp
     Classes/Unit/Shot.cpp
     Classes/AppDelegate.cpp
     )
list(APPEND GAME_HEADER
     Classes/_DebugOut/_DebugConOut.h
     Classes/_DebugOut/_DebugDispOut.h
     Classes/CricketJni/CricketJni.h
     Classes/Effekseer/Effekseer.h
     Classes/Effekseer/EffekseerNative.h
     Classes/Effekseer/EffekseerRendererNative.h
     Classes/Input/OprtKey.h
     Classes/Input/OprtTouch.h
     Classes/Input/OprtState.h
     Classes/Input/UseKey.h
     Classes/Manager/AnimManager.h
     Classes/Manager/AudioManager.h
     Classes/Manager/EffManager.h
     Classes/Manager/ResourceManager.h
     Classes/Map/MapMaker.h
     Classes/Scene/GameScene.h
     Classes/Scene/TitleScene.h
     Classes/Module/ActSet.h
     Classes/Module/HitCheck.h
     Classes/Module/Jump.h
     Classes/Module/Move.h
     Classes/Module/DirCheck.h
     Classes/Module/Fall.h
     Classes/Module/AnimUpdate.h
     Classes/Module/ActModule.h
     Classes/Module/SetPos.h
     Classes/Module/shooting.h
     Classes/Module/OldKeyUpdate.h
     Classes/Module/DamageCheck.h
     Classes/Module/changeChara.h
     Classes/Unit/Player.h
     Classes/Unit/Enemy.h
     Classes/Unit/Character.h
     Classes/Unit/Shot.h
     Classes/Unit/charaStruct.h
     Classes/AppDelegate.h
)
if(ANDROID)
    # change APP_NAME to the share library name for Android, it's value depend on AndroidManifest.xml
    set(APP_NAME MyGame)
    list(APPEND GAME_SOURCE
         proj.android/app/jni/hellocpp/main.cpp
         )
elseif(LINUX)
    list(APPEND GAME_SOURCE
         proj.linux/main.cpp
         )
elseif(WINDOWS)
    list(APPEND GAME_HEADER
         proj.win32/main.h
         proj.win32/resource.h
         )
    list(APPEND GAME_SOURCE
         proj.win32/main.cpp
         proj.win32/game.rc
         ${common_res_files}
         )
elseif(APPLE)
    if(IOS)
        list(APPEND GAME_HEADER
             proj.ios_mac/ios/AppController.h
             proj.ios_mac/ios/RootViewController.h
             )
        set(APP_UI_RES
            proj.ios_mac/ios/LaunchScreen.storyboard
            proj.ios_mac/ios/LaunchScreenBackground.png
            proj.ios_mac/ios/Images.xcassets
            )
        list(APPEND GAME_SOURCE
             proj.ios_mac/ios/main.m
             proj.ios_mac/ios/AppController.mm
             proj.ios_mac/ios/RootViewController.mm
             proj.ios_mac/ios/Prefix.pch
             ${APP_UI_RES}
             )
    elseif(MACOSX)
        set(APP_UI_RES
            proj.ios_mac/mac/Icon.icns
            proj.ios_mac/mac/Info.plist
            )
        list(APPEND GAME_SOURCE
             proj.ios_mac/mac/main.cpp
             proj.ios_mac/mac/Prefix.pch
             ${APP_UI_RES}
             )
    endif()
    list(APPEND GAME_SOURCE ${common_res_files})
endif()

# mark app complie info and libs info
set(all_code_files
    ${GAME_HEADER}
    ${GAME_SOURCE}
    )
if(NOT ANDROID)
    add_executable(${APP_NAME} ${all_code_files})
else()
    add_library(${APP_NAME} SHARED ${all_code_files})
    add_subdirectory(${COCOS2DX_ROOT_PATH}/cocos/platform/android ${ENGINE_BINARY_PATH}/cocos/platform)
    target_link_libraries(${APP_NAME} -Wl,--whole-archive cpp_android_spec -Wl,--no-whole-archive)
endif()

target_link_libraries(${APP_NAME} cocos2d)
target_include_directories(${APP_NAME}
        PRIVATE Classes
        PRIVATE ${COCOS2DX_ROOT_PATH}/cocos/audio/include/
)

# mark app resources
setup_cocos_app_config(${APP_NAME})
if(APPLE)
    set_target_properties(${APP_NAME} PROPERTIES RESOURCE "${APP_UI_RES}")
    if(MACOSX)
        set_target_properties(${APP_NAME} PROPERTIES
                              MACOSX_BUNDLE_INFO_PLIST "${CMAKE_CURRENT_SOURCE_DIR}/proj.ios_mac/mac/Info.plist"
                              )
    elseif(IOS)
        cocos_pak_xcode(${APP_NAME} INFO_PLIST "iOSBundleInfo.plist.in")
        set_xcode_property(${APP_NAME} ASSETCATALOG_COMPILER_APPICON_NAME "AppIcon")
        set_xcode_property(${APP_NAME} DEVELOPMENT_TEAM "")
        set_xcode_property(${APP_NAME} CODE_SIGN_IDENTITY "iPhone Developer")
    endif()
elseif(WINDOWS)
    cocos_copy_target_dll(${APP_NAME})
endif()

if(LINUX OR WINDOWS)
    set(APP_RES_DIR "$<TARGET_FILE_DIR:${APP_NAME}>/Resources")
    cocos_copy_target_res(${APP_NAME} COPY_TO ${APP_RES_DIR} FOLDERS ${GAME_RES_FOLDER})
endif()