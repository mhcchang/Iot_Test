# coding:utf-8
'''
author:
function:
param:
other
'''
#云图接口所需要的的字典
from test_ga.model.utils.sql_operate import sql_operate as sql
from  test_ga.ga_schema.utils.fun_type import *
from test_ga.ga_schema.Face.model import Face_param,SubImageList as sl
class FaceListObject():
	def __init__(self):
		pass
	@classmethod
	def face(cls):
		cls.FaceObject = [FaceList()]
		return cls()

#FaceObject中单个key-value
class FaceList():
	def __init__(self):
		for x in sql.query_all(Face_param):
			arg = x.name
			self.__dict__[arg] = (fun_type_se(x))
		# self.FaceID = Face_Param.add_face_param(name="FaceID", type="string", funcType="6", funcArgs="48",
		# 										required="R", describe="")

		# self.InfoKind = Face_Param.add_face_param(name="InfoKind", type="number", funcType="3", funcArgs="0,1,2",
		# 										  required="R", describe="")
		#
		# self.SourceID = Face_Param.add_face_param(name="SourceID", type="string", funcType="11", funcArgs="0,41",
		# 										  required="o", describe="")
		#
		# self.DeviceID = Face_Param.add_face_param(name="DeviceID", type="string", funcType="11", funcArgs="0,20",
		# 										  required="R", describe="")
		#
		# self.LeftTopX = Face_Param.add_face_param(name="LeftTopX", type="number", funcType="13", funcArgs="0,100000",
		# 										  required="o", describe="")
		#
		# self.LeftTopY = Face_Param.add_face_param(name="LeftTopY", type="number", funcType="13", funcArgs="0,100000",
		# 										  required="o", describe="")
		#
		# self.RightBtmX = Face_Param.add_face_param(name="RightBtmX", type="number", funcType="13", funcArgs="0,100000",
		# 										   required="o", describe="")
		#
		# self.RightBtmY = Face_Param.add_face_param(name="RightBtmY", type="number", funcType="13", funcArgs="0,100000",
		# 										   required="o", describe="")
		#
		# self.IsDriver = Face_Param.add_face_param(name="IsDriver", type="number", funcType="3", funcArgs="0,1,2",
		# 										  required="o", describe="")
		#
		# self.IsSuspectedTerrorist = Face_Param.add_face_param(name="IsSuspectedTerrorist", type="number", funcType="3",
		# 													  funcArgs="0,1,2",
		# 													  required="o", describe="")
		#
		# self.IsSuspectedTerrorist = Face_Param.add_face_param(name="IsSuspectedTerrorist", type="number", funcType="3",
		# 													  funcArgs="0,1,2",
		# 													  required="o", describe="")
		# self.IsCriminalInvolved = Face_Param.add_face_param(name="IsCriminalInvolved", type="number", funcType="3",
		# 													funcArgs="0,1,2",
		# 													required="o", describe="")
		# self.IsDetainees = Face_Param.add_face_param(name="IsDetainees", type="number", funcType="3", funcArgs="0,1,2",
		# 											 required="o", describe="")
		# self.IsSuspiciousPerson = Face_Param.add_face_param(name="IsSuspiciousPerson", type="number", funcType="3", funcArgs="0,1,2",
		# 											 required="o", describe="")
		#
		# self.IsVictim = Face_Param.add_face_param(name="IsVictim", type="number", funcType="3", funcArgs="0,1,2",
		# 											 required="o", describe="")
		#
		# self.LocationMarkTime = Face_Param.add_face_param(name="LocationMarkTime", type="string", funcType="12",
		# 												  funcArgs="0,14",
		# 											 required="o", describe="")
		#
		#
		# self.FaceAppearTime = Face_Param.add_face_param(name="FaceAppearTime", type="string", funcType="12",
		# 												  funcArgs="0,14",
		# 											 required="o", describe="")
		#
		#
		# self.PersonDisAppearTime = Face_Param.add_face_param(name="PersonDisAppearTime", type="string", funcType="12",
		# 												  funcArgs="0,14",
		# 											 required="o", describe="")
		#
		# self.IDType = Face_Param.add_face_param(name="IDType", type="string", funcType="3",
		# 												  funcArgs="'','111','114','123','413'",
		# 											 required="o", describe="")
		#
		# self.IDNumber = Face_Param.add_face_param(name="IDNumber", type="string", funcType="4",
		# 												  funcArgs="0,64",
		# 											 required="o", describe="")
		#
		#
		# self.Name = Face_Param.add_face_param(name="Name", type="string", funcType="4",
		# 												  funcArgs="0,64",
		# 											 required="o", describe="")
		#
		# self.UsedName = Face_Param.add_face_param(name="UsedName", type="string", funcType="4",
		# 												  funcArgs="0,64",
		# 											 required="o", describe="")
		#
		# self.Alias = Face_Param.add_face_param(name="Alias", type="string", funcType="4",
		# 												  funcArgs="0,64",
		# 											 required="o", describe="")
		#
		# self.GenderCode = Face_Param.add_face_param(name="GenderCode", type="string", funcType="8",
		# 												  funcArgs="reusedRules/GenderCodeType",
		# 											 required="o", describe="")
		#
		# self.AgeUpLimit = Face_Param.add_face_param(name="AgeUpLimit", type="string", funcType="13",
		# 												  funcArgs="0,120",
		# 											 required="o", describe="")
		#
		# self.AgeLowerLimit = Face_Param.add_face_param(name="AgeLowerLimit", type="string", funcType="13",
		# 												  funcArgs="0,120",
		# 											 required="o", describe="")
		#
		# self.EthicCode = Face_Param.add_face_param(name="EthicCode", type="string", funcType="8",
		# 												  funcArgs="reusedRules/EthicCodeType",
		# 											 required="o", describe="")
		#
		# self.NationalityCode = Face_Param.add_face_param(name="NationalityCode", type="string", funcType="4",
		# 												  funcArgs="0,3",
		# 											 required="o", describe="")
		# self.NativeCityCode = Face_Param.add_face_param(name="NativeCityCode", type="string", funcType="4",
		# 												  funcArgs="0,12",
		# 											 required="o", describe="")
		#
		# self.ResidenceAdminDivision = Face_Param.add_face_param(name="ResidenceAdminDivision", type="string", funcType="4",
		# 												  funcArgs="0,12",
		# 											 required="o", describe="")
		# self.ChineseAccentCode = Face_Param.add_face_param(name="ChineseAccentCode", type="string", funcType="4",
		# 												  funcArgs="0,6",
		# 											 required="o", describe="")
		self.SubImageList =eval(Face_Param.add_face_param(name="SubImageList", type="object", funcType="20",#20代表object
														  funcArgs="0,6",
													 required="o", describe="SubImageList()"))
		pass

