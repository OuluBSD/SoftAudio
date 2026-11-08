#include <Core/Core.h>
#include <SoftAudio/SoftAudio.h>
#include <cmath>

using namespace Upp;
namespace Upp { extern bool NoMemoryLeaksCheck; }

NAMESPACE_AUDIO_BEGIN
void RunInstrumentGraphTest();
NAMESPACE_AUDIO_END

CONSOLE_APP_MAIN
{
	NoMemoryLeaksCheck = true;
	StdLogSetup(LOG_COUT | LOG_FILE);
	Cout() << "Running SoftAudioCheck...\n";

	using namespace Audio;

	// 1. Verify Audio Sample Rate
	Upp::Audio::Audio::SetSampleRate(48000.0f);
	VERIFY(Upp::Audio::Audio::GetSampleRate() == 48000.0f);

	// 2. Verify SineWave Oscillator
	SineWave sine;
	sine.SetFrequency(440.0f);
	float sample0 = sine.Tick();
	float sample1 = sine.Tick();
	VERIFY(std::isfinite(sample0));
	VERIFY(std::isfinite(sample1));
	VERIFY(sample0 != sample1); // Verify phase progression

	// Verify amplitude remains within [-1.0, 1.0]
	for (int i = 0; i < 1000; i++) {
		float s = sine.Tick();
		VERIFY(std::isfinite(s));
		VERIFY(s >= -1.05f && s <= 1.05f);
	}
	Cout() << "  SineWave check passed\n";

	// 3. Verify ADSR Envelope Generator
	ADSR env;
	env.SetAllTimes(0.01f, 0.02f, 0.7f, 0.03f); // Attack 10ms, Decay 20ms, Sustain 0.7, Release 30ms
	VERIFY(env.GetState() == ADSR::IDLE);

	env.KeyOn();
	VERIFY(env.GetState() == ADSR::ATTACK);

	// Advance through attack phase
	float env_val = 0.0f;
	for (int i = 0; i < 480; i++) { // 10ms at 48kHz = 480 samples
		env_val = env.Tick();
		VERIFY(std::isfinite(env_val));
	}
	VERIFY(env_val > 0.8f); // Near attack target 1.0

	env.KeyOff();
	VERIFY(env.GetState() == ADSR::RELEASE);
	Cout() << "  ADSR envelope check passed\n";

	// 4. Verify BiQuad Filter
	BiQuad biquad;
	biquad.SetResonance(1000.0f, 0.707f, true); // 1kHz low-pass filter
	float filtered = biquad.Tick(1.0f);
	VERIFY(std::isfinite(filtered));
	Cout() << "  BiQuad filter check passed\n";

	// 5. Verify Echo Effect
	Echo echo;
	echo.SetDelay(100);
	echo.SetEffectMix(0.5f);
	for (int i = 0; i < 200; i++) {
		float out = echo.Tick(i == 0 ? 1.0f : 0.0f);
		VERIFY(std::isfinite(out));
	}
	Cout() << "  Echo effect check passed\n";

	// 6. Run InstrumentGraphTest (Hybrid instrument voice building, detuning, and rendering)
	RunInstrumentGraphTest();
	Cout() << "  InstrumentGraph test passed\n";

	Cout() << "SoftAudioCheck: ALL CHECKS PASSED!\n";
	SetExitCode(0);
}
