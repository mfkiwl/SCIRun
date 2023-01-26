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

#include <Modules/ParticleInCell/TestModuleSimple.h>
#include <Core/Datatypes/String.h>

using namespace SCIRun;
using namespace SCIRun::Modules::StringManip;
using namespace SCIRun::Core::Datatypes;
using namespace SCIRun::Dataflow::Networks;

MODULE_INFO_DEF(TestModuleSimple, ParticleInCell, SCIRun);

TestModuleSimple::TestModuleSimple() : Module(staticInfo_, false)
    {
    INITIALIZE_PORT(OutputString);
    }

void TestModuleSimple::setStateDefaults()
    {
    //setStateIntFromAlgo(Variables::Method);
    current_iteration = 0;
    }

void TestModuleSimple::execute()
    {
    //setAlgoIntFromState(Variables::Method);

    if(current_iteration == last_iteration + 1) current_iteration = 0;
    std::string s              = std::to_string(current_iteration);
    std::string message_string = "Message "+s;
    StringHandle msH(new String(message_string));

    sendOutput(OutputString, msH);

    sleep(1);
    current_iteration = current_iteration + 1;
    if(current_iteration < last_iteration + 1) enqueueExecuteAgain(false);
    }

