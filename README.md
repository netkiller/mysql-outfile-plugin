mysql-outfile-plugin
=================

MySQL Outfile Plugin

Build
-----
	cd /usr/local/src/
	git clone https://github.com/netkiller/mysql-outfile-plugin.git
	cd mysql-outfile-plugin/

	yum install -y cmake3
	
	cmake3 .
	make
	make install

	or
	
	gcc -O3  -g  -I/usr/include/mysql -I/usr/include  -fPIC -lm -lz -shared -o liboutfile.so outfile.c
	sudo mv liboutfile.so /usr/lib/mysql/plugin/
	
Plugin Install and Uninstall
--------------

### Install

	create function outfile_create returns string soname 'liboutfile.so';
	create function outfile_remove returns string soname 'liboutfile.so';
	create function outfile_read returns string soname 'liboutfile.so';
	create function outfile_write returns string soname 'liboutfile.so';

### Uninstall

	drop function outfile_create;
	drop function outfile_remove;
	drop function outfile_read;
	drop function outfile_write;

Testing
-------
### 创建管道	
	mysql> create function outfile_create returns string soname 'liboutfile.so';
	Query OK, 0 rows affected (0.02 sec)

	mysql> select outfile_create('/tmp/myoutfile');
	+----------------------------+
	| outfile_create('/tmp/myoutfile') |
	+----------------------------+
	| ture                       |
	+----------------------------+
	1 row in set (0.00 sec)
	
	查看管道是否创建
	
	$ ls /tmp/myoutfile 
	/tmp/myoutfile
	
	覆盖测试，正确应该返回false
	
	mysql> select outfile_create('/tmp/myoutfile');
	+----------------------------+
	| outfile_create('/tmp/myoutfile') |
	+----------------------------+
	| false                      |
	+----------------------------+
	1 row in set (0.00 sec)

### 删除管道	
	mysql> select outfile_remove('/tmp/myoutfile');
	+----------------------------+
	| outfile_remove('/tmp/myoutfile') |
	+----------------------------+
	| true                       |
	+----------------------------+
	1 row in set (0.00 sec)
	
	mysql> select outfile_remove('/tmp/my');
	+------------------------+
	| outfile_remove('/tmp/my') |
	+------------------------+
	| false                  |
	+------------------------+
	1 row in set (0.00 sec)

	删除不存在的管道会提示 false

### 读管道

	在一个终端窗口中运行
	mysql> select outfile_read('/tmp/myoutfile');
	+--------------------------+
	| outfile_read('/tmp/myoutfile') |
	+--------------------------+
	| Hello world              |
	+--------------------------+
	1 row in set (7.85 sec)

	在另一个终端窗口中运行
	mysql> select outfile_write('/tmp/myoutfile','Hello world !!!');
	+---------------------------------------------+
	| outfile_write('/tmp/myoutfile','Hello world !!!') |
	+---------------------------------------------+
	| true                                        |
	+---------------------------------------------+
	1 row in set (0.00 sec)	
	
	或者
	
	在命令行运行
	$ echo "Hello world" > /tmp/myoutfile
	
	在SQL客户端中运行
	mysql> select outfile_read('/tmp/myoutfile');
	+--------------------------+
	| outfile_read('/tmp/myoutfile') |
	+--------------------------+
	| Hello world
				 |
	+--------------------------+
	1 row in set (0.00 sec)
	注意上面echo会自动增加换行符，-n参数可以避免
	$ echo -n "Hello world" > /tmp/myoutfile
	
	mysql> select outfile_read('/tmp/myoutfile');
	+--------------------------+
	| outfile_read('/tmp/myoutfile') |
	+--------------------------+
	| Hello world              |
	+--------------------------+
	1 row in set (0.01 sec)
	
### 写管道
	mysql> select outfile_write('/tmp/myoutfile','Hello world !!!');
	+---------------------------------------------+
	| outfile_write('/tmp/myoutfile','Hello world !!!') |
	+---------------------------------------------+
	| true                                        |
	+---------------------------------------------+
	1 row in set (0.00 sec)
	
	$ cat /tmp/myoutfile
	Hello world !!!
	
	管道 /tmp/nooutfile 不存在会返回false
	mysql> select outfile_write('/tmp/nooutfile',concat(mobile,'\r\n')) from demo;
	+-------------------------------------------------+
	| outfile_write('/tmp/nooutfile',concat(mobile,'\r\n')) |
	+-------------------------------------------------+
	| false                                           |
	| false                                           |
	| false                                           |
	| false                                           |
	| false                                           |
	+-------------------------------------------------+
	5 rows in set (0.01 sec)	

# Donations

We accept PayPal through:

https://www.paypal.me/netkiller

Wechat (微信) / Alipay (支付宝) 打赏:

http://www.netkiller.cn/home/donations.html

[![Bitdeli Badge](https://d2weczhvl823v0.cloudfront.net/netkiller/mysql-outfile-plugin/trend.png)](https://bitdeli.com/free "Bitdeli Badge")

