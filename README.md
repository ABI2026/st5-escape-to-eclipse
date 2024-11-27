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

# Statistics of team members
### Moritz Feik:

<a href="https://git.io/streak-stats"><img src="https://github-readme-streak-stats.herokuapp.com?user=M0M0F3IK&theme=dark&background=45%2C000000%2C000000" alt="GitHub Streak Moritz Feik" /></a>

### Josef Schmidth:

<a href="https://git.io/streak-stats"><img src="https://github-readme-streak-stats.herokuapp.com?user=zn2plusc&theme=dark&background=45%2C000000%2C000000" alt="GitHub Streak Josef Schmidth" /></a>

### Lennard Helmig:

<a href="https://git.io/streak-stats"><img src="https://github-readme-streak-stats.herokuapp.com?user=Manni2211&theme=dark&background=45%2C000000%2C000000" alt="GitHub Streak Lennard Helmig" /></a>

### Domenik:

<a href="https://git.io/streak-stats"><img src="https://github-readme-streak-stats.herokuapp.com?user=DeusNeptun&theme=dark&background=45%2C000000%2C000000" alt="GitHub Streak Domenik" /></a>

