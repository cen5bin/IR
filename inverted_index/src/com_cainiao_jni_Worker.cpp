#include "com_cainiao_jni_Worker.h"
#include "IREngine.h"

#define MIN(a, b) ((a) < (b) ? (a) : (b))

JNIEXPORT jintArray JNICALL Java_com_cainiao_jni_Worker_getTids
  (JNIEnv *env, jclass cc, jobjectArray arr, jint n)
{
	jintArray ret = env->NewIntArray(n);
	IREngine *engine = IREngine::sharedInstance();
	int tmp[128];
	if (engine == NULL) return NULL;
	for (int i = 0; i < n && i < 128; i++)
	{
		jstring s = (jstring)(env->GetObjectArrayElement(arr, i));
		tmp[i] = engine->getTid((char *)(env->GetStringUTFChars(s, NULL)));
	}
	env->SetIntArrayRegion(ret, 0, MIN(n, 128), tmp);
	return ret;
}

JNIEXPORT jintArray JNICALL Java_com_cainiao_jni_Worker_getDocids
  (JNIEnv *env, jclass cc, jintArray arr, jint n)
{
	int *tids = (env->GetIntArrayElements(arr, NULL));
	int docids[10000];
	int size;
	IREngine *engine = IREngine::sharedInstance();
	if (engine == NULL) return NULL;
	engine->query(tids, MIN(n, 128), docids, size);
	jintArray ret = env->NewIntArray(size);
	env->SetIntArrayRegion(ret, 0, size, docids);
	return ret;
}


JNIEXPORT jobjectArray JNICALL Java_com_cainiao_jni_Worker_getDocVector
  (JNIEnv *env, jclass cc, jint docid)
{
	IREngine *engine = IREngine::sharedInstance();
	if (engine == NULL) return NULL;
	const int N = 10000;
	int tids[N];
	double tfidf[N];
	int size;
	engine->getDocVector((int)docid, tids, tfidf, size);
	jclass objClass = env->FindClass("com/cainiao/jni/DocVectorNode");
	jobjectArray ret = env->NewObjectArray(size, objClass, 0);
	jfieldID itid = env->GetFieldID(objClass, "tid", "I");
	jfieldID itfidf = env->GetFieldID(objClass, "tfidf", "D");
	jmethodID init = env->GetMethodID(objClass, "<init>", "()V");
	for (int i = 0; i < size; i++)
	{
		jobject obj = env->NewObject(objClass, init);
		env->SetIntField(obj, itid, tids[i]);
		env->SetDoubleField(obj, itfidf, tfidf[i]);
		env->SetObjectArrayElement(ret, i, obj);
	}
	return ret;
	//jobjectArray ret = env->NewObjectArray(n);
	//return ret;
}

JNIEXPORT void JNICALL Java_com_cainiao_jni_Worker_initEngine
  (JNIEnv *env, jclass cc, jstring datapath)
{
	IREngine::initEngine((char*)(env->GetStringUTFChars(datapath, NULL)));
}
