mkdir build
mkdir bin

# Компиляция и установка
cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
make
cp SecretCipher ../bin/SecretCipher
cp SecretTest ../bin/SecretTest
cd ..
rm -rf build

# Подготовка тестов
cd bin
cp ../tests/test_files/test1.txt test1.txt

