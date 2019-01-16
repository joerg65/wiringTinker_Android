#include <jni.h>
#include <android/log.h>
#include <stdio.h>
#include <string.h>

#define LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
#define LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)
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

#include <wiringSerial.h>
#include <errno.h>

#ifdef __cplusplus
extern "C" {
#endif

#define I2C_DEVICE  "/dev/i2c-1"





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
jint Java_com_jw_wiringpi_wpiAndroid_digitalRead(JNIEnv* env, jobject obj, jint port) {
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

//extern int   serialOpen      (const char *device, const int baud) ;
JNIEXPORT
jint Java_com_jw_wiringpi_wpiAndroid_serialOpen(JNIEnv* env, jobject obj, jstring device, jint baud) {
    const char *nativeString = (*env)->GetStringUTFChars(env, device, 0);
    int ret = serialOpen(nativeString, baud);
    if (ret < 0) LOGE("Unable to open serial device: %s", strerror (errno)) ;
    (*env)->ReleaseStringUTFChars(env, device, nativeString);
    return ret;
}

//extern void  serialClose     (const int fd) ;
JNIEXPORT
void Java_com_jw_wiringpi_wpiAndroid_serialClose(JNIEnv* env, jobject obj, jint fd) {
    serialClose(fd);
}

//extern void  serialFlush     (const int fd) ;
JNIEXPORT
void Java_com_jw_wiringpi_wpiAndroid_serialFlush(JNIEnv* env, jobject obj, jint fd) {
    serialFlush(fd);
}

//extern void  serialPutchar   (const int fd, const unsigned char c) ;
JNIEXPORT
void Java_com_jw_wiringpi_wpiAndroid_serialPutchar(JNIEnv* env, jobject obj, jint fd, jbyte c) {
    serialPutchar(fd, c);
}

//extern void  serialPuts      (const int fd, const char *s) ;
JNIEXPORT
void Java_com_jw_wiringpi_wpiAndroid_serialPuts(JNIEnv* env, jobject obj, jint fd, jstring s) {
    const char *nativeString = (*env)->GetStringUTFChars(env, s, 0);
    serialPuts(fd, nativeString);
    (*env)->ReleaseStringUTFChars(env, s, nativeString);
}

//extern void  serialPrintf    (const int fd, const char *message, ...) ;

//extern int   serialDataAvail (const int fd) ;
JNIEXPORT
jint Java_com_jw_wiringpi_wpiAndroid_serialDataAvail(JNIEnv* env, jobject obj, jint fd) {
    return serialDataAvail(fd);
}

//extern int   serialGetchar   (const int fd) ;
JNIEXPORT
jint Java_com_jw_wiringpi_wpiAndroid_serialGetchar(JNIEnv* env, jobject obj, jint fd) {
    return serialGetchar(fd);
}

#ifdef __cplusplus
}
#endif


