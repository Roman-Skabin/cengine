//
// Copyright 2020 Roman Skabin
//

#pragma once

#include "core/common.h"
#include "core/memory.h"
#include "core/allocator.h"
#include "core/work_queue.h"
#include "core/window.h"
#include "core/input.h"
#include "core/scene.h"

#include "graphics/graphics_api.h"

#include "tools/logger.h"
#include "tools/timer.h"
#include "tools/array.hpp"
#include "tools/static_string.hpp"

#include "asset_manager/asset_manager.h"

int REV_CDECL main(int argc, char **argv);

namespace REV
{
    class REV_API Application
    {
    public:
        static Application *Get();

    protected:
        explicit Application(const StaticString<128>& name, GraphicsAPI::API api, const char *REVAM_filename);

    public:
        virtual ~Application();

        void SetCurrentScene(SceneBase *scene);

        REV_INLINE const Memory       *GetMemory()       const { return m_Memory;       }
        REV_INLINE const Allocator&    GetAllocator()    const { return m_Allocator;    }
        REV_INLINE const WorkQueue    *GetWorkQueue()    const { return m_WorkQueue;    }
        REV_INLINE const Window&       GetWindow()       const { return m_Window;       }
        REV_INLINE const Input        *GetInput()        const { return m_Input;        }
        REV_INLINE const Timer&        GetTimer()        const { return m_Timer;        }
        REV_INLINE const SceneBase    *GetCurrentScene() const { return m_CurrentScene; }
        REV_INLINE const AssetManager *GetAssetManager() const { return m_AssetManager; }

        REV_INLINE Memory       *GetMemory()       { return m_Memory;       }
        REV_INLINE Allocator&    GetAllocator()    { return m_Allocator;    }
        REV_INLINE WorkQueue    *GetWorkQueue()    { return m_WorkQueue;    }
        REV_INLINE Window&       GetWindow()       { return m_Window;       }
        REV_INLINE Input        *GetInput()        { return m_Input;        }
        REV_INLINE Timer&        GetTimer()        { return m_Timer;        }
        REV_INLINE SceneBase    *GetCurrentScene() { return m_CurrentScene; }
        REV_INLINE AssetManager *GetAssetManager() { return m_AssetManager; }

    private:
        void Run();

        Application(const Application&)  = delete;
        Application(Application&&)       = delete;

        Application& operator=(const Application&) = delete;
        Application& operator=(Application&&)      = delete;

    private:
        Logger        m_Logger;

    protected:
        Memory       *m_Memory;
        Allocator     m_Allocator;
        WorkQueue    *m_WorkQueue;
        Window        m_Window;
        Input        *m_Input;
        Timer         m_Timer;
        SceneBase    *m_CurrentScene;
        AssetManager *m_AssetManager;

    private:
        static Application *s_Application;

        friend int REV_CDECL ::main(int argc, char **argv);
    };
}
