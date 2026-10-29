.PHONY: test test-core test-python test-all
test: test-core test-python

test-all: test

test-core:
	@set -eu; build=$$(mktemp -d); trap 'rm -rf "$$build"' EXIT; \
	for source in lessons/*/test.cpp; do \
	  echo "Testing $$source"; \
	  $${CXX:-g++} -std=c++17 -Wall -Wextra -Werror -pedantic "$$source" -o "$$build/test"; \
	  "$$build/test"; \
	done
	python3 -m unittest discover -s tests -v

test-python:
	@set -eu; for directory in lessons/*-python; do \
	  echo "Testing $$directory"; \
	  python3 -B -m unittest discover -s "$$directory" -p 'test_*.py' -v; \
	done
