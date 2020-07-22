---
title: SVD A=UΣV^T to compress a Picture(奇异值分解)进行图片压缩
date: 2020-07-22 18:04:14
tags: Linear Algebra
categories: Linear Algebra
---

### 1. 奇异值分解：A=UΣV^T, 其中，U是AA^T的特征向量，Σ^2是AA^T的特征值，V是A^TA的特征向量，目的即将图片weights x heights分解为矩阵表达，这样存储时仅仅存储矩阵表达即可，从而达到压缩的效果。代码如下所示。
```python
import numpy as np
from PIL import Image


if __name__ == "__main__":
    # psuedo Code
    # 1. 加载图片成width x height的数组A
    # 2. 计算A^TA，算出其lambda^2, lambda是SIGMA, 对应特征向量是V1，V2；再根据(1):解AA^T的eigen vector作为U；（2）或者解AV/SIGMA得出U。
    # 3. 从大到小排列SIGMA以及对应U，V得出分解内容。
    # 4. 分析结论

    # 1. 得出矩阵A_TA
    Img = Image.open('./test.jpg')
    Img_array = np.array(Img)
    A = Img_array[:,:,0]
    A_T = A.transpose()
    A_TA = np.dot(A_T, A)

    # 2. 计算出对应特征值及对应特征向量，并排好序（in order of importance）
    eigenvalues,eigenVectors = np.linalg.eig(A_TA)
    tmp = np.column_stack((eigenvalues, eigenVectors))
    tmp = tmp[np.argsort(-(tmp[:,0]))]
    singularValues, singularVectorsV = np.nan_to_num(np.power(tmp[:, 0], 0.5)), tmp[:, 1:]

    # 用AV/SIGMA = U 计算U
    singularVectorsU = np.dot(A, singularVectorsV)/singularValues

    # 设置阈值为99%
    threshold = 0.99
    SigmaSum = np.sum(singularValues)
    tmp = singularValues[0]
    i = 1
    while(tmp/SigmaSum <= threshold):
        tmp += singularValues[i]
        i += 1

    reConstructImgArray = np.dot(
        np.dot(singularVectorsU[:, 0:i+1], np.diag(singularValues[0:i+1])), 
        np.transpose(singularVectorsV[:, 0:i+1]))

    reConstructImg = Image.fromarray(reConstructImgArray)
    reConstructImg.show()
    # 结果为i=44, 即压缩为了1257*(1980+2640), 原图是1980*2640, 这样压缩保留了99%的信息
    print("good luck")

```
### 2. 左为重构，右为原图
![SVD_Sample_Pic](https://raw.githubusercontent.com/GiganticRay/lei.Blog.File/master/Picture/SVD/SVD%E4%BB%A3%E7%A0%81%E6%95%88%E6%9E%9C%E7%A4%BA%E4%BE%8B%E5%9B%BE.jpg "SVD_Sample_Pic")

### 3. 结果说明
> 原图大小是 1980*2640*3(带color channel)，现经过SVD压缩为了(1257*(1980+2640)*3)`(代码中为了简单表明过程，只计算了一个color channel上的)`。上述例子表明，在保存图片信息99%的情况下，压缩率为90%。
---