class SubImageList:
	def __init__(self):
		self.SubImageInfoObject=[SubImageInfo()]
class SubImageInfo:
	def __init__(self):
		for x in sql.query_all(sl):
			arg = x.name
			self.__dict__[arg] = (fun_type_se(x))

		#若存入sql后，后期不执行
		# self.ImageID =subimagelist.add_face_param(name="ImageID", type="string", funcType="6", funcArgs="41",
		# 										required="R", describe="")
		#
		# self.Type =subimagelist.add_face_param(name="Type", type="string", funcType="6", funcArgs="01,02,03,04,05,"
		# 																							 "06,07,08,09,10,"
		# 																							 "11,12,13,14,100",
		# 										required="R", describe="")
		# self.InfoKind =subimagelist.add_face_param(name="InfoKind", type="string", funcType="6", funcArgs="01,02,03,04,05,"
		# 																							 "06,07,08,09,10,"
		# 																							 "11,12,13,14,100",
		# 										required="R", describe="")
		#
		# self.ImageSource =subimagelist.add_face_param(name="ImageSource", type="string", funcType="6", funcArgs="01,02,03,04,05,"
		# 																							 "06,07,08,09,10,"
		# 																							 "11,12,13,14,100",
		# 										required="R", describe="")
		#
		#
		# self.EventSort =subimagelist.add_face_param(name="EventSort", type="number", funcType="13", funcArgs="0,36",
		# 										required="R", describe="")
		#
		# self.DeviceID = subimagelist.add_face_param(name="DeviceID", type="string", funcType="11", funcArgs="0,20",
		# 										  required="R", describe="")
		#
		# self.FileFormat = subimagelist.add_face_param(name="FileFormat", type="string", funcType="3", funcArgs="jpeg",
		# 										  required="R", describe="")
		#
		# self.ShotTime = subimagelist.add_face_param(name="ShotTime", type="string", funcType="3", funcArgs="0,14",
		# 										  required="R", describe="")
		#
		# self.Title = subimagelist.add_face_param(name="Title", type="string", funcType="3", funcArgs="0,128",
		# 											required="R", describe="")
		#
		# self.ContentDescription = subimagelist.add_face_param(name="ContentDescription", type="string", funcType="3",
		# 													  funcArgs="0,1024",
		# 											required="R", describe="")
		# self.ShotPlaceFullAdress = subimagelist.add_face_param(name="ShotPlaceFullAdress", type="string", funcType="3",
		# 													  funcArgs="0,100",
		# 											required="R", describe="")
		# self.SecurityLevel = subimagelist.add_face_param(name="SecurityLevel", type="string", funcType="3",
		# 													  funcArgs="8",
		# 											required="R", describe="")
		#
		# self.Width = subimagelist.add_face_param(name="Width", type="number", funcType="3",
		# 													  funcArgs="0,1000000",
		# 											required="R", describe="")
		#
		# self.Height = subimagelist.add_face_param(name="Height", type="number", funcType="3",
		# 													  funcArgs="0,1000000",
		# 											required="R", describe="")
		#
		# self.FileSize = subimagelist.add_face_param(name="FileSize", type="number", funcType="3",
		# 													  funcArgs="0,1000000",
		# 											required="R", describe="")
		#
		#
		# self.Data = subimagelist.add_face_param(name="Data", type="number", funcType="3",
		# 													  funcArgs="0,1000000",
		# 											required="R", describe="")
# print(dir(SubImageInfo()))


#存到sql
class subimagelist():
	@classmethod
	def add_face_param(cls, **kwargs):
		if sql.query(sl, name=str(kwargs['name'])):
			sql.add(sl, **kwargs)
		else:
			pass
		return kwargs['describe']
class Face_Param():
	@classmethod
	def add_face_param(cls, **kwargs):
		if sql.query(Face_param, name=str(kwargs['name'])):
			sql.add(Face_param, **kwargs)
		else:
			pass
		return kwargs['describe']
#对外返回人脸采集的object
class Face:
	@classmethod
	def add_att(cls):
		cls.FaceListObject = FaceListObject.face()
		return cls()

