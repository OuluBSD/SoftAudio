#include <Core/Core.h>
#include <SoftSynth/SoftSynth.h>
#include <SoftInstru/SoftInstru.h>

using namespace Upp;

CONSOLE_APP_MAIN
{
	StdLogSetup(LOG_COUT | LOG_FILE);
	SetExitCode(0);

	Cout() << "Running SynthCheck..." << EOL;

	// 1. FM Synth Check
	{
		SoftSynth::FmSynth synth;
		synth.Init(44100.0f);
		synth.LoadTest();

		SoftSynth::Status st = synth.NoteOn(60, 100);
		ASSERT(st == SoftSynth::STATUS_OK);

		Buffer<float> output(1024 * 2);
		int active_voices = synth.RenderInterleaved(output, 1024);
		ASSERT(active_voices >= 1);

		// Verify non-silent output
		float max_amp = 0.0f;
		for(int i = 0; i < 1024 * 2; i++) {
			max_amp = max(max_amp, abs(output[i]));
		}
		ASSERT(max_amp > 0.0001f);

		synth.NoteOff(60);
		synth.ReleaseAll();
		Cout() << "  FmSynth note-on, render, note-off passed (max amplitude: " << max_amp << ")" << EOL;
	}

	// 2. Instrument Check
	{
		SoftInstru::Instrument instru;
		instru.Reset();
		Cout() << "  SoftInstru Instrument reset passed" << EOL;
	}

	Cout() << "SynthCheck: ALL CHECKS PASSED!" << EOL;
}
