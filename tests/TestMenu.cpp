/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TestMenu.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpeck <dpeck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/27 20:06:43 by dpeck             #+#    #+#             */
/*   Updated: 2019/05/27 20:38:04 by dpeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "TestMenu.hpp"
#include "vendor/imgui/imgui.h"

namespace test {

    TestMenu::TestMenu(ITest*& currentTestPtr) : _currentTest(currentTestPtr)
    {
        return;
    }
    
    TestMenu::~TestMenu()
    {
        
    }

    void TestMenu::OnImGuiRender()
    {
        for (auto & test : _tests)
        {
            if (ImGui::Button(test.first.c_str()))
                _currentTest = test.second();
        }
    }
}