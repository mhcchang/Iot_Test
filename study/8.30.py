#coding:utf-8
'''
author:
function:
param:
other
'''
'''
1、python学习
	ORM:ORM 相当于把数据库也给你实例化了。
	ORM框架中有：sqlalchemy:https://blog.csdn.net/fgf00/article/details/52949973
	架构调用：
		python-------sqlalchemy------pymysql----mysql---database---table
	安装：
		pip3 install sqlalchemy
		pip3 install pymysql
	Dialect用于和数据API交流，根据配置文件的不同调用不同的数据库API,调用的url
		MySQL-Python
			mysql+mysqldb://<user>:<password>@<host>[:<port>]/<dbname>
		pymysql
			mysql+pymysql://<username>:<password>@<host>/<dbname>[?<options>]
		MySQL-Connector
			mysql+mysqlconnector://<user>:<password>@<host>[:<port>]/<dbname>
		cx_Oracle
			oracle+cx_oracle://user:pass@host:port/dbname[?key=value&key=value...]
	拓展：
	    1、类型对象的实例属性由两部分组成：1、type类的实例属性，如值恒为<class 'type'>的__class__属性；2、用户定义类时提供的类属性
        2、type()函数可以查看一个类型或变量的类型，Hello是一个class，它的类型就是type，而h是一个实例，它的类型就是class Hello。
        3、type可以自动创建类：H = type('H',(object,),dict(h=fn))

        自我理解：
            type类型中包括class类型，class是type对象的的一种类型
            那type是个啥？type是个类，因此也是type自己这个类的实例。这是个Metaclass。
            类就是个type。你可以试试任何你知道是class的东西（包括你自己的自定义类）。在Python这个一切皆对象的语言里，类型的类型是什么？是type。
    metaclass:
                metaclass允许你创建类或者修改类,如果类中加了metaclass参数，则先执行metaclass中的类
    self.__class__:返回实例化
                self.__class__.__name__返回类名
2、shell
    说明:主要执行之前写的性能测试脚本
        #写一个 bash脚本以统计一个文本文件 nowcoder.txt中字母数小于8的单词
        read line < nowcoder.txt
        for n in $line
        do
        if [ "${#n}" -lt 8 ] 
        then
            echo "${n}"
        fi
        done
        
        
        exit 0
        cat nowcoder.txt | awk '{
        for (i=1;i<=NF;i++){
                if (length($i) < 8)
                        print $i
        }
        }'
        
        
        
        exit 0
        #写一个 bash脚本以去掉一个文本文件 nowcoder.txt中的空行
        count=0
        while read value
        do
        let count+=1
        if [[ ${value} != "" ]];then
        echo  $value
        fi
        done
        
        
        
        exit 0
        
        #写一个 bash脚本以输出一个文本文件 nowcoder.txt中空行的行号,可能连续,从1开始
        count=0
        while read value
        do
        let count+=1
        if [[ ${value} == "" ]];then
        echo  $count
        fi
        done
        
        
        exit 0
        #写一个 bash脚本以输出一个文本文件 nowcoder.txt 中第5行的内容。
        array=()
        count=0
        while read value
        do
        let count+=1
        if [ $count -eq 5 ];then
        echo $value
        exit
        fi
        done
        
        
        
        
        
        
        exit 0
        #写一个 bash脚本以输出数字 0 到 500 中 7 的倍数(0 7 14 21...)的命令
        for x in `seq 0 7 100`;do
            echo $x
        done
        for(( i=0;i<=500;i=i+7))
        do
        echo $i
        done
        
        for 
3、sql学习
    学习链接：https://blog.csdn.net/fashion2014/article/details/78826299/
        –1.学生表
		Student(s_id,s_name,s_birth,s_sex) --学生编号,学生姓名, 出生年月,学生性别
		–2.课程表
		Course(c_id,c_name,t_id) – --课程编号, 课程名称, 教师编号
		–3.教师表
		Teacher(t_id,t_name) --教师编号,教师姓名
		–4.成绩表
		Score(s_id,c_id,s_score) --学生编号,课程编号,分数
    9、查询学过编号为"01"并且也学过编号为"02"的课程的同学的信息
        a.
            SELECT  DISTINCT f.s_id,f.s_name,f.s_birth,f.s_sex FROM (SELECT  Student.s_name,Student.s_birth,Student.s_id,Student.s_sex FROM Student  LEFT JOIN  Score on  Score.c_id=01 WHERE Student.s_id=Score.s_id) as f
        left  join
         (SELECT Score.s_id  FROM Student  LEFT JOIN  Score on    Score.c_id=02 WHERE  Score.c_id is not NULL and  Student.s_id=Score.s_id) as f1 on 
         f.s_id=f1.s_id
        b.
            SELECT F.s_id,F.s_name,F.s_birth,F.s_sex  FROM  (SELECT Student.*,COUNT(Score.c_id) as c FROM Student LEFT JOIN Score on  Student.s_id=Score.s_id  WHERE Score.c_id=01  or Score.c_id=02    GROUP BY Student.s_id  HAVING  c>1)  AS F
        学到的知识点：
            1、每个派生表必须要有别名。
            2、group by 是通过分组
            3、having 是把分组好的组某个属性再进行聚合，就是用使用聚合函数的列别名再选
            4、左查询中on 后面最好不要用or 要不然每次查询的数据都太多了
            5、distinct字段多表查询时候不要用，没啥用
            6、查询的时候可以进行 not in (1,2)
            7、 s.c is not null 代表某个字段不为null 
'''
#拓展
class ListMetaclass(type):
    def __new__(cls, name, bases, attrs):
        # print(cls)#当前准备创建的类的对象
        # print(name)#类的名字
        # print(bases)#类继承的父类集合
        # # print(attrs)#类的方法集合

        attrs['add'] = lambda self, value: self.append(value)
        # print(attrs)
        return type.__new__(cls, name, bases, attrs)

