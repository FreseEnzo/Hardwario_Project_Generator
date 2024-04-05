"""my_west_extension.py

Basic example of a west extension."""

from textwrap import dedent  # just for nicer code indentation

from west.commands import WestCommand  # your extension must subclass this
from west import log  # use this for user output
from west.configuration import config
from west.manifest import Manifest
from west.util import WestNotFound
from project_generator import run
import os
import sys

def get_west_workspace_root():
    try:
        # Load the manifest. This operation will fail if not run inside a west workspace.
        manifest = Manifest.from_file()

        # The topdir attribute of the manifest object gives you the absolute path to the workspace root.
        return manifest.topdir

    except WestNotFound:
        # Handle the case where the script is not run inside a west workspace
        log.err("Error: Not inside a west workspace. Please run this within a west-managed directory.")
        sys.exit(1)


class ProjectUpdate(WestCommand):

    def __init__(self):
        super().__init__(
            "chester-update",  # gets stored as self.name
            "Generate Hardwario Skeleton Project based in a YAML",  # self.help
            # self.description:
            dedent(
                """
            This helper command generates Hardwario Skeleton Project based in a YAML."""
            ),
        )

    def do_add_parser(self, parser_adder):
        # This is a bit of boilerplate, which allows you full control over the
        # type of argparse handling you want. The "parser_adder" argument is
        # the return value of an argparse.ArgumentParser.add_subparsers() call.
        parser = parser_adder.add_parser(
            self.name, help=self.help, description=self.description
        )
        parser.add_argument('name', help='Name of the project')
        
        return parser  
    def do_run(self, args, unknown_args):
        topdir = get_west_workspace_root()
        try:
            if(run(topdir,prj_name=args.name, mode='update')):  
                log.inf("★ Project successfully updated.", colorize=True)
        except:
             log.err("⊗ Project unsuccessfully updated.")