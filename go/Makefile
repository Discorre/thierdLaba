# Go parameters
GOCMD=go
GOBUILD=$(GOCMD) build
GOCLEAN=$(GOCMD) clean
GOTEST=$(GOCMD) test
GOGET=$(GOCMD) get
BINARY_NAME=my_hash_map_bench
BENCHMARK_FILE=my_hash_map_bench_test.go myHashMap.go myList.go
BENCHMARK_FLAGS=-bench=. -benchmem
COVERAGE_FILE=coverage.out
COVERAGE_HTML=coverage.html
TEST_DIRECTORY=testFiles

all: benchmark

build:
	$(GOBUILD) -o $(BINARY_NAME) $(BENCHMARK_FILE)

clean: cleanSeri
	$(GOCLEAN)
	rm -f $(BINARY_NAME)
	rm -f $(COVERAGE_FILE)
	rm -f $(COVERAGE_HTML)
	rm -rf $(TEST_DIRECTORY)
	rm -f benchmark_test.txt
	rm -f hashmap.bin

cleanSeri:
	rm -f hashmap.bin

seri: cleanSeri
	go run seri.go myHashMap.go myList.go

benchmark:
	$(GOTEST) $(BENCHMARK_FLAGS) -run=^$$ -bench=. $(BENCHMARK_FILE)

profile:
	$(GOTEST) -cpuprofile=cpu.prof -memprofile=mem.prof -bench=. $(BENCHMARK_FILE)
	go tool pprof -http=:8080 cpu.prof

coverage: clean
	mkdir $(TEST_DIRECTORY)
	$(GOTEST) $(BENCHMARK_FLAGS) -run=^$$ -coverprofile=$(COVERAGE_FILE) $(BENCHMARK_FILE)
	$(GOCMD) tool cover -html=$(COVERAGE_FILE) -o $(COVERAGE_HTML)
	@echo "Coverage report generated: $(COVERAGE_HTML)"

coverage-view: clean coverage
	xdg-open $(COVERAGE_HTML)

.PHONY: all build clean benchmark profile coverage coverage-view