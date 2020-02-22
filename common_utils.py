""" Common utilities or functions
"""
import os


def is_installed(program):
    """ Check if a program is installed in the given path
        Returns True if it exists or False if not
    """

    def is_executable(file_path):
        """ Check if given file has executable permissions
        """
        return os.path.isfile(file_path) and os.access(file_path, os.X_OK)

    retval = False

    dirname, _ = os.path.split(program)
    if dirname:
        if is_executable(program):
            retval = True
    else:
        for path in os.environ["PATH"].split(os.pathsep):
            exe_file = os.path.join(path, program)
            if is_executable(exe_file):
                retval = True

    return retval
