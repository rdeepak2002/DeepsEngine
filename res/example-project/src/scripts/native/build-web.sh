rm -rf web
mkdir web

#cd web
#emcmake cmake -D CMAKE_CXX_FLAGS="-shared" -DCMAKE_BUILD_TYPE=Release ..
#emmake make

emcc -shared NativeScriptComponent.h SpinningEntity.cpp -o web/libnative.dylib