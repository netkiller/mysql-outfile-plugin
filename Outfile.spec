Name: mysql-outfile-plugin		
Version: 1.0
Release:	1%{?dist}
Summary: MySQL outfile plugin	

Group: MySQL Database server
License: CC 3.0
URL: http://www.netkiller.cn	
Source0: https://github.com/netkiller/mysql-outfile-plugin/archive/v1.0.tar.gz

BuildRequires: cmake3 mysql-community-devel	
Requires: gcc	

%description

This is function for MySQL Server.
You can query data and then save as a file as plain text.

%prep
%setup -q


%build
cmake3 .
make %{?_smp_mflags}


%install
make install DESTDIR=%{buildroot}


%files
/usr/lib64/mysql/plugin/liboutfile.so
%doc

Setup plugin

mysql> create function out2file returns string soname 'liboutfile.so';
Query OK, 0 rows affected (0.00 sec)

Example

mysql> select out2file('/tmp/myoutfile',"Helloworld!!!");
+--------------------------------------------+
| out2file('/tmp/myoutfile',"Helloworld!!!") |
+--------------------------------------------+
| true                                       |
+--------------------------------------------+
1 row in set (0.00 sec)

Show file

root@netkiller ~/mysql-outfile-plugin % cat /tmp/myoutfile
Helloworld!!!

%changelog

