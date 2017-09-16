# wiringPi TinkerBoard
wiringPi for TinkerBoard ported to Android.

To compile the library, execute from the jni folder the command: 
```
"/path/to/your/SDK/ndk-bundle/ndk-build -B"
```
You will get some binaries and libraries:
```
[armeabi] Install        : gpio => libs/armeabi/gpio
[armeabi] Install        : led => libs/armeabi/led
[armeabi] Install        : libwiringPi.so => libs/armeabi/libwiringPi.so
[armeabi] Install        : libwiringPiDev.so => libs/armeabi/libwiringPiDev.so
[armeabi] Install        : libwpi_android.so => libs/armeabi/libwpi_android.so
```
The libraries need to be installed to the /system/lib/ folder on the TinkerBoard and the gpio binary to the folder /system/bin/:
```
adb push ../libs/armeabi/libwiringPi.so /system/lib/
adb push ../libs/armeabi/libwiringPiDev.so /system/lib/
adb push ../libs/armeabi/gpio /system/bin/
```
Also with a rooted TinkerBoard, it is not possible to access the /dev/mem from an app. So to use the library from an app, it is needed a custom kernel with a gpiomem driver. 
Without gpiomem driver, you can access the library only from root shell.

The libwpi_android.so is the library you can load in your java code:
```
package com.jw.wiringpi;

public final class wpiAndroid {
    static {
        System.loadLibrary("wpi_android");
    }
    static public native int wiringPiSetup();
    static public native int wiringPiSetupSys();
    static public native int digitalRead(int port);
    static public native void digitalWrite(int port, int onoff);
    static public native void pullUpDnControl(int port, int pud);
    static public native void pinMode(int port, int mode);
    static public native int softPwmCreate(int port, int value, int range);
    static public native void softPwmWrite  (int port, int value) ;
    static public native void softPwmStop   (int port) ;
}
```

