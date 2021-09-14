package com.example.sampleopengl;

import android.graphics.Bitmap;
import android.util.Log;

public class libHolder {

    private static final String TAG = "libHolder.java";

    static {
        try {
            System.loadLibrary("native-lib");
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public  static native String stringFromJNI();

    public static native void createSurface();

    public static native void changeSurface(int w,int h);

    public  static native void updateVals();

    public static native void getImage(char a[]);

    public static native void deliverImages(byte[] image,int w,int h);

    public static native void send_pixel(Bitmap image,int w,int h);


}
