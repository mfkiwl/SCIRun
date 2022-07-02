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
*/

#include <Modules/ParticleInCell/PIConGPU.h>
#include <Core/Datatypes/String.h>
#include <Core/Datatypes/Matrix.h>

#include <Core/Algorithms/ParticleInCell/PIConGPUAlgo.h>

using namespace SCIRun;
using namespace SCIRun::Modules::ParticleInCell;
using namespace SCIRun::Dataflow::Networks;
using namespace SCIRun::Core::Algorithms;
using namespace SCIRun::Core::Datatypes;
using namespace SCIRun::Core::Algorithms::ParticleInCell;

MODULE_INFO_DEF(PIConGPU,ParticleInCell,SCIRun);

PIConGPU::PIConGPU() : Module(staticInfo_)
    {
    INITIALIZE_PORT(x_coordinates);
    INITIALIZE_PORT(y_coordinates);
    INITIALIZE_PORT(z_coordinates);
    }

void PIConGPU::setStateDefaults()
    {
    auto state = get_state();
    setStateStringFromAlgo(Parameters::SimulationFile);
    setStateStringFromAlgo(Parameters::ConfigFile);
    setStateStringFromAlgo(Parameters::CloneDir);
    setStateStringFromAlgo(Parameters::OutputDir);
//    setStateIntFromAlgo(Parameters::IterationIndex);
//    setStateIntFromAlgo(Parameters::MaxIndex);
    }

void PIConGPU::execute()
    {
    if(needToExecute() || running_)
        { 
        AlgorithmInput input;
        setAlgoStringFromState(Parameters::SimulationFile);
        setAlgoStringFromState(Parameters::ConfigFile);
        setAlgoStringFromState(Parameters::CloneDir);
        setAlgoStringFromState(Parameters::OutputDir);

        auto output=algo().run(input);

        sendOutputFromAlgorithm(x_coordinates,output);
        sendOutputFromAlgorithm(y_coordinates,output);
        sendOutputFromAlgorithm(z_coordinates,output);
        }
    }