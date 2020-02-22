""" Python script to generate a command parser given a configuration file.
    The generation will be template based, this way it won't depend on the language.
"""
import argparse
import logging
import os
import subprocess
import yaml

import jinja2

import common_utils


def check_me():
    """ Function to format this file with black and to check it with pylint
    """
    file_to_check = os.path.abspath(__file__)
    subprocess.call(["black", "-l", "80", file_to_check])
    subprocess.call(["pylint", file_to_check])


def get_function_types(subcommand_params):
    """ Reads all subcommands and returns a set with all the types of functions used
    """
    list_functions = [
        subcommand["function_type"] for subcommand in subcommand_params
    ]
    return set(list_functions)


class CommandGenerator:
    """ Class of the command generator tool
    """

    def __init__(self, config_file_path, template_folder):
        self.yaml_check_tool = "yamllint"
        self.check_tool_installed = False

        self.config_file_path = config_file_path

        self.template_folder = template_folder
        template_loader = jinja2.FileSystemLoader(searchpath=template_folder)
        self.template_env = jinja2.Environment(loader=template_loader)

        if common_utils.is_installed(self.yaml_check_tool):
            self.check_tool_installed = True
        else:
            logging.warning(
                "%s is not installed and it is recommended",
                self.yaml_check_tool,
            )

    def is_yaml_ok(self, yaml_file):
        """ Check if yaml is OK using yamllint
        """
        retval = subprocess.call([self.yaml_check_tool, yaml_file])
        if retval:
            retval = False
        else:
            retval = True

        return retval

    def apply_template(self, template_file, config_dict, output_file):
        """ Apply a jinja template
        """
        template = self.template_env.get_template(template_file)
        output_text = template.render(
            config_dict=config_dict,
            function_types=config_dict["function_types"],
            get_function_types=get_function_types,
        )
        with open(output_file, "w") as output:
            output.write(output_text)

    def generate(self, output_folder):
        """ Generate the code in a given folder
        """
        retval = False

        # Check if output folder exists, if not create it
        if not os.path.exists(output_folder):
            os.makedirs(output_folder)

        if os.path.exists(self.config_file_path):
            if self.is_yaml_ok(self.config_file_path) is not False:
                with open(self.config_file_path, "r") as config_file:
                    try:
                        config_dict = yaml.safe_load(config_file)
                        output_file = os.path.join(
                            output_folder, "process_command.c"
                        )
                        self.apply_template(
                            "template_c.tmpl", config_dict, output_file
                        )
                        output_file = os.path.join(
                            output_folder, "process_command.h"
                        )
                        self.apply_template(
                            "template_h.tmpl", config_dict, output_file
                        )
                        retval = True
                    except yaml.YAMLError as exc:
                        logging.critical(exc)
            else:
                logging.error("Configuration file is not OK")
        else:
            logging.error("File %s does not exist", self.config_file_path)

        return retval


def main(config_file_path, template_folder, output_folder):
    """ Main function of the script
    """
    # check_me()
    generator = CommandGenerator(config_file_path, template_folder)
    generator.generate(output_folder)


if __name__ == "__main__":
    PARSER = argparse.ArgumentParser()

    PARSER.add_argument(
        "-i",
        "--input",
        required=True,
        dest="configuration_file",
        help="YAML configuration file to generate commands",
    )
    PARSER.add_argument(
        "-o",
        "--output_folder",
        required=True,
        dest="output_folder",
        help="Output folder where code will be generated",
    )
    PARSER.add_argument(
        "-t",
        "--template_folder",
        dest="template_folder",
        default=os.path.join(
            os.path.abspath(os.path.dirname(__file__)), "templates"
        ),
        help="Template folder path",
    )

    ARGS = PARSER.parse_args()
    main(ARGS.configuration_file, ARGS.template_folder, ARGS.output_folder)
