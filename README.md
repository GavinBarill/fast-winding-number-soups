Get started with 

   git clone --recursive https://github.com/GavinBarill/neil-triangle-example.git


Build the example with

   cd neil-triangle-example
   mkdir build
   cd build
   cmake ../
   make

Run the example with

  ./fastwinding ../hotdog.ply ../hotdog-Q.dmat ../hotdog-W.dmat

This should create a [.dmat](http://libigl.github.io/libigl/file-formats/dmat/)
file `../hot:og-W.dmat' containing the generalized winding number for each query
point in `../hotdog-Q.dmat`.
