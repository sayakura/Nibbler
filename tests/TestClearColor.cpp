/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TestClearColor.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpeck <dpeck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/27 19:11:17 by dpeck             #+#    #+#             */
/*   Updated: 2019/05/30 15:12:39 by dpeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "TestClearColor.hpp"
#include "GLDebug.hpp"
#include "vendor/imgui/imgui.h"

namespace test {

    TestClearColor::TestClearColor() : _clearColor {0.0f, 0.0f, 0.0f, 1.0f}
    {

    }

    TestClearColor::~TestClearColor()
    {

    }

    void TestClearColor::OnUpdate(float deltaTime)
    {

    }

    void TestClearColor::OnRender()
    {
        GLCall(glClearColor(_clearColor[0], _clearColor[1], _clearColor[2], _clearColor[3]));
        GLCall(glClear(GL_COLOR_BUFFER_BIT));
    }

    void TestClearColor::OnImGuiRender()
    {
        ImGui::ColorEdit4("Clear Color", _clearColor);
    }

    glm::vec4 TestClearColor::getClearColor() const
    {
        return (glm::vec4(_clearColor[0], _clearColor[1], _clearColor[2], _clearColor[3]));
    }

}