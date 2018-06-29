#include                  <ttkComputeGenus.h>

vtkStandardNewMacro(ttkComputeGenus)

int ttkComputeGenus::doIt(vector<vtkDataSet *> &inputs, vector<vtkDataSet *> &outputs){

  Memory m;
  
  vtkDataSet *input = inputs[0];
  vtkDataSet *output = outputs[0];
  
  Triangulation *triangulation = ttkTriangulation::getTriangulation(input);
 
  if(!triangulation)
    return -1;
  
  triangulation->setWrapper(this);
  computeGenus_.setupTriangulation(triangulation);
  computeGenus_.setWrapper(this);
 
  // use a pointer-base copy for the input data -- to adapt if your wrapper does
  // not produce an output of the type of the input.
  output->DeepCopy(input);
  
  // in the following, the target scalar field of the input is replaced in the 
  // variable 'output' with the result of the computation.
  // if your wrapper produces an output of the same type of the input, you 
  // should proceed in the same way.

    vtkPoints *inputPointSet = (vtkPointSet::SafeDownCast(input))->GetPoints();
    vtkPoints *outputPointSet = (vtkPointSet::SafeDownCast(output))->GetPoints();
  
  
  // calling the executing package
  switch(outputPointSet->GetDataType()){
   
    vtkTemplateMacro((
      {
          computeGenus_.setInputDataPointer(inputPointSet->GetVoidPointer(0));
          computeGenus_.setOutputDataPointer(outputPointSet->GetVoidPointer(0));
          computeGenus_.execute<float>();
      }
    ));
  }
  
  {
    stringstream msg;
    msg << "[ttkComputeGenus] Memory usage: " << m.getElapsedUsage() 
      << " MB." << endl;
    dMsg(cout, msg.str(), memoryMsg);
  }
  
  return 0;
}
