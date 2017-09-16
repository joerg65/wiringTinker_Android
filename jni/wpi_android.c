#include <jni.h>
#include <android/log.h>
#include <stdio.h>
#include <string.h>

#define LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
#define LOG_TAG "wpi_android"

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include <unistd.h>
#include <string.h>
#include <time.h>
#include <sys/system_properties.h>

#include <wiringPi.h>
#include <softPwm.h>
#include <dlfcn.h>

#ifdef __cplusplus
extern "C" {
#endif

//#define I2C_DEVICE  "/dev/i2c-1"

JNIEXPORT
jint Java_com_jw_wiringpi_wpiAndroid_wiringPiSetupSys(JNIEnv* env, jobject obj) {
    LOGI("Entering wiringPiSetup");
    return wiringPiSetupSys();
}

JNIEXPORT
jint Java_com_jw_wiringpi_wpiAndroid_wiringPiSetup(JNIEnv* env, jobject obj) {
    return wiringPiSetup();
}

JNIEXPORT
void Java_com_jw_wiringpi_wpiAndroid_pullUpDnControl(JNIEnv* env, jobject obj, jint port, jint pud) {
    return pullUpDnControl(port, pud);
}

JNIEXPORT
void Java_com_jw_wiringpi_wpiAndroid_pinMode(JNIEnv* env, jobject obj, jint port, jint mode) {
    return pinMode(port, mode);
}

JNIEXPORT
jint Java_com_jw_wiringpi_wpi_android_digitalRead(JNIEnv* env, jobject obj, jint port) {
    return digitalRead(port);
}

JNIEXPORT
void Java_com_jw_wiringpi_wpiAndroid_digitalWrite(JNIEnv* env, jobject obj, jint port, jint onoff) {
    digitalWrite(port, onoff);
}

jint Java_com_jw_wiringpi_wpiAndroid_analogRead(JNIEnv* env, jobject obj, jint port) {
    return analogRead(port);
}

JNIEXPORT
jint Java_com_jw_wiringpi_wpiAndroid_softPwmCreate(JNIEnv* env, jobject obj, jint port, jint value, jint range) {
    return softPwmCreate(port, value, range);
}

JNIEXPORT
void Java_com_jw_wiringpi_wpiAndroid_softPwmWrite(JNIEnv* env, jobject obj, jint port, jint value) {
    softPwmWrite(port, value);
}

JNIEXPORT
void Java_com_jw_wiringpi_wpiAndroid_softPwmStop(JNIEnv* env, jobject obj, jint port) {
    softPwmStop(port);
}


#ifdef __cplusplus
}
#endif


