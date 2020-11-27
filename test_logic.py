import pytest
import unittest
import _build_gate


def set_up_two_node():
    n1 = _build_gate.node()
    n1.str_set("1100")
    n2 = _build_gate.node()
    n2.str_set("1010")
    return [n1, n2]


class LogicTest(unittest.TestCase):
    def test_nand(self):
        tem = set_up_two_node()
        n3 = _build_gate.node(_build_gate.mynand, tem)
        n3.no_run()
        self.assertEqual(n3.__str__(), "11111111111111111111111111110111")

    def test_and(self):
        tem = set_up_two_node()
        n3 = _build_gate.node(_build_gate.myand, tem)
        n3.no_run()
        self.assertEqual(n3.__str__(), "00000000000000000000000000001000")

    def test_or(self):
        tem = set_up_two_node()
        n3 = _build_gate.node(_build_gate.myor, tem)
        n3.no_run()
        print(n3)
        self.assertEqual(n3.__str__(), "00000000000000000000000000001110")

    def test_xor(self):
        tem = set_up_two_node()
        n3 = _build_gate.node(_build_gate.myxor, tem)
        n3.no_run()
        print(n3)
        self.assertEqual(n3.__str__(), "00000000000000000000000000000110")

    def test_nor(self):
        tem = set_up_two_node()
        n3 = _build_gate.node(_build_gate.mynor, tem)
        n3.no_run()
        print(n3)
        self.assertEqual(n3.__str__(), "11111111111111111111111111110001")

    def test_not(self):
        n3 = _build_gate.node()
        n3.str_set("01")
        n4 = _build_gate.node(_build_gate.mynot, [n3])
        n4.no_run()
        print(n4)
        self.assertEqual(n4.__str__(), "11111111111111111111111111111110")

    def test_buf(self):
        n3 = _build_gate.node()
        n3.str_set("01")
        n4 = _build_gate.node(_build_gate.mybuf, [n3])
        n4.no_run()
        print(n4)
        self.assertEqual(n4.__str__(), "00000000000000000000000000000001")
