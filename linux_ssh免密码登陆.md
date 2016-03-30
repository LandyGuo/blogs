# ssh免密码登陆 #

1）ubuntu为当前用户产生ssh非对称秘钥的方法:

```Bash
ssh-keygen -t rsa//-t 指定rsa加密算法
```

产生一对秘钥：

```Bash
id_rsa id_rsa.pub
```

其中id_rsa为私钥，id_rsa.pub为公钥


2) ubuntu中免密码登陆的重要文件：authorized_keys

如果一台服务器中的authorized_keys中有这把公钥，那么当其他的机器用ssh连接这台机器时都会拿着自己的公钥作为凭证，这时服务器查询authoried_keys的文件中有公钥，那么久允许它免密码登陆
将这台机器的公钥加入到已授权的公钥中，当前用户就可以免密码登陆本机

```Bash
id_rsa.pub>>authoried_keys
```
