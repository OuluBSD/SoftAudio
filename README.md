# SoftAudio

Modular Audio Synthesis, Physical Modeling, Sound Playback, and MIDI Processing for the U++ Ecosystem.

Part of the [OuluBSD](https://github.com/OuluBSD) project.

---

## Overview

`SoftAudio` provides high-performance audio synthesis, processing, and MIDI handling decoupled from monolithic dependencies:

| Package | Role | Key Capabilities |
|---|---|---|
| `Sound` | Low-level Audio I/O | PortAudio wrapper, sound streams, thread-safe audio daemons, clips, and discussion channels |
| `SoftAudio` | Physical Audio Modeling & DSP | Spatial audio (Sphere), node-based audio graph (`SAGraph`), ADSR envelopes, BiQuad filters, echo/reverb, procedural instruments |
| `SoftSynth` | FM Synthesis Engine | 8-operator frequency modulation synthesizer (`FmSynth`), envelopes, LFOs, voice allocation, preset serialisation |
| `SoftInstru` | SoundFont Playback | SoundFont 2 (`.sf2`) parser (`Hydra`), multi-voice wavetable synthesis, preset mapping |
| `MidiFile` | MIDI File I/O | Standard MIDI file format 0/1 parser and writer, event linking, track sequencing |
| `AudioCtrl` | Audio GUI Controls | Sliders and parametric EQ knobs for U++ `CtrlLib` |
| `SoundCtrl` | Audio Visualizer Widgets | Waveform and level meters for GUI audio inspection |
| `plugin/portaudio` | Embedded PortAudio | Built-in PortAudio fallback driver |
| `plugin/wav` | RIFF WAV Encoder/Decoder | Wave file reading/writing routines |

---

## Building & Verification

`SoftAudio` builds with [UppBuilder](https://github.com/OuluBSD/UppBuilder) across Linux, macOS, and Windows:

```bash
# Build & run MIDI unit tests
uppbuilder tests/MidiCheck -m CLANG --bazaarcore /path/to/BazaarCore -v
./bin/MidiCheck

# Build & run DSP & graph tests
uppbuilder tests/SoftAudioCheck -m CLANG --bazaarcore /path/to/BazaarCore -v
./bin/SoftAudioCheck

# Build & run FM synth & instrument tests
uppbuilder tests/SynthCheck -m CLANG --bazaarcore /path/to/BazaarCore -v
./bin/SynthCheck

# Build interactive audio example
uppbuilder uppsrc/SoundExample -m CLANG --bazaarcore /path/to/BazaarCore -v
```

---

## Continuous Integration

`SoftAudio` maintains a 4-platform CI matrix:
- **Ubuntu Clang** (`CLANG`)
- **Ubuntu GCC** (`GCC`)
- **macOS Clang** (`CLANG_macOS`)
- **Windows MSVC** (`MSVS22x64`)

---

## License

BSD 2-Clause License (see [LICENSE](LICENSE)).
