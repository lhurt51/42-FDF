#include "fdf.h"

/*---------- Sources ----------*/

//http://www.ecere.com/3dbhole/mathematics_of_3d_graphics.html
//http://www.ecere.com/3dbhole/3d_transformations.html

/*---------- Basic Matrix System ----------*/

float mat1[4][4], mat2[4][4];

//Copying a maxtrix to another.
void MAT_Copy(float source[4][4], float dest[4][4])
{
    int i,j;

    i = 0;
    while (i < 4)
    {
        j = 0;
        while (j < 4)
        {
            dest[i][j]=source[i][j];
            j++;
        }
        i++;
    }
}

//Multiplying two matricies together.
void MAT_Mult(float matA[4][4], float matB[4][4], float dest[4][4])
{
    int i,j;

    i = 0;
    while (i < 4)
    {
        j = 0;
        while (j < 4)
        {
            dest[i][j] = matA[i][0] * matB[0][j] + matA[i][1] * matB[1][j] +
                matA[i][2] * matB[2][j] + matA[i][3] * matB[3][j];
            j++;
        }
        i++;
    }
}

// Multiplying vectors with a matrix???? still a bit confused on why & how.
void VEC_MultMatrix(_3D *Source, float mat[4][4], _3D *Dest)
{
    Dest->x = Source->x * mat[0][0] + Source->y * mat[1][0]
        + Source->z * mat[2][0] + mat[3][0];
    Dest->y = Source->x * mat[0][1] + Source->y * mat[1][1]
        + Source->z * mat[2][1] + mat[3][1];
    Dest->z = Source->x * mat[0][2] + Source->y * mat[1][2]
        + Source->z * mat[2][2] + mat[3][2];
}

/*---------- Transformations Matricies ----------*/

void MAT_Identity(float mat[4][4])
{
    //Identity matrix
    mat[0][0]=1; mat[0][1]=0; mat[0][2]=0; mat[0][3]=0;
    mat[1][0]=0; mat[1][1]=1; mat[1][2]=0; mat[1][3]=0;
    mat[2][0]=0; mat[2][1]=0; mat[2][2]=1; mat[2][3]=0;
    mat[3][0]=0; mat[3][1]=0; mat[3][2]=0; mat[3][3]=1;
}

//This is to translate a matrix base on the vector we use
void TR_Translate(float matrix[4][4], float tx, float ty, float tz)
{
   float tmat[4][4];

   //Translation matrix;
   tmat[0][0]=1;  tmat[0][1]=0;  tmat[0][2]=0;  tmat[0][3]=0;
   tmat[1][0]=0;  tmat[1][1]=1;  tmat[1][2]=0;  tmat[1][3]=0;
   tmat[2][0]=0;  tmat[2][1]=0;  tmat[2][2]=1;  tmat[2][3]=0;
   tmat[3][0]=tx; tmat[3][1]=ty; tmat[3][2]=tz; tmat[3][3]=1;
   //First we must copy the translation into mat1 so we dont destroy data
   MAT_Mult(matrix, tmat, mat1);
   //Then we copy back into matrix and return indirrectly
   MAT_Copy(mat1, matrix);
}

//this can make my matrix scale to any size i want
void TR_Scale(float matrix[4][4], float sx, float sy, float sz)
{
    float smat[4][4];

    //scalular matrix
    smat[0][0]=sx; smat[0][1]=0;  smat[0][2]=0;  smat[0][3]=0;
    smat[1][0]=0;  smat[1][1]=sy; smat[1][2]=0;  smat[1][3]=0;
    smat[2][0]=0;  smat[2][1]=0;  smat[2][2]=sz; smat[2][3]=0;
    smat[3][0]=0;  smat[3][1]=0;  smat[3][2]=0;  smat[3][3]=1;
    //First we must copy the scale into mat1 so we dont destroy data
    MAT_Mult(matrix, smat, mat1);
    //Then we copy back into matrix and return indirrectly
    MAT_Copy(mat1, matrix);
}

//this will rotate my matrix to any position i want
void TR_Rotate(float matrix[4][4], int ax, int ay, int az)
{
    float xmat[4][4], ymat[4][4], zmat[4][4];
    //x-axis rotation matrix
    xmat[0][0]=1;        xmat[0][1]=0;        xmat[0][2]=0;        xmat[0][3]=0;
    xmat[1][0]=0;        xmat[1][1]=cos(ax);  xmat[1][2]=sin(ax);  xmat[1][3]=0;
    xmat[2][0]=0;        xmat[2][1]=-sin(ax); xmat[2][2]=cos(ax);  xmat[2][3]=0;
    xmat[3][0]=0;        xmat[3][1]=0;        xmat[3][2]=0;        xmat[3][3]=1;

    //y-axis rotation matrix
    ymat[0][0]=cos(ay);  ymat[0][1]=0;        ymat[0][2]=-sin(ay); ymat[0][3]=0;
    ymat[1][0]=0;        ymat[1][1]=1;        ymat[1][2]=0;        ymat[1][3]=0;
    ymat[2][0]=sin(ay);  ymat[2][1]=0;        ymat[2][2]=cos(ay);  ymat[2][3]=0;
    ymat[3][0]=0;        ymat[3][1]=0;        ymat[3][2]=0;        ymat[3][3]=1;

    //z-axis rotation matrix
    zmat[0][0]=cos(az);  zmat[0][1]=sin(az);  zmat[0][2]=0;        zmat[0][3]=0;
    zmat[1][0]=-sin(az); zmat[1][1]=cos(az);  zmat[1][2]=0;        zmat[1][3]=0;
    zmat[2][0]=0;        zmat[2][1]=0;        zmat[2][2]=1;        zmat[2][3]=0;
    zmat[3][0]=0;        zmat[3][1]=0;        zmat[3][2]=0;        zmat[3][3]=1;

    //First we must rotate around the x-axis
    MAT_Mult(matrix, ymat, mat1);
    //Then we rotate around the y-axis
    MAT_Mult(mat1, xmat, mat2);
    //Finnaly, we rotate around the z-axis
    MAT_Mult(mat2, zmat, matrix);
    //We then return matrix indirrectly
}

/*---------- Creating Perspective ----------*/

//the view point for the window X & YOrigin is the origin point of the window... THE CENTER!!!
void Project(vertex_t *Vertex)
{
    if(!Vertex->Aligned.z)
        Vertex->Aligned.z = 1;
    //Projection formula
    Vertex->Screen.x = FOCAL_DISTANCE * Vertex->Aligned.x / Vertex->Aligned.z + XOrigin;
    Vertex->Screen.y = FOCAL_DISTANCE * Vertex->Aligned.y / Vertex->Aligned.z + YOrigin;
}
