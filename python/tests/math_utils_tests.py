#!/bin/env python3

import unittest

from common import math_utils

class MathUtilsTests(unittest.TestCase):
    def test_arithmetic_sequence_sum(self):
        self.assertEqual(math_utils.arithmetic_sequence_sum(1, 101, 1), 5050)
        self.assertEqual(math_utils.arithmetic_sequence_sum(1, 101, 2), 2500)

if __name__ == "__main__":
    unittest.main()
