/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TestMenu.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpeck <dpeck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/27 19:29:17 by dpeck             #+#    #+#             */
/*   Updated: 2019/05/30 15:12:45 by dpeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TESTMENU_HPP
#define TESTMENU_HPP

#include "ITest.hpp"
#include <vector>
#include <functional>
#include <iostream>
#include <string>

namespace test {

    class TestMenu : public ITest {
    private:
        ITest *& _currentTest;
        std::vector<std::pair<std::string, std::function<ITest*()>>> _tests;
    public:
        TestMenu(ITest*& curTestPtr);
        ~TestMenu();

        void OnImGuiRender() override;

        template<typename T>
        void registerTest(const std::string & name)
        {
            std::cout << "Registering test " << name << std::endl;
            _tests.push_back(std::make_pair(name, []() { return new T(); }));
        }
    };
}

#endif