#docker基本用法总结#

## 1、为方便远程管理，在容器中安装ssh ##

```Bash
    docker run -i -t ubuntu /bin/bash #此方式运行的容器，退出后容器就会关闭
    apt-get install openssh-server #安装ssh
    #需要修改/etc/sshd/sshd_config文件中内容  
    PermitRootLogin yes  
    UsePAM no 
```

1.启动ssh，让容器以后台方式运行：

```Bash
    docker run -d -p 50001:22 <容器id> /usr/sbin/sshd-D  
    #容器id可通过 docker ps-a查看，最上面的为最新的。 
```

2.通过ssh登录到容器：

```Bash

    ssh root@127.0.0.1-p 50001  
    #连上后想装什么就装什么，可使用exit退出容器，但后台还会运行。 
```

3.停止容器,把容器提交生成最新的镜像
```Bash

    docker stop <容器id> #停止运行的容器 
	docker commit -a "some author" -m "some message" Container-id LocalRepository-name 
```

4.打包镜像

```Bash

    docker save debian02 >/root/debian02.tar #debian02镜像打包 
	sudo cat ubuntu-14.04-x86_64-minimal.tar.gz | docker import - ubuntu[Repository]:14.04[TAG] #恢复镜像
```

5.在另外的机器上导入镜像

```Bash

    docker load < debian02.tar #导入镜像  
    docker images #查看存在的镜像 
```

docker容器迁移简单方便，可以任意的拷贝部署，以后再也不怕新部署环境了


6、关于docker容器的端口映射

由于docker容器的IP地址每次启动都会变，所以需要每次启动容器时由docker程序自动添

加NAT规则，前期尽可能的把需要映射的端口在创建容器时配置好，如下：

```Bash

    docker run -h="activemq" --name mydocker -d -p 51000:22 -p 
51001:3306-p 51003:6379 -p 51004:6381 -p 51005:80-p 51006:8000 -p 
51007:8888 debian/base/etc/rc.local  
    #此处我把mysql,redis,nginx,ssh都进行了映射。 
```
后续对于docker容器的管理，记住容器的名称，如上述名称是mydocker，则使用
docker stop,start来控制容器进程。

```Bash
    docker stop mydocker  
    docker start mydocker 
```

参考docker网络配置：http://www.open-open.com/lib/view/open1404896485747.html



## 2.安装ssh之后，我们就可以远程登录docker,以下是常用的docker命令 ##
### 1.docker run命令详解 ###
```Bash

    Usage: docker run [OPTIONS] IMAGE[:TAG] [COMMAND] [ARG...]  
    Run a command in a new container  
    -a=map[]: 附加标准输入、输出或者错误输出  
    -c=0: 共享CPU格式（相对重要）  
    -cidfile="": 将容器的ID标识写入文件  
    -d=false: 分离模式，在后台运行容器，并且打印出容器ID  
    -e=[]:设置环境变量  
    -h="": 容器的主机名称  
    -i=false: 保持输入流开放即使没有附加输入流  
    -privileged=false: 给容器扩展的权限  
    -m="": 内存限制 (格式:<number><optional unit>, unit单位 = b, k, m or g)  
    -n=true: 允许镜像使用网络  
    -p=[]: 匹配镜像内的网络端口号  
    -rm=false:当容器退出时自动删除容器 (不能跟 -d一起使用)  
    -t=false: 分配一个伪造的终端输入  
    -u="": 用户名或者ID  
    -dns=[]: 自定义容器的DNS服务器  
    -v=[]: 创建一个挂载绑定：[host-dir]:[container-dir]:[rw|ro].如果容器
	目录丢失，docker会创建一个新的卷  
    -volumes-from="": 挂载容器所有的卷  
    -entrypoint="": 覆盖镜像设置默认的入口点  
    -w="": 工作目录内的容器  
    -lxc-conf=[]: 添加自定义-lxc-conf="lxc.cgroup.cpuset.cpus = 0,1" 
    -sig-proxy=true: 代理接收所有进程信号(even in non-tty mode)  
    -expose=[]: 让你主机没有开放的端口  
    -link="": 连接到另一个容器(name:alias)  
    -name="": 分配容器的名称，如果没有指定就会随机生成一个  
    -P=false: Publish all exposed ports to thehost interfaces 公布所有显
	示的端口主机接口 
```
### 2.搜索和下载镜像 ###

```Bash

    docker pull <镜像名:tag> #从官网拉取镜像  
    docker search <镜像名> #搜索在线可用镜像名 
```

### 3.查询容器、镜像、日志 ###

```Bash

    docker top <container> #显示容器内运行的进程  
    docker images #查询所有的镜像，默认是最近创建的排在最上。  
    docker ps #查看正在运行的容器  
    docker ps -l #查看最后退出的容器的ID  
    docker ps -a #查看所有的容器，包括退出的。  
    docker logs {容器ID|容器名称} #查询某个容器的所有操作记录。  
    docker logs -f {容器ID|容器名称} #实时查看容易的操作记录。 
```

### 4.删除容器与镜像 ###


```Bash

    docker rm$(docker ps -a -q) #删除所有容器  
    docker rm <容器名or ID> #删除单个容器  
    docker rmi <ID> #删除单个镜像  
    docker rmi$(docker images | grep none | awk '{print $3}' | sort -r) #删除所有镜像 

```

### 5.启动停止容器 ###
```Bash
    docker stop <容器名or ID> #停止某个容器  
    docker start <容器名or ID> #启动某个容器  
    docker kill <容器名or ID> #杀掉某个容器 
```
### 6容器迁移 ###
```Bash
    docker export <CONTAINER ID> > /home/export.tar #导出  
    cat /home/export.tar | sudo docker import - busybox-1-export:latest 
	# 导入export.tar文件  
    docker save debian> /home/save.tar #将debian容器打包  
    docker load< /home/save.tar #在另一台服务器上加载打包文件 
```
save和export的对比参考地址：
http://www.fanli7.net/a/bianchengyuyan/C__/20140423/452256.html


### 7.docker Dockfile镜像制作 ###

```Bash
    FROM ubuntu/testa #这是基础镜像  
    CMD ["/root/start.sh"] #这是启动命令  
    docker build -t <新镜像名> ./ #build新的镜像 
```

参考：

http://www.tuicool.com/articles/FRvAbe

http://www.colorscode.net/2014/01/04/howto-build-image-with-automatic-startup-ssh-service-from-dockerfile/
