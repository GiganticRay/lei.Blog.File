---
title: A=QR_HouseHolder_Defactorization
date: 2020-08-07 17:24:17
tags: Linear Algebra
categories: Linear Algebra
---

> 参考章节目录

> 1. Iteriative Methods for Sparse Linear Systems P12
> 2. MATH 5330: Computational Methods of Linear Algebra--Lecture Note 10: Householder Transformation--Xianyi Zeng--Department of Mathematical Sciences, UTEP

## Abstract
> 关于A=QR的分解，有三种方法：**[Gram、Givens](https://giganticray.github.io/2020/07/20/%E5%85%B3%E4%BA%8EA-QR-defactorization%E7%9A%84%E4%B8%A4%E7%A7%8D%E8%A7%A3%E9%87%8A%E5%8F%8A%E4%BB%A3%E7%A0%81%E5%AE%9E%E7%8E%B0/)、Householder**，Givens我不熟悉、但好像和旋转有关、可以保留A's columns的长度。HouseHolder也有这个优点。

## 大致了解
> Gram-Schmidt的方法是通过一步一步地将新的列A<sub>j</sub>，减去其在已正交化的q<sub>1</sub>，q<sub>2</sub>，q<sub>(j-1)</sub>的投影从而得到新的正交项以此构成Q，**HouseHolder**采取了另外一种完全的方法，其一步一步地将待分解矩阵A，分解成**Echelon matrix**，当然这个分解过程不是简单的**Gaussian Decomposition**，而是用了**HouseHolder算子**，下面翻译一下参考书目1中的分解步骤

## 什么是Householder算子（Householder矩阵的几何表示）
> Householder算子是一个矩阵，其形式是**P = I - 2ww<sup>T</sup>**，这里我一般记作**P<sub>w</sub>**，因为P是由w决定的，后续我们也是针对待分解矩阵的每一列来构造对应的w，从而得出针对每一列的P。
> 
> 易证，`P是Ortogonal矩阵、且是Symmetric矩阵`：**P<sup>T</sup>=P，P<sup>T</sup>P=I**。

> 注意，我们后续在选择w的时候，要让其是2-norm unity的向量。

> 从几何上来看，Px表示的就是x,关于空间{w}<sup>⊥</sup>的镜像。画图表示就是
![HouseholderMatrix的几何表示][1]

> v就是上文中的w、H<sub>v</sub>就是上文中的P<sub>w</sub>。

## 如何为每一列X<sub>j</sub>构造每一个HouseHolder矩阵P<sub>j</sub>
+ 针对向量x、构造其P<sub>w</sub>
> 一直在强调，HouseHolder矩阵P<sub>j</sub>的作用就相当于Gaussian Elimination的消除矩阵（应该这么叫吧）。下面以第一列为例，假设第一列是x，那么目的肯定是
![1.15.1][2]
> α是一个张量，后面我们会知道其实就是x的长度。现在将P的表达式代入:
![1.16][3]
![推导1][4]
![推导2][5]

> **至此、我们就用通过x、求得了一个w，使得x在P<sub>w</sub>的作用下可以变换至||x||e<sub>1</sub>**，w的表达式如下
![w1_Expression][6]

+ 针对矩阵的每一列，进行构造P
> 先看矩阵的第一列x<sub>1</sub>，我们直接用x<sub>1</sub>替换掉`1.17`中的x，即得出w<sub>1</sub>，从而得出P<sub>1</sub>。记X<sub>1</sub>是第一次HouseHolder变换后的矩阵（形如已经完成一次Gaussian Elimination的矩阵）
![X1][7]
> X<sub>1</sub>的第一个元素为α，其余元素为0。

> 现在我们看一下第`k`次HouseHolder变换的情况，操作对象当然是已经完成`k-1`次的矩阵了鸭。表达式如下：
![Xk][8]

> 矩阵在列k-1前是一个上三角矩阵。进行下一步时，`前k-1列`保持不变，根据第`k`列的向量**x<sub>k</sub>**，确定一个w，然后生成P。w的形状是`1至k-1`个元素都是0，这样才保证了前k-1列不变。P<sub>k</sub>的推导如下
![Pk][9]

> 当k=0时，即第一次变换的P，此时的**β=αe<sub>1</sub>**，符合上文的描述。

## 构造A=QR
> 到这里，我们就描述完了整个X的分解过程，使得x可以分解成
![1.22][10]
> 这里仅需要一小步、就可以将上式变成A=QR的美丽式子了鸭。(下面这个过程，即将R那部分中的0，转移到P中去，形成Q).我们将`1.22`表示成下面的式子`1.23`，R是`mxm`的矩阵。
![1.23][11]

> 我们在前面给出了P<sub>i</sub>是`对称、且正交`的，所以我们把P放到右边:
![1.23.1][12]

> 我们用**E<sub>m</sub>**表示I的前m列，shape=(n,m)。可表示如下
![1.23.2][13]

> 令Q=P<sup>T</sup>E<sub>m</sub>，这表示取P<sup>T</sup>的前m列。我们可以验证：
![1.23.3][14]

> 所以，Q是我们想要的Q(Orthonomal)。分解成功！



[1]: http "HouseholderMatrix的几何表示"
[2]: http "1.15.1"
[3]: http "1.16"
[4]: http "推导1"
[5]: http "推导2"
[6]: http "w1_Expression"
[7]: http "X1"
[8]: http "Xk"
[9]: http "Pk"
[10]: http "1.22"
[11]: http "1.23"
[12]: http "1.23.1"
[13]: http "1.23.2"
[14]: http "1.23.3"