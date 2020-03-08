# 增加一个新材料

## UniaxialMaterial 基类提供了必要的方法，用来构建一个新材料的特征

### setTriaStrain()

#### **有限单元法中通常使用位移法，因其方便计算机批量处理**

1. 这是一个核心函数，当单元由高斯点获得位移时通过此函数计算应力和刚度信息
    1. getTangent() 获得刚度
    2. getStrees() 获得应力
2. 当迭代算法由上一步迭代进入下一步时，应用此方法，并由收敛准则判断是否能够收敛

### commitState()

1. 这个函数的目的在于在一个时步收敛后被调用，用于接下来替换初始状态，给下一时步提供初始条件
2. 如果下一时步出现问题不收敛，就提供回退到上一时步方法 **revertToLastCOmmit()**的初始值，用来更换迭代方法

### getCopy()

1. 被element的构造函数调用蚕声一个副本

### setResponse()/getResponse()

1. 一个响应函数,可能是利用**addToParameter**命令更新材料特性

### sendSelf()/recvSelf()

1. 利用数据库的并行处理方法

### OPS_Globals

1. 提供了错误函数判断和输出
2. 提供了堆内存池

### elementAPI

1. 提供了单元调用的API

### OPS_YOURMATERIALNAME()

#### **这个函数提供了关于输入的正确性检验**

1. 利用 OPS_GetNumRemainingInputArgs() 函数获得除去类型和名称之外所有参数的个数, 可以一句此函数进行输入的检验
2. OPS_GetIntInput(int *numData, int *data)()在 elementAPI_TCL定义, 获得输出的数字,可以检查标签的正确性
3. iData 存放标签的数组, 用于检验标签的唯一性
4. dData 存放参数的数组, 要吧所有可选参数全部计入, 防止溢出. dData 要初始化

## 文件构造顺序

### TclModelBuilderUniaxialMaterialCommand.cpp

#### 这是tcl控制函数

1. 不需要#include
2. 需要extern 函数
3. 写出判断依据

### FEM_ObjectBrokerAllClasses.cpp

#### 这个是关于MAT_TAG的函数

1. 提供#include
2. 提供case方法

### OpenSeesUniaxialMaterialCommands.cpp

#### 提供总体控制

1. extern 函数
2. uniaxialMaterialsMap.insert( std::make_pair("NAME", &OPS_NAME))

### makefile

#### 在 uniaxial 内添加.o文件

1. 顺序没有要求
2. 生成 .o 文件方便链接静态库

#### 在 SRC 的文件Material静态库添加 .o 文件

1. 否则 TclModelBuilderUniaxialMaterialCommand.cpp 文件无法链接成功

## 分析 Steel01 材料

### 控制参数 Steel01

1. 设定参数
    1. Energy:作用未知
    2. Fy: 屈服应力
    3. E0: 初始刚度
    4. b:硬化系数,屈服后刚度和初始刚度比值
    5. a: 各项同性硬化系数
        1. a1:当塑性应变为 a2 * (Fy / E0), 压缩屈服包络线随屈服强度增加的比例,默认为0
        2. a2: 控制 a1,默认55
        3. a3: 当塑性应变为 a4 * (Fy / E0), 拉伸屈服包络线随屈服强度增加的比例,默认0
        4. a4: 控制 a3默认55
2. Converged History Variables
    1. CminStrain: 最小的压缩应变,默认0
    2. CmaxStrain: 最大的拉伸应变,默认0
    3. CshiftP: 正向加载的滞回曲线改变量,目前未知与哪个因素有关,默认1
    4. CshiftN: 负向加载的滞回曲线改变量,目前未知与哪个因素有关,默认1
    5. Cloading: 加载卸载的标志,默认0
        1. 值为1时,有正向的应变增量
        2. 值为-1时,有负向的应变增量
        3. 值为0表示,初始状态
3. Converged State Variables
    1. Cstrain: 应变,默认0
    2. Cstress: 应力,默认0
    3. Ctangent: 刚度,默认E0
4. Trial History Variables
    1. TminStrain: 最小的压缩应变,默认0
    2. TmaxStrain: 最大的拉伸应变,默认0
    3. TshiftP: 正向加载的滞回曲线偏移量,目前未知与哪个因素有关,默认1
    4. TshiftN: 负向加载的滞回曲线偏移量,目前未知与哪个因素有关,默认1
    5. Tloading: 加载卸载的标志,默认0
        1. 值为1时,有正向的应变增量
        2. 值为-1时,有负向的应变增量
        3. 值为0表示,初始状态
5. Trial State Variables
    1. Tstrain: 应力,默认0
    2. Tstress: 应变,默认0
    3. Ttangent: 刚度,不是状态变量,默认E0

### 控制方法 Steel01

1. int setTrialStrain(double strain, double strainRate)

    **单元类调用此函数用于更新状态**

    **返回值是用来判断此函数是否正确结束**

    **第一个形参是得到的应变,第二个形参作用未知**

    1. 第一步先用历史数据初始化实验参数
    2. 第二步计算出应变增量,判断是否小于最小精度,如果大于最小精度,则直接把应变赋给 Tstrain并由应变增量计算应力应变状态

2. int setTrial(double strain, double &stress, double &tangent, double strainRate)

    **是上一个函数的四参数版本,具体作用不清楚**

3. void determineTrialState(double dStrain)

    **核心函数--由应变增量计算全部应力应变刚度状态**
    1. 屈服后的刚度 Esh
    2. 屈服前的最大应变 epsy
    3. 在同等屈服前最大应变下应力差 FyOneMinusB = Fy - epsy * Esh,用来平衡Esh从原点开始和从Fy开始
    4. c1 = Esh * Tstrain 屈服后的应力
    5. c2 = TshiftN * FyOneMinusB
    6. c3 = TshiftP * FyOneMinusB
    7. c = Cstress + E0*dStrain 按照未屈服应力考虑
    8. c1c2 当前按照以屈服考虑
    9. 更新全部数据

4. void detectLoadReversal(double dStrain)

    **决定此次加载是否为反向加载**
    1. 此方可能没有利用,在上一个方法中已经显现出来了

5. int commitState()

    **把当前状态记录**
    1. Enery 采用累加发法,做法是直接求面积

6. int revertToLastCommit()

    **返回上一个记录值**

7. int revertToStart()

    **回到初始状态**

## 分析 Steel02 材料

### 控制参数Steel01

1. EnergyP:能量
2. 输入参数
    1. Fy 屈服应力
    2. E0 初始刚度
    3. b 应变硬化比
    4. R0 cR1 cR2 控制弹性塑性变化的区域
    5. a1 a2 a3 a4 与 Steel01 一样
    6. sigini 初始应力
    7. eps 当前荷载步应变