class MyList(list, metaclass=ListMetaclass):
    pass
#
# print(dir(l))
# print(l.f())
# class T:
#
#     pass
# T.test()
# print(type(T))

# def fn(self,name='name'):
#     print(name)
# H = type('H',(object,),dict(h=fn))
# s = H()
# s.h()

#sqlalcemy
import  sqlalchemy
from  sqlalchemy import create_engine,Table,MetaData
from sqlalchemy.ext.declarative import declarative_base
from sqlalchemy import Column, Integer, String
from  sqlalchemy.orm import mapper,sessionmaker
engine = create_engine("mysql+pymysql://root:123456@10.235.97.220:3309/study",encoding='utf-8')#创建需要操作的sql对象，相当于创建连接池
# echo=True是否开启打印
Base = declarative_base()#相当于创建鸡肋对象，对于class表模型都要继承
# print(dir(Base))
# print(dir(Base.metadata))
#第一步创建方式
class User(Base):
    __tablename__ = 'user'  # 表名
    id = Column(Integer, primary_key=True)
    name = Column(String(32))
    password = Column(String(64))
    def __init__(self,**kwargs):
        self.k_d = {}
        for k,v in kwargs.items():
            self.k_d[k] = v
    def __repr__(self):
        return "<User(name='%s',  password='%s')>" % (
                self.name, self.password)
    @classmethod
    def query(cls,id):#现在实现了自查方法，后面需要把session close掉
        f = cls.db_connet().query(cls).filter(cls.id==id).first()
        cls.session.close()
        return f
    @classmethod
    def query_id(cls,id):
        f = cls.db_connet().query(cls).filter(cls.id==id).first()
    @classmethod
    def db_connet(cls):
        Session_Class = sessionmaker(bind=engine)  # 示例和engine绑定
        cls.session = Session_Class()
        return cls.session
    # @classmethod
    # def db_disconnet(cls):
    #     Session_Class = sessionmaker(bind=engine)  # 示例和engine绑定
    #     # session = Session_Class()
    #     return  Session_Class
    def __enter__(self):
        return  eval("%s.query(%s)"%((self.__class__.__name__),self.k_d['id']))
    def __exit__(self, exc_type, exc_val, exc_tb):
        print("exit")

with User(id=27) as f  :
    print(f)
exit(0)
User.query(id=27)
Base.metadata.create_all(engine)#创建表结构 （这里是父类调子类）
# exit(0)
#第二创建方式
# metadata = MetaData()
#
# user = Table('user', metadata,
#             Column('id', Integer, primary_key=True),
#             Column('name', String(50)),
#             Column('password', String(12))
#         )
#
# class User(object):
#     def __init__(self, name, id, password):
#         self.id = id
#         self.name = name
#         self.password = password
#     def __repr__(self):#如果想具体看清楚，则定义这个
#         return "<User(name='%s',  password='%s')>" % (
#             self.name, self.password)
# mapper(User,user)#把User和user关联起来

# the table metadata is created separately with the Table construct,
# then associated with the User class via the mapper() function

#创建与数据库的会话session class ,注意,这里返回给session的是个class,不是实例
Session_Class = sessionmaker(bind=engine)#示例和engine绑定
session = Session_Class()
#插入
# user_obj = User(id=27,name="fgf",password="123456")  #生成你要创建的数据对象


# session.add(user_obj)# 把要创建的数据对象添加到这个session里， 一会统一创建
# session.commit()#统一创建


#查询
my_user = session.query(User).filter_by(name='fgf').first()
# print(dir(my_user))#sqlalchemy把返回数据映射成对象，其中字段就包括id password name  ,my_user.id调用即可

#多条件查询
my_user1 = session.query(User).filter(User.id>2).all()

#修改
my_user = session.query(User).filter_by(name="fenggf").first()
# print("----------")
# print(dir(my_user))
# print(my_user)
# my_user.name = "fen1ggf"  # 查询出来之后直接赋值修改
# my_user.passwork = "123qwe"
# session.commit()

#回滚
my_user = session.query(User).filter_by(id=27).first()
my_user.name = "Jack"

fake_user = User(name='Rain', password='12345')
session.add(fake_user)

print(session.query(User).filter(User.name.in_(['Jack','rain'])).all() )  #这时看session里有你刚添加和修改的数据

session.rollback() #此时你rollback一下,清楚缓存

# print(session.query(User).filter(User.name.in_(['Jack','rain'])).all() ) #再查就发现刚才添加的数据没有了。

#统计
session.query(User).filter(User.name.like("f%")).count()