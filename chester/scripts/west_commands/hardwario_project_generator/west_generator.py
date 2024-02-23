'''my_west_extension.py

Basic example of a west extension.'''

from textwrap import dedent            # just for nicer code indentation

from west.commands import WestCommand  # your extension must subclass this
from west import log                   # use this for user output
from project_generator import run
from cmake_generator import cmake
import os
class ProjectGenerator(WestCommand):

    def __init__(self):
        super().__init__(
            'scaffold',  # gets stored as self.name
            'Generate Hardwario Skeleton Project based in a YAML',  # self.help
            # self.description:
            dedent('''
            This helper command generate Hardwario Skeleton Project based in a YAML.'''))

    def do_add_parser(self, parser_adder):
        # This is a bit of boilerplate, which allows you full control over the
        # type of argparse handling you want. The "parser_adder" argument is
        # the return value of an argparse.ArgumentParser.add_subparsers() call.
        parser = parser_adder.add_parser(self.name,
                                         help=self.help,
                                         description=self.description)

        return parser           # gets stored as self.parser

    def do_run(self, args, unknown_args):
        run()
        log.inf('Project successfully created')
        cmake()
        log.inf('CMakeLists.txt successfully created')
 
        
  