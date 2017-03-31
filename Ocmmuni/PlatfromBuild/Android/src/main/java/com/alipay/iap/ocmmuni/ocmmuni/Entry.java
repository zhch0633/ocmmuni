package com.alipay.iap.ocmmuni.ocmmuni;

/**
 * Created by chen.zhang on 16/03/17.
 * this is the entry to Ocmmuni
 */

public class Entry {
    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("native-lib");
    }

    public static String getString(){
        return stringFromJNI();
    }

    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    public static native String stringFromJNI();
}