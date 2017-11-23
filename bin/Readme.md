# Setup RPM

rpm -ivh mysql-outfile-plugin-1.0-1.el7.centos.x86_64.rpm

# Setup plugin

```
mysql> create function out2file returns string soname 'liboutfile.so';
Query OK, 0 rows affected (0.00 sec)
```

# Example

```
mysql> select out2file('/tmp/myoutfile',"Helloworld!!!");
+--------------------------------------------+
| out2file('/tmp/myoutfile',"Helloworld!!!") |
+--------------------------------------------+
| true                                       |
+--------------------------------------------+
1 row in set (0.00 sec)
```

# Show file

```
root@netkiller ~/mysql-outfile-plugin % cat /tmp/myoutfile
Helloworld!!!
```

# Demo 

```

DROP TRIGGER IF EXISTS `test`.`demo_AFTER_INSERT`;

DELIMITER $$
USE `test`$$
CREATE DEFINER=`root`@`%` TRIGGER `test`.`demo_AFTER_INSERT` AFTER INSERT ON `demo` FOR EACH ROW
BEGIN
	set @rev = "";
	SELECT 
    OUT2FILE('/tmp/demo.log',
            CONCAT_WS(',',
                    NEW.id,
                    NEW.name,
                    NEW.sex,
                    NEW.address))
	INTO @rev;
END$$
DELIMITER ;		

```
