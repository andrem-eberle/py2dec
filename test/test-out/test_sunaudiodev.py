from test.test_support import findfile, TestFailed, import_module
import unittest
sunaudiodev = import_module('sunaudiodev',deprecated=True)
import os
try:
    audiodev = os.environ['AUDIODEV']
except KeyError:
        audiodev = '/dev/audio'
