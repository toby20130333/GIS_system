
GIS_system
==========
这2个项目是关于GIS的简单的项目
GPS_sql项目主要介绍
数据库的设计
        根据shapefile文件格式读取的结果，进行数据库的设计，共设计了四个表，分别是Building表、Road表、Point表、Line表
hapefile文件的读取
shapefile文件格式
shape文件包含了.shp (主文件)、shx (索引文件)以及dBASE表三个文件。主要读取.shp (主文件)和dBASE表。
.shp主文件是直接存取的、变长度的记录的文件，其中的每个记录主要描述的是构成地理特征的所有的vertices坐标。
dBASE 表则包了SHP文件中的每一个地理特征的特征属性。
了解了shapefile文件格式，对shapefile文件的读取就特别的容易
GLWidget项目：
地图显示
地图的显示是通过对数据库中的数据操作，编写opengl代码实现的，地图的显示主要包括地图的放大、地图的缩小、地图的平移和地图的旋转三项基本功能。
1、地图的缩放
2、地图的平移
3、地图的旋转
等
具体参考项目代码
PS:此项目只能用于学习，切勿商用，如有违权，后果自负