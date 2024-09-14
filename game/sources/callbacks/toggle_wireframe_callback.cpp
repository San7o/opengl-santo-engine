/*
 * MIT License
 *
 * Copyright (c) 2024 Giovanni Santini

 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 */

#include "callbacks/toggle_wireframe_callback.hpp"

#include "ecs.hpp"
#include "engine.hpp"
#include "resources/wireframe_resource.hpp"

using namespace brenta;
using namespace brenta::ecs;
using namespace brenta::ecs::types;

void init_toggle_wireframe_callback()
{
    auto toggle_wireframe_callback = []()
    {
        auto wireframe = world::get_resource<WireframeResource>();
        if (wireframe == nullptr)
            return;

        gl::set_poligon_mode(!wireframe->enabled);
        wireframe->enabled = !wireframe->enabled;
    };
    input::add_keyboard_callback(GLFW_KEY_F, toggle_wireframe_callback);
}
