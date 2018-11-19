// Copyright (C) 2018 Alec Jacobson <alecjacobson@gmail.com>
// 
// This Source Code Form is subject to the terms of the Mozilla Public License 
// v. 2.0. If a copy of the MPL was not distributed with this file, You can 
// obtain one at http://mozilla.org/MPL/2.0/.

#include "WindingNumber/UT_SolidAngle.h"

#include <igl/read_triangle_mesh.h>
#include <igl/parallel_for.h>
#include <igl/readDMAT.h>
#include <igl/writeDMAT.h>

#include <Eigen/Core>

#include <cstdlib>

int main(int argc, char * argv[])
{
  Eigen::MatrixXf V,P;
  Eigen::Matrix<int,Eigen::Dynamic,3,Eigen::RowMajor> F;
  if(argc != 3+1)
  {
    std::cerr<<R"(USAGE:

./fastwinding input.[mesh|msh|obj|off|ply|stl|wrl] query.dmat output.dmat

input.*     contains a 3D triangle mesh
query.dmat  contains a #Q by 3 matrix of input query points

output.dmat will contain a #Q by 1 vector of output winding numbers
)";
    return EXIT_FAILURE;
  }

  igl::read_triangle_mesh(argv[1],V,F);
  igl::readDMAT(argv[2],P);

  HDK_Sample::UT_SolidAngle<float,float> solid_angle;
  int order = 2;
  double accuracy_scale = 2.0;

  std::vector<HDK_Sample::UT_Vector3T<float> > U(V.rows());
  for(int i = 0;i<V.rows();i++)
  {
    for(int j = 0;j<3;j++)
    {
      U[i][j] = V(i,j);
    }
  }
  solid_angle.init(
      F.rows(),
      F.data(),
      V.rows(),
      &U[0],
      order);

  Eigen::VectorXf W(P.rows());
  igl::parallel_for(P.rows(),[&](int p)
  //for(int p = 0;p<P.rows();p++)
  {
  HDK_Sample::UT_Vector3T<float>Pp;
      Pp[0] = P(p,0);
      Pp[1] = P(p,1);
      Pp[2] = P(p,2);
    W(p) = solid_angle.computeSolidAngle(
      Pp,
      accuracy_scale) 
      / (4.0*M_PI);
  }
  ,1000);

  return
    igl::writeDMAT(argv[3],W,false);
}
