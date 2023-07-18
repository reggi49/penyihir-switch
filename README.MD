<a name="switch"></a>
### Build your project (on linux/mac for nintendo switch)
- Build !
  ```
  mkdir cmake-build-release && cd cmake-build-release
  export DEVKITPRO=/opt/devkitpro
  cmake -G "Unix Makefiles" -DPLATFORM_SWITCH=ON -DCMAKE_BUILD_TYPE=Release ../
  make -j4 penyihir.nro
  ```

### Video Example
[![Youtube Video](https://img.youtube.com/vi/0KzisNmLRuU/0.jpg)](https://www.youtube.com/watch?v=0KzisNmLRuU)

### Troubleshooting
Jika Instalasi Berhasil Tetapi Bahasa Belum Berubah (If Installation Is Successful But The Language Has Not Changed)
![Image Install](https://images2.imgbox.com/c7/c5/44KwJb4h_o.jpeg)

English Desc: 
1. Enter dbi and then enter installed game, select the game the witcher 3, copy it or write down the title id.
2. Enter the explorer or nxshell application then enter the atmosphere/contents/ folder
look for the 0100BFE00E9CA000 folder then rename or match the title id that was copied/written.

<a name="next"></a>
### What to do next ?
