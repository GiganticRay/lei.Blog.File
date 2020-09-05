---
title: Finite Difference Methods(有限差分方法)
date: 2020-08-21 15:11:33
tags: Linear Algebra
categories: Linear Algebra
---

> 最近半月都在练习驾照、Iterative methods也间断地看完了第一章（期间配合着Gilbert的Linear圣经夯实了线代的基础）。今天学习Discretization of PDES。

> 参考书籍：Iterative methods for sparse linear system

## 一：初识
> 本章大致是在讲对偏微分方程进行离散化求近似解(当然，精确解我们能够用数值计算方法计算得出)。离散化的意思是用`Taylor series expansion`，将一个方程用幂函数之和来表示。关于Taylor series的解释，[这个知乎问题](https://www.zhihu.com/question/25627482)下的高赞回答简直是经典！`section 2.1`介绍了两个经典的微分方程：椭圆操作器的`Poisson方程`、`Convection Diffusion equation（对流扩散方程）`。然后2.2开始介绍`有限差分法`，根据[维基百科](https://zh.wikipedia.org/wiki/%E6%9C%89%E9%99%90%E5%B7%AE%E5%88%86%E6%B3%95)的定义，有限差分法即通过有限差分来近似导数、，从而求微分方程的近似解。


## 二：搁置
在阅读的过程中发现对新的数学基础有要求、先修一下ma691课程。