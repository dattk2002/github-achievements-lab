.PHONY: test
test:
	@set -eu; build=$$(mktemp -d); trap 'rm -rf "$$build"' EXIT; \
	for source in lessons/*/test.cpp; do \
	  echo "Testing $$source"; \
	  $${CXX:-g++} -std=c++17 -Wall -Wextra -Werror -pedantic "$$source" -o "$$build/test"; \
	  "$$build/test"; \
	done
	python3 -m unittest discover -s tests -v
