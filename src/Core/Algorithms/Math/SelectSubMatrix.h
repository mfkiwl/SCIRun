/*
   For more information, please see: http://software.sci.utah.edu

   The MIT License

   Copyright (c) 2012 Scientific Computing and Imaging Institute,
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

#ifndef ALGORITHMS_MATH_SelectSubMatrix_H
#define ALGORITHMS_MATH_SelectSubMatrix_H
#include <Core/Datatypes/DenseMatrix.h>
#include <Core/Algorithms/Base/AlgorithmBase.h>
#include <Core/Algorithms/Math/AlgorithmFwd.h>
#include <Core/Algorithms/Math/share.h>

namespace SCIRun {
namespace Core {
namespace Algorithms {
namespace Math {
  
  class SCISHARE SelectSubMatrixAlgorithm : public AlgorithmBase
  {
  public:
    static AlgorithmInputName InputMatrix;
    static AlgorithmOutputName RowIndicies;
    static AlgorithmOutputName ColumnIndicies;
    static AlgorithmParameterName rowCheckBox;
    static AlgorithmParameterName columnCheckBox;
    static AlgorithmParameterName rowStartSpinBox;
    static AlgorithmParameterName columnStartSpinBox;
    static AlgorithmParameterName columnEndSpinBox;
    static AlgorithmParameterName rowEndSpinBox;
    Datatypes::DenseMatrixHandle run(Datatypes::MatrixHandle input_matrix, Datatypes::MatrixHandle rows, Datatypes::MatrixHandle columns) const; 
    SelectSubMatrixAlgorithm();
    AlgorithmOutput run_generic(const AlgorithmInput& input) const;
   // bool run(Datatypes::DenseMatrixHandle& input_matrix, Datatypes::Handle& sub_matrix, Datatypes::MatrixHandle row_indices, Datatypes::MatrixHandle column_indices) const;
    Datatypes::DenseMatrixHandle get_sub_matrix(Datatypes::MatrixHandle& input_matrix, Datatypes::MatrixHandle rows, Datatypes::MatrixHandle columns) const;
    Datatypes::DenseMatrixHandle get_sub_matrix(Datatypes::MatrixHandle& input_matrix, std::vector<SCIRun::index_type>& rows, std::vector<SCIRun::index_type>& columns) const;
  };

}}}}

#endif
