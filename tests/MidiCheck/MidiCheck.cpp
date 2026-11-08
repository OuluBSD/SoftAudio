#include <Core/Core.h>
#include <MidiFile/MidiFile.h>

using namespace Upp;
namespace Upp { extern bool NoMemoryLeaksCheck; }

CONSOLE_APP_MAIN
{
	NoMemoryLeaksCheck = true;
	StdLogSetup(LOG_COUT | LOG_FILE);
	Cout() << "Running MidiCheck...\n";

	using namespace MidiIO;

	// 1. Create in-memory MIDI file
	File mf;
	int track_idx = mf.AddTrack();
	VERIFY(track_idx == 1);
	VERIFY(mf.GetTrackCount() == 2); // Track 0 is tempo/meta track, Track 1 is note track

	// 2. Add MIDI Note On and Note Off events
	MidiIO::Event note_on;
	note_on.tick = 0;
	note_on.track = 1;
	note_on.SetCommand(0x90, 60, 100); // Note On: Channel 0, Middle C (60), Velocity 100
	mf[1].Add(note_on);

	MidiIO::Event note_off;
	note_off.tick = 480;
	note_off.track = 1;
	note_off.SetCommand(0x80, 60, 64); // Note Off: Channel 0, Middle C (60), Velocity 64
	mf[1].Add(note_off);

	VERIFY(mf[1].GetCount() == 2);

	// 3. Link note-ons to note-offs
	int linked = mf[1].LinkNotePairs();
	VERIFY(linked == 1);
	VERIFY(mf[1][0].IsLinked());
	VERIFY(mf[1][0].GetTickDuration() == 480);

	// 4. Test file serialization to temporary buffer / stream
	String temp_path = ConfigFile("test_output.mid");
	int written = mf.Write(temp_path);
	VERIFY(written > 0);
	VERIFY(FileExists(temp_path));

	// 5. Test reading back the serialized MIDI file
	File mf2;
	int read_ok = mf2.Read(temp_path);
	VERIFY(read_ok > 0);
	VERIFY(mf2.GetTrackCount() >= 2);
	VERIFY(mf2[1].GetCount() >= 2);

	// Clean up temp file
	FileDelete(temp_path);

	Cout() << "MidiCheck: ALL CHECKS PASSED!\n";
	SetExitCode(0);
}
