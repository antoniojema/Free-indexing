#include <iostream>
#include <chrono>

#include "Vector3D_pyramid.h"
#include "Vector3D_single.h"
#include "Vector3D_triple.h"
#include "Vector_ptr.h"
#include "Vector3D_ptr.h"
#include "Vector3D_complicao.h"
#include "Vector_generic.h"

using namespace std;

const int XL=-300, YL=-300, ZL=-300;
const int XU=+300, YU=+300, ZU=+300;
const int Nt = 1;

const int Nx=XU-XL;
const int Ny=YU-YL;
const int Nz=ZU-ZL;

void allocate_native(double***& arr, int x0, int y0, int z0, int x1, int y1, int z1);

void deallocate_native(double***& arr, int x0, int y0, int z0, int x1, int y1, int z1);

void allocate(double*** &arr, double*** &arr_lvl0, double*** &arr_lvl1, double*** &arr_lvl2, int x0, int y0, int z0, int x1, int y1, int z1);

void deallocate(double*** &arr, double*** &arr_lvl0, double*** &arr_lvl1, double*** &arr_lvl2, int x0, int y0, int z0, int x1, int y1, int z1);

struct VectorStatic
{
    double Ex[Nx  ][Ny+1][Nz+1];
    double Ey[Nx+1][Ny  ][Nz+1];
    double Ez[Nx+1][Ny+1][Nz  ];
    double Hx[Nx+1][Ny  ][Nz  ];
    double Hy[Nx  ][Ny+1][Nz  ];
    double Hz[Nx  ][Ny  ][Nz+1];
};

