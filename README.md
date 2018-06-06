# Fast Winding Numbers for Soups

Implementation of the _ACM SIGGRAPH_ 2018 paper, 

"Fast Winding Numbers for Soups and Clouds" 

Gavin Barill¹, Neil Dickson², Ryan Schmidt³, David I.W. Levin¹, Alec Jacobson¹

¹University of Toronto, ²SideFX, ³Gradient Space


_Note: this implementation is for triangle soups only, not point clouds._

## Get started with 

    git clone --recursive https://github.com/GavinBarill/neil-triangle-example.git


## Build the example with

    cd neil-triangle-example
    mkdir build
    cd build
    cmake ../
    make

## Run the example with

    ./fastwinding ../pig-head.ply ../pig-head-Q.dmat ../pig-head-W.dmat

This should create a [.dmat](http://libigl.github.io/libigl/file-formats/dmat/)
file `../hot:og-W.dmat' containing the generalized winding number for each query
point in `../pig-head-Q.dmat`.

