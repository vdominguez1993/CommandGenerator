PHONY: run build generate

run: build
	./example

build: generate main.c
	gcc main.c generated/process_command.c -o example -I.

generate: example.yaml
	python3 ../command_generator.py -i example.yaml -o generated