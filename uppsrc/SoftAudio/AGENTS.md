# SoftAudio – AGENTS Guide

This guide covers how to work in the `SoftAudio` package: structure, coding conventions, the U++ header include policy (BLITZ), and the ongoing non‑GUI, graph‑based audio engine task.

Scope: This file applies to `uppsrc/SoftAudio` and all subdirectories unless a nested AGENTS.md overrides it.

## Package Overview

- Main header: `SoftAudio.h` aggregates this package’s headers. Do not add cross‑package includes inside non‑main headers.
- Dependencies: `SoftAudio` uses core U++ facilities and depends on `Geometry` and `MidiFile` via `.upp`. `SoftAudio.h` includes `Core2/Core.h`, `Geometry/Geometry.h`, and `MidiFile/MidiFile.h`.
- Core types:
  - `Audio`: base class with sample rate ownership and utilities.
  - `AudioFrames`: interleaved floating‑point buffer helper.
  - `Instrument`, `Effect`, `Function`, `Generator`, `WaveOut`: processing primitives.

## Header Include Policy (U++ BLITZ)

Follow `ai/rules/header-include-policy.md`. Package-specific points:

- Main header is `SoftAudio.h`; it wraps aggregated headers with `NAMESPACE_UPP` via the `NAMESPACE_AUDIO_BEGIN/END` macros.
- `.icpp` files are compiled, not included companions. Start them with `#include "SoftAudio.h"` as well.

- Integration path: a new subpackage `SoftAudio/Graph` with `Graph.h` as its main header.

### Subpackage Independence

See `ai/rules/subpackage-independence.md`; subpackages such as `SoftAudio/Graph` are independent packages with their own main header.
### Interfaces (early sketch)

- `IAudioNode { Prepare(rate, block); Process(dst, frames); GetInputPorts(); GetOutputPorts(); }`
- `Graph { AddNode, Connect, Compile, Process, SetSink }`
- `EventQueue { Push(param, value, frame_offset), PopRange(...) }`

## Testing & Validation

- Add small integration examples:
  - `SineWave → Gain → FreeVerb → Output (PortAudio)`
  - `MIDI → Voicer(Instrument) → Mixer → Compressor → FileWaveOut`
- Verify: no allocations on audio thread, no clipping beyond ±1.0, and deterministic output for offline renders.
- Prefer unit tests local to the graph subpackage; avoid introducing global test harness changes.

Reference App
- See `reference/SoftAudioGraph` for a minimal offline example chain using the graph engine.

## Contributor Checklist

- Start every implementation file with `#include "SoftAudio.h"`.
- Avoid adding includes to non‑main headers.
- Keep processing code lock‑free and allocation‑free on the audio path.
- When adding files, update `SoftAudio.upp`. Ensure `AGENTS.md` is the first entry in the `file` section.
- For graph engine work, keep interfaces minimal and stable; iterate behind wrappers.

## Current Task

See `CURRENT_TASK.md` for the up‑to‑date plan, milestones, and open questions for the graph‑based audio engine.
