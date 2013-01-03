/*
 * Copyright (c) 2010, Google Inc. All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 * 
 *     * Redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above
 * copyright notice, this list of conditions and the following disclaimer
 * in the documentation and/or other materials provided with the
 * distribution.
 *     * Neither the name of Google Inc. nor the names of its
 * contributors may be used to endorse or promote products derived from
 * this software without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef ScriptWrappable_h
#define ScriptWrappable_h

#include "JSDOMWrapper.h"
#include "MemoryInstrumentation.h"
#include <heap/Weak.h>

namespace WebCore {

class ScriptWrappable {
public:
    JSDOMWrapper* wrapper() const
    {
        return m_wrapper.get();
    }

    void setWrapper(JSC::JSGlobalData&, JSDOMWrapper* wrapper, JSC::WeakHandleOwner* wrapperOwner, void* context)
    {
        ASSERT(!m_wrapper);
        m_wrapper = JSC::PassWeak<JSDOMWrapper>(wrapper, wrapperOwner, context);
    }

    void clearWrapper(JSDOMWrapper* wrapper)
    {
        weakClear(m_wrapper, wrapper);
    }

    void reportMemoryUsage(MemoryObjectInfo* memoryObjectInfo) const
    {
        MemoryClassInfo info(memoryObjectInfo, this, MemoryInstrumentation::DOM);
        info.addMember(m_wrapper);
    }

private:
    JSC::Weak<JSDOMWrapper> m_wrapper;
};

} // namespace WebCore

#endif // ScriptWrappable_h