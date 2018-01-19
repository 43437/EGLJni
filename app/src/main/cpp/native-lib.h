#include <jni.h>
void Java_com_max_egljni_NdkGlRender_onNdkDrawFrame(JNIEnv *env, jobject);
void Java_com_max_egljni_NdkGlRender_onNdkSurfaceCreated(JNIEnv *env, jobject);
void JNICALL Java_com_max_egljni_NdkGlRender_onNdkSurfaceChanged(JNIEnv *env, jobject, jint width, jint height);