int main()
{
    VectorStatic* F;
    Vector3D_single<double>  Ex_s, Ey_s, Ez_s, Hx_s, Hy_s, Hz_s;
    Vector3D_triple<double>  Ex_t, Ey_t, Ez_t, Hx_t, Hy_t, Hz_t;
    Vector3D_pyramid<double> Ex_p, Ey_p, Ez_p, Hx_p, Hy_p, Hz_p;
    Vector_ptr<Vector_ptr<Vector_ptr<double>>> Ex_ptr, Ey_ptr, Ez_ptr, Hx_ptr, Hy_ptr, Hz_ptr;
    Vector3D_ptr<double> Ex_3ptr, Ey_3ptr, Ez_3ptr, Hx_3ptr, Hy_3ptr, Hz_3ptr;
    Vector3D_complicao<double> Ex_c, Ey_c, Ez_c, Hx_c, Hy_c, Hz_c;
    chrono::steady_clock::time_point begin, end;
    double AA = 1, A=1, B=1, C=1, D=1;
    int i, j, k;
    
      /********************************/
     /*  0. Static native C++ array  */
    /********************************/
    
    F = new VectorStatic;
    for (i = 0; i < Nx  ; i++) {
    for (j = 0; j < Ny+1; j++) {
    for (k = 0; k < Nz+1; k++) {
        (*F).Ex[i][j][k] = 1;
    }
    }
    }
    for (i = 0; i < Nx+1; i++) {
    for (j = 0; j < Ny  ; j++) {
    for (k = 0; k < Nz+1; k++) {
        (*F).Ey[i][j][k] = 1;
    }
    }
    }
    for (i = 0; i < Nx+1; i++) {
    for (j = 0; j < Ny+1; j++) {
    for (k = 0; k < Nz  ; k++) {
        (*F).Ez[i][j][k] = 1;
    }
    }
    }
    for (i = 0; i < Nx+1; i++) {
    for (j = 0; j < Ny  ; j++) {
    for (k = 0; k < Nz  ; k++) {
        (*F).Hx[i][j][k] = 1;
    }
    }
    }
    for (i = 0; i < Nx  ; i++) {
    for (j = 0; j < Ny+1; j++) {
    for (k = 0; k < Nz  ; k++) {
        (*F).Hy[i][j][k] = 1;
    }
    }
    }
    for (i = 0; i < Nx  ; i++) {
    for (j = 0; j < Ny  ; j++) {
    for (k = 0; k < Nz+1; k++) {
        (*F).Hz[i][j][k] = 1;
    }
    }
    }
    
    begin = chrono::steady_clock::now();
    for (int n = 0; n < Nt; n++){
        #pragma omp parallel default(shared) private(i,j,k)
        {
        #pragma omp for collapse(2)
        for (i = 0; i < Nx; i++){
        for (j = 1; j < Ny; j++){
        for (k = 1; k < Nz; k++){
            (*F).Ex[i][j][k] = AA * (*F).Ex[i][j][k] + A * (*F).Hy[i][j  ][k-1]
                                                      - B * (*F).Hy[i][j  ][k  ]
                                                      - C * (*F).Hz[i][j-1][k  ]
                                                      + D * (*F).Hz[i][j  ][k  ];
        }
        }
        }
        #pragma omp for collapse(2)
        for (i = 1; i < Nx; i++) {
        for (j = 0; j < Ny; j++) {
        for (k = 1; k < Nz; k++) {
            (*F).Ey[i][j][k] = AA * (*F).Ey[i][j][k] + A * (*F).Hz[i-1][j][k  ]
                                                     - B * (*F).Hz[i  ][j][k  ]
                                                     - C * (*F).Hx[i  ][j][k-1]
                                                     + D * (*F).Hx[i  ][j][k  ];
        }
        }
        }
        #pragma omp for collapse(2)
        for (i = 1; i < Nx; i++) {
        for (j = 1; j < Ny; j++) {
        for (k = 0; k < Nz; k++) {
            (*F).Ez[i][j][k] = AA * (*F).Ez[i][j][k] + A * (*F).Hx[i  ][j-1][k]
                                                     - B * (*F).Hx[i  ][j  ][k]
                                                     - C * (*F).Hy[i-1][j  ][k]
                                                     + D * (*F).Hy[i  ][j  ][k];
        }
        }
        }
        
        #pragma omp barrier
        
        #pragma omp for collapse(2)
        for (i = 0; i < Nx+1; i++){
        for (j = 0; j < Ny  ; j++){
        for (k = 0; k < Nz  ; k++){
            (*F).Hx[i][j][k] = AA * (*F).Hx[i][j][k] - A * (*F).Ey[i][j  ][k  ]
                                                      + B * (*F).Ey[i][j  ][k+1]
                                                      + C * (*F).Ez[i][j  ][k  ]
                                                      - D * (*F).Ez[i][j+1][k  ];
        }
        }
        }
        #pragma omp for collapse(2)
        for (i = 0; i < Nx  ; i++){
        for (j = 0; j < Ny+1; j++){
        for (k = 0; k < Nz  ; k++){
            (*F).Hy[i][j][k] = AA * (*F).Hy[i][j][k] - A * (*F).Ez[i  ][j][k  ]
                                                      + B * (*F).Ez[i+1][j][k  ]
                                                      + C * (*F).Ex[i  ][j][k  ]
                                                      - D * (*F).Ex[i  ][j][k+1];
        }
        }
        }
        #pragma omp for collapse(2)
        for (i = 0; i < Nx  ; i++){
        for (j = 0; j < Ny  ; j++){
        for (k = 0; k < Nz+1; k++){
            (*F).Hz[i][j][k] = AA * (*F).Hz[i][j][k] - A * (*F).Ex[i  ][j  ][k]
                                                      + B * (*F).Ex[i  ][j+1][k]
                                                      + C * (*F).Ey[i  ][j  ][k]
                                                      - D * (*F).Ey[i+1][j  ][k];
        }
        }
        }
        }
    }
    end = chrono::steady_clock::now();
    
    delete F;
    
    cout << "Time (C++ static) = " << (double)chrono::duration_cast<chrono::milliseconds>(end - begin).count()/1000. << " s = "
         << (double)(1.*Nx*Ny*Nz*Nt)/(chrono::duration_cast<chrono::milliseconds>(end - begin).count())/1000. << " Mcells/s." << endl;

      /*************************/
     /*  0.5. Vector generic  */
    /*************************/
    
    ugr::Vector<double, 3> Ex_g, Ey_g, Ez_g, Hx_g, Hy_g, Hz_g;

    Ex_g.allocate({XL, YL, ZL}, {XU  , YU+1, ZU+1});
    Ey_g.allocate({XL, YL, ZL}, {XU+1, YU  , ZU+1});
    Ez_g.allocate({XL, YL, ZL}, {XU+1, YU+1, ZU  });
    Hx_g.allocate({XL, YL, ZL}, {XU+1, YU  , ZU  });
    Hy_g.allocate({XL, YL, ZL}, {XU  , YU+1, ZU  });
    Hz_g.allocate({XL, YL, ZL}, {XU  , YU  , ZU+1});

    Ex_g = 1.;
    Ey_g = 1.;
    Ez_g = 1.;
    Hx_g = 1.;
    Hy_g = 1.;
    Hz_g = 1.;
    
    begin = chrono::steady_clock::now();
    for (int n = 0; n < Nt; n++){
        #pragma omp parallel default(shared) private(i,j,k)
        {
        #pragma omp for collapse(2)
        for (i = XL  ; i < XU; i++){
        for (j = YL+1; j < YU; j++){
        for (k = ZL+1; k < ZU; k++){
            Ex_g[i][j][k] = AA * Ex_g[i][j][k] + A * Hy_g[i][j  ][k-1]
                                               - B * Hy_g[i][j  ][k  ]
                                               - C * Hz_g[i][j-1][k  ]
                                               + D * Hz_g[i][j  ][k  ];
        }
        }
        }
        #pragma omp for collapse(2)
        for (i = XL+1; i < XU; i++) {
        for (j = YL  ; j < YU; j++) {
        for (k = ZL+1; k < ZU; k++) {
            Ey_g[i][j][k] = AA * Ey_g[i][j][k] + A * Hz_g[i-1][j][k  ]
                                               - B * Hz_g[i  ][j][k  ]
                                               - C * Hx_g[i  ][j][k-1]
                                               + D * Hx_g[i  ][j][k  ];
        }
        }
        }
        #pragma omp for collapse(2)
        for (i = XL+1; i < XU; i++) {
        for (j = YL+1; j < YU; j++) {
        for (k = ZL  ; k < ZU; k++) {
            Ez_g[i][j][k] = AA * Ez_g[i][j][k] + A * Hx_g[i  ][j-1][k]
                                               - B * Hx_g[i  ][j  ][k]
                                               - C * Hy_g[i-1][j  ][k]
                                               + D * Hy_g[i  ][j  ][k];
        }
        }
        }
        
        #pragma omp barrier
        
        #pragma omp for collapse(2)
        for (i = XL; i < XU+1; i++){
        for (j = YL; j < YU  ; j++){
        for (k = ZL; k < ZU  ; k++){
            Hx_g[i][j][k] = AA * Hx_g[i][j][k] - A * Ey_g[i][j  ][k  ]
                                               + B * Ey_g[i][j  ][k+1]
                                               + C * Ez_g[i][j  ][k  ]
                                               - D * Ez_g[i][j+1][k  ];
        }
        }
        }
        #pragma omp for collapse(2)
        for (i = XL; i < XU  ; i++){
        for (j = YL; j < YU+1; j++){
        for (k = ZL; k < ZU  ; k++){
            Hy_g[i][j][k] = AA * Hy_g[i][j][k] - A * Ez_g[i  ][j][k  ]
                                               + B * Ez_g[i+1][j][k  ]
                                               + C * Ex_g[i  ][j][k  ]
                                               - D * Ex_g[i  ][j][k+1];
        }
        }
        }
        #pragma omp for collapse(2)
        for (i = XL; i < XU  ; i++){
        for (j = YL; j < YU  ; j++){
        for (k = ZL; k < ZU+1; k++){
            Hz_g[i][j][k] = AA * Hz_g[i][j][k] - A * Ex_g[i  ][j  ][k]
                                               + B * Ex_g[i  ][j+1][k]
                                               + C * Ey_g[i  ][j  ][k]
                                               - D * Ey_g[i+1][j  ][k];
        }
        }
        }
        }
    }
    end = chrono::steady_clock::now();
    
    Ex_g.deallocate();
    Ey_g.deallocate();
    Ez_g.deallocate();
    Hx_g.deallocate();
    Hy_g.deallocate();
    Hz_g.deallocate();

    cout << "Time (Vector generic) = " << (double)chrono::duration_cast<chrono::milliseconds>(end - begin).count()/1000. << " s = "
         << (double)(1.*Nx * Ny * Nz * Nt) / (chrono::duration_cast<chrono::milliseconds>(end - begin).count()) / 1000. << " Mcells/s." << endl;

    

      /*********************************/
     /*  1. Dynamic native C++ array  */
    /*********************************/
    
    double ***Ex_d, ***Ey_d, ***Ez_d, ***Hx_d, ***Hy_d, ***Hz_d;

    allocate_native(Ex_d, XL, YL, ZL, XU  , YU+1, ZU+1);
    allocate_native(Ey_d, XL, YL, ZL, XU+1, YU  , ZU+1);
    allocate_native(Ez_d, XL, YL, ZL, XU+1, YU+1, ZU  );
    allocate_native(Hx_d, XL, YL, ZL, XU+1, YU  , ZU  );
    allocate_native(Hy_d, XL, YL, ZL, XU  , YU+1, ZU  );
    allocate_native(Hz_d, XL, YL, ZL, XU  , YU  , ZU+1);
    
    begin = chrono::steady_clock::now();
    for (int n = 0; n < Nt; n++){
        #pragma omp parallel default(shared) private(i,j,k)
        {
        #pragma omp for collapse(2)
        for (i = 0; i < Nx; i++){
        for (j = 1; j < Ny; j++){
        for (k = 1; k < Nz; k++){
            Ex_d[i][j][k] = AA * Ex_d[i][j][k] + A * Hy_d[i][j  ][k-1]
                                                - B * Hy_d[i][j  ][k  ]
                                                - C * Hz_d[i][j-1][k  ]
                                                + D * Hz_d[i][j  ][k  ];
        }
        }
        }
        #pragma omp for collapse(2)
        for (i = 1; i < Nx; i++) {
        for (j = 0; j < Ny; j++) {
        for (k = 1; k < Nz; k++) {
            Ey_d[i][j][k] = AA * Ey_d[i][j][k] + A * Hz_d[i-1][j][k  ]
                                               - B * Hz_d[i  ][j][k  ]
                                               - C * Hx_d[i  ][j][k-1]
                                               + D * Hx_d[i  ][j][k  ];
        }
        }
        }
        #pragma omp for collapse(2)
        for (i = 1; i < Nx; i++) {
        for (j = 1; j < Ny; j++) {
        for (k = 0; k < Nz; k++) {
            Ez_d[i][j][k] = AA * Ez_d[i][j][k] + A * Hx_d[i  ][j-1][k]
                                               - B * Hx_d[i  ][j  ][k]
                                               - C * Hy_d[i-1][j  ][k]
                                               + D * Hy_d[i  ][j  ][k];
        }
        }
        }
        
        #pragma omp barrier
        
        #pragma omp for collapse(2)
        for (i = 0; i < Nx+1; i++){
        for (j = 0; j < Ny  ; j++){
        for (k = 0; k < Nz  ; k++){
            Hx_d[i][j][k] = AA * Hx_d[i][j][k] - A * Ey_d[i][j  ][k  ]
                                                + B * Ey_d[i][j  ][k+1]
                                                + C * Ez_d[i][j  ][k  ]
                                                - D * Ez_d[i][j+1][k  ];
        }
        }
        }
        #pragma omp for collapse(2)
        for (i = 0; i < Nx  ; i++){
        for (j = 0; j < Ny+1; j++){
        for (k = 0; k < Nz  ; k++){
            Hy_d[i][j][k] = AA * Hy_d[i][j][k] - A * Ez_d[i  ][j][k  ]
                                                + B * Ez_d[i+1][j][k  ]
                                                + C * Ex_d[i  ][j][k  ]
                                                - D * Ex_d[i  ][j][k+1];
        }
        }
        }
        #pragma omp for collapse(2)
        for (i = 0; i < Nx  ; i++){
        for (j = 0; j < Ny  ; j++){
        for (k = 0; k < Nz+1; k++){
            Hz_d[i][j][k] = AA * Hz_d[i][j][k] - A * Ex_d[i  ][j  ][k]
                                                + B * Ex_d[i  ][j+1][k]
                                                + C * Ey_d[i  ][j  ][k]
                                                - D * Ey_d[i+1][j  ][k];
        }
        }
        }
        }
    }
    end = chrono::steady_clock::now();
    
    deallocate_native(Ex_d, XL, YL, ZL, XU  , YU+1, ZU+1);
    deallocate_native(Ey_d, XL, YL, ZL, XU+1, YU  , ZU+1);
    deallocate_native(Ez_d, XL, YL, ZL, XU+1, YU+1, ZU  );
    deallocate_native(Hx_d, XL, YL, ZL, XU+1, YU  , ZU  );
    deallocate_native(Hy_d, XL, YL, ZL, XU  , YU+1, ZU  );
    deallocate_native(Hz_d, XL, YL, ZL, XU  , YU  , ZU+1);

    cout << "Time (C++ dynamic) = " << (double)chrono::duration_cast<chrono::milliseconds>(end - begin).count()/1000. << " s = "
         << (double)(1.*Nx * Ny * Nz * Nt) / (chrono::duration_cast<chrono::milliseconds>(end - begin).count()) / 1000. << " Mcells/s." << endl;

    /*****************************/
   /*  2.1 Vector3D single *()  */
  /*****************************/

    Ex_s.allocate(XL, YL, ZL, XU  , YU+1, ZU+1);
    Ey_s.allocate(XL, YL, ZL, XU+1, YU  , ZU+1);
    Ez_s.allocate(XL, YL, ZL, XU+1, YU+1, ZU  );
    Hx_s.allocate(XL, YL, ZL, XU+1, YU  , ZU  );
    Hy_s.allocate(XL, YL, ZL, XU  , YU+1, ZU  );
    Hz_s.allocate(XL, YL, ZL, XU  , YU  , ZU+1);
    Ex_s = 1.;
    Ey_s = 1.;
    Ez_s = 1.;
    Hx_s = 1.;
    Hy_s = 1.;
    Hz_s = 1.;
    
    begin = chrono::steady_clock::now();
    for (int n = 0; n < Nt; n++){
        #pragma omp parallel default(shared) private(i,j,k)
        {
        #pragma omp for collapse(2)
        for (i = XL  ; i < XU; i++){
        for (j = YL+1; j < YU; j++){
        for (k = ZL+1; k < ZU; k++){
            Ex_s(i, j, k) = AA * Ex_s(i, j, k) + A * Hy_s(i, j  , k-1)
                                                - B * Hy_s(i, j  , k  )
                                                - C * Hz_s(i, j-1, k  )
                                                + D * Hz_s(i, j  , k  );
        }
        }
        }
        #pragma omp for collapse(2)
        for (i = XL+1; i < XU; i++){
        for (j = YL  ; j < YU; j++){
        for (k = ZL+1; k < ZU; k++){
            Ey_s(i, j, k) = AA * Ey_s(i, j, k) + A * Hz_s(i-1, j, k  )
                                               - B * Hz_s(i  , j, k  )
                                               - C * Hx_s(i  , j, k-1)
                                               + D * Hx_s(i  , j, k  );
        }
        }
        }
        #pragma omp for collapse(2)
        for (i = XL+1; i < XU; i++){
        for (j = YL+1; j < YU; j++){
        for (k = ZL  ; k < ZU; k++){
            Ez_s(i, j, k) = AA * Ez_s(i, j, k) + A * Hx_s(i  , j-1, k)
                                               - B * Hx_s(i  , j  , k)
                                               - C * Hy_s(i-1, j  , k)
                                               + D * Hy_s(i  , j  , k);
        }
        }
        }
        
        #pragma omp barrier
        
        #pragma omp for collapse(2)
        for (i = XL; i < XU+1; i++){
        for (j = YL; j < YU  ; j++){
        for (k = ZL; k < ZU  ; k++){
            Hx_s(i, j, k) = AA * Hx_s(i, j, k) - A * Ey_s(i, j  , k  )
                                                + B * Ey_s(i, j  , k+1)
                                                + C * Ez_s(i, j  , k  )
                                                - D * Ez_s(i, j+1, k  );
        }
        }
        }
        #pragma omp for collapse(2)
        for (i = XL; i < XU  ; i++){
        for (j = YL; j < YU+1; j++){
        for (k = ZL; k < ZU  ; k++){
            Hy_s(i, j, k) = AA * Hy_s(i, j, k) - A * Ez_s(i  , j, k  )
                                                + B * Ez_s(i+1, j, k  )
                                                + C * Ex_s(i  , j, k  )
                                                - D * Ex_s(i  , j, k+1);
        }
        }
        }
        #pragma omp for collapse(2)
        for (i = XL; i < XU  ; i++){
        for (j = YL; j < YU  ; j++){
        for (k = ZL; k < ZU+1; k++){
            Hz_s(i, j, k) = AA * Hz_s(i, j, k) - A * Ex_s(i  , j  , k)
                                                + B * Ex_s(i  , j+1, k)
                                                + C * Ey_s(i  , j  , k)
                                                - D * Ey_s(i+1, j  , k);
        }
        }
        }
        }
    }
    end = chrono::steady_clock::now();
    
    Ex_s.deallocate();
    Ey_s.deallocate();
    Ez_s.deallocate();
    Hx_s.deallocate();
    Hy_s.deallocate();
    Hz_s.deallocate();

    cout << "Time (single *()) = " << (double)chrono::duration_cast<chrono::milliseconds>(end - begin).count() / 1000. << " s = "
        << (double)(1.*Nx * Ny * Nz * Nt) / (chrono::duration_cast<chrono::milliseconds>(end - begin).count()) / 1000. << " Mcells/s." << endl;

    /*****************************/
   /*  2.2. Vector3D single []  */
  /*****************************/

    Ex_s.allocate(XL, YL, ZL, XU  , YU+1, ZU+1);
    Ey_s.allocate(XL, YL, ZL, XU+1, YU  , ZU+1);
    Ez_s.allocate(XL, YL, ZL, XU+1, YU+1, ZU  );
    Hx_s.allocate(XL, YL, ZL, XU+1, YU  , ZU  );
    Hy_s.allocate(XL, YL, ZL, XU  , YU+1, ZU  );
    Hz_s.allocate(XL, YL, ZL, XU  , YU  , ZU+1);
    Ex_s = 1.;
    Ey_s = 1.;
    Ez_s = 1.;
    Hx_s = 1.;
    Hy_s = 1.;
    Hz_s = 1.;
    
    begin = chrono::steady_clock::now();
    for (int n = 0; n < Nt; n++){
        #pragma omp parallel default(shared) private(i,j,k)
        {
        #pragma omp for collapse(2)
        for (i = XL  ; i < XU; i++){
        for (j = YL+1; j < YU; j++){
        for (k = ZL+1; k < ZU; k++){
            Ex_s[{i, j, k}] = AA * Ex_s[{i, j, k}] + A * Hy_s[{i, j  , k-1}]
                                                - B * Hy_s[{i, j  , k  }]
                                                - C * Hz_s[{i, j-1, k  }]
                                                + D * Hz_s[{i, j  , k  }];
        }
        }
        }
        #pragma omp for collapse(2)
        for (i = XL+1; i < XU; i++){
        for (j = YL  ; j < YU; j++){
        for (k = ZL+1; k < ZU; k++){
            Ey_s[{i, j, k}] = AA * Ey_s[{i, j, k}] + A * Hz_s[{i-1, j, k  }]
                                               - B * Hz_s[{i  , j, k  }]
                                               - C * Hx_s[{i  , j, k-1}]
                                               + D * Hx_s[{i  , j, k  }];
        }
        }
        }
        #pragma omp for collapse(2)
        for (i = XL+1; i < XU; i++){
        for (j = YL+1; j < YU; j++){
        for (k = ZL  ; k < ZU; k++){
            Ez_s[{i, j, k}] = AA * Ez_s[{i, j, k}] + A * Hx_s[{i  , j-1, k}]
                                               - B * Hx_s[{i  , j  , k}]
                                               - C * Hy_s[{i-1, j  , k}]
                                               + D * Hy_s[{i  , j  , k}];
        }
        }
        }
        
        #pragma omp barrier
        
        #pragma omp for collapse(2)
        for (i = XL; i < XU+1; i++){
        for (j = YL; j < YU  ; j++){
        for (k = ZL; k < ZU  ; k++){
            Hx_s[{i, j, k}] = AA * Hx_s[{i, j, k}] - A * Ey_s[{i, j  , k  }]
                                                + B * Ey_s[{i, j  , k+1}]
                                                + C * Ez_s[{i, j  , k  }]
                                                - D * Ez_s[{i, j+1, k  }];
        }
        }
        }
        #pragma omp for collapse(2)
        for (i = XL; i < XU  ; i++){
        for (j = YL; j < YU+1; j++){
        for (k = ZL; k < ZU  ; k++){
            Hy_s[{i, j, k}] = AA * Hy_s[{i, j, k}] - A * Ez_s[{i  , j, k  }]
                                                + B * Ez_s[{i+1, j, k  }]
                                                + C * Ex_s[{i  , j, k  }]
                                                - D * Ex_s[{i  , j, k+1}];
        }
        }
        }
        #pragma omp for collapse(2)
        for (i = XL; i < XU  ; i++){
        for (j = YL; j < YU  ; j++){
        for (k = ZL; k < ZU+1; k++){
            Hz_s[{i, j, k}] = AA * Hz_s[{i, j, k}] - A * Ex_s[{i  , j  , k}]
                                                + B * Ex_s[{i  , j+1, k}]
                                                + C * Ey_s[{i  , j  , k}]
                                                - D * Ey_s[{i+1, j  , k}];
        }
        }
        }
        }
    }
    end = chrono::steady_clock::now();
    
    Ex_s.deallocate();
    Ey_s.deallocate();
    Ez_s.deallocate();
    Hx_s.deallocate();
    Hy_s.deallocate();
    Hz_s.deallocate();

    cout << "Time (single []) = " << (double)chrono::duration_cast<chrono::milliseconds>(end - begin).count() / 1000. << " s = "
        << (double)(1.*Nx * Ny * Nz * Nt) / (chrono::duration_cast<chrono::milliseconds>(end - begin).count()) / 1000. << " Mcells/s." << endl;

    /******************************/
   /*  3.1. Vector3D triple *()  */
  /******************************/

    Ex_t.allocate(XL, YL, ZL, XU  , YU+1, ZU+1);
    Ey_t.allocate(XL, YL, ZL, XU+1, YU  , ZU+1);
    Ez_t.allocate(XL, YL, ZL, XU+1, YU+1, ZU  );
    Hx_t.allocate(XL, YL, ZL, XU+1, YU  , ZU  );
    Hy_t.allocate(XL, YL, ZL, XU  , YU+1, ZU  );
    Hz_t.allocate(XL, YL, ZL, XU  , YU  , ZU+1);
    Ex_t = 1.;
    Ey_t = 1.;
    Ez_t = 1.;
    Hx_t = 1.;
    Hy_t = 1.;
    Hz_t = 1.;
    
    begin = chrono::steady_clock::now();
    for (int n = 0; n < Nt; n++){
        #pragma omp parallel default(shared) private(i,j,k)
        {
        #pragma omp for collapse(2)
        for (i = XL  ; i < XU; i++){
        for (j = YL+1; j < YU; j++){
        for (k = ZL+1; k < ZU; k++){
            Ex_t(i, j, k) = AA * Ex_t(i, j, k) + A * Hy_t(i, j  , k-1)
                                                - B * Hy_t(i, j  , k  )
                                                - C * Hz_t(i, j-1, k  )
                                                + D * Hz_t(i, j  , k  );
        }
        }
        }
        #pragma omp for collapse(2)
        for (i = XL+1; i < XU; i++){
        for (j = YL  ; j < YU; j++){
        for (k = ZL+1; k < ZU; k++){
            Ey_t(i, j, k) = AA * Ey_t(i, j, k) + A * Hz_t(i-1, j, k  )
                                               - B * Hz_t(i  , j, k  )
                                               - C * Hx_t(i  , j, k-1)
                                               + D * Hx_t(i  , j, k  );
        }
        }
        }
        #pragma omp for collapse(2)
        for (i = XL+1; i < XU; i++){
        for (j = YL+1; j < YU; j++){
        for (k = ZL  ; k < ZU; k++){
            Ez_t(i, j, k) = AA * Ez_t(i, j, k) + A * Hx_t(i  , j-1, k)
                                               - B * Hx_t(i  , j  , k)
                                               - C * Hy_t(i-1, j  , k)
                                               + D * Hy_t(i  , j  , k);
        }
        }
        }
        
        #pragma omp barrier
        
        #pragma omp for collapse(2)
        for (i = XL; i < XU+1; i++){
        for (j = YL; j < YU  ; j++){
        for (k = ZL; k < ZU  ; k++){
            Hx_t(i, j, k) = AA * Hx_t(i, j, k) - A * Ey_t(i, j  , k  )
                                                + B * Ey_t(i, j  , k+1)
                                                + C * Ez_t(i, j  , k  )
                                                - D * Ez_t(i, j+1, k  );
        }
        }
        }
        #pragma omp for collapse(2)
        for (i = XL; i < XU  ; i++){
        for (j = YL; j < YU+1; j++){
        for (k = ZL; k < ZU  ; k++){
            Hy_t(i, j, k) = AA * Hy_t(i, j, k) - A * Ez_t(i  , j, k  )
                                                + B * Ez_t(i+1, j, k  )
                                                + C * Ex_t(i  , j, k  )
                                                - D * Ex_t(i  , j, k+1);
        }
        }
        }
        #pragma omp for collapse(2)
        for (i = XL; i < XU  ; i++){
        for (j = YL; j < YU  ; j++){
        for (k = ZL; k < ZU+1; k++){
            Hz_t(i, j, k) = AA * Hz_t(i, j, k) - A * Ex_t(i  , j  , k)
                                                + B * Ex_t(i  , j+1, k)
                                                + C * Ey_t(i  , j  , k)
                                                - D * Ey_t(i+1, j  , k);
        }
        }
        }
        }
    }
    end = chrono::steady_clock::now();
    
    Ex_t.deallocate();
    Ey_t.deallocate();
    Ez_t.deallocate();
    Hx_t.deallocate();
    Hy_t.deallocate();
    Hz_t.deallocate();

    cout << "Time (triple *()) = " << (double)chrono::duration_cast<chrono::milliseconds>(end - begin).count() / 1000. << " s = "
        << (double)(1.*Nx * Ny * Nz * Nt) / (chrono::duration_cast<chrono::milliseconds>(end - begin).count()) / 1000. << " Mcells/s." << endl;

    /*****************************/
   /*  3.2. Vector3D triple []  */
  /*****************************/

    Ex_t.allocate(XL, YL, ZL, XU  , YU+1, ZU+1);
    Ey_t.allocate(XL, YL, ZL, XU+1, YU  , ZU+1);
    Ez_t.allocate(XL, YL, ZL, XU+1, YU+1, ZU  );
    Hx_t.allocate(XL, YL, ZL, XU+1, YU  , ZU  );
    Hy_t.allocate(XL, YL, ZL, XU  , YU+1, ZU  );
    Hz_t.allocate(XL, YL, ZL, XU  , YU  , ZU+1);
    Ex_t = 1.;
    Ey_t = 1.;
    Ez_t = 1.;
    Hx_t = 1.;
    Hy_t = 1.;
    Hz_t = 1.;
    
    begin = chrono::steady_clock::now();
    for (int n = 0; n < Nt; n++){
        #pragma omp parallel default(shared) private(i,j,k)
        {
        #pragma omp for collapse(2)
        for (i = XL  ; i < XU; i++){
        for (j = YL+1; j < YU; j++){
        for (k = ZL+1; k < ZU; k++){
            Ex_t[{i, j, k}] = AA * Ex_t[{i, j, k}] + A * Hy_t[{i, j  , k-1}]
                                                - B * Hy_t[{i, j  , k  }]
                                                - C * Hz_t[{i, j-1, k  }]
                                                + D * Hz_t[{i, j  , k  }];
        }
        }
        }
        #pragma omp for collapse(2)
        for (i = XL+1; i < XU; i++){
        for (j = YL  ; j < YU; j++){
        for (k = ZL+1; k < ZU; k++){
            Ey_t[{i, j, k}] = AA * Ey_t[{i, j, k}] + A * Hz_t[{i-1, j, k  }]
                                               - B * Hz_t[{i  , j, k  }]
                                               - C * Hx_t[{i  , j, k-1}]
                                               + D * Hx_t[{i  , j, k  }];
        }
        }
        }
        #pragma omp for collapse(2)
        for (i = XL+1; i < XU; i++){
        for (j = YL+1; j < YU; j++){
        for (k = ZL  ; k < ZU; k++){
            Ez_t[{i, j, k}] = AA * Ez_t[{i, j, k}] + A * Hx_t[{i  , j-1, k}]
                                               - B * Hx_t[{i  , j  , k}]
                                               - C * Hy_t[{i-1, j  , k}]
                                               + D * Hy_t[{i  , j  , k}];
        }
        }
        }
        
        #pragma omp barrier
        
        #pragma omp for collapse(2)
        for (i = XL; i < XU+1; i++){
        for (j = YL; j < YU  ; j++){
        for (k = ZL; k < ZU  ; k++){
            Hx_t[{i, j, k}] = AA * Hx_t[{i, j, k}] - A * Ey_t[{i, j  , k  }]
                                                + B * Ey_t[{i, j  , k+1}]
                                                + C * Ez_t[{i, j  , k  }]
                                                - D * Ez_t[{i, j+1, k  }];
        }
        }
        }
        #pragma omp for collapse(2)
        for (i = XL; i < XU  ; i++){
        for (j = YL; j < YU+1; j++){
        for (k = ZL; k < ZU  ; k++){
            Hy_t[{i, j, k}] = AA * Hy_t[{i, j, k}] - A * Ez_t[{i  , j, k  }]
                                                + B * Ez_t[{i+1, j, k  }]
                                                + C * Ex_t[{i  , j, k  }]
                                                - D * Ex_t[{i  , j, k+1}];
        }
        }
        }
        #pragma omp for collapse(2)
        for (i = XL; i < XU  ; i++){
        for (j = YL; j < YU  ; j++){
        for (k = ZL; k < ZU+1; k++){
            Hz_t[{i, j, k}] = AA * Hz_t[{i, j, k}] - A * Ex_t[{i  , j  , k}]
                                                + B * Ex_t[{i  , j+1, k}]
                                                + C * Ey_t[{i  , j  , k}]
                                                - D * Ey_t[{i+1, j  , k}];
        }
        }
        }
        }
    }
    end = chrono::steady_clock::now();
    
    Ex_t.deallocate();
    Ey_t.deallocate();
    Ez_t.deallocate();
    Hx_t.deallocate();
    Hy_t.deallocate();
    Hz_t.deallocate();

    cout << "Time (triple []) = " << (double)chrono::duration_cast<chrono::milliseconds>(end - begin).count() / 1000. << " s = "
        << (double)(1.*Nx * Ny * Nz * Nt) / (chrono::duration_cast<chrono::milliseconds>(end - begin).count()) / 1000. << " Mcells/s." << endl;

    /*************************/
   /*  4. Vector3D pyramid  */
  /*************************/

    Ex_p.allocate(XL, YL, ZL, XU  , YU+1, ZU+1);
    Ey_p.allocate(XL, YL, ZL, XU+1, YU  , ZU+1);
    Ez_p.allocate(XL, YL, ZL, XU+1, YU+1, ZU  );
    Hx_p.allocate(XL, YL, ZL, XU+1, YU  , ZU  );
    Hy_p.allocate(XL, YL, ZL, XU  , YU+1, ZU  );
    Hz_p.allocate(XL, YL, ZL, XU  , YU  , ZU+1);
    Ex_p = 1.;
    Ey_p = 1.;
    Ez_p = 1.;
    Hx_p = 1.;
    Hy_p = 1.;
    Hz_p = 1.;
    
    begin = chrono::steady_clock::now();
    for (int n = 0; n < Nt; n++){
        #pragma omp parallel default(shared) private(i,j,k)
        {
        #pragma omp for collapse(2)
        for (i = XL  ; i < XU; i++){
        for (j = YL+1; j < YU; j++){
        for (k = ZL+1; k < ZU; k++){
            Ex_p[i][j][k] = AA * Ex_p[i][j][k] + A * Hy_p[i][j  ][k-1]
                                                - B * Hy_p[i][j  ][k  ]
                                                - C * Hz_p[i][j-1][k  ]
                                                + D * Hz_p[i][j  ][k  ];
        }
        }
        }
        #pragma omp for collapse(2)
        for (i = XL+1; i < XU; i++){
        for (j = YL  ; j < YU; j++){
        for (k = ZL+1; k < ZU; k++){
            Ey_p[i][j][k] = AA * Ey_p[i][j][k] + A * Hz_p[i-1][j][k  ]
                                               - B * Hz_p[i  ][j][k  ]
                                               - C * Hx_p[i  ][j][k-1]
                                               + D * Hx_p[i  ][j][k  ];
        }
        }
        }
        #pragma omp for collapse(2)
        for (i = XL+1; i < XU; i++){
        for (j = YL+1; j < YU; j++){
        for (k = ZL  ; k < ZU; k++){
            Ez_p[i][j][k] = AA * Ez_p[i][j][k] + A * Hx_p[i  ][j-1][k]
                                               - B * Hx_p[i  ][j  ][k]
                                               - C * Hy_p[i-1][j  ][k]
                                               + D * Hy_p[i  ][j  ][k];
        }
        }
        }
        
        #pragma omp barrier
        
        #pragma omp for collapse(2)
        for (i = XL; i < XU+1; i++){
        for (j = YL; j < YU  ; j++){
        for (k = ZL; k < ZU  ; k++){
            Hx_p[i][j][k] = AA * Hx_p[i][j][k] - A * Ey_p[i][j  ][k  ]
                                                + B * Ey_p[i][j  ][k+1]
                                                + C * Ez_p[i][j  ][k  ]
                                                - D * Ez_p[i][j+1][k  ];
        }
        }
        }
        #pragma omp for collapse(2)
        for (i = XL; i < XU  ; i++){
        for (j = YL; j < YU+1; j++){
        for (k = ZL; k < ZU  ; k++){
            Hy_p[i][j][k] = AA * Hy_p[i][j][k] - A * Ez_p[i  ][j][k  ]
                                                + B * Ez_p[i+1][j][k  ]
                                                + C * Ex_p[i  ][j][k  ]
                                                - D * Ex_p[i  ][j][k+1];
        }
        }
        }
        #pragma omp for collapse(2)
        for (i = XL; i < XU  ; i++){
        for (j = YL; j < YU  ; j++){
        for (k = ZL; k < ZU+1; k++){
            Hz_p[i][j][k] = AA * Hz_p[i][j][k] - A * Ex_p[i  ][j  ][k]
                                                + B * Ex_p[i  ][j+1][k]
                                                + C * Ey_p[i  ][j  ][k]
                                                - D * Ey_p[i+1][j  ][k];
        }
        }
        }
        }
    }
    end = chrono::steady_clock::now();
    
    Ex_p.deallocate();
    Ey_p.deallocate();
    Ez_p.deallocate();
    Hx_p.deallocate();
    Hy_p.deallocate();
    Hz_p.deallocate();

    cout << "Time (pyramid) = " << (double)chrono::duration_cast<chrono::milliseconds>(end - begin).count() / 1000. << " s = "
        << (double)(1.*Nx * Ny * Nz * Nt) / (chrono::duration_cast<chrono::milliseconds>(end - begin).count()) / 1000. << " Mcells/s." << endl;

    /*******************/
   /*  5. Vector ptr  */
  /*******************/
    
    Ex_ptr.allocate(XL, XU  );
    for (i = XL; i < XU  ; i++) {
        Ex_ptr[i].allocate(YL, YU+1);
        for (j = YL;    j < YU+1; j++) {
            Ex_ptr[i][j].allocate(ZL, ZU+1);
        }
    }
    Ey_ptr.allocate(XL, XU+1);
    for (i = XL; i < XU+1; i++) {
        Ey_ptr[i].allocate(YL, YU  );
        for (j = YL;    j < YU  ; j++) {
            Ey_ptr[i][j].allocate(ZL, ZU+1);
        }
    }
    Ez_ptr.allocate(XL, XU+1);
    for (i = XL; i < XU+1; i++) {
        Ez_ptr[i].allocate(YL, YU+1);
        for (j = YL;    j < YU+1; j++) {
            Ez_ptr[i][j].allocate(ZL, ZU  );
        }
    }
    Hx_ptr.allocate(XL, XU+1);
    for (i = XL; i < XU+1; i++) {
        Hx_ptr[i].allocate(YL, YU  );
        for (j = YL;    j < YU  ; j++) {
            Hx_ptr[i][j].allocate(ZL, ZU  );
        }
    }
    Hy_ptr.allocate(XL, XU  );
    for (i = XL; i < XU  ; i++) {
        Hy_ptr[i].allocate(YL, YU+1);
        for (j = YL;    j < YU+1; j++) {
            Hy_ptr[i][j].allocate(ZL, ZU  );
        }
    }
    Hz_ptr.allocate(XL, XU  );
    for (i = XL; i < XU  ; i++) {
        Hz_ptr[i].allocate(YL, YU  );
        for (j = YL;    j < YU  ; j++) {
            Hz_ptr[i][j].allocate(ZL, ZU+1);
        }
    }

    for (i = XL; i < XU  ; i++) {
    for (j = YL; j < YU+1; j++) {
    for (k = ZL; k < ZU+1; k++) {
        Ex_ptr[i][j][k] = 1;
    }
    }
    }
    for (i = XL; i < XU+1; i++) {
    for (j = YL; j < YU  ; j++) {
    for (k = ZL; k < ZU+1; k++) {
        Ey_ptr[i][j][k] = 1;
    }
    }
    }
    for (i = XL; i < XU+1; i++) {
    for (j = YL; j < YU+1; j++) {
    for (k = ZL; k < ZU  ; k++) {
        Ez_ptr[i][j][k] = 1;
    }
    }
    }
    for (i = XL; i < XU+1; i++) {
    for (j = YL; j < YU  ; j++) {
    for (k = ZL; k < ZU  ; k++) {
        Hx_ptr[i][j][k] = 1;
    }
    }
    }
    for (i = XL; i < XU  ; i++) {
    for (j = YL; j < YU+1; j++) {
    for (k = ZL; k < ZU  ; k++) {
        Hy_ptr[i][j][k] = 1;
    }
    }
    }
    for (i = XL; i < XU  ; i++) {
    for (j = YL; j < YU  ; j++) {
    for (k = ZL; k < ZU+1; k++) {
        Hz_ptr[i][j][k] = 1;
    }
    }
    }
    
    begin = chrono::steady_clock::now();
    for (int n = 0; n < Nt; n++){
        #pragma omp parallel default(shared) private(i,j,k)
        {
        #pragma omp for collapse(2)
        for (i = XL  ; i < XU; i++){
        for (j = YL+1; j < YU; j++){
        for (k = ZL+1; k < ZU; k++){
            Ex_ptr[i][j][k] = AA * Ex_ptr[i][j][k] + A * Hy_ptr[i][j  ][k-1]
                                                   - B * Hy_ptr[i][j  ][k  ]
                                                   - C * Hz_ptr[i][j-1][k  ]
                                                   + D * Hz_ptr[i][j  ][k  ];
        }
        }
        }
        #pragma omp for collapse(2)
        for (i = XL+1; i < XU; i++){
        for (j = YL  ; j < YU; j++){
        for (k = ZL+1; k < ZU; k++){
            Ey_ptr[i][j][k] = AA * Ey_ptr[i][j][k] + A * Hz_ptr[i-1][j][k  ]
                                                   - B * Hz_ptr[i  ][j][k  ]
                                                   - C * Hx_ptr[i  ][j][k-1]
                                                   + D * Hx_ptr[i  ][j][k  ];
        }
        }
        }
        #pragma omp for collapse(2)
        for (i = XL+1; i < XU; i++){
        for (j = YL+1; j < YU; j++){
        for (k = ZL  ; k < ZU; k++){
            Ez_ptr[i][j][k] = AA * Ez_ptr[i][j][k] + A * Hx_ptr[i  ][j-1][k]
                                                   - B * Hx_ptr[i  ][j  ][k]
                                                   - C * Hy_ptr[i-1][j  ][k]
                                                   + D * Hy_ptr[i  ][j  ][k];
        }
        }
        }
        
        #pragma omp barrier
        
        #pragma omp for collapse(2)
        for (i = XL; i < XU+1; i++){
        for (j = YL; j < YU  ; j++){
        for (k = ZL; k < ZU  ; k++){
            Hx_ptr[i][j][k] = AA * Hx_ptr[i][j][k] - A * Ey_ptr[i][j  ][k  ]
                                                   + B * Ey_ptr[i][j  ][k+1]
                                                   + C * Ez_ptr[i][j  ][k  ]
                                                   - D * Ez_ptr[i][j+1][k  ];
        }
        }
        }
        #pragma omp for collapse(2)
        for (i = XL; i < XU  ; i++){
        for (j = YL; j < YU+1; j++){
        for (k = ZL; k < ZU  ; k++){
            Hy_ptr[i][j][k] = AA * Hy_ptr[i][j][k] - A * Ez_ptr[i  ][j][k  ]
                                                   + B * Ez_ptr[i+1][j][k  ]
                                                   + C * Ex_ptr[i  ][j][k  ]
                                                   - D * Ex_ptr[i  ][j][k+1];
        }
        }
        }
        #pragma omp for collapse(2)
        for (i = XL; i < XU  ; i++){
        for (j = YL; j < YU  ; j++){
        for (k = ZL; k < ZU+1; k++){
            Hz_ptr[i][j][k] = AA * Hz_ptr[i][j][k] - A * Ex_ptr[i  ][j  ][k]
                                                   + B * Ex_ptr[i  ][j+1][k]
                                                   + C * Ey_ptr[i  ][j  ][k]
                                                   - D * Ey_ptr[i+1][j  ][k];
        }
        }
        }
        }
    }
    end = chrono::steady_clock::now();
    
    for (i = XL; i < XU  ; i++) {
        for (j = YL;    j < YU+1; j++) {
            Ex_ptr[i][j].deallocate();
        }
        Ex_ptr[i].deallocate();
    }
    Ex_ptr.deallocate();
    for (i = XL; i < XU+1; i++) {
        for (j = YL;    j < YU  ; j++) {
            Ey_ptr[i][j].deallocate();
        }
        Ey_ptr[i].deallocate();
    }
    Ey_ptr.deallocate();
    for (i = XL; i < XU+1; i++) {
        for (j = YL;    j < YU+1; j++) {
            Ez_ptr[i][j].deallocate();
        }
        Ez_ptr[i].deallocate();
    }
    Ez_ptr.deallocate();
    for (i = XL; i < XU+1; i++) {
        for (j = YL;    j < YU  ; j++) {
            Hx_ptr[i][j].deallocate();
        }
        Hx_ptr[i].deallocate();
    }
    Hx_ptr.deallocate();
    for (i = XL; i < XU  ; i++) {
        for (j = YL;    j < YU+1; j++) {
            Hy_ptr[i][j].deallocate();
        }
        Hy_ptr[i].deallocate();
    }
    Hy_ptr.deallocate();
    for (i = XL; i < XU  ; i++) {
        for (j = YL;    j < YU  ; j++) {
            Hz_ptr[i][j].deallocate();
        }
        Hz_ptr[i].deallocate();
    }
    Hz_ptr.deallocate();

    cout << "Time (ptr) = " << (double)chrono::duration_cast<chrono::milliseconds>(end - begin).count() / 1000. << " s = "
        << (double)(1.*Nx * Ny * Nz * Nt) / (chrono::duration_cast<chrono::milliseconds>(end - begin).count()) / 1000. << " Mcells/s." << endl;

    /**********************/
   /*  6. Vector 3D ptr  */
  /**********************/

    Ex_3ptr.allocate(XL, YL, ZL, XU  , YU+1, ZU+1);
    Ey_3ptr.allocate(XL, YL, ZL, XU+1, YU  , ZU+1);
    Ez_3ptr.allocate(XL, YL, ZL, XU+1, YU+1, ZU  );
    Hx_3ptr.allocate(XL, YL, ZL, XU+1, YU  , ZU  );
    Hy_3ptr.allocate(XL, YL, ZL, XU  , YU+1, ZU  );
    Hz_3ptr.allocate(XL, YL, ZL, XU  , YU  , ZU+1);
    Ex_3ptr = 1.;
    Ey_3ptr = 1.;
    Ez_3ptr = 1.;
    Hx_3ptr = 1.;
    Hy_3ptr = 1.;
    Hz_3ptr = 1.;
    
    begin = chrono::steady_clock::now();
    for (int n = 0; n < Nt; n++){
        #pragma omp parallel default(shared) private(i,j,k)
        {
        #pragma omp for collapse(2)
        for (i = XL  ; i < XU; i++){
        for (j = YL+1; j < YU; j++){
        for (k = ZL+1; k < ZU; k++){
            Ex_3ptr[i][j][k] = AA * Ex_3ptr[i][j][k] + A * Hy_3ptr[i][j  ][k-1]
                                                     - B * Hy_3ptr[i][j  ][k  ]
                                                     - C * Hz_3ptr[i][j-1][k  ]
                                                     + D * Hz_3ptr[i][j  ][k  ];
        }
        }
        }
        #pragma omp for collapse(2)
        for (i = XL+1; i < XU; i++){
        for (j = YL  ; j < YU; j++){
        for (k = ZL+1; k < ZU; k++){
            Ey_3ptr[i][j][k] = AA * Ey_3ptr[i][j][k] + A * Hz_3ptr[i-1][j][k  ]
                                                     - B * Hz_3ptr[i  ][j][k  ]
                                                     - C * Hx_3ptr[i  ][j][k-1]
                                                     + D * Hx_3ptr[i  ][j][k  ];
        }
        }
        }
        #pragma omp for collapse(2)
        for (i = XL+1; i < XU; i++){
        for (j = YL+1; j < YU; j++){
        for (k = ZL  ; k < ZU; k++){
            Ez_3ptr[i][j][k] = AA * Ez_3ptr[i][j][k] + A * Hx_3ptr[i  ][j-1][k]
                                                     - B * Hx_3ptr[i  ][j  ][k]
                                                     - C * Hy_3ptr[i-1][j  ][k]
                                                     + D * Hy_3ptr[i  ][j  ][k];
        }
        }
        }
        
        #pragma omp barrier
        
        #pragma omp for collapse(2)
        for (i = XL; i < XU+1; i++){
        for (j = YL; j < YU  ; j++){
        for (k = ZL; k < ZU  ; k++){
            Hx_3ptr[i][j][k] = AA * Hx_3ptr[i][j][k] - A * Ey_3ptr[i][j  ][k  ]
                                                     + B * Ey_3ptr[i][j  ][k+1]
                                                     + C * Ez_3ptr[i][j  ][k  ]
                                                     - D * Ez_3ptr[i][j+1][k  ];
        }
        }
        }
        #pragma omp for collapse(2)
        for (i = XL; i < XU  ; i++){
        for (j = YL; j < YU+1; j++){
        for (k = ZL; k < ZU  ; k++){
            Hy_3ptr[i][j][k] = AA * Hy_3ptr[i][j][k] - A * Ez_3ptr[i  ][j][k  ]
                                                     + B * Ez_3ptr[i+1][j][k  ]
                                                     + C * Ex_3ptr[i  ][j][k  ]
                                                     - D * Ex_3ptr[i  ][j][k+1];
        }
        }
        }
        #pragma omp for collapse(2)
        for (i = XL; i < XU  ; i++){
        for (j = YL; j < YU  ; j++){
        for (k = ZL; k < ZU+1; k++){
            Hz_3ptr[i][j][k] = AA * Hz_3ptr[i][j][k] - A * Ex_3ptr[i  ][j  ][k]
                                                     + B * Ex_3ptr[i  ][j+1][k]
                                                     + C * Ey_3ptr[i  ][j  ][k]
                                                     - D * Ey_3ptr[i+1][j  ][k];
        }
        }
        }
        }
    }
    end = chrono::steady_clock::now();

    Ex_3ptr.deallocate();
    Ey_3ptr.deallocate();
    Ez_3ptr.deallocate();
    Hx_3ptr.deallocate();
    Hy_3ptr.deallocate();
    Hz_3ptr.deallocate();

    cout << "Time (3D ptr) = " << (double)chrono::duration_cast<chrono::milliseconds>(end - begin).count() / 1000. << " s = "
        << (double)(1.*Nx * Ny * Nz * Nt) / (chrono::duration_cast<chrono::milliseconds>(end - begin).count()) / 1000. << " Mcells/s." << endl;

    /******************************/
   /*  7.1. Vector 3D complicao  */
  /******************************/

    Ex_c.allocate(XL, YL, ZL, XU  , YU+1, ZU+1);
    Ey_c.allocate(XL, YL, ZL, XU+1, YU  , ZU+1);
    Ez_c.allocate(XL, YL, ZL, XU+1, YU+1, ZU  );
    Hx_c.allocate(XL, YL, ZL, XU+1, YU  , ZU  );
    Hy_c.allocate(XL, YL, ZL, XU  , YU+1, ZU  );
    Hz_c.allocate(XL, YL, ZL, XU  , YU  , ZU+1);
    Ex_c = 1.;
    Ey_c = 1.;
    Ez_c = 1.;
    Hx_c = 1.;
    Hy_c = 1.;
    Hz_c = 1.;
    
    begin = chrono::steady_clock::now();
    for (int n = 0; n < Nt; n++){
        #pragma omp parallel default(shared) private(i,j,k)
        {
        #pragma omp for collapse(2)
        for (i = XL  ; i < XU; i++){
        for (j = YL+1; j < YU; j++){
        for (k = ZL+1; k < ZU; k++){
            Ex_c[i][j][k] = AA * Ex_c[i][j][k] + A * Hy_c[i][j  ][k-1]
                                               - B * Hy_c[i][j  ][k  ]
                                               - C * Hz_c[i][j-1][k  ]
                                               + D * Hz_c[i][j  ][k  ];
        }
        }
        }
        #pragma omp for collapse(2)
        for (i = XL+1; i < XU; i++){
        for (j = YL  ; j < YU; j++){
        for (k = ZL+1; k < ZU; k++){
            Ey_c[i][j][k] = AA * Ey_c[i][j][k] + A * Hz_c[i-1][j][k  ]
                                               - B * Hz_c[i  ][j][k  ]
                                               - C * Hx_c[i  ][j][k-1]
                                               + D * Hx_c[i  ][j][k  ];
        }
        }
        }
        #pragma omp for collapse(2)
        for (i = XL+1; i < XU; i++){
        for (j = YL+1; j < YU; j++){
        for (k = ZL  ; k < ZU; k++){
            Ez_c[i][j][k] = AA * Ez_c[i][j][k] + A * Hx_c[i  ][j-1][k]
                                               - B * Hx_c[i  ][j  ][k]
                                               - C * Hy_c[i-1][j  ][k]
                                               + D * Hy_c[i  ][j  ][k];
        }
        }
        }
        
        #pragma omp barrier
        
        #pragma omp for collapse(2)
        for (i = XL; i < XU+1; i++){
        for (j = YL; j < YU  ; j++){
        for (k = ZL; k < ZU  ; k++){
            Hx_c[i][j][k] = AA * Hx_c[i][j][k] - A * Ey_c[i][j  ][k  ]
                                               + B * Ey_c[i][j  ][k+1]
                                               + C * Ez_c[i][j  ][k  ]
                                               - D * Ez_c[i][j+1][k  ];
        }
        }
        }
        #pragma omp for collapse(2)
        for (i = XL; i < XU  ; i++){
        for (j = YL; j < YU+1; j++){
        for (k = ZL; k < ZU  ; k++){
            Hy_c[i][j][k] = AA * Hy_c[i][j][k] - A * Ez_c[i  ][j][k  ]
                                               + B * Ez_c[i+1][j][k  ]
                                               + C * Ex_c[i  ][j][k  ]
                                               - D * Ex_c[i  ][j][k+1];
        }
        }
        }
        #pragma omp for collapse(2)
        for (i = XL; i < XU  ; i++){
        for (j = YL; j < YU  ; j++){
        for (k = ZL; k < ZU+1; k++){
            Hz_c[i][j][k] = AA * Hz_c[i][j][k] - A * Ex_c[i  ][j  ][k]
                                               + B * Ex_c[i  ][j+1][k]
                                               + C * Ey_c[i  ][j  ][k]
                                               - D * Ey_c[i+1][j  ][k];
        }
        }
        }
        }
    }
    end = chrono::steady_clock::now();

    Ex_c.deallocate();
    Ey_c.deallocate();
    Ez_c.deallocate();
    Hx_c.deallocate();
    Hy_c.deallocate();
    Hz_c.deallocate();

    cout << "Time (complicao) = " << (double)chrono::duration_cast<chrono::milliseconds>(end - begin).count() / 1000. << " s = "
         << (double)(1.*Nx * Ny * Nz * Nt) / (chrono::duration_cast<chrono::milliseconds>(end - begin).count()) / 1000. << " Mcells/s." << endl;

    /************************************/
   /*  7.2. Vector 3D complicao (.arr) */
  /************************************/

    Ex_c.allocate(XL, YL, ZL, XU  , YU+1, ZU+1);
    Ey_c.allocate(XL, YL, ZL, XU+1, YU  , ZU+1);
    Ez_c.allocate(XL, YL, ZL, XU+1, YU+1, ZU  );
    Hx_c.allocate(XL, YL, ZL, XU+1, YU  , ZU  );
    Hy_c.allocate(XL, YL, ZL, XU  , YU+1, ZU  );
    Hz_c.allocate(XL, YL, ZL, XU  , YU  , ZU+1);
    Ex_c = 1.;
    Ey_c = 1.;
    Ez_c = 1.;
    Hx_c = 1.;
    Hy_c = 1.;
    Hz_c = 1.;
    
    begin = chrono::steady_clock::now();
    for (int n = 0; n < Nt; n++){
        #pragma omp parallel default(shared) private(i,j,k)
        {
        #pragma omp for collapse(2)
        for (i = XL  ; i < XU; i++){
        for (j = YL+1; j < YU; j++){
        for (k = ZL+1; k < ZU; k++){
            Ex_c.arr[i][j][k] = AA * Ex_c.arr[i][j][k] + A * Hy_c.arr[i][j  ][k-1]
                                               - B * Hy_c.arr[i][j  ][k  ]
                                               - C * Hz_c.arr[i][j-1][k  ]
                                               + D * Hz_c.arr[i][j  ][k  ];
        }
        }
        }
        #pragma omp for collapse(2)
        for (i = XL+1; i < XU; i++){
        for (j = YL  ; j < YU; j++){
        for (k = ZL+1; k < ZU; k++){
            Ey_c.arr[i][j][k] = AA * Ey_c.arr[i][j][k] + A * Hz_c.arr[i-1][j][k  ]
                                               - B * Hz_c.arr[i  ][j][k  ]
                                               - C * Hx_c.arr[i  ][j][k-1]
                                               + D * Hx_c.arr[i  ][j][k  ];
        }
        }
        }
        #pragma omp for collapse(2)
        for (i = XL+1; i < XU; i++){
        for (j = YL+1; j < YU; j++){
        for (k = ZL  ; k < ZU; k++){
            Ez_c.arr[i][j][k] = AA * Ez_c.arr[i][j][k] + A * Hx_c.arr[i  ][j-1][k]
                                               - B * Hx_c.arr[i  ][j  ][k]
                                               - C * Hy_c.arr[i-1][j  ][k]
                                               + D * Hy_c.arr[i  ][j  ][k];
        }
        }
        }
        
        #pragma omp barrier
        
        #pragma omp for collapse(2)
        for (i = XL; i < XU+1; i++){
        for (j = YL; j < YU  ; j++){
        for (k = ZL; k < ZU  ; k++){
            Hx_c.arr[i][j][k] = AA * Hx_c.arr[i][j][k] - A * Ey_c.arr[i][j  ][k  ]
                                               + B * Ey_c.arr[i][j  ][k+1]
                                               + C * Ez_c.arr[i][j  ][k  ]
                                               - D * Ez_c.arr[i][j+1][k  ];
        }
        }
        }
        #pragma omp for collapse(2)
        for (i = XL; i < XU  ; i++){
        for (j = YL; j < YU+1; j++){
        for (k = ZL; k < ZU  ; k++){
            Hy_c.arr[i][j][k] = AA * Hy_c.arr[i][j][k] - A * Ez_c.arr[i  ][j][k  ]
                                               + B * Ez_c.arr[i+1][j][k  ]
                                               + C * Ex_c.arr[i  ][j][k  ]
                                               - D * Ex_c.arr[i  ][j][k+1];
        }
        }
        }
        #pragma omp for collapse(2)
        for (i = XL; i < XU  ; i++){
        for (j = YL; j < YU  ; j++){
        for (k = ZL; k < ZU+1; k++){
            Hz_c.arr[i][j][k] = AA * Hz_c.arr[i][j][k] - A * Ex_c.arr[i  ][j  ][k]
                                               + B * Ex_c.arr[i  ][j+1][k]
                                               + C * Ey_c.arr[i  ][j  ][k]
                                               - D * Ey_c.arr[i+1][j  ][k];
        }
        }
        }
        }
    }
    end = chrono::steady_clock::now();

    Ex_c.deallocate();
    Ey_c.deallocate();
    Ez_c.deallocate();
    Hx_c.deallocate();
    Hy_c.deallocate();
    Hz_c.deallocate();

    cout << "Time (complicao .arr) = " << (double)chrono::duration_cast<chrono::milliseconds>(end - begin).count() / 1000. << " s = "
        << (double)(1.*Nx * Ny * Nz * Nt) / (chrono::duration_cast<chrono::milliseconds>(end - begin).count()) / 1000. << " Mcells/s." << endl;

      /****************************************/
     /*  7.3. Vector 3D complicao sin clases */
    /****************************************/
    double ***Ex_c_lvl0, ***Ex_c_lvl1, ***Ex_c_lvl2, ***Ex_c_lvl3;
    double ***Ey_c_lvl0, ***Ey_c_lvl1, ***Ey_c_lvl2, ***Ey_c_lvl3;
    double ***Ez_c_lvl0, ***Ez_c_lvl1, ***Ez_c_lvl2, ***Ez_c_lvl3;
    double ***Hx_c_lvl0, ***Hx_c_lvl1, ***Hx_c_lvl2, ***Hx_c_lvl3;
    double ***Hy_c_lvl0, ***Hy_c_lvl1, ***Hy_c_lvl2, ***Hy_c_lvl3;
    double ***Hz_c_lvl0, ***Hz_c_lvl1, ***Hz_c_lvl2, ***Hz_c_lvl3;

    allocate(Ex_c_lvl0, Ex_c_lvl1, Ex_c_lvl2, Ex_c_lvl3, XL, YL, ZL, XU  , YU+1, ZU+1);
    allocate(Ey_c_lvl0, Ey_c_lvl1, Ey_c_lvl2, Ey_c_lvl3, XL, YL, ZL, XU+1, YU  , ZU+1);
    allocate(Ez_c_lvl0, Ez_c_lvl1, Ez_c_lvl2, Ez_c_lvl3, XL, YL, ZL, XU+1, YU+1, ZU  );
    allocate(Hx_c_lvl0, Hx_c_lvl1, Hx_c_lvl2, Hx_c_lvl3, XL, YL, ZL, XU+1, YU  , ZU  );
    allocate(Hy_c_lvl0, Hy_c_lvl1, Hy_c_lvl2, Hy_c_lvl3, XL, YL, ZL, XU  , YU+1, ZU  );
    allocate(Hz_c_lvl0, Hz_c_lvl1, Hz_c_lvl2, Hz_c_lvl3, XL, YL, ZL, XU  , YU  , ZU+1);
    
    begin = chrono::steady_clock::now();
    for (int n = 0; n < Nt; n++){
        #pragma omp parallel default(shared) private(i,j,k)
        {
        #pragma omp for collapse(2)
        for (i = 0; i < Nx; i++){
        for (j = 1; j < Ny; j++){
        for (k = 1; k < Nz; k++){
            Ex_c_lvl3[i][j][k] = AA * Ex_c_lvl3[i][j][k] + A * Hy_c_lvl3[i][j  ][k-1]
                                                         - B * Hy_c_lvl3[i][j  ][k  ]
                                                         - C * Hz_c_lvl3[i][j-1][k  ]
                                                         + D * Hz_c_lvl3[i][j  ][k  ];
        }
        }
        }
        #pragma omp for collapse(2)
        for (i = 1; i < Nx; i++){
        for (j = 0; j < Ny; j++){
        for (k = 1; k < Nz; k++){
            Ey_c_lvl3[i][j][k] = AA * Ey_c_lvl3[i][j][k] + A * Hz_c_lvl3[i-1][j][k  ]
                                                         - B * Hz_c_lvl3[i  ][j][k  ]
                                                         - C * Hx_c_lvl3[i  ][j][k-1]
                                                         + D * Hx_c_lvl3[i  ][j][k  ];
        }
        }
        }
        #pragma omp for collapse(2)
        for (i = 1; i < Nx; i++){
        for (j = 1; j < Ny; j++){
        for (k = 0; k < Nz; k++){
            Ez_c_lvl3[i][j][k] = AA * Ez_c_lvl3[i][j][k] + A * Hx_c_lvl3[i  ][j-1][k]
                                                         - B * Hx_c_lvl3[i  ][j  ][k]
                                                         - C * Hy_c_lvl3[i-1][j  ][k]
                                                         + D * Hy_c_lvl3[i  ][j  ][k];
        }
        }
        }
        
        #pragma omp barrier
        
        #pragma omp for collapse(2)
        for (i = 0; i < Nx+1; i++){
        for (j = 0; j < Ny  ; j++){
        for (k = 0; k < Nz  ; k++){
            Hx_c_lvl3[i][j][k] = AA * Hx_c_lvl3[i][j][k] - A * Ey_c_lvl3[i][j  ][k  ]
                                                         + B * Ey_c_lvl3[i][j  ][k+1]
                                                         + C * Ez_c_lvl3[i][j  ][k  ]
                                                         - D * Ez_c_lvl3[i][j+1][k  ];
        }
        }
        }
        #pragma omp for collapse(2)
        for (i = 0; i < Nx  ; i++){
        for (j = 0; j < Ny+1; j++){
        for (k = 0; k < Nz  ; k++){
            Hy_c_lvl3[i][j][k] = AA * Hy_c_lvl3[i][j][k] - A * Ez_c_lvl3[i  ][j][k  ]
                                                         + B * Ez_c_lvl3[i+1][j][k  ]
                                                         + C * Ex_c_lvl3[i  ][j][k  ]
                                                         - D * Ex_c_lvl3[i  ][j][k+1];
        }
        }
        }
        #pragma omp for collapse(2)
        for (i = 0; i < Nx  ; i++){
        for (j = 0; j < Ny  ; j++){
        for (k = 0; k < Nz+1; k++){
            Hz_c_lvl3[i][j][k] = AA * Hz_c_lvl3[i][j][k] - A * Ex_c_lvl3[i  ][j  ][k]
                                                         + B * Ex_c_lvl3[i  ][j+1][k]
                                                         + C * Ey_c_lvl3[i  ][j  ][k]
                                                         - D * Ey_c_lvl3[i+1][j  ][k];
        }
        }
        }
        }
    }
    end = chrono::steady_clock::now();

    cout << "Time (a3) = " << (double)chrono::duration_cast<chrono::milliseconds>(end - begin).count() / 1000. << " s = "
        << (double)(1.*Nx * Ny * Nz * Nt) / (chrono::duration_cast<chrono::milliseconds>(end - begin).count()) / 1000. << " Mcells/s." << endl;
    
    begin = chrono::steady_clock::now();
    for (int n = 0; n < Nt; n++){
        #pragma omp parallel default(shared) private(i,j,k)
        {
        #pragma omp for collapse(2)
        for (i = XL  ; i < XU; i++){
        for (j = YL+1; j < YU; j++){
        for (k = ZL+1; k < ZU; k++){
            Ex_c_lvl0[i][j][k] = AA * Ex_c_lvl0[i][j][k] + A * Hy_c_lvl0[i][j  ][k-1]
                                                         - B * Hy_c_lvl0[i][j  ][k  ]
                                                         - C * Hz_c_lvl0[i][j-1][k  ]
                                                         + D * Hz_c_lvl0[i][j  ][k  ];
        }
        }
        }
        #pragma omp for collapse(2)
        for (i = XL+1; i < XU; i++){
        for (j = YL  ; j < YU; j++){
        for (k = ZL+1; k < ZU; k++){
            Ey_c_lvl0[i][j][k] = AA * Ey_c_lvl0[i][j][k] + A * Hz_c_lvl0[i-1][j][k  ]
                                                         - B * Hz_c_lvl0[i  ][j][k  ]
                                                         - C * Hx_c_lvl0[i  ][j][k-1]
                                                         + D * Hx_c_lvl0[i  ][j][k  ];
        }
        }
        }
        #pragma omp for collapse(2)
        for (i = XL+1; i < XU; i++){
        for (j = YL+1; j < YU; j++){
        for (k = ZL  ; k < ZU; k++){
            Ez_c_lvl0[i][j][k] = AA * Ez_c_lvl0[i][j][k] + A * Hx_c_lvl0[i  ][j-1][k]
                                                         - B * Hx_c_lvl0[i  ][j  ][k]
                                                         - C * Hy_c_lvl0[i-1][j  ][k]
                                                         + D * Hy_c_lvl0[i  ][j  ][k];
        }
        }
        }
        
        #pragma omp barrier
        
        #pragma omp for collapse(2)
        for (i = XL; i < XU+1; i++){
        for (j = YL; j < YU  ; j++){
        for (k = ZL; k < ZU  ; k++){
            Hx_c_lvl0[i][j][k] = AA * Hx_c_lvl0[i][j][k] - A * Ey_c_lvl0[i][j  ][k  ]
                                                         + B * Ey_c_lvl0[i][j  ][k+1]
                                                         + C * Ez_c_lvl0[i][j  ][k  ]
                                                         - D * Ez_c_lvl0[i][j+1][k  ];
        }
        }
        }
        #pragma omp for collapse(2)
        for (i = XL; i < XU  ; i++){
        for (j = YL; j < YU+1; j++){
        for (k = ZL; k < ZU  ; k++){
            Hy_c_lvl0[i][j][k] = AA * Hy_c_lvl0[i][j][k] - A * Ez_c_lvl0[i  ][j][k  ]
                                                         + B * Ez_c_lvl0[i+1][j][k  ]
                                                         + C * Ex_c_lvl0[i  ][j][k  ]
                                                         - D * Ex_c_lvl0[i  ][j][k+1];
        }
        }
        }
        #pragma omp for collapse(2)
        for (i = XL; i < XU  ; i++){
        for (j = YL; j < YU  ; j++){
        for (k = ZL; k < ZU+1; k++){
            Hz_c_lvl0[i][j][k] = AA * Hz_c_lvl0[i][j][k] - A * Ex_c_lvl0[i  ][j  ][k]
                                                         + B * Ex_c_lvl0[i  ][j+1][k]
                                                         + C * Ey_c_lvl0[i  ][j  ][k]
                                                         - D * Ey_c_lvl0[i+1][j  ][k];
        }
        }
        }
        }
    }
    end = chrono::steady_clock::now();

    cout << "Time (a) = " << (double)chrono::duration_cast<chrono::milliseconds>(end - begin).count() / 1000. << " s = "
        << (double)(1.*Nx * Ny * Nz * Nt) / (chrono::duration_cast<chrono::milliseconds>(end - begin).count()) / 1000. << " Mcells/s." << endl;
    
    deallocate(Ex_c_lvl0, Ex_c_lvl1, Ex_c_lvl2, Ex_c_lvl3, XL, YL, ZL, XU  , YU+1, ZU+1);
    deallocate(Ey_c_lvl0, Ey_c_lvl1, Ey_c_lvl2, Ey_c_lvl3, XL, YL, ZL, XU+1, YU  , ZU+1);
    deallocate(Ez_c_lvl0, Ez_c_lvl1, Ez_c_lvl2, Ez_c_lvl3, XL, YL, ZL, XU+1, YU+1, ZU  );
    deallocate(Hx_c_lvl0, Hx_c_lvl1, Hx_c_lvl2, Hx_c_lvl3, XL, YL, ZL, XU+1, YU  , ZU  );
    deallocate(Hy_c_lvl0, Hy_c_lvl1, Hy_c_lvl2, Hy_c_lvl3, XL, YL, ZL, XU  , YU+1, ZU  );
    deallocate(Hz_c_lvl0, Hz_c_lvl1, Hz_c_lvl2, Hz_c_lvl3, XL, YL, ZL, XU  , YU  , ZU+1);
}

