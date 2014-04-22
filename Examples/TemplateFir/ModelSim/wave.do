onerror {resume}
quietly WaveActivateNextPane {} 0
add wave -noupdate -format Logic /Top/ArchFir/inAdapt/clock
add wave -noupdate -format Logic /Top/ArchFir/inAdapt/reset
add wave -noupdate -format Logic /Top/ArchFir/inAdapt/sample_clock
add wave -noupdate -format Literal /Top/ArchFir/inAdapt/out_data
add wave -noupdate -format Logic /Top/ArchFir/outAdapt/clock
add wave -noupdate -format Logic /Top/ArchFir/outAdapt/reset
add wave -noupdate -format Logic /Top/ArchFir/outAdapt/sample_clock
add wave -noupdate -format Literal /Top/ArchFir/outAdapt/in_data
TreeUpdate [SetDefaultTree]
WaveRestoreCursors {{Cursor 1} {22930991 ns} 0}
configure wave -namecolwidth 239
configure wave -valuecolwidth 100
configure wave -justifyvalue left
configure wave -signalnamewidth 0
configure wave -snapdistance 10
configure wave -datasetprefix 0
configure wave -rowmargin 4
configure wave -childrowmargin 2
configure wave -gridoffset 0
configure wave -gridperiod 1
configure wave -griddelta 40
configure wave -timeline 0
update
WaveRestoreZoom {22881990 ns} {23070474 ns}
