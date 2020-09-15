//
// Copyright 2020 Roman Skabin
//

#pragma once

#include "core/core.h"

typedef struct SoundBuffer
{
    f32 *samples;
    u32  samples_count;
    u32  samples_per_second;
    u16  channels_count;
} SoundBuffer;

#define SOUND_CALLBACK(name) void name(Engine *engine, SoundBuffer *buffer)
typedef SOUND_CALLBACK(SoundCallback);

typedef struct SoundStream
{
    IMMDevice            *device;
    IAudioClient         *client;
    IAudioRenderClient   *renderer;
    ISimpleAudioVolume   *volume;
    WAVEFORMATEXTENSIBLE  wave_format;
    HRESULT               error;
    b32                   pause;
} SoundStream;

INLINE void SoundPlay(SoundStream *stream)       { stream->pause = false;          }
INLINE void SoundPause(SoundStream *stream)      { stream->pause = true;           }
INLINE void ToggleSoundPlay(SoundStream *stream) { stream->pause = !stream->pause; }

typedef struct AudioBuffer
{
    f32 *samples;
    u32  samples_count;
    u32  samples_index;
    u16  channels_count;
} AudioBuffer;

struct Engine;

// @NOTE(Roman): It would be better if you pass non-null filename_len,
//               otherwise strlen will be used.
ENGINE_FUN void CreateAudioBuffer(
    in     Engine      *engine,
    in     const char  *filename,
    in_opt u64          filename_len,
    out    AudioBuffer *buffer
);

ENGINE_FUN void DestroyAudioBuffer(
    in Engine      *engine,
    in AudioBuffer *buffer
);