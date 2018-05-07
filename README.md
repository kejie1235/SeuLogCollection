# SeuLogCollection
东大项目实训多源日志采集系统

该项目基于C/S模式 
Server端是使用Boost.Asio IO库搭建的一个日志服务器，主要可以采集局域网中的网络设备日志信息，比如Tomcat服务器，防火墙，vpn等一系列网络设备信息。
并且将数据导入Mysql数据当中。
Client端使用MFC的图形界面库，与server通信展示和筛选需要查看的网络日志设备信息。
