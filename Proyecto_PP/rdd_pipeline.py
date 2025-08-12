from pyspark import SparkContext
from pyspark.sql import SparkSession
import time, json, sys

sc = SparkContext.getOrCreate()
spark = SparkSession.builder.getOrCreate()
path = sys.argv[1]  # ADLS path con datos normalizados (jsonlines/csv)
out = sys.argv[2]

t0 = time.time()
rdd = sc.textFile(path).map(lambda x: float(json.loads(x)["value"]))
count = rdd.count()
mean  = rdd.mean()
stdev = rdd.stdev()
spark.createDataFrame([(count,mean,stdev)], ["count","mean","stdev"]).write.mode("overwrite").parquet(out+"/rdd_metrics")
t1 = time.time()
print(json.dumps({"stage":"RDD","seconds":t1-t0}))
