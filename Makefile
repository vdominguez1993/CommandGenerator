
FILES_TO_FORMAT := $(shell find . -type f -name "*.py*" -not -path "./__pycache__/*")

.PHONY: format

format:
	black -l 80 $(FILES_TO_FORMAT)
	pylint $(FILES_TO_FORMAT)