#include <iostream>
#include <vector>
#include <memory>
#include <chrono>
#include <thread>
#include <questdb/ilp/line_sender.hpp>

int sendsPerThread = 500;
int metricCountPerSend = 10000;

void sendMetricsIlp(std::string id) {
  std::string tenantName = "test-tenant-1659670465" + id;
  std::string metricBaseName = "c8db_service_dynamo_query_execution_";

  const std::string_view document = ("{"
  "\"label1\":\"something\","
  "\"cluster-id\":\"metrics-ap-west\"}");

  questdb::ilp::line_sender_buffer buffer;

  for (int j =0; j < sendsPerThread; j++) {
    for (int i=0; i < metricCountPerSend; i++) {
      buffer
        .table("metrics")
        .symbol("tenant", tenantName)
        .symbol("fabric", "test-fabric-1659708340-1-"+std::to_string(j))
        .symbol("type", "counter")
        .symbol("metric", metricBaseName + std::to_string(i))
        .column("document", document)
        .column("value", 1.0);

      auto time = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
      buffer.at(questdb::ilp::timestamp_nanos{time});
    }
    try {
      questdb::ilp::line_sender sender{"localhost", "9009"};
      sender.flush(buffer);
    } catch (const std::exception& ex) {
      std::cout<<"Exception caught: " << ex.what() <<std::endl;
      buffer.clear();
      continue;
    }
  }
}

int main(int argc, char** argv) {
  int threadCount = 15;
  std::cout<<"Using "<<threadCount<<" threads and each thread sends: "<< sendsPerThread
          <<" sends. Metric Count per Send: "<<metricCountPerSend<<std::endl;

  std::vector<std::shared_ptr<std::thread>> vec;
  for (int i=0; i< threadCount; i++) {
    vec.push_back(std::make_shared<std::thread>(sendMetricsIlp, std::to_string(i)));
  }
  for (int i=0; i< threadCount; i++) {
    vec[i]->join();;
  }
  std::cout<<"Done ... !"<<std::endl;
  return 0;
}
