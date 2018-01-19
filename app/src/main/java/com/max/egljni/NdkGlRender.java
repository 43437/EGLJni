package com.max.egljni;

import android.opengl.GLSurfaceView;
import android.util.Log;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

/**
 * Created by geyu on 18-1-2.
 */

public class NdkGlRender implements GLSurfaceView.Renderer {

    private static final String TAG = "NdkGlRender";

    native private void onNdkSurfaceCreated();
    native private void onNdkSurfaceChanged(int width, int height);
    native private void onNdkDrawFrame();

    @Override
    public void onDrawFrame(GL10 gl) {
        Log.d(TAG, "onDrawFrame");
        onNdkDrawFrame();
    }

    @Override
    public void onSurfaceCreated(GL10 gl, EGLConfig config) {
        Log.d(TAG, "onSurfaceCreated");
        onNdkSurfaceCreated();
    }

    @Override
    public void onSurfaceChanged(GL10 gl, int width, int height) {
        Log.d(TAG, "onSurfaceChanged width height " + width + " " +height);
        onNdkSurfaceChanged(width, height);
    }
}
