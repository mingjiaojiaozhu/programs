#!/usr/bin/env python
# -*- coding:gbk -*-

class ListNode:
    def __init__(self, value: int):
        self.value, self.next = value, None

class BubbleSort:
    def sort(self, head: ListNode) -> None:
        border = None
        while head.next.next != border:
            flag, prev, current = False, head, head.next
            while current.next != border:
                if current.value > current.next.value:
                    next = current.next
                    current.next, next.next, prev.next = next.next, prev.next, next

                    flag, current = True, prev.next
                prev, current = prev.next, current.next
            border = current

            if not flag:
                break
