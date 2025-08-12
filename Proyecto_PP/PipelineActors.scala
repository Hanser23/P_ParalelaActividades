sealed trait Msg
case class Start(jobId:String, dataPath:String) extends Msg
case class SparkDone(jobId:String, rddSec:Double, dfSec:Double) extends Msg
case class Error(jobId:String, cause:String, attempt:Int) extends Msg

class Validator(next: ActorRef) extends Actor {
  def receive = { case s: Start =>
    if (s.dataPath.nonEmpty) next ! s else sender() ! Error(s.jobId,"invalid input",0)
  }
}

class Submitter(analyzer: ActorRef) extends Actor {
  def receive = { case Start(jobId, path) =>
    // llamar Function spark-submit (HTTP) y hacer polling con backoff
    context.system.scheduler.scheduleOnce(0.seconds)(/* invoke */)(context.dispatcher)
  }
}

class Analyzer(responder: ActorRef) extends Actor {
  def receive = { case SparkDone(jobId, rdd, df) =>
    val speedup = rdd / df
    responder ! s"""{"jobId":"$jobId","speedup":$speedup}"""
  }
}

class Responder() extends Actor {
  def receive = { case payload: String => println(payload) /* o escribir Cosmos/emitir HTTP */ }
}
