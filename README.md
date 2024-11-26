# Prototype GameDev: Escape To Eclipse

### Description:
> A space story game, about the escape of the human race from earth to another universe to protect its species. During this journey you have to fight against other biological forms of life, repair your spaceship, get new ressources and explore unknown exoplanets. Once you've done, your can enter a parallel universe and build up a new society.


Development Start Date: *01.11.2024*


### Development Instructions (CMake):
---
**Build and Run:** ```./run.sh```

**Cmake Configure:** ```cmake ./build```

**Build Project:** ```cmake --build ./build```

**Raw Run:** ```cd ./build && ./(executable_file)```

### Folder Structure and usage of build generator CMAKE
---
Folder Structure:
```
|_ ProjectRoot/
|___ /build
|    |___ /bin
|    |    |___ prog (executable)
|    |___ /externals
|         |___ /SFML-2.6.1
|
|___ /src [Including GameEngine and system relevant local includes]
|    |___ /...
|    |___ main.cpp
|
|___ /lib [Including entities/players/ships/items/ui ect...]
|    |___ /Entities
|    |___ /Items
|    |___ /UI
|    |___ /...
|    |___ CMakeLists.txt [add library with recursively collected files]
|___ /data [local binary database]
|___ /ressources
|    |___ /graphics
|    |___ /sounds
|    |___ /...
|___ CMakeLists.txt -> main cmake file
|___ README.md
|___ run.sh [Executes cmake configuration, build and executable]
|___ /...

```