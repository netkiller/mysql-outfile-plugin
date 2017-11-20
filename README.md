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

	create function out2file returns string soname 'liboutfile.so';

### Uninstall

	drop function out2file;

Testing
-------
### 创建管道	

	mysql> create function out2file returns string soname 'liboutfile.so';
	Query OK, 0 rows affected (0.00 sec)


	mysql> select out2file('/tmp/myoutfile',"Helloworld!!!");
	+--------------------------------------------+
	| out2file('/tmp/myoutfile',"Helloworld!!!") |
	+--------------------------------------------+
	| true                                       |
	+--------------------------------------------+
	1 row in set (0.00 sec)


	
	查看管道是否创建


	root@netkiller ~/mysql-outfile-plugin % cat /tmp/myoutfile
	Helloworld!!!
	

# Donations

We accept PayPal through:

https://www.paypal.me/netkiller

Wechat (微信) / Alipay (支付宝) 打赏:

http://www.netkiller.cn/home/donations.html

[![Bitdeli Badge](https://d2weczhvl823v0.cloudfront.net/netkiller/mysql-outfile-plugin/trend.png)](https://bitdeli.com/free "Bitdeli Badge")

