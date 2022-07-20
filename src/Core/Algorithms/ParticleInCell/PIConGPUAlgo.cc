/*
   For more information, please see: http://software.sci.utah.edu

   The MIT License

   Copyright (c) 2020 Scientific Computing and Imaging Institute,
   University of Utah.

   Permission is hereby granted, free of charge, to any person obtaining a
   copy of this software and associated documentation files (the "Software"),
   to deal in the Software without restriction, including without limitation
   the rights to use, copy, modify, merge, publish, distribute, sublicense,
   and/or sell copies of the Software, and to permit persons to whom the
   Software is furnished to do so, subject to the following conditions:

   The above copyright notice and this permission notice shall be included
   in all copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
   OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
   THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
   FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
   DEALINGS IN THE SOFTWARE.


Coding Sources:
   https://openpmd-api.readthedocs.io/en/latest/usage/streaming.html#c
   https://openpmd-api.readthedocs.io/en/latest/usage/serial.html#c
   email from Franz Poschel, dated 17 May 2022
   email from Franz Poschel, dated 16 June 2022: PIConGPU Issue 4162; https://github.com/ComputationalRadiationPhysics/picongpu/issues/4162


To Do:
    Implement a process for particle sample rate, mesh (node) sample rate, and mesh slice through a specified x, y, or z axis point
    Implement all of the above as config settings
    Figure out why including PSypy in the output (TBG Plugins option in the .cfg file) causes an execution crash

The current known to be functional implementation is the LaserWakefield simulation using any of the following config files 1.cfg, 2.cfg and sst.cfg
I have successfully tested the following PIConGPU module UI entries for Simulation and Config file:
    $PIC_EXAMPLES/LaserWakefield
    $PIC_CFG/sst.cfg
    $PIC_CFG/1.cfg
*/

#include <openPMD/openPMD.hpp>
#include <filesystem>

#include<Core/Algorithms/ParticleInCell/PIConGPUAlgo.h>
#include<Core/Datatypes/MatrixTypeConversions.h>
#include <chrono>

using namespace SCIRun;
using namespace SCIRun::Core::Datatypes;
using namespace SCIRun::Core::Algorithms;
using namespace SCIRun::Core::Algorithms::ParticleInCell;

using std::cout;
using namespace openPMD;
using position_t = float; // TODO: move to header file

ALGORITHM_PARAMETER_DEF(ParticleInCell, SimulationFile);
ALGORITHM_PARAMETER_DEF(ParticleInCell, ConfigFile);
ALGORITHM_PARAMETER_DEF(ParticleInCell, CloneDir);
ALGORITHM_PARAMETER_DEF(ParticleInCell, OutputDir);
//ALGORITHM_PARAMETER_DEF(ParticleInCell, IterationIndex);
//ALGORITHM_PARAMETER_DEF(ParticleInCell, MaxIndex);

PIConGPUAlgo::PIConGPUAlgo()
    {
    addParameter(Parameters::SimulationFile, std::string("[Enter the path to your PIConGPU Simulation here]"));
    addParameter(Parameters::ConfigFile, std::string("[Enter the path to your .config file here]"));
    addParameter(Parameters::CloneDir, std::string("[Enter the path to the simulation clone directory here]"));
    addParameter(Parameters::OutputDir, std::string("[Enter the path to the output directory here]"));
    addParameter(Variables::Method,1);
//    addParameter(Parameters::IterationIndex, 0);
//    simulationstarted_ = false;
    }

bool PIConGPUAlgo::StartPIConGPU(const std::string sim_input, const std::string cfg_input, const std::string sim_clone, const std::string sim_output, const int reRun) const
    {
    #include <stdlib.h>
    using namespace std;
    string text_file;

                                  //Assemble the script that creates the Test_compile_run script

    text_file = "printf '#!/usr/bin bash\n\ncd $HOME && source picongpu.profile && pic-create "
                        +sim_input+" "+sim_clone+"\ncd "+sim_clone+" && pic-build && tbg -s bash -c "
                        +cfg_input+" -t etc/picongpu/bash/mpiexec.tpl "+sim_output+" &' > $HOME/Test_compile_run";

    if(cfg_input.compare("$PIC_CFG/sst.cfg")==0)
        {
        text_file = "printf '#!/usr/bin bash\n\ncd $HOME && source picongpu.profile && pic-create "
                  +sim_input+" "+sim_clone+"\ncd "+sim_clone+" && pic-build && tbg -s bash -c "
                  +cfg_input+" -t etc/picongpu/bash/mpiexec.tpl $HOME/scratch/runs/SST &' > $HOME/Test_compile_run";
        }

/*
*/
    cout<<"Debug 3: sim_output is "<<sim_output<<"\n";
    cout<<"Debug 3: reRun is "<<reRun<<"\n";
    if(reRun==0)
        {
        string str_2="rm -rf "+sim_output;
        cout<<"Debug 3: str_2 is "<<str_2<<"\n";
        const char *command_2=str_2.c_str();
        system(command_2);

        text_file = "printf '#!/usr/bin bash\n\nsource $HOME/picongpu_reRun.profile && \ncd "+sim_clone+" && tbg -s bash -c "
                  +cfg_input+" -t etc/picongpu/bash/mpiexec.tpl "+sim_output+" &' > $HOME/Test_compile_run";

        if(cfg_input.compare("$PIC_CFG/sst.cfg")==0)
            {
            string str_3="rm -rf $HOME/scratch/runs/SST";
            cout<<"Debug 3: str_3 is "<<str_3<<"\n";
            const char *command_3=str_3.c_str();
            system(command_3);

            text_file = "printf '#!/usr/bin bash\n\nsource $HOME/picongpu_reRun.profile && \ncd "+sim_clone+" && tbg -s bash -c "
                      +cfg_input+" -t etc/picongpu/bash/mpiexec.tpl $HOME/scratch/runs/SST &' > $HOME/Test_compile_run";
            }
        }

                                  //Run the script that creates the Test_compile_run script

    const char *command=text_file.c_str();
    system(command);

                                  //Run the Test1.py program that runs the Test_compile_run script

    string str="cd $HOME && python3 Test1.py";
    const char *command_1=str.c_str();
    system(command_1);

    return true;
    }

AlgorithmOutput PIConGPUAlgo::run(const AlgorithmInput&) const
    {
    AlgorithmOutput output;
    auto sim_input  = get(Parameters::SimulationFile).toString();
    auto cfg_input  = get(Parameters::ConfigFile).toString();
    auto sim_clone  = get(Parameters::CloneDir).toString();
    auto sim_output = get(Parameters::OutputDir).toString();
    auto reRun = get(Variables::Method).toInt();

    StartPIConGPU(sim_input, cfg_input, sim_clone, sim_output, reRun);

    return output;

    } //end of the PIConGPUAlgo algorithm run