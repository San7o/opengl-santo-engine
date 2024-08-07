# Guide

Welcome to this quick guide on most of the features of the engine. For each
feature, an example with context will be shown. Enjoy the read :)

## 🕵️‍♂️ How it works

The `World` contains `Entities`. You can add `Components` to entities,
which are their "properties" (like Health, Position, Mesh). You interact 
with those components through `Systems` by making `Queries`. There are
also `Resources` that store global data. Components, Systems and 
Resources are identified by a name, while entities are defined with 
an ID.

Let's take a deeper look:

### Main loop

The engine provides functions to interact with the window in `ECS::Screen`, 
some OpenGL helper functions in `ECS::GL`, a nice `ECS::Logger`,
input handling with `ECS::Input`, manage time with `ECS::Time`, display text with `ECS::Text` and more!

The main loop calls `World::Tick()`. At each tick, all the 
Systems will be called in the order they were added in 
the World. 


```c++
#include "engine.h"
using namespace ECS;

int main() {

    /* Set Log level, default = WARNING */
    Logger::SetLogLevel(Types::LogLevel::INFO);

    /* Initialize the screen */
    Screen::Init(SCR_WIDTH, SCR_HEIGHT);

    /* Load OpenGL */
    GL::LoadOpenGL();

    /* Initialize the world */
    World::Init();

    InitPlayer();
    InitRenderer();
    // ...

    while(!Screen::isWindowClosed()) {

        GL::SetColor(0.2f, 0.3f, 0.3f, 1.0f);
        GL::Clear();

        World::Tick();

        Screen::PollEvents();
        Screen::SwapBuffers();
    }
    
    World::Delete();
    Screen::Terminate();
    return 0;
}
```

### Component

A Component is a piece of data (more precisely, a struct) that gets assigned to an Entity. 

You can define your own component like so:

```c++
/* This is a component */
struct ModelComponent : Types::Component {
    Model model;
    Types::ShaderName shader;

    /* I added a constructor for ease of use */
    ModelComponent(Model model, Types::ShaderName shader)
            : model(model), shader(shader) {}
};
```

### System

A System is a function that gets called at each 
Tick in the reder loop. It contains all the logic of 
the World. You will interact with the Entities, 
Components and Resources via 
`World::QueryComponents({"component1", "component2", ...})`,
`World::EntityToComponent(Entity e)`
and `World::GetResource("resourceName")`.

Here is an example:

```c++
/* A system is composed of a name and a function */
auto renderer = std::make_shared<System>("Renderer", []() {

    /* Get the entities with the model component */
    auto matches = World::QueryComponents({"ModelComponent"});
    if (matches.empty()) return;


    for (auto match : matches) {
        /* Get the model component */
        auto model_component = static_cast<ModelComponent*>
             (World::EntityToComponent(match, "ModelComponent"));
        

        /* Translate the model */
        // ...
        

        myModel.Draw(default_shader);
    }
});

World::AddSystem(renderer);
```

### Entity

You can create Entities and assign Components to them like so:

```c++
/* Create the player entity */
auto player_entity = World::NewEntity();


/* Add the player component to the player entity */
auto player_component = std::make_shared<PlayerComponent>();
World::AddComponent(player_entity, "PlayerComponent", player_component);


/* Load model and shader */
// ...


/* Add the model component to the player entity */
auto model_component = std::make_shared<ModelComponent>(model, "default_shader");
World::AddComponent(player_entity, "ModelComponent", model_component);

```

### Resources

Resources hold global data accessible via `World::GetResource("name")`. You can define a Resource like so:

```c++
/* This is a resource */
struct WireframeResource : Types::Resource {
    bool enabled;
    WireframeResource(bool e) : enabled(e) {}
};


auto wireframe_resource = std::make_shared<WireframeResource>(false);
World::AddResource("WireframeResource", wireframe_resource);
```

### Callbacks

Callbacks are funcitons that are called when the specified `key` is pressed,
the code responsible for this is in `ECS::Input`. Here is an example:
```c++
auto toggle_wireframe_callback = []() {

    auto wireframe = static_cast<WireframeResource*>(World::GetResource("WireframeResource"));
    if (wireframe == nullptr) return;

    GL::SetPoligonMode(!wireframe->enabled);
    wireframe->enabled = !wireframe->enabled;
};

Input::AddCallback(GLFW_KEY_F, toggle_wireframe_callback);
```

### Audio

There is a simple-to-use audio API in `ECS::Audio`. You can load sound files, create channels and play
a sound on a channel. There can be only one sound playing per channel, but of course there can be
multiple channels playing so some channel management from the developer is needed:

```c++
Audio::LoadAudio("guitar", std::filesystem::absolute("assets/audio/guitar.wav"));
Audio::PlayAudio("guitar"); /* This will use the "default_stream", or you can specify
                               a particular stream */

Audio::CreateStream("background_music");
Audio::PlayAudio("guitar", "background_music");
```

There are many other examples in the `examples` directory and in the `game` which is guaranteed to be updated to the lastest APIs.

Here is an high lievel simplified view of those objects:

![image](https://github.com/user-attachments/assets/d76b238d-56f1-4b57-8140-400af6ed1d23)