void allocate_native(double***& arr, int x0, int y0, int z0, int x1, int y1, int z1){
    int s[3];

    s[0] = x1-x0;
    s[1] = y1-y0;
    s[2] = z1-z0;

    arr = new double**[s[0]];
    for (int i = 0; i < s[0]; i++) {
        arr[i] = new double*[s[1]];
        for (int j = 0; j < s[1]; j++) {
            arr[i][j] = new double[s[2]];
            for (int k = 0; k < s[1]; k++) {
                arr[i][j][k] = 1.;
            }
        }
    }
}

void deallocate_native(double*** &arr, int x0, int y0, int z0, int x1, int y1, int z1){
    int s[3];

    s[0] = x1-x0;
    s[1] = y1-y0;
    s[2] = z1-z0;
    
    for (int i = 0; i < s[0]; i++) {
        for (int j = 0; j < s[1]; j++) {
            delete [] arr[i][j];
        }
        delete [] arr[i];
    }
    delete [] arr;
}

void allocate(double*** &arr, double*** &arr_lvl0, double*** &arr_lvl1, double*** &arr_lvl2, int x0, int y0, int z0, int x1, int y1, int z1){
    int s[3];

    s[0] = x1-x0;
    s[1] = y1-y0;
    s[2] = z1-z0;

    arr_lvl2 = new double**[s[0]];
    for (int i = 0; i < s[0]; i++) {
        arr_lvl2[i] = new double*[s[1]];
        for (int j = 0; j < s[1]; j++) {
            arr_lvl2[i][j] = new double[s[2]];
            for (int k = 0; k < s[1]; k++) {
                arr_lvl2[i][j][k] = 1.;
            }
        }
    }

    arr_lvl1 = new double**[s[0]];
    for (int i = 0; i < s[0]; i++) {
        arr_lvl1[i] = new double*[s[1]];
        for (int j = 0; j < s[1]; j++) {
            arr_lvl1[i][j] = arr_lvl2[i][j] - z0;
        }
    }

    arr_lvl0 = new double**[s[0]];
    for (int i = 0; i < s[0]; i++) {
        arr_lvl0[i] = arr_lvl1[i] - y0;
    }

    arr = arr_lvl0 - x0;
}

