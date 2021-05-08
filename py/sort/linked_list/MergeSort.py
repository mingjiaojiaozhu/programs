#!/usr/bin/env python
# -*- coding:gbk -*-

class ListNode:
    def __init__(self, value: int):
        self.value, self.next = value, None

class MergeSort:
    def sort(self, head: ListNode) -> None:
        self.__sort(head, head.next)

    def __sort(self, head: ListNode, start: ListNode) -> None:
        if not start.next:
            head.next = start
            return

        left, right, middle = ListNode(0), ListNode(0), self.__getMiddle(start)
        left.next, right.next, middle.next = start, middle.next, None

        self.__sort(left, left.next)
        self.__sort(right, right.next)
        self.__merge(head, left.next, right.next)

    def __merge(self, head: ListNode, left: ListNode, right: ListNode) -> None:
        current = head
        while left and right:
            if left.value > right.value:
                current.next, right = right, right.next
            else:
                current.next, left = left, left.next
            current = current.next

        if left:
            current.next = left
        if right:
            current.next = right

    def __getMiddle(self, start: ListNode) -> ListNode:
        if not start.next:
            return start

        slow, fast = start, start.next
        while fast and fast.next:
            slow, fast = slow.next, fast.next.next
        return slow
