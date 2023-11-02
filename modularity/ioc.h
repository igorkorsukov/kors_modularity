/*
MIT License

Copyright (c) 2020 Igor Korsukov

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/
#ifndef KORS_MODULARITY_IOC_H
#define KORS_MODULARITY_IOC_H

#include <memory>

#include "modulesioc.h"

#define INJECT(Interface, getter) \
private: \
    mutable std::shared_ptr<Interface> m_##getter = nullptr; \
public: \
    std::shared_ptr<Interface> getter() const {  \
        if (!m_##getter) { \
            static const std::string_view sig(FUNC_SIG); \
            m_##getter = kors::modularity::ioc()->resolve<Interface>(kors::funcinfo::moduleNameBySig(sig), sig); \
        } \
        return m_##getter; \
    } \
    void set##getter(std::shared_ptr<Interface> impl) { m_##getter = impl; } \

#define INJECT_STATIC(Interface, getter) \
public: \
    static std::shared_ptr<Interface>& getter() {  \
        static std::shared_ptr<Interface> s_##getter = nullptr; \
        if (!s_##getter) { \
            static const std::string_view sig(FUNC_SIG); \
            s_##getter = kors::modularity::ioc()->resolve<Interface>(kors::funcinfo::moduleNameBySig(sig), sig); \
        } \
        return s_##getter; \
    } \
    static void set##getter(std::shared_ptr<Interface> impl) { \
        std::shared_ptr<Interface>& s_##getter = getter(); \
        s_##getter = impl; \
    } \

namespace kors::modularity {
inline ModulesIoC* ioc()
{
    return ModulesIoC::instance();
}
}

#endif // KORS_MODULARITY_IOC_H
