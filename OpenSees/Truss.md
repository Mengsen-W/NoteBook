# 学习 truss 单元

## 1. 先期准备
1. 包含头文件
```c++
#include <Element.h>  // 虚基类
#include <Matrix.h>   // 矩阵运算
```
2. 声明类
```c++
class Node;               // 节点类
class Channel;            // 维护实体
class UniaxialMaterial;   // 材料类
```

## 2. 成员变量
```c++
UniaxialMaterial *theMaterial;  // pointer to a material
ID  connectedExternalNodes;     // contains the tags of the end nodes
int dimension;                  // truss in 2 or 3d domain
int numDOF;	                    // number of dof for truss

Vector *theLoad;    // pointer to the load vector P
Matrix *theMatrix;  // pointer to objects matrix (a class wide Matrix)
Vector *theVector;  // pointer to objects vector (a class wide Vector)

double L;               // length of truss based on undeformed configuration
double A;               // area of truss
double rho;             // rho: mass density per unit length
int doRayleighDamping;  // flag to include Rayleigh damping
int cMass;              // consistent mass flag

double cosX[3];  // direction cosines

Node *theNodes[2];
double *initialDisp;

// AddingSensitivity:BEGIN //////////////////////////////////////////
int parameterID;
Vector *theLoadSens
// AddingSensitivity:END ///////////////////////////////////////////

// static data - single copy for all objects of the class
static Matrix trussM2;   // class wide matrix for 2*2
static Matrix trussM4;   // class wide matrix for 4*4
static Matrix trussM6;   // class wide matrix for 6*6
static Matrix trussM12;  // class wide matrix for 12*12
static Vector trussV2;   // class wide Vector for size 2
static Vector trussV4;   // class wide Vector for size 4
static Vector trussV6;   // class wide Vector for size 6
static Vector trussV12;  // class wide Vector for size 12
```

## 3. 成员函数