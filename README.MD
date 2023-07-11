<a name="switch"></a>
### Build your project (on linux/mac for nintendo switch)
- Build !
  ```
  mkdir cmake-build-release && cd cmake-build-release
  export DEVKITPRO=/opt/devkitpro
  cmake -G "Unix Makefiles" -DPLATFORM_SWITCH=ON -DCMAKE_BUILD_TYPE=Release ../
  make -j4 penyihir.nro
  ```
<a name="next"></a>
### What to do next ?
