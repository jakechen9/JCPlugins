# ---------
# Arguments
# ---------

set(PLUGIN_NAME "RhythmicCreator")
set(VERSION "0.0.1")
set(IS_SYNTH FALSE)
set(SIDECHAIN_INPUT 0)
set(MIDI_INPUT FALSE)
set(MIDI_OUTPUT FALSE)
set(PLUGIN_CODE "JCRC") # Must be 4 characters


project(RhythmicCreator VERSION ${VERSION})

Generate_Plugin()