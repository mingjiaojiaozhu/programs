#!/usr/bin/env python
# -*- coding:gbk -*-

class ListNode:
    def __init__(self, value: int):
        self.value, self.next = value, None

class BinarySearch:
    def search(self, head: ListNode, target: int) -> ListNode:
        return self.__search(head.next, None, target)

    def __search(self, start: ListNode, end: ListNode, target: int) -> ListNode:
        if start == end:
            return start if start and target == start.value else None

        middle = self.__getMiddle(start, end)
        if target == middle.value:
            return middle

        if target < middle.value:
            return self.__search(start, middle, target)
        return self.__search(middle.next, None, target)

    def __getMiddle(self, start: ListNode, end: ListNode) -> ListNode:
        slow, fast = start, start.next
        while fast != end and fast.next != end:
            slow, fast = slow.next, fast.next.next
        return slow
