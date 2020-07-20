---
title: FirstHomeWork
date: 2020-07-14 19:42:06
tags: 并行计算
categories: 新竹清华大学作业
---

# 作业描述：新竹清华大学，周志远老师的并行计算课程，[作业一](http://lms.nthu.edu.tw/course.php?courseID=35305&f=hw&hw=168455)
1. 环境配置
> 在[slurm平台搭建成功](https://giganticray.github.io/2020/07/13/%E7%94%A8ubuntu%E6%90%AD%E5%BB%BAslurm%E5%B9%B3%E5%8F%B0/)的基础上，（使用```sinfo```查看，应该如下图所示），包含2台机器（虚拟机ubuntu16.04 64位），一台master, 既作为control节点，又作为computing节点，配置为2核cpu。一台slaver，只作为computing节点，配置为一核cpu。
![sinfo配置成功图片](https://github.com/GiganticRay/lei.Blog.File/blob/master/Picture/FirstHomeWork/slurm%E9%85%8D%E7%BD%AE%E6%88%90%E5%8A%9Fsinfo.jpg "sinfo配置成功图片")
2. 配置共享nfs文件服务器
> 这是根据报错来的，我在master节点独立目录下运行任务时报错如下图所示，显示在slaver节点上找不到这个目录，于是采用share memory的方式，根据[这篇nfs配置](https://www.tecmint.com/install-nfs-server-on-ubuntu/)对nfs进行配置。
![nfs未配置](https://github.com/GiganticRay/lei.Blog.File/blob/master/Picture/FirstHomeWork/slurm_srun_%E6%9C%AA%E9%85%8D%E7%BD%AEnfs.jpg "nfs未配置")
> 我的配置是将物理主机的```/mnt/nfs_share```作为共享目录，然后将虚拟机（master and slaver）的```/mnt/nfs_clientshare```作为挂载目录
```python
# 需要注意的一条命令，在nfs client上对nfs server上目录进行挂载
sudo mount 192.168.1.103:/mnt/nfs_share  /mnt/nfs_clientshare
# 注意，最后面没有 '/'，不然好像会挂在失败（未提示错误但是就是显示不出文件）
```
3. 修改slaver状态
> 我这默认salver's state=down, 需要手动设置其状态为idle，然后再使用```sinfo```查看节点状态
``` scontrol: update NodeName=slave1 State=down ```
4. hello.c进行测试
> 用master主机在共享目录下下载[测试文件](https://www.open-mpi.org/papers/workshop-2006/hello.c)，运行如下
```
# mpicc编译
mpicc hello.c -o hello
srun -n 3 hello
```
> 结果如下图所示，但是按道理来说应该是0 of 2, 1 of 2, 2 of 2啊，为啥是3个 0 of 1 呢，奇怪
![nfs配置成功后运行srun](https://github.com/GiganticRay/lei.Blog.File/blob/master/Picture/FirstHomeWork/slurm_srun_%E9%85%8D%E7%BD%AEnfs.jpg "成功配置nfs")
