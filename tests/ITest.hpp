/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ITest.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpeck <dpeck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/27 19:04:00 by dpeck             #+#    #+#             */
/*   Updated: 2019/05/27 20:36:46 by dpeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITEST_HPP
#define ITEST_HPP

namespace test {

    class ITest {

    public:
        ITest() { return; }
        virtual ~ITest() { return; }

        virtual void OnUpdate(float deltaTime) { return; }
        virtual void OnRender() { return; }
        virtual void OnImGuiRender() { return; }
    };  

}


#endif