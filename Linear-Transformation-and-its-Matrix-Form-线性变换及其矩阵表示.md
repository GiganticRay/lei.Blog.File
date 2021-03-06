---
title: Linear Transformation and its Matrix Form(线性变换及其矩阵表示)
date: 2020-07-27 18:51:03
tags: Linear Algebra
categories: Linear Algebra
---

参考书：[Introduction to Linear Algebra]

# 概念汇总
> 这一节内容真实非常奇妙啊，简直是线代精华，用线代可以描述世间万物。`空间、基、坐标表示、线性变换`这四个术语息息相关，这里来阐述其关系。

+ 空间
> 这个很好理解，从小我们就知道：点，线，面，体。这就对应着`0维、1维、2维、3维`空间，我们所处的就是三维空间。*（PS:三体中的二向箔，莫非就是说明了宇宙是数字化出来的，歌者实则为编程人员，其甩出的二向箔，就是对宇宙(矩阵表示)的一部分进行了三维到二维的一个线性变化: linear transformation? interesting...）*

+ 基
> 既然我们有了空间的概念，那么我们如何表示这个空间呢？`基(basis)`就此出现了，可以理解为：*空间的基础*，即空间的任何一个位置，我们都可以用`基的线性组合`来表示。比如在我们三维空间里面，一个`standard basis`就是`b1(1,0,0) b2(0,1,0) b3(0,0,1)`,任何一个位置`v`我们都可以用`v = α*b1 + β*b2 + Γ*b3`来表示。**需要注意的是，我们对基的选择是非常自由的，如我们将列向量作为基写成矩阵A<sub>NxN</sub>，R(A)=N，那么这些列向量就可以作为这个N维空间的基。**

+ 坐标表示
> 我们平时所画的那个三维坐标轴x,y,z笛卡尔坐标系。常用3个数字来表述一个位置，如`p1=(12,34,56)`。这实则用完整的语言表述是：**p1点，在基`b1(1,0,0) b2(0,1,0) b3(0,0,1)`所表示的三维空间下的坐标为(12,34,56)**，用矩阵的表述语言如![坐标与基][1]。**同一空间下相同的点，在不同的基下其坐标表示会不一样。**

+ 线性变换 (Linear Transformation)
> 线性变换的定义就不再赘述了，[1]中`P405`提出：**任何从V=R<sup>n</sup>到W=R<sup>m</sup>的线性变换，都对应着其矩阵表达。**(V是n维输入空间，W是m维输出空间。)

> 思考问题：
> 从V=R<sup>n</sup>到W=R<sup>m</sup>的线性变换的矩阵表达A**是唯一的吗？**

> answer: **不是唯一的，变换肯定是在空间中进行的，而无关于基的选择。基的选择会确定该变换矩阵表达A。**

> 解释：我们用顺时针旋转90度来举例子，V=R<sup>2</sup>到W=R<sup>2</sup>，那么，不管我们怎么选择V=(v1,v2)与W=(w1,w2)，顺时针旋转90<sup>。</sup>始终表示顺时针旋转<sup>。</sup>。只是我们对基的选择，会决定该变换的矩阵表达A。
> ![决定变换矩阵A的三要素][2]

+ 基变换矩阵
> 这个其实相当于特殊的线性变换，即**Basis<sub>in</sub> -> Basis<sub>out</sub>的identitic transformation**。说人话就是，我们只变换一下空间的基的表示而已。我们以[1]中**p412**举例。
> ![basisTransformation1][3]
> ![basisTransformation2][4]
> ![basisTransformation3][5]

+ 如何选择**好的基**，使得该变换T在这组input basis与output basis下的矩阵表示比较简单？
> 待续...




[1]: https://raw.githubusercontent.com/GiganticRay/lei.Blog.File/master/Picture/Linear_Transformation/%E5%9D%90%E6%A0%87%E4%B8%8E%E5%9F%BA.png "坐标与基"
[2]: https://raw.githubusercontent.com/GiganticRay/lei.Blog.File/master/Picture/Linear_Transformation/%E5%86%B3%E5%AE%9A%E5%8F%98%E6%8D%A2%E7%9F%A9%E9%98%B5A%E7%9A%84%E4%B8%89%E8%A6%81%E7%B4%A0.png "决定变换矩阵A的三要素"
[3]: https://raw.githubusercontent.com/GiganticRay/lei.Blog.File/master/Picture/Linear_Transformation/basisTransformation1.png "basisTransformation1"
[4]: https://raw.githubusercontent.com/GiganticRay/lei.Blog.File/master/Picture/Linear_Transformation/basisTransformation2.png "basisTransformation2"
[5]: https://raw.githubusercontent.com/GiganticRay/lei.Blog.File/master/Picture/Linear_Transformation/basisTransformation3.png "basisTransformation3"
