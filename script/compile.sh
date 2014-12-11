FILENAME=com_cainiao_jni_Worker.cpp
TARGET=jni.o
#g++ -shared -fPIC  -I/usr/lib/jvm/java-7-openjdk-i386/include  -I/usr/lib/jvm/java-7-openjdk-i386/include/linux ${FILENAME} -o ${TARGET}
g++ -c  -I/usr/lib/jvm/java-7-openjdk-i386/include  -I/usr/lib/jvm/java-7-openjdk-i386/include/linux ${FILENAME} -o obj/${TARGET}
