from pyspark.sql import SparkSession, functions as F
import time, sys
spark = SparkSession.builder.getOrCreate()
path, out = sys.argv[1], sys.argv[2]

t0 = time.time()
df = spark.read.json(path)  # esquema: {value: float}
met = df.agg(F.count("*").alias("count"), F.mean("value").alias("mean"), F.stddev("value").alias("stdev"))
met.write.mode("overwrite").parquet(out+"/df_metrics")
t1 = time.time()
print({"stage":"DataFrame","seconds":t1-t0})
