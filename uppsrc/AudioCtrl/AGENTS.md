# AudioCtrl Package AGENTS Guide

## Scope
- Applies to `uppsrc/AudioCtrl` and its entire sub-tree of U++ packages.

## Purpose
- Audio control and mixing for U++ applications
- Provides audio playback, mixing, and processing capabilities
- Supports multiple audio formats and backends
- Integrates with other U++ packages for audio workflows

## Key Areas
- **Audio Playback**: Core playback engine with seek, pause, and resume
- **Audio Mixing**: Multi-track mixing with volume and pan control
- **Audio Processing**: Effects like EQ, reverb, and compression
- **Audio Formats**: Support for WAV, MP3, OGG, and other formats
- **Audio Devices**: Management of audio input/output devices

## Extension Points
- Add new audio formats by extending `AudioFormatBase`
- Implement custom audio effects by extending `AudioEffectBase`
- Add new audio device backends
- Extend mixing capabilities with new algorithms
- Integrate with external audio libraries

## Conventions
- Follow `/CODESTYLE.md` for code style and documentation
- Use proper U++ naming conventions (PascalCase for classes, camelCase for methods)
- Include `AGENTS.md` as first file in `.upp` manifest
- Document all public APIs with Topic++ (`.tpp`) style comments
- Use `Separate` and `ReadOnly` options in `.upp` for logical grouping
- Keep package header (`AGENTS.md`) up to date with any structural changes
- Use proper acronym casing for shared components
- Prefer shared implementations over duplicated code patterns
- Follow existing patterns in the codebase

- Follow repo-wide naming rules: `ai/rules/naming-conventions.md`

## Dependencies
- Core: Basic U++ functionality
- Common: Shared utilities and base classes
- TheIDE: Integration with the IDE application

## Where To Start
- Review `AudioCtrl.h` for the main audio control interface
- Examine `AudioCtrl.cpp` for audio control implementation
- Study `AudioMixer` for mixing implementation
- Look at `AudioPlayer` for playback engine
- Check `AudioFormat` for format handlers

## Design Principles
- Low-latency audio processing for real-time applications
- Clean separation between playback and processing
- Extensible architecture for new audio features
- Consistent API design for audio operations
- Comprehensive error handling

