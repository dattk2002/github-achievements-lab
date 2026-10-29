RUSTC ?= rustc

.PHONY: test test-core test-python test-java test-typescript test-rust test-all
test: test-core test-python

test-all: test test-java test-typescript test-rust

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

test-java:
	@set -eu; build=$$(mktemp -d); trap 'rm -rf "$$build"' EXIT; \
	for directory in lessons/*-java; do \
	  echo "Testing $$directory"; \
	  java -m jdk.compiler/com.sun.tools.javac.Main -Xlint:all -Werror \
	    -d "$$build" "$$directory"/*.java; \
	  java -cp "$$build" Test; \
	done

test-typescript:
	@set -eu; for directory in lessons/*-typescript; do \
	  echo "Testing $$directory"; \
	  node --test "$$directory/test.mts"; \
	done

test-rust:
	@set -eu; build=$$(mktemp -d); trap 'rm -rf "$$build"' EXIT; \
	for directory in lessons/*-rust; do \
	  echo "Testing $$directory"; \
	  "$(RUSTC)" --edition=2021 -D warnings --test "$$directory/test.rs" -o "$$build/test"; \
	  "$$build/test"; \
	done