void deallocate(double*** &arr, double*** &arr_lvl0, double*** &arr_lvl1, double*** &arr_lvl2, int x0, int y0, int z0, int x1, int y1, int z1){
    int s[3];

    s[0] = x1-x0;
    s[1] = y1-y0;
    s[2] = z1-z0;
    
    for (int i = 0; i < s[0]; i++) {
        for (int j = 0; j < s[1]; j++) {
            delete [] arr_lvl2[i][j];
        }
        delete [] arr_lvl2[i];
        delete [] arr_lvl1[i];
    }
    delete [] arr_lvl2;
    delete [] arr_lvl1;
    delete [] arr_lvl0;
}

//#include <iostream>
//#include <chrono>
//
//using namespace std;
//
//int main() {
//    double **a, **a1, **a2;
//    double **b, **b1, **b2;
//    int i0 = -1000;
//    int j0 = -1000;
//    int i1 = +1000;
//    int j1 = +1000;
//    int Nx = i1-i0;
//    int Ny = j1-j0;
//    double C1 = 1., C2 = 1., C3 = 1.;
//    chrono::steady_clock::time_point begin, end;
//
//    /* Allocate */
//    /* a2 */
//    a2 = new double*[Nx];
//    for (int i = 0; i < Nx; i++) {
//        a2[i] = new double[Ny];
//    }
//    
//    /* a1 */
//    a1 = new double*[Nx];
//    for (int i = 0; i < Nx; i++) {
//        a1[i] = a2[i] - j0;  // a1[i][j0+j] == *(a1[i]+j0+j) == *(a2[i]+j) == a2[i][j]
//    }
//
//    /* a */
//    a = a1 - i0;  // a[i0+i][j0+j] == (*(a+i0+i))[j0+j] == (*(a1+i))[j0+j] == a1[i][j0+j] == a2[i][j]
//
//    /* b2 */
//    b2 = new double*[Nx];
//    for (int i = 0; i < Nx; i++) {
//        b2[i] = new double[Ny];
//    }
//    
//    /* b1 */
//    b1 = new double*[Nx];
//    for (int i = 0; i < Nx; i++) {
//        b1[i] = b2[i] - j0;  // b1[i][j0+j] == *(b1[i]+j0+j) == *(b2[i]+j) == b2[i][j]
//    }
//
//    /* b */
//    b = b1 - i0;  // b[i0+i][j0+j] == (*(b+i0+i))[j0+j] == (*(b1+i))[j0+j] == b1[i][j0+j] == b2[i][j]
//    
//    int Nt = 100;
//
//    /* Using a2 */
//    begin = chrono::steady_clock::now();
//    for (int n = 0; n < Nt; n++){
//        for (int i = 1; i < Nx; i++) {
//        for (int j = 1; j < Ny; j++) {
//            a2[i][j] = C1 * a2[i][j] + C2 * (b2[i-1][j  ] - b2[i][j])
//                                     + C3 * (b2[i  ][j-1] - b2[j][j]);
//        }
//        }
//        for (int i = 0; i < Nx-1; i++) {
//        for (int j = 0; j < Ny-1; j++) {
//            b2[i][j] = C1 * b2[i][j] - C2 * (a2[i+1][j  ] - a2[i][j])
//                                     - C3 * (a2[i  ][j+1] - a2[j][j]);
//        }
//        }
//    }
//    end = chrono::steady_clock::now();
//    cout << "Time (a): " << (double)chrono::duration_cast<chrono::milliseconds>(end - begin).count() << " ms.\n";
//
//    /* Using a */
//    begin = chrono::steady_clock::now();
//    for (int n = 0; n < Nt; n++){
//        for (int i = i0+1; i < i1; i++) {
//        for (int j = j0+1; j < j1; j++) {
//            a[i][j] = C1 * a[i][j] + C2 * (b[i-1][j  ] - b[i][j])
//                                   + C3 * (b[i  ][j-1] - b[j][j]);
//        }
//        }
//        for (int i = i0; i < i1-1; i++) {
//        for (int j = j0; j < j1-1; j++) {
//            b[i][j] = C1 * b[i][j] - C2 * (a[i+1][j  ] - a[i][j])
//                                   - C3 * (a[i  ][j+1] - a[j][j]);
//        }
//        }
//    }
//    end = chrono::steady_clock::now();
//    cout << "Time (b): " << (double)chrono::duration_cast<chrono::milliseconds>(end - begin).count() << " ms.\n";
//}
//
//#include <iostream>
//#include <chrono>
//
//using namespace std;
//
//template <class T>
//void allocate(T*** &arr, T*** &arr_lvl0, T*** &arr_lvl1, T*** &arr_lvl2, int x0, int y0, int z0, int x1, int y1, int z1);
//
//int main() {
//    double ***ax, ***a1x, ***a2x, ***a3x;
//    double ***bx, ***b1x, ***b2x, ***b3x;
//    double ***ay, ***a1y, ***a2y, ***a3y;
//    double ***by, ***b1y, ***b2y, ***b3y;
//    double ***az, ***a1z, ***a2z, ***a3z;
//    double ***bz, ***b1z, ***b2z, ***b3z;
//    int i0 = -300;
//    int j0 = -300;
//    int k0 = -300;
//    int i1 = +300;
//    int j1 = +300;
//    int k1 = +300;
//    int Nt = +50;
//    int Nx = i1-i0;
//    int Ny = j1-j0;
//    int Nz = k1-k0;
//    double C1 = 1., C2 = 1., C3 = 1., C4 = 1.;
//    int i, j, k;
//    chrono::steady_clock::time_point begin, end;
//
//    /* Allocate */
//    allocate(ax, a1x, a2x, a3x, i0, j0, k0, i1, j1, k1);
//    allocate(bx, b1x, b2x, b3x, i0, j0, k0, i1, j1, k1);
//    allocate(ay, a1y, a2y, a3y, i0, j0, k0, i1, j1, k1);
//    allocate(by, b1y, b2y, b3y, i0, j0, k0, i1, j1, k1);
//    allocate(az, a1z, a2z, a3z, i0, j0, k0, i1, j1, k1);
//    allocate(bz, b1z, b2z, b3z, i0, j0, k0, i1, j1, k1);
//    
//    /* Using a3 */
//    begin = chrono::steady_clock::now();
//    for (int n = 0; n < Nt; n++){
//        #pragma omp parallel default(shared) private(i,j,k)
//        {
//        #pragma omp for collapse(2)
//        for (i = 1; i < Nx; i++) {
//        for (j = 1; j < Ny; j++) {
//        for (k = 1; k < Nz; k++) {
//            a3x[i][j][k] = C1 * a3x[i][j][k] + C2 * (b3y[i  ][j  ][k-1] - b3y[i][j][k])
//                                             + C3 * (b3z[i  ][j-1][k  ] - b3z[i][j][k]);
//        }
//        }
//        }
//        #pragma omp for collapse(2)
//        for (i = 1; i < Nx; i++) {
//        for (j = 1; j < Ny; j++) {
//        for (k = 1; k < Nz; k++) {
//            a3y[i][j][k] = C1 * a3y[i][j][k] + C2 * (b3z[i-1][j  ][k  ] - b3z[i][j][k])
//                                             + C3 * (b3x[i  ][j  ][k-1] - b3x[i][j][k]);
//        }
//        }
//        }
//        #pragma omp for collapse(2)
//        for (i = 1; i < Nx; i++) {
//        for (j = 1; j < Ny; j++) {
//        for (k = 1; k < Nz; k++) {
//            a3z[i][j][k] = C1 * a3z[i][j][k] + C2 * (b3x[i  ][j-1][k  ] - b3x[i][j][k])
//                                             + C3 * (b3y[i-1][j  ][k-1] - b3y[i][j][k]);
//        }
//        }
//        }
//
//        #pragma omp barrier
//
//        #pragma omp for collapse(2)
//        for (i = 0; i < Nx-1; i++) {
//        for (j = 0; j < Ny-1; j++) {
//        for (k = 0; k < Nz-1; k++) {
//            b3x[i][j][k] = C1 * b3x[i][j][k] + C2 * (a3y[i  ][j  ][k+1] - a3y[i][j][k])
//                                             + C3 * (a3z[i  ][j+1][k  ] - a3z[i][j][k]);
//        }
//        }
//        }
//        #pragma omp for collapse(2)
//        for (i = 0; i < Nx-1; i++) {
//        for (j = 0; j < Ny-1; j++) {
//        for (k = 0; k < Nz-1; k++) {
//            b3y[i][j][k] = C1 * b3y[i][j][k] + C2 * (a3z[i+1][j  ][k  ] - a3z[i][j][k])
//                                             + C3 * (a3x[i  ][j  ][k+1] - a3x[i][j][k]);
//        }
//        }
//        }
//        #pragma omp for collapse(2)
//        for (i = 0; i < Nx-1; i++) {
//        for (j = 0; j < Ny-1; j++) {
//        for (k = 0; k < Nz-1; k++) {
//            b3z[i][j][k] = C1 * b3z[i][j][k] + C2 * (a3x[i  ][j+1][k  ] - a3x[i][j][k])
//                                             + C3 * (a3y[i+1][j  ][k  ] - a3y[i][j][k]);
//        }
//        }
//        }
//        }
//    }
//    end = chrono::steady_clock::now();
//    cout << "Time (a): " << (double)chrono::duration_cast<chrono::milliseconds>(end - begin).count() << " ms.\n";
//
//     Using a
//    begin = chrono::steady_clock::now();
//    for (int n = 0; n < Nt; n++){
//        #pragma omp parallel default(shared) private(i,j,k)
//        {
//        #pragma omp for collapse(2)
//        for (int i = i0+1; i < i1; i++) {
//        for (int j = j0+1; j < j1; j++) {
//        for (int k = k0+1; k < k1; k++) {
//            ax[i][j][k] = C1 * ax[i][j][k] + C2 * (by[i  ][j  ][k-1] - by[i][j][k])
//                                           + C3 * (bz[i  ][j-1][k  ] - bz[i][j][k]);
//        }
//        }
//        }
//        #pragma omp for collapse(2)
//        for (int i = i0+1; i < i1; i++) {
//        for (int j = j0+1; j < j1; j++) {
//        for (int k = k0+1; k < k1; k++) {
//            ay[i][j][k] = C1 * ay[i][j][k] + C2 * (bz[i-1][j  ][k  ] - bz[i][j][k])
//                                           + C3 * (bx[i  ][j  ][k-1] - bx[i][j][k]);
//        }
//        }
//        }
//        #pragma omp for collapse(2)
//        for (int i = i0+1; i < i1; i++) {
//        for (int j = j0+1; j < j1; j++) {
//        for (int k = k0+1; k < k1; k++) {
//            az[i][j][k] = C1 * az[i][j][k] + C2 * (bx[i  ][j-1][k  ] - bx[i][j][k])
//                                           + C3 * (by[i-1][j  ][k-1] - by[i][j][k]);
//        }
//        }
//        }
//
//        #pragma omp barrier
//
//        #pragma omp for collapse(2)
//        for (int i = i0; i < i1-1; i++) {
//        for (int j = j0; j < j1-1; j++) {
//        for (int k = k0; k < k1-1; k++) {
//            bx[i][j][k] = C1 * bx[i][j][k] + C2 * (ay[i  ][j  ][k+1] - ay[i][j][k])
//                                           + C3 * (az[i  ][j+1][k  ] - az[i][j][k]);
//        }
//        }
//        }
//        #pragma omp for collapse(2)
//        for (int i = i0; i < i1-1; i++) {
//        for (int j = j0; j < j1-1; j++) {
//        for (int k = k0; k < k1-1; k++) {
//            by[i][j][k] = C1 * by[i][j][k] + C2 * (az[i+1][j  ][k  ] - az[i][j][k])
//                                           + C3 * (ax[i  ][j  ][k+1] - ax[i][j][k]);
//        }
//        }
//        }
//        #pragma omp for collapse(2)
//        for (int i = i0; i < i1-1; i++) {
//        for (int j = j0; j < j1-1; j++) {
//        for (int k = k0; k < k1-1; k++) {
//            bz[i][j][k] = C1 * bz[i][j][k] + C2 * (ax[i  ][j+1][k  ] - ax[i][j][k])
//                                           + C3 * (ay[i+1][j  ][k  ] - ay[i][j][k]);
//        }
//        }
//        }
//        }
//    }
//    end = chrono::steady_clock::now();
//    cout << "Time (b): " << (double)chrono::duration_cast<chrono::milliseconds>(end - begin).count() << " ms.\n";
//}
//
//template <class T>
//void allocate(T*** &arr, T*** &arr1, T*** &arr2, T*** &arr3, int x0, int y0, int z0, int x1, int y1, int z1){
//    int s[3];
//
//    s[0] = x1-x0;
//    s[1] = y1-y0;
//    s[2] = z1-z0;
//
//    arr3 = new T**[s[0]];
//    arr2 = new T**[s[0]];
//    arr1 = new T**[s[0]];
//    arr = arr1 - x0;
//    for (int i = 0; i < s[0]; i++) {
//        arr3[i] = new T*[s[1]];
//        arr2[i] = new T*[s[1]];
//        arr1[i] = arr2[i] - y0;
//        for (int j = 0; j < s[1]; j++) {
//            arr3[i][j] = new T[s[2]];
//            arr2[i][j] = arr3[i][j] - z0;
//            for (int k = 0; k < s[2]; k++) {
//                arr3[i][j][k] = 1.;
//            }
//        }
//    }
//    
//}
