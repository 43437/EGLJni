#include <jni.h>
#include <string>
#include <GLES/gl.h>
#include <android/log.h>
#include "native-lib.h"

#define NELEM(x) ((int) (sizeof(x) / sizeof((x)[0])))
#define JNIREG_CLASS "com/max/egljni/NdkGlRender"

unsigned int vbo[2];
float positions[12] = {1,-1,0, 1,1,0, -1,-1,0, -1,1,0};
short indices  [4]  = {0,1,2,3};

extern "C" {
JNIEXPORT jstring JNICALL
Java_com_max_egljni_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}
}

    void Java_com_max_egljni_NdkGlRender_onNdkSurfaceCreated(JNIEnv *env, jobject) {
        __android_log_print(ANDROID_LOG_DEBUG, "DEBUG", "jni call onNdkSurfaceCreated");
        //生成两个缓存区对象
        glGenBuffers(2, vbo);
        //绑定第一个缓存对象
        glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
        //创建和初始化第一个缓存区对象的数据
        glBufferData(GL_ARRAY_BUFFER, 4 * 12, positions, GL_STATIC_DRAW);
        //绑定第二个缓存对象
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo[1]);
        //创建和初始化第二个缓存区对象的数据
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, 2 * 4, indices, GL_STATIC_DRAW);
    }

    void JNICALL
    Java_com_max_egljni_NdkGlRender_onNdkSurfaceChanged(JNIEnv *env, jobject, jint width,
                                                        jint height) {
        __android_log_print(ANDROID_LOG_DEBUG, "DEBUG", "jni onNdkSurfaceChanged");
        //图形最终显示到屏幕的区域的位置、长和宽
        glViewport(0, 0, width, height);
        //指定矩阵
        glMatrixMode(GL_PROJECTION);
        //将当前的矩阵设置为glMatrixGL_TRIANGLE_STRIPMode指定的矩阵
        glLoadIdentity();
        glOrthof(-2, 2, -2, 2, -2, 2);;
    }

    void JNICALL Java_com_max_egljni_NdkGlRender_onNdkDrawFrame(JNIEnv *env, jobject) {

        __android_log_print(ANDROID_LOG_DEBUG, "DEBUG", "jni onNdkDrawFrame");
        //启用顶点设置功能，之后必须要关闭功能
        glEnableClientState(GL_VERTEX_ARRAY);
        //清屏positions
        glClearColor(0, 0, 1, 1);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
        //定义顶点坐标
        glVertexPointer(3, GL_FLOAT, 0, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo[1]);
        //按照参数给定的值绘制图形
        glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_SHORT, 0);
        //关闭顶点设置功能
        glDisableClientState(GL_VERTEX_ARRAY);
    }


static JNINativeMethod g_methods[] = {
        { "onNdkSurfaceCreated",            "()V",      (void *) Java_com_max_egljni_NdkGlRender_onNdkSurfaceCreated },
        { "onNdkDrawFrame",            "()V",      (void *) Java_com_max_egljni_NdkGlRender_onNdkDrawFrame },
        { "onNdkSurfaceChanged",            "(II)V",      (void *) Java_com_max_egljni_NdkGlRender_onNdkSurfaceChanged }
};


JNIEXPORT jint JNI_OnLoad(JavaVM *vm, void *reserved)
{
    JNIEnv* env = NULL;

    if (vm->GetEnv((void**) &env, JNI_VERSION_1_4) != JNI_OK) {
        return -1;
    }
    jclass clazz = env->FindClass(JNIREG_CLASS);

    env->RegisterNatives(clazz, g_methods, NELEM(g_methods) );

    return JNI_VERSION_1_4;
}

JNIEXPORT void JNI_OnUnload(JavaVM *jvm, void *reserved)
{

}

