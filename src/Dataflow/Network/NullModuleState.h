/*
   For more information, please see: http://software.sci.utah.edu

   The MIT License

   Copyright (c) 2015 Scientific Computing and Imaging Institute,
   University of Utah.

   License for the specific language governing rights and limitations under
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

/// @todo Documentation Dataflow/Network/NullModuleState.h

#ifndef DATAFLOW_STATE_NULLMODULESTATE_H
#define DATAFLOW_STATE_NULLMODULESTATE_H

#include <Dataflow/Network/ModuleStateInterface.h>
#include <Dataflow/Network/share.h>

namespace SCIRun {
namespace Engine {
namespace State {
  
  class SCISHARE NullModuleState : public SCIRun::Dataflow::Networks::ModuleStateInterface
  {
  public:
    virtual void setValue(const Name&, const SCIRun::Core::Algorithms::AlgorithmParameter::Value&) override;
    virtual const Value getValue(const Name&) const override;
    virtual Keys getKeys() const override;
    virtual bool containsKey(const Name&) const override;
    virtual SCIRun::Dataflow::Networks::ModuleStateHandle clone() const override;
    virtual TransientValueOption getTransientValue(const Name& name) const override;
    virtual void setTransientValue(const Name& name, const TransientValue& value, bool b) override;
    virtual boost::signals2::connection connectStateChanged(state_changed_sig_t::slot_function_type subscriber) override;
    virtual boost::signals2::connection connectSpecificStateChanged(const Name& stateKeyToObserve, state_changed_sig_t::slot_function_type subscriber) override;
    virtual void fireTransientStateChangeSignal() override {}
  };

}}}

#endif
