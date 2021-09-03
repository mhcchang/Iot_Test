#coding:utf-8
'''
author:
function:
param:
other
'''
import sys,os
sys.path.append(os.path.abspath('../'))
from  study.test_db.model.utils.config import *
import sqlalchemy
from sqlalchemy import create_engine, Table, MetaData
from sqlalchemy.ext.declarative import declarative_base
from sqlalchemy import Column, Integer, String
from sqlalchemy.orm import mapper, sessionmaker

engine = create_engine("mysql+pymysql://%s:%s@%s:%s/%s"%(USER,PSD,SQL,PORT,DATABASE),
					   encoding='utf-8',isolation_level="READ UNCOMMITTED")  # 创建需要操作的sql对象，相当于创建连接池
Base = declarative_base()  # 相当于创建鸡肋对