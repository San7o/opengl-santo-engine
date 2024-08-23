#pragma once

#include "ecs.hpp"
#include "systems/directional_light_system.hpp"
#include "components/directional_light_component.hpp"

#include <vector>

using namespace Brenta::ECS;

struct DirectionalLightSystem : System<DirectionalLightComponent> {

    void run(std::vector<Entity> entities) const override {
        if (entities.empty()) return;

        for (auto entity : entities) {
            auto light = World::EntityToComponent<DirectionalLightComponent>(entity);

            for (auto shader : light->shaders) {
                if (Shader::GetId(shader) == (unsigned int) 0 ) {
                    ERROR("Light shader not found with name: ", shader);
                    continue;
                }
                Shader::Use(shader);

                /* Set the light properties */
                Shader::SetVec3(shader, "dirLight.direction", light->direction);
                Shader::SetVec3(shader, "dirLight.ambient", light->ambient);
                Shader::SetVec3(shader, "dirLight.diffuse", light->diffuse);
                Shader::SetVec3(shader, "dirLight.specular", light->specular);
                Shader::SetFloat(shader, "dirLight.dir_strength", light->strength);
                Shader::SetBool(shader, "useDirLight", true);
            }
        }

    }
};
