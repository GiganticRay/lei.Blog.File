---
title: 用ubuntu搭建slurm平台
date: 2020-07-13 16:31:58
tags: 工具
categories: 工具
---
### 机器配置(注：我是基于[zxh](http://blog.zxh.site/)的博客，以及[官方文档](https://slurm.schedmd.com/quickstart_admin.html)针对ubuntu进行配置的)
> 两台ubuntu的虚拟机，一台作为master(2核心)，一台作为slave(1核心)
* 配置过程
0. 配置etc/hosts文件, 以及配置静态ip（默认是dhcp动态的，这样重启或者到了一个新的网络环境下局域网内部ip会自适应，这样每次都要调整很麻烦，所以此处设置为静态的）
> 注意修改master node的etc/hostname文件，最好保持与你的用户名一致，不然后续可能会出现"slurmctld: error: this host (xx) not valid controller (master or (null))"错误
> 设置静态ip的时候需注意网关的设置，一般是192.168.1.1（路由器的地址嘛，关于网关的知识可以自行了解一下）
1. 关闭防火墙（ubuntu's SELinux默认是关闭的）
```
ufw disable (注：ufw，即uncomplicated firewall)
```
2. 配置ntp **（network Time protocol）** 时间同步服务
> [ntp简介](https://linux.cn/article-8091-1.html)，使用**timedatectl**可以查看时间同步状态，默认我这里时ntp synchronized: yes已经开启的

3. 配置安装munge
> munge是为了授权才安装的，确保所有节点上的munge.key是相同的，并且在启动slurm之前要确保守护进程munged处于运行状态
```
sudo apt-get install munge
```
> 这里直接用apt安装，默认就配置好了munge的owner以及grouper，如果要手动配置的话要**注意**, munge daemon process的启用者要与munge' owner一致。
> 安装完毕后将host节点中/etc/munge/munge.txt拷贝到其他节点的/etc/munge里面去(首先都安装上ssh)
```python
# host machine
scp /etc/munge/munge.key slave1@192.168.1.105:/tmp # 将host machine节点上的munge.key复制到ip为192.168.1.105的slave1节点的tmp目录（这个目录有权限）
# 然后在slave节点上移动munge.txt到/etc/munge目录下，注意更改复制过来后key文件的owner与grouper为munge
sudo chown munge:munge munge.key

# Start the daemon automatically at boot:
sudo systemctl enable munge #(开机自启)
# Start the daemon now:
sudo systemctl start munge
# Stop the daemon:
sudo systemctl stop munge

ps -aux | grep munge查看
```
*** 注意：一定要在slurm daemon开启之前start munge daemon

4. 下载配置 slurm
> 4.1 ubuntu，现在[下载页面](https://slurm.schedmd.com/download.html)下载slurm源码，编译后根据[这篇博客](https://blog.csdn.net/datuqiqi/article/details/50827040)配置slurm.conf文件
```python
# 安装依赖
apt-get install hwloc libhwloc-dev libmunge-dev libmunge2 munge mariadb-server libmysqlclient-dev（slave节点不需要最后两个sql）
# 解压，在目录进行编译
./configure
sudo make
sudo make install
# 编译完成后进入 slurm-xxxx/etc
cp slurm.conf.example slurm.conf, 然后根据上述博客进行配置，配置完成后将slurm.conf拷贝到集群所有节点上面
scp slurm.conf slave1@192.168.1.105:/tmp
# 在slave1节点将slurm.conf文件拷贝进入安装目录
cp /tmp/slurm.conf /home/slave1/slurmxxxx/etc
```
4.2 此处根据[zxh](http://blog.zxh.site/2018/08/26/HPC-series-6-setup-slurm/)配置Maria DB以及配置slurm
```python
sudo apt-get install mariadb-servert
# 注意，在ubuntu下安装mariadb，但是操作的时候是操作的mysql
sudo systemctl start mysql
systemctl enable mysql
mysql_secure_installation
# 将配置好的slurm.conf copy至/usr/local/etc/中去
```

4.3
主节点运行:
```
slurmctld -c
slurmd -c
注意：-c时后台运行，在第一次运行时可以使用-D参数，显式运行以观察运行情况
```
slave节点运行：
```
slurmd -c
```

# False Log
+ 我在master运行sudo slurmctld -c启动时报错找不到/usr/local/etc/slurm.conf文件
> 将编译目录下/etc/slurm.conf复制进去即可
+ 使用sinfo时报错：slurm_load_partitions: unable to contact slurm controller (connect failure)
> 这个就是slurmctld没有正常启动...
+ "slurmd: fatal: mkdir(/var/spool/slurm/d): No such file or directory"
> 创建slurm中部分配置的目录，/var/spool/slurm/ctld 和 /var/spool/slurm/d
```python
# 注意更改spool以及其子目录文件的所有者及权限(如果需要的话)
mkdir -p /var/spool/slurm/ctld
mkdir -p /var/spool/slurm/d
```
+ master成功启动slurmctld 与 slurmd,但是从节点启动slurmd启动时报错：invalid user for slurmUser xxx, ignored（此时master与slave的slurm.conf完全一样）
> 更改salve节点/etc/slurm-llnl/slurm.conf文件的slurmUser的值为slave的用户即可

+ slave节点：slurmd:error:couldn't find the specified plugin name for select/cons_tres lokking at all files
> 这个我也找不到问题所在了，定位在 slave节点上的/usr/local/lib下面居然没有找到与slurm相关的文件!,奇了怪了，算了，现在已经凌晨了，其他centos配个环境怎么这么简单，一路都没有错误，ubuntu错误为什么这么多呢，这个问题也是连日志都没有，我把master上面的相关文件copy至slave节点还是没有，那我直接把slave节点删除了！就用一个master同时充当controller与computer算了。就这样，
> 第二天早上我tm发现，在salve节点上居然没有make install... 所以在```/usr/local/lib```中找不到相关文件...

# 安装经验总结
+ 安装整体来说还是挺容易的，碰到问题不要慌，仔细看错误提示，每个人碰到的问题都是不同的，可能是文件权限错误，也可能是缺少某些文件等等，加油!
# 参考博客
1.http://blog.zxh.site/2018/08/26/HPC-series-6-setup-slurm/
2.https://blog.csdn.net/qq_40474522/article/details/78898128
3.https://blog.csdn.net/datuqiqi/article/details/50827040
4.http://blog.zxh.site/2018/09/02/HPC-%E7%B3%BB%E5%88%97%E6%96%87%E7%AB%A0-7-Debian-Ubuntu%E5%AE%89%E8%A3%85Slurm/
5.https://blog.csdn.net/banana1006034246/article/details/99301649
