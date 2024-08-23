#pragma once

#include "engine.hpp"
#include "ecs.hpp"

using namespace Brenta;
using namespace Brenta::ECS;

/* Model Component */
struct ModelComponent : Component {
    Model model;
    float shininess;
    Brenta::Types::ShaderName shader;
    bool hasAtlas;
    int atlasSize;
    int atlasIndex;
    int elapsedFrames = 0;

    ModelComponent() : model(Model()), shininess(0.0f), shader("default_shader"),
                       hasAtlas(false), atlasSize(0), atlasIndex(0) {}
    ModelComponent(Model model, float shininess, Brenta::Types::ShaderName shader,
                    bool hasAtlas = false, int atlasSize = 0,
                    int atlasIndex = 0)
            : model(model), shininess(shininess), shader(shader),
              hasAtlas(hasAtlas), atlasSize(atlasSize),
              atlasIndex(atlasIndex) {}
};
