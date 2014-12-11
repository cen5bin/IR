make
mkdir -p deploy

cp data/statistic.dat deploy
cp data/runtime/*.txt deploy
cp data/runtime/*.dat deploy
cp bin/release/*.so deploy

sudo mkdir -p /usr/lib/jni/data
sudo cp -rf deploy/* /usr/lib/jni/data
cd /usr/lib/jni/data
sudo mv *.so ../
cd ..
sudo mkdir -p log
