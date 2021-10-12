#coding:utf-8
'''
author:
function:
param:
other
'''
#redis
redis_host = '10.235.97.220'
redis_port = 6378
import redis, uuid
pool = redis.ConnectionPool(host=redis_host, port=redis_port, decode_responses=True)
r_redis = redis.Redis(connection_pool=pool)