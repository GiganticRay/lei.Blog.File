---
title: 关于A=QR defactorization的两种解释及代码实现
date: 2020-07-20 11:39:35
tags: Linear Algebra
categories: Linear Algebra
---
## 参考书目章节
1. Introduction to linear algebra: *P239*, The Factorization A = QR
2. Iterative Methods for Sparse Linear systems: *P11*, Gram-schmidt
## 一：Gram-Schmidt
> Interesting: gilbert strang said:"i don't know what schmidt did in this greatful process"
在很多工作中，我们需要用到一组向量空间的正交基来简化计算（如简化求解Ax=b的最小二乘解的过程）。Gram-Schmidt就是**正交化**一种经典方法，掌握了**投影**后，gram-schmidt就很好理解了。

> **prerequisite**: A的column space's projection matrix is ![A对应投影矩阵公式](https://raw.githubusercontent.com/GiganticRay/lei.Blog.File/master/Picture/A%3DQR/%E6%8A%95%E5%BD%B1%E7%9F%A9%E9%98%B5%E5%85%AC%E5%BC%8F.png "P = A(A^TA)^{-1}A^T")

> ### 1. 首先以二维为例
> `(x1, x2)`是线性无关的列向量，现需找出`orthonormal的(q1, q2)`来表示(x1,x2)的`列空间`。第一步:`q1=x1/norm2(x1)`。问题是如何依据x2找到q2使`<q1, q2> = 0`。 ![二维Gram_Schmidt](https://raw.githubusercontent.com/GiganticRay/lei.Blog.File/master/Picture/A%3DQR/Gram_Schmidt_Dim2.png "二维Gram_Schmidt")

>如图所示，`x2`在`q1`上的投影`p=<q1, x2>q1`，而我们需要的部分是`e(error) = x2-p`(# 注为啥叫error在投影那一章节有记录)。从而令`q2 = e/norm2(e)`。**用人话**来说就是，第n维的目标向量`(qn)`是第n维的已知向量`(xn)`依次减去其在`q1 -> qn-1`上的投影，最后单位化。

> ### 2. 三维图示
> ![三维Gram_Schmidt](https://raw.githubusercontent.com/GiganticRay/lei.Blog.File/master/Picture/A%3DQR/Gram_Schmidt_Dim3.png "三维Gram_Schmidt")

>由此可推到出Gram_Schmidt的公式：
> ![Gram_Schmidt公式](https://raw.githubusercontent.com/GiganticRay/lei.Blog.File/master/Picture/A%3DQR/Gram_Schmidt%E5%85%AC%E5%BC%8F.png "Gram_Schmidt公式")

> ### 3. Pseudo Code of Gram-Schmidt
> ![Gram_Schmidt_Algorithm](https://raw.githubusercontent.com/GiganticRay/lei.Blog.File/master/Picture/A%3DQR/Gram_Schmidt_Algorithm.png "Gram_Schmidt_Algorithm")

## 二：A=QR与Gram-Schmidt的关系
> 实际上这也是A=QR的第一种推理方式，即从`Gram-Schmidt`的推理过程得出`A=QR`。现假设我们已经通过Gram-Schmidt得到了前j个q`(q1,q2...qj)`，这样我们就可以得到![分解xj](https://raw.githubusercontent.com/GiganticRay/lei.Blog.File/master/Picture/A%3DQR/%E5%88%86%E8%A7%A3xj.png "分解xj"),即将`xj`分解至每一个正交基上。用矩阵的语言进行表达，即`X=QR`,`X=[x1, x2...,xr]`,`Q=[q1,q2,...,qr]`。如下图所示![A=QR矩阵表示](https://raw.githubusercontent.com/GiganticRay/lei.Blog.File/master/Picture/A%3DQR/A%3DQR%E7%9F%A9%E9%98%B5%E8%A1%A8%E7%A4%BA.png "A=QR矩阵表示")

## 三：从行列空间规律得出A=QR
> 这是`A=QR`的第二种推理方式，C(A)是`independent`的，在Gram-Schmidt中，我们的目的是找出`orthonormal的Q`，从目的而言，Q与A的列向量代表的向量空间肯定是一样的，即`C(A) = C(Q)`，根据线代的基础知识我们知道，肯定存在一个矩阵R，使得`A=QR`(A与Q的列向量空间相同)。若A is `Square`，那么`A and Q both are invertiable`。从而`R=Q^(-1)A`，又`Q is orthonormal`，so `Q^(-1) = Q^T`，so `R = Q^TA`，这样就求出了R，如下图所示。
> > ![A=QR矩阵表示方法二](https://raw.githubusercontent.com/GiganticRay/lei.Blog.File/master/Picture/A%3DQR/A%3DQR%E7%9F%A9%E9%98%B5%E8%A1%A8%E7%A4%BA%E6%96%B9%E6%B3%95%E4%BA%8C.png "A=QR矩阵表示方法二")

## 四：A=QR的应用
> gilbert Strang教授在书上说过：`"the matrix factorization is of most importance in linear algebra"`,`A=QR`作为一种矩阵分解，可以把线性独立的矩阵，分解成QR，Q是`orthonormal`,`R`又是`upper triangle`，特别是`orthonormal`给计算提供了很好的性质，目前接触到的就是在`least square solution`中的投影矩阵部分，`逆`的那一块直接为单位矩阵了，大大节约了计算时间成本。