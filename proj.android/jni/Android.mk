LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

$(call import-add-path,$(LOCAL_PATH)/../../cocos2d)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/external)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/cocos)

LOCAL_MODULE := cocos2dcpp_shared

LOCAL_MODULE_FILENAME := libcocos2dcpp

LOCAL_SRC_FILES := App/main.cpp \
                   ../../Classes/AppDelegate.cpp \
                   ../../Classes/GameManager.cpp \
                   ../../Classes/Scene/GameScene.cpp \
                   ../../Classes/Scene/MenuScene.cpp \
                   ../../Classes/Layer/GameLayer/GameLayer.cpp \
                   ../../Classes/Layer/GameLayer/VisibleRect.cpp \
                   ../../Classes/Layer/MenuLayer/MenuLayer.cpp \
                   ../../Classes/Entity/FSM.cpp \
                   ../../Classes/Entity/Role/Role.cpp \
                   ../../Classes/Entity/Role/Player.cpp \
                   ../../Classes/Controller/Controller.cpp\
                   ../../Classes/Controller/ContactListener.cpp\
                   ../../Classes/Controller/KeyboardController.cpp\
                   ../../Classes/Controller/RobotController.cpp\
                   ../../Classes/Util/Animation/AnimationUtil.cpp \
                   ../../Classes/Util/CSVParse/CSVParseUtil.cpp \
                   ../../Classes/Util/CSVParse/FileLoadUtil.cpp \
                   ../../Classes/Util/CSVParse/StringUtil.cpp

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes

# _COCOS_HEADER_ANDROID_BEGIN
# _COCOS_HEADER_ANDROID_END


LOCAL_STATIC_LIBRARIES := cocos2dx_static

# _COCOS_LIB_ANDROID_BEGIN
# _COCOS_LIB_ANDROID_END

include $(BUILD_SHARED_LIBRARY)

$(call import-module,.)

# _COCOS_LIB_IMPORT_ANDROID_BEGIN
# _COCOS_LIB_IMPORT_ANDROID_END
