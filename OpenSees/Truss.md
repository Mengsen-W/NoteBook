# 学习单元构建

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
3. Element 虚函数
```c++
// methods dealing with nodes and number of external dof
virtual int getNumExternalNodes(void) const =0;
virtual const ID &getExternalNodes(void)  =0;
virtual Node **getNodePtrs(void)  =0;
virtual int getNumDOF(void) =0;
virtual double getCharacteristicLength(void);

// methods dealing with committed state and update
virtual int commitState(void);
virtual int revertToLastCommit(void) = 0;
virtual int revertToStart(void);
virtual int update(void);
virtual bool isSubdomain(void);

// methods to return the current linearized stiffness,
// damping and mass matrices
virtual const Matrix &getTangentStiff(void) =0;
virtual const Matrix &getInitialStiff(void) =0;
virtual const Matrix &getDamp(void);
virtual const Matrix &getMass(void);
virtual const Matrix &getGeometricTangentStiff();

// methods for applying loads
virtual void zeroLoad(void);
virtual int addLoad(ElementalLoad *theLoad, double loadFactor);
virtual int addLoad(ElementalLoad *theLoad, const Vector &loadFactors);

virtual int addInertiaLoadToUnbalance(const Vector &accel);
virtual int setRayleighDampingFactors(double alphaM, double betaK, double betaK0, double betaKc);

// methods for obtaining resisting force (force includes elemental loads)
virtual const Vector &getResistingForce(void) =0;
virtual const Vector &getResistingForceIncInertia(void);

// method for obtaining information specific to an element
virtual Response *setResponse(const char **argv, int argc, 
                              OPS_Stream &theHandler);
virtual int getResponse(int responseID, Information &eleInformation);
virtual int getResponseSensitivity(int responseID, int gradIndex,
                                   Information &eleInformation);

virtual int displaySelf(Renderer &, int mode, float fact, const char **displayModes=0, int numModes=0);

// AddingSensitivity:BEGIN //////////////////////////////////////////
virtual int addInertiaLoadSensitivityToUnbalance(const Vector &accel, bool tag);
virtual const Vector & getResistingForceSensitivity(int gradIndex);
virtual const Matrix & getTangentStiffSensitivity(int gradIndex);
virtual const Matrix & getInitialStiffSensitivity(int gradIndex);
virtual const Matrix & getCommittedStiffSensitivity(int gradIndex);
virtual const Matrix & getDampSensitivity(int gradIndex);
virtual const Matrix & getMassSensitivity(int gradIndex);
virtual int   commitSensitivity(int gradIndex, int numGrads);
// AddingSensitivity:END ///////////////////////////////////////////

virtual int addResistingForceToNodalReaction(int flag);

virtual int storePreviousK(int numK);
virtual const Matrix *getPreviousK(int num);

const Vector &getRayleighDampingForces(void);
double alphaM, betaK, betaK0, betaKc;

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

Node *theNodes[2];    // Node id
double *initialDisp;  // initial displacement

// AddingSensitivity:BEGIN
int parameterID;
Vector *theLoadSens
// AddingSensitivity:END

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
```c++
OPS_Export void *
OPS_TrussElement(); // 用于TCL调用

#include ".../TclElementCommands.cpp"
#include ".../OpenSeesElementComands.cpp"
#include "OpenSeesPy/.../TclElementCommands.cpp"
#include "OpenSeesPy/.../OpenSeesElementComands.cpp"
```

1. 存储数据结构
```c++
data(0) = getTag (Element Tag)
data(1) = dimension
data(2) = numDOF
data(3) = A
data(4) = MaterialTag
date(5) = MaterialDbTag
data(6) = rho
data(7) = doRayleighDamping
data(8) = cMass
date(9 ~ ...) = displacement
```
```c++
data(0) = this->getTag();
data(1) = numDIM;
data(2) = numDOF;
data(3) = numDIR;
data(4) = x.Size();
data(5) = y.Size();
data(6) = Mratio.Size();
data(7) = shearDistI.Size();
data(8) = addRayleigh;
data(9) = mass;
data(10) = alphaM;
data(11) = betaK;
data(12) = betaK0;
data(13) = betaKc;
```
