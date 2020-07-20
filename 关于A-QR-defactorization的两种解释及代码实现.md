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
**prerequisite**: A的column space's projection matrix is $P = A((A^T)A)^(-1))A^T$
## 二：A=QR与Gram-Schmidt的关系
> 实际上这也是A=QR的第一种推理方式，即从Gram-Schmidt的推理过程得出A=QR
