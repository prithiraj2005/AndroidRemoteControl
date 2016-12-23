#include <jni.h>
#include <string>
#include "PersistentDataManager.h"
#include "NetworkController.h"
#include "VideoPlayer.h"

extern "C" {

JNIEXPORT void JNICALL
Java_com_arc_prith_androidremotecontrol_SettingsActivity_clearLog(JNIEnv *env, jobject instance) {

    NetworkController::getInstance().ClearLog();
}

JNIEXPORT jstring JNICALL
Java_com_arc_prith_androidremotecontrol_SettingsActivity_getLog(JNIEnv *env, jobject instance) {
    const std::string& log =  NetworkController::getInstance().GetLog();
    return env->NewStringUTF(log.c_str());
}

JNIEXPORT void JNICALL
Java_com_arc_prith_androidremotecontrol_SettingsActivity_savePersistentData(JNIEnv *env,jobject instance)
{
    PersistentDataManager::getInstance().SavePersistentData();
}
JNIEXPORT void JNICALL
Java_com_arc_prith_androidremotecontrol_SettingsActivity_setStartCommandString(JNIEnv *env,jobject instance, jstring cmd_)
{
    const char *cmd = env->GetStringUTFChars(cmd_, 0);

    std::string cmdName(cmd);
    VideoPlayer::getInstance().SetCommandName(COMMAND_TYPE_START, cmdName);

    env->ReleaseStringUTFChars(cmd_, cmd);
}

JNIEXPORT void JNICALL
Java_com_arc_prith_androidremotecontrol_SettingsActivity_setStopCommandString(JNIEnv *env,jobject instance,jstring cmd_)
{
    const char *cmd = env->GetStringUTFChars(cmd_, 0);
    std::string cmdName(cmd);
    VideoPlayer::getInstance().SetCommandName(COMMAND_TYPE_STOP, cmdName);
    env->ReleaseStringUTFChars(cmd_, cmd);
}

JNIEXPORT void JNICALL
Java_com_arc_prith_androidremotecontrol_SettingsActivity_setVideoName(JNIEnv *env, jobject instance,jint id, jstring name_)
{
    const char *name = env->GetStringUTFChars(name_, 0);

    std::string vidName(name);
    VideoPlayer::getInstance().SetVideoName(static_cast<VIDEO_TYPE >(id), vidName);

    env->ReleaseStringUTFChars(name_, name);
}

JNIEXPORT void JNICALL
Java_com_arc_prith_androidremotecontrol_SettingsActivity_setHostIpAddress(JNIEnv *env, jobject instance,jstring address_)
{
    const char *address = env->GetStringUTFChars(address_, 0);

    std::string addressString(address);
    NetworkController::getInstance().SetHostAddress(addressString);

    env->ReleaseStringUTFChars(address_, address);
}

JNIEXPORT void JNICALL
Java_com_arc_prith_androidremotecontrol_SettingsActivity_setHostPortNumber(JNIEnv *env, jobject instance, jint port)
{
    NetworkController::getInstance().SetHostPort(port);
}

JNIEXPORT jstring JNICALL
Java_com_arc_prith_androidremotecontrol_SettingsActivity_getHostIpAddress(JNIEnv *env, jobject instance)
{
    return env->NewStringUTF(NetworkController::getInstance().GetCurrentHostIP().c_str());
}

JNIEXPORT jint JNICALL
Java_com_arc_prith_androidremotecontrol_SettingsActivity_getHostPortNumber(JNIEnv *env, jobject instance)
{
    return NetworkController::getInstance().GetCurrentHostPort();
}

JNIEXPORT jstring JNICALL
Java_com_arc_prith_androidremotecontrol_SettingsActivity_getVideoName(JNIEnv *env, jobject instance, jint id)
{
    std::string videoName = VideoPlayer::getInstance().GetVideoName(static_cast<VIDEO_TYPE >(id));
    return env->NewStringUTF(videoName.c_str());
}

JNIEXPORT jstring JNICALL
Java_com_arc_prith_androidremotecontrol_SettingsActivity_getStopCommandString(JNIEnv *env,jobject instance)
{
    std::string cmdName = VideoPlayer::getInstance().GetCommandName(COMMAND_TYPE_STOP);
    return env->NewStringUTF(cmdName.c_str());
}

JNIEXPORT jstring JNICALL
Java_com_arc_prith_androidremotecontrol_SettingsActivity_getStartCommandString(JNIEnv *env, jobject instance)
{
    std::string cmdName = VideoPlayer::getInstance().GetCommandName(COMMAND_TYPE_START);
    return env->NewStringUTF(cmdName.c_str());
}

JNIEXPORT void JNICALL
Java_com_arc_prith_androidremotecontrol_MainActivity_initializeNativeComponents(JNIEnv *env, jobject instance, jstring dataFilePath_)
{
    const char *dataFilePath = env->GetStringUTFChars(dataFilePath_, 0);

    std::string filePath(dataFilePath);
    PersistentDataManager::getInstance().setDataFile(filePath);

    PersistentDataManager::getInstance().LoadPersistentData();
    VideoPlayer::getInstance().Init();
    NetworkController::getInstance().Init();
    env->ReleaseStringUTFChars(dataFilePath_, dataFilePath);
}

JNIEXPORT void JNICALL
Java_com_arc_prith_androidremotecontrol_MainActivity_btnVid1_1OnClick(JNIEnv *env, jobject instance)
{
    VideoPlayer& player = VideoPlayer::getInstance();
    player.StopCurrentlyPlayingVideo();
    player.PlayVideo(VIDEO_TYPE_1);
}


JNIEXPORT void JNICALL
Java_com_arc_prith_androidremotecontrol_MainActivity_btnVid2_1OnClick(JNIEnv *env, jobject instance)
{
    VideoPlayer& player = VideoPlayer::getInstance();
    player.StopCurrentlyPlayingVideo();
    player.PlayVideo(VIDEO_TYPE_2);
}

JNIEXPORT void JNICALL
Java_com_arc_prith_androidremotecontrol_MainActivity_btnVid3_1OnClick(JNIEnv *env, jobject instance)
{
    VideoPlayer& player = VideoPlayer::getInstance();
    player.StopCurrentlyPlayingVideo();
    player.PlayVideo(VIDEO_TYPE_3);
}
}