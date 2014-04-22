---------------------------------------------------------
System Level Modeling with SystemC.
FIR Example with usage of templates for parameterization.
---------------------------------------------------------
Danish Technological Institute 2008, by Kim Bjerge

This project contains an implementation of a FIR filter in SystemC that is simulated 
on different levels of modeling covering functional, architecture and implementation(GateLevel).

The purpose is to give an example of an iterative development method with a step wise refinement 
of the model from functional model to implementation.

A description of this method is to be found in the document "Usage of System Level Modeling with SystemC", by Kim Bjerge.


Free tools that is needed to run this example covers:
-----------------------------------------------------

SystemC ver. 2.2.0
Eclipse ver. 3.3.1.1
Cygwin ver. 3.8.0
GTKWave Analyzer ver. 3.0.29 (For view of HW signals)

See how to install these tools in "Getting started with SystemC", by Kim Bjerge.
(If you are using Cygwin version 3.8.1 you have to use an older version (3.8.0) for /cygwin/bin/make.exe.)


Tools that is optional for plotting results, VHDL code generation and co-simulation:
--------------------------------------------------------------------------------------

MATHLAB R2007b (Plotting)
SystemCrafter SC ver. 3.0.0.0 (SystemC Gate level and VHDL code generation)
ModelSimSE 6.3 (Co-simulation of mixed SystemC and VHDL source files)


SystemC UML class model:
-----------------------

Enterprice Architect ver. 6.5 (TemplateFir.eap - UML class model)


Functional
----------
This is the functional model of the FIR filer with double precision without timing. 
This is the fastest model to simulate.

To build and run this model select from Eclipse:

1. Project -> Build Configurations -> Set Active -> Functional
2. Project -> Build Project
3. Run -> Open run Dialog... 
4. Search Project .. "Functional/TemplateFir.exe"
5. Run

The input signal to the FIR filter is stored in the mix_file.txt.
The result of the FIR filter is stored in the output_double.txt file.

Source files part of the functional model:
	Defs.h
	Fork.h
	Mixer.h
	Monitor.h
	ParFir.h
	Source.h
	Top.h, Top.cpp
	main.cpp


Architecture
------------
This is the architectural model of the FIR filer in 18 bits fixed point precision 
with timing for the hardware signals including clock and sample clock.

To build and run this model select from Eclipse:

1. Project -> Build Configurations -> Set Active -> Architecture
2. Project -> Build Project
3. Run -> Open run Dialog... 
4. Search Project .. "Architecture/TemplateFir.exe"
5. Run

The input signal to the FIR filter is stored in the mix_file.txt.
The result of the FIR filter from functional model is stored in the output_fixed.txt file.
The result of the FIR filter from architecture model is stored in the output_rtl.txt file.
The simulated hardware signals (clock and sample clock) are stored in FirWave.vcd. (GTKWave to display it)
To plot the result from MATLAB using the resultArchVsFunc.m file.

Source files part of the architecture model:
	Defs.h
	Fork.h
	Mixer.h
	Monitor.h
	ParFir.h
	SynFir.h, SynFir.cpp
	InAdapter.h
	OutAdapter.h
	Source.h
	Top.h, Top.cpp
	main.cpp


GateLevel
----------
This is the architectural model of the FIR filer with timing 
and the hardware model for the FIR filter at Gate level in SystemC.

To build and run this model select from Eclipse:

Add the "#define SC_GATELEVEL" in SynFir.h by removing comments

1. Project -> Build Configurations -> Set Active -> GateLevel
2. Execute the SystemCraft.bat file that will create the SynFirGate.h and SynFirGate.c and the *.vhd files
	(Requires that SystemCrafterSC is installed)
2. Project -> Build Project
3. Run -> Open run Dialog... 
4. Search Project .. "GateLevel/TemplateFir.exe"
5. Run

The input signal to the FIR filter is stored in the mix_file.txt.
The result of the FIR filter from functional model is stored in the output_fixed.txt file.
The result of the FIR filter from architecture model is stored in the output_rtl.txt file.
The simulated hardware signals are stored in FirWave.vcd. (GTKWave to display it)
To plot the result from MATLAB using the resultGateVsArch.m file.
  (Remark that there is a one sample delay in the output_rtl file)

Source files part of the GateLevel model:
	Defs.h
	Fork.h
	Mixer.h
	Monitor.h
	ParFir.h
	SynFirGate.h, SynFirGate.cpp
	InAdapter.h
	OutAdapter.h
	Source.h
	Top.h, Top.cpp
	main.cpp

ModelSim
--------
This is the architectural model of the FIR filer with timing 
and contains the hardware implementation of the FIR filter in VHDL.

Start ModelSimSE and open the FirFilter.mpf project.
ModelSimSE must be licensed and installed with SystemC support.

Add the "#define SC_ARCHITECTURE" in Top.h by removing comments

1. Compile -> Compile All
2. Compile -> SystemC Link
3. Simulate -> Start simulation..
4. Add signals to wave (>do wave.do)
5. Simulate -> Run -> Run All

The input signal to the FIR filter is stored in the modelsim\mix_file.txt.
The result of the FIR filter from functional model is stored in the modelsim\output_fixed.txt file.
The result of the FIR filter from architecture model is stored in the modelsim\output_rtl.txt file.
To plot the result from MATLAB using the modelsim\resultGateVsArch.m file.
 (Remark that there is a one sample delay in the output_rtl file, and zeros in start of simulation)

Source files part of the ModelSim model:
	Defs.h
	Fork.h
	Mixer.h
	Monitor.h
	ParFir.h
	SynFir_SynFir.vdh, SynFir_SynFir_DoCalculate.vhd
	craft_gatelibrary.vhd
	InAdapter.h
	OutAdapter.h
	Source.h
	Top.h, Top.cpp
	main.cpp

