#!/usr/bin/env python
# -*- coding:gbk -*-

class ListNode:
    def __init__(self, value: int):
        self.value, self.next = value, None

class QuickSort:
    def sort(self, head: ListNode) -> None:
        self.__sort(head, head.next, None)

    def __sort(self, head: ListNode, start: ListNode, end: ListNode) -> None:
        if start == end or start.next == end:
            return

        partition = self.__getPartition(head, start, end)
        self.__sort(head, head.next, partition)
        self.__sort(partition, partition.next, end)

    def __getPartition(self, head: ListNode, start: ListNode, end: ListNode) -> None:
        headLeft, headRight = ListNode(0), ListNode(0)
        pivot, left, right, node = start.value, headLeft, headRight, start.next
        while node != end:
            if node.value < pivot:
                left.next, left = node, node
            else:
                right.next, right = node, node
            node = node.next
        left.next, right.next = start, end

        head.next, start.next = headLeft.next, headRight.next
        return start
