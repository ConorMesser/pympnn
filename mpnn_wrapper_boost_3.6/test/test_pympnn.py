import unittest
import pympnn
from math import sin

PI = 3.1415926535897932385


class TestCollision(unittest.TestCase):
    def setUp(self) -> None:
        self.linear_tree = pympnn.KDTree_topologies(1, 2, [1], [1], 10)
        self.circular_tree = pympnn.KDTree_topologies(1, 3, [2], [1], 10)

        self.linear_tree.add_point([0])
        self.linear_tree.add_point([1])
        self.linear_tree.add_point([1.5])
        self.linear_tree.add_point([1.6])
        self.linear_tree.add_point([2])
        self.linear_tree.add_point([25])
        self.linear_tree.add_point([6.27])

        self.circular_tree.add_point([0])
        self.circular_tree.add_point([1])
        self.circular_tree.add_point([1.5])
        self.circular_tree.add_point([6])
        self.circular_tree.add_point([PI * 2])

    def test_linear(self):
        dist, ind = self.linear_tree.k_nearest_neighbor([0], 2)
        self.assertAlmostEqual(0, dist[0])
        self.assertAlmostEqual(1, dist[1])
        self.assertEqual([0, 1], ind)

        dist, ind = self.linear_tree.k_nearest_neighbor([1.55], 2)
        self.assertAlmostEqual(0.05, dist[0])
        self.assertAlmostEqual(0.05, dist[1])
        self.assertEqual([2, 3], ind)

        dist, ind = self.linear_tree.k_nearest_neighbor([6.28], 2)
        self.assertAlmostEqual(0.01, dist[0])
        self.assertAlmostEqual(4.28, dist[1])
        self.assertEqual([6, 4], ind)

        dist, ind = self.linear_tree.k_nearest_neighbor([25], 2)
        self.assertAlmostEqual(0, dist[0])
        self.assertAlmostEqual(18.73, dist[1])
        self.assertEqual([5, 6], ind)

    def test_circular(self):
        dist, ind = self.circular_tree.k_nearest_neighbor([0], 3)
        self.assertAlmostEqual(0, dist[0])
        self.assertAlmostEqual(0, dist[1])
        self.assertAlmostEqual(2 * PI - 6, dist[2])
        self.assertEqual([0, 4, 3], ind)

        dist, ind = self.circular_tree.k_nearest_neighbor([1.25], 3)
        self.assertAlmostEqual(0.25, dist[0])
        self.assertAlmostEqual(0.25, dist[1])
        self.assertAlmostEqual(1.25, dist[2])
        self.assertEqual([1, 2, 0], ind)

        dist, ind = self.circular_tree.k_nearest_neighbor([6], 3)
        self.assertAlmostEqual(0, dist[0])
        self.assertAlmostEqual(2 * PI - 6, dist[1])
        self.assertAlmostEqual(2 * PI - 6, dist[2])
        self.assertEqual([3, 0, 4], ind)

    def test_within_distance(self):
        pass

    def test_max_size(self):
        pass

    def test_large_tree_no_bugs(self):
        big_tree = pympnn.KDTree_topologies(2, 5, [1, 2], [1, 1], 100002)

        for i in range(100000):
            big_tree.add_point([i, sin(i) * PI])
            dist, ind = big_tree.k_nearest_neighbor([i + 0.5, sin(i) * PI], 5)

    # def test_bug(self):
    #     big_tree = pympnn.KDTree_topologies(2, 1, [1, 2], [1, 1], 1001)
    #     big_tree.add_point([0, 0])
    #
    #     for i in range(100):
    #         dist, ind = big_tree.k_nearest_neighbor([i + 0.5, sin(i) * PI], 1)
    #
    #         true_insertion = [i]
    #         new_rotation = [sin(i) * PI]
    #         query_pt = true_insertion + new_rotation
    #         query_pt[::2] = true_insertion
    #         query_pt[1::2] = new_rotation
    #
    #
    #         x = true_insertion + new_rotation
    #         x[::2] = true_insertion
    #         x[1::2] = new_rotation
    #         big_tree.add_point(x)
    #
    #     dist_2, ind_2 = big_tree.k_nearest_neighbor([5, 2], 7)
    #
    #     print(ind_2)
    #
    #     big_tree.add_point([10, 1])
    #
    #     self.assertTrue(True)



