# LeaderEngine

`LeaderEngine` is a 2d game engine written in **C++** using the **Entity-Component-System** (ECS) architecture, built on top of the **Simple and Fast Multimedia Library** (SFML). The game engine use LuaBridge to allow users to write game logic in Lua with an asset loader system driven by a `YAML` configuration file.
The main goal of this project is to create a simple, yet powerful game engine that is easy to use and extend.  
It is currently in development and is not ready for use.

## Features
- Rendering
  - Sprites
  - Animations
  - ~~Text~~
  - ~~Shapes~~
  - ~~Particles~~
  - ~~Tilemaps~~
- Camera
    - Size
    - Position
    - Rotation
    - Zoom
    - Multiple cameras
- Physics
    - ~~Rigidbodies~~
    - Box Colliders
    - ~~Raycasts~~
- Audio
    - ~~Sound~~
    - ~~Music~~
- Input
    - Keyboard
    - Mouse
    - Gamepad
- Events
    - Event System
    - ~~Event Queue~~
- ~~UI~~
- ~~Networking~~
- Scripting
    - Lua
        - Game loop => Update
- ~~Editor~~

## Getting Started
These instructions will get you a copy of the project up and running on your local machine for development and testing purposes.
## Prerequisites
- [SFML](https://www.sfml-dev.org/) (2.6.1 or higher)
- C++ Compiler (C++ 20 standard or higher)

## Installing
### Windows
1. Clone the repository
```bash
git clone https://github.com/LeaderGRL/ECS-SFML-Engine.git
```
2. Open the project in Visual Studio
3. Build the project
4. Run the project

### Linux
1. Clone the repository
```bash
git clone
```
2. Build the project
```bash
make
```
3. Run the project
```bash
./LeaderEngine
```

## UML Diagram
### Components class diagram
![UML Diagram](https://i.imgur.com/lRh0Ecl.png)

## Usage
### Creating a script
Go to your game/Assets/Scripts directory and create a new lua file.
```lua
-- Object.lua
Object = {
    ObjectName = "Rocket",
    speed = 100,
    EManager = EntityManager:GetInstance(),
    RManager = ResourceManager:GetInstance(),
    EventManager = EventManager:GetInstance(),
}

function Object:Update(dt)
    self:Move(dt)
end

function Object:fixedUpdate()
    print("Fixed Update")
end
```

### Loading assets
Go to your game/Assets/Config directory and update the `Resources.yaml` file.
```yaml
# assets.yaml
---
textures:
    path: YOUR_PATH_TO_TEXTURES
  - id: TEXTURE_ID


animations:
  - id: ANIMATION_ID
    textureId: TEXTURE_ID
    frames:
      - x: 0
        y: 0
        width: 64
        height: 64
        duration: 0.1
      - x: 64
        y: 0
        width: 64
        height: 64
        duration: 0.1
      - x: 128
        y: 0
        width: 64
        height: 64
        duration: 0.1
```

### Creating an entity
    For now, the scene is managed by the Application class. You can create an entity by calling the CreateEntity function.

```cpp
// Application.cpp
void Application::Init()
{
    // ...
    Entity* camera = EntityManager::GetInstance().CreateEntity("MainCamera");
	camera->AddComponent<ScriptComponent, const char*>("Assets/Scripts/Cameralua");
}
```

### Getting an entity
```lua
-- Object.lua
    local camera = self.EManager:GetEntity(self.cameraName)
```

### Adding a component
```lua
-- Object.lua
    if camera then
        camera:AddComponent(Component.CAMERA)
    end
```

### Adding a sprite
```lua
    if object then
        object:SetSprite(self.RManager:GetTexture("OBJECT_TEXTURE_ID"))
    end
```

### Adding an animation
```lua
    objectAnimation:AddComponent(Component.ANIMATION)

    if object then
        objectAnimation:PlayAnimation("OBJECT_ANIMATION_ID", true)
    end
```
Second parameter is a boolean to loop the animation

## Acknowledgments
This project relies on the following great tools:
- [SFML](https://www.sfml-dev.org/) - Simple and Fast Multimedia Library
- [LuaBridge3](https://github.com/kunitoki/LuaBridge3) - A lightweight, dependency-free library for binding Lua to C++
- [yaml-cpp](https://github.com/jbeder/yaml-cpp) - A YAML parser and emitter in C++
- ~~[Box2D](https://box2d.org/)~~ - A 2D Physics Engine for Games

