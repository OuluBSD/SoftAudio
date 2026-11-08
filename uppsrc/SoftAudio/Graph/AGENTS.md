# SoftAudio/Graph – AGENTS Guide

Scope: This AGENTS file applies to the `uppsrc/SoftAudio/Graph` subpackage.

Purpose: Provide a small, generic, non‑GUI audio graph engine (DAG) that other packages can wrap. This subpackage intentionally does not depend on `SoftAudio`; the parent package may include this subpackage, not the other way around.

Header Policy (BLITZ)
- See `ai/rules/header-include-policy.md`; every implementation file starts with `#include "Graph.h"`, which is the main header aggregating the package's headers.

Design
- Generic nodes process interleaved float audio in blocks.
- `Graph` manages nodes, connections, topological order, and per‑block processing.
- No dynamic allocations on the audio path in hot loops beyond small Vector growth during graph construction.

Extending
- Add new nodes by deriving from `SAGraph::Node` and implementing `Prepare` and `Process`.
- Keep processing allocation‑free; preallocate buffers in `Prepare`.

