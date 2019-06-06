/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TestClearColor.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpeck <dpeck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/27 19:08:10 by dpeck             #+#    #+#             */
/*   Updated: 2019/05/27 20:51:36 by dpeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TESTCLEARCOLOR_HPP
#define TESTCLEARCOLOR_HPP

#include "ITest.hpp"

#include "vendor/glm/glm.hpp"

namespace test {

    class TestClearColor : public ITest {
    private:
        float _clearColor[4];
    public:
        TestClearColor();
        ~TestClearColor();

        void OnUpdate(float deltaTime) override;
        void OnRender() override;
        void OnImGuiRender() override;

        glm::vec4 getClearColor() const;
    };
}

#endif