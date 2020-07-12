---
title: git的核心理念与基本操作(基本)
date: 2020-07-12 07:11:18
tags:
---

* ### git上文件的状态
> 这很重要，要求git使用者必须知道你local repository中文件的状态，可以通过**git status**命令查看。其中，可以从两方面来看到文件状态
### 1. 从git的角度来考虑
> 从git角度考量文件，只有两种状态：**untracked与tracked**，untracked可以理解为git没有存放该文件的信息，一般是新建文件后文件的状态。tracked是git已经知道了文件的信息了。
### 2. 从文件本身角度来考虑
> 从文件本身来说其有**unmodified、modified、staged**三种状态，意思顾名思义即可，知道了文件当前的状态，使用git命令对其进行状态进行修改，从而达到操控local repository的目的。
### 3. 问题探讨（将文件从**staging area**中移除，但是仍让其保存在**working tree**中）
> 应用场景：这通常是在项目开发中。随项目产生的那些.o文件等等不需要存在repositiry中，但是要在本地端存在
```
$ git rm --cached README
```
>解决办法即添加参数 --cached
### 4. 镜像问题探讨（如何让文件只在于repository中而不存在于本地local working tree中，以免浪费本地资源）
> 应用场景：相当于作为图片服务器
> 解决办法：目前好没有看到，之后再看吧。
